#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1e9+7
class segType{
    public:
    ll pref,suff,sum,seg;
    segType(){
        pref = suff = sum = seg = 0;
    }
};

void buildTree(vector<segType>&tree, vector<int>&v, int l, int r, int treeNode){
    if(l==r){
        if(v[l] > 0){
            tree[treeNode].pref = tree[treeNode].seg = tree[treeNode].suff = v[l];   
        }
        tree[treeNode].sum = v[l];
        return;
    }
    int mid = (l+r)/2;
    int left = 2*treeNode + 1;
    int right = 2*treeNode + 2;
    buildTree(tree,v,l,mid,left);
    buildTree(tree,v,mid+1,r,right);
    tree[treeNode].sum = tree[left].sum + tree[right].sum;
    tree[treeNode].seg = max(tree[left].seg, max(tree[right].seg, tree[left].suff+tree[right].pref));
    tree[treeNode].pref = max(tree[left].pref, tree[left].sum + tree[right].pref);
    tree[treeNode].suff = max(tree[right].suff, tree[right].sum + tree[left].suff);
}

//update at index id i.e. v[id] = id
void update(vector<segType>&tree, int id, int val, int l, int r, int treeNode){
    if(l == r){
        if(val > 0){
            tree[treeNode].pref = tree[treeNode].seg = tree[treeNode].suff = val;   
        }else{
            tree[treeNode].pref = tree[treeNode].seg = tree[treeNode].suff = 0;
        }
        tree[treeNode].sum = val;
        return;
    }
    int mid = (l+r)/2;
    int left = 2*treeNode + 1;
    int right = 2*treeNode + 2;
    if(id <= mid){
        update(tree,id,val,l,mid,left);
    }else{
        update(tree,id,val,mid+1,r,right);
    }
    tree[treeNode].sum = tree[left].sum + tree[right].sum;
    tree[treeNode].seg = max(tree[left].seg, max(tree[right].seg, tree[left].suff+tree[right].pref));
    tree[treeNode].pref = max(tree[left].pref, tree[left].sum + tree[right].pref);
    tree[treeNode].suff = max(tree[right].suff, tree[right].sum + tree[left].suff);
}

//query -> [l,r]
segType query(vector<segType>&tree, int l, int r, int myl, int myr, int treeNode){
    if(myl>=l && myr<=r){
        return tree[treeNode];
    }
    int mid = (l+r)/2;
    int left = 2*treeNode + 1;
    int right = 2*treeNode + 2;
    if(r<=mid){
        return query(tree,l,r,myl,mid,left);
    }else if(l>mid){
        return query(tree,l,r,mid+1,myr,right);
    }else{
        segType s1 = query(tree,l,r,myl,mid,left);
        segType s2 = query(tree,l,r,mid+1,myr,right);
        segType res;
        res.sum = s1.sum + s2.sum;
        res.seg = max(s1.seg, max(s2.seg, s1.suff + s2.pref));
        res.pref = max(s1.pref, s1.sum + s2.pref);
        res.suff = max(s2.suff, s2.sum + s1.suff);
        return res;
    }
}
int main(){
    int n,m; cin>>n>>m;
    vector<int> v(n);
    for(int&i:v) cin>>i;
    vector<segType> tree(4*n);
    buildTree(tree,v,0,n-1,0);
    cout<<tree[0].seg<<endl;
    while(m--){
        int id, val; cin>>id>>val;
        update(tree,id,val,0,n-1,0);
        cout<<tree[0].seg<<endl;
    }
    return 0;
}