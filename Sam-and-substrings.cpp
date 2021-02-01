#include <bits/stdc++.h>

using namespace std;

constexpr int mod=1e9+7;
// Complete the substrings function below.
int substrings(string n) {
    vector<vector<long long>> dp(n.size(), vector<long long>(2));
    dp[0][0] = dp[0][1] = n[0] - '0';
    for (int i = 1; i < n.size(); ++i) {
        dp[i][1] = (dp[i - 1][1] * 10 + (i + 1) * (n[i] - '0')) % mod;
        dp[i][0] = (dp[i - 1][0] + dp[i][1]) % mod;
    }
    return dp.back()[0];
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n;
    getline(cin, n);

    int result = substrings(n);

    fout << result << "\n";

    fout.close();

    return 0;
}
