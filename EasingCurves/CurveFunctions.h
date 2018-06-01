#pragma once

#include <math.h>

// todo: use the same method with only time functions changing
namespace EasingCurves
{
	class ICurveFunction
	{
	public:
		virtual float CurveFunction(const float& x_t0, const float& x_tMax, const float& duration, const float& time)
		{
			return x_t0 + ((timeFunctionResult * (x_tMax - x_t0)) / duration);
		}

	protected:
		float timeFunctionResult;
	};

	class LinearFunction : public ICurveFunction
	{
	public:
		float CurveFunction(const float& x_t0, const float& x_tMax, const float& duration, const float& time)
		{
			timeFunctionResult = time;
			return ICurveFunction::CurveFunction(x_t0, x_tMax, duration, timeFunctionResult);
		}
	};

	class InQuadFunction : public ICurveFunction
	{
	public:
		 float CurveFunction(const float& x_t0, const float& x_tMax, const float& duration, const float& time) override
		 {
			 timeFunctionResult = pow(time, 2);
			 return  ICurveFunction::CurveFunction(x_t0, x_tMax, duration, timeFunctionResult);
		 }
	};

	class OutQuadFunction : public ICurveFunction
	{
	public:
		float CurveFunction(const float& x_t0, const float& x_tMax, const float& duration, const float& time)
		{
			timeFunctionResult = pow(time, 0.5);
			return ICurveFunction::CurveFunction(x_t0, x_tMax, duration, timeFunctionResult);
		}
	};

	class InOutQuadFunction : public ICurveFunction
	{
	public:
		float CurveFunction(const float& x_t0, const float& x_tMax, const float& duration, const float& time)
		{
			auto halfwayPoint = duration / 2;
			timeFunctionResult;

			if (time < halfwayPoint)
				timeFunctionResult = pow(time, 2);
			else
				timeFunctionResult = pow(time, 0.5);

			return ICurveFunction::CurveFunction(x_t0, x_tMax, duration, timeFunctionResult);
		}
	};

	// Circle function is similar to the other curve functions, but gives different outputs. Therefore it does not inherit from ICurveFunction
	class CircleFunction
	{
	public:
		std::pair<float, float> GetCurrentXY(const float& radius, const float& theta_t0, const float& theta_tMax, const float& duration, const float& time)
		{
			LinearFunction linearFunction;
			auto currentTheta = linearFunction.CurveFunction(theta_t0, theta_tMax, duration, time);
			auto xPosition = radius * cos(currentTheta);
			auto yPosition = radius * sin(currentTheta);
			return std::make_pair(xPosition, yPosition);
		}
	};
}