#include "path_dependent_barrier.h"

PathDependentBarrier::PathDependentBarrier(const MJArray &look_at_times_,
    double delivery_time_,
    const PayOffBridge &the_payoff_,
    double barrierA, double barrierB , int is_double_barrier, int is_knock_out_)
    : PathDependent(look_at_times_),
    delivery_time(delivery_time_),
    the_payoff(the_payoff_),
    number_of_times(look_at_times_.size()),
    barrier1(barrierA),
    barrier2(barrierB)
{
is_double = is_double_barrier;
is_knock_out = is_knock_out_ ;
}

PathDependentBarrier::PathDependentBarrier(const MJArray &look_at_times_,
    double delivery_time_,
    const PayOffBridge &the_payoff_,
    double barrierA, int is_double_barrier, int is_knock_out_)
    : PathDependent(look_at_times_),
    delivery_time(delivery_time_),
    the_payoff(the_payoff_),
    number_of_times(look_at_times_.size()),
    barrier1(barrierA),
    barrier2(0.0)
{
is_double = is_double_barrier;
is_knock_out = is_knock_out_ ;
}

    
unsigned long PathDependentBarrier::max_number_of_cash_flows() const
{
    return 1UL;
}

MJArray PathDependentBarrier::possible_cash_flow_times() const
{
    MJArray tmp(1UL);
    tmp[0] = delivery_time;
    return tmp;
}

unsigned long PathDependentBarrier::cash_flows(const MJArray &spot_values, std::vector<CashFlow> &generated_flows) const
{
    double final_spot = spot_values[spot_values.size() -1];

    int hit;

    if (is_double){
        hit = spot_values.min() <= barrier1 || spot_values.max() >= barrier2;
    }
    else {
        hit = spot_values.max() >= barrier1;
    }
    generated_flows[0].time_index = 0UL;
    
    double payoff = the_payoff(final_spot);
    if (is_knock_out){
        generated_flows[0].amount = (hit) ? 0.0 : payoff;
    } else
    {
        generated_flows[0].amount = (hit) ? payoff : 0.0;
    }
    return 1UL;
}

PathDependent* PathDependentBarrier::clone() const
{
    return new PathDependentBarrier(*this);
}
