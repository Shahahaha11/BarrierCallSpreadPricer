#include "path_dependent_geometric_asian.h"
#include <cmath>
PathDependentGeometricAsian::PathDependentGeometricAsian(const MJArray &look_at_times_,
                                       double delivery_time_,
                                       const PayOffBridge &the_payoff_)
    : PathDependent(look_at_times_),
      delivery_time(delivery_time_),
      the_payoff(the_payoff_),
      number_of_times(look_at_times_.size())
{
}

// definitions of methods
unsigned long PathDependentGeometricAsian::max_number_of_cash_flows() const
{
    return 1UL; // 1UL stands for 'one unsigned long'
}

MJArray PathDependentGeometricAsian::possible_cash_flow_times() const
{
    MJArray tmp(1UL);
    tmp[0] = delivery_time;
    return tmp;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ! this method is (partially) responsible for determining payments of the option!!
// is uses the object of the PayOffCall subclass (thePayOff), which previously took
// as argument the final price of underlying. Since we are pricing arithmetic asian call,
// this time it takes mean spot price of underlying.
unsigned long PathDependentGeometricAsian::cash_flows(const MJArray &spot_values,
                                             std::vector<CashFlow> &generated_flows) const
{
    // idea one
    // just replace the spot prices with logarithms.
    MJArray log_values = spot_values;
    for (unsigned  long i =0 ; i < log_values.size(); i++){
        log_values[i] = log(spot_values[i]);
    }
    double sum = log_values.sum();
    double mean = sum / number_of_times;


    generated_flows[0].time_index = 0UL;
    generated_flows[0].amount = the_payoff(exp(mean));

    // the_payoff
    // There are three posibilities : is this created here? is this being fed here? no to both 
    // is it a member of this classs , yes

    return 1UL;
}

// standard method for cloning (making a copy of this object)
PathDependent *PathDependentGeometricAsian::clone() const
{
    return new PathDependentGeometricAsian(*this);
}
