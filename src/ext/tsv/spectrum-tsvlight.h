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
    static size_t x_size, y_size, z_size;

    static void setWavelengthSize(size_t x, size_t y, size_t z) {
      x_size = x;
      y_size = y;
      z_size = z;
    }

    PBRT_CPU_GPU
    static SampledXYZWavelengths SampleTsv(Float u, Float lambda_min = Lambda_min,
                                          Float lambda_max = Lambda_max, 
                                           size_t x = 4, size_t y = 4, size_t z = 4) {
      SampledXYZWavelengths swl;
      swl.setWavelengthSize(x, y, z);
      
      for(size_t i = 0; i < NSpectrumSamples; i++) {
        Float up = u + Float(i) / NSpectrumSamples;
        if(up > 1)
          up -= 1;
        
        if(i < x){
          swl.lambda[i] = SampleXyzXWavelengths(up);
          swl.pdf[i] = XyzXWavelengthsPDF(swl.lambda[i]);
        } else if(i < y) {
          swl.lambda[i] = SampleXyzYWavelengths(up);
          swl.pdf[i] = XyzYWavelengthsPDF(swl.lambda[i]);
        } else if(i < z) {
          swl.lambda[i] = SampleXyzZWavelengths(up);
          swl.pdf[i] = XyzZWavelengthsPDF(swl.lambda[i]);
        }

        return swl;
      }
    }

  private:
    // SampledWavelengths Private Members
    friend struct SOA<SampledXYZWavelengths>;
    pstd::array<Float, NSpectrumSamples> lambda, pdf;
};


size_t SampledXYZWavelengths::x_size = 0;
size_t SampledXYZWavelengths::y_size = 0;
size_t SampledXYZWavelengths::z_size = 0;

static Float xHistogram[400] = {0}, yHistogram[400] = {0}, zHistogram[400] = {0};

}
// namespace pbrt
#endif