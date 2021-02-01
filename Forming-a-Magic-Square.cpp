#include <bits/stdc++.h>

using namespace std;

vector<vector<vector<int>>> magicSquare;
vector<bool> used;
void dfs(int pos, vector<vector<int>>& square) {
    if (pos == 9) {
        magicSquare.push_back(square);
        return;
    }
    int r = pos / 3, c = pos % 3;
    for (int i = 1; i <= 9; ++i) {
        if (used[i - 1])
            continue;
        if (c == 2 && square[r][0] + square[r][1] + i != 15)
            continue;
        if (r == 2 && square[0][c] + square[1][c] + i != 15)
            continue;
        if (r == 2 && c == 0 && square[0][2] + square[1][1] + i != 15)
            continue;
        if (r == 2 && c == 2 && square[0][0] + square[1][1] + i != 15)
            continue;
        square[r][c] = i;
        used[i - 1] = true;
        dfs(pos + 1, square);
        square[r][c] = 0;
        used[i - 1] = false;
    }
}
void solveMagicSquare() {

    used.resize(9, false);
    vector<vector<int>> square(3, vector<int>(3));
    dfs(0, square);
}

// Complete the formingMagicSquare function below.
int formingMagicSquare(vector<vector<int>> s) {
    solveMagicSquare();
    int res = INT_MAX;
    for (const auto &x:magicSquare) {
        int t = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j)
                t += abs(x[i][j] - s[i][j]);
        }
        res = min(res, t);
    }
    return res;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<vector<int>> s(3);
    for (int i = 0; i < 3; i++) {
        s[i].resize(3);

        for (int j = 0; j < 3; j++) {
            cin >> s[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = formingMagicSquare(s);

    fout << result << "\n";

    fout.close();

    return 0;
}


