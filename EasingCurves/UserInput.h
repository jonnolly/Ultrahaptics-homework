#pragma once

#include <string>
#include <functional>
#include "CurveFunctions.h"
#include <memory>

namespace EasingCurves
{
	class CurveInput
	{
	public:
		CurveInput(std::shared_ptr<ICurveFunction> CurveFunction, float x_t0, float x_tMax, float duration)
			: CurveFunction(CurveFunction),
			x_t0(x_t0),
			x_tMax(x_tMax),
			duration(duration)
		{
		}

		std::shared_ptr<ICurveFunction> CurveFunction;
		float x_t0, x_tMax, duration;
	};

	// remember:
	//	*	Readable
	//	*	Extensible

	// todo:
	//	If necessary, change to WinAPI
	class UserInput
	{
	public:

		enum InputType { TimeValue, CurveFunction, Invalid };
		static InputType GetInputType(const std::string& fileLine);
		static CurveInput GetCurveFunction(const std::string& fileLine);
		static float GetInputValue(const std::string& fileLine);
	};

	// jobs:
	//	*	Read input & convert into usable value/function
	//	*	Take 
}