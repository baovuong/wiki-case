cmake_minimum_required(VERSION 3.10) # Adjust version as needed
project(wiki-case C) # Replace MyGtkApp with your project name

# Find the PkgConfig module
find_package(PkgConfig REQUIRED)

# Check for GTK3
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Include GTK3 headers
include_directories(${GTK3_INCLUDE_DIRS})

# Link GTK3 libraries
link_directories(${GTK3_LIBRARY_DIRS})

# Add other compiler flags if necessary
add_definitions(${GTK3_CFLAGS_OTHER})

# Define your source files
set(SOURCE_FILES
    src/main.c
    # Add other .c files here
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link the GTK3 libraries to your executable
target_link_libraries(${PROJECT_NAME} ${GTK3_LIBRARIES})