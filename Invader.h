#ifndef INVADER_H
#include "SFML/Graphics.hpp"
#include <deque>
#include <cmath>
#include <cstdlib>

enum class Monster{UFO, MARTIAN, COMMAND};

struct Enemy{
Enemy(float x, float y, Monster type) : position(x,y){}
sf::Vector2f position;
Monster type;
bool isActive = true;
bool isExploding = false;
float timer = 0.f;
};

struct eBullet{
eBullet(float x, float y) : position(x,y){}
sf::Vector2f position;
bool isActive = true;
};

using EnemyContainer = std::deque<Enemy>;
using BulletContainer2 = std::deque<eBullet>;

class Invader{
public:
    Invader(sf::Vector2u l_size);
    ~Invader();

    void Setup(sf::Vector2u l_size);
    void SetWindowSize( sf::Vector2u l_size);

    void Update();
    void Render(sf::RenderWindow& l_window);
    void Move();
    void EnemyFire();
    void DestroyEnemy(int l_target);
    void DestroyBullet(int l_target);
    void Explosion();

    EnemyContainer enemyarmy;
    BulletContainer2 bulletclip;
    sf::Vector2f m_bulletSize;
    float m_enemySize;
    float m_gapSize;


private:


    float m_enemySpeed;
    sf::Vector2u m_windSize;
    void Reset();

    sf::Vector2i m_clusterSize;
    float m_edgeSize;
    sf::Vector2f m_enemyStartPos;

    int m_yJump;

    sf::RectangleShape m_ufoRect;
    sf::RectangleShape m_ufoBulletRect;
    sf::CircleShape m_ufoExplosion;

    std::vector<int> enemiesFiring;
    sf::Vector2f i_speed;
    sf::Clock i_clock;
    sf::Time i_elapsed;
    float timestep;
    void RestartClock();
    inline bool random_bool();
    std::deque<short> enemiesExploding;

};


#endif // INVADER_H
