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
		Point pt0 = Point(key0.pt.x + base0.x, key0.pt.y + base0.y);
		Point pt1 = Point(key1.pt.x + base1.x, key1.pt.y + base1.y);
		circle(dest, pt0, 1, color);
		circle(dest, pt1, 1, color);
		line(dest, pt0, pt1, color);
	}
}

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
	
	
	mat0.copyTo(mat16(Rect(0, 0, 512, 512)));
	mat1.copyTo(mat16(Rect(512, 0, 512, 512)));
	mat2.copyTo(mat16(Rect(0, 512, 512, 512)));
	mat3.copyTo(mat16(Rect(512, 512, 512, 512)));


	drawMatch(mat16, good_matches01, keypoints0, keypoints1, Point(0, 0), Point(512, 0));
	drawMatch(mat16, good_matches02, keypoints0, keypoints2, Point(0, 0), Point(0, 512));
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