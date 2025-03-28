#ifndef MYBGM_HPP
#define MYBGM_HPP

#include "pch.hpp"
#include "Util/GameObject.hpp"
#include "Util/BGM.hpp"

class MyBGM : public Util::GameObject {
public:
    explicit MyBGM(const std::string& BGMPath);

    void SetVolume(int volume);

    void LoadMedia(const std::string &path);

    void Play(int loop);
private:
    std::unique_ptr<Util::BGM> m_BGM;
};

#endif
