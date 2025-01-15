cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(Networking)

find_package(Boost 1.77.0 REQUIRED)

# Add the library
file(GLOB SOURCES src/* src/*/* src/*/*/*)
add_library(${PROJECT_NAME} ${SOURCES})



# Specify include directories
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include>        # Correct install interface
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    ${Boost_INCLUDE_DIRS}
  PRIVATE
)

# Add the executable
add_executable(NetworkingExec src/server/TcpServer.cpp "src/server/TcpConnection.cpp" "src/client/TcpClient.cpp")

# Link the library to the executable
target_link_libraries(NetworkingExec PUBLIC ${PROJECT_NAME}

)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${Boost_LIBRARIES}    
)