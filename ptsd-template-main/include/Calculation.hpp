#ifndef CALCULATION_HPP
#define CALCULATION_HPP

#include "pch.hpp"
#include <random>

class Calculation {
public:
    static int CalcuAttack(glm::vec2 baseDmg, int CriticalRate) {
        // 初始化隨機數生成器
        std::random_device rd;                   // 真實隨機數生成器
        std::mt19937 engine(rd());               // Mersenne Twister 引擎
        std::uniform_int_distribution<int> Critical(0, 100);  // 生成 0~3 之間的隨機索引
        std::uniform_int_distribution<int> Dmg(baseDmg[0], baseDmg[1]);
        int finalDmg = Dmg(engine);
        if (Critical(engine) < CriticalRate) {
            finalDmg *= 3;
        }
        return finalDmg;
    }

    static int CalcuDmg(int damage, int defense, int physicalresistance) {
        int finalDmg = (damage - defense / 4) * (damage / (damage + defense));
        finalDmg = finalDmg * (100 - physicalresistance) / 100;
        return glm::max(1, finalDmg);
    }
};

#endif