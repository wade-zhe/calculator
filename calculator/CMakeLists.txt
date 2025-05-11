cmake_minimum_required(VERSION 3.16)
project(calculator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Define source files
set(PROJECT_SOURCES
    src/main.cpp
    src/calculator.cpp
    include/calculator.h
)

# Create executable
qt_add_executable(calculator
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

# Include directories
target_include_directories(calculator PRIVATE include)

# Link Qt6 libraries
target_link_libraries(calculator PRIVATE Qt6::Widgets)

# Set Windows-specific properties
set_target_properties(calculator PROPERTIES
    WIN32_EXECUTABLE TRUE
)

# Install rules
include(GNUInstallDirs)
install(TARGETS calculator
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize executable for Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(calculator)
endif()
