cmake_minimum_required(VERSION 3.16)
project(easyCAD)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
find_package(OpenGL REQUIRED)

if(NOT ${wxWidgets_FOUND})
    message("package is not found : wxWidgets")
endif()

if(NOT ${OPENGL_FOUND})
    message("package is not found : openGL")
endif()

include(${wxWidgets_USE_FILE})

include_directories(
    include/
    ${wxWidgets_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/app.cpp
    src/frame.cpp
    src/gl_plane.cpp
)

target_link_libraries(${PROJECT_NAME} 
    ${wxWidgets_LIBRARIES}
    ${OPENGL_LIBRARIES}
)
