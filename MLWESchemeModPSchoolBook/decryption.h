#ifndef HEADER_DECRYPTION
#define HEADER_DECRYPTION

#include <NTL/mat_ZZ_p.h>
#include <NTL/ZZX.h>
#include <NTL/ZZ_pX.h>
#include <vector>

using namespace NTL;
using namespace std;

class DecryptionScheme{

public:
	mat_ZZ_p U,V,S,M;
	ZZ_pXModulus F;
	ZZ_pX f; 
	ZZ_pX* u_p;
	ZZ_pX* S_p;
	ZZ_pX  v_p;
	DecryptionScheme(mat_ZZ_p& U, mat_ZZ_p& V, mat_ZZ_p& S){
		this->U = U;
		this->V = V;
		this->S = S;
	}
	DecryptionScheme(ZZ_pX* & u_p, ZZ_pX& v_p, ZZ_pX*& S_p, long d){
		this->u_p = u_p;
		this->v_p = v_p;
		this->S_p = S_p;
		f.SetLength(d+1);
		f[0] = 1;
		f[d] = 1;
		build(F,f);
	}
};

//Decrypt the message

ZZX decrypt(DecryptionScheme& DS,long q,long d,long n,long p);

#endif