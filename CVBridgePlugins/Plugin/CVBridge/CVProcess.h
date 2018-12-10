#pragma once
#include <opencv2/opencv.hpp>
namespace cvBridge
{
	using namespace cv;
	class CVTexture;
	
	class CVProcess
	{
	public:
		static int intValues[32];
		static CVTexture*	cvTextures[32];
	public:
		virtual void Process(Mat** inputs, Mat** outputs);

	};
}

