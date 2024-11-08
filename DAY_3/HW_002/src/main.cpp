#include <opencv2/opencv.hpp>
#include <opencv4/opencv2/core/base.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/core/types.hpp>
#include <opencv4/opencv2/opencv.hpp>

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

    // 이미지 출력
    cv::imshow("Image", image_original);

    cv::waitKey(0);

    return 0;
}