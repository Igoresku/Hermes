cmake_minimum_required(VERSION 3.12)
project(Path_Finding)

set(CMAKE_CXX_STANDARD 14)

add_executable(Path_Finding main.cpp src/Game_Map.cpp include/Game_Map.h src/Agent.cpp include/Agent.h include/Traversal_Type.h src/Logger.cpp include/Logger.h src/Traversal_Type.cpp src/Cell.cpp include/Cell.h src/Zone.cpp include/Zone.h src/Game_Map_Master.cpp include/Game_Map_Master.h include/Runnable.h src/Runnable.cpp)