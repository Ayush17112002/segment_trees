//In this task, you need to add to the segment tree the operation of finding for the given x and l the minimum index j such that j≥l and a[j]≥x.
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
    tree[treeNode] = max(tree[left],tree[right]);
}
void update(vector<int>&tree, int id, int val, int l, int r, int treeNode){
    if(l==r){
        tree[treeNode] = val;
        return; 
    }
    int mid = (l+r)/2;
    int left = 2*treeNode + 1;
    int right = left + 1;
    if(id <= mid){
        update(tree,id,val,l,mid,left);
    }else{
        update(tree,id,val,mid+1,r,right);
    }
    tree[treeNode] = max(tree[left],tree[right]);
}
// index j >= id && a[j]>=x
int query(vector<int>&tree, int id, int x, int l, int r, int treeNode){
    //if element u want is not present in the tree
    if(tree[treeNode] < x){
        return -1;
    }
    if(l == r){
        return l;   
    }
    int mid = (l+r)/2;
    int left = 2*treeNode + 1;
    int right = left+1;
    if(id <= mid){
        //go to left tree
        int ans = -1;
        if(x <= tree[left]){
            ans = query(tree,id,x,l,mid,left);
        }
        if(ans==-1){
            //go to right tree
            return query(tree,id,x,mid+1,r,right);
        }
        return ans;
    }else{
        //u have no permission to look into left subtreee
        return query(tree,id,x,mid+1,r,right);
    }

}
int main(){
    int n,m; cin>>n>>m;
    vector<int> v(n), tree(4*n,0); for(int&i:v) cin>>i;
    buildTree(tree,v,0,n-1,0);
    //for(int&i:tree) cout<<i<<" ";
    while(m--){
        int a; cin>>a;
        if(a == 1){
            //upd
            int id,val; cin>>id>>val;
            update(tree,id,val,0,n-1,0);
        }else{
            //query
            int x,j; cin>>x>>j;
            cout<<query(tree,j,x,0,n-1,0)<<endl;
        }
    }
    return 0;
}