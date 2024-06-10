#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

struct DSU {
	vector<int> fa, sz;
	DSU(int n) {
		fa.assign(n + 1, 0);
		sz.assign(n + 1, 1);
		for (int i = 0; i <= n; i++) fa[i] = i;
	}
	int find(int x) {
		return (fa[x] == x ? x : fa[x] = find(fa[x]));
	}
	bool unite(int a, int b) {
		a = find(a), b = find(b);
		if(a == b) return false;
		if(sz[a] > sz[b]) swap(a, b);
		fa[a] = b;
		sz[b] += sz[a];
        return true;
	}
};

int main()
{
    int n; cin>>n;
    vector<int> x(n,0);
    vector<int> y(n,0);
    DSU dsu(n);
    for(int i=0; i<n; i++)
    {
        cin>>x[i];
        cin>>y[i];
    }
    int e = n * (n-1) / 2; //num of edges;
    vector<tuple<int, int, int>> edges(e);
    int k = 0;
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            int w = (x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j]);
            get<0>(edges[k]) = i;
            get<1>(edges[k]) = j;
            get<2>(edges[k]) = w;
            //cout<<"[u,v,w] = "<<i<<' '<<j<<' '<<w<<'\n';
            k++;
        }
    }

    sort(edges.begin(), edges.end(), [](auto &a, auto &b) {
        return get<2>(a) < get<2>(b); //lambda function, 根據weight升序排列
    });
    long long ans = 0;
    for (auto &[u, v, w] : edges) {
        if (dsu.unite(u, v)) ans += w;
    }
    cout << ans << '\n';
}