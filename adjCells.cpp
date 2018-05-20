#include <sstream>
#include <fstream>
#include <streambuf>
#include <vector>
#include <iostream>
#include <cstdint>
#include <chrono>
#include "json.hpp"
#include "solvers/recursiveExploration.cpp"
#include "solvers/opencvSolver.cpp"

using json = nlohmann::json;

void printUsage(std::string prog){
    std::cerr << "Usage: " << prog << " <path to file> [--out <path to file>|--notime]";
}

void printTime(std::chrono::duration<double> &secs, std::streambuf *out){
    std::ostream o(out);
    o << "Answer in: " << secs.count() << std::endl;
}

int main(int argc, char **argv){
    if(argc == 1){
        printUsage(argv[0]);
        exit(-1);
    }

    std::ifstream in(argv[1]);
	std::stringstream s;
	s << in.rdbuf();

    std::vector<std::string> args;
    args.assign(argv + 1, argv + argc);

    std::streambuf *output;
    std::ofstream outputFile;

    ptrdiff_t outIndex = std::find(args.begin(), args.end(), "--out") - args.begin();
    if(outIndex < args.size()){
        outputFile.open(args[outIndex + 1]);
        output = outputFile.rdbuf();
    } 
    else {
        output = std::cout.rdbuf();
    }

    auto start = std::chrono::system_clock::now();
    
    std::vector<std::vector<uint8_t>> matrix = json::parse(s.str());

    auto groups = opencvSolver(matrix);

    auto end = std::chrono::system_clock::now();
 
    printSolution(groups, output);

    if(std::find(args.begin(), args.end(), "--notime") == args.end()){
        std::chrono::duration<double> elapsed_seconds = end-start;
        printTime(elapsed_seconds, output);
    }
}