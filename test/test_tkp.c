#include <stdio.h>
#include <string.h>

#include "../src/libtkp.h"

int main(void) {
	char test_string[50] = "Nobody expects the Spanish Inquisition.,";

	// char *encoded_str = encode_str(test_string, strlen(test_string));	
	// printf("%s\n", encoded_str);

	// char *decoded_str = decode_str(encoded_str, strlen(encoded_str));
	// printf("%s\n", decoded_str);

	char encoded_str_2[31];
	char decoded_str_2[40];
	
	memset(encoded_str_2, 0, 31);
	memset(decoded_str_2, 0, 40);	
	
	encode_str_2(test_string, encoded_str_2, 31);
	printf("\n%s\n\n", encoded_str_2);

	decode_str_2(encoded_str_2, decoded_str_2, 40);
	printf("\n%s\n", decoded_str_2);
}