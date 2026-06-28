#include <cmath>
#include "exotic_bs_engine_w_stop.h"

void ExoticBSEngineWStop::get_one_path(MJArray &spot_values)
{
    the_generator->get_gaussians(variates);

    double current_log_spot = log_spot;

    for (unsigned long j = 0; j < number_of_times; j++)
    {
        current_log_spot += drifts[j];
        current_log_spot += standard_deviations[j] * variates[j];
        spot_values[j] = exp(current_log_spot);
    }

    return;
}

ExoticBSEngineWStop::ExoticBSEngineWStop(const Wrapper<PathDependent> &the_product_,
                                         const Parameters &r_,
                                         const Parameters &d_,
                                         const Parameters &vol_,
                                         const Wrapper<RandomBase> &the_generator_,
                                         double spot_)
    : ExoticEngine(the_product_, r_),
      the_generator(the_generator_)
{
    MJArray times(the_product_->get_look_at_times());
    number_of_times = times.size();

    the_generator->reset_dimensionality(number_of_times);

    drifts.resize(number_of_times);
    standard_deviations.resize(number_of_times);

    double variance = vol_.get_integral_square(0, times[0]);

    drifts[0] = r_.get_integral(0.0, times[0]) - d_.get_integral(0.0, times[0]) - 0.5 * variance;
    standard_deviations[0] = sqrt(variance);

    for (unsigned long j = 1; j < number_of_times; ++j)
    {
        double this_variance = vol_.get_integral_square(times[j - 1], times[j]);
        drifts[j] = r_.get_integral(times[j - 1], times[j]) - d_.get_integral(times[j - 1], times[j]) - 0.5 * this_variance;
        standard_deviations[j] = sqrt(this_variance);
    }

    log_spot = log(spot_);
    variates.resize(number_of_times);
}

void ExoticBSEngineWStop::do_simulation(StatisticsMC &the_gatherer, unsigned long number_of_paths)
{
    MJArray spot_values(number_of_times);
    double this_payoff;

    for (unsigned long i = 0; i < number_of_paths; ++i)
    {
        get_one_path(spot_values);
        this_payoff = do_one_path(spot_values);
        the_gatherer.dump_one_result(this_payoff);

        if (the_gatherer.has_converged())
            break;
    }

    return;
}