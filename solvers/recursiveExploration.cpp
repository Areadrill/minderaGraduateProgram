#include <vector>

typedef std::pair<uint32_t, uint32_t> coord;
typedef std::vector<coord> coordVector;

void printSolution(std::vector<coordVector> &groups){
    for (std::vector<coordVector>::iterator it = groups.begin() ; it != groups.end(); ++it){
        std::cout << "[";
        for (coordVector::iterator jt = it->begin(); jt != it->end(); ++jt){
            std::cout << "[" << jt->first << ", " << jt->second << "],";
        }
        std::cout << "\b]" << std::endl;
    }
}

coordVector getAdjacents(coord point){
    const coord adjacents[] = {coord(point.first + 1, point.second), 
                               coord(point.first - 1, point.second),
                               coord(point.first, point.second + 1),
                               coord(point.first, point.second - 1)};
    return coordVector (adjacents, adjacents + sizeof(adjacents) / sizeof(adjacents[0]));
}

void exploreCluster(coord point, coordVector &accum, std::vector<std::vector<uint8_t>> &matrix){
    matrix[point.first][point.second] = 0;
    accum.push_back(point);

    coordVector res = getAdjacents(point);
    
    if(point.first != 0 && matrix[res[1].first][res[1].second] == 1){ //up
        exploreCluster(res[1], accum, matrix);
    }
    if(point.first != matrix.size() -1 && matrix[res[0].first][res[0].second] == 1){ //down
        exploreCluster(res[0], accum, matrix);
    }
    if(point.second != 0 && matrix[res[3].first][res[3].second] == 1){ //left
        exploreCluster(res[3], accum, matrix);
    }
    if(point.second != matrix[0].size() -1 && matrix[res[2].first][res[2].second] == 1){ //right
        exploreCluster(res[2], accum, matrix);
    }
}

std::vector<coordVector> recursiveExploration(std::vector<std::vector<uint8_t>> &matrix){
    std::vector<coordVector> groups;

    for (std::vector<std::vector<uint8_t>>::iterator it = matrix.begin() ; it != matrix.end(); ++it){
        for (std::vector<uint8_t>::iterator jt = it->begin(); jt != it->end(); ++jt){
            if(*jt == 1){
                coordVector res;
                exploreCluster(coord(it - matrix.begin(), jt - it->begin()), res, matrix);

                if(res.size() > 1){
                    groups.push_back(res);
                }
            }
        }
    }

    return groups;
}
