#pragma once


namespace EasingCurves
{
	class ICurveFunction
	{
	public:
		virtual float CurveFunction(float x_t0, float x_tMax, float duration) = 0;
	};

	class LinearFunction : ICurveFunction
	{
	public:
		// todo:
		// do i need to explicitly define these functions?
		float CurveFunction(float x_t0, float x_tMax, float duration);
	};

	class InQuadFunction : ICurveFunction
	{
	public:
		// todo:
		// do i need to explicitly define these functions?
		float CurveFunction(float x_t0, float x_tMax, float duration);
	};

	class OutQuadFunction : ICurveFunction
	{
	public:
		// todo:
		// do i need to explicitly define these functions?
		float CurveFunction(float x_t0, float x_tMax, float duration);
	};

	class InOutQuadFunction : ICurveFunction
	{
	public:
		// todo:
		// do i need to explicitly define these functions?
		float CurveFunction(float x_t0, float x_tMax, float duration);
	};
}