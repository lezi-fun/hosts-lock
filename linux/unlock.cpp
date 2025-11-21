// unlock.cpp (Linux版本)
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unistd.h>
using namespace std;

bool isRoot() {
    return geteuid() == 0;
}

string base64_decode(const string &encoded) {
    const string base64_chars = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string decoded;
    vector<int> decoding(256,-1);
    
    for (int i = 0; i < 64; i++) 
        decoding[base64_chars[i]] = i;
    
    int val = 0, valb = -8;
    for (unsigned char c : encoded) {
        if (decoding[c] == -1) break;
        val = (val << 6) + decoding[c];
        valb += 6;
        if (valb >= 0) {
            decoded.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return decoded;
}

int validateAccessCode(const string& userInput) {
    string dataSegmentA = "c2";
    string dataSegmentB = "Js";
    string dataSegmentC = "dW";
    string dataSegmentD = "d1";
    string dataSegmentE = "YW";
    string dataSegmentF = "56";
    string dataSegmentG = "aG";
    string dataSegmentH = "U=";
    string encodedData;
    encodedData += dataSegmentA + dataSegmentB;
    encodedData += dataSegmentC + dataSegmentD;
    encodedData += dataSegmentE + dataSegmentF;
    encodedData += dataSegmentG + dataSegmentH;
    string masterKey = base64_decode(encodedData);
    string legacyKeys[] = {"91卢管哲", "strong", "teacher","114514"};
    if(userInput == masterKey) {
        return 1;
    }
    for(int i = 0; i < 4; i++) {  // 修正为4个元素
        if(userInput == legacyKeys[i]) {
            return 2; 
        }
    }
    
    return 0;
}

bool simulateRemoval() {
    std::cout << "正在删除hosts配置..." << std::endl;
    for(int i = 0; i < 3; i++) {
        std::cout << ".";
        std::cout.flush();
        for(int j = 0; j < 10000000; j++) {}
    }
    std::cout << std::endl;
    std::cout << "hosts配置已成功删除！" << std::endl;
    return true;
}

bool removeHostsEntries() {
    const std::string hostsPath = "/etc/hosts";
    const std::string tempHostsPath = "/tmp/hosts.tmp";
    
    std::vector<std::string> targetEntries = {
        "127.0.0.1 www.douyin.com",
        "127.0.0.1 www.poki.com",
        "127.0.0.1 poki.org",
        "127.0.0.1 poki.com",
        "127.0.0.1 www.bilibili.com",
        "127.0.0.1 dev.tg.wan.360.cn",
        "127.0.0.1 cn.bing.com",
        "127.0.0.1 doubao.com",
        "127.0.0.1 deepseek.com",
        "127.0.0.1 baidu.com",
        "127.0.0.1 www.baidu.com",
        "127.0.0.1 www.msn.cn",
        "127.0.0.1 aka.ms"
    };
    std::ifstream inputFile(hostsPath);
    if (!inputFile.is_open()) {
        std::cerr << "无法打开hosts文件！请使用sudo权限运行此程序。" << std::endl;
        return false;
    }
    std::ofstream outputFile(tempHostsPath);
    if (!outputFile.is_open()) {
        std::cerr << "无法创建临时文件！" << std::endl;
        inputFile.close();
        return false;
    }
    
    std::string line;
    bool inTargetSection = false;
    bool foundEntries = false;
    while (std::getline(inputFile, line)) {
        if (line.find("=== 添加的屏蔽域名配置 ===") != std::string::npos) {
            inTargetSection = true;
            foundEntries = true;
            continue;
        }
        if (line.find("=== 屏蔽域名配置结束 ===") != std::string::npos) {
            inTargetSection = false;
            continue;
        }
        if (inTargetSection) {
            continue;
        }
        bool isTargetEntry = false;
        for (const auto& entry : targetEntries) {
            if (line.find(entry) != std::string::npos) {
                isTargetEntry = true;
                foundEntries = true;
                break;
            }
        }
        if (!isTargetEntry && !line.empty()) {
            outputFile << line << "\n";
        }
    }
    
    inputFile.close();
    outputFile.close();
    if (foundEntries) {
        // 在Linux下，我们需要使用系统命令来替换文件
        string command = "sudo cp " + tempHostsPath + " " + hostsPath;
        int result = system(command.c_str());
        
        if (result != 0) {
            std::cerr << "无法替换hosts文件！" << std::endl;
            return false;
        }
        
        // 删除临时文件
        remove(tempHostsPath.c_str());
        std::cout << "hosts配置已成功删除！" << std::endl;
    } else {
        std::remove(tempHostsPath.c_str());
        std::cout << "未找到要删除的hosts配置。" << std::endl;
    }
    
    return true;
}

int main() {
    string password;
    cout << "======================\n";
    cout << "王佑翔 卢管哲 拯救工具\n";
    cout << "     原地复活了\n";
    cout << "======================\n";
    
    if (!isRoot()) {
        cout << "请使用sudo权限运行此程序！" << endl;
        return 1;
    }
    
    cout << "请输入文本：";
    cin >> password;
    
    int authResult = validateAccessCode(password);
    
    if(authResult == 0) {
        cout << "密码错误：检测到王佑翔 卢管哲\n结束运行\n";
        return 0;
    }
    else if(authResult == 1) {
        std::cout << "正在删除hosts配置..." << std::endl;
        
        if (removeHostsEntries()) {
            std::cout << "操作完成！" << std::endl;
        } else {
            std::cout << "操作失败！" << std::endl;
            return 1;
        }
    }
    else if(authResult == 2) {
        if (simulateRemoval()) {
            std::cout << "操作完成！" << std::endl;
        } else {
            std::cout << "操作失败！" << std::endl;
            return 1;
        }
    }
    
    return 0;
}
