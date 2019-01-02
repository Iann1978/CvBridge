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
void CVProcess_Calibration::Process(Mat** inputs, Mat** outputs)
{
	Mat& img_object = *cvTextures[0]->mat;
	Mat& img_scene = *cvTextures[1]->mat;
	Mat& mat16 = *cvTextures[16]->mat;
	//-- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
	int minHessian = 400;
	Ptr<SURF> detector = SURF::create(minHessian);
	std::vector<KeyPoint> keypoints_object, keypoints_scene;
	Mat descriptors_object, descriptors_scene;
	detector->detectAndCompute(img_object, noArray(), keypoints_object, descriptors_object);
	detector->detectAndCompute(img_scene, noArray(), keypoints_scene, descriptors_scene);

	//-- Step 2: Matching descriptor vectors with a FLANN based matcher
	// Since SURF is a floating-point descriptor NORM_L2 is used
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
	std::vector< std::vector<DMatch> > knn_matches;
	matcher->knnMatch(descriptors_object, descriptors_scene, knn_matches, 2);

	//-- Filter matches using the Lowe's ratio test
	const float ratio_thresh = 0.75f;
	std::vector<DMatch> good_matches;
	for (size_t i = 0; i < knn_matches.size(); i++)
	{
		if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
		{
			if (keypoints_object[knn_matches[i][0].queryIdx].pt.x > 350)
			{
				good_matches.push_back(knn_matches[i][0]);
				break;
			}
		}
	}

	//-- Draw matches
	Mat img_matches;
	drawMatches(img_object, keypoints_object, img_scene, keypoints_scene, good_matches, img_matches, Scalar::all(-1),
		Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	//-- Localize the object
	std::vector<Point2f> obj;
	std::vector<Point2f> scene;

	for (size_t i = 0; i < good_matches.size(); i++)
	{
		//-- Get the keypoints from the good matches
		obj.push_back(keypoints_object[good_matches[i].queryIdx].pt);
		scene.push_back(keypoints_scene[good_matches[i].trainIdx].pt);
		break;
	}

	//Mat H = findHomography(obj, scene, RANSAC);

	////-- Get the corners from the image_1 ( the object to be "detected" )
	//std::vector<Point2f> obj_corners(4);
	//obj_corners[0] = Point2f(0, 0);
	//obj_corners[1] = Point2f((float)img_object.cols, 0);
	//obj_corners[2] = Point2f((float)img_object.cols, (float)img_object.rows);
	//obj_corners[3] = Point2f(0, (float)img_object.rows);
	//std::vector<Point2f> scene_corners(4);

	//perspectiveTransform(obj_corners, scene_corners, H);

	////-- Draw lines between the corners (the mapped object in the scene - image_2 )
	//line(img_matches, scene_corners[0] + Point2f((float)img_object.cols, 0),
	//	scene_corners[1] + Point2f((float)img_object.cols, 0), Scalar(0, 255, 0), 4);
	//line(img_matches, scene_corners[1] + Point2f((float)img_object.cols, 0),
	//	scene_corners[2] + Point2f((float)img_object.cols, 0), Scalar(0, 255, 0), 4);
	//line(img_matches, scene_corners[2] + Point2f((float)img_object.cols, 0),
	//	scene_corners[3] + Point2f((float)img_object.cols, 0), Scalar(0, 255, 0), 4);
	//line(img_matches, scene_corners[3] + Point2f((float)img_object.cols, 0),
	//	scene_corners[0] + Point2f((float)img_object.cols, 0), Scalar(0, 255, 0), 4);

	//-- Show detected matches
	//imshow("Good Matches & Object detection", img_matches);
	img_matches.copyTo(mat16);

	if (obj.size() > 0 && scene.size() > 0)
	{
		Point3f p = Calculate3DPoint(obj[0], scene[0]);
		floatValues[0] = p.x;
		floatValues[1] = p.y;
		floatValues[2] = p.z;

		floatValues[3] = obj[0].x;
		floatValues[4] = obj[0].y;

		floatValues[5] = scene[0].x;
		floatValues[6] = scene[0].y;

	}
	
	//mat0.copyTo(mat16(Rect(0, 0, 512, 512)));
	//mat1.copyTo(mat16(Rect(512, 0, 512, 512)));
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