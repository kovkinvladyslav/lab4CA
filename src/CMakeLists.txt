set(READER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Reader/Reader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Reader/FileReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Reader/StringReader.cpp
)

set(
    ANALYSER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Analyser/Interpreter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Analyser/Context.cpp

)

set(MEMORY_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Memory/Memory.cpp

)


set(LIB_SOURCES
    ${READER_SOURCES}
    ${ANALYSER_SOURCES}
    ${MEMORY_SOURCES}
)


add_library(${LIB_NAME} ${LIB_SOURCES})
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)
