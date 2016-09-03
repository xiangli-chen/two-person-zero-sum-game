CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(zeroSumGame)

# speed up
# ADD_DEFINITIONS(-w -O3 -Wall)

# include directory
INCLUDE_DIRECTORIES(include)

# link directory
LINK_DIRECTORIES(${CMAKE_CURRENT_LIST_DIR}/lib)

# C++11 Standard
IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  SET(CMAKE_CXX_FLAGS “${CMAKE_CXX_FLAGS} -std=gnu++11”)
ENDIF()

# executable file
ADD_EXECUTABLE(test_
	   src/test_.cpp
	   src/ZeroSumGame.cpp
)

# link library

TARGET_LINK_LIBRARIES(test_ gurobi_c++ gurobi65 blas lapack)

# use the high speed OpenBLAS library instead of BLAS
# TARGET_LINK_LIBRARIES(test_ gurobi_c++ gurobi65 openblas lapack)

# add dl if link library under line system
# TARGET_LINK_LIBRARIES(test_ gurobi_c++ gurobi65 blas lapack dl)
# TARGET_LINK_LIBRARIES(test_ gurobi_c++ gurobi65 openblas lapack dl)
