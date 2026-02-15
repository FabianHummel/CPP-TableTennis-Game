//
// Created by Fabian Hummel on 15.02.26.
//

#include "onstart.h"

OnStart::OnStart(const std::function<void()> &onStart) : onStartCb(onStart)
{
}

void OnStart::onStart()
{
    this->onStartCb();
}
