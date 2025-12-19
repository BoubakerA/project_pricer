// monte_carlo_pricer.hpp
#ifndef MONTE_CARLO_PRICER_HPP
#define MONTE_CARLO_PRICER_HPP

#include "pricer.hpp"
#include <random>

class MonteCarloPricer : public Pricer {
private:
    int num_sims_;

public:
    explicit MonteCarloPricer(int num_sims)
        : num_sims_(num_sims) {}

    double price(const Option& option) const override;
};

#endif
