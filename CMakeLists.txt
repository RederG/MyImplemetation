cmake_minimum_required(VERSION 3.30)

project(CreatingMyImplemetation)

set(TestAppName test)

add_executable(${TestAppName})

file(GLOB_RECURSE MINE_IMPLEMETATION
    "src/MyImplemetation/*.c"
    "src/tool.c"
)

target_sources(${TestAppName} PUBLIC src/main.c src/test/vehicle.c)
target_link_libraries(${TestAppName} PUBLIC MyImplemetation)

add_library(MyImplemetation ${MINE_IMPLEMETATION})