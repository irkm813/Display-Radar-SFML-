cmake_minimum_required(VERSION 3.15)

project(MySFMLProject)

set(CMAKE_CXX_STANDARD 20)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Find Boost (Ensure 'boost-system' is included for Asio)
find_package(Boost REQUIRED COMPONENTS system)

if(SFML_FOUND AND Boost_FOUND)
    include_directories(${SFML_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

    add_executable(MySFMLProject main.cpp)

    target_link_libraries(MySFMLProject sfml-graphics sfml-window sfml-system Boost::system ws2_32) 

    # Copy SFML DLLs (Windows only)
    if(WIN32)
        add_custom_command(TARGET MySFMLProject POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:sfml-graphics> $<TARGET_FILE_DIR:MySFMLProject>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:sfml-window> $<TARGET_FILE_DIR:MySFMLProject>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:sfml-system> $<TARGET_FILE_DIR:MySFMLProject>
        )
    endif()
else()
    message(FATAL_ERROR "SFML or Boost not found. Please install them.")
endif()