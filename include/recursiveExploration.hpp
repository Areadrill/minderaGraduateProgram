#pragma once
#include <vector>
#include <cstdint>
#include <streambuf>
#include <iostream>

typedef std::pair<uint32_t, uint32_t> coord;
typedef std::vector<coord> coordVector;

void printSolution(std::vector<coordVector> &groups, std::streambuf *out);
coordVector getAdjacents(coord point);
void exploreCluster(coord point, coordVector &accum, std::vector<std::vector<uint8_t>> &matrix);
std::vector<coordVector> recursiveExploration(std::vector<std::vector<uint8_t>> &matrix);