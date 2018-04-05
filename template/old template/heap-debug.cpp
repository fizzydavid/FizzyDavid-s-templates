//while(true)rp++;
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<map>
#include<queue>
#include<stack>
#include<string>
#include<set>
#include<utility>
#include<vector>
using namespace std;
#define ff first
#define ss second
#define pb push_back 
#define mp make_pair
#define online
typedef long long ll;
const ll INF=1<<28;
const ll LINF=1ll<<61;
struct heap
{
	int arr[100011];
	int heap_size;
	heap()
	{
		memset(arr,0,sizeof(int));
		heap_size=0;
	}
	int size()
	{
		return heap_size;
	}
	bool empty()
	{
		return heap_size>0;
	}
	int top()
	{
		return arr[1];
	}
	void push(int x)
	{
		arr[++heap_size]=x;
		int i=heap_size;
		while(i!=1&&arr[i/2]<arr[i])
		{
			swap(arr[i],arr[i/2]);
			i=i/2;
		}
	}
	int pop()
	{
		int ans=arr[1];
		arr[1]=arr[heap_size];
		heap_size--;
		int i=1;
		while(i*2<=heap_size&&arr[i]<arr[i*2]||i*2+1<=heap_size&&arr[i]<arr[i*2+1])
		{
			if(arr[i*2+1]<arr[i*2])
			{
				swap(arr[i*2],arr[i]);
				i=i*2;
			}
			else if(arr[i*2]<arr[i*2+1])
			{
				swap(arr[i*2+1],arr[i]);
				i=i*2+1;
			}
		}
		return ans;
	}
}pq;
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		pq.push(x);
	}
	for(int i=1;i<=n;i++)cout<<pq.arr[i]<<" ";
}
