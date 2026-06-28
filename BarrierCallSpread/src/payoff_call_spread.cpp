#include "payoff_call_spread.h"
#include "minmax.h"

PayOffCallSpread::PayOffCallSpread(double strikeA, double strikeB, int is_bull_)
: strike1(strikeA), strike2(strikeB), is_bull(is_bull_)
{
}

// assuming strike1 is the lower strike and strike2 is the higher strike
double PayOffCallSpread::operator()(double spot) const{
    double bull = max(spot - strike1, 0.0) - max(spot - strike2, 0.0);
    return (is_bull) ? bull : (-bull);
}

PayOff* PayOffCallSpread::clone() const{
    return new PayOffCallSpread(*this);
}


