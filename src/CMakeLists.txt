file(GLOB SAURON_SOURCES *.C)

add_library(sauron SHARED ${SAURON_SOURCES})

target_include_directories(sauron
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
