
#include "monte_carlo_pricer.hpp"
#include <cmath>

double MonteCarloPricer::price(const Option& option) const {
    std::mt19937 gen(42); // seeding
    std::normal_distribution<> dist(0.0, 1.0); // Represente le Mouvement Brownien 

    // Partie deterministe de la formule du prix à la maturité
    double S_adj = option.S() *
        std::exp((option.r() - 0.5 * option.v() * option.v()) * option.T());

    double payoff_sum = 0.0;

    for (int i = 0; i < num_sims_; ++i) {
        double Z = dist(gen);
        double ST = S_adj *
            std::exp(option.v() * std::sqrt(option.T()) * Z);
        payoff_sum += option.payoff(ST);
    }
    // Actualisation et divsion de payoff_sum sur le nombre de simulations
    return std::exp(-option.r() * option.T())
         * payoff_sum / num_sims_;
}
