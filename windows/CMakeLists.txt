# Windows CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(NetworkTools_Windows)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows特定设置
if(WIN32)
    # 设置可执行文件后缀
    set(CMAKE_EXECUTABLE_SUFFIX ".exe")
    
    # 添加Windows库
    find_library(SHELL32_LIBRARY shell32)
    find_library(ADVAPI32_LIBRARY advapi32)
    
    # lock程序
    add_executable(lock lock.cpp)
    target_link_libraries(lock ${SHELL32_LIBRARY} ${ADVAPI32_LIBRARY})
    
    # unlock程序
    add_executable(unlock unlock.cpp)
    target_link_libraries(unlock ${SHELL32_LIBRARY} ${ADVAPI32_LIBRARY})
    
    # lunch-lock启动器
    add_executable(lunch-lock lunch-lock.cpp)
    target_link_libraries(lunch-lock ${SHELL32_LIBRARY} ${ADVAPI32_LIBRARY})
    
    # lunch-unlock启动器
    add_executable(lunch-unlock lunch-unlock.cpp)
    target_link_libraries(lunch-unlock ${SHELL32_LIBRARY} ${ADVAPI32_LIBRARY})
    
    # 设置输出目录
    set_target_properties(lock unlock lunch-lock lunch-unlock
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
    
    # 安装目标（可选）
    install(TARGETS lock unlock lunch-lock lunch-unlock
        RUNTIME DESTINATION bin
    )
    
else()
    message(FATAL_ERROR "This CMakeLists.txt is for Windows only!")
endif()
