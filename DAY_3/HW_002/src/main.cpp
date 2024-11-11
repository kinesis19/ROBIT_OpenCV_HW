#include <opencv2/opencv.hpp>
#include <opencv4/opencv2/core/base.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/core/types.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <cmath>
#include <iostream>

/* memo: 로직 먼저 생각해 보자
* 1. 이미지 가져와서 블러 처리 & 그레이 스케일(항상 기본이 되는 작업)
* 2. 그레이 스케일 처리된 이미지에서 엣지 검출하기
* 3. 허프 변환을 통해 선 따기
* 4. 딴 선에 대한 기울기 구하기(C++, OpenCV에서의 기울기는 우리가 아는 수학에서의 기울기와의 기준이 다르다고 하심)
* 기존 수학: x축 기준 기울기, C++ & OpenCV: y축 기준 기울기
*/

int main() {
    // 이미지 타겟팅
    cv::Mat image_original = cv::imread("../resources/image_sample.jpg");

    // 가우시안 블러 처리
    cv::Mat image_gaussianblur;
    cv::GaussianBlur(image_original, image_gaussianblur, cv::Size(5, 5), 2);

    // 그레이 스케일로 변환
    cv::Mat image_gray;
    cv::cvtColor(image_gaussianblur, image_gray, cv::COLOR_BGR2GRAY);

    // Canny 엣지 검출
    cv::Mat image_canny;
    cv::Canny(image_gray, image_canny, 150, 255);

    // HoughLinesP()로 선 선따기
    std::vector<cv::Vec4i> linesP;
    cv::HoughLinesP(image_canny, linesP, 1, CV_PI / 180, 50, 0, 30);

    // 각도 저장하는 배열(0도부터 ~ 180도까지 -> index 181 필요)
    int ary_angle[181] = {0, };

    // 모든 선에 대해 각도 계산 및 색상 변경
    for (int i = 0; i < linesP.size(); i++) {
        // 각 요소를 cv::Vec4i 타입으로 line에 할당함
        // HoughLinesP 처리한 linesP의 구조: (x1, y1, x2, y2) 좌표
        cv::Vec4i line = linesP[i];  

        // 기울기 계산
        double deltaY = line[3] - line[1];
        double deltaX = line[2] - line[0];

        // 각도 계산 (기울기 기반)
        int angle_deg;
        if (deltaX != 0) {
            double slope = deltaY / deltaX;
            /* atan() 메서드는 탄젠트 값을 받아서 각도를 반환하는 메서드임
            * -> 인자로 받은 값을 라디안 단위로 반환함
            * 탄젠트 값인 slople를 각도 단위인 라디안으로 변환하기 위해 atan() 메서드를 사용하고, 
            * 이 값을 "도" 단위로 바꾸기 위해 180을 곱하고 CV_PI(3.14~~~) 값으로 나누는 공식을 적용함
            */ 
            angle_deg = static_cast<int>(std::round(std::atan(slope) * 180 / CV_PI));
        } else {
            // deltaX가 0인 경우 수직선이므로 90도 처리
            angle_deg = 90;
        }

        // 각도 제한: 0도부터 ~ 180까지
        if (angle_deg < 0) angle_deg += 180;
        else if (angle_deg == 180) angle_deg = 0;

        // 각도 배열에 카운트 증가
        ary_angle[angle_deg]++;

        // 디버깅: 선 그리려서 띄우기
        cv::line(image_original, cv::Point(line[0], line[1]), cv::Point(line[2], line[3]), cv::Scalar(255, 0, 0), 2);

        // 각 선에 대한 각도 출력
        std::cout << i << "번째 선의 각도: " << angle_deg << "도" << std::endl;

        // 디버깅: 검출된 선 중 0번째 선에 한하여 해당 선의 각도에 대하여 텍스트를 추가해 봄
        // if (i == 0) {

        //     // 선의 중간 지점 구하는 공식
        //     int mid_x = (line[0] + line[2]) / 2;
        //     int mid_y = (line[1] + line[3]) / 2;

        //     std::string text = + "[" + std::to_string(i) + "]";

        //     // 텍스트 추가해서 이미지에 띄우기
        //     cv::putText(image_original, text, cv::Point(mid_x, mid_y), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(100, 0, 0), 1);
        // }
    }

    std::cout << "\n검출된 총 선의 개수: " << linesP.size() << std::endl;

    // 결과 이미지 출력
    cv::imshow("Original Image with Line", image_original);
    cv::imshow("Canny Image", image_canny);

    cv::waitKey(0);

    return 0;
}