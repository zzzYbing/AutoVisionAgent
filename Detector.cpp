#include "Detector.h"
#include <cmath>

DetectResult Detector::detect(const cv::Mat& src, const ParamSet& param)
{
    DetectResult res;
    res.valid = false;

    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

    cv::GaussianBlur(gray, gray, cv::Size(param.blur, param.blur), 0);

    cv::Mat bin;
    cv::threshold(gray, bin, param.thresh, 255, cv::THRESH_BINARY_INV);

    cv::Mat edge;
    cv::Canny(bin, edge, param.canny1, param.canny2);

    std::vector<cv::Point> pts;
    for (int y = 0; y < edge.rows; y++)
        for (int x = 0; x < edge.cols; x++)
            if (edge.at<uchar>(y, x))
                pts.emplace_back(x, y);

    if (pts.size() < 30) return res;

    if (!fitCircle(pts, res.center, res.radius, res.error))
        return res;

    res.pointCount = pts.size();
    res.valid = true;
    return res;
}

// ===== 最小二乘拟合 =====
bool Detector::fitCircle(const std::vector<cv::Point>& pts,
                         cv::Point2f& center,
                         float& radius,
                         double& error)
{
    int N = pts.size();
    if (N < 10) return false;

    double sumX = 0, sumY = 0, sumX2 = 0, sumY2 = 0;

    for (auto& p : pts) {
        sumX += p.x;
        sumY += p.y;
        sumX2 += p.x * p.x;
        sumY2 += p.y * p.y;
    }

    double cx = sumX / N;
    double cy = sumY / N;

    center = cv::Point2f(cx, cy);

    double r = 0;
    for (auto& p : pts)
        r += cv::norm(p - center);

    radius = r / N;

    error = 0;
    for (auto& p : pts)
        error += fabs(cv::norm(p - center) - radius);

    error /= N;

    return true;
}