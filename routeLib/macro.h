#pragma once

#ifdef ROUTELIB_EXPORTS
#define ROUTELIB_API __declspec(dllexport)
#else
#define ROUTELIB_API __declspec(dllimport)
#endif

