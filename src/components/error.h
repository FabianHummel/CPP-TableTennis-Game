//
// Created by Fabian Hummel on 15.02.26.
//

#ifndef TABLETENNIS_ERROR_H
#define TABLETENNIS_ERROR_H

#include "../animationmanager.h"

class Error : public Component {
private:
    constexpr static double FADEOUT_DURATION = 0.3;
    constexpr static double FADEIN_DURATION = 0.3;

    double closeTime;
    double elapsedTime{0};
    AnimationInstance *fadeout{nullptr};

public:
    explicit Error(double closeTime);

    void onStart() override;
    void onUpdate(double deltaTime) override;
};


#endif //TABLETENNIS_ERROR_H