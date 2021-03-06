#include "opencvSolver.hpp"



std::map<unsigned int, coordVector> convertFormat(Mat &labels){
    cv::Size size = labels.size();

    std::map<unsigned int, coordVector> groups;
    
    for (int x = 0; x < size.height; x++) {
       for (int y = 0; y < size.width; y++) {
            if(labels.at<int>(x,y) != 0){
                if(groups.find(labels.at<int>(x,y)) == groups.end()){
                    groups[labels.at<int>(x,y)] = coordVector();
                    groups[labels.at<int>(x,y)].push_back(coord(x, y));
                }
                else{
                    groups[labels.at<int>(x,y)].push_back(coord(x, y));
                }
            }
        }
    }
    return groups;
}

void printSolution(std::map<unsigned int, coordVector> &groups, std::streambuf *out){
    std::ostream o(out);

    for (auto &group : groups){
        if(group.second.size() == 1){
            continue;
        }
        o << "[";
        for(coordVector::iterator it = group.second.begin(); it != group.second.end(); ++it){
            o << "[" << it->first << ", " << it->second << "],";
        }
        if(out == std::cout.rdbuf()){
            o << "\b]" << std::endl;
        }
        else{
            o.seekp(-1, std::ios::cur);
            o << "]" << std::endl;
        }
    }
}

std::map<unsigned int, coordVector> opencvSolver(std::vector<std::vector<uint8_t>> &matrix){
    cv::Mat matted(0, matrix[0].size(), DataType<uint8_t>::type), dst, cclLabels;

    for (unsigned int i = 0; i < matrix.size(); ++i){
        cv::Mat Sample(1, matrix[0].size(), DataType<uint8_t>::type, matrix[i].data());
        matted.push_back(Sample);
    }

    threshold(matted, dst, 0.5, 255, THRESH_BINARY);
    matted.release();

    connectedComponents(dst, cclLabels, 4);
    dst.release();

    std::map<unsigned int, coordVector> groups = convertFormat(cclLabels);

    return groups;
}
