#pragma once 

#include "CVBridge/CVProcess.h"
#include "opencv2/core.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"

using namespace cvBridge;
using namespace cv;
using namespace cv::xfeatures2d;
using std::vector;

struct MatchData
{
	int idx0;
	int idx1;
	int idx2;
	int idx3;
};

class CVProcess_Calibration : CVProcess
{
public:
	virtual void Process(Mat** inputs, Mat** outputs) override;

	float a = 0.03f;
	bool first = true;
	bool reset = true;
	int minHessian = 400;
	Ptr<SURF> detector;
	Ptr<DescriptorMatcher> matcher;
	const float ratio_thresh = 0.75f;
	

	Mat mat0, mat1;
	vector<KeyPoint> keypoints0, keypoints1, keypoints2, keypoints3;
	Mat descriptors0, descriptors1, descriptors2, descriptors3;
	vector< vector<DMatch> > knn_matches01, knn_matches02, knn_matches03, knn_matches23;
	vector<DMatch> good_matches01, good_matches02, good_matches03, good_matches23;

	vector<MatchData> matchDatas;

	Point3f Calculate3DPoint(Point2f pl, Point2f pr);
	float CalculateZValue(float ul, float ur);
	
};