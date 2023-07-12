//
// Created by minkyung on 23. 7. 12.
//
#include <iostream>
#include <vector>
#include <sys/utsname.h>

#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc/types_c.h>

// #ifdef CVVISUAL_DEBUGMODE
#include <opencv2/cvv/debug_mode.hpp>
#include <opencv2/cvv/show_image.hpp>
#include <opencv2/cvv/filter.hpp>
#include <opencv2/cvv/dmatch.hpp>
#include <opencv2/cvv/final_show.hpp>

using namespace std;
using namespace cv;

template<class T> std::string toString(const T& p_arg)
{
	std::stringstream ss;
	ss << p_arg;
	return ss.str();
}

int main(){
	utsname u;
	if(uname(&u) != 0){
		return 1;
	}

	std::cout << "Hello from " << u.nodename << std::endl;

	int res_w = 0, res_h = 0;

	Mat prev_img_gray;
	vector<KeyPoint> prev_keypoints;
	Mat prev_descriptors;

	int max_feature_count = 500;
	Ptr<ORB> detector = ORB::create(max_feature_count);
	BFMatcher matcher(NORM_HAMMING);

	Mat img_read;
	string img_id_str = "img_read";
	cvv::showImage(img_read, CVVISUAL_LOCATION, img_id_str.c_str());

	// convert to rgb
	Mat img_rgb;
	cvtColor(img_read, img_rgb, COLOR_GRAY2BGR);
	cvv::debugFilter(img_read, img_rgb, CVVISUAL_LOCATION, "to rgb");

	// detect ORB features
	vector<KeyPoint> keypoints;
	Mat descriptors;
	detector->detectAndCompute(img_read, cv::noArray(), keypoints, descriptors);
	cout << "detected keypoints: " << keypoints.size() << endl;


	cvv::finalShow();

	return 0;

}
