// monte_carlo_pricer.cpp
#include "monte_carlo_pricer.hpp"
#include <cmath>

double MonteCarloPricer::price(const Option& option) const {
    std::mt19937 gen(42);
    std::normal_distribution<> dist(0.0, 1.0);

    double S_adj = option.S() *
        std::exp((option.r() - 0.5 * option.v() * option.v()) * option.T());

    double payoff_sum = 0.0;

    for (int i = 0; i < num_sims_; ++i) {
        double Z = dist(gen);
        double ST = S_adj *
            std::exp(option.v() * std::sqrt(option.T()) * Z);
        payoff_sum += option.payoff(ST);
    }

    return std::exp(-option.r() * option.T())
         * payoff_sum / num_sims_;
}
