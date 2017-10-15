#include <bits/stdc++.h>
#define N 1024
using namespace std;
struct TreeNode
{
	int val;
	int left,right;
}tree[4*N];
int arr[N];
void build(int root,int l,int r)
{
	tree[root].left=l;
	tree[root].right=r;
	if(l==r)
	{
		tree[root].val=arr[l];
		return;
	}
	int mid=(l+r)/2;
	build(2*root,l,mid);
	build(2*root+1,mid+1,r);
	tree[root].val=tree[2*root].val+tree[2*root+1].val;
}
int query(int root,int l,int r)
{
	if(tree[root].left==l&&tree[root].right==r)
	{
		return tree[root].val;
	}
	int mid=(tree[root].left+tree[root].right)/2;
	if(mid>=r)
		return query(2*root,l,r);
	else if(mid+1<=l)
		return query(2*root+1,l,r);
	return query(2*root,l,mid)+query(2*root+1,mid+1,r);
}
void update(int root,int pos,int val)
{
	if(tree[root].left==pos&&tree[root].right==pos)
	{
		tree[root].val=val;
		return;
	}
	int mid=(tree[root].left+tree[root].right)/2;
	if(pos<=mid)
		update(2*root,pos,val);
	else update(2*root+1,pos,val);
	tree[root].val=tree[2*root].val+tree[2*root+1].val;
}
int main()
{
	freopen("2.txt","r",stdin);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		cin>>arr[i];
	build(1,1,n);
	for(int i=0;i<m;++i)
	{
		int opt,x,y;
		cin>>opt>>x>>y;
		if(opt==1)
			update(1,x,y);
		else
			cout<<query(1,x,y)<<endl;
	}
	return 0;
}
/* test case
8 4
1 2 3 4 5 6 7 8
1 2 0
2 1 8
1 8 0
2 2 2
*/

/*output
34
0
*/
