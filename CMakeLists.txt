cmake_minimum_required(VERSION 3.16)
project(SecureVault VERSION 1.0 LANGUAGES CXX)

# Require C++17 (needed for std::chrono literals like 24s, 5s)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include/ directory so all headers are found
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect all .cpp source files
set(SOURCES
    src/main.cpp
    src/FileVault.cpp
    src/User.cpp
    src/Vault.cpp
    src/PassworkCheacker.cpp
    src/PasswordGenerator.cpp
)

# Define the executable target
add_executable(SecureVault ${SOURCES})

# Link pthread (needed for std::thread on Linux/macOS)
find_package(Threads REQUIRED)
target_link_libraries(SecureVault PRIVATE Threads::Threads)

# Make sure the data/ directory exists next to the binary after build
add_custom_command(TARGET SecureVault POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
            $<TARGET_FILE_DIR:SecureVault>/data
    COMMENT "Ensuring data/ directory exists beside the executable"
)

# Copy data/users.txt to the build output directory so the app can find it
add_custom_command(TARGET SecureVault POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/data/users.txt
            $<TARGET_FILE_DIR:SecureVault>/data/users.txt
    COMMENT "Copying data/users.txt to build directory"
)
