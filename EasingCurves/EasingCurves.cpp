// EasingCurves.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <memory>
#include <iostream>
#include "UserInput.h"

using namespace EasingCurves;

int main()
{
	// todo: read input file (from args?)
	// std::string testInput[] = { "InQuad,x_t0=1020,x_tmax=2400,duration=3", "0.3", "0.9", "1" };
	std::string testInput[] = { "radius=5,theta_t0=1020,theta_tmax=2400,duration=3", "0.3", "0.9", "1" };

	bool curveInputIsAssigned = false;

	// possible improvement: Have a returned class that has two separate lists of returned values. one for 1D line & one for 2D circle
	// then have the "UserInput::GetCurveFunction" functions to return that type & deal with the two types separately.
	// for the mean time we have this enum.

	// could also have two separate input classes for curve & circle, inheritting from the same base class, with different implementations
	// could include input and output methods that would be different for both.

	UserInput::InputType lastFunctionInputType = UserInput::InputType::Invalid;

	// the last curve input entered is stored and used for any subsequent calculations
	std::function<float(float)> lastCurveInput;
	std::function<std::pair<float,float>(float)> lastCircleInput;

	for (std::string inputLine : testInput)
	{
		auto inputType = UserInput::GetInputType(inputLine);

		if (inputType == UserInput::InputType::CurveFunction)
		{
			lastFunctionInputType = UserInput::CurveFunction;
			lastCurveInput = UserInput::GetCurveFunction(inputLine);
			curveInputIsAssigned = true;

			// output curve function line
			std::cout << '\n' << inputLine;
		}
		else if (inputType == UserInput::InputType::Circle)
		{
			lastFunctionInputType = UserInput::Circle;
			lastCircleInput = UserInput::GetCircleFunction(inputLine);
			curveInputIsAssigned = true;

			std::cout << '\n' << inputLine;
		}
		else if (inputType == UserInput::InputType::TimeValue && curveInputIsAssigned)
		{
			float inputValue;
			std::string outputValue;
			auto success = UserInput::GetInputValue(inputLine, &inputValue);

			// handle circles & curves differently
			if (lastFunctionInputType == UserInput::InputType::Circle)
			{
				auto xyValues = lastCircleInput(inputValue);
				outputValue = "x: " + std::to_string(xyValues.first) + ", y: " + std::to_string(xyValues.second);
			}

			if (lastFunctionInputType == UserInput::InputType::CurveFunction)
				outputValue = "value: " + std::to_string(lastCurveInput(inputValue));

			// output value
			std::cout << '\n' << outputValue;
		}
		else
		{
			// add to log which is displayed at the end of run.
		}
	}

	return 0;
}