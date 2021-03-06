/*
 * aes_tools.c
 *
 *  Created on: 2011-12-23
 *      Author: pangt
 */

#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <app/common/aes_tools.h>

u_char iv[BLOCK_SIZE]; // init vector

int32_t at_create_key(aes_encode *aes_ins)
{
	int32_t ret = EXIT_SUCCESS;
	if (NULL == aes_ins) {
		ret = EXIT_FAILURE;
		return ret;
	}

	// Generate AES 128-bit key
//	aes_encode aes_encode_ins;
	u_char key[BLOCK_SIZE] = { 0 };
	int32_t i = 0;
	srand((unsigned) time(NULL));
	for (i = 0; i < BLOCK_SIZE; i++) {
		key[i] = ts_random(128);
	}

	ret = at_create_key_by_string(key, aes_ins);

	return ret;
}

int32_t at_create_key_by_string(const u_char *s, aes_encode *aes_ins)
{
	int32_t ret = EXIT_SUCCESS;

	/*printf("----------------------------------->create key = ");
	int i = 0;
	for (i = 0; i < BLOCK_SIZE; i++) {
		printf("%d,", s[i]);
	}
	printf("\n");
	*/
	if (NULL == aes_ins) {
		ret = EXIT_FAILURE;
		return ret;
	}
	bzero(aes_ins->key, BLOCK_SIZE);
	memcpy(aes_ins->key, s, BLOCK_SIZE);

	//create encrypt key
	if (AES_set_encrypt_key(aes_ins->key, AES_KEY_BITS, &aes_ins->encrypt_aes)
		< 0) {
		fprintf(stderr, "Unable to set encryption key in AES\n");
		return -1;
	}

	//create decrypt key
	if (AES_set_decrypt_key(aes_ins->key, AES_KEY_BITS, &aes_ins->decrypt_aes)
		< 0) {
		fprintf(stderr, "Unable to set decryption key in AES\n");
		return -1;
	}

	return ret;
}

/**
 * get encrypt or decrypt part
 */
int32_t at_get_count(int32_t len)
{
	int32_t n = 0;
	if (len % (BLOCK_SIZE - 1) == 0) {
		n = len / (BLOCK_SIZE - 1);
	} else {
		n = len / (BLOCK_SIZE - 1) + 1;
	}
	return n;
}

int32_t at_get_encrypt_len_from_strlen(int32_t str_len)
{
	int32_t len = at_get_count(str_len) * BLOCK_SIZE;
	return len;
}

int32_t at_get_encrypt_len(const char * base_string)
{
	int32_t len = 0;
	if (NULL == base_string || (strlen(base_string) <= 0)) {
		len = -1;
		fprintf(stderr, "get encrypt's length error.");
		return len;
	}
	int32_t str_len = strlen(base_string);
	len = at_get_encrypt_len_from_strlen(str_len);
	return len;
}

/**
 * encrypt unit
 */
int32_t at_encrypt_unit(const char * base_string, char *s_encrypt, int32_t len,
	aes_encode aes_encode_ins)
{
//	int32_t i = 0;
	memset(iv, 0, BLOCK_SIZE);
	memset(iv, BLOCK_SIZE - len, len);
//	memcpy(iv, iv_base, BLOCK_SIZE);

	AES_cbc_encrypt((const u_char *) base_string, (u_char *) s_encrypt, len,
		&aes_encode_ins.encrypt_aes, iv, AES_ENCRYPT);
//	printf("base = %s,len = %d en = ", base_string, len);
//	for (i = 0; i < BLOCK_SIZE; i++) {
//		printf("%d,", s_encrypt[i]);
//	}
//	printf("\n");
	return EXIT_SUCCESS;
}

/**
 * encrypt
 */
int16_t at_encrypt(const char * base_string, char *s_encrypt, int32_t len,
	aes_encode aes_encode_ins)
{
	char s_base_tmp[BLOCK_SIZE] = { 0 };
	char s_en_tmp[BLOCK_SIZE] = { 0 };
	int32_t n = at_get_count(len);
	int32_t i = 0;
	int32_t t = 0;
	const char * temp = base_string;
	for (i = 0; i < n; i++) {
		memcpy(s_base_tmp, temp, BLOCK_SIZE - 1);
		if (i == n - 1) {
			t = len - i * (BLOCK_SIZE - 1);
		} else {
			t = BLOCK_SIZE - 1;
		}
		at_encrypt_unit(s_base_tmp, (char *) s_en_tmp, t, aes_encode_ins);
		memcpy(s_encrypt, s_en_tmp, BLOCK_SIZE);
		s_encrypt += BLOCK_SIZE;
		temp += BLOCK_SIZE - 1;
	}
	return EXIT_SUCCESS;
}

/**
 * decrtypt unit
 */
int16_t at_decrypt_unit(char* encrypt_string, char * decrypt_string,
	int16_t len, aes_encode aes_encode_ins)
{
//	int fill = at_get_encrypt_len_from_strlen(len) - len;
	memset(iv, 0, BLOCK_SIZE);
	memset(iv, BLOCK_SIZE - len, len);

//	memset(iv, fill, BLOCK_SIZE);
//	memcpy(iv, iv_base, BLOCK_SIZE);

	AES_cbc_encrypt((const u_char*) encrypt_string, (u_char*) decrypt_string,
		BLOCK_SIZE, (const AES_KEY*) &aes_encode_ins.decrypt_aes, (u_char*) iv,
		AES_DECRYPT);
	decrypt_string += len;
	*decrypt_string = '\0';
	return EXIT_SUCCESS;
}

int16_t at_decrypt(char* s_encrypt, char * s_decrypt, int32_t len,
	aes_encode aes_encode_ins)
{
	int32_t n = at_get_count(len);
	char s_encrypt_unit[BLOCK_SIZE] = { 0 };
	char s_de_unit[BLOCK_SIZE] = { 0 };
	int32_t i = 0;
	int32_t t_len = 0;
	for (i = 0; i < n; i++) {
		memcpy(s_encrypt_unit, s_encrypt, BLOCK_SIZE);
		if (i == n - 1) {
			t_len = len - i * (BLOCK_SIZE - 1);
		} else {
			t_len = BLOCK_SIZE - 1;
		}
		at_decrypt_unit((char *) s_encrypt_unit, (char *) s_de_unit, t_len,
			aes_encode_ins);
		memcpy(s_decrypt, s_de_unit, BLOCK_SIZE);
		s_decrypt += BLOCK_SIZE - 1;
		s_encrypt += BLOCK_SIZE;
	}

	return EXIT_SUCCESS;
}

