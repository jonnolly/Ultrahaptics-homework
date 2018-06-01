#include "stdafx.h"
#include "UserInput.h"
#include <regex>
#include <string>
#include <stdlib.h>
#include <sstream>

using namespace EasingCurves;
using namespace std;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
UserInput::InputType UserInput::GetInputType(const std::string& fileLine)
{
	std::regex curveLineMatcher;
	std::regex circleLineMatcher;
	std::string floatPat = "[+-]?([0-9]*[.])?[0-9]+";

	 std::string curveLinePattern = 
		 "((" + curve_name_linear + 
		 ")|(" + curve_name_inQuad+ 
		 ")|(" + curve_name_outQuad + 
		 ")|(" + curve_name_inOutQuad + 
		 "))," + parameter_name_xt0 + "=" + floatPat + 
		 "," + parameter_name_xtMax + "=" + floatPat +
		 "," + parameter_name_duration + "=" + floatPat;

	 std::string circlePattern =
		       parameter_name_radius + "=" + floatPat +
		 "," + parameter_name_theta_t0 + "=" + floatPat +
		 "," + parameter_name_theta_tMax + "=" + floatPat +
		 "," + parameter_name_duration + "=" + floatPat;

	// this is not used. Only here so i can re-use GetInputValue to check that the input was a float.
	// i've done this as a bit of a trade-off to the code being more readable. If I were to do the check separately, the same code would be run.
	// an improvement could be to have a helper class with methods for a check if a string is a float & getting a float for a string
	// however, since it's only used twice i've left it out for now.
	float inputValue;
	curveLineMatcher.assign(curveLinePattern);
	circleLineMatcher.assign(circlePattern);

	if (std::regex_match(fileLine, curveLineMatcher))
		return InputType::CurveFunction;
	else if (std::regex_match(fileLine, circleLineMatcher))
		return InputType::Circle;
	else if (GetInputValue(fileLine, &inputValue))
		return InputType::TimeValue;
	else
		return InputType::Invalid;
}

vector<string> SplitString(const std::string& inputLine, const std::string& delimiter)
{
	vector<string> stringElements;

	// split fileLine into an array
	size_t last = 0; size_t next = 0;
	while ((next = inputLine.find(delimiter, last)) != string::npos)
	{
		stringElements.push_back(inputLine.substr(last, next - last));
		last = next + 1;
	}
	stringElements.push_back(inputLine.substr(last));

	return stringElements;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void UserInput::GetParameters(const std::string& inputLine, std::string* curveType, float* x_t0, float* x_tMax, float* duration)
{
	vector<string> inputParameters = SplitString(inputLine, ",");

	// first line is always curve type
	*curveType = inputParameters[0];

	// read each line & assign the rest of the variables
	for (auto& inputLine : inputParameters)
	{
		string paramterNames[] = { parameter_name_xt0, parameter_name_xtMax, parameter_name_duration };

		for (auto& parameterName : paramterNames)
		{
			if (inputLine.find(parameter_name_xt0) != string::npos)
				*x_t0 = GetUserInputValue(inputLine, parameter_name_xt0);
			if (inputLine.find(parameter_name_xtMax) != string::npos)
				*x_tMax = GetUserInputValue(inputLine, parameter_name_xtMax);
			if (inputLine.find(parameter_name_duration) != string::npos)
				*duration = GetUserInputValue(inputLine, parameter_name_duration);
		}
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void UserInput::GetCircleParameters(const std::string& inputLine, float* radius, float* theta_t0, float* theta_tMax, float* duration)
{
	vector<string> inputParameters = SplitString(inputLine, ",");

	// read each line & assign the rest of the variables
	for (auto& inputLine : inputParameters)
	{
		string paramterNames[] = { parameter_name_radius, parameter_name_theta_t0, parameter_name_theta_tMax, parameter_name_duration };

		for (auto& parameterName : paramterNames)
		{
			if (inputLine.find(parameter_name_radius) != string::npos)
				*radius = GetUserInputValue(inputLine, parameter_name_radius);
			if (inputLine.find(parameter_name_theta_t0) != string::npos)
				*theta_tMax = GetUserInputValue(inputLine, parameter_name_theta_t0);
			if (inputLine.find(parameter_name_theta_tMax) != string::npos)
				*theta_tMax = GetUserInputValue(inputLine, parameter_name_theta_tMax);
			if (inputLine.find(parameter_name_duration) != string::npos)
				*duration = GetUserInputValue(inputLine, parameter_name_duration);
		}
	}
}

// todo: could have a xyCoordinates class instead of this pair for more readability
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::function<float(float)> UserInput::GetCurveFunction(const std::string& fileLine)
{
	float x_t0, x_tMax, duration;
	string curveType;
	GetParameters(fileLine, &curveType, &x_t0, &x_tMax, &duration);
	std::shared_ptr<ICurveFunction> curveFunction;

	if (curveType == curve_name_linear)
		curveFunction.reset(new LinearFunction());
	else if (curveType == curve_name_inQuad)
		curveFunction.reset(new InQuadFunction());
	else if (curveType == curve_name_outQuad)
		curveFunction.reset(new OutQuadFunction());
	else if (curveType == curve_name_inOutQuad)
		curveFunction.reset(new InOutQuadFunction());

	return [x_t0, x_tMax, duration, curveFunction](float timeInSeconds) {
		return curveFunction->CurveFunction(x_t0, x_tMax, duration, timeInSeconds); };
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::function<pair<float,float>(float)> UserInput::GetCircleFunction(const std::string& fileLine)
{
	float radius, theta_t0, x_tMax, duration;
	GetCircleParameters(fileLine, &radius, &theta_t0, &x_tMax, &duration);
	return [radius, theta_t0, x_tMax, duration](float timeInSeconds) {
		CircleFunction circleFunction;
		return circleFunction.GetCurrentXY(radius, theta_t0, x_tMax, duration, timeInSeconds); };
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool UserInput::GetInputValue(const std::string& fileLine, float* inputValue)
{
	try
	{
		*inputValue = std::stof(fileLine);
		return true;
	}
	catch (...)
	{
		// todo: add to log
		return false;
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Private
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const std::string UserInput::curve_name_linear = "Linear";
const std::string UserInput::curve_name_inQuad = "InQuad";
const std::string UserInput::curve_name_outQuad = "OutQuad";
const std::string UserInput::curve_name_inOutQuad = "InOutQuad";

const std::string UserInput::parameter_name_xt0 = "x_t0";
const std::string UserInput::parameter_name_xtMax = "x_tmax";
const std::string UserInput::parameter_name_theta_t0 = "theta_t0";
const std::string UserInput::parameter_name_theta_tMax = "theta_tmax";
const std::string UserInput::parameter_name_duration = "duration";
const std::string UserInput::parameter_name_radius = "radius";

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
float UserInput::GetUserInputValue(string inputLine, std::string parameterName)
{
	// + 1 for the equals sign
	auto valuePos = parameterName.length() + 1;
	auto valueString = inputLine.substr(valuePos);
	float inputValue;
	if (!GetInputValue(valueString, &inputValue))
	{
		// todo: add to log
		throw new exception("Could not read string. Please ensure your string is the format: [curveType],x_t0=[value],x_tmax=[value],duration=[value]");
	}

	return inputValue;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~