#pragma once

#include <random>

//--------------------------------------------------------------------------------------
// Noiseクラス：ノイズ
//--------------------------------------------------------------------------------------
class Noise
{
public:
    Noise();
    double Fade(double t);
    double Lerp(double t, double a, double b);
    double Grad(int hash, double x, double y, double z);
    double CalculationNoise(double x, double y, double z);
    double Octave(double x, double y, double z, int octaves);
private:
    int p[512];
};