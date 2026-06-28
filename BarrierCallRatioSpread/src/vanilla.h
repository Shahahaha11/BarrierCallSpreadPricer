// vanilla.h

#ifndef VANILLA_H
#define VANILLA_H

#include "payoff_bridge.h"

class Vanilla
{
public:
    Vanilla(double expiry_,
            const PayOffBridge& the_payoff_);

    double option_payoff(double spot) const;
    double get_expiry() const;

    virtual ~Vanilla() {}
    Vanilla* clone() const;
private:
    double expiry;
    PayOffBridge the_payoff;
};

#endif