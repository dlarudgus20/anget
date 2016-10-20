#pragma once

#include <initializer_list>
#include <string>
#include <vector>
#include "Object.h"

class Map
{
public:
    Map(std::vector<Object::sptr> objMap, int width, int height);
    Map(const std::string& strMap, int width, int height);
    Map(const std::initializer_list<std::string>& vtStrMap);

    int getWidth() const { return width_; }
    int getHeight() const { return height_; }

    bool isValid(int x, int y) const;

    void draw(int mx, int my, int sx = -1, int sy = -1, int w = -1, int h = -1) const;

    void place(const Object::sptr& obj, int x, int y);
    Object::sptr displace(int x, int y);
    Object::sptr& get(int x, int y);

private:
    std::vector<Object::sptr> objMap_;
    int width_;
    int height_;
};

