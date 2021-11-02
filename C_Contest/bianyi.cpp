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
//д���ļ�
ofstream fout;
//����״̬
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
//����״̬ת�ƾ���
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
//������̬����
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
//������̬���ƣ�����ѡ�
void init_finalState()
{
    finalState[S1] = "ID";
    finalState[S2] = "0";
    finalState[S3] = "����";
    finalState[S4] = "�ָ���";
    finalState[S5] = "��Ŀ�����";
    finalState[S6] = "����";
    finalState[S8] = "��Ŀ�����";
    finalState[S10] = "˫Ŀ�����";
    finalState[S12] = "ע��";
}
//�ж�������ַ�����
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
//״̬ת�ƺ���
State Go_to(State now, char ch)
{
    int row = 0; // ��ǰ״̬�к�
    int col = Toint(ch);
    row = now;
    //���뵱ǰ�ַ������Ӧ����ת���к�
    return (State)a[row][col];
}
//�ж��Ƿ�Ϊ�ؼ���
bool iskeyword(string ss)
{
    for (int i = 0; i < 8; i++)
    {
        if (ss == words[i])
            return true;
    }
    return false;
}
//���Ѿ��жϳ�����Ϣ������ı���
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
            mark = "��ʶ��\t" + ans + "\n";
        else
            mark = "ID\t" + ans + "\n";
    }
    else if (now == S2)
    {
        mark = "����\t0\n";
    }
    else if (now == S3)
    {
        mark = "����\t" + ans + "\n";
    }
    else if (now == S4)
    {
        mark = "�ָ���\t" + ans + "\n";
    }
    else if (now == S5 || now == S8)
    {
        mark = "��Ŀ�����\t" + ans + "\n";
    }
    else if (now == S6)
    {
        mark = "����\t" + ans + "\n";
    }
    else if (now == S10)
    {
        mark = "˫Ŀ�����\t" + ans + "\n";
    }
    else if (now == S12)
    {
        mark = "ע��\t" + ans + "\n";
    }
    fout << mark;
}
//��������
void analyse(string ss)
{
    int len = ss.size();
    State now = S0; //������ʼ״̬
    State pre = S0; //ǰһ��״̬
    int head = 0;   //��ǵ�ǰ�����ĴʵĿ�ʼλ��
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

        //����ת������ת��״̬
        now = Go_to(now, ss[i]);
        //����״̬Ϊ��̬������ת����һ״̬Ϊ����״̬ʱ���˴��������ƥ��ԭ��
        //,��Ϊ����״̬�����ִ��
        if (is_end(now) && Go_to(now, ss[i + 1]) == ERR)
        {
            print(ss, head, i, now);
            head = i + 1;
            now = S0;
            flaghang = hang + 1;
        }
        //��ǰ״̬Ϊ����״̬
        else if (!is_end(now) && Go_to(now, ss[i + 1]) == ERR || now == ERR)
        {
            cout << "��" << flaghang << "�з�������";
            for (int j = head; j <= i; j++)
            {
                cout << ss[j];
            }
            cout << endl;
            //����ֱ�Ӷ���Ϊhead=i ���׷�����©
            head += 1;

            now = S0;
        }
    }

    //������֮��鿴�Ƿ�����©�Ĵ���
    if ((!is_end(now) && head < len))
    {
        cout << "��" << flaghang + 1 << "�з�������";
        for (int j = head; j <= len; j++)
        {
            cout << ss[j];
        }
        cout << endl;
        //����ֱ�Ӷ���Ϊhead=i ���׷�����©
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
        cout << "�ļ���ʧ��" << endl;
    }
    fout.open("lex.txt", ios::out);
    if (fout.fail())
    {
        cout << "�ļ���ʧ��" << endl;
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