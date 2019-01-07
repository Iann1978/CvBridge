#include <opencv2/opencv.hpp>
#include "CVBridge/CVProcess.h"
#include "CVBridge/CVTexture.h"
#include "CVProcess_Calibration.h"

//#ifdef HAVE_OPENCV_XFEATURES2D

#include "opencv2/core.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include <algorithm>



extern "C"
{
	__declspec(dllexport) CVProcess* GetCVProcess()
	{
		return (CVProcess *)new CVProcess_Calibration();
	}
}

using namespace cv;
using namespace cv::xfeatures2d;
using std::vector;

void goodMatch(vector< vector<DMatch> > &match, vector<DMatch> &goodMatch, float ratio_thresh)
{
	for (size_t i = 0; i < match.size(); i++)
	{
		if (match[i][0].distance < ratio_thresh * match[i][1].distance)
		{
			goodMatch.push_back(match[i][0]);
		}
	}
}

void drawMatch(Mat& dest, vector<DMatch> &goodMatch, vector<KeyPoint> &kp0, vector<KeyPoint> &kp1, Point base0, Point base1)
{
	for (int i = 0; i < goodMatch.size(); i++)
	{
		DMatch &match = goodMatch[i];
		KeyPoint key0 = kp0[match.queryIdx];
		KeyPoint key1 = kp1[match.trainIdx];


		Scalar color(rand() % 256, rand() % 256, rand() % 256);
		Point pt0 = Point((int)(key0.pt.x + base0.x), (int)(key0.pt.y + base0.y));
		Point pt1 = Point((int)(key1.pt.x + base1.x), (int)(key1.pt.y + base1.y));
		circle(dest, pt0, 1, color);
		circle(dest, pt1, 1, color);
		line(dest, pt0, pt1, color);
	}
}

void CalculateMatchDatas(vector<DMatch> &goodMatch01, vector<DMatch> &goodMatch02, vector<DMatch> &goodMatch03, vector<MatchData>& matchDatas)
{
	for each (DMatch m in goodMatch01)
	{
		vector<DMatch>::iterator it2 = std::find_if(goodMatch02.begin(), goodMatch02.end(),
			[m](const DMatch& x) -> bool { return x.queryIdx == m.queryIdx;  });
		vector<DMatch>::iterator it3 = std::find_if(goodMatch03.begin(), goodMatch03.end(),
			[m](const DMatch& x) -> bool { return x.queryIdx == m.queryIdx;  });
		
		if (it2 != goodMatch02.end() && it3 != goodMatch03.end())
		{
			MatchData matchData;
			matchData.idx0 = m.queryIdx;
			matchData.idx1 = m.trainIdx;
			matchData.idx2 = it2->trainIdx;
			matchData.idx3 = it3->trainIdx;
			matchDatas.push_back(matchData);
		}
	}
}

void CVProcess_Calibration::FillMatchData(vector<MatchData>& matchDatas, vector<KeyPoint>& keypoint0, vector<KeyPoint>& keypoint1,
	vector<KeyPoint>& keypoint2, vector<KeyPoint>& keypoint3)
{
	for (int i=0; i<matchDatas.size(); i++)
	{
		MatchData &matchData = matchDatas[i];
		matchData.p0 = keypoint0[matchData.idx0].pt;
		matchData.p1 = keypoint0[matchData.idx1].pt;
		matchData.p2 = keypoint0[matchData.idx2].pt;
		matchData.p3 = keypoint0[matchData.idx3].pt;
		matchData.pw = Calculate3DPoint(matchData.p0, matchData.p2);
	}
}



