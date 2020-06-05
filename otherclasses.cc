#include <bits/stdc++.h>
#include "helperfunc.cc"
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

class instructions
{
	public:
	char type;
	string op;
	int rs;
	int rt;
	int dest;
	int i;
	instructions(char typea,string opa,int rsa,int rta,int desta,int ia)
	{
		type=typea;op=opa;rs=rsa;rt=rta;dest=desta;i=ia;
	}
	instructions()
	{
		type='B';op="bubble";rs=0;rt=0;dest=0;i=0;
	}
	instructions(string inst)
	{
		inst=trimInstruction(inst);
		string opcode=extractOpcode(inst);
		if(isRType(opcode))
		{
		    int rs = extractRegister(inst,1);
		    int rt = extractRegister(inst,2);
		    int rd = extractRegister(inst,0);
		    type = 'R';
		    op = opcode;
		    rs = rs;
		    rt = rt;
		    dest = rd;
		    i = -1;
		}
		else if(isIType(opcode))
		{
			int rst,imm;
			int rat = extractRegister(inst,0);
			if(opcode!="lw"&& opcode!="sw")
			{
				rst = extractRegister(inst,1);
				imm = extractImmediate(inst,2);
			}
			else
			{
				rst = extractBase(inst);
				imm = extractImmediate(inst,1);
			}
			type = 'I';
			op = opcode;
			rs = rs;
			rt = rat;
			dest = rat;
			i = imm;
		}
		else
		{
			cout<<opcode<<"\n";
			assert(!"Illegal opcode");
		}
	}
	void print()
	{
		cout<<op<<" $"<<rs<<", $"<<rt<<" $"<<dest<<" "<<i<<"\n";
	}
};
instructions bubble('B',"bubble",0,0,0,0);
class latch
{
	public:
	bool valid;
	int data;
	bool warmed_up;
	instructions inst;
	latch()
	{
		warmed_up=false;
	}
};

class prog
{
	public:
	vector<instructions> instlist;
	bool totally_done;
	int pc;
	bool branchpending;
	int ifutil;
	int idutil;
	int exutil;
	int memutil;
	int wbutil;
	prog(string filename)
	{
		totally_done=false;
		pc=0;
		branchpending=false;
		ifutil=0;
		idutil=0;
		exutil=0;
		memutil=0;
		wbutil=0;
		string line;
		ifstream file;
		file.open(filename);
		if(file.is_open())
		{
			while(getline(file,line))
			{
				instructions tmp(line);
				instlist.push_back(tmp);
			}
			file.close();
		}
		instructions tmp('B',"haltsimulation",-1,-1,-1,-1);
		instlist.push_back(tmp);
	}
	void print()
	{
		tr(a,instlist)
		{
			a.print();
		}
	}
};
