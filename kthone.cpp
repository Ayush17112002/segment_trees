#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1e9+7

void buildTree(vector<int>&tree, vector<int>&v, int l, int r, int treeNode){
    if(l==r){
        tree[treeNode] = v[l];
        return;
    }
    int mid = (l+r)/2;
    int left = 2*treeNode + 1;
    int right = left + 1;
    buildTree(tree,v,l,mid,left);
    buildTree(tree,v,mid+1,r,right);
    tree[treeNode] = tree[left] + tree[right];
}
void update(vector<int>&tree, int id, int l, int r, int treeNode){
    if(l==r){
        tree[treeNode] = (tree[treeNode]+1)%2; 
        return; 
    }
    int mid = (l+r)/2;
    int left = 2*treeNode + 1;
    int right = left + 1;
    if(id <= mid){
        update(tree,id,l,mid,left);
    }else{
        update(tree,id,mid+1,r,right);
    }
    tree[treeNode] = tree[left] + tree[right];
}

int query(vector<int>&tree, int k, int l, int r, int treeNode){
    if(l==r){
        return l;
    }
    int mid = (l+r)/2;
    int left = 2*treeNode + 1;
    int right = left + 1;
    if(k<=tree[left]){
        return query(tree,k,l,mid,left);
    }else{
        return query(tree,k-tree[left],mid+1,r,right);
    }
}
int main(){
    int n,m; cin>>n>>m;
    vector<int> v(n), tree(4*n,0); for(int&i:v) cin>>i;
    buildTree(tree,v,0,n-1,0);
    for(int&i:tree) cout<<i<<" ";
    while(m--){
        int a,b; cin>>a>>b;
        if(a == 1){
            //upd
            update(tree,b,0,n-1,0);
        }else{
            //query
            cout<<query(tree,b+1,0,n-1,0)<<endl;
        }
    }
    return 0;
}