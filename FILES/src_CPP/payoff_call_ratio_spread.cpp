#include "payoff_call_ratio_spread.h"
#include "minmax.h"

PayOffCallRatioSpread::PayOffCallRatioSpread(double strikeA, double strikeB, int is_bull_, int ratio_)
: strike1(strikeA), strike2(strikeB), is_bull(is_bull_), ratio(ratio_)
{
}

// unedited 
// assuming strike1 is the lower strike than strike2.
double PayOffCallRatioSpread::operator()(double spot) const{
    // DESIGN CHOICE (INPUT)
    // int first = ratio/10; // "ratio" is an int. 12 is default. 
    // for bull first digit 1 refers to one long positions, 2 refers to number of short positions.
    int x = ratio % 10;
    return (is_bull) ? 
        max(spot - strike1, 0.0) - x * max(spot - strike2, 0.0) 
        : 
        x * max(spot - strike2, 0.0) - max(spot - strike1, 0.0);
}

PayOff* PayOffCallRatioSpread::clone() const{
    return new PayOffCallRatioSpread(*this);
}


