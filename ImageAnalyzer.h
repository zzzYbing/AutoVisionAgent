#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

struct ParamSet {
    int thresh;
    int blur;
    int canny1;
    int canny2;
};

class ImageAnalyzer {
public:
    std::vector<ParamSet> generateParams(const cv::Mat& src);
};