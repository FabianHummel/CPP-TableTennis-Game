//
// Created by Fabian Hummel on 15.02.26.
//

#include "onstart.h"

OnStart::OnStart(const std::function<void()>& on_start) : on_start_cb(on_start)
{
}

void OnStart::on_start()
{
    this->on_start_cb();
}