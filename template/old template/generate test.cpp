//generate tests
#include<bits/stdc++.h>
using namespace std;
const bool israndom=0;
const int testnum=10;
const string name="rmq";
void generate(int n,int m)
{
	cout<<n<<" "<<m<<endl;
	while(m--)
	{
		int op=rand()%3;
		cout<<op<<" ";
		int x=rand()%n+1,y=rand()%n+1;
		double v=1.0*rand()/rand();
		if(x>y)
			swap(x,y);
		cout<<x<<" "<<y;
		if(op==0)
			cout<<endl;
		else
			cout<<fixed<<setprecision(8)<<" "<<v<<endl;	
	}
}
void generatetest(int id)
{
	generate(100,100);
}
char* stringtochar(string s)
{
	char *ch=new char[100];
	for(int i=0;i<100;i++)
		ch[i]=0;
	for(int i=0;i<s.size();i++)
		ch[i]=s[i];
	return ch;
}
string inttostring(int x)
{
	string s;
	if(x==0)
	{
		s='0';
	}
	else
	{
		while(x>0)
		{
			char c='0'+x%10;
			s=c+s;
			x/=10;
		}
	}
	return s;
}
int main()
{
	if(israndom)
		srand(time(NULL));
	for(int i=0;i<testnum;i++)
	{
		cerr<<"Generating test "<<i<<endl;
		freopen(stringtochar(name+".in"),"w",stdout);
		generatetest(i);
		fclose(stdout);
		system(stringtochar(name+".exe"));
		string number=inttostring(i);
		string cmd1="copy "+name+".in "+name+number+".in";
		string cmd2="copy "+name+".out "+name+number+".ans";
		system(stringtochar(cmd1));
		system(stringtochar(cmd2));
		cerr<<"Test "<<i<<" generated."<<endl;
	}
	fclose(stdout);
	cerr<<"All tests generated successfully."<<endl;
	system(stringtochar("del "+name+".in"));
	system(stringtochar("del "+name+".out"));
	return 0;
}

