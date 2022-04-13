#include "Gunship.h"
#include <iostream>
Gunship::Gunship(){
    Setup();
//    m_shipSize = 15;
//    ship.position = sf::Vector2f(385, 750);
}

Gunship::~Gunship(){}

void Gunship::Setup(){
    m_shipSize = 15;
    m_increment = 5;
    ship.position = sf::Vector2f(292, 750);
    m_shipRect.setSize(sf::Vector2f(15,15));
    m_shipRect.setFillColor(sf::Color::Green);
    m_lives = 3;
    isHit = false;
    spacebar = false;

    b_speed = sf::Vector2f(0, 5);
    b_timestep = 1.f / 10.f;
    m_bulletSize = sf::Vector2f(2,6);
    m_bulletRect.setSize(m_bulletSize);
    m_bulletRect.setFillColor(sf::Color::Blue);

}

bool Gunship::IsHit(){ return isHit;}

void Gunship::Update(){
    Move();
    BulletMove();
    RestartClock();
//    std::cout << m_bulletFired.size() << std::endl;


}

void Gunship::Render(sf::RenderWindow& l_window){

//    m_position = sf::Vector2f(385.f, 750.f);
//    m_shipRect.setPosition(m_position);
    //Ship ship(385,750);

    m_shipRect.setPosition(ship.position);
    if(ship.isHit){
        m_shipRect.setFillColor(sf::Color::Red);
        std::cout << c_elapsed.asSeconds() << std::endl;
        if(c_elapsed.asSeconds() > 2){
            ship.isHit = false;
            m_shipRect.setFillColor(sf::Color::Blue);
        }
    } else { c_elapsed = sf::seconds(0);}
    RestartClockc();



    l_window.draw(m_shipRect);
    for(int i = 0; i < m_lives; i++){
        m_shipRect.setPosition(50 * i + 30, 10);
        l_window.draw(m_shipRect);
    }

    if(!m_bulletFired.empty()){
        for(int i = 0; i < m_bulletFired.size(); i++){
            m_bulletRect.setPosition(m_bulletFired[i].position);
            if(m_bulletFired[i].isActive){
                l_window.draw(m_bulletRect);
            }
        }
    }




}

void Gunship::Move(){
    m_switch = 1;
//    m_dir = Direction::Left;
    if(m_dir == Direction::None){ m_switch = 0;}
    else if(m_dir == Direction::Left){
            ship.position.x = ship.position.x + (-m_increment * m_switch);
            if(ship.position.x < 0.f){ ship.position.x = 0.f;}
            }
    else if(m_dir == Direction::Right){
            ship.position.x = ship.position.x + (m_increment * m_switch);
            if(ship.position.x + m_shipSize > m_windSize.x){
                ship.position.x = m_windSize.x - m_shipSize;}
//              ship.position.x = windSize - m_shipSize;}
            }
}

void Gunship::BulletMove(){
    // create new bullet
    if(b_elapsed.asSeconds() >= b_timestep){
        b_elapsed = sf::seconds(b_timestep);

        if(spacebar){
        m_bulletFired.push_back(Bullet(
            ship.position.x + m_shipSize / 2,
            ship.position.y));
        b_elapsed -= sf::seconds(b_timestep);
        }
    }

    // remove front ?
    // move bullet using b_speed as increment
    if(!m_bulletFired.empty()){
        for(int i = 0; i < m_bulletFired.size(); i++){
            m_bulletFired[i].position -= b_speed;
        }
        if(m_bulletFired[0].position.y <= 0){ m_bulletFired.pop_front();}
    }
}

void Gunship::DestroyBullet(int l_target){
    m_bulletFired[l_target].isActive = false;
//    m_bulletFired.pop_front();
}

void Gunship::SetWindowSize(sf::Vector2u l_size){ m_windSize = l_size;}

void Gunship::SetDirection(Direction l_dir){
    m_dir = l_dir;
}

void Gunship::SetSpacebar(bool l_switch){
    spacebar = l_switch;
}

void Gunship::RestartClock(){ b_elapsed += b_clock.restart();}
void Gunship::RestartClockc(){ c_elapsed += c_clock.restart();}
