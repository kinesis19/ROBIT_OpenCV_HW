#include "rclcpp/rclcpp.hpp"
#include "opencv_arm_draw/opencv_arm_draw.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    
    auto node = std::make_shared<OpenCVArmDraw>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}