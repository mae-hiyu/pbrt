#ifndef PBRT_EXT_TSV_SAMPLING_TSV_LIGHT
#define PBRT_EXT_TSV_SAMPLING_TSV_LIGHT

#include <pbrt/pbrt.h>
#include <pbrt/util/sampling.h>

namespace pbrt {

PBRT_CPU_GPU Float SampleXyzXWavelengths(Float u);

PBRT_CPU_GPU Float XyzXWavelengthsPDF(Float lambda);

PBRT_CPU_GPU Float SampleXyzYWavelengths(Float u);

PBRT_CPU_GPU Float XyzYWavelengthsPDF(Float lambda);

PBRT_CPU_GPU Float SampleXyzZWavelengths(Float u);

PBRT_CPU_GPU Float XyzZWavelengthsPDF(Float lambda);

}

#endif