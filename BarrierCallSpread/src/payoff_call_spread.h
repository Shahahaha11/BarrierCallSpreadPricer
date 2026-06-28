#ifndef PAYOFF_CALL_SPREAD
#define PAYOFF_CALL_SPREAD
#include "payoff4.h"


class PayOffCallSpread : public PayOff {
public :
    PayOffCallSpread(double strike1, double strike2, int is_bull);

    virtual double operator()(double spot) const;
    virtual ~PayOffCallSpread() {}
    virtual PayOff *clone() const;

private :
double strike1;
double strike2;
int is_bull;
};


#endif

