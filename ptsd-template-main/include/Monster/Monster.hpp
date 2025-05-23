#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "pch.hpp"
#include "Character.hpp"
#include "AnimatedCharacter.hpp"
#include "Util/GameObject.hpp"
#include "ICollidable.hpp"

class ICollidable;
class Player;
class InvisibleWall;
namespace Util {
    class Renderer;
}

class Monster : public Character , public ICollidable {
public:
    enum class State {
        Move,
        MoveMap,
        Stop
    };

    Monster(const std::vector<std::string> &ImagePaths,
        int hp, int mp, glm::vec2 attack, int defense, int hitrate, int dodgerate, std::vector<int> resistance, int gold, int exp, float TrackRange);

    virtual ~Monster() = default;
     
    virtual void Update(std::shared_ptr<Player> &m_Player, std::vector<std::shared_ptr<Character>> AllObjects, std::vector<std::shared_ptr<ICollidable>> AllCollidableObjects, std::vector<std::shared_ptr<InvisibleWall>> m_Invisiblewalls, std::vector<std::shared_ptr<Monster>> m_Monsters) = 0;

    void UpdateHPProgress();

    virtual void TakeDamage(int damage);

    int GetHP() const { return m_HP; }

    int GetMaxHP() const { return m_MaxHP; }

    void SetHP(int hp) { m_HP = hp; }

    int GetMP() const { return m_MP; }

    void SetMP(int mp) { m_MP = mp; }

    void SetChangeImageCD(float cd) { m_ChangeImageCD = cd; }

    float GetChangeImageCD() const { return m_ChangeImageCD; }

    void SetAttackCD(float cd) { m_AttackCD = cd; }

    float GetAttackCD() const { return m_AttackCD; }

    bool IsCollision(const std::shared_ptr<Character> &other, glm::vec2 displacement) override;

    void OnCollision() override {};

    void OffCollision() override {};

    bool IfFocus();

    void ChangeImage(int index) {
        this->SetImage(m_ImagePaths[index]);
    }

    glm::vec2 GetGoalPosition() { return this->goalpos; }

    void SetGoalPosition(glm::vec2 goal) { this->goalpos = goal; }

    glm::vec2 GetPosPosition() { return this->pos; }

    void SetPosPosition(glm::vec2 pos) { this->pos = pos; }

    std::shared_ptr<Util::GameObject> GetHPBox() { return std::static_pointer_cast<Util::GameObject>(m_HPBox); }
    
    std::shared_ptr<Util::GameObject> GetHPBar() { return std::static_pointer_cast<Util::GameObject>(m_HPBar); }
private:
    int m_HP;
    int m_MP;

    int m_MaxHP = m_HP;
    int m_MaxMP = m_MP;

    std::shared_ptr<Character> m_HPBox;
    std::shared_ptr<AnimatedCharacter> m_HPBar;
protected:
    //move
    State state = State::Stop;
    glm::vec2 randomDisplacement;
    glm::vec2 pos;
    glm::vec2 goalpos;
    int grids;
    int goalgrids;
public:
    std::vector<std::string> m_ImagePaths;
    int m_ImageIndex = 0;

    const glm::vec2 m_Attack;
    const int m_Defense;
    const int m_Hitrate;
    const int m_Dodgerate;
    const std::vector<int> m_Resistance; // 火 冰 雷 毒 物理

    const int m_Gold;
    const int m_Exp;

    const float m_TrackRange;
    float m_ChangeImageCD = 0.25f;
    float m_AttackCD = 1.f;
};

#endif //MONSTER_HPP