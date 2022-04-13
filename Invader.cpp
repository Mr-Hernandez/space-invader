#include "Invader.h"
#include <iostream>

Invader::Invader(sf::Vector2u l_size){
//    std::cout << "l_size" << l_size.x << ":" << l_size.y << std::endl;
    Setup(l_size);
    }

Invader::~Invader(){}

void Invader::Setup(sf::Vector2u l_size){
    m_enemySize = 16;
    m_clusterSize = sf::Vector2i(11,5); //(columns,rows)
    m_gapSize = 50;
    m_windSize = l_size;
    m_edgeSize = 42;
    m_enemySpeed = 0.1;
    m_yJump = 10;
    m_bulletSize = sf::Vector2f(2,5);
    i_speed = sf::Vector2f(0, 1);
    timestep = 1.f / 1.f;
//    std::cout << "wind1:" << m_windSize.x << "::" << m_windSize.y << std::endl;
    m_enemyStartPos = sf::Vector2f(m_edgeSize, (m_windSize.y / 2) - m_enemySize);
    m_ufoRect.setSize(sf::Vector2f(m_enemySize, m_enemySize));
    m_ufoRect.setFillColor(sf::Color::White);
    m_ufoBulletRect.setSize(m_bulletSize);
    m_ufoBulletRect.setFillColor(sf::Color::Magenta);
    m_ufoExplosion.setRadius(m_enemySize / 2);
    m_ufoExplosion.setFillColor(sf::Color::Transparent);
    m_ufoExplosion.setOutlineColor(sf::Color::White);
    m_ufoExplosion.setOutlineThickness(-2);
//    m_ufoExplosion.setOrigin(m_enemySize/2, m_enemySize/2);
//    m_ufoExplosion.setRadius(m_enemySize);
//    std::cout << m_enemyStartPos.x << ":::" << m_enemyStartPos.y << std::endl;
    Reset();
}

void Invader::SetWindowSize(sf::Vector2u l_size){
//    m_windSize = l_size;
//    std::cout << m_windSize.x << "::" << m_windSize.y << std::endl;
}

void Invader::Reset(){
    if(!enemyarmy.empty()){ enemyarmy.clear();}

    for(int i = 0; i < m_clusterSize.y; i++){ // 5 iterations
        for(int j = 0; j < m_clusterSize.x; j++){ // 11 iterations
            enemyarmy.push_back(Enemy(
                m_enemyStartPos.x + (m_gapSize * j),
                m_enemyStartPos.y - (m_gapSize * i),
                Monster::UFO));
        }
    }
}

void Invader::Render(sf::RenderWindow& l_window){
//    std::cout << enemyarmy.size() << std::endl;
    for(int i = 0; i < enemyarmy.size(); i++){
//        std::cout << i << ":" << enemyarmy[i].position.x;
//        std::cout << ":" << enemyarmy[i].position.y;
        m_ufoRect.setPosition(enemyarmy[i].position);
//        std::cout << ":" << m_ufoRect.getPosition().x;
//        std::cout << ":" << m_ufoRect.getPosition().y << std::endl;
        if(enemyarmy[i].isActive){
            l_window.draw(m_ufoRect);
        }
    }

    if(!enemiesExploding.empty()){
//    std::cout << "A";
    for(int j = 0; j < enemiesExploding.size(); j++){
//        std::cout << "B";
//        std::cout << enemyarmy[enemiesExploding[j]].timer;
        m_ufoExplosion.setPosition(
            enemyarmy[enemiesExploding[j]].position.x + m_enemySize/2,
            enemyarmy[enemiesExploding[j]].position.y + m_enemySize/2);
        m_ufoExplosion.setRadius(m_enemySize * enemyarmy[
            enemiesExploding[j]].timer * 0.1);
        m_ufoExplosion.setOrigin(m_ufoExplosion.getRadius(),
                                 m_ufoExplosion.getRadius());
//        m_ufoExplosion.scale(enemyarmy[enemiesExploding[j]].timer*1000,
//                             enemyarmy[enemiesExploding[j]].timer*1000);
        l_window.draw(m_ufoExplosion);
    }
    }

    if(!bulletclip.empty()){
        for(int i = 0; i < bulletclip.size(); i++){
            m_ufoBulletRect.setPosition(
                bulletclip[i].position.x,
                bulletclip[i].position.y);
            if(bulletclip[i].isActive){
                l_window.draw(m_ufoBulletRect);
            }
        }
    }

//    for(int i = 0; i < enemiesFiring.size(); i++){
//        m_ufoBulletRect.setPosition(enemyarmy[
//            enemiesFiring[i]].position +
//            sf::Vector2f(m_enemySize / 2, m_enemySize));
//        l_window.draw(m_ufoBulletRect);
//    }

}

