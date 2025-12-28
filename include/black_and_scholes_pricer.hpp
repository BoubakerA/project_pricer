#ifndef BLACK_AND_SCHOLES_PRICER_HPP
#define BLACK_AND_SCHOLES_PRICER_HPP

#include "pricer.hpp"
#include "european_option.hpp"
#include <cmath>
#include <stdexcept>

class BlackAndScholesPricer : public Pricer {
private:
    double norm_cdf(double x) const;
    double d_j(int j, const Option& opt) const;

public:
    double price(const Option& option) const override;
};

#endif
