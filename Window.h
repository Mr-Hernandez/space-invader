#ifndef WINDOW_H
#include "SFML/Graphics.hpp"

class Window{
public:
    Window();
    Window(const sf::Vector2u& l_size, const std::string& l_title);
    ~Window();

    void Update();
//    void Render(); // Temporary Render
    sf::RenderWindow* GetRenderWindow();

    bool IsDone();
    void BeginDraw();
    void EndDraw();
    void Draw(sf::Drawable& l_drawable);
    sf::Vector2u GetSize();

private:
    void Render(const sf::Vector2u& l_size, const std::string& l_title);
    void Setup(const sf::Vector2u& l_size, const std::string& l_title);
    void Create();
    void Destroy();

    sf::RenderWindow m_window;
    sf::Vector2u  m_windowSize;
    std::string m_windowTitle;
    bool m_isDone;



};

#endif // WINDOW_H
