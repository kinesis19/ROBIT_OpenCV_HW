#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <opencv2/opencv.hpp>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/core/types.hpp>
#include <opencv4/opencv2/opencv.hpp>

void OpenCV_Open(cv::InputArray src, cv::OutputArray dst, int op, cv::InputArray kernel, cv::Point anchor, int iterations, int borderType, const cv::Scalar& borderValue);
void OpenCV_Close(cv::InputArray src, cv::OutputArray dst, int op, cv::InputArray kernel, cv::Point anchor, int iterations, int borderType, const cv::Scalar& borderValue);

#endif // FUNCTION_HPP
