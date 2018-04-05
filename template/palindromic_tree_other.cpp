#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
/*
S - string used to build the palindromic tree  [1...n]
go[u][c] - the node(state) that node u goes through an edge with character c
len[u] - the length of the palindrome string in the node u
par[u] - the fail link (longest palindromic suffix)
diff[u] - the difference between current node and the parent node (the period)
slink[u] - the suffix link which leads to the first different diff with diff[u]

*/
char s[N],t[N],S[N];
int n,go[N][26],len[N],par[N],top,last;
int New(int L){len[++top]=L;return top;}
int diff[N],slink[N];
void extend(int n){
	int w=S[n],p=last;
	while (S[n-len[p]-1]!=w) p=par[p];
	if (!go[p][w-'a']){
		int q=New(len[p]+2),now=p;
		do now=par[now];while (S[n-len[now]-1]!=w);
		par[q]=go[now][w-'a'];
		go[p][w-'a']=q;
		diff[q]=len[q]-len[par[q]];
		slink[q]=(diff[q]==diff[par[q]]?slink[par[q]]:par[q]);
	}
	last=go[p][w-'a'];
}
int ans[N],from[N],_ans[N];
int main()
{
	scanf("%s%s",s+1,t+1);
	n=strlen(s+1);
	for (int i=1;i<=n;i++) S[i*2-1]=s[i],S[i*2]=t[i];
	par[0]=top=1;len[1]=-1;
	n*=2;
	for (int i=1;i<=n;i++) ans[i]=1e9;
	_ans[0]=1;
	for (int i=1;i<=n;i++){
		extend(i);
		for (int p=last;p;p=slink[p]){
			_ans[p]=i-(len[slink[p]]+diff[p]);
			if (diff[par[p]]==diff[p]&&ans[_ans[p]]>ans[_ans[par[p]]])
				_ans[p]=_ans[par[p]];
			if (!(i&1)&&ans[i]>ans[_ans[p]]+1)
				ans[i]=ans[_ans[p]]+1,from[i]=_ans[p];
		}
		if (!(i&1)&&S[i-1]==S[i]&&ans[i]>ans[i-2])
			ans[i]=ans[i-2],from[i]=i-2;
	}
	if (ans[n]<1e9){
		printf("%d\n",ans[n]);
		for (int i=n;i;i=from[i])
		if (i-from[i]>2) printf("%d %d\n",(from[i]+2)>>1,i>>1);
	}
	else puts("-1");
	return 0;
}
