#include "app.h"
#include "../utils/logger/log.h"

namespace angle {
	clog::Log log;

	App::App() {
		log.info("App::App() base App constructor");
	}

	App::~App() {
		log.info("App::~App() base App destructor");
	}

	void App::run() {
		log.info("App::run()");
	}
}