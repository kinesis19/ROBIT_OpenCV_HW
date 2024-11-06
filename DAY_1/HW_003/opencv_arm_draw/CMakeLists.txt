cmake_minimum_required(VERSION 3.8)
project(opencv_arm_draw)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


# Setting Standard C++ (New)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(OpenCV REQUIRED)

# Add include directory (New)
include_directories(
  include
  ${rclcpp_INCLUDE_DIRS}
)

# Add executable file (Update)
add_executable(opencv_arm_draw 
  src/main.cpp
  src/opencv_arm_draw.cpp
)

# Add ament dependency
ament_target_dependencies(opencv_arm_draw 
  rclcpp
  OpenCV
)

# Setting Install target
install(TARGETS
  opencv_arm_draw
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
