#include <gtest/gtest.h>
#include "adjCells.hpp"
#include "recursiveExploration.hpp"

TEST(FileReading, Normal){
    ASSERT_NO_THROW(readFile("../../test/testMatrixes/100x100.json"));
}

TEST(FileReading, NonExistant){
    ASSERT_EQ(readFile("doesntexist"), std::vector<std::vector<uint8_t>>());
}

TEST(FileReading, CorrectMapping){
    std::vector<std::vector<uint8_t>> small = readFile("../../test/testMatrixes/small.json");
    std::vector<std::vector<uint8_t>> expected = {{1,1,0,0}, {0,0,1,0}, {1,0,0,0}};

    ASSERT_EQ(small, expected);
}

TEST(RecursiveExploration, NormalParsing){
    std::vector<std::vector<uint8_t>> matrix = {{1,1,0,0}, {0,0,1,0}, {1,0,0,0}};
    
    std::vector<coordVector> result = recursiveExploration(matrix);
    std::vector<coordVector> expected = {{coord(0, 0), coord(0, 1)}};

    ASSERT_EQ(result, expected);
}

TEST(RecursiveExploration, CheckeredPattern){
    std::vector<std::vector<uint8_t>> matrix = {{1,0,1,0}, {0,1,0,1}, {1,0,1,0}};
    
    std::vector<coordVector> result = recursiveExploration(matrix);
    std::vector<coordVector> expected = {};

    ASSERT_EQ(result, expected);
}

TEST(RecursiveExploration, FullMatrix){
    std::vector<std::vector<uint8_t>> matrix = {{1,1,1}, {1,1,1}, {1,1,1}};

    std::vector<coordVector> result = recursiveExploration(matrix);
    std::vector<coordVector> expected = {{coord(0, 0), coord(1, 0), coord(2, 0), coord(2, 1), coord(1, 1), coord(0, 1), coord(0, 2), coord(1, 2), coord(2, 2)}};

    ASSERT_EQ(result, expected);
}

TEST(OpenCVSolver, NormalParsing){
    std::vector<std::vector<uint8_t>> matrix = {{1,1,0,0}, {0,0,1,0}, {1,0,0,0}};
    
    std::map<unsigned int, coordVector> result = opencvSolver(matrix);
    std::map<unsigned int, coordVector> expected;
    expected[1] = coordVector();
    expected[1].push_back(coord(0, 0));
    expected[1].push_back(coord(0, 1));

    ASSERT_EQ(result.size(), 3);//It considers 1-pixel labels as well. They are then filtered in the printing.
    ASSERT_EQ(result[1], expected[1]);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}