#include <iostream>
#include <string.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>
#define Err ERR
#define KeepWordNum 8
using namespace std;
map<int, string> finalState;
int hang;
int flaghang;
bool vis[100];
//写入文件
ofstream fout;
//定义状态
enum State
{
    S0 = 0,
    S1,
    S2,
    S3,
    S4,
    S5,
    S6,
    S7,
    S8,
    S9,
    S10,
    S11,
    S12,
    ERR
};
//定义状态转移矩阵
int a[13][13] = {
    {S1, S2, S3, S4, S5, S6, S5, S7, S8, S8, ERR},
    {S1, S1, S1, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
    {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
    {ERR, S3, S3, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
    {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
    {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
    {ERR, ERR, ERR, ERR, ERR, ERR, S9, ERR, ERR, ERR, ERR},
    {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, S10, ERR, ERR},
    {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, S10, ERR, ERR},
    {S9, S9, S9, S9, S9, S9, S11, S9, S9, S9, S9},
    {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
    {S9, S9, S9, S9, S9, S12, S9, S9, S9, S9, S9},
    {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR},
};
//定义终态类型
State endState[9] = {S1, S2, S3, S4, S5, S6, S8, S10, S12};
string words[8] = {"if", "else", "for", "while", "int", "write", "read"};
bool is_end(State now)
{
    for (int i = 0; i < 9; i++)
    {
        if (now == endState[i])
        {
            return true;
        }
    }
    return false;
}
//定义终态名称（备用选项）
void init_finalState()
{
    finalState[S1] = "ID";
    finalState[S2] = "0";
    finalState[S3] = "数字";
    finalState[S4] = "分隔符";
    finalState[S5] = "单目运算符";
    finalState[S6] = "除号";
    finalState[S8] = "单目运算符";
    finalState[S10] = "双目运算符";
    finalState[S12] = "注释";
}
//判断输入的字符类型
int Toint(char ch)
{
    if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
        return 0;
    else if (ch == '0')
        return 1;
    else if (ch >= '1' && ch <= '9')
        return 2;
    else if (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == ';' || ch == ',')
        return 3;
    else if (ch == '+' || ch == '-')
        return 4;
    else if (ch == '/')
        return 5;
    else if (ch == '*')
        return 6;
    else if (ch == '!')
        return 7;
    else if (ch == '=')
        return 8;
    else if (ch == '<' || ch == '>')
        return 9;
    else
        return 10;
}
//状态转移函数
State Go_to(State now, char ch)
{
    int row = 0; // 求当前状态行号
    int col = Toint(ch);
    row = now;
    //读入当前字符，求得应该跳转的列号
    return (State)a[row][col];
}
//判断是否为关键字
bool iskeyword(string ss)
{
    for (int i = 0; i < 8; i++)
    {
        if (ss == words[i])
            return true;
    }
    return false;
}
//将已经判断出的信息输出到文本内
void print(string ss, int head, int end, State now)
{
    string ans;
    string mark;
    for (int i = head; i <= end; i++)
    {
        ans += ss[i];
    }
    if (now == S1)
    {
        if (iskeyword(ans))
            mark = "标识符\t" + ans + "\n";
        else
            mark = "ID\t" + ans + "\n";
    }
    else if (now == S2)
    {
        mark = "数字\t0\n";
    }
    else if (now == S3)
    {
        mark = "数字\t" + ans + "\n";
    }
    else if (now == S4)
    {
        mark = "分隔符\t" + ans + "\n";
    }
    else if (now == S5 || now == S8)
    {
        mark = "单目运算符\t" + ans + "\n";
    }
    else if (now == S6)
    {
        mark = "除号\t" + ans + "\n";
    }
    else if (now == S10)
    {
        mark = "双目运算符\t" + ans + "\n";
    }
    else if (now == S12)
    {
        mark = "注释\t" + ans + "\n";
    }
    fout << mark;
}
//分析函数
void analyse(string ss)
{
    int len = ss.size();
    State now = S0; //设置起始状态
    State pre = S0; //前一个状态
    int head = 0;   //标记当前分析的词的开始位置
    char ch;
    for (int i = 0; i < len; i++)
    {
        ch = ss[i];
        if (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t')
        {
            if (ch == '\n')
            {
                hang += 1;
            }
            if (head == i)
            {
                head += 1;
            }
            continue;
        }

        //根据转换矩阵转换状态
        now = Go_to(now, ss[i]);
        //若此状态为终态，但跳转到下一状态为错误状态时（此处运用了最长匹配原则）
        //,不为错误状态则继续执行
        if (is_end(now) && Go_to(now, ss[i + 1]) == ERR)
        {
            print(ss, head, i, now);
            head = i + 1;
            now = S0;
            flaghang = hang + 1;
        }
        //当前状态为错误状态
        else if (!is_end(now) && Go_to(now, ss[i + 1]) == ERR || now == ERR)
        {
            cout << "第" << flaghang << "行发生错误：";
            for (int j = head; j <= i; j++)
            {
                cout << ss[j];
            }
            cout << endl;
            //不能直接定义为head=i 容易发生遗漏
            head += 1;

            now = S0;
        }
    }

    //遍历完之后查看是否有遗漏的错误
    if ((!is_end(now) && head < len))
    {
        cout << "第" << flaghang + 1 << "行发生错误：";
        for (int j = head; j <= len; j++)
        {
            cout << ss[j];
        }
        cout << endl;
        //不能直接定义为head=i 容易发生遗漏
        head += 1;

        now = S0;
    }
}

int main()
{
    ifstream fin;
    fin.open("code.txt");
    if (fin.fail())
    {
        cout << "文件打开失败" << endl;
    }
    fout.open("lex.txt", ios::out);
    if (fout.fail())
    {
        cout << "文件打开失败" << endl;
    }
    hang = 0;
    // stringstream buffer;
    // buffer << fin.rdbuf();
    // string ss(buffer.str());
    string ss;
    while (getline(fin, ss))
    {
        analyse(ss);
    }

    fin.close();
    fout.close();
    getchar();
    return 0;
}