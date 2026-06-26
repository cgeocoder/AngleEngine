#include "angle.h"

namespace angle {
    void PreInit(void) {
        if (!glfwInit()) {
            printf("GL::Init() glfwInit() failed");
            exit(-1);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void Init(void) {
        if (glewInit() != GLEW_OK) {
            printf("GL::InitContext() glewInit() failed");
            exit(-1);
        }

        debug::InitDebugOutput();
    }

    void Terminate(void) {
        glfwTerminate();
    }
}