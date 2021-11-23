cmake_minimum_required(VERSION 3.16)
project(easyCAD)

find_package(wxWidgets REQUIRED COMPONENTS net core base)

if(NOT ${wxWidgets_FOUND})
    message("package is not found : wxWidgets")
endif()

include(${wxWidgets_USE_FILE})

include_directories(
    include/
    ${wxWidgets_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/app.cpp
    src/frame.cpp
)

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
