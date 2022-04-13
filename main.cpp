#include "SFML/Graphics.hpp"
#include "Game.h"

int main(){
//
//    sf::RenderWindow window(sf::VideoMode(800, 400), "learn_window");
//    sf::RectangleShape rect(sf::Vector2f(200,200));
//    rect.setFillColor(sf::Color::Blue);
//
//    while(window.isOpen()){
//        sf::Event event;
//        while(window.pollEvent(event)){
//            if(event.type == sf::Event::Closed){
//            window.close();
//            }
//        }
//    window.clear();
//    window.draw(rect);
//    window.display();
//    }

//    Window window;
//    while(!window.IsDone()){
//        window.Update();
//        window.Render();
//    }

    Game game;
    while(!game.GetWindow()->IsDone()){
        game.HandleInput();
        game.Update();
        game.Render();
        game.RestartClock();
    }


    return 0;
}
