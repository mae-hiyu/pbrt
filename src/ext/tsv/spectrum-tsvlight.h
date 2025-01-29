#ifndef PBRT_EXT_TSV_SPECTRUM_TSV_LIGHT
#define PBRT_EXT_TSV_SPECTRUM_TSV_LIGHT

#include <iostream>
#include <fstream>
#include <pbrt/pbrt.h>
#include <pbrt/util/spectrum.h>
#include <pbrt/util/sampling.h>
#include <ext/tsv/sampling-tsvlight.h>

namespace pbrt {

class SampledXYZWavelengths : public SampledWavelengths {
  public:

    PBRT_CPU_GPU
    static SampledXYZWavelengths SampleTsv(Float u, Float lambda_min = Lambda_min,
                                          Float lambda_max = Lambda_max) {
      SampledXYZWavelengths swl;
      // swl.setWavelengthSize(x, y, z);

      for(int i = 0; i < swl.x_size; ++i) {
        Float up = u + Float(i) / swl.x_size;
        if(up > 1)
          up -= 1;

        swl.lambda[i] = SampleXyzXWavelengths(up);
        swl.pdf[i] = 1;        
      }
      for(int i = 0; i < swl.y_size; ++i) {
        Float up = u + Float(i) / swl.y_size;
        if(up > 1)
          up -= 1;

        swl.lambda[swl.x_size + i] = SampleXyzYWavelengths(up);
        swl.pdf[swl.x_size + i] = 1;
      }
      for(int i = 0; i < swl.z_size; ++i) {
        Float up = u + Float(i) / swl.z_size;
        if(up > 1)
          up -= 1;

        swl.lambda[swl.x_size + swl.y_size + i] = SampleXyzZWavelengths(up);
        swl.pdf[swl.x_size + swl.y_size + i] = 1;
      }
        return swl;
    }

    PBRT_CPU_GPU
    static SampledXYZWavelengths SampleTsvLight(Float u, Float lambda_min = Lambda_min,
                                         Float lambda_max = Lambda_max, int total_size = NSpectrumSamples) {
    SampledXYZWavelengths swl;

    // 確率に基づいたサンプル数の決定
    swl.x_size = std::round(total_size * 0.437);
    swl.y_size = std::round(total_size * 0.405);
    swl.z_size = total_size - swl.x_size - swl.y_size;  // 誤差調整

    for(int i = 0; i < swl.x_size; ++i) {
        Float up = u + Float(i) / swl.x_size;
        if(up > 1) up -= 1;

        swl.lambda[i] = SampleLightXyzXWavelengths(up);
        swl.pdf[i] = 1;
    }

    for(int i = 0; i < swl.y_size; ++i) {
        Float up = u + Float(i) / swl.y_size;
        if(up > 1) up -= 1;

        swl.lambda[swl.x_size + i] = SampleLightXyzYWavelengths(up);
        swl.pdf[swl.x_size + i] = 1;
    }

    for(int i = 0; i < swl.z_size; ++i) {
        Float up = u + Float(i) / swl.z_size;
        if(up > 1) up -= 1;

        swl.lambda[swl.x_size + swl.y_size + i] = SampleLightXyzZWavelengths(up);
        swl.pdf[swl.x_size + swl.y_size + i] = 1;
    }
    return swl;
}

  private:
    // SampledWavelengths Private Members
    friend struct SOA<SampledXYZWavelengths>;
    pstd::array<Float, NSpectrumSamples> lambda, pdf;
    int x_size;
    int y_size;
    int z_size;
};

namespace XYZSpectra {

void Init(Allocator alloc);

PiecewiseLinearSpectrum *xlight, *ylight, *zlight;

void Init(Allocator alloc) {
  
}

PBRT_CPU_GPU
inline const PiecewiseLinearSpectrum &Xlight() {
#ifdef PBRT_IS_GPU_CODE
    extern PBRT_GPU DenselySampledSpectrum *xlightGPU;
    return *xlightGPU;
#else
    extern PiecewiseLinearSpectrum *xlight;
    return *xlight;
#endif

}
// namespace Spectra
}
}
// namespace pbrt
#endif