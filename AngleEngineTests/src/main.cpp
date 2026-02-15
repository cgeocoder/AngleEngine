#include <angle.h>
#include <utils/logger/log.h>

class MyApp : public angle::App {
private:
	clog::Log log;

public:
	MyApp() {
		log.info("Hello world!");
	}

	~MyApp() {}
};

set_entry_point_class(MyApp);
