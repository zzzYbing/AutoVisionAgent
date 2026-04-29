#include <opencv2/opencv.hpp>
#include <iostream>
#include "Agent.h"

int main()
{
    cv::Mat src = cv::imread("test.png");
    if (src.empty()) {
        std::cout << "图像读取失败" << std::endl;
        return -1;
    }

    VisionAgent agent;
    auto result = agent.run(src);

    std::cout << "center: " << result.center << std::endl;
    std::cout << "radius: " << result.radius << std::endl;
    std::cout << "score: " << result.score << std::endl;

    cv::Mat show = src.clone();
    cv::circle(show, result.center, result.radius, cv::Scalar(0,0,255), 2);

    cv::imshow("result", show);
    cv::waitKey(0);

    return 0;
}