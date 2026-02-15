//
// Created by Fabian Hummel on 15.02.26.
//

#ifndef TABLETENNIS_ONSTART_H
#define TABLETENNIS_ONSTART_H
#include "../componentsystem.h"


class OnStart : public Component {

private:
    std::function<void()> onStartCb;

public:
    explicit OnStart(const std::function<void()> &onStart);

    void onStart() override;
};


#endif //TABLETENNIS_ONSTART_H