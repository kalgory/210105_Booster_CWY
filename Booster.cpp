#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <functional>
#include <queue>
#include <utility>
#include <stdlib.h>
using namespace std;

const int NMAX = 250001;
struct edge {
    int m;
    pair<int, int> coord;
};
struct compare {
    bool operator()(edge& I, edge& C) {
        return I.m > C.m;
    }
};
typedef struct edge edge;
int N, Q;
int parent[NMAX];
vector<edge> x; // x 좌표를 기준으로 오름차순 정렬 {m: 번호, pair(x좌표, y좌표)}
vector<edge> y; // y 좌표를 기준으로 오름차순 정렬 {m: 번호, pair(x좌표, y좌표)}
priority_queue<edge, vector<edge>, compare> pq; // {m: 가중치, pair(좌표번호, 좌표번호)}
//priority_queue<edge, vector<edge>, compare> query; // {m: 가중치, pair(좌표번호, 좌표번호)}
bool answer[NMAX];
int find(int a)
{
    if (parent[a] < 0)
        return a;

    return parent[a] = find(parent[a]);

}

void _union(int a, int b)
{
    a = find(a);
    b = find(b);

    if (a == b)
        return;

    if (parent[a] < parent[b])
        swap(a, b);

    parent[b] += parent[a];
    parent[a] = b;

}
bool compareX(const edge& a, const edge& b) {
    return a.coord.first < b.coord.first;
}
bool compareY(const edge& a, const edge& b) {
    return a.coord.second < b.coord.second;
}
int main() {
    cin >> N >> Q;
    edge I;
    int a;
    int b;
    int c;
    memset(parent, -1, sizeof(parent));
    for (int i = 0; i < N; i++) {
        cin >>a>>b;
        I.m = i+1;
        I.coord = make_pair(a, b);
        x.push_back(I);
        y.push_back(I);
    }
    sort(x.begin(), x.end(), compareX);
    sort(y.begin(), y.end(), compareY);
    for (int i = 0; i < N - 1; i++) {
        I.m = abs(x[i].coord.first - x[i+1].coord.first);
        I.coord.first = x[i].m;
        I.coord.second = x[i+1].m;
        pq.push(I);
    }
    for (int i = 0; i < N - 1; i++) {
        I.m = abs(y[i].coord.second - y[i + 1].coord.second);
        I.coord.first = y[i].m;
        I.coord.second = y[i + 1].m;
        pq.push(I);
    }
    // query {가중치, {번호1, 번호2}}
    vector<pair<pair<int, pair<int, int>>, int>> query;
    for (int i = 0; i < Q; i++)
    {
        cin >> a >> b >> c;
        query.push_back({ {c, {a, b}}, i });
    }

    sort(query.begin(), query.end());
    int p;
    int q;
    for(int i = 0;i<query.size();i++){
        int value = query[i].first.first;
        while (!pq.empty()) {
            int cur = pq.top().m;
            if (cur > value)
                break;
            // printf("\n%d번 %d번 연결\n", pq.top().coord.first, pq.top().coord.second);
            _union(pq.top().coord.first, pq.top().coord.second);
            pq.pop();
            
        }
        p = find(query[i].first.second.first);
        q = find(query[i].first.second.second);
        
        answer[query[i].second] = (p == q);
        
        
    }
    for (int i = 0; i < Q;i++) {
        if (answer[i])
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}

// 우선순위 큐 비교연산자: https://hydroponicglass.tistory.com/169
// 풀이참고: (https://jaimemin.tistory.com/797) (https://blog.naver.com/pasdfq/221332735719)