#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 最大命令长度
#define MAX_CMD_LEN 256

// 显示帮助信息
void display_help() {
    printf("简易文件管理系统支持以下命令：\n");
    printf("1. cp <源文件> <目标路径>    - 复制文件\n");
    printf("2. rm <文件路径>             - 删除文件\n");
    printf("3. tar -czf <压缩包名> <目录/文件> - 压缩为.tar.gz\n");
    printf("4. tar -xzf <压缩包名> -C <目标路径> - 解压.tar.gz文件\n");
    printf("5. exit                     - 退出程序\n");
}

// 命令解析器
void parse_command(const char *input) {
    char command[MAX_CMD_LEN];
    char args[MAX_CMD_LEN];

    // 分离命令和参数
    if (sscanf(input, "%s %[^\n]", command, args) < 1) {
        printf("无效命令，请输入有效命令。\n");
        return;
    }

    // 处理不同命令
    if (strcmp(command, "cp") == 0 || strcmp(command, "rm") == 0 || strncmp(command, "tar", 3) == 0) {
        char system_command[MAX_CMD_LEN];
        snprintf(system_command, sizeof(system_command), "%s %s", command, args);

        // 执行系统命令
        if (system(system_command) == 0) {
            printf("命令执行成功：%s\n", system_command);
        } else {
            printf("命令执行失败，请检查输入。\n");
        }
    } else if (strcmp(command, "exit") == 0) {
        printf("退出程序。\n");
        exit(0);
    } else {
        printf("未知命令，请输入有效命令。\n");
    }
}

// 主函数
int main() {
    char input[MAX_CMD_LEN];

    printf("欢迎使用简易文件管理系统！\n");
    display_help();

    while (1) {
        printf("\n请输入命令：");
        if (fgets(input, sizeof(input), stdin) != NULL) {
            input[strcspn(input, "\n")] = '\0'; // 去掉换行符
            parse_command(input);
        }
    }

    return 0;
}



