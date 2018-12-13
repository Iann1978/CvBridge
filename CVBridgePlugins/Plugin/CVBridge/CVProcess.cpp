
#include <vector>
#include <opencv2/opencv.hpp>
#include "CVProcess.h"
#include "CVTexture.h"

namespace cvBridge
{
	using namespace cv; //°üº¬cvÃüÃû¿Õ¼ä
	using namespace std;

	CVProcess* CVProcess::cvProcs[32];
	CVProcess::CVProcess()
	{
		memset(cvTextures, sizeof(CVTexture*) * 32, 0);
		memset(intValues, sizeof(int*) * 32, 0);
	}
}