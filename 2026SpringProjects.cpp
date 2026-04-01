#define NOMINMAX
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <iomanip>

#include <limits>
#include <conio.h>   //_getch()函数
#include <chrono>    //计算时间， auto start_time = std::chrono::high_resolution_clock::now(); 高分辨率时钟
#include <ctime>     // 用于 srand(time(0)) 随机数
#include <windows.h> //颜色 和 控制台权限   GetStdHandle(STD_OUTPUT_HANDLE);                        拿到控制台权限
                                          //SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);    改变颜色
                                          //GetConsoleScreenBufferInfo(hConsole, &consoleInfo);     获取当前状态



struct GameStats {
    int total_games = 0;
    double best_wpm = 0.0;
    double average_wpm = 0.0;
    double best_accuracy = 0.0;
    double average_accuracy = 0.0;
    void update_stats(double wpm, double accuracy) {
        total_games++;
        if (wpm > best_wpm) best_wpm = wpm;
        if (accuracy > best_accuracy) best_accuracy = accuracy;
        average_wpm = ((average_wpm * (total_games - 1)) + wpm) / total_games;
        average_accuracy = ((average_accuracy * (total_games - 1)) + accuracy) / total_games;
    }
};


class TypingGameApp {
private:
    std::map<std::string, std::string> users;  //名字和密码
    std::map<std::string, GameStats> user_stats;  //名字和状态
    std::string current_user = "";

    const std::map<std::string, std::vector<std::string>> sentences_by_difficulty = {
        {"easy", {
            "hello world",
            "the quick brown fox jumps over the lazy dog",
            "a journey of a thousand miles begins with a single step",
            "to be or not to be that is the question",
            "all that glitters is not gold"
        }},
        {"medium", {
            "The beauty of the sunset was breathtaking.",
            "Programming requires patience and logical thinking.",
            "She opened the book and started reading immediately.",
            "Success is often built on failure, frustration, and sometimes tragedy.",
            "The cat sat on the windowsill, watching the rain."
        }},
        {"hard", {
            "The juxtaposition of her profound silence and his voluble chatter was striking.",
            "In the ephemeral nature of life, we must find our own enduring meaning.",
            "The labyrinthine corridors of the old mansion held secrets untold.",
            "Her perspicacious observations cut through the veil of obfuscation.",
            "The zeitgeist of the era was one of cautious optimism."
        }}
    };

    std::string trim(const std::string& str) {  //去掉字符串两边的空白
        size_t start = str.find_first_not_of(" \t\n\r");
        if (start == std::string::npos) return "";
        size_t end = str.find_last_not_of(" \t\n\r");
        return str.substr(start, end - start + 1);
    }

    void clearScreen() {
        system("cls");  //清屏操作
    }

public:
    void initialize() {
        loadUsers();
        loadUserStats();
    }

