#ifndef OPENCV_ARM_DRAW_HPP
#define OPENCV_ARM_DRAW_HPP

#include "rclcpp/rclcpp.hpp"
#include <opencv2/opencv.hpp>
#include <cmath>

class OpenCVArmDraw : public rclcpp::Node
{
public:
    OpenCVArmDraw(); // 생성자
    void run(); // 프로세스 시작
private:

};

#endif // OPENCV_ARM_DRAW_HPP