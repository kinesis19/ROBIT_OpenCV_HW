#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

int main() {
    // 이미지 타겟팅
    cv::Mat image_original = cv::imread("../resources/KULS.png");
    cv::Mat image_noise = cv::imread("../resources/noisyImage.png");

    // 1. Averaging
    cv::Mat image_blur;
    cv::blur(image_original, image_blur, cv::Size(5, 5));

    // 2. Median Filtering
    cv::Mat image_median_filtering;
    cv::medianBlur(image_noise, image_median_filtering, 5); // 커널 크기 5x5


    // 3. Convolution Filtering (컨볼루션 필터) - 샤프닝 필터 예제
    cv::Mat image_convolution;
    cv::Mat sharpening_kernel = (cv::Mat_<float>(3, 3) << 
        0, -1,  0,
        -1,  5, -1,
        0, -1,  0); // 샤프닝 필터 커널

    cv::filter2D(image_original, image_convolution, -1, sharpening_kernel);

    // 이미지 출력
    cv::imshow("Original Image", image_original); // 원본 이미지
    cv::imshow("Averaging Image", image_blur); // Averaging 이미지
    cv::imshow("Dot Noise Image", image_noise); // salt and pepper 이미지
    cv::imshow("Median Filtering Image", image_median_filtering); // Median Filtering 이미지
    cv::imshow("Median Filtering Image", image_median_filtering); // Median 필터 적용 이미지
    cv::imshow("Convolution Filtered Image", image_convolution); // Convolution 필터(샤프닝) 적용 이미지
    
    cv::waitKey(0);

    return 0;
}