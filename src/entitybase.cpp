//
// Created by Fabian Hummel on 17.04.22.
//

#include <cstdio>
#include <typeinfo>
#include "entitybase.h"

EntityBase::EntityBase() : renderX(0), renderY(0) {
//    EntityBase(0, 0);
}

EntityBase::EntityBase(int renderX, int renderY) {
    this->renderX = renderX;
    this->renderY = renderY;
}

EntityBase::~EntityBase() {
    printf("Killed Entity: ", (typeid(this).name()), "\n");
}

int EntityBase::getRenderX() const {
    return this->renderX;
}

int EntityBase::getRenderY() const {
    return this->renderY;
}

void EntityBase::setRenderX(int v) {
    this->renderX = v;
}

void EntityBase::setRenderY(int v) {
    this->renderY = v;
}

void EntityBase::moveByX(int v) {
    this->renderX += v;
}

void EntityBase::moveByY(int v) {
    this->renderY += v;
}