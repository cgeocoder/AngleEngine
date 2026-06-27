#pragma once

#ifndef __OPENGL_ERRORS_H__
#define __OPENGL_ERRORS_H__

#include "../engine/kernel.h"
#include "opengl.h"
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

    void API enable_notification(DebugSeverity);
    void API disable_notification(DebugSeverity);
    void API add_debug_info(const wchar_t*, const char*, long);
    void API clear_debug_info();
    void API APIENTRY DebugErrorCallback(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar*, const void*);
    void API InitDebugOutput();
}

# define GL(code)                       \
    angle::debug::add_debug_info(       \
        __FILEW__, #code, __LINE__       \
    );                                  \
    code;                               \
    if (glGetError() == GL_NO_ERROR) angle::debug::clear_debug_info()

#else
# define GL(code) code
#endif// !_DEBUG

#endif // !__OPENGL_ERRORS_H__