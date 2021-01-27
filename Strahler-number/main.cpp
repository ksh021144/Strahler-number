#pragma warning(disable:4996)
#include <iostream>
#include <queue>
using namespace std;

int T;
int nodeCount, edgeCount;
vector<int> adj[1001], adjReverse[1001];
int indegree[1001];
int strahlerNumber[1001];

int main() {
    std::freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(false), cin.tie(nullptr);


    cin >> nodeCount >> edgeCount;
    for (int i = 0, u, v; i < edgeCount; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        adjReverse[v].push_back(u);
        ++indegree[v];
    }

    queue<int> q;
    for (int i = 1; i <= nodeCount; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
            strahlerNumber[i] = 1;
        }
    }

    while (!q.empty()) {
        int now = q.front();
        q.pop();
        if (indegree[now] == 0) {
            int mx = 0, mxCnt = 0;
            for (int upstream : adjReverse[now]) {
                if (mx < strahlerNumber[upstream]) {
                    mx = strahlerNumber[upstream];
                    mxCnt = 1;
                }
                else if (mx == strahlerNumber[upstream]) {
                    ++mxCnt;
                }
            }
            if (mxCnt == 1)
                strahlerNumber[now] = mx;
            else if (mxCnt > 1)
                strahlerNumber[now] = mx + 1;
        }

        for (int next : adj[now]) {
            --indegree[next];
            if (indegree[next] == 0) {
                q.push(next);
            }
            else {
                if (strahlerNumber[next] == 0)
                    strahlerNumber[next] = strahlerNumber[now];
            }
        }
    }

    // outdegree == 0
    // if 'nodeCount(value) vertex' is always 'River joining the sea'.
    cout << "Strahler number : " << strahlerNumber[nodeCount] << '\n';

    // outdegree != 0
    //int ansStrahlerNumber = 0;
    //for (int i = 1; i <= nodeCount; ++i) {
    //    if (ansStrahlerNumber < strahlerNumber[i])
    //        ansStrahlerNumber = strahlerNumber[i];
    //}
    //cout << "Strahler number : " << ansStrahlerNumber << '\n';
    return 0;
}