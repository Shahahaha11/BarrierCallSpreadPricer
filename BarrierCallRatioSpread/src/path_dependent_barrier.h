#ifndef PATH_DEPENDENT_BARRIER_H
#define PATH_DEPENDENT_BARRIER_H
#include "path_dependent.h"
#include "payoff_bridge.h"

class PathDependentBarrier : public PathDependent {

public :
PathDependentBarrier(const MJArray &look_at_times_,
    double delivery_time,
    const PayOffBridge &the_payoff_,
    double barrierA, double barrierB ,
    int is_double_barrier, int is_knock_out);

PathDependentBarrier(const MJArray &look_at_times_,
    double delivery_time,
    const PayOffBridge &the_payoff_, double barrierA, 
    int is_double_barrier, int is_knock_out,
    int barrier_direction);
    
    virtual unsigned long max_number_of_cash_flows() const;
    virtual MJArray possible_cash_flow_times() const;
    virtual unsigned long cash_flows(const MJArray &spot_values,
    std::vector<CashFlow> &generated_flows) const;
    virtual ~PathDependentBarrier() {}
    virtual PathDependent *clone() const;
        
private :
    double delivery_time;
    PayOffBridge the_payoff;
    unsigned long number_of_times;
    double barrier1;
    double barrier2;
    int is_double;
    int is_knock_out;
    int barrier_direction;
};

#endif
