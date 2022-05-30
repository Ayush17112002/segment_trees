#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1e9+7

int main(){
        int n; cin>>n;
        vector<int> v(n); for(int&i:v) cin>>i;
        vector<int> vis(n+1,0);
        vector<int> ans(n+1);
        set<int> st;
        for(int i = n-1; i >= 0; i--){
            int j = n, empty_places=v[i];
                while(j>=1 && empty_places>0){
                    if(vis[j]==0) empty_places--;
                    j--;
                }
                while(j>=1){
                    if(vis[j]==1)j--;
                    else break;
                }
            ans[i] = j;
            vis[j] = 1;
        }
        for(int i = 0; i < n; i++) cout<<ans[i]<<" ";
    return 0;
}