file(GLOB RAY_TRACING_SOURCES *.C)

add_library(sauron SHARED ${RAY_TRACING_SOURCES})

target_include_directories(sauron
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
