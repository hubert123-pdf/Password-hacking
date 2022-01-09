#ifndef MD5_H
#define MD5_H
#include <openssl/md5.h>
#include <stdio.h>
#include <string.h>

void MD5_digest(char argv[],unsigned char tab[])
{
unsigned int passlen = strlen (argv);
char password[32];
for (int i = 0; i < 32; i++){
    password[i]=argv[i];
}

MD5_CTX context;
unsigned char digest[16];
unsigned int len = strlen (password);

MD5_Init(&context);
MD5_Update (&context, password, len);
MD5_Final(digest, &context);

for (int i = 0; i < 16; i++){
    tab[i]=digest[i];
}
}
#endif //MD5_H