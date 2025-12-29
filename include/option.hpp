// option.hpp
#ifndef OPTION_HPP
#define OPTION_HPP

#include <vector>
#include <stdexcept>
#include "types.hpp"  


class Option {
protected:
    double S_;   // spot
    double K_;   // strike
    double r_;   // rate
    double v_;   // volatility
    double T_;   // maturity

public:
    Option(double S, double K, double r, double v, double T)
        : S_(S), K_(K), r_(r), v_(v), T_(T) {}

    virtual ~Option() = default;

    // Terminal payoff 
    virtual double payoff(double ST) const {
        throw std::logic_error("Terminal payoff not implemented");
    }

    // Path-dependent payoff 
    virtual double payoff(const std::vector<double>& path) const {
        throw std::logic_error("Path payoff not implemented");
    }

    virtual bool isPathDependent() const { return false; }

    virtual OptionType type() const { throw std::logic_error("type() not implemented"); }

    
    double S() const { return S_; }
    double K() const { return K_; }
    double r() const { return r_; }
    double v() const { return v_; }
    double T() const { return T_; }
};

#endif
