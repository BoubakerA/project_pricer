#include "types.hpp"
#include <cmath>
#include "black_and_scholes_pricer.hpp"
#include <stdexcept>

double BlackAndScholesPricer::norm_cdf(double x) const {
    return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
}

double BlackAndScholesPricer::d_j(int j, const Option& opt) const {
    double S = opt.S();
    double K = opt.K();
    double r = opt.r();
    double v = opt.v();
    double T = opt.T();

    if (j == 1)
        return (std::log(S / K) + (r + 0.5 * v * v) * T) / (v * std::sqrt(T));
    else
        return (std::log(S / K) + (r - 0.5 * v * v) * T) / (v * std::sqrt(T));
}

double BlackAndScholesPricer::price(const Option& option) const {
    if (option.isPathDependent()) {
        throw std::invalid_argument(
            "Option path-dépendante non supportée par Black-Scholes"
        );
    }

    double S = option.S();
    double K = option.K();
    double r = option.r();
    double v = option.v();
    double T = option.T();

    double d1 = (std::log(S / K) + (r + 0.5 * v*v) * T) / (v * std::sqrt(T));
    double d2 = d1 - v * std::sqrt(T);

    if (option.type() == OptionType::Call)
        return S * norm_cdf(d1) - K * std::exp(-r*T) * norm_cdf(d2);
    else // Put
        return K * std::exp(-r*T) * norm_cdf(-d2) - S * norm_cdf(-d1);
}