void PrepareData(int &m, int&n, float *&M, float*&N, vector<MatchData>& matchDatas)
{
	m = matchDatas.size() * 3;
	n = 16;
	M = new float[m * n];
	N = new float[m];
	memset(M, 0, sizeof(float)*m*n);
	memset(N, 0, sizeof(float)*m);

	for (int i = 0; i < matchDatas.size(); i++)
	{
		MatchData matchData = matchDatas[i];
		Point3f pw = matchData.pw;
		Point2f pl = matchData.p2;
		Point2f pr = matchData.p3;
		//u*y' = v*x'
		M[(i * 3 + 0) * n + 0] = pl.y * pw.x;
		M[(i * 3 + 0) * n + 1] = pl.y * pw.y;
		M[(i * 3 + 0) * n + 2] = pl.y * pw.z;
		M[(i * 3 + 0) * n + 3] = pl.y;
		M[(i * 3 + 0) * n + 4] = -pl.x * pw.x;
		M[(i * 3 + 0) * n + 5] = -pl.x * pw.y;
		M[(i * 3 + 0) * n + 6] = -pl.x * pw.z;
		M[(i * 3 + 0) * n + 7] = -pl.x;
		N[i * 3 + 0] = 0;

		//u*y' = v*x'
		M[(i * 3 + 1) * n + 8] = pr.y * pw.x;
		M[(i * 3 + 1) * n + 9] = pr.y * pw.y;
		M[(i * 3 + 1) * n + 10] = pr.y * pw.z;
		M[(i * 3 + 1) * n + 11] = pr.y;
		M[(i * 3 + 1) * n + 12] = -pr.x * pw.x;
		M[(i * 3 + 1) * n + 13] = -pr.x * pw.y;
		M[(i * 3 + 1) * n + 14] = -pr.x * pw.z;
		M[(i * 3 + 1) * n + 15] = -pr.x;
		N[i * 3 + 1] = 0;


		//xl'-xr'=1
		M[(i * 3 + 2) * n + 0] = pw.x;
		M[(i * 3 + 2) * n + 1] = pw.y;
		M[(i * 3 + 2) * n + 2] = pw.z;
		M[(i * 3 + 2) * n + 3] = 1;
		M[(i * 3 + 2) * n + 8] = -pw.x;
		M[(i * 3 + 2) * n + 9] = -pw.y;
		M[(i * 3 + 2) * n + 10] = -pw.z;
		M[(i * 3 + 2) * n + 11] = -1;
		N[i * 3 + 2] = 1;
	}
}

//bool cal_line_equation(float *x, int m, int n, float *M, float *N)
//{
//	MatrixXf MM = MatrixXf::Random(m, n);
//	MatrixXf NN = MatrixXf::Random(m, 1);
//
//	for (int r = 0; r < m; r++)
//	{
//		NN(r, 0) = N[r];
//		for (int c = 0; c < n; c++)
//		{
//			MM(r, c) = M[r*n + c];
//		}
//	}
//	MatrixXf XX = (MM.transpose() * MM).inverse() * MM.transpose() * NN;
//	for (int i = 0; i < n; i++)
//	{
//		x[i] = XX(i, 0);
//	}
//
//
//
//	return true;
//}

