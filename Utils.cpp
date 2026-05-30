#include "Utils.h"
#include <float.h>
#include <math.h>
#include <stdlib.h>

bool IsFloatEqual(float Num1, float Num2)
{
    return fabsf(Num1 - Num2) <= 0.001f;
}

float GetRandom()
{
    return rand() / (float)RAND_MAX;   // 0.0f ~ 1.0f
}

int GetRandomRange(int Min, int Max)
{
    return Min + rand() % (Max - Min + 1);  // Min ~ Max(양끝 포함)
}