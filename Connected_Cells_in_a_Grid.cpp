#include <bits/stdc++.h>

using namespace std;

int d[8][2] = {
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1},
        {1, 1},
        {1, -1},
        {-1, 1},
        {-1, -1}
};
int n1, n2;
int dfs(const vector<vector<int>>& matrix, vector<vector<bool>>& vis, int r, int c) {
    vis[r][c] = true;
    int cnt = 1;
    for (int k = 0; k < 8; ++k) {
        int rr = r + d[k][0], cc = c + d[k][1];
        if (rr >= 0 && rr < n1 && cc >= 0 && cc < n2 && !vis[rr][cc] && matrix[rr][cc] == 1)
            cnt += dfs(matrix, vis, rr, cc);
    }
    return cnt;
}

// Complete the connectedCell function below.
int connectedCell(vector<vector<int>> matrix) {
    n1 = matrix.size();
    n2 = matrix[0].size();
    vector<vector<bool>> vis(n1, vector<bool>(n2, false));
    int res = 0;
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n2; ++j) {
            if (matrix[i][j] == 1 && !vis[i][j])
                res = max(res, dfs(matrix, vis, i, j));
        }
    }
    return res;
}

int main()
{
//    freopen("../data.txt", "r", stdin);
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int m;
    cin >> m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> matrix(n);
    for (int i = 0; i < n; i++) {
        matrix[i].resize(m);

        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = connectedCell(matrix);

    fout << result << "\n";
//    cout << result << "\n";
    fout.close();

    return 0;
}
