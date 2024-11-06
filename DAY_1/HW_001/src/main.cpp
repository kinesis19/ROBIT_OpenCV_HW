#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {

    cv::Mat image = cv::Mat::zeros(480, 640, CV_8UC3);

    cv::Mat img = cv::imread("../resources/testImg.png");
    cv::imshow("Test Image", img);
    cv::waitKey(0);

    return 0;
}