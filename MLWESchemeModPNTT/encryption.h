#ifndef HEADER_ENCRYPTION
#define HEADER_ENCRYPTION

#include "NTT.h"
#include <NTL/mat_ZZ_p.h>
#include <NTL/ZZ_pX.h>


using namespace NTL;
using namespace std;

class EncryptionScheme{

public:

	long n,m,beta,q,d,p;
	ZZ_pXModulus F;
	ZZ_pX f; 
	NTTScheme *NTT;
	ZZ_pX **A_p;
	ZZ_pX *t;
	ZZ_pX mu;
	ZZ_pX *u_p;
	ZZ_pX v_p;
	ZZ_pX *S_p;
	EncryptionScheme(long n,long m,long beta,long q, long d,long p){
		srand(time(0));
		NTTScheme *NTT = new NTTScheme(ZZ(d),ZZ(q));
		this->NTT = NTT;
		this->m = m;
		this->n = n;
		this->beta = beta;
		this->q = q;
		this->d = d;
		this->p = p;
		f.SetLength(d+1);
		f[0] = 1;
		f[d] = 1;
		build(F,f);
		int range = p;
		int rand_n;
		this->mu.SetLength(d);
		for (int j=0;j<d;j++){
			rand_n = rand() % range;
			mu[j] = conv<ZZ_p>(rand_n) ;
		}
		cout << this->mu << endl;
	}
;
	
};


//We'll use this function to compute the modulus of
//negative number
int mod(int a, int b);

//Generate Matrix A, first part of public key
void generatePKey_A(EncryptionScheme& ES);

//Generate Matrix T ,second part of public key
void generatePKey_T(EncryptionScheme& ES);

//Encryption of the message
void encrypt(EncryptionScheme& ES);

//Perform NTT multiplication
ZZ_pX performNTTMultiplication(EncryptionScheme& ES,ZZ_pX A, ZZ_pX B);

#endif