void CVProcess_Calibration::Process(Mat** inputs, Mat** outputs)
{
	Mat& mat2 = *cvTextures[0]->mat;
	Mat& mat3 = *cvTextures[1]->mat;
	Mat& mat16 = *cvTextures[16]->mat;

	if (first)
	{	
		detector = SURF::create(minHessian);
		matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
	}

	if (reset)
	{
		mat2.copyTo(mat0);
		mat3.copyTo(mat1);

		keypoints0.clear();
		keypoints1.clear();
		knn_matches01.clear();
		good_matches01.clear();

		detector->detectAndCompute(mat0, noArray(), keypoints0, descriptors0);
		detector->detectAndCompute(mat1, noArray(), keypoints1, descriptors1);
		matcher->knnMatch(descriptors0, descriptors1, knn_matches01, 2);
		goodMatch(knn_matches01, good_matches01, ratio_thresh);
	}
	
	keypoints2.clear();
	keypoints3.clear();
	detector->detectAndCompute(mat2, noArray(), keypoints2, descriptors2);
	detector->detectAndCompute(mat3, noArray(), keypoints3, descriptors3);


	knn_matches23.clear(); 
	good_matches23.clear();
	matcher->knnMatch(descriptors2, descriptors3, knn_matches23, 2);
	goodMatch(knn_matches23, good_matches23, ratio_thresh);


	knn_matches02.clear();
	good_matches02.clear();
	matcher->knnMatch(descriptors0, descriptors2, knn_matches02, 2);
	goodMatch(knn_matches02, good_matches02, ratio_thresh);

	knn_matches03.clear();
	good_matches03.clear();
	matcher->knnMatch(descriptors0, descriptors3, knn_matches03, 2);
	goodMatch(knn_matches03, good_matches03, ratio_thresh);

	matchDatas.clear();
	CalculateMatchDatas(good_matches01, good_matches02, good_matches03, matchDatas);
	floatValues[0] = (float)matchDatas.size();
	
	
	mat0.copyTo(mat16(Rect(0, 0, 512, 512)));
	mat1.copyTo(mat16(Rect(512, 0, 512, 512)));
	mat2.copyTo(mat16(Rect(0, 512, 512, 512)));
	mat3.copyTo(mat16(Rect(512, 512, 512, 512)));


	drawMatch(mat16, good_matches01, keypoints0, keypoints1, Point(0, 0), Point(512, 0));
	drawMatch(mat16, good_matches02, keypoints0, keypoints2, Point(0, 0), Point(0, 512));
	drawMatch(mat16, good_matches03, keypoints0, keypoints3, Point(0, 0), Point(512, 512));


	// calculate camera's positioin
	FillMatchData(matchDatas, keypoints0, keypoints1, keypoints2, keypoints3);
	int m, n;
	float *M = nullptr, *N = nullptr;
	PrepareData(m, n, M, N, matchDatas);
	delete[] M;
	delete[] N;



/*
	for (int i = 0; i < good_matches01.size(); i++)
	{
		DMatch &match = good_matches01[i];
		KeyPoint key0 = keypoints0[match.queryIdx];
		KeyPoint key1 = keypoints1[match.trainIdx];

		
		Scalar color(rand() % 256, rand() % 256, rand() % 256);
		Point pt0 = key0.pt;
		Point pt1 = Point(key1.pt.x + 512, key1.pt.y);
		circle(mat16, pt0, 1, color);
		circle(mat16, pt1, 1, color);
		line(mat16, pt0, pt1, color);
	}*/
	//circle(mat16, Point(100, 100), 5, Scalar(1, 0, 0));
	/*
	Mat img_matches01;
	drawMatches(mat0, keypoints0, mat1, keypoints1, good_matches01, img_matches01, Scalar::all(-1),
		Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	img_matches01.copyTo(mat16(Rect(0, 0, 1024, 512)));

	Mat img_matches23;
	drawMatches(mat2, keypoints2, mat3, keypoints3, good_matches23, img_matches23, Scalar::all(-1),
		Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	img_matches23.copyTo(mat16(Rect(0, 512, 1024, 512)));

*/
	first = false;
	reset = false;
		

	


	//if (first)
	//{

	//}

	//if (reset)
	//{
	//	keypoints0.clear();
	//	keypoints1.clear();
	//	knn_matches01.clear();
	//	good_matches01.clear();

	//	detector->detectAndCompute(img0, noArray(), keypoints0, descriptors0);
	//	detector->detectAndCompute(img1, noArray(), keypoints1, descriptors1);
	//}


	////keypoints_object.clear();
	////keypoints_scene.clear();
	////knn_matches.clear();
	////good_matches.clear();
	//



	////-- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
	//detector->detectAndCompute(img0, noArray(), keypoints_object, descriptors_object);
	//detector->detectAndCompute(img1, noArray(), keypoints_scene, descriptors_scene);

	////-- Step 2: Matching descriptor vectors with a FLANN based matcher
	//// Since SURF is a floating-point descriptor NORM_L2 is used
	//matcher->knnMatch(descriptors_object, descriptors_scene, knn_matches, 2);


	////-- Filter matches using the Lowe's ratio test
	//for (size_t i = 0; i < knn_matches.size(); i++)
	//{
	//	if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
	//	{
	//		good_matches.push_back(knn_matches[i][0]);
	//	}
	//}



	////-- Localize the object
	//std::vector<Point2f> obj;
	//std::vector<Point2f> scene;
	//std::vector<Point3f> world;

	//for (size_t i = 0; i < good_matches.size(); i++)
	//{
	//	//-- Get the keypoints from the good matches
	//	Point2f pl = keypoints_object[good_matches[i].queryIdx].pt;
	//	Point2f pr = keypoints_scene[good_matches[i].trainIdx].pt;
	//	Point3f pw = Calculate3DPoint(pl, pr);
	//	obj.push_back(pl);
	//	scene.push_back(pr);
	//	world.push_back(pw);
	//}

	////-- Draw matches
	//Mat img_matches;
	//drawMatches(img0, keypoints_object, img1, keypoints_scene, good_matches, img_matches, Scalar::all(-1),
	//	Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	//Mat H = findHomography(obj, scene, RANSAC);

	////-- Get the corners from the image_1 ( the object to be "detected" )
	//std::vector<Point2f> obj_corners(4);
	//obj_corners[0] = Point2f(0, 0);
	//obj_corners[1] = Point2f((float)img0.cols, 0);
	//obj_corners[2] = Point2f((float)img0.cols, (float)img0.rows);
	//obj_corners[3] = Point2f(0, (float)img0.rows);
	//std::vector<Point2f> scene_corners(4);

	//perspectiveTransform(obj_corners, scene_corners, H);

	////-- Draw lines between the corners (the mapped object in the scene - image_2 )
	//line(img_matches, scene_corners[0] + Point2f((float)img0.cols, 0),
	//	scene_corners[1] + Point2f((float)img0.cols, 0), Scalar(0, 255, 0), 4);
	//line(img_matches, scene_corners[1] + Point2f((float)img0.cols, 0),
	//	scene_corners[2] + Point2f((float)img0.cols, 0), Scalar(0, 255, 0), 4);
	//line(img_matches, scene_corners[2] + Point2f((float)img0.cols, 0),
	//	scene_corners[3] + Point2f((float)img0.cols, 0), Scalar(0, 255, 0), 4);
	//line(img_matches, scene_corners[3] + Point2f((float)img0.cols, 0),
	//	scene_corners[0] + Point2f((float)img0.cols, 0), Scalar(0, 255, 0), 4);

	////-- Show detected matches
	////imshow("Good Matches & Object detection", img_matches);
	//img_matches.copyTo(mat16);

	//if (obj.size() > 0 && scene.size() > 0)
	//{
	//	Point3f p = Calculate3DPoint(obj[0], scene[0]);
	//	floatValues[0] = p.x;
	//	floatValues[1] = p.y;
	//	floatValues[2] = p.z;

	//	floatValues[3] = obj[0].x;
	//	floatValues[4] = obj[0].y;

	//	floatValues[5] = scene[0].x;
	//	floatValues[6] = scene[0].y;

	//}
	
	//mat0.copyTo(mat16(Rect(0, 0, 512, 512)));
	//mat1.copyTo(mat16(Rect(512, 0, 512, 512)));

//	first = false;
}


Point3f CVProcess_Calibration::Calculate3DPoint(Point2f pl, Point2f pr)
{
	float xxl = (pl.x-256) / 256;
	float xxr = (pr.x-256) / 256;
	float yyr = (pr.y-256) / 256;
	float z = 2 * a / (xxl - xxr);
	float xr = xxr * z;
	float x = xr + a;
	float yr = yyr * z;
	float y = yr;
	return Point3f(x, y, z);
}