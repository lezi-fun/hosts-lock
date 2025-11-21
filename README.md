# hosts-lock

为了防止我们学校某些人中午喜欢刷 Douyin（抖音），本项目提供一个简易的 hosts 管理/锁定工具，用于在指定时间段或按需将一些域名重定向到本地或无效地址，从而阻断访问。

> 仓库信息：lezi-fun/hosts-lock  
> 语言：C++（仓库语言统计显示主要为 C++）  
> 许可证：MIT

## 主要功能
- 将指定域名写入系统 hosts 文件以阻断访问（例如阻断抖音相关域名）。
- 支持备份与恢复原有 hosts 文件，安全可回滚。
- 可配合计划任务（cron / 任务计划）定时启用或解除阻断。
- 简单轻量，适合在受控环境（例如校园网）使用。

> 注意：修改系统 hosts 需要管理员权限（Linux/macOS 需要 sudo，Windows 需要管理员权限）。

## 快速开始

1. 克隆仓库
```bash
git clone https://github.com/lezi-fun/hosts-lock.git
cd hosts-lock
```

2. 编译（示例）
- 若项目使用 CMake：
```bash
mkdir build
cd build
cmake ..
make
# 生成可执行文件，例如：hosts-lock
```
- 若为单文件或简单项目，可用 g++ 编译：
```bash
g++ -O2 -o hosts-lock src/*.cpp   # 根据实际源文件路径调整
```

3. 运行（需要管理员权限）
```bash
sudo ./hosts-lock --apply  # 应用阻断规则到 /etc/hosts
sudo ./hosts-lock --restore  # 恢复备份的 hosts 文件
```

（具体可用命令请参见程序帮助：`./hosts-lock --help`）

## 配置与规则
建议在仓库里维护一个规则文件（例如 `rules.txt` 或 `hosts-block.txt`），格式可类似：
```
# hosts-block.txt
# 屏蔽抖音相关域名
127.0.0.1 douyin.com
127.0.0.1 *.douyin.com
127.0.0.1 tiktok.com
```
程序启动时可以读取此文件并将规则写入系统 hosts（写入前请先备份原 hosts）。

## 备份与恢复
- 应用前：程序会将当前系统 hosts 备份到同目录下（例如 `hosts.bak.TIMESTAMP`）。
- 恢复：提供 `--restore` 参数来将最新备份恢复到系统 hosts。

使用前请确认备份可用且位置安全。

## 与计划任务结合（示例：每天中午禁用 11:30-13:30）
编辑当前用户的 crontab：
```cron
# 每天 11:30 应用阻断
30 11 * * * /path/to/hosts-lock --apply
# 每天 13:30 恢复原 hosts
30 13 * * * /path/to/hosts-lock --restore
```
确保 crontab 中使用的可执行文件路径正确，并且 cron 任务具备足够权限（可通过运行脚本调用 sudo）。

## 常见问题
- Q：会破坏原 hosts 吗？  
  A：程序会在修改前自动备份原 hosts，请先确认备份文件存在并可恢复。

- Q：如何取消所有阻断？  
  A：运行 `--restore` 或者手动将 hosts 文件恢复到备份内容。

- Q：Windows 支持吗？  
  A：原理上支持（修改 `C:\Windows\System32\drivers\etc\hosts`），但需在 Windows 下编译或使用可执行版本，并以管理员权限运行。路径与权限需调整。

## 安全与合规
- 请确保在合法合规的范围内使用本工具。未经允许用于影响他人上网可能违反学校或公司规章。
- 建议仅在个人可控环境或经授权的场景中使用。

## 贡献
欢迎提交 issue 或 PR。贡献建议：
- 提供更完善的规则文件格式（支持域名通配、注释、分组）。
- 增加日志与更友好的 CLI 帮助信息。
- 增加 Windows 支持的构建脚本与说明。

## 许可证
本项目使用 MIT 许可证，详情见 LICENSE 文件。

## 联系
作者：lezi-fun  
仓库地址：https://github.com/lezi-fun/hosts-lock
