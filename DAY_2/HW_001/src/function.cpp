#include "function.hpp"
#include <opencv4/opencv2/opencv.hpp>


/* 보려고 적은 MORPH 상수 모음
* cv::MORPH_ERODE: 0
* cv::MORPH_DILATE: 1
* cv::MORPH_OPEN: 2
* cv::MORPH_CLOSE: 3
* cv::MORPH_GRADIENT: 4
* cv::MORPH_TOPHAT: 5
* cv::MORPH_BLACKHAT: 6
* cv::MORPH_HITMISS: 7
*/

// Open() 메서드
void OpenCV_Open(cv::InputArray src, cv::OutputArray dst, int op, cv::InputArray kernel, cv::Point anchor, int iterations, int borderType, const cv::Scalar& borderValue) {
    // MORPH_OPEN으로 파라미터를 받았을 때 = OpenCV의 Open 메서드를 사용하겠다
    if(op == 2){
        cv::erode(src, dst, kernel);
    }
}

// Close() 메서드
void OpenCV_Close(cv::InputArray src, cv::OutputArray dst, int op, cv::InputArray kernel, cv::Point anchor, int iterations, int borderType, const cv::Scalar& borderValue) {

    if(op == 3){
        cv::dilate(src, dst, kernel);
    }
}