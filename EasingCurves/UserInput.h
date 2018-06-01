#pragma once

#include <string>
#include <functional>
#include "CurveFunctions.h"
#include <memory>

namespace EasingCurves
{
	class UserInput
	{
	public:

		enum InputType { TimeValue, CurveFunction, Circle, Invalid };
		static InputType GetInputType(const std::string& fileLine);
		static std::function<float(float)> GetCurveFunction(const std::string& fileLine);
		static std::function<std::pair<float, float>(float)> GetCircleFunction(const std::string& fileLine);
		static bool GetInputValue(const std::string& fileLine, float* inputValue);

	private:
		static const std::string curve_name_linear;
		static const std::string curve_name_inQuad;
		static const std::string curve_name_outQuad;
		static const std::string curve_name_inOutQuad;
		static const std::string curve_name_circle;

		static const std::string parameter_name_xt0;
		static const std::string parameter_name_xtMax;
		static const std::string parameter_name_theta_t0;
		static const std::string parameter_name_theta_tMax;
		static const std::string parameter_name_duration;
		static const std::string parameter_name_radius;

		static float GetUserInputValue(std::string inputString, std::string parameterName);
		static void GetParameters(const std::string& inputLine, std::string* curveType, float* x_t0, float* x_tMax, float* duration);
		static void GetCircleParameters(const std::string& inputLine, float* radius, float* theta_t0, float* theta_tMax, float* duration);
	};
}