#include <bits/stdc++.h>
#include "pipelined_simulator.cc"
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

int main(int arc,char *argv[])
{
	if(arc<2)
	{
		printf("enter the file name as arg ");
		return 0;
	}
	string fil(argv[1]);
	prog prog1(fil);
	prog1.print();
	pipelined_simulator sim;
	sim.simulate(prog1);
	return 0;
}


