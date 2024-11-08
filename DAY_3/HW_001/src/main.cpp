#include <opencv2/opencv.hpp>
#include <opencv4/opencv2/core/base.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/core/types.hpp>
#include <opencv4/opencv2/opencv.hpp>

/* memo: 로직 먼저 생각해 보자
* 1. 이미지 가져와서 블러 처리 & 그레이 스케일(항상 기본이 되는 작업)
* 2. contour 메서드를 사용해서 외각선 검출하기(모드 총 네 개를 다 사용)
* 3. 각 모드에 따른 hierarchy 정보를 추출해서 출력
*/

int main() {
    // 이미지 타겟팅
    cv::Mat image_original_1 = cv::imread("../resources/image_sample.png");
    cv::Mat image_original_2 = cv::imread("../resources/image_sample.png");
    cv::Mat image_original_3 = cv::imread("../resources/image_sample.png");
    cv::Mat image_original_4 = cv::imread("../resources/image_sample.png");

    // 가우시안 블러 처리
    cv::Mat image_gaussianblur_1, image_gaussianblur_2, image_gaussianblur_3, image_gaussianblur_4;
    cv::GaussianBlur(image_original_1, image_gaussianblur_1, cv::Size(5, 5), 2);
    cv::GaussianBlur(image_original_2, image_gaussianblur_2, cv::Size(5, 5), 2);
    cv::GaussianBlur(image_original_3, image_gaussianblur_3, cv::Size(5, 5), 2);
    cv::GaussianBlur(image_original_4, image_gaussianblur_4, cv::Size(5, 5), 2);

    // 그레이스케일로 변환
    cv::Mat image_gray_1, image_gray_2, image_gray_3, image_gray_4;
    cv::cvtColor(image_gaussianblur_1, image_gray_1, cv::COLOR_BGR2GRAY);
    cv::cvtColor(image_gaussianblur_2, image_gray_2, cv::COLOR_BGR2GRAY);
    cv::cvtColor(image_gaussianblur_3, image_gray_3, cv::COLOR_BGR2GRAY);
    cv::cvtColor(image_gaussianblur_4, image_gray_4, cv::COLOR_BGR2GRAY);

    // Contour 메서드를 사용하기 위한 벡터 선언
    std::vector<std::vector<cv::Point>> image_contours_1;
    std::vector<std::vector<cv::Point>> image_contours_2;
    std::vector<std::vector<cv::Point>> image_contours_3;
    std::vector<std::vector<cv::Point>> image_contours_4;

    /* hierarchy 구조
    * [Next, Previous, First Child, Parent]
    * e.g.,) [2, -1, -1, 0]일 때:
    * Next(2): 현재 컨투어와 같은 부모를 가진 다음 컨투어는 인덱스 2임.
    * Previous(-1): 현재 컨투어와 같은 부모를 가진 이전 컨투어가 없음.
    * First Child(-1): 현재 컨투어에는 자식이 없음.
    * Parent(0): 현재 컨투어의 부모는 인덱스 0에 있는 컨투어임.
    
    */ 

    std::vector<cv::Vec4i> hierarchy_1;
    std::vector<cv::Vec4i> hierarchy_2;
    std::vector<cv::Vec4i> hierarchy_3;
    std::vector<cv::Vec4i> hierarchy_4;


    // Contour 방법1(RETR_EXTERNAL)
    cv::findContours(image_gray_1, image_contours_1, hierarchy_1, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Contour 방법2(RETR_LIST)
    cv::findContours(image_gray_2, image_contours_2, hierarchy_2, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

    // Contour 방법3(RETR_CCOMP)
    cv::findContours(image_gray_3, image_contours_3, hierarchy_3, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    // Contour 방법4(RETR_TREE)
    cv::findContours(image_gray_4, image_contours_4, hierarchy_4, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    // 외각선 그리리기
    cv::drawContours(image_original_1, image_contours_1, -1, cv::Scalar(0, 255, 0), 2);
    cv::drawContours(image_original_2, image_contours_2, -1, cv::Scalar(0, 255, 0), 2);
    cv::drawContours(image_original_3, image_contours_3, -1, cv::Scalar(0, 255, 0), 2);
    cv::drawContours(image_original_4, image_contours_4, -1, cv::Scalar(0, 255, 0), 2);


    // 이미지 출력
    cv::imshow("Contours Image 1", image_original_1);
    cv::imshow("Contours Image 2", image_original_2);
    cv::imshow("Contours Image 3", image_original_3);
    cv::imshow("Contours Image 4", image_original_4);
    
    // hierarchy 정보 추출
    std::cout << std::endl << "[Data of Countours_1 hierarchy]" << std::endl;
    for(int i = 0; i < hierarchy_1.size(); i++){
        std::cout << "[" << i << "]: " << hierarchy_1.at(i) << std::endl;
    }

    std::cout << std::endl <<  "[Data of Countours_2 hierarchy]" << std::endl;
    for(int i = 0; i < hierarchy_2.size(); i++){
        std::cout << "[" << i << "]: " << hierarchy_2.at(i) << std::endl;
    }

    std::cout << std::endl <<  "[Data of Countours_3 hierarchy]" << std::endl;
    for(int i = 0; i < hierarchy_3.size(); i++){
        std::cout << "[" << i << "]: " << hierarchy_3.at(i) << std::endl;
    }

    std::cout << std::endl << "[Data of Countours_4 hierarchy]" << std::endl;
    for(int i = 0; i < hierarchy_4.size(); i++){
        std::cout << "[" << i << "]: " << hierarchy_4.at(i) << std::endl;
    }



    cv::waitKey(0);

    return 0;
}