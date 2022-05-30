#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1e9+7
int do_or(int a, int b){
    int c = 0;
    for(int i = 0; i < 31; i++){
        int f = ((a>>i)&1);
        int s = ((b>>i)&1);
        if(f>0 || s>0){
            c += pow(2,i);
        }
    }
    return c;
}
int do_xor(int a, int b){
    int c = 0;
    for(int i = 0; i < 31; i++){
        int f = ((a>>i)&1);
        int s = ((b>>i)&1);
        if(f != s){
            c += pow(2,i);
        }
    }
    return c;
}
int buildTree(vector<int>&tree, vector<int>&v, int l, int r, int treeNode){
    if(l == r){
        tree[treeNode] = v[l];
        return 0;
    }
    int mid = (l+r)/2;
    int left = 2*treeNode + 1;
    int right = left+1;
    int val = buildTree(tree,v,l,mid,left);
    buildTree(tree,v,mid+1,r,right);
    if(val == 0){
        //do or
        tree[treeNode] = (tree[left]|tree[right]);
    }else{
        //do xor 
        tree[treeNode] = (tree[left]^tree[right]);
    }
    return (val+1)%2;
}
int update(vector<int>&tree, int id, int val, int l, int r, int treeNode){
    if(l == r){
        tree[treeNode] = val;
        return 0;
    }
    int mid = (l+r)/2;
    int left = 2*treeNode + 1;
    int right = left+1;
    int ch;
    if(id <= mid){
        ch = update(tree,id,val,l,mid,left);
    }else{
        ch = update(tree,id,val,mid+1,r,right);
    }
    if(ch == 0){
        //do or
        tree[treeNode] = (tree[left]|tree[right]);
    }else{
        //do xor 
        tree[treeNode] = (tree[left]^tree[right]);
    }
    return (ch+1)%2;
}

int main(){
    int n,m; cin>>n>>m;
    n = pow(2,n);
    vector<int> v(n); for(int&i:v) cin>>i;
    vector<int>tree(4*n,0);
    buildTree(tree,v,0,n-1,0);
    //for(int&i:tree) cout<<i<<" ";
    while(m--){
        int a,b; cin>>a>>b;
        update(tree,a-1,b,0,n-1,0);
        cout<<tree[0]<<endl;
    }
    return 0;
}