#include <iostream>
#include <set>
#include <vector>
#include <queue>
using namespace std;
using pii = pair<int,int>;

int main()
{
    int n, m; cin>>n>>m;
    vector<int> mp(n);
    vector<int> cp(n);
    for(int i=0; i<n; i++)
    {
        cin>>mp[i];
        cin>>cp[i];
    }
    //if m <= cp[i], m = m - mp[i];
    //find min. number of loli needed to make m <= 0.
    //set<pii> lolis;
    //for(int i=0;i<n;i++) lolis.insert({mp[i], cp[i]});

    priority_queue<pii> lolis;
    for(int i=0;i<n;i++) lolis.push({mp[i], cp[i]});

    int cnt = 0;
    for(int i=0; i<n; i++)
    {
        auto now = lolis.top();
        if(now.second >= m)
        {
            m -= now.first;
            cnt ++;
            
        }
        lolis.pop();
        if(m <= 0) break;
    }

    if(m <= 0) cout<<cnt<<'\n';
    else cout<<-1<<'\n';
}
    