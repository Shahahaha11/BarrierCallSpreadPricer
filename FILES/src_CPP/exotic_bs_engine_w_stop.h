#ifndef EXOTIC_BS_ENGINE_W_STOP_H
#define EXOTIC_BS_ENGINE_W_STOP_H

#include "exotic_engine.h"
#include "random2.h"

class ExoticBSEngineWStop : public ExoticEngine
{
public:
    ExoticBSEngineWStop(const Wrapper<PathDependent> &the_product_,
                        const Parameters &r_,
                        const Parameters &d_,
                        const Parameters &vol_,
                        const Wrapper<RandomBase> &the_generator_,
                        double spot_);

    virtual void get_one_path(MJArray &spot_values);
    virtual void do_simulation(StatisticsMC &the_gatherer, unsigned long number_of_paths);

    virtual ~ExoticBSEngineWStop() {}

private:
    Wrapper<RandomBase> the_generator;
    MJArray drifts;
    MJArray standard_deviations;
    double log_spot;
    unsigned long number_of_times;
    MJArray variates;
};

#endif