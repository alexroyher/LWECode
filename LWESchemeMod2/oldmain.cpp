#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/mat_ZZ_p.h>
#include <vector>

using namespace std;
using namespace NTL;

int mod(int a, int b) { 
	return (a % b + b) % b;
}


int main(int argc, char** argv){


	long m,beta,q,l,k,N;
	//Define the size of the matrix message
	l = k = 16;
	m = 256;
	beta = 2;
	q = 8210;  
	ZZ_p::init(to_ZZ(q));
	srand(time(0));

	//Generate random matrix A (mxm) over Z_q
	mat_ZZ_p A;
	random(A,m,m);

	//Generate secret key S (m x l) with elements in [beta]
	//Generate E1 (m x l) with elements in [beta]
	//Compute T elements




	int range = 2*beta + 1;
	int rand_n, S[m][l], E1[m][l],T[m][l], i ,j, w, R[k][m], E2[k][m], E3[k][l];
 	for( i = 0; i < m; ++i){
 		for( j = 0;  j < l; ++j){
 			rand_n = rand() % range;
 			S[i][j] = mod(rand_n - beta,q);
 			rand_n = rand() % range;
 			E1[i][j] = mod(rand_n - beta,q);

 		}
  	}

  	for( i = 0; i < m; ++i){
 		for( j = 0;  j < l; ++j){
  			T[i][j] = 0;
            for (int w = 0; w < m; ++w) {
                T[i][j] += mod(conv<long>(A[i][w]) * S[w][j],q) ;
                T[i][j] = mod(T[i][j],q);
            }
            T[i][j] = mod(T[i][j]+E1[i][j],q);
  		}
  	}

  	//Select the Matrix message we want to encrypt
  	ZZ_p::init(to_ZZ(2));
  	mat_ZZ_p M;
  	random(M,k,l);


  	//Encryption
  	int U[k][m];
  	for( i=0; i<k; ++i){
  		for( j =0; j<m; ++j){
  			rand_n = rand() % range;
  			R[i][j] = mod(rand_n - beta,q);

  			rand_n = rand() % range;
  			E2[i][j] = mod(rand_n - beta,q);
  		}
  		for( w =0; w<l; ++w){
  			rand_n = rand() % range;
  			E3[i][w] = mod(rand_n - beta,q);
  		}
  	}

  	//Compute U
  	for( i=0; i<k; ++i){
  		for( j =0; j<m; ++j){
  			U[i][j]=0;
  			for( w=0; w< m;++w){
  				U[i][j] +=mod(R[i][w]*conv<long>(A[w][j]),q);
  				U[i][j] = mod(U[i][j],q);
  			}
  			U[i][j] = mod(U[i][j]+E2[i][j],q);
  		}
  	}

  	//Compute V 
  	long factor = q/2;
  	int V[k][l];
    for ( i = 0; i < k; ++i) {
        for (j = 0; j < l; ++j) {
            V[i][j] = 0;
            for ( w = 0; w < m; ++w) {
                V[i][j] += mod(R[i][w] * T[w][j],q);
                V[i][j] = mod(V[i][j],q);
            }
            V[i][j] = mod(V[i][j]+E3[i][j],q);
            V[i][j] += mod(factor*conv<long>(M[i][j]),q);
            V[i][j] = mod(V[i][j],q);
        }
    }

    //Decryption we are given the cipher-text (U,V) and the secret key S
    int D[k][l];
    for ( i=0; i<k; ++i){
    	for ( j=0; j<l; ++j){
    		D[i][j] = 0;
    		for( w=0;w<k;++w){
    			D[i][j]+=mod(U[i][w]*S[w][j],q);
    			D[i][j] = mod(D[i][j],q);
    		}
	    	D[i][j] = mod(mod(-D[i][j],q)+mod(V[i][j],q),q);
	    	if (D[i][j] <= q/4){
	    		D[i][j] = 0;
	    	}
	    	else {D[i][j] = 1;}
	    	cout << D[i][j] << " " << M[i][j] << endl;
    	}
    }
}