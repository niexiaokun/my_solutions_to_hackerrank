#include <bits/stdc++.h>

using namespace std;

// Complete the angryChildren function below.
long angryChildren(int k, vector<int> packets) {
    int n=packets.size();
    sort(packets.begin(),packets.end());
    vector<long> pre(n+1);
    for(int i=1;i<=n;++i)
        pre[i]=pre[i-1]+packets[i-1];
    long cur = 0;
    for(int i=1;i<k;++i)
        cur+=(long)i*packets[i]-pre[i];
    long res = cur;
    for(int i=1;i+k<=n;++i){
        cur+=(long)(k-1)*((long)packets[i+k-1]+packets[i-1])-2*(pre[i+k-1]-pre[i]);
        res=min(res,cur);
    }
    return res;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int k;
    cin >> k;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> packets(n);

    for (int i = 0; i < n; i++) {
        int packets_item;
        cin >> packets_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        packets[i] = packets_item;
    }

    long result = angryChildren(k, packets);

    fout << result << "\n";

    fout.close();

    return 0;
}
