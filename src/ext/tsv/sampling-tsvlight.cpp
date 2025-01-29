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

PBRT_CPU_GPU Float SampleLightXyzXWavelengths(Float u) {
    const DenselySampledSpectrum &xSpectrum = Spectra::X();
    const Spectrum f12 = GetNamedSpectrum("f12");
    Float sumX = 0.0, sumF12 = 0.0;

    // スペクトルの正規化係数を計算
    for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
        sumX += xSpectrum(lambda); // 負の値を排除
        sumF12 += f12(lambda);
    }

    Float normFactorX = 1.0 / sumX;
    Float normFactorF12 = 1.0 / sumF12;

    // CDF 計算
    pstd::vector<Float> cdf(Lambda_max - Lambda_min + 1, 0.0);
    Float cumulativeSum = 0.0;

    for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
        Float probabilityDensity =
            xSpectrum(lambda) * normFactorX *
            f12(lambda) * normFactorF12; // 負の値を無視
        cumulativeSum += probabilityDensity;
        cdf[lambda - Lambda_min] = cumulativeSum;
    }

    // 最後に正規化 (累積分布の最後の値を1にする)
    for (int i = 0; i < cdf.size(); ++i) {
        cdf[i] /= cumulativeSum;
    }

    // サンプリング部分 (u に基づく波長の選択)
    for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
        if (u <= cdf[lambda - Lambda_min]) {
            return lambda;
        }
    }

    // 万が一 u が 1 を超える場合に備えて最大波長を返す
    return Lambda_max;
}

PBRT_CPU_GPU Float SampleLightXyzYWavelengths(Float u) {
    const DenselySampledSpectrum &ySpectrum = Spectra::Y();
    const Spectrum f12 = GetNamedSpectrum("f12");

    // 正規化: xSpectrumとf12の値を正規化
    Float sumX = 0.0, sumF12 = 0.0;
    for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
        sumX += ySpectrum(lambda);
        sumF12 += f12(lambda);
    }

    // xSpectrumとf12を正規化
    Float normFactorX = 1.0 / sumX;
    Float normFactorF12 = 1.0 / sumF12;

    // CDFのための配列
    pstd::vector<Float> cdf(Lambda_max - Lambda_min + 1, 0.0);
    Float cumulativeSum = 0.0;

    // xSpectrumとf12の確率密度を掛け合わせてCDFを計算
    for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
        Float probabilityDensity = ySpectrum(lambda) * normFactorX * f12(lambda) * normFactorF12;
        cumulativeSum += probabilityDensity;
        cdf[lambda - Lambda_min] = cumulativeSum;
    }

        // 最後に正規化 (累積分布の最後の値を1にする)
    for (int i = 0; i < cdf.size(); ++i) {
        cdf[i] /= cumulativeSum;
    }

    // 逆変換サンプリング: 累積分布関数を基にlambdaを決定
    for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
        if (u <= cdf[lambda - Lambda_min]) {
            return lambda;
        }
    }

    // 万が一、uがCDFを超えた場合に備えて、最大のlambdaを返す
    return Lambda_max;
}

PBRT_CPU_GPU Float SampleLightXyzZWavelengths(Float u) {
    const DenselySampledSpectrum &zSpectrum = Spectra::Z();
    const Spectrum f12 = GetNamedSpectrum("f12");

    // 正規化: xSpectrumとf12の値を正規化
    Float sumX = 0.0, sumF12 = 0.0;
    for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
        sumX += zSpectrum(lambda);
        sumF12 += f12(lambda);
    }

    // xSpectrumとf12を正規化
    Float normFactorX = 1.0 / sumX;
    Float normFactorF12 = 1.0 / sumF12;

    // CDFのための配列
    pstd::vector<Float> cdf(Lambda_max - Lambda_min + 1, 0.0);
    Float cumulativeSum = 0.0;

    // xSpectrumとf12の確率密度を掛け合わせてCDFを計算
    for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
        Float probabilityDensity = zSpectrum(lambda) * normFactorX * f12(lambda) * normFactorF12;
        cumulativeSum += probabilityDensity;
        cdf[lambda - Lambda_min] = cumulativeSum;
    }

        // 最後に正規化 (累積分布の最後の値を1にする)
    for (int i = 0; i < cdf.size(); ++i) {
        cdf[i] /= cumulativeSum;
    }

    // 逆変換サンプリング: 累積分布関数を基にlambdaを決定
    for (int lambda = Lambda_min; lambda <= Lambda_max; ++lambda) {
        if (u <= cdf[lambda - Lambda_min]) {
            return lambda;
        }
    }

    // 万が一、uがCDFを超えた場合に備えて、最大のlambdaを返す
    return Lambda_max;
}

}