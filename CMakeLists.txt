# 根目录CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(NetworkTools)

# 根据平台选择相应的子目录
if(WIN32)
    add_subdirectory(windows)
elseif(UNIX AND NOT APPLE)
    add_subdirectory(linux)
else()
    message(WARNING "Unsupported platform! Only Windows and Linux are supported.")
endif()

# 通用的安装后信息
install(CODE "message(\"===========================================\")")
install(CODE "message(\"网络管理工具安装完成\")")
install(CODE "message(\"请根据需要使用相应的可执行文件\")")
install(CODE "message(\"===========================================\")")
