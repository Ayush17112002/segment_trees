#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1e9+7
void buildTree(vector<int>&tree, int l, int r, int treeNode){
    if(l == r){
        tree[treeNode] = 1;
        return;
    }
    int mid = (l+r)/2;
    int left = 2*treeNode + 1;
    int right = left+1;
    buildTree(tree,l,mid,left);
    buildTree(tree,mid+1,r,right);
    tree[treeNode] = tree[left] + tree[right];
}
void update(vector<int>&tree, int l, int r, int id, int treeNode){
    if(l == r){
        tree[treeNode] = 0;
        return;
    }
    int mid = (l+r)/2;
    int left = 2*treeNode + 1;
    int right = left+1;
    if(id <= mid){
        update(tree,l,mid,id,left);
    }else{
        update(tree,mid+1,r,id,right);
    }
    tree[treeNode] = tree[left] + tree[right];
}
//find max number j s.t. there are exactly x numbers bigger than it which are not used 
int query(vector<int>&tree, int l, int r, int x, int treeNode){
    if(l == r){
        //cout<<l;
        return l;
    }
    int mid = (l+r)/2;
    int left = 2*treeNode + 1;
    int right = left+1;
    
    int ele = r-l+1;
    //check right side
    if(tree[right] >= x+1){
        //total empty places in right half >= (x unused numbers + 1 number that I can use)
        return query(tree,mid+1,r,x,right);
    }else{
        return query(tree,l,mid,x-tree[right],left);
    }
}
int main(){
    int n; cin>>n;
    vector<int> v(n); for(int&i:v) cin>>i;
    vector<int>tree(4*n,0), res(n);
    buildTree(tree,0,n-1,0);
    for(int i = n-1; i >= 0; i--){
        int ans = query(tree,0,n-1,v[i],0);
        update(tree,0,n-1,ans,0);
        res[i] = ans+1;
    }
    for(int&i:res) cout<<i<<" ";
    return 0;
}