#ifndef GUNSHIP_H
#include "SFML/Graphics.hpp"
#include <deque>

struct Bullet{
Bullet(float x, float y) : position(x,y){}
sf::Vector2f position;
bool isActive = true;
};

using BulletContainer = std::deque<Bullet>;

struct Ship{
Ship(){}
Ship(float x, float y) : position(x,y){}
sf::Vector2f position;
bool isHit = false;
};

enum class Direction{ None, Up, Down, Left, Right};

class Gunship{
public:
    Gunship();
    ~Gunship();

    void Render(sf::RenderWindow& l_window);
    bool IsHit();
    void Update();

    void SetDirection(Direction l_dir);
    void SetSpacebar(bool l_switch);
    void SetWindowSize(sf::Vector2u l_size);
    void DestroyBullet(int l_target);

    int m_shipSize;
    short m_lives;
    sf::Vector2f m_bulletSize;
    Ship ship;
    BulletContainer m_bulletFired;




private:
    void Setup();
    void Move();
    void BulletMove();
    void RestartClock();
    void RestartClockc();
    sf::RenderWindow m_Gunship;
    sf::Vector2f m_position;
    sf::RectangleShape m_shipRect;
    bool isHit;

    int m_increment;
    Direction m_dir;
    bool spacebar;
    short m_switch;

    sf::RectangleShape m_bulletRect;
    sf::Vector2f b_speed;
    sf::Time b_elapsed;
    sf::Time c_elapsed;
    sf::Clock c_clock;
    sf::Clock b_clock;
    float b_timestep;
    sf::Vector2u m_windSize;



};


#endif // GUNSHIP_H
