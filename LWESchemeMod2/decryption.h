#ifndef HEADER_DECRYPTION
#define HEADER_DECRYPTION

#include <NTL/mat_ZZ_p.h>
#include <vector>

using namespace NTL;
using namespace std;

class DecryptionScheme{

public:
	mat_ZZ_p U,V,S,M;
	DecryptionScheme(mat_ZZ_p& U, mat_ZZ_p& V, mat_ZZ_p& S){
		this->U = U;
		this->V = V;
		this->S = S;
	}
};

//Decrypt the message
void decrypt(DecryptionScheme& DS,long q,long k, long l);

#endif