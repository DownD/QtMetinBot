#pragma once
#include <windows.h>
#define COLOR_RED "\x1B[31m"
#define COLOR_GREEN "\x1B[32m"
#define COLOR_DEFAULT "\033[0m"

#define DEBUG_INFO(color,...); {printf(__VA_ARGS__); printf("\n");}
