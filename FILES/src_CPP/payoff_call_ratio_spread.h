#ifndef PAYOFF_CALL_RATIO_SPREAD_H
#define PAYOFF_CALL_RATIO_SPREAD_H

#include "payoff4.h"

class PayOffCallRatioSpread : public PayOff {
public :
    PayOffCallRatioSpread(double strike1, double strike2, int is_bull, int ratio);

    virtual double operator()(double spot) const;
    virtual ~PayOffCallRatioSpread() {}
    virtual PayOff *clone() const;

private :
double strike1;
double strike2;
int is_bull;
int ratio;
};


#endif
