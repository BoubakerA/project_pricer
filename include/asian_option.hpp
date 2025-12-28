#ifndef ASIAN_OPTION_HPP
#define ASIAN_OPTION_HPP

#include "option.hpp"
#include "types.hpp"
#include <vector>
#include <numeric>


class AsianOption : public Option {
public:
    AsianOption(
        OptionType type,
        double S,
        double K,
        double r,
        double v,
        double T
    )
        : Option(S, K, r, v, T), type_(type) {}

    bool isPathDependent() const override { return true; }

    double payoff(const std::vector<double>& path) const override {
        double avg =
            std::accumulate(path.begin(), path.end(), 0.0) / path.size();

        if (type_ == OptionType::Call)
            return std::max(avg - K_, 0.0);
        else
            return std::max(K_ - avg, 0.0);
    }

private:
    OptionType type_;
};

#endif