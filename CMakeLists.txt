cmake_minimum_required(VERSION 3.10)
project(Project403 VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include headers directory
include_directories(header)

# Automatically find ALL .cpp files in src/ and root
file(GLOB SOURCE_FILES "src/*.cpp" "*.cpp")

# Create executable with all found files
add_executable(Project_403 ${SOURCE_FILES})

#All of this Cmake file was made using the help of Cmake Documentation and AI
