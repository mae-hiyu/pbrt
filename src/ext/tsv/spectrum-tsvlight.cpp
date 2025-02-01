#include <iostream>
#include <fstream>
#include <pbrt/pbrt.h>
#include <pbrt/util/spectrum.h>
#include <pbrt/util/sampling.h>
#include <ext/tsv/sampling-tsvlight.h>

namespace pbrt {

namespace XYZSpectra {

DenselySampledSpectrum *normalizedX, *normalizedY, *normalizedZ;

PiecewiseLinearSpectrum *xlight, *ylight, *zlight;

void Init(Allocator alloc) {   
  normalizedX = alloc.new_object<DenselySampledSpectrum>(Spectra::X(), alloc);
    normalizedX = alloc.new_object<DenselySampledSpectrum>(Spectra::X(), alloc);
    normalizedY = alloc.new_object<DenselySampledSpectrum>(Spectra::Y(), alloc);
    normalizedZ = alloc.new_object<DenselySampledSpectrum>(Spectra::Z(), alloc);

    Float scaleX = CIE_Y_integral / InnerProduct(normalizedX, &Spectra::Y());
    Float scaleY = CIE_Y_integral / InnerProduct(normalizedY, &Spectra::Y());
    Float scaleZ = CIE_Y_integral / InnerProduct(normalizedZ, &Spectra::Y());
    normalizedX->Scale(scaleX);
    normalizedY->Scale(scaleY);
    normalizedZ->Scale(scaleZ);

    int nSamples = Lambda_max - Lambda_min + 1;
    const Spectrum light = GetNamedSpectrum("f12");
    pstd::vector<Float> targetLambdas(nSamples);
    for (int i = 0; i < nSamples; ++i) {
        targetLambdas[i] = Lambda_min + i;
    }

    // xlight, ylight, zlight 用の CDF を計算
    pstd::vector<Float> xCDF(nSamples, 0), yCDF(nSamples, 0), zCDF(nSamples, 0);
    Float xSum = 0, ySum = 0, zSum = 0;

    for (int i = 1; i < nSamples; ++i) {
        Float dx = targetLambdas[i] - targetLambdas[i - 1];
        Float xVal = (*normalizedX)(targetLambdas[i]) * light(targetLambdas[i]);
        Float yVal = (*normalizedY)(targetLambdas[i]) * light(targetLambdas[i]);
        Float zVal = (*normalizedZ)(targetLambdas[i]) * light(targetLambdas[i]);

        xSum += 0.5 * (xVal + (*normalizedX)(targetLambdas[i - 1]) * light(targetLambdas[i - 1])) * dx;
        ySum += 0.5 * (yVal + (*normalizedY)(targetLambdas[i - 1]) * light(targetLambdas[i - 1])) * dx;
        zSum += 0.5 * (zVal + (*normalizedZ)(targetLambdas[i - 1]) * light(targetLambdas[i - 1])) * dx;

        xCDF[i] = xSum;
        yCDF[i] = ySum;
        zCDF[i] = zSum;
    }

    // CDF を正規化
    for (int i = 0; i < nSamples; ++i) {
        xCDF[i] /= xSum;
        yCDF[i] /= ySum;
        zCDF[i] /= zSum;
    }

    // PiecewiseLinearSpectrum を確保
    xlight = alloc.new_object<PiecewiseLinearSpectrum>(targetLambdas, xCDF, alloc);
    ylight = alloc.new_object<PiecewiseLinearSpectrum>(targetLambdas, yCDF, alloc);
    zlight = alloc.new_object<PiecewiseLinearSpectrum>(targetLambdas, zCDF, alloc);
}


}
// namespace XYZSpectra

}
// namespace pbrt
