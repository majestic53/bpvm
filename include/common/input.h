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

#ifndef BPVM_COMMON_INPUT_H_
#define BPVM_COMMON_INPUT_H_

enum {
	INPUT_8 = 0,
	INPUT_9,
	INPUT_A,
	INPUT_B,
	INPUT_C,
	INPUT_D,
	INPUT_E,
	INPUT_F,
	INPUT_0,
	INPUT_1,
	INPUT_2,
	INPUT_3,
	INPUT_4,
	INPUT_5,
	INPUT_6,
	INPUT_7,
};

#define INPUT_MAX INPUT_7

enum {
	INPUT_PART_LOW = 0,
	INPUT_PART_HIGH,
};

#define INPUT_WIDTH (INPUT_PART_HIGH + 1)

typedef union {
	uint8_t part[INPUT_WIDTH];
	uint16_t raw;
} __attribute__((packed)) input_t;

#endif // BPVM_COMMON_INPUT_H_
