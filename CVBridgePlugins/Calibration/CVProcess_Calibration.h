#pragma once 

#include "CVBridge/CVProcess.h"

using namespace cvBridge;

class CVProcess_Calibration : CVProcess
{
public:
	virtual void Process(Mat** inputs, Mat** outputs) override;

	float a = 0.03;

	Point3f Calculate3DPoint(Point2f pl, Point2f pr);
	float CalculateZValue(float ul, float ur);
};