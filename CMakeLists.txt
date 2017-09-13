cmake_minimum_required( VERSION 2.6 FATAL_ERROR )
project(Taquin)

IF (WIN32)
    set(CMAKE_CXX_FLAGS "")
ELSE (WIN32)
    set(CMAKE_CXX_FLAGS "-g3 -W -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "-g3 -W -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -W -Wall -Wextra")
ENDIF (WIN32)


IF (${CMAKE_SYSTEM_NAME} MATCHES Linux)
	find_package( Boost COMPONENTS regex signals FATAL_ERROR)
ELSE()
	SET (Boost_LIBRARY_DIRS "C:\\boost\\stage\\lib")
	SET (Boost_INCLUDE_DIRS "C:\\boost")
ENDIF()
link_directories ( ${Boost_LIBRARY_DIRS} )

include_directories (${Boost_INCLUDE_DIRS})

SET (CMAKE_BUILD_TYPE Debug)

IF (NLOG MATCHES "enable")
  ADD_DEFINITIONS(-DNLOG=log)
ENDIF()

SET (SOURCES
    main.cpp
    Parser.cpp
    )
SET (HEADERS
    BasicHeuristic.hpp
    Heuristic.hpp
    AStar.hpp
    State.hpp
    )
SET (EXECUTABLE_NAME
    taquin
    )
SOURCE_GROUP (Headers  FILES AStar.hpp State.hpp)
add_executable (
    ${EXECUTABLE_NAME}
    ${SOURCES}
    ${HEADERS}
    )
target_link_libraries (
    ${EXECUTABLE_NAME}
    ${Boost_LIBRARIES}
    )
