#include "ImageAnalyzer.h"

std::vector<ParamSet> ImageAnalyzer::generateParams(const cv::Mat& src)
{
    std::vector<ParamSet> params;

    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    double meanVal = cv::mean(gray)[0];

    int baseThresh = static_cast<int>(meanVal);

    for (int t = baseThresh - 40; t <= baseThresh + 40; t += 20)
    {
        for (int blur = 3; blur <= 7; blur += 2)
        {
            ParamSet p;
            p.thresh = std::max(10, std::min(200, t));
            p.blur = blur;
            p.canny1 = 50;
            p.canny2 = 150;
            params.push_back(p);
        }
    }

    return params;
}