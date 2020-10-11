#pragma once
#include "iostream"
#define UNREACHABLE(v) do {std::cout << "unreachable code: " << v << std::endl; exit(1);} while(0)