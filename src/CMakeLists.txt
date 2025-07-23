file(GLOB RAY_TRACING_SOURCES *.C)

add_library(ray_tracing_sources SHARED ${RAY_TRACING_SOURCES})

target_include_directories(ray_tracing_sources
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
