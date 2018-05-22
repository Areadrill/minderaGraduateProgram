#pragma once
#include <sstream>
#include <fstream>
#include <streambuf>
#include <vector>
#include <iostream>
#include <cstdint>
#include <chrono>
#include "../include/json.hpp"
#include "recursiveExploration.hpp"
#include "opencvSolver.hpp"

void printUsage(std::string prog);
void printTime(std::chrono::duration<double> &secs, std::streambuf *out);
