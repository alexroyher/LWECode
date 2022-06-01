#include "decryption.h"
#include "encryption.h"


ZZX decrypt(DecryptionScheme& DS, long q,long d,long n,long p){
	ZZ_pX res;
	res.SetLength(d);

	for(int i=0;i < n;++i){
		res+= MulMod(DS.u_p[i],DS.S_p[i],DS.F);
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