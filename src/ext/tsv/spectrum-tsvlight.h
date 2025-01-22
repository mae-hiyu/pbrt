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
      static constexpr int x_size = 4;  // 宣言
      static constexpr int y_size = 4;
      static constexpr int z_size = 4;

    // static void setWavelengthSize(int x, int y, int z) {
    //   x_size = x;
    //   y_size = y;
    //   z_size = z;
    // }

    PBRT_CPU_GPU
    static SampledXYZWavelengths SampleTsv(Float u, Float lambda_min = Lambda_min,
                                          Float lambda_max = Lambda_max) {
      SampledXYZWavelengths swl;
      // swl.setWavelengthSize(x, y, z);

      for(int i = 0; i < x_size; ++i) {
        Float up = u + Float(i) / x_size;
        if(up > 1)
          up -= 1;

        swl.lambda[i] = SampleXyzXWavelengths(up);
        swl.pdf[i] = XyzXWavelengthsPDF(swl.lambda[i]);        
      }
      for(int i = 0; i < y_size; ++i) {
        Float up = u + Float(i) / y_size;
        if(up > 1)
          up -= 1;

        swl.lambda[x_size + i] = SampleXyzYWavelengths(up);
        swl.pdf[x_size + i] = XyzYWavelengthsPDF(swl.lambda[x_size + i]);
      }
      for(int i = 0; i < z_size; ++i) {
        Float up = u + Float(i) / z_size;
        if(up > 1)
          up -= 1;

        swl.lambda[x_size + y_size + i] = SampleXyzZWavelengths(up);
        swl.pdf[x_size + y_size + i] = XyzZWavelengthsPDF(swl.lambda[x_size + i]);
      }
        std::cout << "!lambda!" << swl.lambda[2] << std::endl;
        return swl;
      }

  private:
    // SampledWavelengths Private Members
    friend struct SOA<SampledXYZWavelengths>;
    pstd::array<Float, NSpectrumSamples> lambda, pdf;
};
}
// namespace pbrt
#endif