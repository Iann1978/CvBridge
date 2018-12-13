#pragma once
#include <opencv2/opencv.hpp>
namespace cvBridge
{
	using namespace cv;
	class CVTexture;
	
	class CVProcess
	{
	public:
		static CVProcess* cvProcs[32];
		int			intValues[32];
		CVTexture*	cvTextures[32];

	public:
		CVProcess();

	public:
		virtual void Process(Mat** inputs, Mat** outputs) = 0;
	};
}