    void loadUsers() {
        std::ifstream file("users.txt");
        if (!file.is_open()) {
            std::cout << "注意: 用户文件 users.txt 不存在，将创建新文件。\n";
            return;
        }
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            std::istringstream iss(line);
            std::string username, password;
            if (std::getline(iss, username, ',') && std::getline(iss, password)) { //","之前的存进username  之后的存进password
                users[trim(username)] = trim(password);  //user是一个map
            }
        }
        file.close();
    }


    void saveUsers() {
        std::ofstream file("users.txt");
        if (!file.is_open()) {
            std::cerr << "错误: 无法写入 users.txt 文件!\n";
            return;
        }
        for (const auto& pair : users) {
            file << pair.first << "," << pair.second << "\n";
        }
        file.close();
    }

    
    void loadUserStats() {  //加载，把内容  从硬件读取到内存
        std::ifstream file("user_stats.txt");
        if (!file.is_open()) {
            std::cout << "注意: 统计文件 user_stats.txt 不存在，将创建新文件。\n";
            return;
        }
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            std::istringstream iss(line);
            std::string username, tgames_str, bwpm_str, awpm_str, bacc_str, aacc_str;
            if (std::getline(iss, username, ',') &&
                std::getline(iss, tgames_str, ',') &&
                std::getline(iss, bwpm_str, ',') &&
                std::getline(iss, awpm_str, ',') &&
                std::getline(iss, bacc_str, ',') &&
                std::getline(iss, aacc_str, ',')) {
                try {
                    GameStats stats; //新建一个GameStats对象
                    stats.total_games = std::stoi(tgames_str);
                    stats.best_wpm = std::stod(bwpm_str);
                    stats.average_wpm = std::stod(awpm_str);
                    stats.best_accuracy = std::stod(bacc_str);
                    stats.average_accuracy = std::stod(aacc_str);
                    user_stats[trim(username)] = stats;  //将名字与状态配对
                }
                catch (...) {
                    continue;
                }
            }
        }
        file.close();
    }

    void saveUserStats() {  //保存，把内容  从内存保存到硬件
        std::ofstream file("user_stats.txt");
        if (!file.is_open()) {
            std::cerr << "错误: 无法写入 user_stats.txt 文件!\n";
            return;
        }
        for (const auto& pair : user_stats) {  //清空所有内容，再写入最新的内容
            const auto& s = pair.second;
            file << pair.first << "," << s.total_games << "," << s.best_wpm << ","
                << s.average_wpm << "," << s.best_accuracy << "," << s.average_accuracy << "\n";
        }
        file.close();
    }

    

    void printColoredText(const std::string& target, const std::string& input) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  //获取控制台输出句柄（HANDLE），相当于拿到控制台的“操作权限”。
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo; //一个结构体，用来保存控制台当前的所有状态信息（颜色、光标位置、大小等）。
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo); //把当前控制台的状态信息保存到 consoleInfo 中。
        WORD saved_attributes = consoleInfo.wAttributes;  //把当前的文字颜色属性（前景色、背景色等）保存起来，后面要还原用。

        for (size_t i = 0; i < target.length(); ++i) {
            char target_char = target[i];
            char input_char = (i < input.length()) ? input[i] : ' ';
            SetConsoleTextAttribute(hConsole, (target_char == input_char) ? FOREGROUND_GREEN : FOREGROUND_RED); 
            //SetConsoleTextAttribute()：设置控制台接下来的输出颜色
            
            std::cout << target_char;
        }

        if (input.length() > target.length()) {  //多余的内容也是红色
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            for (size_t i = target.length(); i < input.length(); ++i) {
                std::cout << input[i];
            }
        }

        SetConsoleTextAttribute(hConsole, saved_attributes);  // 始终重置颜色
        std::cout << std::endl;
    }



    void run() {
        initialize();
        clearScreen();  // 程序启动时先清屏
        while (true) {
            if (current_user.empty()) {
                int choice = displayMainMenu();
                switch (choice) {
                case 1: handleLogin(); break;
                case 2: handleSignup(); break;
                case 3: return;
                default: std::cout << "无效选项，请重新选择。\n"; break;
                }
            }
            else {
                int choice = displayLoggedInMenu();
                switch (choice) {
                case 1: startTypingTest(); break;
                case 2: showUserStats(); break;
                case 3: logout(); break;
                case 4: return;
                default: std::cout << "无效选项，请重新选择。\n"; break;
                }
            }
        }
    }

