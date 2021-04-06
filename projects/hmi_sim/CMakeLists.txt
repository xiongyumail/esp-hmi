cmake_minimum_required(VERSION 3.10)
project(lvgl)
set(CMAKE_C_STANDARD 11)#C11
set(CMAKE_CXX_STANDARD 17)#C17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LVGL_DIR "../hmi/components/lvgl")
set(GUI_DIR "../hmi/main/gui")

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR} ${LVGL_DIR} ${LVGL_DIR}/lvgl ${LVGL_DIR}/lvgl/src/lv_font ${LVGL_DIR}/lv_examples ${GUI_DIR} ${GUI_DIR}/generated ${GUI_DIR}/generated/guider_fonts)

file(GLOB_RECURSE INCLUDES "lv_drivers/*.h" "${LVGL_DIR}/*.h" "${LVGL_DIR}/*.h" "${GUI_DIR}/*.h" "./*h")
file(GLOB_RECURSE SOURCES  "lv_drivers/*.c" "${LVGL_DIR}/*.c" "${GUI_DIR}/*.c")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 

find_package(SDL2 REQUIRED SDL2)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(main main.c ${SOURCES} ${INCLUDES} )
target_link_libraries(main PRIVATE SDL2 )
add_custom_target (run COMMAND ${EXECUTABLE_OUTPUT_PATH}/main)
