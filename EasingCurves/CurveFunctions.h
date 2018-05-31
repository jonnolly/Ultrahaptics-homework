#pragma once


namespace EasingCurves
{
	class ICurveFunction
	{
	public:
		virtual float CurveFunction(float x_t0, float x_tMax, float duration, float time) = 0;
	};

	class LinearFunction : ICurveFunction
	{
	public:
		float CurveFunction(float x_t0, float x_tMax, float duration, float time)
		{
			return x_t0 + ((time * (x_tMax - x_t0)) / duration);
		}
	};

	class InQuadFunction : ICurveFunction
	{
	public:
		float CurveFunction(float x_t0, float x_tMax, float duration, float time)
		{
			return 0;
		}
	};

	class OutQuadFunction : ICurveFunction
	{
	public:
		float CurveFunction(float x_t0, float x_tMax, float duration, float time)
		{
			return 0;
		}
	};

	class InOutQuadFunction : ICurveFunction
	{
	public:
		float CurveFunction(float x_t0, float x_tMax, float duration, float time)
		{
			return 0;
		}
	};
}