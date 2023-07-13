//
// Created by minkyung on 23. 7. 12.
//
#include <iostream>
#include <vector>
#include <chrono>

#ifdef unix
#include <sys/utsname.h>
#endif

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc/types_c.h>

#define CVVISUAL_DEBUGMODE
#include <opencv2/cvv/debug_mode.hpp>
#include <opencv2/cvv/show_image.hpp>
#include <opencv2/cvv/filter.hpp>
#include <opencv2/cvv/dmatch.hpp>
#include <opencv2/cvv/final_show.hpp>

#include "view.hpp"

using namespace std;
using namespace cv;
using namespace std::chrono;

template<class T> std::string toString(const T& p_arg)
{
	std::stringstream ss;
	ss << p_arg;
	return ss.str();
}

int main(int argc, char* argv[]){
#ifdef unix
	utsname u;
	if(uname(&u) != 0){
		return 1;
	}
	std::cout << "Hello from " << u.nodename << std::endl;
#endif

	if(argc < 2){
		return 1;
	}

	int max_feature_count = 500;
	Ptr<ORB> detector = ORB::create(max_feature_count);
	BFMatcher matcher(NORM_HAMMING);

	string src_path = "/home/images/";

	for(int i=1; i<argc; i++){
		string imname_str = string(argv[i]);
		string open_path = src_path + imname_str;
		cout << "Open " << open_path << endl;

		Mat img_read = cv::imread(open_path, 0);
		cout << "image W=" << img_read.cols << " H=" << img_read.rows << endl;

		string img_id_str = "img_read";
		cvv::showImage(img_read, CVVISUAL_LOCATION, img_id_str.c_str());

		// convert to rgb
		Mat img_rgb;
		cvtColor(img_read, img_rgb, COLOR_GRAY2BGR);

		// Set roi
		Rect roi;
		SetROI(img_rgb, imname_str, roi);

		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		Mat img_roi = img_read(roi);

		// laplacian
		Mat img_lap, img_lap_8u;
		Laplacian(img_roi, img_lap, CV_64F);
		Laplacian(img_roi, img_lap_8u, CV_8U);
		cvv::debugFilter(img_roi, img_lap_8u, CVVISUAL_LOCATION, "laplacian");

		// measure blurry
		Scalar mean_, stdev_;
		cv::meanStdDev(img_lap, mean_, stdev_);
		high_resolution_clock::time_point t2 = high_resolution_clock::now();

		cout << "blurry : " << stdev_[0] << endl;
		duration<double> time_ = duration_cast<milliseconds>(t2 - t1) ;
		cout << "time : " << time_.count() << " ms" << endl;

		// detect ORB features
		vector<KeyPoint> keypoints;
		Mat descriptors;
		detector->detectAndCompute(img_read, cv::noArray(), keypoints, descriptors);
		cout << "detected keypoints: " << keypoints.size() << endl;

		//cvv::debugFilter(img_read, img_rgb, CVVISUAL_LOCATION, "to rgb");
		cvv::showImage(img_rgb, CVVISUAL_LOCATION, "to rgb");

		Mat img_keypoints;
		drawKeypoints(img_rgb, keypoints, img_keypoints);
		cvv::showImage(img_keypoints, CVVISUAL_LOCATION, "keypoints");

	}

	cvv::finalShow();

	cout << "done" << endl;
	return 0;

}
