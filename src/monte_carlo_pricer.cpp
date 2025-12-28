#include "monte_carlo_pricer.hpp"
#include <cmath>
#include <random>
#include <vector>

double MonteCarloPricer::price(const Option& option) const {
    std::mt19937 gen(42);
    std::normal_distribution<> dist(0.0, 1.0);

    double payoff_sum = 0.0;

    if (!option.isPathDependent()) {

        double S_adj = option.S() *
            std::exp((option.r() - 0.5 * option.v() * option.v()) * option.T());

        for (int i = 0; i < num_sims_; ++i) {
            double Z = dist(gen);
            double ST = S_adj *
                std::exp(option.v() * std::sqrt(option.T()) * Z);

            payoff_sum += option.payoff(ST);
        }
    }
    else {
        // ===== Path-dependent option (Asian, Barrier, etc.) =====
        int N = num_steps_;              
        double dt = option.T() / N;

        for (int i = 0; i < num_sims_; ++i) {
            std::vector<double> path;
            path.reserve(N + 1);

            double S = option.S();
            path.push_back(S);

            for (int j = 0; j < N; ++j) {
                double Z = dist(gen);
                S *= std::exp(
                    (option.r() - 0.5 * option.v() * option.v()) * dt
                    + option.v() * std::sqrt(dt) * Z
                );
                path.push_back(S);
            }

            payoff_sum += option.payoff(path);
        }
    }

    return std::exp(-option.r() * option.T())
         * payoff_sum / num_sims_;
}
