cmake_minimum_required (VERSION 2.8)
project (VoxEngine)

# Project output directories
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# SDL 2
set(SDL2_ROOT_PATH "${CMAKE_SOURCE_DIR}/external/SDL2-devel-2.0.4-VC/SDL2-2.0.4")
set(SDL2_INCLUDE_DIR "${SDL2_ROOT_PATH}/include")
set(SDL2_LIBRARY "${SDL2_ROOT_PATH}/lib/x86/SDL2.lib")
set(SDL2_LIBRARY_MAIN "${SDL2_ROOT_PATH}/lib/x86/SDL2main.lib")
set(SDL2_RUNTIME_LIBRARY "${SDL2_ROOT_PATH}/lib/x86/SDL2.dll")
set(VOXENGINE_ROOT_PATH "${CMAKE_SOURCE_DIR}/engine")

# Launcher project
add_executable(Launcher launcher/main.cpp)
target_link_libraries(Launcher ${SDL2_LIBRARY})
target_link_libraries(Launcher ${SDL2_LIBRARY_MAIN})

# Copy SDL2.dll to output directory in post
add_custom_command(TARGET Launcher POST_BUILD		# Post-build event
	COMMAND ${CMAKE_COMMAND} -E copy_if_different	# execute "cmake - E copy_if_different..."
	"${SDL2_RUNTIME_LIBRARY}"						# SDL lib
	$<TARGET_FILE_DIR:Launcher>)                 	# Output directory

# Include engine projects
add_subdirectory (${VOXENGINE_ROOT_PATH}/kernel)
target_include_directories(Launcher PUBLIC ${VOXENGINE_ROOT_PATH}/kernel)
target_link_libraries(Launcher Kernel)
