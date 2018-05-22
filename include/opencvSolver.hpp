#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;

std::map<unsigned int, std::vector<std::pair<int, int>>> convertFormat(Mat &labels);
void printSolution(std::map<unsigned int, std::vector<std::pair<int, int>>> &groups, std::streambuf *out);
std::map<unsigned int, std::vector<std::pair<int, int>>> opencvSolver(std::vector<std::vector<uint8_t>> &matrix);