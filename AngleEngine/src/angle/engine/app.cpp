#include "app.h"

namespace angle {
	App::App() {
		log.p("App::App() base App constructor");
	}

	App::~App() {
		log.info("App::~App() base App destructor");
	}
}