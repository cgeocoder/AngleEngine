#pragma once

#ifndef __ANGLE_H__
#define __ANGLE_H__

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "errors.h"
#include "shader.h"
#include "vertex_buffer.h"
#include "vertex_array.h"
#include "index_buffer.h"

namespace angle {
    void PreInit(void);
    void Init(void);
    void Terminate(void);
}

#endif // !__ANGLE_H__