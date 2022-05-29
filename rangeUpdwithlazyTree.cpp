#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1e9+7

//lazy tree storing upd value that needs to be updated at each index that the segment, our node is representing

void buildTree(int lazy[], int arr[], int l, int r, int treeNode){
    if(l==r){
        lazy[treeNode] = arr[l];
        return;
    }
    int left = 2*treeNode + 1;
    int mid = (l+r)/2;
    buildTree(lazy,arr,l,mid,left);
    buildTree(lazy,arr,mid+1,r,left+1);
    lazy[treeNode] = 0;
}

//range update
void update(int lazy[], int val, int l, int r, int myl, int myr, int treeNode){
    if(myl >= l && myr <= r){
        lazy[treeNode] += val;
        return;
    }else if(myl > r || myr < l){
        return;
    }else{
        int mid = (myl+myr)/2;
        int left = 2*treeNode + 1;
        int right = left+1;
        int myval = lazy[treeNode];
        lazy[left] += myval;
        lazy[right] += myval;
        lazy[treeNode] = 0;
        update(lazy,val,l,r,myl,mid,left);
        update(lazy,val,l,r,mid+1,myr,right);
        return;
    }
}
//point query
int query(int lazy[], int id, int l,int r, int treeNode){
    if(l == r){
        return lazy[treeNode];
    }
    int mid = (l+r)/2;
    int left = 2*treeNode + 1;
    int right = left+1;
    lazy[left] += lazy[treeNode];
    lazy[right] += lazy[treeNode];
    lazy[treeNode] = 0;
    if(id <= mid){
        return query(lazy,id,l,mid,left);
    }else{
        return query(lazy,id,mid+1,r,right);
    }
}
int main(){
    int n,m; cin>>n>>m;
    int arr[n];
    for(int&i:arr) cin>>i;
    int lazy[4*n];
    buildTree(lazy,arr,0,n-1,0);
    while(m--){
        int a,b,c; cin>>a;
        if(a == 1){
            //update
            int val; cin>>b>>c>>val;
            update(lazy,val,b,c,0,n-1,0);
        }else{
            //query
            cin>>b;
            cout<<query(lazy,b,0,n-1,0)<<endl;
        }
    }
    return 0;
}