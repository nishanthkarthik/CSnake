project(CSnake)

find_package(Python3 COMPONENTS Development REQUIRED)

add_library(${PROJECT_NAME} PyExpr.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Python3::Python)
target_include_directories(${PROJECT_NAME} PUBLIC include)
