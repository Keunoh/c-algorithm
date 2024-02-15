#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
 
int n;
int population[11];
bool check[11];
bool arr[11][11];
bool visit[11];
int answer = 987654321;
 
bool bfs(vector<int> v, bool t) {
 
 
    memset(visit, false, sizeof(visit));
    visit[v[0]] = true;
    queue<int> q;
    q.push(v[0]);
    int cnt = 1;
 
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 1; i <= n; i++) {
            //선거구인지, 연결되어있는지, 방문안했는지
            if (check[i] == t && arr[x][i] == true && visit[i] == false) {
                visit[i] = true;
                q.push(i);
                cnt++;
            }
        }
    }
    if (v.size() == cnt) return true;
    return false;
}
 
void calculate() {
 
    int agroup = 0;
    int bgroup = 0;
    for (int i = 1; i <= n; i++) {
        if (check[i] == true) agroup += population[i];
        else bgroup += population[i];
    }
    int result = agroup - bgroup;
    if (result < 0) result *= (-1);
 
    answer = min(answer, result);
}
 
// 그룹을 나눠주고구역이 이어져있는지 확인
bool right() {
 
    vector<int> a, b;
    for (int i = 1; i <= n; i++) {
        if (check[i] == true) a.push_back(i);
        else b.push_back(i);
    }
    //if (a.size() < 1 || b.size() < 1) return false;
    //이어져있는지 확인
    if (bfs(a, true) != true) return false;
    if (bfs(b, false) != true) return false;
 
 
    return true;
}
 
void dfs(int x, int cnt) {
 
    if (cnt >= 1) {
        //조합이 만들어지면 일단 체크해야함
        if (right() == true)
            calculate();
    }
    if (cnt == n - 1)
        return;
 
    for (int i = x; i <= n; i++) {
        if (check[i] == true) continue;
        check[i] = true;
        dfs(i, cnt + 1);
        check[i] = false;
    }
}
int main() {
    cin >> n;
 
    for (int i = 1; i <= n; i++)
        cin >> population[i];
 
    for (int i = 1; i <= n; i++) {
        int cnt;
        cin >> cnt;
        for (int j = 0; j < cnt; j++) {
            int x; cin >> x;
            arr[i][x] = true;
            arr[x][i] = true;
        }
    }
 
    dfs(1, 0);
 
    if (answer == 987654321) cout << -1;
    else cout << answer;
 
    return 0;
}
