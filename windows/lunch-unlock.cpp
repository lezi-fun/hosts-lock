
#include <windows.h>
#include <shellapi.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    // 获取当前目录
    char path[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, path);
    
    string exePath = string(path) + "\\unlock.exe";
    
    // 检查文件是否存在
    if(GetFileAttributes(exePath.c_str()) == INVALID_FILE_ATTRIBUTES) {
        cout << "错误: 未找到 unlock.exe" << endl;
        system("pause");
        return 1;
    }
    
    cout << "正在请求管理员权限运行解锁工具..." << endl;
    
    // 以管理员权限运行程序
    SHELLEXECUTEINFO sei = { sizeof(sei) };
    sei.lpVerb = "runas"; // 请求管理员权限
    sei.lpFile = exePath.c_str();
    sei.hwnd = NULL;
    sei.nShow = SW_NORMAL;
    
    if (!ShellExecuteEx(&sei)) {
        DWORD dwError = GetLastError();
        if (dwError == ERROR_CANCELLED) {
            cout << "用户拒绝了管理员权限请求。" << endl;
        } else {
            cout << "无法启动程序，错误代码: " << dwError << endl;
        }
        system("pause");
        return 1;
    }
    
    cout << "程序已启动！" << endl;
    return 0;
}
