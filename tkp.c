#include <stdio.h>
#include <string.h>

#include "tkp.h"

int char2hex(char cur_char) {
	// capital characters
	if (cur_char > 64 && cur_char < 91)
		return cur_char - 'A' + 1;
	// small letters
	else if (cur_char > 96 && cur_char < 123)
		return cur_char - 'a' + 1;
	// numbers
	else if (cur_char > 47 && cur_char < 58)
		return cur_char - '0' + TKP_0;
	else if (cur_char == 32)
		return TKP_SPACE;
	else if (cur_char == 46)
		return TKP_PERIOD;
	else if (cur_char == 44)
		return TKP_COMMA;
}

char hex2char(int cur_char) {
	if (cur_char < TKP_0)
		return cur_char + 'a' - 1;
	else if (cur_char < TKP_SPACE)
		return cur_char + '0' - 1;
	else if (cur_char == TKP_SPACE)
		return ' ';
	else if (cur_char == TKP_PERIOD)
		return '.';
	else if (cur_char == TKP_COMMA)
		return ',';
}

size_t ascii2tkp(int *ret_arr, char *input_str, size_t len) {
	printf("Input str: %s\n", input_str);
	printf("%d\n", len);
	int intermediary[50];
	size_t intermediary_len = 0;
	for (int cur_char = 0; cur_char < len; cur_char++) {
		// printf("%c: ", input_str[cur_char]);
		// for (int i = 7; i >= 0; i--) {
		// 	printf("%d", input_str[cur_char] & 1<<i ? 1 : 0);
		// }
		intermediary[cur_char] = char2hex(input_str[cur_char]);
		intermediary_len++;
		// printf(" |\t%d\t| ", intermediary[cur_char]);
		// for (int i = 7; i >= 0; i--) {
		// 	printf("%d", intermediary[cur_char] & 1<<i ? 1 : 0);
		// }
		// printf("\n");
	}

	int output_arr_pos = 0;
	// for (int cur_pos = intermediary_len-1; cur_pos >= 0; cur_pos--) {
	for (int cur_pos = 0; cur_pos < intermediary_len; cur_pos++) {
		for (int i = 5; i >= 0; i--) {
			int arr_index = output_arr_pos / 8;
			int bit_index = output_arr_pos % 8;
			if (intermediary[cur_pos] & 1<< i)
				ret_arr[arr_index] |= 1 << bit_index;
			output_arr_pos++;
		}
	}

	// round up division to get minimum size of outpur array
	size_t output_arr_size = (output_arr_pos + 7)/ 8;

	return output_arr_size;
}

int tkp2ascii(char *ret_str, int *input_arr) {
	int intermediary[50];
	// int intermediary2[50];
	// memset(intermediary, 0, 50);
	for (int i = 0; i < 50; i++)
		intermediary[i] = 0;

	int input_arr_pos = 0;
	for (int cur_pos = 0; cur_pos < 50; cur_pos++) {
		for (int i = 0; i < 8; i++) {
			int arr_index = input_arr_pos / 6;
			int bit_index = input_arr_pos % 6;

			if (input_arr[cur_pos] & 1 << i) 
				intermediary[arr_index] |= 1 << (5 - bit_index);

			input_arr_pos++;
		}
	}

	// printf("-----------------\n");
	// for (int cur_pos = 0; cur_pos < 50; cur_pos++) {
	// 	for (int i = 7; i >= 0; i--) {
	// 		printf("%d", intermediary[cur_pos] & 1<<i ? 1 : 0);
	// 	}
	// 	printf("\n");
	// }

	char intermediary_str[50];
	int ret_str_len;
	for (int i = 0; i < 50; i++) {
		char ret_char = hex2char(intermediary[i]);
		if (ret_char == '`') {
			ret_str_len = i;
			break;
		} else {
			intermediary_str[i] = ret_char;
		}
	}

	strncpy(ret_str, intermediary_str, ret_str_len);
	ret_str[ret_str_len] = '\0';

	return ret_str_len;
}

int main(void) {
	char test_string[50] = "Nobody expects the Spanish Inquisition.,";
	int tkp_arr[50];

	size_t encoded_len = ascii2tkp(tkp_arr, test_string, strlen(test_string));

	printf("%d\n", encoded_len);

	// for (int cur_pos = encoded_len-1; cur_pos >= 0; cur_pos--) {
	// 	for (int i = 7; i >= 0; i--) {
	// 		printf("%d", tkp_arr[cur_pos] & 1<< i ? 1 : 0);
	// 	}
	// 	printf("\n");
	// }

	char ret_str[50];
	size_t ret_str_len = tkp2ascii(ret_str, tkp_arr);
	printf("Output str: %s\n", ret_str);
	printf("%d\n", ret_str_len);

	return 0;
}