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
#define C 100
#define N 10
#define M 15
using namespace std;
class pipelined_simulator
{
	public:
	latch l1,l2,l3,l4;
	int registers[32];
	int data[512];
	int rawHazard()
	{
		instructions inst = l1.inst;
		if(l1.inst.type != 'B')
		{
			if(l2.warmed_up && inst.rs == l2.inst.dest && l2.inst.op != "sw")
			{
				if(inst.rs != 0)
				{
					return inst.rs;
				}
			}

			if(l3.warmed_up && inst.rs == l3.inst.dest && l3.inst.op != "sw")
			{
				if(inst.rs != 0)
				{
					return inst.rs;
				}
			}

			if(l4.warmed_up && inst.rs == l4.inst.dest && l4.inst.op != "sw")
			{
				if(inst.rs != 0)
				{
					return inst.rs;
				}
			}


			if(inst.type == 'R' || inst.op == "beq")
			{
				if(l2.warmed_up && inst.rt == l2.inst.dest && l2.inst.op != "sw")
				{
					if(inst.rt != 0)
					{
						return inst.rt;
					}
				}

				if(l3.warmed_up && inst.rt == l3.inst.dest && l3.inst.op != "sw")
				{
					if(inst.rt != 0)
					{
						return inst.rt;
					}
				}

				if(l4.warmed_up && inst.rt == l4.inst.dest && l4.inst.op != "sw")
				{
					if(inst.rt != 0)
					{
						return inst.rt;
					}
				}
			}
		}
		return -1;
	}

	void fetch(prog &p)
	{
		if(!p.branchpending)
		{
			if(!l1.valid)
			{
				//cout<<"executed fetch\n";
				//cout<<"pc is "<<p.pc<<"\n";
				l1.valid=true;
				l1.inst=p.instlist[p.pc];
				//l1.inst.print();
				if(p.pc<sz(p.instlist)-1)
				{
					//cout<<"incremented pc\n";
					p.pc=p.pc+1;
				}
				p.ifutil++;
				if(!l1.warmed_up)
				{
					l1.warmed_up=true;
				}
			}
		}

	}
	void decode(prog &p)
	{
		if(l1.valid && l1.warmed_up && !l2.valid)
		{
			//cout<<"executed decode\n";
			//l1.inst.print();
			if(rawHazard() == -1)//change this function
			{
				if(l1.inst.op == "beq")
				{
					p.branchpending = true;
				}
				l1.valid = false;
				l2.valid = true;
				l2.inst = l1.inst;
				if(l2.inst.type != 'B')
				{
					p.idutil++;
				}
				if(!l2.warmed_up)
				{
					l2.warmed_up = true;
				}
			}
			else
			{
				l2.valid = true;
				l2.inst = bubble;
			}
		}
	}
	void execute(prog &p)
	{
		if(l2.warmed_up && l2.valid)
		{
			//cout<<"executed execute\n";
			//l2.inst.print();
			static int e_cycles = 0;
			if(l2.inst.type == 'B')
			{
				if(!l3.valid)
				{
					l2.valid = false;
					l3.valid = true;
					l3.inst = l2.inst;
				}
			}
			else
			{
				if(!l3.valid  && ((e_cycles == M && l2.inst.op == "mul") || (e_cycles == N && l2.inst.op != "mul")) )
				{
					if(l2.inst.rs > 31 || l2.inst.rt > 31)
					{
						assert(!"Invalid register location");
					}
					if(l2.inst.op == "add")
					{
						l3.data = registers[l2.inst.rs] + registers[l2.inst.rt];
					}
					else if(l2.inst.op == "addi")
					{
						l3.data = registers[l2.inst.rs] + l2.inst.i;
					}
					else if(l2.inst.op == "sub")
					{
						l3.data = registers[l2.inst.rs] - registers[l2.inst.rt];
					}
					else if(l2.inst.op == "mul")
					{
						l3.data = registers[l2.inst.rs] * registers[l2.inst.rt];
					}
					else if(l2.inst.op  == "beq")
					{
						if(registers[l2.inst.rs] == registers[l2.inst.rt])
						{
							p.pc= p.pc + l2.inst.i;
							if(p.pc >sz(p.instlist)-1)
							{
								assert(!"Branched out of program");
							}
						}
						p.branchpending = false;
					}
					else if(l2.inst.op == "lw" || l2.inst.op == "sw")
					{
						if(l2.inst.i % 4 == 0)
						{
							l3.data = registers[l2.inst.rt];
							l3.inst.dest = registers[l2.inst.rs] + l2.inst.i/4;
						}
						else
						{
							assert(!"Misaligned memory access");
						}
					}
					else 
					{
						cout<<"instruction is\n";
						l2.inst.print();
						cout<<" opcode is "<<l2.inst.op<<"\n";
						assert(!"Unrecognized instruction");
					}
					e_cycles = 0;
					l2.valid = false;
					l3.valid = true;
					l3.inst = l2.inst;
					if(!l3.warmed_up)
					{
						l3.warmed_up = true;
					}
				}
				else if((e_cycles < M && l2.inst.op == "mul") || (e_cycles < N && l2.inst.op != "mul"))
				{
					e_cycles++;
				}
				p.exutil++;
			}	
		}
	}

