#include "decryption.h"
#include "encryption.h"


ZZ_pX SchoolBookMultiplicationv2(ZZ_pX A, ZZ_pX B,long d, ZZ_pXModulus F) {
   	ZZ_pX productPolynomial;
   	productPolynomial.SetLength(2*d-1);
   	for (int i = 0; i < d; i++) {
     	for (int j = 0; j < d; j++) {
        	productPolynomial[i + j] += A[i] * B[j];
      	}
   	}
   	ZZ_pX x;
	rem(x, productPolynomial,F);
	return x;
}

ZZX decrypt(DecryptionScheme& DS, long q,long d,long n,long p){
	ZZ_pX res;
	res.SetLength(d);

	for(int i=0;i < n;++i){
		res+= SchoolBookMultiplicationv2(DS.u_p[i],DS.S_p[i],d,DS.F);
	}
	res = DS.v_p - res;
	ZZX res_intt;
	res_intt.SetLength(d);
	for (int j=0;j<d;j++){
		res_intt[j] = mod(conv<long>(res[j])-(conv<long>(res[j])>q/2)*q,p);
	}
	cout << res_intt << endl;
	return res_intt;
}