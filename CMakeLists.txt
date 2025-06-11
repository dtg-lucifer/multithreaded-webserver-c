cmake_minimum_required(VERSION 3.14)
project(http_server C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Set include directories more explicitly
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

include(CheckIncludeFiles)
include(CheckFunctionExists)
check_include_files("sys/socket.h" HAVE_SYS_SOCKET_H)
check_include_files("netinet/in.h" HAVE_NETINET_IN_H)
check_include_files("arpa/inet.h" HAVE_ARPA_INET_H)
check_include_files("unistd.h" HAVE_UNISTD_H)
check_include_files("string.h" HAVE_STRING_H)
check_include_files("stdio.h" HAVE_STDIO_H)
check_include_files("stdlib.h" HAVE_STDLIB_H)
check_include_files("sys/types.h" HAVE_SYS_TYPES_H)
check_include_files("sys/stat.h" HAVE_SYS_STAT_H)
check_include_files("fcntl.h" HAVE_FCNTL_H)
check_include_files("pthread.h" HAVE_PTHREAD_H)
check_function_exists(socket HAVE_SOCKET)
check_function_exists(bind HAVE_BIND)
check_function_exists(listen HAVE_LISTEN)
check_function_exists(accept HAVE_ACCEPT)
check_function_exists(send HAVE_SEND)
check_function_exists(recv HAVE_RECV)
check_function_exists(close HAVE_CLOSE)
check_function_exists(pthread_create HAVE_PTHREAD_CREATE)
check_function_exists(pthread_join HAVE_PTHREAD_JOIN)
check_function_exists(pthread_mutex_init HAVE_PTHREAD_MUTEX_INIT)
check_function_exists(pthread_mutex_lock HAVE_PTHREAD_MUTEX_LOCK)
check_function_exists(pthread_mutex_unlock HAVE_PTHREAD_MUTEX_UNLOCK)
check_function_exists(pthread_mutex_destroy HAVE_PTHREAD_MUTEX_DESTROY)
check_function_exists(pthread_cond_init HAVE_PTHREAD_COND_INIT)
check_function_exists(pthread_cond_wait HAVE_PTHREAD_COND_WAIT)
check_function_exists(pthread_cond_signal HAVE_PTHREAD_COND_SIGNAL)
check_function_exists(pthread_cond_destroy HAVE_PTHREAD_COND_DESTROY)
if(NOT HAVE_SYS_SOCKET_H OR NOT HAVE_NETINET_IN_H OR NOT HAVE_ARPA_INET_H OR NOT HAVE_UNISTD_H OR
   NOT HAVE_STRING_H OR NOT HAVE_STDIO_H OR NOT HAVE_STDLIB_H OR NOT HAVE_SYS_TYPES_H OR
   NOT HAVE_SYS_STAT_H OR NOT HAVE_FCNTL_H OR NOT HAVE_PTHREAD_H)
    message(FATAL_ERROR "Required headers not found. Please ensure your system has the necessary development libraries installed.")
endif()

file(GLOB_RECURSE SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.c
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/.bin)

add_executable(server ${SOURCES})

# Add compiler flags for warnings
if(CMAKE_COMPILER_IS_GNUC OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(server PRIVATE -Wall)
endif()
