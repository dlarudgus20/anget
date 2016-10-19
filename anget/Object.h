#pragma once

#include <string>
#include <memory>

class Map;
struct Effect;

class Object : public std::enable_shared_from_this<Object>
{
public:
    using sptr = std::shared_ptr<Object>;

    explicit Object(char ch, std::string str = "Object");

    char getChar() const { return objch_; }
    void setChar(char ch) { objch_ = ch; }

    Map* getMap() const { return map_; }
    void setMap(Map* map) { map_ = map; }

    int getX() const { return x_; }
    void setX(int x) { x_ = x; }
    int getY() const { return y_; }
    void setY(int y) { y_ = y; }

    int printinfo(int x, int y);

    bool move(int dx, int dy);

    bool isDestroyable() const { return destroyable_; }
    int getMaxHp() const { return maxHp_; }
    int getHp() const { return hp_; }
    int getMaxMp() const { return mp_; }
    int getMp() const { return maxMp_; }

    bool getHit(Object* from, int damage);

    bool isAttackable() const { return attackable_; }
    int getAtk() const { return atk_; }

    bool giveHit(Object* to);

    bool isPickable() const { return pickable_; }

    virtual bool picked(Object* by, Effect& eff);

    bool isMoneyEarnable() const { return moneyEarnable_; }
    int getMoney() const { return money_; }

    bool isExpEarnable() const { return expEarnable_; }
    int getMaxExp() const { return maxExp_; }
    int getExp() const { return exp_; }

protected:
    virtual bool collapse(Object* other);

private:
    std::string name_;

    char objch_;
    Map* map_;
    int x_;
    int y_;

protected:
    bool destroyable_ = false;
    int maxHp_ = 1;
    int hp_ = 1;
    int maxMp_ = 0;
    int mp_ = 0;

    bool attackable_ = false;
    int atk_ = 0;

    bool pickable_ = false;

    bool moneyEarnable_ = false;
    int money_ = 0;

    bool expEarnable_ = false;
    int maxExp_ = 1;
    int exp_ = 0;
};
