cmake_minimum_required(VERSION 3.16)
project(SecureVault VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    src/main.cpp
    src/FileVault.cpp
    src/User.cpp
    src/Vault.cpp
    src/PassworkCheacker.cpp
    src/PasswordGenerator.cpp
)

add_executable(SecureVault ${SOURCES})

find_package(Threads REQUIRED)
target_link_libraries(SecureVault PRIVATE Threads::Threads)

# Link stdc++fs for std::filesystem on GCC < 9
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
    target_link_libraries(SecureVault PRIVATE stdc++fs)
endif()

# Create data/ dir next to binary after build
add_custom_command(TARGET SecureVault POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:SecureVault>/data
    COMMENT "Ensuring data/ directory exists beside the executable"
)
