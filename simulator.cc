#include <bits/stdc++.h>
#include "simulatorclass.cc"

#define pp pair<ll,ll>
#define ll long long int
#define tr(a,x) for(auto a:x)
#define tri(a,x) for(auto a=x.begin();a!=x.end();a++)
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x).size()
#define fo(i,x) for(int i=0;i<x;i++)
#define p_b(x,i) x.push_back(i)
#define printe(i) cout<<i<<" "
#define printed(x,i) cout<< x  <<i<<"\n"
#define ip(s) vector <s>vec;for(int i=0;i<n;i++){s tmp;cin>>tmp;vec.push_back(tmp);}
#define op(s) for(auto i:s) cout<<i<<" ";cout<<"\n";
#define vi vector<ll>
#define vpp vector<pair<ll,ll>>
#define newl cout<<"\n"
#define opa(s) tr(a,s){op(a);newl;}

using namespace std;

inline bool exists(string& name) {
    ifstream f(name.c_str());
    return f.good();
}
int main(int arc,char *argv[])
{
	cout<<"enter the file name for program\n";
	string fil;
	cin>>fil;
	if(!exists(fil))
	{
		cout<<"file doesnt exist\n";
		exit(0);
	}
	prog p(fil);
	//prog1.print();
	cout<<"Do you want single cycle simulator(0) or MIPS multicycle/pipelined (1) or R4000 MIPS Pipelined(2)?\n";
	int ch;
	cin>>ch;
	if(ch==0)
	{
		singlecycle_simulator sim;
		sim.simulate(p);
	}
	else
	{
		if(ch==1)
		{
			pipelined_simulator sim;
			cout<<"do you want to print each step status to a file[steps.txt]?(y/n)\n";
			char x;
			cin>>x;
			if(x=='n')
				sim.simulate(p,true,false);
			else
				sim.simulate(p,true,true);
		}
		else
		{
			r4000_pipelined_simulator sim;
			cout<<p.print();
			cout<<"do you want to print each step status to a file[steps.txt]?(y/n)\n";
			char x;
			cin>>x;
			if(x=='n')
				sim.simulate(p,true,false);
			else
				sim.simulate(p,true,true);
		}
	}
	//pipelined_simulator sim1;
	//sim1.simulate(prog1,true,true);
	//singlecycle_simulator sim2;
	//sim2.simulate(prog1);
	return 0;
}


