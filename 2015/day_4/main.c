#include<stdio.h>
#include<string.h>
#include<openssl/evp.h>

const int MAX = 1000000000;

void md5_hash_from_string(char* string, char* hash) {
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digest_len;

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_md5(), NULL);
    EVP_DigestUpdate(ctx, string, strlen(string));
    EVP_DigestFinal_ex(ctx, digest, &digest_len);
    EVP_MD_CTX_free(ctx);

    for (unsigned int i = 0; i < EVP_MAX_MD_SIZE; i++) {
        sprintf(hash+ 2*i, "%02x", digest[i]);
    }
}

bool has_five_zeros(char* str) {
    char pre[255] = "000000";
    return strncmp(pre, str, strlen(pre)) == 0;
}

int main() {
    int i = 0;
    bool find = false;
    char string[255] = "bgvyzdsv";

    for ( i = 0; i < MAX; i++) {
        char hash[2 * EVP_MAX_MD_SIZE+1] = "";
        char cpy_string[255 + 12];
        char int_to_char[12];
        sprintf(int_to_char, "%d", i);

        strcpy(cpy_string, string);
        strcat(cpy_string, int_to_char);

        md5_hash_from_string(cpy_string, hash);

        if ( has_five_zeros(hash) ) {
            printf("FIND !");
            break;
        }

        i++;
    }
    
    printf("%d\n", i);
    return 0;
}
