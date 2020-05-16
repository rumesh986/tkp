// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

void print_bin(char *input_str, size_t len) {
	for (int cur_char_pos = 0; cur_char_pos < len; cur_char_pos++) {
		// printf("%02d | %c| ", input_str[cur_char_pos], (input_str[cur_char_pos] < 11) ? input_str[cur_char_pos] + 'A' : input_str[cur_char_pos]);
		printf("%2d | ", cur_char_pos);
		for (int i = 7; i >-1; i--) {
			printf("%d", input_str[cur_char_pos] & 1 << i ? 1 : 0);
		}
		printf("\n");
	} 
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

size_t tkp2ascii(char *ret_str, int *input_arr) {
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

char *encode_str(char *input_str, size_t len) {
	printf("Input str: %s\n", input_str);
	// char *intermediary = malloc(sizeof(char) * len);
	char intermediary[len];

	size_t ret_str_len = ((3 * len) + 3)/4; // round up calculation
	// char ret_str[ret_str_len];
	char *ret_str = malloc(sizeof(char) * ret_str_len);
	// char *ret_str = calloc(ret_str_len, sizeof(char));
	
	printf("Inital length: %d | Compressed length: %d\n", len, ret_str_len);

	for (int cur_char_pos = 0; cur_char_pos < len; cur_char_pos++) {
		// printf("%c: | ", input_str[cur_char_pos]);
		// for (int i = 7; i >-1; i--) {
		// 	printf("%d", input_str[cur_char_pos] & 1<<i ? 1 : 0);
		// }

		char newchar = char2hex(input_str[cur_char_pos]);
		intermediary[cur_char_pos] = newchar;

		// printf(" | %02d | ", newchar);
		// for (int i = 7; i >-1; i--) {
		// 	printf("%d", intermediary[cur_char_pos] & 1<<i ? 1 : 0);
		// }
		// printf("\n");
	}

	// printf("###################\n\tINTERMEDIARY\n###################\n");
	// print_bin(intermediary, len);
	// printf("###################\n");

	int bit_pos = 0;
	for (int cur_char_pos = 0; cur_char_pos < len; cur_char_pos++) {
		for (int i = 5; i >-1; i--) {
			int arr_index = bit_pos / 8;
			int bit_index = bit_pos % 8;

			if (intermediary[cur_char_pos] & 1 << i)
				ret_str[arr_index] |= 1 << bit_index;
			bit_pos++;
		}
	}
	ret_str[ret_str_len] = '\n';
	// printf("Output string: %s\n", ret_str);

	// printf("###################\n\tENCODED\n###################\n");
	// print_bin(ret_str, ret_str_len);
	// printf("###################\n");
	return ret_str;
}

char *decode_str(char *input_str, size_t len) {
	// printf("Input encoded string: %s\n", input_str);
	len--; // to ignore the NULL terminator
	size_t ret_str_len = ((4 * len) + 2)/3; // round up calculation

	char *ret_str = malloc(sizeof(char) * ret_str_len);
	printf("Encoded length: %d | Decoded length: %d\n", len, ret_str_len);
	// print_bin(input_str);

	int bit_pos = 0;
	for (int cur_char_pos = 0; cur_char_pos < ret_str_len; cur_char_pos++) {
		// printf("1 %d %d %d\n", ret_str_len, cur_char_pos, strlen(ret_str));
		for (int i = 5; i >-1; i--) {
			int arr_index = bit_pos / 8;
			int bit_index = bit_pos % 8;

			// printf("A %d %d %d\n", ret_str_len, cur_char_pos, strlen(ret_str));
			if (input_str[arr_index] & 1 << bit_index)
				// ret_str[arr_index] |= 1 << (5 - bit_index);
				// printf("B %d %d %d\n", ret_str_len, cur_char_pos, strlen(ret_str));
				ret_str[cur_char_pos] |= 1 << i;
				// printf("C %d %d %d\n", ret_str_len, cur_char_pos, strlen(ret_str));

			bit_pos++;
			// printf("D %d %d %d\n", ret_str_len, cur_char_pos, strlen(ret_str));

		}
		// printf("2 %d %d %d\n", ret_str_len, cur_char_pos, strlen(ret_str));
		ret_str[cur_char_pos] = hex2char(ret_str[cur_char_pos]);
		// ret_str[cur_char_pos] = ret_str[cur_char_pos] >> 2;
		// ret_str[cur_char_pos] = hex2char(ret_str[cur_char_pos]);
		// printf("3 %d %d %d\n", ret_str_len, cur_char_pos, strlen(ret_str));
	}
	// printf("###################\n\tDECODEDHEX\n###################\n");
	// print_bin(ret_str, ret_str_len);
	// printf("###################\n");
	// for (int cur_char_pos = 0; cur_char_pos < len; cur_char_pos++) {
	// 	ret_str[cur_char_pos] = hex2char(ret_str[cur_char_pos]);
	// }
	// printf("Decoded string: %s\n", ret_str);

	// printf("###################\n\tDECODED\n###################\n");
	// print_bin(ret_str, ret_str_len);
	// printf("###################\n");

	ret_str[ret_str_len] = '\0';
	return ret_str;
}

char *encode_time(int cur_time) {
	printf("##############START ENCODE##################\n");
	// int cur_time = time(NULL);
	char *ret_str = malloc(sizeof(char) * 4);

	for (int i = 31; i >-1; i--) {
		int arr_index = i / 8;
		int bit_index = i % 8;

		if (cur_time & 1 << i)
			ret_str[arr_index] |= 1 << bit_index;
	}

	for (int i = 3; i>-1; i--)
		printf("%c | %u\n", ret_str[i], ret_str[i]);

	printf("%d\n", cur_time);
	printf("%s\n", ret_str);

	printf("##############END ENCODE##################\n");
	return ret_str;
}

int decode_time(char *time_str) {
	printf("##############START DECODE##################\n");
	printf("%s\n", time_str);
	int ret_int = 0;
	for (int i = 3; i >-1; i--) {
		printf("%c | %u\n", time_str[i], time_str[i]);
		ret_int += time_str[i] << (i * 8);
	}
	printf("%u\n", ret_int);
	printf("%s\n", time_str);

	printf("##############END DECODE##################\n");
	return ret_int;
}

int main(void) {
	char test_string[50] = "Nobody expects the Spanish Inquisition.,";
	// int tkp_arr[50];

	// size_t encoded_len = ascii2tkp(tkp_arr, test_string, strlen(test_string));

	// printf("%d\n", encoded_len);

	// // for (int cur_pos = encoded_len-1; cur_pos >= 0; cur_pos--) {
	// // 	for (int i = 7; i >= 0; i--) {
	// // 		printf("%d", tkp_arr[cur_pos] & 1<< i ? 1 : 0);
	// // 	}
	// // 	printf("\n");
	// // }

	// char ret_str[50];
	// size_t ret_str_len = tkp2ascii(ret_str, tkp_arr);
	// printf("Output str: %s\n", ret_str);
	// printf("%d\n", ret_str_len);

	char *tkp_str = ascii2tkpstr(test_string, strlen(test_string));
	printf("[%d] %s\n", strlen(tkp_str), tkp_str);

	char *ascii_str = tkp2asciistr(tkp_str, strlen(tkp_str));
	printf("[%d] %s\n", strlen(ascii_str), ascii_str);

	// printf("###################\n\tDECODED\n###################\n");
	// print_bin(ascii_str, strlen(ascii_str));
	// printf("###################\n");

	free(tkp_str);
	free(ascii_str);
	// printf("%s\n", tkp_str);

	// printf("%d\n", time(NULL));
	char *time_str = time_in_ascii();
	ascii_to_time(time_str);
	return 0;
}