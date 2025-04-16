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

    static float Round4(float x) {
        return glm::round(x * 1e4f) / 1e4f;
    }
    
    static glm::vec2 RoundVec2(glm::vec2 v) {
        return { Round4(v.x), Round4(v.y) };
    }
    
    static glm::vec2 AddPosition(glm::vec2 pos1, glm::vec2 pos2) {
        return RoundVec2(pos1 + pos2);
    }
    
    static glm::vec2 SubPosition(glm::vec2 pos1, glm::vec2 pos2) {
        return RoundVec2(pos1 - pos2);
    }
    
    static glm::vec2 MulPosition(glm::vec2 pos1, float number) {
        return RoundVec2(pos1 * number);
    }
    
    static glm::vec2 ModPosition(glm::vec2 pos1, int number) {
        return {
            Round4(fmod(pos1.x, static_cast<float>(number))),
            Round4(fmod(pos1.y, static_cast<float>(number)))
        };
    }

    static glm::vec2 GetDirection(glm::vec2 diff) {
        int dxRaw = static_cast<int>(diff.x);
        int dyRaw = static_cast<int>(diff.y);
    
        int dx = (std::abs(dxRaw) > std::abs(dyRaw)) ? ((dxRaw > 0) ? 1 : -1) : 0;
        int dy = (std::abs(dyRaw) > std::abs(dxRaw)) ? ((dyRaw > 0) ? 1 : -1) : 0;
    
        return glm::vec2(dx, dy);
    }    
};

#endif