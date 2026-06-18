#ifndef STATISTICS_MEAN_SE_H
#define STATISTICS_MEAN_SE_H

#include "statistics_mc.h"
#include "wrapper.h"

class StatisticsMeanSE : public StatisticsMC
{
public:
    StatisticsMeanSE(const Wrapper<StatisticsMC>& Inner_, double tolerance_);

    virtual void dump_one_result(double result);
    virtual std::vector<std::vector<double>> get_results_so_far() const;
    virtual StatisticsMC* clone() const;
    virtual void reset();

    double get_standard_error() const;
    double get_confidence_interval_width() const;
    unsigned long get_paths_done() const;
    bool has_converged() const;

private:
    Wrapper<StatisticsMC> Inner;
    double tolerance;
    double running_sum_square;
    unsigned long paths_done;
};

#endif