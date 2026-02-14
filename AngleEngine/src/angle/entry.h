#pragma once

#ifndef __ENTRY_H__
#define __ENTRY_H__

#ifdef WINDOWS_PLATFORM

extern angle::App* angle::create_app();

int main() {
	angle::App* app = angle::create_app();
	app->run();
	delete app;

	return 0;
}

#endif 
#endif // !__ENTRY_H__