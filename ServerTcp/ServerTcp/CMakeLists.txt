# CMakeList.txt : CMake project for ServerTcp, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (ServerTcp "ServerTcp.cpp" "ServerTcp.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ServerTcp PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_include_directories(${PROJECT_NAME}
  PUBLIC
 Networking	
)


# Link the library to the executable
target_link_libraries(${PROJECT_NAME} PUBLIC Networking)


