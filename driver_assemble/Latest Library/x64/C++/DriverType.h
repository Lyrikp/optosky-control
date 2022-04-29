#ifndef _TYPE_H_
#define _TYPE_H_

#define MAX_LINEAR_FACTOR_NUM 100
#define MAX_WAVE_FACTOR_NUM 10
#define MAX_SHAPE_FACTOR_NUM 3000
#define MAX_DARK_FACTOR_NUM 3000
#define SPECTRUM_SIZE 4096

typedef struct DarkFactor
{
	float k;
	float b;
}s_DARK_FACTOR;

typedef struct
{
	int iByteSize;
	int iFactorLenth;
	s_DARK_FACTOR SDarkFactor[MAX_DARK_FACTOR_NUM];
}DarkFactorArray;

typedef struct
{
	int iFactorLenth;
	s_DARK_FACTOR *SDarkFactor;
}DarkFactorArraysp;

typedef struct
{
	int iByteSize;
	int iFactorLenth;
	float LinearFactor[MAX_LINEAR_FACTOR_NUM];
}LinearFactorArray;

typedef struct
{
	int iByteSize;
	int iFactorLenth;
	float WaveFactor[MAX_WAVE_FACTOR_NUM];
}WaveFactorArray;

typedef struct
{
	int iByteSize;
	int iFactorLenth;
	float ShapeFactor[MAX_SHAPE_FACTOR_NUM];
}ShapeFactorArray;

typedef struct
{
	int iFactorLenth;
	float *Factor;
}FactorArraysp;

typedef struct
{
	int array[SPECTRUM_SIZE];
	int valid_flag;
}Spectrum;

typedef struct
{
	int *array;
	int valid_flag;
}Spectrumsp;

struct DeviceProperty {
	int PixelCount;
	int Model;
	int MaximumIntegrationTime;
};

struct device_descriptor {
	char serial[128];
};

struct spectrum_device_info
{
	int length;
	device_descriptor descriptor[10];
};

#endif