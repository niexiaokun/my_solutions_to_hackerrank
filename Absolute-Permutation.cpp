#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

vector<int> nums;
bool dfs(int n, int k, int index, vector<bool>& used) {
    if (index == n + 1)
        return true;
    int i = index - k;
    if (i >= 1 && !used[i]) {
        used[i] = true;
        nums[index - 1] = i;
        if (dfs(n, k, index + 1, used))
            return true;
        used[i] = false;
    }
    i = index + k;
    if (i <= n && !used[i]) {
        used[i] = true;
        nums[index - 1] = i;
        if (dfs(n, k, index + 1, used))
            return true;
        used[i] = false;
    }
    return false;
}

// Complete the absolutePermutation function below.
vector<int> absolutePermutation(int n, int k) {
    vector<int> res(n);
    if(k == 0){
        iota(res.begin(),res.end(),1);
        return res;
    }
    if(n%k!=0||n/k%2!=0)
        return {-1};
    bool t = true;
    for(int i=0;i<n;++i){
        int j=i+1;
        if(t){
            res[i]=j+k;
        }else{
            res[i]=j-k;
        }
        if(j%k==0)
            t=!t;
    }
    return res;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string nk_temp;
        getline(cin, nk_temp);

        vector<string> nk = split_string(nk_temp);

        int n = stoi(nk[0]);

        int k = stoi(nk[1]);

        vector<int> result = absolutePermutation(n, k);

        for (int i = 0; i < result.size(); i++) {
            fout << result[i];

            if (i != result.size() - 1) {
                fout << " ";
            }
        }

        fout << "\n";
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
