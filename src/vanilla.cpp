// vanilla.cpp

#include "vanilla.h"

Vanilla::Vanilla(double expiry_,
                 const PayOffBridge& the_payoff_)
    : expiry(expiry_), the_payoff(the_payoff_)
{
}

double Vanilla::option_payoff(double spot) const
{
    return the_payoff(spot);
}

double Vanilla::get_expiry() const
{
    return expiry;
}

Vanilla* Vanilla::clone() const
{
    return new Vanilla(*this);
}