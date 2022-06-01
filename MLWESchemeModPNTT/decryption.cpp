#include "decryption.h"
#include "encryption.h"


ZZ_pX performNTTMultiplication(DecryptionScheme& DS, ZZ_pX A, ZZ_pX B, long d, long q){
	NTTScheme *NTT = new NTTScheme(ZZ(d),ZZ(q));
	ZZX poly_A = conv<ZZX>(A); 
	ZZX poly_B = conv<ZZX>(B);
	poly_A.SetLength(d);
	poly_B.SetLength(d);
	ZZ_pX temp_A_p = conv<ZZ_pX>(FNTT(*NTT,poly_A,ZZ(q),ZZ(d)));
	ZZ_pX temp_S_p = conv<ZZ_pX>(FNTT(*NTT,poly_B,ZZ(q),ZZ(d)));
	ZZ_pX temp_prod;
	temp_prod.SetLength(d);
	for (int k=0;k<d; k++){
		temp_prod[k] = temp_A_p[k]*temp_S_p[k];
	}
	ZZX poly_C = conv<ZZX>(temp_prod);
	poly_C.SetLength(d);
	ZZ_pX res_ntt = conv<ZZ_pX>(INTT(*NTT,poly_C, ZZ(q),ZZ(d)));
	ZZ_pX x;
	rem(x, res_ntt,DS.F);
	return x;
}

ZZX decrypt(DecryptionScheme& DS, long q,long d,long n,long p){
	ZZ_pX res;
	res.SetLength(d);

	for(int i=0;i < n;++i){
		res+= performNTTMultiplication(DS,DS.u_p[i],DS.S_p[i],d,q);
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