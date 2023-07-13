//
// Created by minkyung on 23. 7. 12.
//
#include <iostream>
#include <vector>
#include <sys/utsname.h>

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

using namespace std;
using namespace cv;

template<class T> std::string toString(const T& p_arg)
{
	std::stringstream ss;
	ss << p_arg;
	return ss.str();
}

int main(int argc, char* argv[]){
	utsname u;
	if(uname(&u) != 0){
		return 1;
	}
	if(argc < 2){
		return 1;
	}

	std::cout << "Hello from " << u.nodename << std::endl;

	int max_feature_count = 500;
	Ptr<ORB> detector = ORB::create(max_feature_count);
	BFMatcher matcher(NORM_HAMMING);

	string src_path = "/home/images/";

	for(int i=1; i<argc; i++){
		string open_path = src_path + string(argv[i]);
		cout << "Open " << open_path << endl;

		Mat img_read = cv::imread(open_path, 0);
		cout << "image W=" << img_read.cols << " H=" << img_read.rows << endl;

		imshow("img", img_read);
		waitKey(0);

		string img_id_str = "img_read";
		cvv::showImage(img_read, CVVISUAL_LOCATION, img_id_str.c_str());

		// gaussian blur
		Mat img_blur;
		GaussianBlur(img_read, img_blur, Size(3,3), 0,0, BORDER_DEFAULT);
		cvv::debugFilter(img_read, img_blur, CVVISUAL_LOCATION, "gaussian");

		// sobel filter
		Mat grad_x, grad_y, abs_grad_x, abs_grad_y;
		Sobel(img_blur, grad_x, -1, 1, 0, 3);
		cvv::debugFilter(img_blur, grad_x, CVVISUAL_LOCATION, "sobel x");
		Sobel(img_blur, grad_y, -1, 0, 1, 3);
		cvv::debugFilter(img_blur, grad_y, CVVISUAL_LOCATION, "sobel y");

		convertScaleAbs(grad_x, abs_grad_x);
		convertScaleAbs(grad_y, abs_grad_y);

		Mat grad;
		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

		// detect ORB features
		vector<KeyPoint> keypoints;
		Mat descriptors;
		detector->detectAndCompute(img_read, cv::noArray(), keypoints, descriptors);
		cout << "detected keypoints: " << keypoints.size() << endl;

		// convert to rgb
		Mat img_rgb;
		cvtColor(img_read, img_rgb, COLOR_GRAY2BGR);
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
