#include <opencv2/opencv.hpp>
#include "CVBridge/CVProcess.h"
#include "CVBridge/CVTexture.h"
#include "CVProcess_Calibration.h"
extern "C"
{
	__declspec(dllexport) CVProcess* GetCVProcess()
	{
		return (CVProcess *)new CVProcess_Calibration();
	}
}
void CVProcess_Calibration::Process(Mat** inputs, Mat** outputs)
{

}