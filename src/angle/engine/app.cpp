#include "app.h"

#include "../gl/errors.h"

namespace angle {
	App::App() {
		if (!glfwInit()) {
			log.err("App::App(): glfwInit() failed");
			exit(-1);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	}

	App::~App() {
		log.info("App::~App(): glfwTerminate()");

		glfwTerminate();
	}

	void API set_current_context() {
		if (glewInit() != GLEW_OK) {
			clog::Log().err("set_current_context(): glewInit() failed");
			exit(-1);
		}

		debug::InitDebugOutput();

		GL(glEnable(GL_BLEND));
		GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}
}