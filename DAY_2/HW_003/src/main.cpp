#include <opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/core/base.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/core/types.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <iostream>

int main() {

    // 이미지 할당하기
    cv::Mat image_background = cv::imread("../resources/image_background.png");
    cv::Mat image_logo = cv::imread("../resources/image_logo.png");

    // 로고 누끼 따기(배경 흰색 제거)
    cv::Mat image_logo_gray, image_logo_mask;
    cv::cvtColor(image_logo, image_logo_gray, cv::COLOR_BGR2GRAY);
    /* threshold(): 단일 임계값을 기준으로 이진화함
    * inRange(): 특정 범위를 기준으로 값을 필터링함
    * 배운 내용인 inRange()를 사용해서 빨강, 초록, 파랑, 검은색을 추출해서 설계해도 되겠지만, 
    * threshold()를 사용해서 한 번 구현해 보고 싶음.
    * 어쩌면 threshold()를 사용하는 것이 더 효율적인 로직이지 않을까 싶음.
    * threshold() 메서드는 밝기 수준을 기준으로 픽셀 값을 변경함 -> 그레이스케일 이미지에서 흰색 배경을 제거하는 데 적합함.
    * 현재 내가 구현하고 싶은 로직에서는 그레이 스케일 처리한 이미지에서 흰색 배경을 제거 하고 싶기에 threshold() 메서드 처리가 더 적합하다고 생각함.
    */ 
    /*  threshold()의 인자 구조
    * cv::threshold(src, dst, thresh, maxval, type);
    * src: 입력 이미지
    * dst: 출력 이미지
    * thresh: 임계값 (이 값보다 높은 픽셀은 maxval로 설정됨)
    * maxval: 임계값을 넘는 픽셀에 설정할 값
    * type: 임계값 처리 방식 (THRESH_BINARY_INV는 흰색을 제거하는 데 유용)
    */ 
    cv::threshold(image_logo_gray, image_logo_mask, 240, 255, cv::THRESH_BINARY_INV);

    // 흰색이 제거된 로고 이미지 생성
    cv::Mat image_logo_no_bg;
    image_logo.copyTo(image_logo_no_bg, image_logo_mask);

    // 로고 불투명도 조절 (50%)
    cv::Mat image_logo_transparent;
    cv::addWeighted(image_logo_no_bg, 0.5, cv::Mat::zeros(image_logo_no_bg.size(), image_logo_no_bg.type()), 0.5, 0, image_logo_transparent);

    // 로고 위치 설정
    int x = 190;
    int y = 50;

    cv::Rect roi(x, y, image_logo.cols, image_logo.rows);
    cv::Mat roi_background = image_background(roi);

    // 로고와 배경을 합성
    cv::add(roi_background, image_logo_transparent, roi_background);

    // 결과 출력
    cv::imshow("Result", image_background);
    cv::waitKey(0);

    return 0;
}