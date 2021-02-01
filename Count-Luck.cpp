#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);


int n1, n2;
int d[4][2] = {{1,  0},
               {0,  1},
               {-1, 0},
               {0,  -1}};

bool dfs(const vector<string>& matrix, vector<vector<bool>>& vis, int cur, int dest, int& cnt) {
    if (cur == dest)
        return true;
    int r = cur / n2, c = cur % n2;
    vis[r][c] = true;
    int t = 0;
    vector<int> nxts;

    for (int k = 0; k < 4; ++k) {
        int rr = r + d[k][0], cc = c + d[k][1];
        if (rr >= 0 && rr < n1 && cc >= 0 && cc < n2 && !vis[rr][cc]) {
            nxts.emplace_back(rr * n2 + cc);
            ++t;
        }
    }
    if (t > 1)
        ++cnt;
    for (const int &x:nxts) {
        if (dfs(matrix, vis, x, dest, cnt))
            return true;
    }
    return false;
}

// Complete the countLuck function below.
string countLuck(vector<string> matrix, int k) {
    n1 = matrix.size();
    n2 = matrix[0].size();
    int st = 0, dest = 0;
    vector<vector<bool>> vis(n1, vector<bool>(n2, false));
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n2; ++j) {
            if (matrix[i][j] == 'M')
                st = i * n2 + j;
            else if (matrix[i][j] == '*')
                dest = i * n2 + j;
            else if (matrix[i][j] == 'X')
                vis[i][j] = true;
        }
    }
    int cnt = 0;
    if (dfs(matrix, vis, st, dest, cnt)) {
        if (cnt == k)
            return "Impressed";
    }
    return "Oops!";
}

int main()
{
//    freopen("../data.txt", "r", stdin);
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string nm_temp;
        getline(cin, nm_temp);

        vector<string> nm = split_string(nm_temp);

        int n = stoi(nm[0]);

        int m = stoi(nm[1]);

        vector<string> matrix(n);

        for (int i = 0; i < n; i++) {
            string matrix_item;
            getline(cin, matrix_item);

            matrix[i] = matrix_item;
        }

        int k;
        cin >> k;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string result = countLuck(matrix, k);

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
