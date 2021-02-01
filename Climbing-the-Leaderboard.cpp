#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'climbingLeaderboard' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY ranked
 *  2. INTEGER_ARRAY player
 */

vector<int> m_data, tree;

void buildTree(int p, int l, int r) {
    if(l==r){
        tree[p]=m_data[l];
        return;
    }
    int mid=(r-l)/2+l;
    int ls=p*2+1;
    int rs=p*2+2;
    buildTree(ls, l, mid);
    buildTree(rs, mid+1, r);
    tree[p]=tree[ls]+tree[rs];
}

int query(int p, int l, int r, int queryL, int queryR) {
    if (l == queryL && r == queryR)
        return tree[p];
    int mid = (r - l) / 2 + l;
    int ls = p * 2 + 1;
    int rs = p * 2 + 2;
    if (queryR <= mid)
        return query(ls, l, mid, queryL, queryR);
    else if (queryL >= mid + 1)
        return query(rs, mid + 1, r, queryL, queryR);
    else
        return query(ls, l, mid, queryL, mid) + query(rs, mid + 1, r, mid + 1, queryR);
}

void update(int p, int l, int r, int x) {
    if (l == r) {
        tree[p] = ++m_data[x];
        return;
    }
    int mid = (r - l) / 2 + l;
    int ls = p * 2 + 1;
    int rs = p * 2 + 2;
    if (x <= mid)
        update(ls, l, mid, x);
    else
        update(rs, mid + 1, r, x);
    tree[p] = tree[ls] + tree[rs];
}

// use segment tree to solve this problem
vector<int> climbingLeaderboard(vector<int> ranked, vector<int> player) {
    set<int> g;
    for (const int &x:ranked)
        g.insert(x);
    for (const int &x:player)
        g.insert(x);
    unordered_map<int, int> f;
    int index = g.size();
    for (const int &x:g)
        f[x] = index--;
    int n = (int) g.size() + 1;
    m_data.resize(n);
    tree.resize(n * 4);
    for (const int &x:ranked) {
        if (m_data[f[x]])
            continue;
        ++m_data[f[x]];
    }

    buildTree(0, 0, n - 1);

    vector<int> res(player.size());
    for (int i = 0; i < player.size(); ++i) {
        res[i] = query(0, 0, n - 1, 0, f[player[i]] - 1) + 1;
        update(0, 0, n - 1, f[player[i]]);
    }
    return res;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string ranked_count_temp;
    getline(cin, ranked_count_temp);

    int ranked_count = stoi(ltrim(rtrim(ranked_count_temp)));

    string ranked_temp_temp;
    getline(cin, ranked_temp_temp);

    vector<string> ranked_temp = split(rtrim(ranked_temp_temp));

    vector<int> ranked(ranked_count);

    for (int i = 0; i < ranked_count; i++) {
        int ranked_item = stoi(ranked_temp[i]);

        ranked[i] = ranked_item;
    }

    string player_count_temp;
    getline(cin, player_count_temp);

    int player_count = stoi(ltrim(rtrim(player_count_temp)));

    string player_temp_temp;
    getline(cin, player_temp_temp);

    vector<string> player_temp = split(rtrim(player_temp_temp));

    vector<int> player(player_count);

    for (int i = 0; i < player_count; i++) {
        int player_item = stoi(player_temp[i]);

        player[i] = player_item;
    }

    vector<int> result = climbingLeaderboard(ranked, player);

    for (int i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

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
