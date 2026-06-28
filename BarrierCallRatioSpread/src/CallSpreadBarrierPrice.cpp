#include <Rcpp.h>
#include <iostream>
#include "park_miller.h"
#include "statistics_mc.h"
#include "convergence_table.h"
#include "antithetic.h"
#include "payoff_call_spread.h"
#include "payoff_call_ratio_spread.h"
#include "path_dependent_barrier.h"
#include "exotic_bs_engine.h"
#include "statistics_mse.h"
#include "exotic_bs_engine_w_stop.h"

using namespace std;
using namespace Rcpp;
//[[Rcpp::export]]
double CallRatioSpreadBarrier
(
        int is_bull, double expiry, double strike1, double strike2, double spot, double vol,
        double r, double d, int number_of_paths, int number_of_dates, int is_double_barrier,
        int is_knock_out, double barrier1, int barrier_direction,  double barrier2, double tolerance,
        int ratio
)
// all you need to do is have a three leg version of PathDependentOption
// or make a portfolio class that will hold something as common as a option type. 
{

    PayOffCallSpread the_payoff1(strike1, strike2, is_bull);
// watching the above line work in this program, I would like to make 
// another parallel derived class named PayOffCallRatioSpread
// NEW BELOW 
    PayOffCallRatioSpread the_payoff2(strike1, strike2, is_bull, ratio);

    ParametersConstant vol_param(vol);
    ParametersConstant r_param(r);
    ParametersConstant d_param(d);

    MJArray look_at_times(number_of_dates);

    for (int i = 0; i < number_of_dates; i++)
        look_at_times[i] = (i + 1.0) * expiry / number_of_dates;

    PathDependentBarrier the_option =
        is_double_barrier
    ? PathDependentBarrier(look_at_times, expiry, the_payoff1,barrier1, barrier2, is_double_barrier, is_knock_out)
    : PathDependentBarrier(look_at_times, expiry, the_payoff1, barrier1, is_double_barrier, is_knock_out, barrier_direction);

    // StatisticsMean gathererA;
    // ConvergenceTable gatherer2A(gathererA);
    StatisticsMean gathererA;
    StatisticsMeanSE gathererB(gathererA, tolerance);

    RandomParkMiller generator1(number_of_dates);

    ExoticBSEngineWStop the_engine1(the_option, r_param, d_param, vol_param, generator1, spot);
    the_engine1.do_simulation(gathererB, number_of_paths);

    vector<vector<double>> results1 = gathererB.get_results_so_far();

    return results1.back()[0];
    
}
