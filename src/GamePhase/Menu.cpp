/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-quentin.daville
** File description:
** Menu
*/

#include "Menu.hpp"
#include "Server.hpp"
#include "Game.hpp"
#include "Pause.hpp"
#include "Sound.hpp"

Menu::Menu()
{
}

Menu::~Menu()
{
}

GamePhase Menu::launch()
{
    this->_phase = Menu::MainPhase;

    // MainPhase
    this->_bPlay = Button("assets/texture/play_button.png", 20, 35, 36.3, 10.37);
    this->_bHtp = Button("assets/texture/button.png", 75, 32, 21.4, 10);
    this->_bSettings = Button("assets/texture/button.png", 75, 17, 21.4, 10);
    this->_bWeapon = Button("assets/texture/button.png", 75, 47, 21.4, 10);
    this->_bQuit = Button("assets/texture/button.png", 75, 62, 21.4, 10);
    this->_tQuit = rl::Text("Quit", 82, 65, 29, RAYLIB::BLACK);
    this->_tSettings = rl::Text("Settings", 80, 20, 29, RAYLIB::BLACK);
    this->_tHtp = rl::Text("How To Play", 77, 35, 29, RAYLIB::BLACK);
    this->_tWeapon = rl::Text("Weapons", 80, 50, 29, RAYLIB::BLACK);
    this->_tbackground = RAYLIB::LoadTexture("assets/texture/background.png");

    // PlayPhase
    this->_bJoinGame = Button("assets/texture/button_second_page.png", 15, 35, 67.68, 17.1);
    this->_bCreateGame = Button("assets/texture/button_second_page.png", 15, 60, 67.65, 17.1);
    this->_bSolo = Button("assets/texture/button_second_page.png", 15, 10, 67.65, 17.1);
    this->_bReturn = Button("assets/texture/button.png", 3, 85, 21.4, 10);
    this->_tJoinGame = rl::Text("Join Game", 32, 38, 70, RAYLIB::BLACK);
    this->_tCreateGame = rl::Text("Create Game", 27, 63, 70, RAYLIB::BLACK);
    this->_tSolo = rl::Text("Solo", 40, 13, 70, RAYLIB::BLACK);
    this->_tReturn = rl::Text("Return", 9, 88, 29, RAYLIB::BLACK);
    this->_tbackground2 = RAYLIB::LoadTexture("assets/texture/background2.png");

    // JoinPhase
    this->_iYourName = InputButton("assets/texture/port_button.png", 17, 20, 68.64, 14.07, 11, 59, 24, 37);
    this->_tYourName = rl::Text("Choose your name :", 21, 24, 37, RAYLIB::BLACK);
    this->_iIp = InputButton("assets/texture/port_button.png", 17, 38, 68.64, 14.07, 15, 27, 42, 37);
    this->_tIp = rl::Text("Ip : ", 20, 42, 37, RAYLIB::BLACK);
    this->_iPort = InputButton("assets/texture/button_div.png", 17, 56, 33.12, 13, 5, 33, 60, 37);
    this->_tPort = rl::Text("Port : ", 20, 60, 37, RAYLIB::BLACK);
    this->_bJoin = Button("assets/texture/button_div.png", 52, 56, 33.12, 13);
    this->_tJoin = rl::Text("Join", 64, 60, 37, RAYLIB::BLACK);

    // CreatePhase
    this->_iServPort = InputButton("assets/texture/port_button.png", 17, 25, 68.64, 14.07, 5, 67, 29, 37);
    this->_tServPort = rl::Text("Port of your server :", 21, 29, 37, RAYLIB::BLACK);
    this->_iName = InputButton("assets/texture/port_button.png", 17, 45, 68.64, 14.07, 11, 60, 49, 37);
    this->_tName = rl::Text("Choose your name :", 21, 49, 37, RAYLIB::BLACK);
    this->_bCreate = Button("assets/texture/button.png", 60, 70, 21.4, 10);
    this->_tCreate = rl::Text("Create", 65, 73, 29, RAYLIB::BLACK);

    //WeaponsPhase
    this->_tBackGroundWeapons = RAYLIB::LoadTexture("assets/texture/weapons.png");
    this->_bWeaponsReturn = Button("assets/texture/button.png", 5, 87, 21.4, 10);
    this->_tWeaponsReturn = rl::Text("Return", 10, 90, 30, RAYLIB::BLACK);

    //HowToPlay
    this->_tBackGroundHtp = RAYLIB::LoadTexture("assets/texture/howtoplay.png");
    this->_bHtpReturn = Button("assets/texture/button.png", 5, 87, 21.4, 10);
    this->_tHtpReturn = rl::Text("Return", 10, 90, 30, RAYLIB::BLACK);
    return (this->restart());
}

GamePhase Menu::restart()
{
    GamePhase gamePhase = MenuPhase;
    RAYLIB::ShowCursor();

    switch (this->_phase) {
    case Menu::MainPhase:
        gamePhase = this->mainPhase(gamePhase);
        break;
    case Menu::PlayPhase:
        gamePhase = this->playPhase(gamePhase);
        break;
    case Menu::CreatePhase:
        gamePhase = this->createPhase(gamePhase);
        break;
    case Menu::JoinPhase:
        gamePhase = this->joinPhase(gamePhase);
        break;
    case Menu::WeaponsPhase:
        gamePhase = this->weaponsPhase(gamePhase);
        break;
    case Menu::HowToPlayPhase:
        gamePhase = this->howToPlayPhase(gamePhase);
        break;
    default:
        break;
    }
    return (gamePhase);
}

