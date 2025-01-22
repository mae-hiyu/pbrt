#include <pbrt/pbrt.h>
#include <pbrt/util/spectrum.h>
#include <pbrt/util/spectrum.h>
#include <ext/tsv/sampling-tsvlight.h>
#include <iostream>

namespace pbrt {

PBRT_CPU_GPU Float SampleXyzXWavelengths(Float u) {
    const DenselySampledSpectrum &xSpectrum = Spectra::X();
    Float sum = 0.0;

    // Normalize
    for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
        sum += xSpectrum(lambda);
    }
    if (sum == 0.0) return Lambda_min; // Fallback for zero spectrum

    Float normFactor = 1.0 / sum;

    // Compute CDF
    std::array<Float, static_cast<size_t>(Lambda_max) - static_cast<size_t>(Lambda_min) + 1> cdf = {};
    Float cumulativeSum = 0.0;
    for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
        cumulativeSum += xSpectrum(lambda) * normFactor;
        cdf[lambda - Lambda_min] = cumulativeSum;
    }

    // Inverse transform sampling
    for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
        if (u <= cdf[lambda - Lambda_min]) {
            return lambda;
        }
    }
    return Lambda_max; // Default return
}

PBRT_CPU_GPU Float XyzXWavelengthsPDF(Float lambda) {
    const DenselySampledSpectrum &xSpectrum = Spectra::X();
    Float sum = 0.0;

    for (int i = Lambda_min; i <= Lambda_max; ++i) {
        sum += xSpectrum(i);
    }
    if (sum == 0.0 || lambda < Lambda_min || lambda > Lambda_max) return 0.0f;

    Float normFactor = 1.0 / sum;
    return xSpectrum(static_cast<int>(lambda)) * normFactor;
}

PBRT_CPU_GPU Float SampleXyzYWavelengths(Float u) {
    const DenselySampledSpectrum &ySpectrum = Spectra::Y();
    Float sum = 0.0;

    // Normalize
    for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
        sum += ySpectrum(lambda);
    }
    if (sum == 0.0) return Lambda_min; // Fallback for zero spectrum

    Float normFactor = 1.0 / sum;

    // Compute CDF
    std::array<Float, static_cast<size_t>(Lambda_max) - static_cast<size_t>(Lambda_min) + 1> cdf = {};    
    Float cumulativeSum = 0.0;
    for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
        cumulativeSum += ySpectrum(lambda) * normFactor;
        cdf[lambda - Lambda_min] = cumulativeSum;
    }

    // Inverse transform sampling
    for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
        if (u <= cdf[lambda - Lambda_min]) {
            return lambda;
        }
    }
    return Lambda_max; // Default return
}

PBRT_CPU_GPU Float XyzYWavelengthsPDF(Float lambda) {
    const DenselySampledSpectrum &ySpectrum = Spectra::Y();
    Float sum = 0.0;

    for (int i = Lambda_min; i <= Lambda_max; ++i) {
        sum += ySpectrum(i);
    }
    if (sum == 0.0 || lambda < Lambda_min || lambda > Lambda_max) return 0.0f;

    Float normFactor = 1.0 / sum;
    return ySpectrum(static_cast<int>(lambda)) * normFactor;
}

PBRT_CPU_GPU Float SampleXyzZWavelengths(Float u) {
    const DenselySampledSpectrum &zSpectrum = Spectra::Z();
    Float sum = 0.0;

    // Normalize
    for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
        sum += zSpectrum(lambda);
    }
    if (sum == 0.0) return Lambda_min; // Fallback for zero spectrum

    Float normFactor = 1.0 / sum;

    // Compute CDF
    std::array<Float, static_cast<size_t>(Lambda_max) - static_cast<size_t>(Lambda_min) + 1> cdf = {};
    Float cumulativeSum = 0.0;
    for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
        cumulativeSum += zSpectrum(lambda) * normFactor;
        cdf[lambda - Lambda_min] = cumulativeSum;
    }

    // Inverse transform sampling
    for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
        if (u <= cdf[lambda - Lambda_min]) {
            return lambda;
        }
    }
    return Lambda_max; // Default return
}

PBRT_CPU_GPU Float XyzZWavelengthsPDF(Float lambda) {
    const DenselySampledSpectrum &zSpectrum = Spectra::Z();
    Float sum = 0.0;

    for (int i = Lambda_min; i <= Lambda_max; ++i) {
        sum += zSpectrum(i);
    }
    if (sum == 0.0 || lambda < Lambda_min || lambda > Lambda_max) return 0.0f;

    Float normFactor = 1.0 / sum;
    return zSpectrum(static_cast<int>(lambda)) * normFactor;
}


}