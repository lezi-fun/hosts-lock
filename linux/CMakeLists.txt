# Linux CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(NetworkTools_Linux)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Linux特定设置
if(UNIX AND NOT APPLE)
    # lock程序
    add_executable(lock lock.cpp)
    
    # unlock程序
    add_executable(unlock unlock.cpp)
    
    # lunch-lock启动器
    add_executable(lunch-lock lunch-lock.cpp)
    
    # lunch-unlock启动器
    add_executable(lunch-unlock lunch-unlock.cpp)
    
    # 设置输出目录
    set_target_properties(lock unlock lunch-lock lunch-unlock
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
    
    # 设置可执行文件权限（安装时）
    install(TARGETS lock unlock lunch-lock lunch-unlock
        RUNTIME DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    )
    
    # 安装后脚本提示（可选）
    install(CODE "message(\"=== 安装完成 ===\")")
    install(CODE "message(\"使用方法：\")")
    install(CODE "message(\"  sudo ./bin/lock    - 添加hosts屏蔽\")")
    install(CODE "message(\"  sudo ./bin/unlock  - 解除hosts屏蔽\")")
    install(CODE "message(\"  ./bin/lunch-lock   - 自动请求权限运行锁定工具\")")
    install(CODE "message(\"  ./bin/lunch-unlock - 自动请求权限运行解锁工具\")")
    
else()
    message(FATAL_ERROR "This CMakeLists.txt is for Linux only!")
endif()
