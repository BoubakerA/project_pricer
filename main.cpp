#include <iostream>
#include "include/types.hpp"
#include "include/european_option.hpp"
#include "include/asian_option.hpp"
#include "include/barrier_option.hpp"
#include "include/digital_option.hpp"
#include "include/black_and_scholes_pricer.hpp"
#include "include/monte_carlo_pricer.hpp"

int main() {
    EuropeanOption call(
        OptionType::Call,
        100.0, 100.0, 0.05, 0.2, 1.0
    );
    AsianOption asianCall(
        OptionType::Call,
        100.0, 100.0, 0.05, 0.2, 1.0);

    BarrierOption barrier(
    OptionType::Call,
    100.0,  100.0, 0.05, 0.2, 1.0, 130.0, true);

    DigitalOption digitalCall(
        OptionType::Call, 100.0, 100.0, 0.05, 0.2, 1.0, 10.0);

    MonteCarloPricer mc(100000);
    BlackAndScholesPricer bs;
    
    std::cout << "BS Price: " << bs.price(call) << "\n";
    std::cout << "MC Price: " << mc.price(call) << "\n";
    std::cout << "Asian MC Price: " << mc.price(asianCall) << "\n";
    std::cout << "Barrier MC Price: " << mc.price(barrier) << "\n";
    std::cout << "Digital MC Price: " << mc.price(digitalCall) << "\n";
}
