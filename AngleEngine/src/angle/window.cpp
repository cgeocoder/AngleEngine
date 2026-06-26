#include "window.h"

Window::Window(const Vec2i& size, const std::string& title) : m_Size{ size } {
    m_Window = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);

    if (!m_Window) {
        __debugbreak();
    }

    glfwMakeContextCurrent(m_Window);
}