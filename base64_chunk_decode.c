#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/pkcs12.h>
#include <assert.h>

//Calculates the length of a decoded string
size_t sizeOfBase64DecodeLength(const char* b64input) { 
	size_t len = strlen(b64input),
	padding = 0;

	if (b64input[len-1] == '=' && b64input[len-2] == '=') //last two chars are =
		padding = 2;
	else if (b64input[len-1] == '=') //last char is =
		padding = 1;

	return (len*3)/4 - padding;
}

int base64DecodeWithString(char* b64message, unsigned char** buffer, size_t* length) { //Decodes a base64 encoded string
	BIO *bio, *b64;
	int decodeLen = decodeLen = sizeOfBase64DecodeLength(b64message);
	*buffer = (unsigned char*)malloc(decodeLen + 1);
	(*buffer)[decodeLen] = '\0';
	bio = BIO_new_mem_buf(b64message, -1);
	b64 = BIO_new(BIO_f_base64());
	bio = BIO_push(b64, bio);
	BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Do not use newlines to flush buffer
	*length = BIO_read(bio, *buffer, strlen(b64message));
	assert(*length == decodeLen); //length should equal decodeLen, else something went horribly wrong
	BIO_free_all(bio);
	return 0; //success
}

void main(int argc, char const *argv[])
{
	for(int i=1 ; i<=7 ; i++){
		char file_name[256] = {0};
		sprintf(file_name, "test_file/%d", i);
		FILE *file = fopen(file_name, "r");

		// get file size
		fseek(file, 0, SEEK_END);
		long fsize = ftell(file);
		fseek(file, 0, SEEK_SET);

		char *buf;
		buf = calloc(fsize+1, sizeof(char));

		fread(buf , 1, fsize, file);

		char *base64DecodeOutput;
		size_t lengthAfterDecode;
		
		base64DecodeWithString(buf, (unsigned char**)&base64DecodeOutput, &lengthAfterDecode);
		FILE *w_file;
		if(i == 1){
			w_file = fopen("tmpFile", "wb");
		}
		else{
			w_file = fopen("tmpFile", "a");
		}

		if(w_file){
			size_t bytesWritten = fwrite(base64DecodeOutput, 1, lengthAfterDecode, w_file);
			if(bytesWritten != lengthAfterDecode){
				printf("Failed to write file : tmpFile\n");
			}
			fclose(w_file);
		}
		
		fclose(file);
		free(buf);
		free(base64DecodeOutput);
	}
	return;
}
