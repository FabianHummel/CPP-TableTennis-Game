//
// Created by Fabian Hummel on 15.02.26.
//

#ifndef TABLETENNIS_ERROR_H
#define TABLETENNIS_ERROR_H

#include "../managers/animationmanager.h"

class Error : public Component
{
private:
    constexpr static double FADEOUT_DURATION = 0.3;
    constexpr static double FADEIN_DURATION = 0.3;

    double close_time;
    double elapsed_time{0};
    AnimationInstance* fadeout{nullptr};

public:
    explicit Error(double close_time);

    void on_start() override;
    void on_update(double delta_time) override;
};


#endif //TABLETENNIS_ERROR_H