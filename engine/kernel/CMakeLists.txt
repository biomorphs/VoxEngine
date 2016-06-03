file(GLOB KERNEL_SOURCES "*.cpp" "*.h")
add_library(Kernel STATIC ${KERNEL_SOURCES})

#Needs SDL2
target_include_directories(Kernel PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(Kernel ${SDL2_LIBRARY})