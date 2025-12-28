#include <iostream>
#include "include/european_option.hpp"
#include "include/black_and_scholes_pricer.hpp"
#include "include/monte_carlo_pricer.hpp"

int main() {
    EuropeanOption call(
        OptionType::Call,
        100.0, 100.0, 0.05, 0.2, 1.0
    );

    BlackAndScholesPricer bs;
    MonteCarloPricer mc(100000);

    std::cout << "BS Price: " << bs.price(call) << "\n";
    std::cout << "MC Price: " << mc.price(call) << "\n";
}
