#include <iostream>
#include <map>
using namespace std;

/**
 找出字符串的子串，满足不包含重复字符，最长长度
 */

map<char, int> mp;

int main() {
    string str;
    while (cin >> str) {
        mp.clear();
        int n = str.length();
        int len = 0, idx = -1;
        for (int i = 0, j = 0 ; i < n ; i ++) {
            while(j < n && !mp.count(str[j])) mp[str[j]] = 1, j ++;
            if (j - i > len) {
                len = j - i;
                idx = i;
            }
            mp.erase(str[i]);
        }
        cout << str.substr(idx, len) << endl;
    }
    return 0;
}
