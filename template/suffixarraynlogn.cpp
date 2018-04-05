//by yjz
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
#define MP make_pair
int len,rk[400111],tmp[400111],b[400111],sa[400111],nrk[400111];
char s[200111];
inline bool cmp(int i,int j,int k)
{
	return MP(rk[i],i+k>=len?-1:rk[i+k])<MP(rk[j],j+k>=len?-1:rk[j+k]);
}
void constract_sa()
{
	memset(b,0,sizeof(b));
	for(int i=0;i<len;i++)b[s[i]]++;
	for(int i=1;i<256;i++)b[i]+=b[i-1];
	for(int i=0;i<len;i++)rk[i]=b[s[i]];
	for(int i=len-1;i>=0;i--)sa[--b[s[i]]]=i;
	for(int k=1;k<len;k<<=1)
	{
		memset(b,0,sizeof(b));
		for(int i=0;i<len;i++)b[rk[i]]++;
		for(int i=1;i<=len;i++)b[i]+=b[i-1];
		for(int i=len-1;i>=0;i--)if(sa[i]>=k)tmp[--b[rk[sa[i]-k]]]=sa[i]-k;
		for(int i=len-1;i>=0;i--)if(sa[i]+k>=len)tmp[--b[rk[sa[i]]]]=sa[i];
		nrk[tmp[0]]=0;
		for(int i=1;i<len;i++)nrk[tmp[i]]=nrk[tmp[i-1]]+cmp(tmp[i-1],tmp[i],k);
		for(int i=0;i<len;i++)rk[i]=nrk[i],sa[i]=tmp[i];
	}
}
int main()
{
	scanf("%s",s);
	len=strlen(s);
	for(int i=len;i<len*2;i++)s[i]=s[i-len];
	len+=len;
	constract_sa();
	for(int i=0;i<len;i++)
	{
		if(sa[i]<len/2)putchar(s[sa[i]+len/2-1]);
	}
	return 0;
}




int sa[100111],nsa[100111],rk[100111],nrk[100111],b[100111];
int lcp[100111],tab[20][100111],lg2[100111];
void makeb()
{
	memset(b,0,sizeof(b));
	for(int i=1;i<=n;i++)b[rk[i]]++;
	for(int i=1;i<=max(256,n);i++)b[i]+=b[i-1];
}
#define usb(x) MP(rk[x],x+k>n?-1:rk[x+k])
void construct_sa()
{
	for(int i=1;i<=n;i++)rk[i]=s[i];
	makeb();
	for(int i=n;i>=1;i--)sa[b[rk[i]]--]=i;
	for(int k=1;k<n;k<<=1)
	{
		makeb();
		for(int i=n;i>=1;i--)if(sa[i]>k)nsa[b[rk[sa[i]-k]]--]=sa[i]-k;
		for(int i=n;i>=1;i--)if(sa[i]>n-k)nsa[b[rk[sa[i]]]--]=sa[i];
		nrk[nsa[1]]=1;
		for(int i=2;i<=n;i++)nrk[nsa[i]]=nrk[nsa[i-1]]+(usb(nsa[i-1])<usb(nsa[i]));
		swap(sa,nsa);
		swap(rk,nrk);
	}
	for(int i=1;i<=n;i++)rk[sa[i]]=i;
	int h=0;
	ll tmp=0;
	for(int i=1;i<=n;i++)
	{
		if(h>0)h--;
		if(rk[i]==1)continue;
		int j=sa[rk[i]-1];
		while(i+h<=n&&j+h<=n&&s[i+h]==s[j+h])h++;
		lcp[rk[i]-1]=h;
		tmp+=lcp[rk[i]-1];
	}
//	cout<<"tmp="<<1ll*n*(n+1)/2-tmp<<endl;
	for(int i=1;i<=n;i++)
	{
		for(int j=sa[i];j<=n;j++)cerr<<s[j];
		cerr<<" lcp="<<lcp[i]<<" "<<sa[i]<<endl;
	}
	for(int i=1;i<=n;i++)tab[0][i]=lcp[i];
	for(int i=1;i<20;i++)
	{
		for(int j=1;j<=n-(1<<i);j++)
		{
			tab[i][j]=min(tab[i-1][j],tab[i-1][j+(1<<(i-1))]);
		}
	}
	for(int i=2;i<100011;i++)lg2[i]=lg2[i>>1]+1;
}

