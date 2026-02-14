#pragma once

#ifndef __KERNEL_H__
#define __KERNEL_H__

#ifdef WINDOWS_PLATFORM

# ifdef DLL_BUILD

/*
	Specification for declaring functions inside the DLL library code
*/
#  define API __declspec(dllexport)
# else

/*
	Specification for declaring functions inside the user code
*/
#  define API __declspec(dllimport)

/*
	Defines the entry point of the program
	@param class_name - The name of the entry point class
*/
#  define set_entry_point_class(class_name) angle::App* API angle::create_app() { return new class_name(); }

# endif

#else
# error This platform is not supported
#endif

#endif // !__KERNEL_H__