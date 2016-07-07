file(GLOB RENDERER_SOURCES "*.*")

add_library(Renderer STATIC ${RENDERER_SOURCES})
target_include_directories(Renderer PUBLIC ${VOXENGINE_ROOT_PATH})

target_link_libraries(Renderer Core)