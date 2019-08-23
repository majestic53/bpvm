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

#ifndef BPVM_COMMON_LEVEL_H_
#define BPVM_COMMON_LEVEL_H_

enum {
	LEVEL_NONE = 0,
	LEVEL_ERROR,
	LEVEL_WARNING,
	LEVEL_INFORMATION,
	LEVEL_VERBOSE,
};

#define LEVEL_MAX LEVEL_VERBOSE

#endif // BPVM_COMMON_LEVEL_H_
