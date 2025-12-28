#ifndef BARRIER_OPTION_HPP
#define BARRIER_OPTION_HPP

#include "types.hpp"
#include "option.hpp"
#include <vector>
#include <algorithm>

class BarrierOption : public Option {
public:
    BarrierOption(
        OptionType type,
        double S,
        double K,
        double r,
        double v,
        double T,
        double barrier,
        bool isUpAndOut = true
    )
        : Option(S, K, r, v, T),
          type_(type),
          barrier_(barrier),
          isUpAndOut_(isUpAndOut) {}

    bool isPathDependent() const override { return true; }

    double payoff(const std::vector<double>& path) const override {
        bool barrierHit = false;

        for (double s : path) {
            if (isUpAndOut_ && s >= barrier_) {
                barrierHit = true;
                break;
            }
            if (!isUpAndOut_ && s <= barrier_) {
                barrierHit = true;
                break;
            }
        }

        // Knock-out
        if (barrierHit)
            return 0.0;

        // Plain vanilla payoff at maturity
        double ST = path.back();

        if (type_ == OptionType::Call)
            return std::max(ST - K_, 0.0);
        else
            return std::max(K_ - ST, 0.0);
    }

private:
    OptionType type_;
    double barrier_;
    bool isUpAndOut_;
};

#endif
