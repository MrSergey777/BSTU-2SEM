#include <iostream>
#include <string>
using namespace std;
int search(string s, string ss) {
    int count = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ss[0]) {
            if (s.size() - i >= ss.size()) {
                bool flag = true;
                for (int j = 0; j < ss.size(); j++) {
                    if (s[i + j] != ss[j]) {
                        flag = false;
                        break;
                    }
                }
                if (flag) count++;
            }
        }
    }
    return count;
}
int search1(string s, string ss) {
    int count = 0;
    int pos = 0;
    while ((pos = s.find(ss, pos)) != string::npos) {
        count++;
        pos += ss.size();
    }
    return count;
}
int main() {
    setlocale(LC_ALL, "Ru");
    string s = "mondeyAllatusedeyAllaTheterdayAlla";
    string ss = "Alla";
    int count = search(s, ss);
    int count1 = search1(s, ss);
    cout << endl << "Всего вхождений: " << count << endl;
    cout << endl << "Всего вхождений: " << search1(s,ss) << endl;
    return 0;
}
