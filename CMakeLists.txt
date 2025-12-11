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

find_program(GLIB_COMPILE_RESOURCES NAMES glib-compile-resources REQUIRED)

set(GRESOURCE_C   src/gresource.c)
set(GRESOURCE_XML gresource.xml)

add_custom_command(
    OUTPUT ${GRESOURCE_C}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${GLIB_COMPILE_RESOURCES}
    ARGS
        --generate
        --target=${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
        --c-name=wiki_case
        ${GRESOURCE_XML}
    VERBATIM
    MAIN_DEPENDENCY ${GRESOURCE_XML}
    DEPENDS
        builder.ui
)

add_custom_target(
    dummy-resource
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
)

# Define your source files
set(SOURCE_FILES
    src/main.c
    # Add other .c files here
)



# Create the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C})

set_source_files_properties(
    ${CMAKE_CURRENT_BINARY_DIR}/${GRESOURCE_C}
    PROPERTIES GENERATED TRUE
)

add_dependencies(${PROJECT_NAME} dummy-resource)

# Link the GTK3 libraries to your executable
target_link_libraries(${PROJECT_NAME} ${GTK3_LIBRARIES})