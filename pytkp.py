#!/usr/bin/env python3

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

from ctypes import *

libtkp = CDLL("./libtkp.so")

encode_str = libtkp.encode_str
encode_str.restype = c_char_p
encode_str.argtypes = [c_char_p, c_size_t]

decode_str = libtkp.decode_str
decode_str.restype = c_char_p
decode_str.argtypes = [c_char_p, c_size_t]

test_str = "Nobody expects the Spanish Inquisition.,"
c_test_str = c_char_p(test_str.encode('ascii'))
c_len = c_size_t(len(test_str))
# print(c_test_str)

print(type(c_test_str))

encode_ret = encode_str(c_test_str, c_len)

actual_encoded_str = encode_ret[-1]
print(encode_ret)
print(len(encode_ret))
# print(libtkp.decode_time("AHAH"))

decode_ret = decode_str(encode_ret, c_size_t(len(encode_ret)))
print(decode_ret)
print(len(decode_ret))
print(decode_ret.decode('utf-8'))
