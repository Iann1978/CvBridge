
#include <vector>
#include <opencv2/opencv.hpp>
#include "CVProcess.h"
#include "CVTexture.h"

namespace cvBridge
{
	using namespace cv; //����cv�����ռ�
	using namespace std;

	CVProcess* CVProcess::cvProcs[32];
	
}