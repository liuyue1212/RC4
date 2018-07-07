#pragma once


#if !defined(RC4_INT)
/* using int types make the structure larger but make the code faster
 * on most boxes I have tested - up to %20 faster. */
/*
 * I don't know what does "most" mean, but declaring "int" is a must on:
 * - Intel P6 because partial register stalls are very expensive;
 * - elder Alpha because it lacks byte load/store instructions;
 */
#define RC4_INT unsigned int
#endif

typedef struct rc4_key_st
	{
	RC4_INT x,y;
	RC4_INT data[256];
	} RC4_KEY;

void RC4_set_key(RC4_KEY *key, int len, const unsigned char *data);
void RC4(RC4_KEY *key, unsigned long len, const void* indata, void* outdata);