#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// b表示模式串，m表示模式串的长度
vector<int> getNexts(string b) {
    vector<int> next(b.size());
    next[0] = -1;
    int k = -1;
    for (int i = 1; i < b.size(); ++i) {
        while (k != -1 && b[k + 1] != b[i]) {
            k = next[k];
        }
        if (b[k + 1] == b[i]) {
            ++k;
        }
        next[i] = k;
    }
    return next;
}
// a, b分别是主串和模式串；n, m分别是主串和模式串的长度。
vector<int> kmp(string& a, string& b, const vector<int>& next) {
    int n = a.size(), m = b.size();
    int j = 0;
    vector<int> res;
    for (int i = 0; i < n; ++i) {
        while (j > 0 && a[i] != b[j]) { // 一直找到a[i]和b[j]
            j = next[j - 1] + 1;
        }
        if (a[i] == b[j]) {
            ++j;
        }
        if (j == m) { // 找到匹配模式串的了
            res.emplace_back(i - m + 1);
            j = next[j - 1] + 1;
        }
    }
    return res;
}

string gridSearch(vector<string> G, vector<string> P) {
    int m1 = G.size();
    int m2 = P.size();
    int i2 = 0;
    vector<int> next = getNexts(P[0]);

    for (int i1 = 0; i1 + m2 <= m1; ++i1) {
        vector<int> p = kmp(G[i1], P[i2], next);
        if (p.empty())
            continue;
        for (int i = 0; i < p.size(); ++i) {
            bool flag = true;
            for (int j = 1; j < m2; ++j) {
                if (G[j + i1].substr(p[i], P[j].size()) != P[j]) {
                    flag = false;
                    break;
                }
            }
            if (flag)
                return "YES";
        }
    }
    return "NO";
}
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string RC_temp;
        getline(cin, RC_temp);

        vector<string> RC = split_string(RC_temp);

        int R = stoi(RC[0]);

        int C = stoi(RC[1]);

        vector<string> G(R);

        for (int i = 0; i < R; i++) {
            string G_item;
            getline(cin, G_item);

            G[i] = G_item;
        }

        string rc_temp;
        getline(cin, rc_temp);

        vector<string> rc = split_string(rc_temp);

        int r = stoi(rc[0]);

        int c = stoi(rc[1]);

        vector<string> P(r);

        for (int i = 0; i < r; i++) {
            string P_item;
            getline(cin, P_item);

            P[i] = P_item;
        }

        string result = gridSearch(G, P);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
