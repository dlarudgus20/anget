#include <algorithm>
#include <utility>
#include <stdio.h>
#include <assert.h>
#include "conlib.h"
#include "Map.h"

#include "ObjectFactory.h"

Map::Map(const std::vector<Object::sptr> objMap, int width, int height)
    : objMap_(std::move(objMap)), width_(width), height_(height)
{
    assert(objMap_.size() == width * height);
}

Map::Map(const std::string& strMap, int width, int height)
    : width_(width), height_(height)
{
    assert(strMap.size() == width * height);

    objMap_.resize(strMap.size(), nullptr);
    for (std::size_t i = 0; i < strMap.size(); ++i)
    {
        if (strMap[i] != ' ')
        {
            place(ObjectFactory::fromLetter(strMap[i]), i % width_, i / width_);
        }
    }
}

Map::Map(const std::initializer_list<std::string>& vtStrMap)
{
    height_ = vtStrMap.size();
    width_ = 0;
    for (const auto& str : vtStrMap)
    {
        if (str.size() > static_cast<std::size_t>(width_))
            width_ = str.size();
    }

    std::size_t i = 0;
    objMap_.resize(width_ * height_, nullptr);
    for (const auto& str : vtStrMap)
    {
        for (char ch : str)
        {
            if (ch != ' ')
            {
                place(ObjectFactory::fromLetter(ch), i % width_, i / width_);
            }

            ++i;
        }
    }
}

bool Map::isValid(int x, int y) const
{
    return (0 <= x && x < width_ && 0 <= y && y < height_);
}

void Map::draw(int mx, int my, int sx, int sy, int w, int h) const
{
    static std::vector<char> buf;
    buf.resize(w * h + 1);
    std::fill(buf.begin(), buf.end(), ' ');

    if (sx == -1)
        sx = 0;
    if (sy == -1)
        sy = 0;
    if (w == -1)
        w = width_;
    if (h == -1)
        h = height_;

    std::fill_n(buf.begin(), w, '*');
    std::fill_n(buf.begin() + (h - 1) * w, w, '*');
    for (int oy = 1; oy < h - 1; ++oy)
    {
        buf[oy * w] = '*';
        buf[w - 1 + oy * w] = '*';
    }

    for (int dy = 0; dy < h - 2; ++dy)
    {
        for (int dx = 0; dx < w - 2; ++dx)
        {
            if (mx + dx < 0 || mx + dx >= width_ || my + dy < 0 || my + dy >= height_)
            {
                continue;
            }
            else
            {
                auto ptr = objMap_[(mx + dx) + (my + dy) * width_];
                if (ptr)
                {
                    buf[dx + 1 + (dy + 1) * w] = objMap_[(mx + dx) + (my + dy) * width_]->getChar();
                }
            }
        }
    }

    for (int oy = 0; oy < h; ++oy)
    {
        char tmp = '\0';
        std::swap(buf[(oy + 1) * w], tmp);
        gotoxy(sx, sy + oy);
        printf("%s", &buf[oy * w]);
        buf[(oy + 1) * w] = tmp;
    }
}

void Map::place(const Object::sptr& obj, int x, int y)
{
    assert(0 <= x && x < width_);
    assert(0 <= y && y < height_);

    objMap_[x + y * width_] = obj;
    obj->setMap(this);
    obj->setX(x);
    obj->setY(y);
}

Object::sptr Map::displace(int x, int y)
{
    assert(0 <= x && x < width_);
    assert(0 <= y && y < height_);

    auto ret = std::move(objMap_[x + y * width_]);
    objMap_[x + y * width_] = nullptr;
    return ret;
}

Object::sptr& Map::get(int x, int y)
{
    assert(0 <= x && x < width_);
    assert(0 <= y && y < height_);

    return objMap_[x + y * width_];
}
