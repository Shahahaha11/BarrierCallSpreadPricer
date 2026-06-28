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
#include <vector>


int main() 
{
    int is_bull = 1; 
    double expiry = 0.5;
    double strike1 = 105.0;
    double strike2 = 120.0;
    double spot = 110.0;
    double vol = 0.23;
    double r = 0.05;
    double d = 0.0;
    int number_of_paths = 100000;
    int number_of_dates = 126;
    int is_double_barrier = 0;
    int is_knock_out = 1;
    double barrier1 = 90.0;
    int barrier_direction = 0;
    double barrier2 = 0.0;
    double tolerance = 0.002;
    int ratio = 12;


    PayOffCallRatioSpread the_payoff2(strike1, strike2, is_bull, ratio);

    ParametersConstant vol_param(vol);
    ParametersConstant r_param(r);
    ParametersConstant d_param(d);

    MJArray look_at_times(number_of_dates);

    for (int i = 0; i < number_of_dates; i++)
        look_at_times[i] = (i + 1.0) * expiry / number_of_dates;

    PathDependentBarrier the_option =
        is_double_barrier
    ? PathDependentBarrier(look_at_times, expiry, the_payoff2,barrier1, barrier2, is_knock_out)
    : PathDependentBarrier(look_at_times, expiry, the_payoff2, barrier1, is_knock_out, barrier_direction);

    // StatisticsMean gathererA;
    // ConvergenceTable gatherer2A(gathererA);
    StatisticsMean gathererA;
    StatisticsMeanSE gathererB(gathererA, tolerance);

    RandomParkMiller generator1(number_of_dates);

    ExoticBSEngineWStop the_engine1(the_option, r_param, d_param, vol_param, generator1, spot);
    the_engine1.do_simulation(gathererB, number_of_paths);

    std::vector<std::vector<double>> results1 = gathererB.get_results_so_far();
    std::cout << results1.back()[0] << "\n";
    return 0;
    
}
