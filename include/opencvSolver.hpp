#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <cstdint>

typedef std::pair<uint32_t, uint32_t> coord;
typedef std::vector<coord> coordVector;


using namespace cv;

std::map<unsigned int, coordVector> convertFormat(Mat &labels);
void printSolution(std::map<unsigned int, coordVector> &groups, std::streambuf *out);
std::map<unsigned int, coordVector> opencvSolver(std::vector<std::vector<uint8_t>> &matrix);