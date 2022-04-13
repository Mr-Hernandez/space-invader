#include "Game.h"
#include <iostream>

Game::Game() : m_window(sf::Vector2u(600,800), "From Window"),
               m_invader(sf::Vector2u(600,800))
{
    m_gunship.SetWindowSize(m_window.GetSize());
    m_invader.SetWindowSize(m_window.GetSize());
    font.loadFromFile("assets/fonts/arial.ttf");
    text.setFont(font);

}

Game::~Game(){}

void Game::Render(){
    if(m_gunship.m_lives == 0){
        m_window.BeginDraw();
        text.setString("Game Over");
        text.setCharacterSize(34);
        text.setFillColor(sf::Color::Red);
        text.setPosition(m_window.GetSize().x/2, m_window.GetSize().y/2);
        text.setOrigin(text.getLocalBounds().width/2,
                       text.getLocalBounds().height/2);
        m_window.Draw(text);
        m_window.EndDraw();
    }

    else {
    sf::RectangleShape rect(sf::Vector2f(100,100));//tmp
    rect.setFillColor(sf::Color::Blue);//tmp
    m_window.BeginDraw();
    // example of draw here
    // m_snake.Render(*m_window.GetRenderWindow());
    m_gunship.Render(*m_window.GetRenderWindow());
    m_invader.Render(*m_window.GetRenderWindow());
//    m_window.Draw(rect);//tmp
    m_window.EndDraw();
    }


}

void Game::Update(){
    float timestep = 1.f / 120.f;
    if(m_elapsed.asSeconds() >= timestep){
        m_gunship.Update();
        m_invader.Update();
        Collisions();

//        std::cout << "m_elapsed:" << m_elapsed.asSeconds() << std::endl;
        m_elapsed -= sf::seconds(timestep);

    }
    m_window.Update();
}

void Game::HandleInput(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        m_gunship.SetDirection(Direction::Up);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        m_gunship.SetDirection(Direction::Down);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        m_gunship.SetDirection(Direction::Left);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        m_gunship.SetDirection(Direction::Right);
    }

    m_gunship.SetSpacebar(sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
}

void Game::Collisions(){
    //is player ship being hit?
    if(!m_invader.bulletclip.empty() &&
       (!m_gunship.ship.isHit)){
    for(int i = 0; i < m_invader.bulletclip.size(); i++){
//        std::cout << "A:";
        if((m_invader.bulletclip[i].position.y +
           m_invader.m_bulletSize.y >=
           m_gunship.ship.position.y) &&
           (m_invader.bulletclip[i].position.y <=
            m_gunship.ship.position.y +
            m_gunship.m_shipSize))

        {
                if((m_invader.bulletclip[i].position.x + 1 >=
                   m_gunship.ship.position.x) &&
                   (m_invader.bulletclip[i].position.x + 1 <=
                    m_gunship.ship.position.x + m_gunship.m_shipSize))
                   {
                       m_invader.DestroyBullet(i);
                       m_gunship.ship.isHit = true;
                       m_gunship.m_lives -= 1;
                       std::cout << "Hit" << std::endl;
                       break;
                   }
        }
    }
    }

    //is enemy ship being hit?
    if(!m_gunship.m_bulletFired.empty()){
//            std::cout << "X";
    int tiers = (m_invader.enemyarmy[0].position.y -
        m_invader.enemyarmy[m_invader.enemyarmy.size()-1].position.y) /
        m_invader.m_gapSize;
//        std::cout << "tiers" << tiers << "A";

    // for each gunship bullet on screen
    for(int i = 0; i < m_gunship.m_bulletFired.size(); i++){
    if(m_gunship.m_bulletFired[i].isActive){
        // Check if bullet is out of range of enemies
        // As is above the highest and below the lowest
//        std::cout << m_invader.enemyarmy[0].position.y + m_invader.m_enemySize << std::endl;
        if((m_gunship.m_bulletFired[i].position.y >
            m_invader.enemyarmy[0].position.y + m_invader.m_enemySize) ||
           (m_gunship.m_bulletFired[i].position.y + m_gunship.m_bulletSize.y <
            m_invader.enemyarmy[m_invader.enemyarmy.size()-1].position.y)){
                // do nothing
//                std::cout << "C" << i;
        } else {
//            for(int i = 0; i < m_gunship.m_bulletFired.size(); i++){
//            if(m_gunship.m_bulletFired[i].isActive){
                for(int j = 0; j < m_invader.enemyarmy.size(); j++){
                    if(m_invader.enemyarmy[j].isActive){

                    if(m_gunship.m_bulletFired[i].position.y <=
                       m_invader.enemyarmy[j].position.y +
                       m_invader.m_enemySize &&
                       m_gunship.m_bulletFired[i].position.y +
                       m_gunship.m_bulletSize.y >=
                       m_invader.enemyarmy[j].position.y){
                    if(m_gunship.m_bulletFired[i].position.x + 1 >=
                       m_invader.enemyarmy[j].position.x &&
                       m_gunship.m_bulletFired[i].position.x + 1 <=
                       m_invader.enemyarmy[j].position.x +
                       m_invader.m_enemySize){
                            m_invader.DestroyEnemy(j);
                            m_gunship.DestroyBullet(i);

//                            std::cout << "you hit a ship" << std::endl;

                       }
                       }
                    }
                }
//            }
//            }
//        for(int j = 0; j < tiers + 1; j++){
////            if(m_gunship.m_bulletFired[i].isActive){
////            std::cout << "D" << i << ":" << j;
//            // Is bullet position y matching enemy y position
//
//            if((m_gunship.m_bulletFired[i].position.y <=
//                m_invader.enemyarmy[0].position.y +
//                m_invader.m_enemySize -
//                (m_invader.m_gapSize * j)) &&
//                (m_gunship.m_bulletFired[i].position.y + m_gunship.m_bulletSize.y <=
//                m_invader.enemyarmy[0].position.y + (m_invader.m_gapSize * j)))
//            {
////                std::cout << "E" << i << ":" << j;
//                //check if bullet x pos matches an enemyship x vicinity
//                for(int k = 0; k < m_invader.enemyarmy.size(); k++){
////                    std::cout << "F" << i << ":" << j << ":" << k;
////                    if((m_invader.enemyarmy[0].position.y +
////                       (m_invader.m_gapSize * j)) !=
////                       m_invader.enemyarmy[k].position.y){
////                                std::cout << "G" << i << ":" << j << ":" << k;
////                                break;
////                       } else
//                       //
//                       // if bullet is between x coords of enemy
//                       if((m_gunship.m_bulletFired[i].position.x + 1 >=
//                                 m_invader.enemyarmy[k].position.x) &&
//                                 (m_gunship.m_bulletFired[i].position.x + 1 <=
//                                 m_invader.enemyarmy[k].position.x +
//                                 m_invader.m_enemySize) &&
//                                 m_invader.enemyarmy[k].isActive){
//                                    m_invader.DestroyEnemy(k);
//                                    m_gunship.DestroyBullet(i);
////                                    std::cout << "You Hit a Ship" << i << ":" << j << ":" << k << std::endl;
//                                    break;
//                       }
//
//                }
//            }
//            }
            }
        }
    }
    }
}

void Game::PlayerHit(){
    std::cout << "you sunk my spacleship";

}

//m_invader.bulletclip[i].position.x + 1

Window* Game::GetWindow(){ return &m_window;}

sf::Time Game::GetElapsed(){ return m_elapsed;}
void Game::RestartClock(){ m_elapsed += m_clock.restart();}



