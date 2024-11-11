#include <opencv2/opencv.hpp>
#include <opencv4/opencv2/core/base.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/core/types.hpp>
#include <opencv4/opencv2/opencv.hpp>

/* memo: 로직 먼저 생각해 보자
* 1. 이미지 가져와서 블러 처리 & 그레이 스케일(항상 기본이 되는 작업)
* 2. 그레이 스케일 처리된 이미지에서 엣지 검출하기
* 3. HoughCircles() 메서드로 이미지 속 동전에 대한 엣지 추출
* 4. 지름 구해서 이미지 속 돈 구분(10원, 100원, 500원)
* 5. 변수에 저장해서 얼마인지 출력
*
* 과제 리뷰:
* 이번 과제의 핵심은 HoughCircles() 메서드로 이미지속 동전의 좌표와 반지름 값을 구해서, 반지름을 가지고 동전을 분류하는 것임.
*/

int main() {
    // 이미지 타겟팅
    cv::Mat image_original = cv::imread("../resources/image_sample.png");

    // 가우시안 블러 처리
    cv::Mat image_gaussianblur;
    cv::GaussianBlur(image_original, image_gaussianblur, cv::Size(5, 5), 2);

    // 그레이 스케일로 변환
    cv::Mat image_gray;
    cv::cvtColor(image_gaussianblur, image_gray, cv::COLOR_BGR2GRAY);

    // HoughCircles로 각 동전에 대한 엣지 검출
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(image_gray, circles, cv::HOUGH_GRADIENT, 1, 30, 150, 60);


    // 동전, 돈 합계 변수
    int cntCoin10 = 0, cntCoin100 = 0, cntCoin500 = 0, money = 0;

    // 동전 라벨링하고 계산하기
    for (size_t i = 0; i < circles.size(); i++) {
        // 각 원의 중심 좌표와 반지름
        cv::Vec3f circle = circles[i];
        cv::Point center(cvRound(circle[0]), cvRound(circle[1]));
        int radius = cvRound(circle[2]);

        // 동전 중점에 점 찍기
        cv::circle(image_original, center, 3, cv::Scalar(0, 255, 0), -1);

        // 원으로 라벨링
        cv::circle(image_original, center, radius, cv::Scalar(0, 0, 255), 2);

        /* 모든 동전의 사이즈가 완벽하게 똑같을 수 없어서 범위 정해 놓고 처리해야 할 듯
        * 왜 Why? -> 평면에서 촬영 했을 때 이슈나 돈을 주고 받으면서 사이즈 변화 가능
        */ 
        
        std::string text;

        if(radius < 35) {
            text = "10Won";
            cntCoin10++;
            money += 10;
        } else if(radius < 40) {
            text = "100Won";
            cntCoin100++;
            money += 100;
        } else if(radius < 45) {
            text = "500Won";
            cntCoin500++;
            money += 500;
        }

        // 텍스트 추가 (동전의 중심 약간 위에 표시)
        cv::putText(image_original, text, cv::Point(center.x - 20, center.y - radius - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 0, 0), 1);
        // 디버깅
        std::cout << "동전 " << i + 1 << ": 중심 = (" << center.x << ", " << center.y << "), 반지름 = " << radius << std::endl;
    }


    // 결과 이미지 출력
    cv::imshow("Image", image_original);

    // 결과 출력

    std::cout << "10원짜리 갯수: " << cntCoin10 << std::endl  << "100원짜리 갯수: " << cntCoin100 << std::endl << "500원짜리 갯수: " << cntCoin500 << std::endl;
    std::cout << "계산한 돈의 값: " << money << std::endl;

    cv::waitKey(0);

    return 0;
}