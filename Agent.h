#pragma once
#include <opencv2/opencv.hpp>
#include "ImageAnalyzer.h"
#include "Detector.h"
#include "Evaluator.h"

struct AgentResult {
    cv::Point2f center;
    float radius;
    double score;
};

class VisionAgent {
public:
    AgentResult run(const cv::Mat& src);

private:
    ImageAnalyzer analyzer;
    Detector detector;
    Evaluator evaluator;
};