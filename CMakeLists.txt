cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 20)
project(glprac)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(unofficial-openfbx CONFIG REQUIRED)
find_package(libdeflate CONFIG REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${sources} ${headers})

target_link_libraries(glprac PRIVATE glfw)
target_link_libraries(glprac PRIVATE glad::glad)
target_link_libraries(glprac PRIVATE imgui::imgui)
target_link_libraries(glprac PRIVATE glm::glm)
target_link_libraries(glprac PRIVATE assimp::assimp)
target_link_libraries(glprac PRIVATE unoffical::openfbx::openfbx)
target_link_libraries(glprac PRIVATE $<IF:$<TARGET_EXISTS:libdeflate::libdeflate_shared>,libdeflate::libdeflate_shared,libdeflate::libdeflate_static>)
target_include_directories(glprac PRIVATE ${Stb_INCLUDE_DIR})