GamePhase Menu::mainPhase(GamePhase gamePhase)
{
    if (this->_bQuit.isClicked())
        return (QuitPhase);
    if (this->_bPlay.isClicked()) {
        this->_phase = Menu::PlayPhase;
    }
    if (this->_bSettings.isClicked())
        gamePhase = SettingPhase;
    if (this->_bWeapon.isClicked()) {
        this->_phase = WeaponsPhase;
    }
    if (this->_bHtp.isClicked()) {
        this->_phase = HowToPlayPhase;
    }
    RAYLIB::DrawTextureEx(this->_tbackground, {0, 0}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    this->_bPlay.draw();
    this->_bSettings.draw();
    this->_bHtp.draw();
    this->_bWeapon.draw();
    this->_bQuit.draw();
    this->_tSettings.draw();
    this->_tHtp.draw();
    this->_tWeapon.draw();
    this->_tQuit.draw();
    return (gamePhase);
}

GamePhase Menu::howToPlayPhase(GamePhase gamePhase)
{
    if (this->_bHtpReturn.isClicked()) {
        this->_phase = MainPhase;
    }
    RAYLIB::DrawTextureEx(this->_tBackGroundHtp, {0, 0}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    this->_bHtpReturn.draw();
    this->_tHtpReturn.draw();
    return (gamePhase);
}

GamePhase Menu::weaponsPhase(GamePhase gamePhase)
{
    if (this->_bWeaponsReturn.isClicked()) {
        this->_phase = MainPhase;
    }
    RAYLIB::DrawTextureEx(this->_tBackGroundWeapons, {0, 0}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    this->_bWeaponsReturn.draw();
    this->_tWeaponsReturn.draw();
    return (gamePhase);
}

GamePhase Menu::playPhase(GamePhase gamePhase)
{
    if (this->_bCreateGame.isClicked())
        this->_phase = CreatePhase;
    if (this->_bJoinGame.isClicked())
        this->_phase = JoinPhase;
    if (this->_bSolo.isClicked()) {
        rl::Window::loading();
        return(GamePlayPhase);
    }
    if (this->_bReturn.isClicked())
        this->_phase = MainPhase;
    RAYLIB::DrawTextureEx(this->_tbackground2, {0, 0}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    this->_bJoinGame.draw();
    this->_bCreateGame.draw();
    this->_bReturn.draw();
    this->_bSolo.draw();
    this->_tCreateGame.draw();
    this->_tJoinGame.draw();
    this->_tReturn.draw();
    this->_tSolo.draw();
    return (gamePhase);
}

GamePhase Menu::createPhase(GamePhase gamePhase)
{
    if (this->_iServPort.isSelected())
        this->_iServPort.writeChar();
    if (this->_iName.isSelected())
        this->_iName.writeChar();
    if (this->_bReturn.isClicked())
        this->_phase = PlayPhase;
    if (this->_bCreate.isClicked()) {
        int port = std::atoi(this->_iServPort.getText().c_str());
        if (port < 2000 || port > 65535)
            return (MenuPhase);
        rl::Window::loading();
        Server::launch(std::atoi(this->_iServPort.getText().c_str()));
        return (LobbyPhase);
    }
    RAYLIB::DrawTextureEx(this->_tbackground2, {0, 0}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    this->_bReturn.draw();
    this->_tReturn.draw();
    this->_iServPort.draw();
    this->_tServPort.draw();
    this->_iName.draw();
    this->_tName.draw();
    this->_bCreate.draw();
    this->_tCreate.draw();
    return (gamePhase);
}

GamePhase Menu::joinPhase(GamePhase gamePhase)
{
    if (this->_iIp.isSelected())
        this->_iIp.writeChar(); // GESTION ERREUR
    if (this->_iPort.isSelected())
        this->_iPort.writeChar(); // GESTION ERREUR
    if (this->_iYourName.isSelected())
        this->_iYourName.writeChar(); // GESTION ERREUR
    if (this->_bJoin.isClicked()) {
        rl::Window::loading();
        return (LobbyPhase);
    }
    if (this->_bReturn.isClicked())
        this->_phase = PlayPhase;
    RAYLIB::DrawTextureEx(this->_tbackground2, {0, 0}, 0, ((float)RAYLIB::GetScreenHeight() / 1080), RAYLIB::WHITE);
    this->_bReturn.draw();
    this->_tReturn.draw();
    this->_iIp.draw();
    this->_tIp.draw();
    this->_iPort.draw();
    this->_tPort.draw();
    this->_iYourName.draw();
    this->_bJoin.draw();
    this->_tYourName.draw();
    this->_tJoin.draw();

    return (gamePhase);
}

std::string Menu::getIp()
{
    if (this->_iIp.getText() == "")
        return ("127.0.0.1");
    return (this->_iIp.getText());
}

std::string Menu::getPort()
{
    if (this->_phase == JoinPhase)
        return (this->_iPort.getText());
    return (this->_iServPort.getText());
}

std::string Menu::getYourName()
{
    return (this->_iYourName.getText());
}
