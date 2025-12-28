
#include <cmath>
#include "black_and_scholes_pricer.hpp"

double BlackAndScholesPricer::norm_cdf(double x) const {
    return 0.5 * std::erfc(-x / std::sqrt(2));
}

double BlackAndScholesPricer::d_j(int j, const Option& opt) const {
    double sign = (j == 1) ? 1.0 : -1.0;
    return (std::log(opt.S() / opt.K()) +
           (opt.r() + sign * 0.5 * opt.v() * opt.v()) * opt.T())
           / (opt.v() * std::sqrt(opt.T()));
}

double BlackAndScholesPricer::price(const Option& option) const {
    const EuropeanOption& opt =
        dynamic_cast<const EuropeanOption&>(option);

    if (opt.type() == OptionType::Call) {
        return opt.S() * norm_cdf(d_j(1, opt))
             - opt.K() * std::exp(-opt.r() * opt.T())
             * norm_cdf(d_j(2, opt));
    } else {
        return opt.K() * std::exp(-opt.r() * opt.T())
             * norm_cdf(-d_j(2, opt))
             - opt.S() * norm_cdf(-d_j(1, opt));
    }
}