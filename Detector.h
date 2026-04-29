#pragma once
#include <opencv2/opencv.hpp>
#include "ImageAnalyzer.h"

struct DetectResult {
    cv::Point2f center;
    float radius;
    double error;
    int pointCount;
    bool valid;
};

class Detector {
public:
    DetectResult detect(const cv::Mat& src, const ParamSet& param);

private:
    bool fitCircle(const std::vector<cv::Point>& pts,
                   cv::Point2f& center,
                   float& radius,
                   double& error);
};