#include <pbrt/pbrt.h>
#include <pbrt/util/spectrum.h>
#include <pbrt/util/spectrum.h>
#include <ext/tsv/sampling-tsvlight.h>

namespace pbrt {

PBRT_CPU_GPU Float SampleXyzXWavelengths(Float u) {
  const DenselySampledSpectrum &xSpectrum = Spectra::X();
  // normalize 
  Float sum = 0.0;
  for (int lambda = Lambda_min; lambda < Lambda_max + 1; ++lambda){
    sum += xSpectrum(lambda);
  }

  Float normFactor = 1.0 / sum;

    // Compute the cumulative distribution function (CDF)
  pstd::vector<Float> cdf(Lambda_max - Lambda_min + 1, 0.0);
  Float cumulativeSum = 0.0;
  for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
      cumulativeSum += xSpectrum(lambda) * normFactor;
      cdf[lambda - Lambda_min] = cumulativeSum;
  }

  // Perform inverse transform sampling
  // Find the wavelength corresponding to the sampled value `u`
  for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
      if (u <= cdf[lambda - Lambda_min]) {
          return lambda;
      }
  }
}

PBRT_CPU_GPU Float XyzXWavelengthsPDF(Float lambda) {
  const DenselySampledSpectrum &xSpectrum = Spectra::X();
    // normalize 
  Float sum = 0.0;
  for (int i = Lambda_min; lambda < Lambda_max + 1; ++lambda){
    sum += xSpectrum(i);
  }
  
  Float normFactor = 1.0 / sum;

    // Compute the cumulative distribution function (CDF)
  pstd::vector<Float> pdf(Lambda_max - Lambda_min + 1, 0.0);
  Float cumulativeSum = 0.0;
  for (int i = Lambda_min; lambda <= Lambda_max; ++lambda) {
      pdf = xSpectrum(i) * normFactor;
  }
  return pdf[lambda - Lambda_min];
}

PBRT_CPU_GPU Float SampleXyzYWavelengths(Float u) {
  const DenselySampledSpectrum &ySpectrum = Spectra::Y();
  // normalize 
  Float sum = 0.0;
  for (int lambda = Lambda_min; lambda < Lambda_max + 1; ++lambda){
    sum += ySpectrum(lambda);
  }
  
  Float normFactor = 1.0 / sum;

    // Compute the cumulative distribution function (CDF)
  pstd::vector<Float> cdf(Lambda_max - Lambda_min + 1, 0.0);
  Float cumulativeSum = 0.0;
  for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
      cumulativeSum += ySpectrum(lambda) * normFactor;
      cdf[lambda - Lambda_min] = cumulativeSum;
  }

  // Perform inverse transform sampling
  // Find the wavelength corresponding to the sampled value `u`
  for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
      if (u <= cdf[lambda - Lambda_min]) {
          return lambda;
      }
  }
}

PBRT_CPU_GPU Float XyzYWavelengthsPDF(Float lambda) {
  const DenselySampledSpectrum &ySpectrum = Spectra::Y();
    // normalize 
  Float sum = 0.0;
  for (int i = Lambda_min; lambda < Lambda_max + 1; ++lambda){
    sum += ySpectrum(i);
  }
  
  Float normFactor = 1.0 / sum;

    // Compute the cumulative distribution function (CDF)
  pstd::vector<Float> pdf(Lambda_max - Lambda_min + 1, 0.0);
  Float cumulativeSum = 0.0;
  for (int i = Lambda_min; lambda <= Lambda_max; ++lambda) {
      pdf = ySpectrum(i) * normFactor;
  }
  return pdf[lambda - Lambda_min];
}

PBRT_CPU_GPU Float SampleXyzZWavelengths(Float u) {
  const DenselySampledSpectrum &zSpectrum = Spectra::Z();
    // normalize 
  Float sum = 0.0;
  for (int lambda = Lambda_min; lambda < Lambda_max + 1; ++lambda){
    sum += zSpectrum(lambda);
  }
  
  Float normFactor = 1.0 / sum;

    // Compute the cumulative distribution function (CDF)
  pstd::vector<Float> cdf(Lambda_max - Lambda_min + 1, 0.0);
  Float cumulativeSum = 0.0;
  for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
      cumulativeSum += zSpectrum(lambda) * normFactor;
      cdf[lambda - Lambda_min] = cumulativeSum;
  }

  // Perform inverse transform sampling
  // Find the wavelength corresponding to the sampled value `u`
  for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
      if (u <= cdf[lambda - Lambda_min]) {
          return lambda;
          
      }
  }
}

PBRT_CPU_GPU Float XyzZWavelengthsPDF(Float lambda) {
  const DenselySampledSpectrum &zSpectrum = Spectra::Z();
    // normalize 
  Float sum = 0.0;
  for (int i = Lambda_min; lambda < Lambda_max + 1; ++lambda){
    sum += zSpectrum(i);
  }
  
  Float normFactor = 1.0 / sum;

    // Compute the cumulative distribution function (CDF)
  pstd::vector<Float> pdf(Lambda_max - Lambda_min + 1, 0.0);
  Float cumulativeSum = 0.0;
  for (int i = Lambda_min; lambda <= Lambda_max; ++lambda) {
      pdf = zSpectrum(i) * normFactor;
  }
  return pdf[lambda - Lambda_min];
}

}