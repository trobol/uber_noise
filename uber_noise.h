#ifndef _UBER_NOISE_UBER_NOISE_H
#define _UBER_NOISE_UBER_NOISE_H

#include <algorithm>
#include <cmath>

float max(float a, float b) { return a > b ? a : b; }
float min(float a, float b) { return a < b ? a : b; }

float lerp(float a, float b, float x) { return (b - a) * x + a; }

float abs(float a) { return a > 0 ? a : -a; }

struct vec3
{
	float x, y, z;
};

float dot(vec3 a, vec3 b) { return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z)); }

float uber_noise(vec3 position, int octaves, float pertubedFeatures,
		 float Sharpness, float amplifyFeatures, float altitudeErosion,
		 float ridgedErosion, float slopeErosion, float lancunarity,
		 float gain)
{

	// sharpness
	float RidgedNoise = (1.0f - abs(FeatureNoise));
	float BillowNoise = FeatureNoise * FeatureNoise;

	FeatureNoise = lerp(FeatureNoise, lfBillowNoise, max(0.0, Sharpness));

	FeatureNoise = lerp(FeatureNoise, lfRidgedNoise, min(0.0, lfSharpness));

	// slope erosion
	lfSharpnessDerivativeSum += lDerivative * lfSlopeErosion;

	lfSum += lfAmplitude * FeatureNoise *
		 (1.0f / (1.0f + dot(lfSharpnessDerivativeSum,
				     lfSharpnessDerivativeSum)));

	// amplitude Damping
	lfSum += lfDampedAmplitude * FeatureNoise *
		 (1.0f / (1.0f + dot(lfSlopeErosionDerivativeSum,
				     lfSlopeErosionDerivativeSum)));

	lfAmplitude *=
	    lerp(lfCurrentGain, lfCurrentGain * smoothStep(0.0f, 1.0f, lfSum),
		 lfAltitudeErosion);

	lfDampedAplitude = lfAmplitude * (1.0f - (lfRidgeErosion / (1.0f + dot(lfRidgeEorisonDirivativeSum, lfRidgeEorisonDirivativeSum)));

	// domain perturb
	lOctavePosition = (lPosition * lfFrequency) + lPerturbDerivativeSum;

	lPerturbDerivativeSum += lDerivative * lfPerturbFeaters;

	// amplify features
	float lfCurrentGain = gain + amplifyFeatures;
}

#endif