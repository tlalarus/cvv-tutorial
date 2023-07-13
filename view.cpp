//
// Created by minkyung on 23. 7. 13.
//

#include <stdlib.h>
#include "view.hpp"

cv::Mat img_display;
std::string winname;

cv::Point pt_lt;
cv::Point pt_rb;

using namespace std;
using namespace cv;

void OnMouse(int event, int x, int y, int flags, void*)
{
	switch (event) {
		case cv::EVENT_LBUTTONDOWN:
			pt_lt = Point(x, y);
			cout << "l button down: X=" << pt_lt.x << " Y=" << pt_lt.y << endl;
			break;
		case cv::EVENT_LBUTTONUP:
			pt_rb = Point(x,y);
			cout << "l button up: X=" << pt_rb.x << " Y=" << pt_rb.y << endl;
			break;
		case cv::EVENT_MOUSEMOVE:
			if(flags && cv::EVENT_FLAG_LBUTTON){
				Mat im_tmp = img_display.clone();
				pt_rb = Point(x,y);
				cv::rectangle(im_tmp, pt_lt, pt_rb, Scalar(255,0,0));
				imshow(winname, im_tmp);
			}
			break;
		default:
			break;
	}
}
void SetROI(cv::Mat& img, std::string imname, cv::Rect& roi)
{
	assert(!img.empty());

	img_display = img.clone();
	winname = imname;

	system("clear");

	cout << "View: " << imname << endl;
	cv::namedWindow(winname, cv::WINDOW_AUTOSIZE);
	setMouseCallback(winname, OnMouse);

	imshow(winname, img_display);
	waitKey(0);

	roi = Rect(pt_lt, pt_rb);

	cout << "Resolution info: W=" << img.cols << " H=" << img.rows << endl;
	cout << "ROI info: "<< endl;
	cout << "\tX1=" << pt_lt.x << " Y1=" << pt_lt.y << " X2=" << pt_rb.x << " Y2=" << pt_rb.y << endl;
	cout << "\tW=" << roi.width << " H=" << roi.height << endl << endl;

	destroyWindow(winname);
	return;
}
