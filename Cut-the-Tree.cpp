#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'cutTheTree' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY data
 *  2. 2D_INTEGER_ARRAY edges
 */

int sum = 0, res = INT_MAX;
int dfs(const vector<vector<pair<int,int>>>& g, vector<bool>& vis, int x, int cnt) {
    vis[x] = true;
    int t = cnt;
    for (const auto &p:g[x]) {
        if (!vis[p.first]) {
            t += dfs(g, vis, p.first, p.second);
        }
    }
    res = min(res, abs(sum - t * 2));
    return t;
}

int cutTheTree(vector<int> data, vector<vector<int>> edges) {
    int n = data.size();
    sum = accumulate(data.begin(), data.end(), 0);
    vector<vector<pair<int, int>>> g(n);
    for (const vector<int> &v:edges) {
        int a = v[0] - 1, b = v[1] - 1;
        g[a].emplace_back(make_pair(b, data[b]));
        g[b].emplace_back(make_pair(a, data[a]));
    }
    vector<bool> vis(n, false);
    dfs(g, vis, 0, data[0]);
    return res;
}

int main()
{
//    freopen("../data.txt", "r", stdin);
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string data_temp_temp;
    getline(cin, data_temp_temp);

    vector<string> data_temp = split(rtrim(data_temp_temp));

    vector<int> data(n);

    for (int i = 0; i < n; i++) {
        int data_item = stoi(data_temp[i]);

        data[i] = data_item;
    }

    vector<vector<int>> edges(n - 1);

    for (int i = 0; i < n - 1; i++) {
        edges[i].resize(2);

        string edges_row_temp_temp;
        getline(cin, edges_row_temp_temp);

        vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int edges_row_item = stoi(edges_row_temp[j]);

            edges[i][j] = edges_row_item;
        }
    }

    int result = cutTheTree(data, edges);

    fout << result << "\n";
//    cout << result << "\n";
    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
            s.begin(),
            find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
            find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
            s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
