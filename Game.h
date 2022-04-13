#ifndef GAME_H
#include "Window.h"
#include "Gunship.h"
#include "Invader.h"
#include "SFML/Graphics.hpp"

enum class GAMESTATE{PLAY, HIT};

class Game{
public:
    Game();
    ~Game();

    void Render();
    void Update();

    void HandleInput();
    void RestartClock();
    sf::Time GetElapsed();

    Window* GetWindow();

    // extras
    void Collisions();
    GAMESTATE gamestate;
    void PlayerHit();

private:
    Window m_window;
    Gunship m_gunship;
    Invader m_invader;

    //implement clock
    sf::Clock m_clock;
    sf::Time m_elapsed;
    sf::Text text;
    sf::Font font;



};



#endif // GAME_H
