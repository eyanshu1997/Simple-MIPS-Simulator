#include <bits/stdc++.h>
#include "otherclasses.cc"
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

class singlecycle_simulator
{
	public:
	int registers[32];
	int data[512];
	void execute(instructions inst)
	{
		if(inst.type='R')
		{
			if(inst.rs>31||inst.rt>31||inst.dest>31)
			{
				assert(!"Invalid register location");
			}
			switch(inst.op)
			{
				case "add":
					registers[inst.dest]=registers[inst.rs]+registers[inst.rt];
					break;
				case "sub":
					registers[inst.dest]=registers[inst.rs]-registers[inst.rt];
					break;
				case "mul":
					registers[inst.dest]=registers[inst.rs]*registers[inst.rt];
					break;
			}
		}
		else
		{
			if(inst.rs>31)
			{	
				assert(!"Invalid register location");
			}
			switch(inst.op)
			{
				case "addi":
					registers[inst.dest]=registers[inst.rs]+inst.i;
					break;
				case "lw":
					if(inst.i % 4 == 0)
					{
						int y = registers[inst.rs] + inst.i/4;
					}
					else
					{
						assert(!"Misaligned memory access");
					}
					if(&data[y] == NULL)
					{
						assert(!"Read from invalid data memory location");
					}
					registers[inst.rt] = data[y];
					break;
				case "sw":
					if(inst.i % 4 == 0)
					{
						int y = registers[inst.rs] + inst.i/4;
					}
					else
					{
						assert(!"Misaligned memory access");
					}
					if(&data[y] == NULL)
					{
						assert(!"Read from invalid data memory location");
					}
					data[y]=registers[inst.rt];
					break;
				case "beq":
					if(registers[inst.rs] == registers[inst.rt])
					{
						p.pc= p.pc + inst.i;
						if(p.pc >sz(p.instlist)-1)
						{
							assert(!"Branched out of program");
						}
					}
					break;
					
			}
		}
	}
	void simulate(prog p)
	{
		using namespace std::chrono; 
		auto start = high_resolution_clock::now();
		fo(i,sz(p.instlist)-1)
		{
			instructions tmp=instlist[i];
			execute(tmp);
		}
		auto stop = high_resolution_clock::now(); 
		auto duration = duration_cast<microseconds>(stop - start); 
		cout<<"total cycles is"<<sz(p.instlist)-1<<"\n";
		cout<<"time taken is "<<duration.count()<<" microseconds\n";
	}
};
