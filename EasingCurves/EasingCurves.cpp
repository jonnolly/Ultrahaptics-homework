// EasingCurves.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <memory>
#include "UserInput.h"

using namespace EasingCurves;

int main()
{
	// todo: read input file (from args?)
	// std::string testInput[] = { "Linear,x_t0=100,x_tmax=200,duration=1" };
	std::string testInput[] = { "1.2." };
	std::shared_ptr<CurveInput> lastCurveInput;

	for (std::string inputLine : testInput)
	{
		auto inputType = UserInput::GetInputType(inputLine);

		if (inputType == UserInput::InputType::CurveFunction)
		{
			auto curveFuntion = UserInput::GetCurveFunction(inputLine);
			lastCurveInput = std::make_shared<CurveInput>(curveFuntion);
			// output curve function
		}
		else if (inputType == UserInput::InputType::TimeValue && lastCurveInput != nullptr)
		{
			auto inputValue = UserInput::GetInputValue(inputLine);
			auto curveValue = lastCurveInput->CurveFunction->CurveFunction(lastCurveInput->x_t0, lastCurveInput->x_tMax, lastCurveInput->duration, inputValue);
			// output value
		}
		else
		{
			// add to log which is displayed at the end of run.
		}
	}

	return 0;
}