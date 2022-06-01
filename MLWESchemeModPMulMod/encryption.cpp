#include "encryption.h"

int mod(int a, int b) { 
	return (a % b + b) % b;
}

void generatePKey_A(EncryptionScheme& ES){
	ES.A_p = new ZZ_pX*[ES.m];
	for (int i = 0; i<ES.m; i++){
		ES.A_p[i] = new ZZ_pX[ES.n];
		for (int j=0;j<ES.n; j++){
			ES.A_p[i][j] =random_ZZ_pX(ES.d);
		}
	}
}

void generatePKey_T(EncryptionScheme& ES){
	//We start generating the secret key S and E1 matrix
	int range = 2*ES.beta + 1;
	int rand_n;

	ES.S_p = new ZZ_pX[ES.n];
	ZZ_pX *E1_p = new ZZ_pX[ES.m];

	for (int i=0;i<ES.m;i++){
		E1_p[i].SetLength(ES.d);
		for (int j=0;j<ES.d;j++){
			rand_n = rand() % range;
			E1_p[i][j] = conv<ZZ_p>(mod(rand_n - ES.beta,ES.q));
		}
	}
	for(int i=0;i<ES.n; i++){
		ES.S_p[i].SetLength(ES.d);	
		for (int j=0;j<ES.d;j++){
			rand_n = rand() % range;
			ES.S_p[i][j] = conv<ZZ_p>(mod(rand_n - ES.beta,ES.q));
		}
	}
	ES.t = new ZZ_pX[ES.m];
	for (int i = 0;i < ES.m;i++){
		ZZ_pX sum;
		sum.SetLength(ES.d);
		for(int j=0; j< ES.n; j++){
			sum += MulMod(ES.A_p[i][j], ES.S_p[j],ES.F);
		}
		ES.t[i] = sum + ES.p*E1_p[i];
	}

}

void encrypt(EncryptionScheme& ES){
	//First, as before, we generate R,E2 and E3 matrix
	int range = 2*ES.beta + 1;
	int rand_n,i,j,w,v;
	ZZ_pX *r_p = new ZZ_pX[ES.m];
	ZZ_pX *E2_p = new ZZ_pX[ES.n];

	for(int i=0;i<ES.m; i++){
		r_p[i].SetLength(ES.d);
		for (int j=0;j<ES.d;j++){
			rand_n = rand() % range;
			r_p[i][j] = conv<ZZ_p>(mod(rand_n - ES.beta,ES.q));
		}
	}
	for(int i=0;i<ES.n; i++){
		E2_p[i].SetLength(ES.d);
		for (int j=0;j<ES.d;j++){
			rand_n = rand() % range;
			E2_p[i][j] = conv<ZZ_p>(mod(rand_n - ES.beta,ES.q));
		}
	}

	ZZ_pX E3_p;
	E3_p.SetLength(ES.d);
	for (int j=0;j<ES.d;j++){
		rand_n = rand() % range;
		E3_p[j] = conv<ZZ_p>(mod(rand_n - ES.beta,ES.q));
	}
	ES.u_p = new ZZ_pX[ES.n];

	for (int j=0;j<ES.n;++j){
		ZZ_pX sum;
		sum.SetLength(ES.d);
		for(int i=0;i<ES.m;++i){
			sum +=MulMod(ES.A_p[i][j], r_p[i],ES.F);
		}
		ES.u_p[j] = sum + ES.p*E2_p[j];
	}
	ES.v_p.SetLength(ES.d);

	for(int i=0;i<ES.m; ++i){
		ES.v_p += MulMod(r_p[i], ES.t[i],ES.F);
	}
	ES.v_p +=ES.p*E3_p;
	ES.v_p += ES.mu;
}