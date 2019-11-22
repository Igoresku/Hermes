cmake_minimum_required(VERSION 3.12)
project(Path_Finding)

set(CMAKE_CXX_STANDARD 14)

add_executable(Path_Finding main.cpp src/Game_Map.cpp include/Game_Map.h src/Agent.cpp include/Agent.h include/Traversal_Type.h src/Logger.cpp include/Logger.h src/Traversal_Type.cpp src/Cell.cpp include/Cell.h src/Zone.cpp include/Zone.h src/Game_Map_Master.cpp include/Game_Map_Master.h include/Runnable.h src/Runnable.cpp src/Map_Abstraction_Master.cpp include/Map_Abstraction_Master.h src/Map_Creator.cpp include/Map_Creator.h src/Nonexistent_File.cpp include/Nonexistent_File.h src/Invalid_File_Format.cpp include/Invalid_File_Format.h src/Invalid_Parameters.cpp include/Invalid_Parameters.h src/Map_Abstraction.cpp include/Map_Abstraction.h src/Map_Creator_Master.cpp include/Map_Creator_Master.h)