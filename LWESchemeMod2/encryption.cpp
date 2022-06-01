#include "encryption.h"


int mod(int a, int b) { 
	return (a % b + b) % b;
}

void generatePKey_A(EncryptionScheme& ES){
	random(ES.A,ES.m,ES.n);
}


void generatePKey_T(EncryptionScheme& ES){
	//We start generating the secret key S and E1 matrix
	int range = 2*ES.beta + 1;
	int rand_n,i,j;
	mat_ZZ_p S, E1, T;
	random(ES.S,ES.n,ES.l);
	random(E1,ES.m,ES.l);
 	for( i = 0; i < ES.n; ++i){
 		for( j = 0;  j < ES.l; ++j){
 			rand_n = rand() % range;
 			ES.S[i][j] = conv<ZZ_p>(mod(rand_n - ES.beta,ES.q));
 		}
  	}
  	for( i = 0; i < ES.m; ++i){
 		for( j = 0;  j < ES.l; ++j){
  	 		rand_n = rand() % range;
 			E1[i][j] = conv<ZZ_p>(mod(rand_n - ES.beta,ES.q));
 		}
 	}
  	ES.T = ES.A*ES.S+E1;
}

void encrypt(EncryptionScheme& ES){
	//First, as before, we generate R,E2 and E3 matrix
	int range = 2*ES.beta + 1;
	int rand_n,i,j,w,v;

	mat_ZZ_p R, E2, E3;
	random(R,ES.k,ES.m);
	random(E2,ES.k,ES.n);
	random(E3,ES.k,ES.l);

 	for( i = 0; i < ES.k; ++i){
 		for( j = 0;  j < ES.m; ++j){
 			rand_n = rand() % range;
 			R[i][j] = conv<ZZ_p>(mod(rand_n - ES.beta,ES.q));
 		}
 		for( v=0; v< ES.n ;++v){
 			rand_n = rand() % range;
 			E2[i][v] = conv<ZZ_p>(mod(rand_n - ES.beta,ES.q));
 		}
 		for( w = 0; w < ES.l; ++w){
 			rand_n = rand() % range;
 			E3[i][w] = conv<ZZ_p>(mod(rand_n - ES.beta,ES.q));
 		}
  	}
    ES.U = R*ES.A+E2;
    ES.V = R*ES.T+E3+(ES.q/2)*ES.M; 


}