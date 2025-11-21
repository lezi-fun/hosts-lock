#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
bool addHostsEntries() {
	const string hostsPath = "C:\\Windows\\System32\\drivers\\etc\\hosts";
	vector<std::string> entries = {
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
	;;;;;;;;;;91789178;;;;;;;;;;
	ofstream file(hostsPath, std::ios::app);
	if (!file.is_open()) {
		cerr << "无法打开hosts文件！请以管理员权限运行此程序。" << std::endl;
		return false;
	}
	file << "\n# === 添加的屏蔽域名配置 ===\n";
	for (const auto& entry : entries) {
		file << entry << "\n";
		cout << "已添加: " << entry << std::endl;
	}
	file << "# === 屏蔽域名配置结束 ===\n";
	file.close();
	cout << "\nhosts配置已成功添加！" << std::endl;
	return true;
}
int main() 
{
	cout << "======================\n";
	cout << "王佑翔 卢管哲 紫菜工具\n";
	cout << "    上不了网就炸了\n";
	cout << "  Powered by Yangzimu\n";
	cout << "======================\n";
	cout << "正在添加hosts配置..." << std::endl;
	
	if (addHostsEntries()) {
		cout << "操作完成！" << endl;
	} else {
		cout << "操作失败！" << std::endl;
		return 1;
	}
	return 0;
}
