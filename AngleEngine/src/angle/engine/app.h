#pragma once

#ifndef __APP_H__
#define __APP_H__

#include "kernel.h"
#include "../../utils/log/log.h"

namespace angle {

	/* 
		Base Application Engine class
	*/
	class API App {
	protected:
		// Main application loggger
		clog::Log log;

	public:
		App();
		virtual ~App() = 0;

		// A method with main rendering cycle
		virtual void run() = 0;
	};

	/* 
		Create a child class for App as executable.
		A execubacle class must be defined with set_entry_point_class()
	*/
	App* create_app();

	void API set_current_context(void);
}

#endif // !__APP_H__