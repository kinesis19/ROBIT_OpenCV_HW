#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 이미지 타겟팅
    cv::Mat image_original = cv::imread("../resources/testImg.png");

    // hsv 변환
    cv::Mat image_hsv;
    cv::cvtColor(image_original, image_hsv, cv::COLOR_BGR2HSV);

    // 노란색 마스크
    // 색상, 채도, 명도
    cv::Mat yellow_mask;
    cv::Scalar lower_yellow = cv::Scalar(20, 150, 150);
    cv::Scalar upper_yellow = cv::Scalar(30, 255, 255);
    // 바이너리 처리
    cv::inRange(image_hsv, lower_yellow, upper_yellow, yellow_mask);

    // 가우시안 블러 처리
    cv::Mat imgGaussianBlur;
    cv::GaussianBlur(yellow_mask, imgGaussianBlur, cv::Size(5, 5), 2);

    // 마스크 이미지 출력
    cv::imshow("Original Image", image_original); // 원본 이미지
    cv::imshow("Yellow Mask", yellow_mask); // 바이너리 처리만 한 이미지
    cv::imshow("imgGaussianBlur", imgGaussianBlur); // 가우시안 블러까지 처리한 이미지
    
    cv::waitKey(0);

    return 0;
}