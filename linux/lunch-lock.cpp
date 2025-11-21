// lunch-lock.cpp (Linux版本)
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>

using namespace std;

bool fileExists(const string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

int main() {
    // 获取当前目录
    char path[1024];
    if (getcwd(path, sizeof(path)) == NULL) {
        cout << "错误: 无法获取当前目录" << endl;
        return 1;
    }
    
    string exePath = string(path) + "/lock";
    
    // 检查文件是否存在
    if (!fileExists(exePath)) {
        cout << "错误: 未找到 lock 可执行文件" << endl;
        cout << "请按Enter键继续..." << endl;
        cin.get();
        return 1;
    }
    
    cout << "正在请求root权限运行锁定工具..." << endl;
    
    // 使用sudo运行程序
    string command = "sudo " + exePath;
    int result = system(command.c_str());
    
    if (result != 0) {
        cout << "权限请求失败或用户取消了操作。" << endl;
        cout << "请按Enter键继续..." << endl;
        cin.get();
        return 1;
    }
    
    cout << "程序已启动！" << endl;
    return 0;
}
