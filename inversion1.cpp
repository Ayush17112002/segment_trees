#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1e9+7
void upd(vector<int>&tree, int id, int l,int r, int treeNode){
    if(l==r){
        tree[treeNode] = 1;
        return;
    }
    int mid = (l+r)/2;
    int left = 2*treeNode + 1;
    int right = left+1;
    if(id <= mid){
        upd(tree,id,l,mid,left);
    }else{
        upd(tree,id,mid+1,r,right);
    }
    tree[treeNode] = tree[left] + tree[right];
}
int query(vector<int>&tree, int id, int l, int r, int treeNode){
    if(l>id){
        return tree[treeNode];    
    }
    int mid = (l+r)/2;
    int left = 2*treeNode + 1;
    int right = left+1;
    int ans = 0;
    if(id < mid){
        ans = query(tree,id,l,mid,left);
    }
    ans += query(tree,id,mid+1,r,right);
    return ans;
}
int main(){
    int n; cin>>n;
    vector<int>v(n), tree(4*n,0); for(int&i:v) cin>>i;
    for(int i = 0; i < n; i++){
        cout<<query(tree,v[i]-1,0,n-1,0)<<" ";
        upd(tree,v[i]-1,0,n-1,0);
    }
    return 0;
}