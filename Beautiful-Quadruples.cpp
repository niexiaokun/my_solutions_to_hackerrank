#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

long long beautifulQuadruples(int a, int b, int c, int d) {
    vector<int> nums = {a, b, c, d};
    sort(nums.begin(), nums.end());
    vector<vector<int>> cnt1(4096, vector<int>(nums[2] + 1));
    vector<int> cnt2(nums[2] + 1);
    for (int i = 1; i <= nums[2]; ++i) {
        cnt2[i] += nums[3] - i + 1;
        for (int j = i; j <= nums[3]; ++j) {
            cnt1[i ^ j][i]++;
        }
    }
    for (int i = 0; i < cnt1.size(); ++i) {
        for (int j = (int) nums[2] - 1; j >= 1; --j)
            cnt1[i][j] += cnt1[i][j + 1];
    }
    for (int i = (int) nums[2] - 1; i >= 1; --i)
        cnt2[i] += cnt2[i + 1];
    long long res = 0;
    for (int i = 1; i <= nums[0]; ++i) {
        for (int j = i; j <= nums[1]; ++j) {
            res += (long long) cnt2[j] - cnt1[i ^ j][j];
        }
    }
    return res;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));
//    freopen("../data.txt", "r", stdin);
    string abcd_temp;
    getline(cin, abcd_temp);

    vector<string> abcd = split_string(abcd_temp);

    int a = stoi(abcd[0]);

    int b = stoi(abcd[1]);

    int c = stoi(abcd[2]);

    int d = stoi(abcd[3]);

    long long result = beautifulQuadruples(a, b, c, d);

    fout << result << "\n";

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
