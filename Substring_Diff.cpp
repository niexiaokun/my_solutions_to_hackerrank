#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

bool check(const vector<vector<int>>& dp, int m, int n, int x, int k) {
    for (int i = x; i <= m; ++i) {
        for (int j = x; j <= n; ++j) {
            if (dp[i][j] - dp[i - x][j - x] <= k) {
                return true;
            }
        }
    }
    return false;
}

// Complete the substringDiff function below.
// 思路 二分查找
int substringDiff(int k, string s1, string s2) {
    int m = s1.size();
    int n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    // dp[i][j] 表示长度 为 i 和 j 的子串的不同字符数
    // eg. tabriz torino  dp[0][0] = 0, dp[0][1] = 0, dp[1][1] = 0, dp[1][2] = 1, dp[2][1] = 1, dp[2][2] = 1
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] != s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = dp[i - 1][j - 1];
        }
    }

    int lo = 0;
    int hi = min(m, n);
    while (lo < hi) {
        int x = (lo + hi) / 2;
        if (check(dp, m, n, x, k))
            lo = x + 1;
        else
            hi = x;
    }
    // lo 最终表示 upper_bound 值, 需要减去 1
    // 本来想法是直接得到 lower_bound 值, 但实现有问题就没有细究
    if (lo == min(m, n))
        return lo;
    return lo - 1;
}


int main()
{
//    freopen("../data.txt", "r", stdin);
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string kS1S2_temp;
        getline(cin, kS1S2_temp);

        vector<string> kS1S2 = split_string(kS1S2_temp);

        int k = stoi(kS1S2[0]);

        string s1 = kS1S2[1];

        string s2 = kS1S2[2];

        int result = substringDiff(k, s1, s2);

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
