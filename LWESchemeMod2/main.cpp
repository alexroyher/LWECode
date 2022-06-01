#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/mat_ZZ_p.h>
#include <vector>
#include "encryption.h"
#include "decryption.h"

using namespace std;
using namespace NTL;




int main(int argc, char** argv){

	//Parameters of the scheme
	long p,n,beta,q,l,k,m;

	m = 512;
	n = 256;
	beta = 2;
	q = 16411;
	k = l = 16;
	//Set Z_q
  	ZZ_p::init(to_ZZ(q));

	//Define Encryption Scheme
	EncryptionScheme ES(n,m,beta,k,l,q);

	//Generate random key A of size (m,m)
	generatePKey_A(ES);

	//Generate matrix T of the public key
	generatePKey_T(ES);

	//Encrypt the message
	encrypt(ES);

	//Once we have encrypted, we can decrypt
	DecryptionScheme DS(ES.U, ES.V, ES.S);

	decrypt(DS,q,k,l);

	cout << "Plaintext" << endl;
	cout << ES.M << endl;
	cout << "Decrypted text" << endl;
	cout << DS.M << endl;

	//Check if the decryption was succesful (1 if success, 0 else)
	ZZ_p::init(to_ZZ(2));
	cout << "Result: " << IsZero(ES.M-DS.M) << endl;
}
