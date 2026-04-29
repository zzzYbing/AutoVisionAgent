#include "Agent.h"
#include <iostream>

AgentResult VisionAgent::run(const cv::Mat& src)
{
    AgentResult best;
    best.score = 1e12;

    // === 感知 Agent ===
    auto paramCandidates = analyzer.generateParams(src);

    int iter = 0;
    double lastBest = 1e12;

    for (auto& param : paramCandidates)
    {
        // === 执行 Agent ===
        auto result = detector.detect(src, param);

        if (!result.valid) continue;

        // === 评估 Agent ===
        double score = evaluator.evaluate(result);

        if (score < best.score)
        {
            best.score = score;
            best.center = result.center;
            best.radius = result.radius;
        }

        // === 收敛判断（关键）===
        if (fabs(lastBest - best.score) < 0.01)
            break;

        lastBest = best.score;

        if (++iter > 50) break;
    }

    return best;
}