#include "Evaluator.h"

double Evaluator::evaluate(const DetectResult& res)
{
    if (!res.valid) return 1e9;

    // 综合评分（可自己调）
    return res.error * 1000 - res.pointCount * 0.3;
}