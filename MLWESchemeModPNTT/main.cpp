#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/mat_ZZ_p.h>
#include <vector>
#include "encryption.h"
#include "decryption.h"
#include "helper.h"

using namespace std;
using namespace NTL;

long generate_prime(long N){
	long k=1;
	while(!(isPrime(ZZ(k*N+1)))){
		k++;
	}
	return k*N+1;
}


int main(int argc, char** argv){

	//Parameters of the scheme
	long p,n,beta,q,l,k,m,d;

	m = 32;
	n = 32;
	beta = 2;
	//Polynomial degree
	d = 16384;
	q = generate_prime(2*d);
	//Message Space such that beta^2*m + beta < q/2p
	p = 3;
	//Set Z_q
  	ZZ_p::init(to_ZZ(q));

 	//Define Encryption Scheme
	EncryptionScheme ES(n,m,beta,q,d,p);

	//Generate random key A of size (m,m)
	generatePKey_A(ES);

	//Generate matrix T of the public key
	generatePKey_T(ES);

	//Encrypt the message
	encrypt(ES);

	//Once we have encrypted, we can decrypt
	DecryptionScheme DS(ES.u_p, ES.v_p, ES.S_p,d);

	ZZX res = decrypt(DS,q,d,n,p);

	cout << IsZero(res - conv<ZZX>(ES.mu)) << endl;
}
