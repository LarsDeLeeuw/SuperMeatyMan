#ifndef VIEW_WINDOW_HPP
#define VIEW_WINDOW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <mutex>

class Window {
    // Singleton wrapper for sf::RenderWindow
public:
    Window(Window& other) = delete;         // Singleton pattern does not allow cloning
    void operator=(const Window&) = delete; // Singleton pattern does not allow assinging

    static std::shared_ptr<Window> getWindow();

    std::shared_ptr<sf::RenderWindow> getRenderWindow();

    Window();
    ~Window() = default;

private:
    std::shared_ptr<sf::RenderWindow> mRenderWindow;

    static std::shared_ptr<Window> window_;
    static std::mutex mutex_; // This singleton wrapper is threadsafe
};

#endif