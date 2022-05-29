#include <bits/stdc++.h>
using namespace std;
#define ll long long

void buildTree(vector<pair<int,int>> &Tree, vector<int> &v, int l, int r, int treeNode)
{
    if (l == r)
    {
        Tree[treeNode] = {v[l],1};
        return;
    }
    int mid = (l + r) / 2;
    int left = treeNode * 2 + 1;
    int right = treeNode * 2 + 2;
    buildTree(Tree,v,l,mid,left);
    buildTree(Tree,v,mid+1,r,right);
    if(Tree[left].first < Tree[right].first){
        Tree[treeNode] = Tree[left];
    }else if(Tree[left].first > Tree[right].first){
        Tree[treeNode] = Tree[right];
    }else{
        Tree[treeNode] = {Tree[left].first, Tree[left].second+Tree[right].second};
    }
}

// update v[i] = ele
void update(vector<pair<int,int>>&Tree, int i, int ele, int l, int r, int treeNode)
{
    if (l == r && l == i)
    {
        Tree[treeNode] = {ele,1};
        return;
    }
    int mid = (l + r) / 2;
    int left = (2 * treeNode) + 1;
    int right = (2 * treeNode) + 2;
    if (i <= mid)
    {
        // call to left
        update(Tree, i, ele, l, mid, left);
    }
    else
    {
        update(Tree, i, ele, mid + 1, r, right);
    }
    if(Tree[left].first < Tree[right].first){
        Tree[treeNode] = Tree[left];
    }else if(Tree[left].first > Tree[right].first){
        Tree[treeNode] = Tree[right];
    }else{
        Tree[treeNode] = {Tree[left].first, Tree[left].second+Tree[right].second};
    }
    return;
}

// query-> range sum
pair<int,int> query(vector<pair<int,int>>&v, int l, int r, int i, int j, int treeNode)
{
    if (i >= l && j <= r)
    {
        return v[treeNode];
    }
    else if (j<l || i>r)
    {
        return {INT_MAX, 0};
    }
    else
    {
        int mid = (i+j) / 2;
        int left = (2 * treeNode) + 1;
        int right = left + 1;
        pair<int,int> p1 = query(v, l, r, i, mid, left);
        pair<int,int> p2 = query(v, l,r,mid+1,j, right);
        if(p1.first < p2.first){
            return p1;
        }else if(p1.first > p2.first){
            return p2;
        }else{
            return {p1.first, p1.second+p2.second};
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    for (int &i : v){
        cin >> i;
    }
    vector<pair<int,int>> Tree(4 * n, {0,0});
    buildTree(Tree, v, 0, n - 1, 0);
    //for(ll&i:Tree) cout<<i<<" ";
    while (m--)
    {
        int a, b, c;
        cin >> c >> a >> b;
        if (c == 1)
        {
            update(Tree, a, b, 0, n - 1, 0);
        }
        else
        {
            pair<int,int> p = query(Tree, a, b-1, 0, n - 1, 0);
            cout << p.first <<" "<< p.second<<endl;
        }
    }
return 0;
}