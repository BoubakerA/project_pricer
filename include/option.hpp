// option.hpp
#ifndef OPTION_HPP
#define OPTION_HPP

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

    virtual double payoff(double ST) const = 0;

    double S() const { return S_; }
    double K() const { return K_; }
    double r() const { return r_; }
    double v() const { return v_; }
    double T() const { return T_; }
};

#endif