	void mem(prog &p)
	{
		if(l3.warmed_up && l3.valid)
		{
			//cout<<"executed mem\n";
			//l3.inst.print();
			if(l3.inst.type == 'B')
			{
				if(!l4.valid)
				{
					l3.valid = false;
					l4.valid = true;
					l4.inst = l3.inst;
				}
			}
			else
			{
				static int m_cycles = 0;
				bool is_lw = l3.inst.op == "lw";
				bool is_sw = l3.inst.op == "sw";
				if(is_lw || is_sw)
				{
					if(m_cycles == C && !l4.valid)
					{
						m_cycles = 0;
						l3.valid = false;
						l4.valid = true; 
						l4.inst = l3.inst;
						if(!l4.warmed_up)
						{
							l4.warmed_up = true;
						}
						if(is_lw)
						{
							if(&data[l3.data] == NULL)
							{
								assert(!"Read from invalid data memory location");
							}
							l4.data = data[l3.inst.dest];
						}
						if(is_sw)
						{
							if(&data[l3.data] == NULL)
							{
								assert(!"Attempted to write to invalid data memory location");
							}
							data[l3.inst.dest] = l3.data;
						}
					}
					else if(m_cycles < C)
					{
						m_cycles++;
					}
				}
				else
				{
					l3.valid = false;
					l4.valid = true; 
					l4.inst = l3.inst;
					l4.data = l3.data;
					if(!l4.warmed_up)
					{
					l4.warmed_up = true;
					}
				}
				if(l3.inst.type != 'B')
				{
					p.memutil++;
				}
			}
		}
	}  

	void wb(prog &p)
	{
		if(l4.valid && l4.warmed_up)
		{
			//cout<<"executed wb\n";
			//l4.inst.print();
			if(l4.inst.op != "sw" && l4.inst.op != "beq" && l4.inst.op != "haltsimulation" && l4.inst.dest != 0 && l4.inst.type != 'B')
			{
				registers[l4.inst.dest] = l4.data;
				p.wbutil++;
			}   
			if(l4.inst.type == 'B' && l4.inst.op=="haltsimulation")
			{
				p.totally_done = true;
			}
			l4.valid = false; 
		}
	}
	void simulate(prog p)
	{
		int totalcycles=0;
		using namespace std::chrono; 
		auto start = high_resolution_clock::now();
		while(!p.totally_done)
		{
			wb(p);
			mem(p);
			execute(p);
			decode(p);
			fetch(p);	
			//cout<<"cycle done\n";
			totalcycles++;
		}
		auto stop = high_resolution_clock::now(); 
		auto duration = duration_cast<microseconds>(stop - start); 
		cout<<"total cycles is"<<totalcycles<<"\n";
		cout<<"time taken is "<<duration.count()<<" microseconds\n";
	}
};
