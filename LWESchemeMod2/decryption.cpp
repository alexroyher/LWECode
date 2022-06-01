#include "decryption.h"
#include "encryption.h"


void decrypt(DecryptionScheme& DS, long q, long k, long l){
	DS.M = DS.V-DS.U*DS.S;

	for (int i = 0; i < k; ++i){
		for ( int j = 0; j < l; ++j){
			if ( conv<long>(DS.M[i][j])<= q/4 || conv<long>(DS.M[i][j]) >= 3*q/4){
	    		DS.M[i][j] = 0;
	    	}
	    	else {DS.M[i][j] = 1;}
		}
	}
}