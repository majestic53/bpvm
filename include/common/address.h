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

#ifndef BPVM_COMMON_ADDRESS_H_
#define BPVM_COMMON_ADDRESS_H_

#define ADDRESS_WIDTH 3

enum {
	ADDRESS_PART_0 = 0,
	ADDRESS_PART_8,
	ADDRESS_PART_16,
};

typedef union {

	struct {
		uint8_t part[ADDRESS_WIDTH];
		uint8_t unused;
	};

	uint32_t raw;
} __attribute__((packed)) address_t;

#endif // BPVM_COMMON_ADDRESS_H_
