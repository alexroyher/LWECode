#ifndef HEADER_NTT	
#define HEADER_NTT

#include <limits.h>
#include <NTL/mat_ZZ_p.h>
#include <NTL/ZZX.h>
#include <vector>
#include <assert.h> 
#include <math.h> 


using namespace NTL;
using namespace std;

ZZ NthRootOfUnity(ZZ M, ZZ N);

ZZ reverseBits(ZZ n, ZZ len);

ZZX orderReverse(ZZX a, ZZ N_bit);


class NTTScheme{

public:
	ZZX power_of_roots;
	ZZX inv_power_of_roots;
	/* Initialization of the NTT object */
	NTTScheme(){}
	NTTScheme(ZZ N, ZZ q){
		ZZ w = NthRootOfUnity(q,2*N);
		ZZ N_bit_length =  ZZ(log2(conv<int>(N)) +1) ;
		ZZ N_bit = N_bit_length - 1;
		this->power_of_roots.SetLength(conv<int>(N));
		this->inv_power_of_roots.SetLength(conv<int>(N));
		for (int i=0;i<N; i++){
			power_of_roots[i] = PowerMod(w,ZZ(i),q);
			inv_power_of_roots[i] = InvMod(power_of_roots[i],q);
		}
		this->power_of_roots = orderReverse(this->power_of_roots,N_bit);
		this->inv_power_of_roots = orderReverse(this->inv_power_of_roots,N_bit);
	}	
};

ZZX FNTT(NTTScheme& NTT,ZZX a, ZZ q, ZZ N);

ZZX INTT(NTTScheme& NTT, ZZX a, ZZ q, ZZ N);


#endif