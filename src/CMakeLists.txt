add_library(ccl OBJECT utility.cpp solvers/recursiveExploration.cpp solvers/opencvSolver.cpp)
add_executable(AdjacentCellsChallenge $<TARGET_OBJECTS:ccl> adjCells.cpp)

target_compile_features(AdjacentCellsChallenge PUBLIC cxx_std_11)