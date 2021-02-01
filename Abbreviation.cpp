#include <bits/stdc++.h>

using namespace std;

// Complete the abbreviation function below.
string abbreviation(string a, string b) {
    int m = a.size(), n = b.size();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;
    for (int i = 1; i <= m; ++i) {
        if (islower(a[i-1]))
            dp[i][0] = dp[i - 1][0];
        for (int j = 1; j <= n; ++j) {
            if (isupper(a[i - 1])) {
                if (a[i - 1] == b[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
            } else {
                if (toupper(a[i - 1]) == b[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] || dp[i - 1][j];
                else
                    dp[i][j] = dp[i - 1][j];
            }
//            cout<<boolalpha<<a.substr(0,i)<<"  "<<b.substr(0,j)<<"  "<<dp[i][j]<<endl;
        }
    }
    return dp[m][n] ? "YES" : "NO";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string a;
        getline(cin, a);

        string b;
        getline(cin, b);

        string result = abbreviation(a, b);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
