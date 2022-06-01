#include "NTT.h"

/*
	Check if r^k = 1 mod M 
*/

bool existSmallN(ZZ r, ZZ M, ZZ N){
	for (int k = 2; k<N; k++){
		if (PowerMod(r,k,M) == 1){
			return true;
		}
	}
	return false;
}

/*
	Find a Nth root of unity 
*/

ZZ NthRootOfUnity(ZZ q, ZZ N){
	assert((q-1) % N == 0);
	ZZ phi = q-1;
	srand(time(NULL));
	while(true){
		ZZ alpha = ZZ(rand() % conv<int>(q) + 1);
		ZZ beta = PowerMod(alpha,phi / N, q);
		if(!existSmallN(beta,q,N)){
			return ZZ(beta);
		}
	}
}

/* 
	Reverse bits given a number 
	and its length
*/

ZZ reverseBits(ZZ n, ZZ len) {
    ZZ res = ZZ(0);
    for (int i = 0; i < len; i++) {
        if (conv<int>(n) & (1 << i))
            res |= 1 << (conv<int>(len) - 1 - i);
    }
    return res;
}


/*
	Reverse order of a polynomial 
*/

ZZX orderReverse(ZZX a, ZZ N_bit){
	for(int i=0;i<deg(a);i++){
		ZZ rev_i = reverseBits(ZZ(i), N_bit);
		if (rev_i > i){
			ZZ coef = a[conv<int>(rev_i)];
			a[conv<int>(rev_i)] = a[i];
			a[i] = coef;
		}
	}
	return a;
}

/*
	Perform forward NTT
*/

ZZX FNTT(NTTScheme& NTT,ZZX a, ZZ q, ZZ N){
	int t = (conv<int>(N)/2);
	int m=1;
	while(m<N){
		int k = 0;
		for (int i=0;i<m; i++){
			ZZ S = NTT.power_of_roots[m+i];
			for (int j=k; j<k+t; j++){
				ZZ U =a[j];
				ZZ V =a[j+t]*S % q;
				a[j] = (U+V) % q;
				a[j+t] = (U-V) % q;
			}
			k = k+2*t;
		}
		t = t/2;
		m = 2*m;
	}
	return a;
}

/*
	Perform inverse NTT
*/

ZZX INTT(NTTScheme& NTT,ZZX a, ZZ q, ZZ N){
	ZZ inv_N = InvMod(N, q);
	int t = 1;
	ZZ m = (N/2);
	while(m>0){
		int k=0;
		for (int i=0;i < m; i++){
			ZZ S = NTT.inv_power_of_roots[conv<int>(m)+i];
			for (int j=k;j<k+t; j++){
				ZZ U = a[j];
				ZZ V = a[j+t];
				a[j] = (U+V) % q;
				ZZ W = (U-V) % q;
				a[j+t] = (W*S) % q;
			}
			k = k+2*t;
		}
		t = 2*t;
		m = m/2;
	}
	for (int i=0;i <N; i++){
		a[i] = (a[i] * inv_N ) % q;
	}
	return a;
}

