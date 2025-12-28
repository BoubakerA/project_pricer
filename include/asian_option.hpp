// european_option.hpp
#ifndef EUROPEAN_OPTION_HPP
#define EUROPEAN_OPTION_HPP

#include "option.hpp"
#include <algorithm>

enum class OptionType { Call, Put };

class AsianOption : public Option {
private:
    OptionType type_;

public:
    AsianOptionOption(
        OptionType type,
        double S, double K, double r, double v, double T
    )
        : Option(S, K, r, v, T), type_(type) {}

        
    double payoff(double ST) const override {
        if (type_ == OptionType::Call)
            return std::max(ST - K_, 0.0);
        else
            return std::max(K_ - ST, 0.0);
    }

    OptionType type() const { return type_; }
};

#endif
