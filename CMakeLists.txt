cmake_minimum_required(VERSION 4.1.1)

project(Simple-Drawing VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick)

set(SOURCES
    resources.qrc
    
    src/main.cpp
    src/Canvas/CanvasManager/CanvasManager.cpp
    src/Canvas/CanvasItem/CanvasItem.cpp
    src/GraphicObject/GraphicObject.cpp
    src/GraphicObject/LineObject/LineObject.cpp
)

set(HEADERS
    src/Canvas/CanvasManager/CanvasManager.h
    src/Canvas/CanvasItem/CanvasItem.h
    src/GraphicObject/GraphicObject.h
    src/GraphicObject/LineObject/LineObject.h
)

add_executable(Simple-Drawing ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
    Qt6::Core 
    Qt6::Quick
)
