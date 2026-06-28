#pragma once

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <string>
#include "opengl.h"
#include "vertex_array.h"
#include "index_buffer.h"
#include "../../utils/stb_image/stb_image.h"
#include "errors.h"
#include "shader.h"

template<typename _Ty>
class API Vec2 {
    typedef Vec2<_Ty> Vec2T;

public:
    inline Vec2(const Vec2T& vec) : x{ vec.x }, y{ vec.y } {}
    inline Vec2(_Ty X, _Ty Y) : x{ X }, y{ Y } {}

    _Ty x, y;
};

using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;

class API Window {
private:
    GLFWwindow* m_Window;
    Vec2i m_Size;
    std::string m_Title;

public:
    Window();
    Window(const Window& _Copy);
    Window(const Vec2i& size, const std::string& title);

    inline void set_swap_interval(int _Status) const {
        glfwSwapInterval(_Status);
    }

    inline void set_title(const std::string& title) {
        glfwSetWindowTitle(m_Window, title.c_str());
    }

    inline bool is_open(void) {
        return !glfwWindowShouldClose(m_Window);
    }

    inline void clear(void) {
        GL(glClear(GL_DEPTH_BUFFER_BIT));
    }

    inline void update(void) {
        glfwSwapBuffers(m_Window);

        glfwPollEvents();
    }

    inline void draw(const VertexArray& _VA, const IndexBuffer& _IB, const Shader& _Shader) const {
        _Shader.bind();
        _VA.bind();
        _IB.bind();

        GL(glDrawElements(GL_TRIANGLES, _IB.get_count(), GL_UNSIGNED_INT, nullptr));
    }
};

#endif // !__WINDOW_H__