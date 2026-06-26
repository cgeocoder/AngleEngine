#pragma once

#ifndef __OPENGL_ERRORS_H__
#define __OPENGL_ERRORS_H__

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#ifdef _DEBUG

namespace angle::debug {

    enum DebugSeverity 
        : unsigned int { Low, Medium, Hight, Info};

    struct DebugCallbackInfo {
        const wchar_t* file;
        const char* code;
        long line;
    };

    void enable_notification(DebugSeverity severity);
    void disable_notification(DebugSeverity severity);

    void __fastcall add_debug_info(const wchar_t* file, const char* code, long line);
    void clear_debug_info();

    void APIENTRY DebugErrorCallback(
        GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* userParam
    );

    void InitDebugOutput();
}

# define GL(code)                   \
    angle::debug::add_debug_info(       \
        __FILEW__, #code, __LINE__       \
    );                                  \
    code;                               \
    if (glGetError() == GL_NO_ERROR) angle::debug::clear_debug_info()

#else
# define GL(code) code
#endif// !_DEBUG

#endif // !__OPENGL_ERRORS_H__