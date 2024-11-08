cmake_minimum_required(VERSION 3.10)
project(OpenCV_Contours_Extraction)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)

# OpenCV 라이브러리 찾기
find_package(OpenCV REQUIRED)

# 소스 파일
file(GLOB SOURCES "src/*.cpp")

# 실행 파일 생성
add_executable(${PROJECT_NAME} ${SOURCES})

# include 디렉토리
target_include_directories(${PROJECT_NAME} PRIVATE include)

# OpenCV 라이브러리 링크
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
