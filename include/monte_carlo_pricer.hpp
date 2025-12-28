
#ifndef MONTE_CARLO_PRICER_HPP
#define MONTE_CARLO_PRICER_HPP

#include "pricer.hpp"
#include <random>

class MonteCarloPricer {
public:
    MonteCarloPricer(int num_sims, int num_steps = 1)
        : num_sims_(num_sims), num_steps_(num_steps) {}

    double price(const Option& option) const;

private:
    int num_sims_;
    int num_steps_; // utilisé pour les options path-dépendantes
};

#endif