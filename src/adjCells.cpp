#include "adjCells.hpp"

void printUsage(std::string prog){
    std::cerr << "Usage: " << prog << " <path to file> [--solver <solver name>|--out <path to file>|--notime]";
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
    auto end = std::chrono::system_clock::now();

    std::vector<std::vector<uint8_t>> matrix = readFile(argv[1]);
    if(matrix.size() == 0){
        std::cerr << "There was a problem with the file containing the matrix. Cannot proceed." <<std::endl;
        exit(-1);
    }

    ptrdiff_t solverIndex = std::find(args.begin(), args.end(), "--solver") - args.begin();
    if(solverIndex < args.size() && args[solverIndex + 1] == "opencv"){
        std::map<unsigned int, coordVector> groups = opencvSolver(matrix);
        end = std::chrono::system_clock::now();
        printSolution(groups, output);
    }
    else{
        std::vector<coordVector> groups = recursiveExploration(matrix);
        end = std::chrono::system_clock::now();
        printSolution(groups, output);
    }

    if(std::find(args.begin(), args.end(), "--notime") == args.end()){
        std::chrono::duration<double> elapsed_seconds = end-start;
        printTime(elapsed_seconds, output);
    }
}