#pragma once 

#include "CVBridge\CVProcess.h"

using namespace cvBridge;

class CVProcess_Calibration : CVProcess
{
public:
	virtual void Process(Mat** inputs, Mat** outputs) override;
};