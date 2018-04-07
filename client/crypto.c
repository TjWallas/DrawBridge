#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <sys/types.h>


unsigned char *gen_digest(unsigned char *buf, unsigned int len, unsigned int *olen)
{
    EVP_MD_CTX ctx;
    unsigned char *ret;
    //int mdsz;
    const EVP_MD *sha256;

    //sha256 = EVP_sha256();
    sha256 = EVP_sha1();

    //mdsz = EVP_MD_size(sha256);

    if (!(ret = (unsigned char *)malloc(EVP_MAX_MD_SIZE)))
        return NULL;

    EVP_DigestInit(&ctx, sha256);
    EVP_DigestUpdate(&ctx, buf, len);
    EVP_DigestFinal(&ctx, ret, olen);

    return ret;
}


unsigned char *sign_data(RSA * pkey, unsigned char *data, unsigned int len, unsigned int *olen)
{

    unsigned char *sig;
    int rc = 0;

    if (!(sig = calloc(1, RSA_size(pkey)))) {
        perror("calloc");
        return NULL;
    }

	rc = RSA_sign(NID_sha1, data, len, sig, olen, pkey);

	if (1 != rc) { 
		free(sig);
		return NULL;
	}

    return sig;
} 