void Invader::Move(){
    bool isDone = false;
    int i = 0;
    // case reached right edge
    while(!isDone && (i < enemyarmy.size())){
        if(enemyarmy[i].position.x + m_enemySize >= m_windSize.x &&
           enemyarmy[i].isActive){
            isDone = true;
        }
        i++;
    }
    if(isDone){
        for(int i = 0; i < enemyarmy.size(); i++){
            enemyarmy[i].position.y += m_yJump;
            m_enemySpeed = -m_enemySpeed;
            enemyarmy[i].position.x -= 1;
        }
    } else {
    // case left is reached
        i = 0;
        while(!isDone && (i < enemyarmy.size())){
            if(enemyarmy[i].position.x <= 0 &&
               enemyarmy[i].isActive){
                isDone = true;
            }
            i++;
        }
        if(isDone){
            for(int i = 0; i < enemyarmy.size(); i++){
                enemyarmy[i].position.y += m_yJump;
                m_enemySpeed = -m_enemySpeed;
                enemyarmy[i].position.x += 1;
            }
        } else { // case not edge
            for(int i = 0; i < enemyarmy.size(); i++){
                enemyarmy[i].position.x += m_enemySpeed;
            }
        }
    }
}

void Invader::Update(){
    Move();
    EnemyFire();
    Explosion();
//    std::cout << bulletclip.size() << std::endl;
    RestartClock();

}

// Only enemies on the frontline can shoot
void Invader::EnemyFire(){
    enemiesFiring.clear(); // contains position of enemies that shoot
    enemiesFiring.push_back(0);
    bool isDone = false;
    if(!enemyarmy.empty()){
        // check if x position exists already and
        // add location to local vector if it does not
        for(int i = 0; i < enemyarmy.size(); i++){
            if(enemyarmy[i].isActive){
            for(int j = 0; j < enemiesFiring.size(); j++){
                if(enemyarmy[i].position.x ==
                   enemyarmy[enemiesFiring[j]].position.x){
                      isDone = true;
                }
            }
            if(isDone){ isDone = false;}
            else { enemiesFiring.push_back(i);}
        }
        }
    }
    // randomize which enemies are shooting
//    for(int i = 0; i < enemiesFiring.size(); i++){
//        if(random_bool()){
//            enemiesFiring.erase(enemiesFiring.begin() + i);
//        }
//    }


    // Bullet movement---

    // add to bulletclip
    if(!enemyarmy[0].isActive){ enemiesFiring.erase(enemiesFiring.begin());}
    std::vector<bool> isFiring;
    int adjust = 0;
    if(i_elapsed.asSeconds() >= timestep){
        for(int i = 0; i < enemiesFiring.size(); i++){
            isFiring.push_back(random_bool());
//            std::cout << isFiring[i] << ":";
        }
//        std::cout << std::endl;
       for(int i = 0; i < isFiring.size(); i++){
            if(!isFiring[i]){
                enemiesFiring.erase(enemiesFiring.begin() + i - adjust);
                adjust++;
            }
       }

       for(int i = 0; i < enemiesFiring.size(); i++){
            bulletclip.push_back(eBullet(
                enemyarmy[enemiesFiring[i]].position.x +
                m_enemySize /2 ,
                enemyarmy[enemiesFiring[i]].position.y +
                m_enemySize));
       }
       i_elapsed -= sf::seconds(timestep);
    }
//    Explosion();
    // remove front ?
    // move bullet using b_speed as increment
    if(!bulletclip.empty()){
        for(int i = 0; i < bulletclip.size(); i++){
            bulletclip[i].position += i_speed;
        }
        if(bulletclip[0].position.y >= m_windSize.y){ bulletclip.pop_front();}
    }

}
void Invader::DestroyBullet(int l_target){
    bulletclip[l_target].isActive = false;
}

void Invader::DestroyEnemy(int l_target){
    enemyarmy[l_target].isActive = false;
    enemyarmy[l_target].isExploding = true;
    enemiesExploding.push_back(l_target); //list of enemy elements exploding
    }

void Invader::Explosion(){
    if(!enemiesExploding.empty()){
        for(int i = 0; i < enemiesExploding.size(); i++){
            enemyarmy[enemiesExploding[i]].timer += i_elapsed.asSeconds();
            if(enemyarmy[enemiesExploding[i]].timer > 20.f ){
                enemyarmy[enemiesExploding[i]].isExploding = false;
                enemiesExploding.pop_front();
            }
        }
    }
}

inline bool Invader::random_bool(){
    int r = 10;
    static const int shift = static_cast<int>(std::log2(r));
    return (rand() >> shift) & 1;
}



void Invader::RestartClock(){ i_elapsed += i_clock.restart();}
