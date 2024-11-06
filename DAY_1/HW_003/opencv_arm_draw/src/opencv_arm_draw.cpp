#include "opencv_arm_draw/opencv_arm_draw.hpp"

const int link1_length = 50; // 첫 번째 링크의 길이
const int link2_length = 100; // 두 번째 링크의 길이
const cv::Point joint1_position(320, 240); // 첫 번째 조인트 (빨간색 조인트)

OpenCVArmDraw::OpenCVArmDraw() : Node("opencv_arm_draw")
{
    RCLCPP_INFO(this->get_logger(), "OpenCV Arm Draw Node 초기화");
    run();
}

// 프로세스 시작
void OpenCVArmDraw::run()
{
    double angle1 = 0.0; // 첫 번째 링크의 회전 각도
    double angle2 = 0.0; // 두 번째 링크의 회전 각도

    while (true) {
        // 빈 이미지 생성 -> 백그라운드
        cv::Mat image = cv::Mat::zeros(480, 640, CV_8UC3);

        // 첫 번째 링크의 끝 좌표 계산
        cv::Point joint2_position(
            joint1_position.x + static_cast<int>(link1_length * cos(angle1)),
            joint1_position.y + static_cast<int>(link1_length * sin(angle1))
        );

        // 두 번째 링크의 끝 좌표 계산
        cv::Point end_effector_position(
            joint2_position.x + static_cast<int>(link2_length * cos(angle1 + angle2)),
            joint2_position.y + static_cast<int>(link2_length * sin(angle1 + angle2))
        );

        // 링크와 조인트 그리기
        cv::line(image, joint1_position, joint2_position, cv::Scalar(200, 200, 200), 2); // 첫 번째 링크
        cv::line(image, joint2_position, end_effector_position, cv::Scalar(200, 200, 200), 2); // 두 번째 링크

        cv::circle(image, joint1_position, 10, cv::Scalar(255, 46, 99), -1); // 조인트1
        cv::circle(image, joint2_position, 10, cv::Scalar(8, 217, 214), -1); // 조인트2
        cv::circle(image, end_effector_position, 10, cv::Scalar(255, 0, 0), -1); // 조인트3

        // 각도 업데이트 (반시계 방향 회전)
        angle1 -= 0.05; // 첫 번째 링크의 회전 속도
        angle2 -= 0.08; // 두 번째 링크의 회전 속도

        // 이미지 출력
        cv::imshow("2DOF Robot Arm", image);

        // 종료 조건
        cv::waitKey(15);
    }

}
