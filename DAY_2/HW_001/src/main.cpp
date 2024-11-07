#include <opencv2/opencv.hpp>
#include <opencv4/opencv2/core/base.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/core/types.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include "function.hpp"

int main() {
    // 이미지 타겟팅
    cv::Mat image_original = cv::imread("../resources/sample_image.png");

    // 가우시안 블러 처리
    cv::Mat imgGaussianBlur;
    cv::GaussianBlur(image_original, imgGaussianBlur, cv::Size(5, 5), 2);

    // hsv 변환
    cv::Mat image_hsv;
    cv::cvtColor(imgGaussianBlur, image_hsv, cv::COLOR_BGR2HSV);

    // 마스크 처리하기
    // 색상, 채도, 명도
    cv::Mat mask_red, mask_green, mask_blue;
    cv::Scalar lower_red = cv::Scalar(0, 100, 100);
    cv::Scalar upper_red = cv::Scalar(10, 255, 255);

    cv::Scalar lower_green = cv::Scalar(35, 100, 100);
    cv::Scalar upper_green = cv::Scalar(85, 255, 255);

    cv::Scalar lower_blue = cv::Scalar(100, 100, 100);
    cv::Scalar upper_blue = cv::Scalar(133, 255, 255);

    // 바이너리 처리
    cv::inRange(image_hsv, lower_red, upper_red, mask_red);
    cv::inRange(image_hsv, lower_green, upper_green, mask_green);
    cv::inRange(image_hsv, lower_blue, upper_blue, mask_blue);

    // 커널 생성
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(37, 37));

    // Open 처리
    cv::Mat image_red, image_green, image_blue;
    cv::morphologyEx(mask_red, image_red, cv::MORPH_OPEN, kernel);
    cv::morphologyEx(mask_green, image_green, cv::MORPH_OPEN, kernel);
    cv::morphologyEx(mask_blue, image_blue, cv::MORPH_OPEN, kernel);

    // Close 처리
    // 중요! Mat는 재사용   이 가능하다는 것을 알게 됨 (대박사건) 내가 몰랐던 게 맞음. 변수 같은 개념이니까.
    cv::morphologyEx(mask_red, image_red, cv::MORPH_CLOSE, kernel);
    cv::morphologyEx(mask_green, image_green, cv::MORPH_CLOSE, kernel);
    cv::morphologyEx(mask_blue, image_blue, cv::MORPH_CLOSE, kernel);

    // 여기서부터는 내가 만든 Open 메서드와 Close 메서드
    cv::Mat image_red_my_open, image_green_my_open, image_blue_my_open;
    OpenCV_Open(mask_red, image_red_my_open, cv::MORPH_OPEN, kernel, cv::Point(-1, 1), 1, cv::BORDER_CONSTANT, cv::morphologyDefaultBorderValue());
    OpenCV_Open(mask_green, image_green_my_open, cv::MORPH_OPEN, kernel, cv::Point(-1, 1), 1, cv::BORDER_CONSTANT, cv::morphologyDefaultBorderValue());
    OpenCV_Open(mask_blue, image_blue_my_open, cv::MORPH_OPEN, kernel, cv::Point(-1, 1), 1, cv::BORDER_CONSTANT, cv::morphologyDefaultBorderValue());

    cv::Mat image_red_my_close, image_green_my_close, image_blue_my_close;
    OpenCV_Close(mask_red, image_red_my_close, cv::MORPH_CLOSE, kernel, cv::Point(-1, 1), 1, cv::BORDER_CONSTANT, cv::morphologyDefaultBorderValue());
    OpenCV_Close(mask_green, image_green_my_close, cv::MORPH_CLOSE, kernel, cv::Point(-1, 1), 1, cv::BORDER_CONSTANT, cv::morphologyDefaultBorderValue());
    OpenCV_Close(mask_blue, image_blue_my_close, cv::MORPH_CLOSE, kernel, cv::Point(-1, 1), 1, cv::BORDER_CONSTANT, cv::morphologyDefaultBorderValue());

    // 마스크 이미지 출력
    cv::imshow("Original Image", image_original); // 원본 이미지
    cv::imshow("Red Image", image_red); // 처리만 한 이미지
    cv::imshow("Green Image", image_green); // 처리만 한 이미지
    cv::imshow("Blue Image", image_blue); // 처리만 한 이미지

    cv::imshow("My Open Red Image", image_red_my_open); // 내가 만든 OpenCV_Open으로 처리만 한 이미지
    cv::imshow("My Open Green Image", image_green_my_open); // 내가 만든 OpenCV_Open으로 처리만 한 이미지
    cv::imshow("My Open Blue Image", image_blue_my_open); // 내가 만든 OpenCV_Open으로 처리만 한 이미지

    cv::imshow("My Close Red Image", image_red_my_close); // 내가 만든 OpenCV_Open으로 처리만 한 이미지
    cv::imshow("My Close Green Image", image_green_my_close); // 내가 만든 OpenCV_Open으로 처리만 한 이미지
    cv::imshow("My Close Blue Image", image_blue_my_close); // 내가 만든 OpenCV_Open으로 처리만 한 이미지
    
    cv::waitKey(0);

    return 0;
}