#ifndef UTILS_HPP
#define UTILS_HPP

#include "player.hpp"
#include "types.hpp"
#include <fstream>
#include <iostream>

using namespace std;

Clan loadclan(const string& arq_name);
int random_status(int max);

#endif