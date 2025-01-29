#ifndef PBRT_EXT_TSV_SPECTRUM_TSV_LIGHT
#define PBRT_EXT_TSV_SPECTRUM_TSV_LIGHT

#include <iostream>
#include <fstream>
#include <pbrt/pbrt.h>
#include <pbrt/util/spectrum.h>
#include <pbrt/util/sampling.h>
#include <ext/tsv/sampling-tsvlight.h>

namespace pbrt {

namespace XYZSpectra {

PiecewiseLinearSpectrum *xlight, *ylight, *zlight;

void Init(Allocator alloc) {
    
}

}
// namespace 
}
// namespace pbrt

#endif