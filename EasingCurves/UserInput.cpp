#include "stdafx.h"
#include "UserInput.h"
#include <regex>
#include <string>

using namespace EasingCurves;

UserInput::InputType UserInput::GetInputType(const std::string& fileLine)
{
	// todo: Make it so Linear,InQuad etc. inside regex pattern get their values dynamically
	// so that if another pattern is added, it is automatically updated

	std::regex timeValueMatcher;
	std::regex curveLineMatcher;
	std::string curveLinePattern = "((Linear)|(InQuad)|(OutQuad)|(InOutQuad)),x_t0=\\d+,x_tmax=\\d+,duration=\\d+";
	std::string timeValuePattern = "\\d+.\\d+";

	timeValueMatcher.assign(timeValuePattern);
	curveLineMatcher.assign(curveLinePattern);

	if (std::regex_match(fileLine, curveLineMatcher))
		return InputType::CurveFunction;
	else if (std::regex_match(fileLine, timeValueMatcher))
		return InputType::TimeValue;
	else
		return InputType::Invalid;
}

CurveInput UserInput::GetCurveFunction(const std::string& fileLine)
{
	return CurveInput(nullptr, 0, 0, 0);
}

float UserInput::GetInputValue(const std::string& fileLine)
{
	return 0;
}