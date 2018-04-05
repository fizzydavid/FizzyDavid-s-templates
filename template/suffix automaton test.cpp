//while(true)rp++;
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<deque>
#include<fstream>
#include<iostream>
#include<iomanip>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<utility>
#include<vector>
using namespace std;
typedef long long ll;
#define FF first
#define SS second
#define PB push_back
#define MP make_pair
const int maxn=100;
vector<string>ans;
struct SAM
{
	int go[maxn][26],pre[maxn],len[maxn],tot,last;
	void init()
	{
		memset(go,-1,sizeof(go));
		memset(pre,-1,sizeof(pre));
		memset(len,0,sizeof(len));
		tot=1;last=0;
	}
	void insert(char c)
	{
		c-='a';
		int p=last,np=tot++;
		len[np]=len[last]+1;
		while(p!=-1&&go[p][c]==-1)
			go[p][c]=np,p=pre[p];
		if(p==-1)
			pre[np]=0;
		else
		{
			int q=go[p][c];
			if(len[p]+1==len[q])
				pre[np]=q;
			else
			{
				int nq=tot++;
				len[nq]=len[p]+1;
				for(int i=0;i<26;i++)
					go[nq][i]=go[q][i];
				pre[nq]=pre[q];
				pre[q]=pre[np]=nq;
				while(p!=-1&&go[p][c]==q)
					go[p][c]=nq,p=pre[p];
			}
		}
		last=np;
	}
	void dfs(string s,int p=0)
	{
		cout<<s<<endl;
		ans.PB(s);
		for(int i=0;i<26;i++)
			if(go[p][i]!=-1)
				dfs(s+char('a'+i),go[p][i]);
	}
}sam;
int main()
{
	string s;
	cin>>s;
	sam.init();
	for(int i=0;i<s.size();i++)
		sam.insert(s[i]);
	for(int i=1;i<sam.tot;i++)cout<<sam.pre[i]<<" ";cout<<endl;
	for(int i=1;i<sam.tot;i++)cout<<sam.len[i]<<" ";cout<<endl;
	
	sam.dfs("");
	return 0;
}
