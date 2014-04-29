// OpenCVConsole.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>
#include <time.h>

void TestCapture()
{
	cv::VideoCapture capture;
	capture.open(0);
	assert(capture.isOpened());
	cv::Mat frames[100];

	int count = 0;
	for (int i=0; i<100; i++)
		capture >> frames[i];
	int64 start = cvGetTickCount();
	int64 end = start + 1e6 * cvGetTickFrequency();
	while (start < end) {
		count ++;
		capture >> frames[count%100];
		start = cvGetTickCount();
	}

	std::cout << "Total frames in 1 seconds:" << count << std::endl;

	for (int i=0; i<count; i++) {
		char filename[100];
		sprintf_s(filename, "img%d.jpg", i);
		cv::imwrite(filename, frames[i]);
	}
	capture.release();
}

int _tmain(int argc, _TCHAR* argv[])
{
	TestCapture();
	return 0;
	cv::Mat src_base, hsv_base;
	cv::Mat dest1_base, hsv_dest1;
	cv::Mat dest2_base, hsv_dest2;

	src_base = cv::imread("E:\\visualstudio_workspace\\OpenCVTest\\imgs\\2c.jpg",1);
	dest1_base = cv::imread("E:\\visualstudio_workspace\\OpenCVTest\\imgs\\3c.jpg", 1);
	dest2_base = cv::imread("E:\\visualstudio_workspace\\OpenCVTest\\imgs\\1c.jpg", 1);
	

	cv::cvtColor(src_base, hsv_base, CV_BGR2HSV);
	cv::cvtColor(dest1_base, hsv_dest1, CV_BGR2HSV);
	cv::cvtColor(dest2_base, hsv_dest2, CV_BGR2HSV);

	int h_bins = 50; int s_bins=50;
	int histSize[] = {h_bins, s_bins};

	float h_ranges[] = {0, 100};
	float s_ranges[] = {0, 180};

	const float* ranges[] = {h_ranges, s_ranges};
	int channels[] = {0, 1};

	cv::MatND hist_base, hist_dest1, hist_dest2;

	cv::calcHist(&hsv_base, 1, channels, cv::Mat(), hist_base, 2, histSize, ranges, true, false);
	normalize(hist_base, hist_base, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
	cv::calcHist(&hsv_dest1, 1, channels, cv::Mat(), hist_dest1, 2, histSize, ranges, true, false);
	normalize(hist_dest1, hist_dest1, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
	cv::calcHist(&hsv_dest2, 1, channels, cv::Mat(), hist_dest2, 2, histSize, ranges, true, false);
	normalize(hist_dest2, hist_dest2, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

	for (int i=0; i<4; i++) {
		int compare_method = i;
		double base_self = cv::compareHist(hist_base, hist_base, compare_method);
		double base_dest1 = cv::compareHist(hist_base, hist_dest1, compare_method);
		double base_dest2 = cv::compareHist(hist_base, hist_dest2, compare_method);
		std::cout << "Compare Method:" << compare_method << " Base Self:" << base_self << " Base Dest1:" << base_dest1 << " Base Dest2:" << base_dest2 << std::endl;
	}


	return 0;
}

