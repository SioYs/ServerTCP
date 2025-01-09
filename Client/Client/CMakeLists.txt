# CMakeList.txt : CMake project for Client, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Client "Client.cpp" "Client.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Client PROPERTY CXX_STANDARD 20)
endif()


target_include_directories(${PROJECT_NAME}
  PUBLIC
 Networking	
)


# Link the library to the executable
target_link_libraries(${PROJECT_NAME} PUBLIC Networking)


# TODO: Add tests and install targets if needed.