private:
    int displayMainMenu() {
        std::cout << "\n=== 欢迎来到打字练习游戏 ===\n";
        std::cout << "1. 登录\n";
        std::cout << "2. 注册\n";
        std::cout << "3. 退出\n";
        std::cout << "请选择操作 (1-3): ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return choice;
    }

    int displayLoggedInMenu() {
        std::cout << "\n=== 用户: " << current_user << " ===\n";
        std::cout << "1. 开始打字测试\n";
        std::cout << "2. 查看历史记录\n";
        std::cout << "3. 退出登录\n";
        std::cout << "4. 退出程序\n";
        std::cout << "请选择操作 (1-4): ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //清空输入缓冲区中当前行剩余的所有内容
        return choice;
    }

    void handleSignup() {
        std::cout << "请输入新用户名: ";
        std::string new_username;
        std::getline(std::cin, new_username);
        new_username = trim(new_username);

        if (users.find(new_username) != users.end()) {
            std::cout << "错误: 用户名已存在！\n";
        }
        else {
            std::cout << "请输入新密码: ";
            std::string new_password;
            std::getline(std::cin, new_password);
            new_password = trim(new_password);
            users[new_username] = new_password;
            saveUsers();
            std::cout << "注册成功！\n";
        }
        std::cout << "按任意键继续...";
        _getch();  //起到一个停滞作用
        clearScreen();
    }

    void handleLogin() {
        std::cout << "请输入用户名: ";
        std::string username;
        std::getline(std::cin, username);
        username = trim(username);

        std::cout << "请输入密码: ";
        std::string password;
        std::getline(std::cin, password);
        password = trim(password);

        if (users.count(username) && users[username] == password) { 
            current_user = username;
            if (user_stats.find(current_user) == user_stats.end()) { //如果在user_stats里面没有找到current_user,那么创建一个空的GameStats
                user_stats[current_user] = GameStats();
            }
            std::cout << "登录成功！欢迎, " << current_user << "!\n";
        }
        else {
            std::cout << "用户名或密码错误！\n";
        }
        std::cout << "按任意键继续...";
        _getch();
        clearScreen();
    }

    void logout() {
        current_user = "";
        std::cout << "注销成功。\n";
        std::cout << "按任意键继续...";
        _getch();
        clearScreen();
    }



    ///////


    // 【修复点2】重写输入循环 + Backspace 正常工作
    void startTypingTest() {
        std::string difficulty;
        do {
            std::cout << "请选择难度 (easy, medium, hard): ";
            std::getline(std::cin, difficulty);
        } while (difficulty != "easy" && difficulty != "medium" && difficulty != "hard");

        const auto& sentence_pool = sentences_by_difficulty.at(difficulty);
        const std::string& target_sentence = sentence_pool[rand() % sentence_pool.size()];

        std::cout << "\n请准确输入以下句子，完成后按回车:\n";
        std::cout << "\"" << target_sentence << "\"\n";

        auto start_time = std::chrono::high_resolution_clock::now();
        std::string user_input = "";
        char ch;

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        WORD original_attributes = consoleInfo.wAttributes;

        while (true) {
            ch = _getch();
            if (ch == '\r') {  //回车键
                std::cout << std::endl;
                break;
            }
            if (ch == '\b') {  //退格键
                if (!user_input.empty()) {
                    user_input.pop_back();
                    std::cout << "\b \b";
                }
                continue;
            }

            user_input += ch;
            size_t pos = user_input.length() - 1;
            if (pos < target_sentence.length()) {
                SetConsoleTextAttribute(hConsole, (target_sentence[pos] == ch) ? FOREGROUND_GREEN : FOREGROUND_RED);
            }
            else {  //超出原文
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            }
            std::cout << ch;
        }

        SetConsoleTextAttribute(hConsole, original_attributes); //恢复颜色

        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        double time_seconds = static_cast<double>(duration.count()) / 1000.0;

        // 计算统计数据（修复 accuracy 逻辑）
        int correct_chars = 0;
        int total_chars_to_match = static_cast<int>(target_sentence.length());
        int min_len = std::min(static_cast<int>(target_sentence.length()), static_cast<int>(user_input.length()));
        for (int i = 0; i < min_len; ++i) {
            if (target_sentence[i] == user_input[i]) {
                correct_chars++;
            }
        }

        double accuracy = (total_chars_to_match > 0) ? (static_cast<double>(correct_chars) / total_chars_to_match) * 100.0 : 0.0;
        double wpm = (time_seconds > 0) ? (static_cast<double>(correct_chars) / 5.0) / (time_seconds / 60.0) : 0.0;

        std::cout << "\n--- 结果 ---\n";
        std::cout << "原文: ";
        printColoredText(target_sentence, user_input);
        std::cout << "\n";
        std::cout << "正确字符数: " << correct_chars << "/" << total_chars_to_match << "\n";
        std::cout << "准确率: " << std::fixed << std::setprecision(2) << accuracy << "%\n";
        std::cout << "用时: " << std::fixed << std::setprecision(2) << time_seconds << " 秒\n";
        std::cout << "速度: " << std::fixed << std::setprecision(2) << wpm << " WPM\n";

        user_stats[current_user].update_stats(wpm, accuracy);
        saveUserStats();

        // 【修复点1】测试结束后清屏
        std::cout << "\n按任意键返回菜单...";
        _getch();
        clearScreen();
    }

    void showUserStats() {
        auto it = user_stats.find(current_user);
        if (it == user_stats.end() || it->second.total_games == 0) {
            std::cout << "暂无历史记录。\n";
        }
        else {
            const auto& stats = it->second;
            std::cout << "\n--- " << current_user << " 的历史记录 ---\n";
            std::cout << "总游戏次数: " << stats.total_games << "\n";
            std::cout << "最高WPM: " << std::fixed << std::setprecision(2) << stats.best_wpm << "\n";
            std::cout << "平均WPM: " << std::fixed << std::setprecision(2) << stats.average_wpm << "\n";
            std::cout << "最高准确率: " << std::fixed << std::setprecision(2) << stats.best_accuracy << "%\n";
            std::cout << "平均准确率: " << std::fixed << std::setprecision(2) << stats.average_accuracy << "%\n";
        }
        std::cout << "\n按任意键返回菜单...";
        _getch();
        clearScreen();
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));
    TypingGameApp app;
    app.run();
    return 0;
}
