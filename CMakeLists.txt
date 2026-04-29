cmake_minimum_required(VERSION 3.10)
project(AutoVisionAgent)

find_package(OpenCV REQUIRED)

add_executable(AutoVisionAgent
    main.cpp
    Agent.cpp
    ImageAnalyzer.cpp
    Detector.cpp
    Evaluator.cpp
)

target_include_directories(AutoVisionAgent PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(AutoVisionAgent ${OpenCV_LIBS})