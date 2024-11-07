#include <opencv2/opencv.hpp>
#include <opencv4/opencv2/core/base.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/core/types.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <iostream>

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

    // 레이블링 처리
    cv::Mat label_redBall, label_greenBall, label_blueBall; // 라벨 이미지
    cv::Mat stats_red, stats_green, stats_blue;       // 통계 정보
    cv::Mat centroids_red, centroids_green, centroids_blue;   // 중심 좌표

    int cnt_image_red = cv::connectedComponentsWithStats(image_red, label_redBall, stats_red, centroids_red, 8, CV_32S);
    int cnt_image_green = cv::connectedComponentsWithStats(image_green, label_greenBall, stats_green, centroids_green, 8, CV_32S);
    int cnt_image_blue = cv::connectedComponentsWithStats(image_blue, label_blueBall, stats_blue, centroids_blue, 8, CV_32S);

    /* 바운딩 처리
    * 바운딩 처리를 위한 도형의 값은 바뀌면 안 되기에 const 처리함.
    * 근데, 내가 하는 과제에서는 const 처리를 굳이 할 필요가 있을까? 싶음
    * 0 번째 행: 전체 이미지, 1번째 행: 타겟 객체
    */
    const int line_red_width = stats_red.at<int>(1, 2); 
    const int line_red_height = stats_red.at<int>(1, 3); 
    const int line_green_width = stats_green.at<int>(1, 2); 
    const int line_green_height = stats_green.at<int>(1, 3); 
    const int line_blue_width = stats_blue.at<int>(1, 2); 
    const int line_blue_height = stats_blue.at<int>(1, 3); 

    cv::Point red_start(stats_red.at<int>(1, 0), stats_red.at<int>(1, 1)); // 시작 좌표 (x, y)
    cv::Point red_end(stats_red.at<int>(1, 0) + line_red_width, stats_red.at<int>(1, 1) + line_red_height); // 종료 좌표 (x + width, y + height)

    cv::Point green_start(stats_green.at<int>(1, 0), stats_green.at<int>(1, 1));
    cv::Point green_end(stats_green.at<int>(1, 0) + line_green_width, stats_green.at<int>(1, 1) + line_green_height);

    cv::Point blue_start(stats_blue.at<int>(1, 0), stats_blue.at<int>(1, 1));
    cv::Point blue_end(stats_blue.at<int>(1, 0) + line_blue_width, stats_blue.at<int>(1, 1) + line_blue_height);

    // 객체에 바운딩 박스 그리기
    cv::rectangle(image_original, red_start, red_end, cv::Scalar(0, 0, 255), 2); // 빨간색으로 바운딩 박스 표시
    cv::rectangle(image_original, green_start, green_end, cv::Scalar(0, 255, 0), 2);
    cv::rectangle(image_original, blue_start, blue_end, cv::Scalar(255, 0, 0), 2);

    // 마스크 이미지 출력
    cv::imshow("Original Image", image_original); // 원본 이미지
    
    // 디버깅
    // std::cout << "labels: \n" << label_redBall  << std::endl;
    // std::cout << "number of labels: \n" << cnt_image_red  << std::endl;
    // stats의 참조는 .at<int>(행, 열) 형식임

    // std::cout << "Size Width: " << stats_red.at<int>(1, 2) << " Size Heigh: " << stats_red.at<int>(1, 3) << std::endl;


    // std::cout << "labels: \n" << label_greenBall  << std::endl;
    // std::cout << "number of labels: \n" << cnt_image_green  << std::endl;
    // std::cout << "Size Width: " << stats_green.at<int>(1, 2) << " Size Heigh: " << stats_green.at<int>(1, 3) << std::endl;

    // std::cout << "labels: \n" << label_blueBall  << std::endl;
    // std::cout << "number of labels: \n" << cnt_image_blue  << std::endl;
    // std::cout << "Size Width: " << stats_blue.at<int>(1, 2) << " Size Heigh: " << stats_blue.at<int>(1, 3) << std::endl;

    cv::waitKey(0);

    return 0;
}