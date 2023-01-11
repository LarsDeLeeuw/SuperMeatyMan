#include "include/Window.hpp"
#include <memory>
#include <mutex>

std::shared_ptr<Window> Window::window_{nullptr};
std::mutex Window::mutex_;

Window::Window()
    : mRenderWindow(
          std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "SFML Application", sf::Style::Close)) {}

std::shared_ptr<sf::RenderWindow> Window::getRenderWindow() { return mRenderWindow; }

std::shared_ptr<Window> Window::getWindow() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (window_ == nullptr) {
        window_ = std::make_shared<Window>();
    }
    return window_;
}