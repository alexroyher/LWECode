#ifndef HEADER_HELPER	
#define HEADER_HELPER

#include <limits.h>
#include <NTL/mat_ZZ_p.h>
#include <NTL/ZZX.h>
#include <vector>
#include <assert.h> 
#include <math.h> 


using namespace NTL;
using namespace std;

bool Miller_Rabin(ZZ number);
bool isPrime(ZZ number);

#endif