#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the playWithWords function below.
 */
int playWithWords(string s) {
    int n=s.size();
    vector<vector<int>> dp(n, vector<int>(n));
    for(int i=0;i<n;++i)
        dp[i][i]=1;
    for(int t=2;t<=n;++t){
        for(int i=0;i+t<=n;++i){
            int j=i+t-1;
            if(s[i]==s[j]){
                if(t==2)
                    dp[i][j]=2;
                else{
                    dp[i][j]=dp[i+1][j-1]+2;
                }
            }
            dp[i][j]=max(dp[i][j], max(dp[i+1][j], dp[i][j-1]));
        }
    }
    int res=0;
    for(int i=0;i<n;++i){
        for(int j=i-1;j>0;--j)
            res=max(res, dp[j][i]*dp[0][j-1]);
    }
    return res;
}

int main()
{
//    freopen("../data.txt", "r", stdin);
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    int result = playWithWords(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
