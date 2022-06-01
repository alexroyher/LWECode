#include "encryption.h"
#include "NTT.h"

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


ZZ_pX performNTTMultiplication(EncryptionScheme& ES,ZZ_pX A, ZZ_pX B){
	ZZX poly_A = conv<ZZX>(A); 
	ZZX poly_B = conv<ZZX>(B);
	poly_A.SetLength(ES.d);
	poly_B.SetLength(ES.d);
	ZZX temp_A_p = FNTT(*ES.NTT,poly_A,ZZ(ES.q),ZZ(ES.d));
	ZZX temp_S_p = FNTT(*ES.NTT,poly_B,ZZ(ES.q),ZZ(ES.d));
	ZZX temp_prod;
	temp_prod.SetLength(ES.d);
	for (int k=0;k<ES.d; k++){
		temp_prod[k] = temp_A_p[k]*temp_S_p[k];
	}
	ZZ_pX res_ntt = conv<ZZ_pX>(INTT(*ES.NTT,temp_prod, ZZ(ES.q),ZZ(ES.d)));
	ZZ_pX x;
	rem(x, res_ntt,ES.F);
	return x;
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
			sum += performNTTMultiplication(ES, ES.A_p[i][j], ES.S_p[j]);
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
			sum +=performNTTMultiplication(ES,ES.A_p[i][j], r_p[i]);
		}
		ES.u_p[j] = sum + ES.p*E2_p[j];
	}
	ES.v_p.SetLength(ES.d);

	for(int i=0;i<ES.m; ++i){
		ES.v_p += performNTTMultiplication(ES,r_p[i], ES.t[i]);
	}
	ES.v_p +=ES.p*E3_p;
	ES.v_p += ES.mu;
}