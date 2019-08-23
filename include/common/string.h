/**
 * BPVM
 * Copyright (C) 2019 David Jolly
 *
 * BPVM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BPVM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BPVM_COMMON_STRING_H_
#define BPVM_COMMON_STRING_H_

#define COLUMN_WIDTH 24

#define FLOAT_PRECISION 1

#define STRING_EMPTY ""
#define STRING_UNKNOWN "Unknown"

#define _AS_STRING(_STRING_) \
	# _STRING_
#define AS_STRING(_STRING_) \
	_AS_STRING(_STRING_)

#define STRING(_STRING_) \
	((_STRING_).empty() ? STRING_EMPTY : (_STRING_).c_str())

#define _STRING_COLUMN(_WIDTH_) \
	std::left << std::setw(_WIDTH_)
#define STRING_COLUMN() \
	_STRING_COLUMN(COLUMN_WIDTH)

#define _STRING_FLOAT(_PRECISION_, _VALUE_) \
	std::right << std::setprecision(_PRECISION_) << std::fixed << (_VALUE_) << std::defaultfloat
#define STRING_FLOAT(_VALUE_) \
	_STRING_FLOAT(FLOAT_PRECISION, _VALUE_)

#define STRING_HEXIDECIMAL(_TYPE_, _VALUE_) \
	std::right << std::setw(sizeof(_TYPE_) * 2) << std::setfill('0') << std::hex << (uintmax_t) ((_TYPE_) (_VALUE_)) \
		<< std::dec << std::setfill(' ')

#endif // BPVM_COMMON_STRING_H_
