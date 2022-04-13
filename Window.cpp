#include "Window.h"

Window::Window(){Setup(sf::Vector2u(500,500), "Default title");}

Window::Window(const sf::Vector2u& l_windowSize, const std::string& l_title){
    Setup(l_windowSize, l_title);
}

Window::~Window(){ Destroy();}
void Window::Render(const sf::Vector2u& l_size, const std::string& l_title){

}

void Window::Setup(const sf::Vector2u& l_size, const std::string& l_title){
    m_windowSize = l_size;
    m_windowTitle = l_title;
    m_isDone = false;
    Create();
}

void Window::Create(){
    m_window.create({m_windowSize.x, m_windowSize.y, 32}, m_windowTitle, sf::Style::Default);
}

void Window::Destroy(){ m_window.close();}

void Window::Update(){
    sf::Event event;
    while(m_window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            m_isDone = true;
            //m_window.close();
        }
    }
}

bool Window::IsDone(){ return m_isDone;}

sf::RenderWindow* Window::GetRenderWindow(){ return &m_window;}

void Window::BeginDraw(){ m_window.clear(sf::Color::Black);}
void Window::EndDraw(){ m_window.display();}
void Window::Draw(sf::Drawable& l_drawable){ m_window.draw(l_drawable);}
sf::Vector2u Window::GetSize(){ return m_window.getSize();}
//void Window::Render(){
//    BeginDraw();
//    EndDraw();
//}
