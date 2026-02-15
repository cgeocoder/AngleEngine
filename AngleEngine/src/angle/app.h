#pragma once

#ifndef __APP_H__
#define __APP_H__

#include "kernel.h"

namespace angle {

	class API App {
	public:
		App();
		virtual ~App();
		void run();
	};


	App* create_app();
}

#endif // !__APP_H__