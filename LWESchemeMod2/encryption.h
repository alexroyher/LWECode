#ifndef HEADER_ENCRYPTION
#define HEADER_ENCRYPTION

#include <NTL/mat_ZZ_p.h>
#include <vector>

using namespace NTL;
using namespace std;

class EncryptionScheme{

public:

	mat_ZZ_p A,S,T,U,V,M;
	long n,m,k,l,beta,q,p;

	EncryptionScheme(long n,long m,long beta,long k,long l,long q){
		this->m = m;
		this->n = n;
		this->beta = beta;
		this->k = k;
		this->l = l;
		this->q = q;
		ZZ_p::init(to_ZZ(2));
	  	mat_ZZ_p M;
	  	random(M,k,l);
	  	ZZ_p::init(to_ZZ(this->q));
	  	this->M = M;

	  	srand(time(0));
	}
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

#endif