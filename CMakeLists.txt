cmake_minimum_required(VERSION 3.0.0)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 23)
set(VCPKG_TARGET_TRIPLET x64-windows-static-md CACHE STRING "target triplet" FORCE)
set(VCPKG_CRT_LINKAGE "dynamic" FORCE)
set(VCPKG_LINKER_FLAGS "RELEASE")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
project(greedychimp VERSION 0.1.0)

include(CTest)

enable_testing()

file(GLOB_RECURSE HEADERS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.h")
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

# file(GLOB_RECURSE WREN RELAITVE ${CMAKE_SOURCE_DIR} "C:/Users/Carter/vcpkg/packages/wren_x64-windows/include")

# Replace this with your vcpkg path.
include(C:/Users/owcar/vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui REQUIRED)
find_package(freetype CONFIG REQUIRED)
find_package(minhook CONFIG REQUIRED)

add_library(greedychimp SHARED ${SOURCES} ${HEADERS})

target_include_directories(greedychimp PRIVATE ${OPENGL_INCLUDE_DIR})
target_include_directories(greedychimp PRIVATE ${IMGUI_INCLUDE_DIR})

target_link_libraries(greedychimp PUBLIC GLEW::GLEW)
target_link_libraries(greedychimp PUBLIC ${OPENGL_LIBRARIES})
target_link_libraries(greedychimp PUBLIC glfw)
target_link_libraries(greedychimp PRIVATE freetype)
target_link_libraries(greedychimp PRIVATE imgui::imgui)
target_link_libraries(greedychimp PRIVATE minhook::minhook)

include(CPack)