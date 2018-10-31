// mbf9exact.cpp : Defines the entry point for the console application.
//
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include "quicklist.h"
#include "mbf6.h"
#include "swap.h"
#include "consts.h"
#include "time_ms.h"

using namespace std;

const int short_size = 16353;
const int m_size = 7828354;

struct mbf7
{
	ull f1;
	ull f2;
};

//ull* xs6 = new ull[short_size];
//ull* xsh = new ull[m_size];
//int* xshp = new int[m_size];
ull* bits = new ull[1 << n];
mbf7* sorted = new mbf7[nf];

int cmp7(const mbf7 f1, const mbf7 f2)
{
	if (f1.f1<f2.f1) return -1;
	if (f1.f1>f2.f1) return 1;
	if (f1.f2<f2.f2) return -1;
	if (f1.f2>f2.f2) return 1;
	return 0;
}

int cmp7v (const void* f1, const void* f2)
{
	return cmp7(*(mbf7*)f1,*(mbf7*)f2);
}

int bit_count(ull x)
{
	int ret = 0;
	ull t = x;
	while (t>0)
	{
		ret += (t & 1);
		t = t >> 1;
	}
	return ret;
}

int bitcount7(mbf7 x)
{
	return bit_count(x.f1)+ bit_count(x.f2);
}

int locate(const ull x, ull* table, int cnt)
{
	int imin = 0;
	if (table[imin]==x) return imin;

    int imax = cnt-1;
	if (table[imax]==x) return imax;

	int imed;
	imed = (imin+imax) >> 1;
	while (table[imed] != x)
	{
		if (table[imed] < x)
			imin = imed;
		else
			imax = imed;
		imed = (imin+imax) >> 1;
	}
	return imed;
}

ull get_bit7(const mbf7 x, const int bitpos)
{
	if (bitpos<64)
		return (x.f2 >> bitpos) & 1ll;
	else
		return (x.f1 >> (bitpos-64)) & 1ll;
}

void transform7(mbf7& out, const mbf7 x, const int tnum)
{
	assert(tnum < nf);
	out.f1 = 0LL;
	out.f2 = 0LL;
	int i;
	for (i=0; i< (1 << n); i++)
	{
		ull biti = bits[i];
		if (biti > 0)
		{
			int pos = (int)newpos[tnum][i];
			if (pos<64)
			{
				set_bit(out.f2, pos, biti);
			}
			else
			{
				set_bit(out.f1, pos-64, biti);
			}
		}
	}
}

ull transform_min(ull f)
{
	ull res = f;
	int i;
	for (i=0;i<nf;i++)
	{
		ull rr = transform(f,i);
		if (rr < res) res = rr;
	}
	return res;
}

int transform_cnt(ull f)
{
	int i,j;
	int cnt = 1;
	ull* vers = new ull[nf];

	for (i=0;i<nf;i++)
	{
		vers[i] = transform(f,i);
	}

	for (i=1;i<nf;i++)
	{
		bool f = true;
		for (j=0;j<i;j++)
		{
			if (vers[i]==vers[j])
				f = false;
		}
		if (f) cnt++;
	}
	delete[] vers;
	return cnt;
}

bool ismin7(mbf7 x)
{
	int i;
	for (i=0;i<nf;i++)
	{		
		transform7(sorted[i],x,i);
		if (sorted[i].f1 < x.f1) return false;
		if ((sorted[i].f1 == x.f1) && (sorted[i].f2<x.f2)) return false;
	}
	return true;
}

int main(int argc, char** argv)
{	    
	make5();
	make_bittran();
	int i,j;
	int cnt = 0;
	int cs = 0;
	int ccs = 0;
	//for (i=0;i<m_size;i++)
	//	for(j=i;j<m_size;j++)
	/*
	mbf7 t;
	t.f1 = 0;
	t.f2 = 3;
	for (i=0;i<nf;i++)
	{
		mbf7 tmp;
		transform7(tmp,t,i);
		cout << tmp.f1 << "\t" << tmp.f2 << endl;
	}
	//system("pause");

	//while (true)
	cout << ismin7(t) << endl;
	*/
	int* buf = new int[30000];
	string s = "/data/mbf9exact/data/data";
	s  += argv[1];
	s  +=".bin";
	ofstream myFile (s.c_str(), ios::out | ios::binary);


	//for (i=0;i<m_size;i++)
	i = atoi(argv[1]);
	ull sums = 0;
	double tm0 = TimeMillis();
		for(j=i;j<m_size;j++)
		{
			//i = rand() % m_size;
			//j = rand() % m_size;
			if (cmp(i,j,x6))
			{
				mbf7 x;
				x.f1 = x6[i];
				x.f2 = x6[j];
				cnt++;
				int tmp;
				for (tmp = 0; tmp < (1<< n);tmp++)
				{
					bits[tmp] = get_bit7(x,tmp);
				}

				if (ismin7(x))				
				{
					//cout << i << "\t" << j << endl;
					//cs ++;
					qsort((void*)sorted,nf,sizeof(mbf7),cmp7v);
					int smcnt = 1;
					for (tmp=1; tmp<nf;tmp++)
					{
						if (cmp7(sorted[tmp-1],sorted[tmp]) != 0)
						{
							smcnt++;
						}
					}
					buf[ccs*3] = i;
					buf[ccs*3+1] = j;
					buf[ccs*3+2] = smcnt;
					sums += smcnt;
					cs++;
					ccs++;

				}
			}
			if (ccs%10000==0 && ccs > 0)
			{
				//cout << "#" << cnt << "\t" << cs << "\t" << (1.0*cnt/cs) << endl;
				myFile.write((const char*)buf, sizeof(int)*ccs*3);
				ccs = 0;
			}
		}
	double tm1 = TimeMillis();
	myFile.write((const char*)buf, sizeof(int)*3*ccs);
	cout << cs << endl;
	cout << (tm1-tm0) << endl;
	cout << sums << endl;
	//system("pause");
}