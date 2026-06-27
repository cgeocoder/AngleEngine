#include "window.h"

Window::Window() : m_Size{ 0, 0 }, m_Window{ nullptr } {}

Window::Window(const Vec2i& size, const std::string& title) : m_Size{ size } {
    m_Window = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);

    if (!m_Window) {
        __debugbreak();
    }

    glfwMakeContextCurrent(m_Window);
}

Window::Window(const Window& _Copy) 
    : m_Size{ _Copy.m_Size }, m_Window{ _Copy.m_Window }, m_Title{ _Copy.m_Title } {}