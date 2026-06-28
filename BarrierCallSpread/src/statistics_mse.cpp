#include "statistics_mse.h"
#include <cmath>

StatisticsMeanSE::StatisticsMeanSE(const Wrapper<StatisticsMC>& Inner_, double tolerance_)
    : Inner(Inner_), tolerance(tolerance_)
{
    running_sum_square = 0.0;
    paths_done = 0UL;
}

void StatisticsMeanSE::dump_one_result(double result)
{
    Inner->dump_one_result(result);
    running_sum_square += result * result;
    ++paths_done;
}

std::vector<std::vector<double>> StatisticsMeanSE::get_results_so_far() const
{
    std::vector<std::vector<double>> this_result(Inner->get_results_so_far());

    for (unsigned long i = 0; i < this_result.size(); i++)
    {
        this_result[i].push_back(get_standard_error());
        this_result[i].push_back(get_confidence_interval_width());
        this_result[i].push_back(paths_done);
    }

    return this_result;
}

StatisticsMC* StatisticsMeanSE::clone() const
{
    return new StatisticsMeanSE(*this);
}

void StatisticsMeanSE::reset()
{
    Inner->reset();
    running_sum_square = 0.0;
    paths_done = 0UL;
}

double StatisticsMeanSE::get_standard_error() const
{
    if (paths_done < 2)
        return 0.0;

    std::vector<std::vector<double>> this_result(Inner->get_results_so_far());
    double mean = this_result[0][0];

    double variance = (running_sum_square - paths_done * mean * mean) / (paths_done - 1);

    if (variance < 0.0)
        variance = 0.0;

    return std::sqrt(variance / paths_done);
}

double StatisticsMeanSE::get_confidence_interval_width() const
{
    return 2.576 * get_standard_error();
}

unsigned long StatisticsMeanSE::get_paths_done() const
{
    return paths_done;
}

bool StatisticsMeanSE::has_converged() const
{
    if (paths_done < 2)
        return false;

    return get_confidence_interval_width() <= tolerance;
}