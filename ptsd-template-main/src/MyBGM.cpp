#include "MyBGM.hpp"

MyBGM::MyBGM(const std::string& BGMPath) {
    this->m_BGM = std::make_unique<Util::BGM>(BGMPath);
}

void MyBGM::SetVolume(int volume) {
    m_BGM->SetVolume(volume);
}

void MyBGM::LoadMedia(const std::string &path) {
    m_BGM->LoadMedia(path);
}

void MyBGM::Play(int loop = -1) {
    m_BGM->Play(loop);
}