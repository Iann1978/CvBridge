#include <opencv2/opencv.hpp>
#include "CVBridge/CVProcess.h"
#include "CVBridge/CVTexture.h"
#include "CVProcess_Calibration.h"

#ifdef HAVE_OPENCV_XFEATURES2D
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#endif

extern "C"
{
	__declspec(dllexport) CVProcess* GetCVProcess()
	{
		return (CVProcess *)new CVProcess_Calibration();
	}
}
void CVProcess_Calibration::Process(Mat** inputs, Mat** outputs)
{
	Mat& mat0 = *cvTextures[0]->mat;
	Mat& mat1 = *cvTextures[1]->mat;
	Mat& mat16 = *cvTextures[16]->mat;

	//-- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
	//int minHessian = 400;
	//Ptr<SURF> detector = SURF::create(minHessian);
	//std::vector<KeyPoint> keypoints1, keypoints2;
	//Mat descriptors1, descriptors2;
	//detector->detectAndCompute(img1, noArray(), keypoints1, descriptors1);
	//detector->detectAndCompute(img2, noArray(), keypoints2, descriptors2);

	mat0.copyTo(mat16(Rect(0, 0, 512, 512)));
	mat1.copyTo(mat16(Rect(512, 0, 512, 512)));


}