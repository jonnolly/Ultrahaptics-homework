#include "stdafx.h"
#include "UserInput.h"

using namespace EasingCurves;

// todo:
// Implement class

UserInput::InputType UserInput::GetInputType(const std::string& fileLine)
{
	return InputType::currentTime;
}

CurveInput UserInput::GetCurveFunction(const std::string& fileLine)
{
	return CurveInput(nullptr, 0, 0, 0);
}

float UserInput::GetInputValue(const std::string& fileLine)
{
	return 0;
}