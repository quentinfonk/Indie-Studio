/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** End
*/

#include "End.hpp"
#include "PowerUp.hpp"

End::End()
{
}

End::~End()
{
}

float convertSizes(float x, int size)
{
    x = (x * 100) / size;
    x = (x * size) / 100;
    return (x);
}

GamePhase End::launch()
{
    this->_tbackground = RAYLIB::LoadTexture("assets/texture/EndBackground.png");
    this->_tRocket = RAYLIB::LoadTexture("assets/texture/victory.png");
    this->_tReturn = rl::Text("Menu", 9, 88, 29, RAYLIB::BLACK);
    this->_bReturn = Button("assets/texture/button.png", 3, 85, 21.4, 10);
    this->_tVictory = RAYLIB::LoadTexture("assets/texture/victory-title-sm.png");
    this->_bAgain = Button("assets/texture/button.png", 76, 85, 21.4, 10);
    this->_tAgain = rl::Text("Quitter", 82, 88, 29, RAYLIB::BLACK);
    return (this->restart());
}

GamePhase End::restart()
{
    return (endPhase(EndPhase));
}

GamePhase End::endPhase(GamePhase gamePhase)
{
    static auto time = TIMENOW;
    static int a = 100;
    static auto e = TIMENOW;
    static int i = 0;
    static int u = 0;

    if (this->_bReturn.isClicked()) {
        gamePhase = RestartPhase;
    }
    if (this->_bAgain.isClicked())
        gamePhase = QuitPhase;
    if (CHRONO(time) >= 1000 && i <= 1)
        i++;
    if (i != 0 && i < 2000)
        if (CHRONO(e) >= a) {
            if (a > 1)
                a--;
            e = TIMENOW;
            i++;
        }
    RAYLIB::DrawTextureEx(this->_tbackground, {0, 0}, 0, ((float)RAYLIB::GetScreenHeight() / 1820), RAYLIB::WHITE);
    if (i < 2000)
        RAYLIB::DrawTextureEx(this->_tRocket, {600, (float)800-i}, -45, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    if (i >= 800) {
        if (u < 255)
        u++;
       RAYLIB::DrawTexture(this->_tVictory, 400, 250, { 255, 255, 255, (unsigned char)u});
    }
    this->_bAgain.draw();
    this->_tAgain.draw();
    this->_bReturn.draw();
    this->_tReturn.draw();
    return (gamePhase); 
}
