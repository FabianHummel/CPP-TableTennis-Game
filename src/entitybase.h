//
// Created by Fabian Hummel on 17.04.22.
//

#pragma once

class EntityBase {
public:
    int renderX;
    int renderY;

    EntityBase(int renderX, int renderY);
    EntityBase();
    ~EntityBase();

    int getRenderX() const;
    int getRenderY() const;

    void setRenderX(int v);
    void setRenderY(int v);

    void moveByX(int v);
    void moveByY(int v);
};