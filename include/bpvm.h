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

#ifndef BPVM_H_
#define BPVM_H_

#include <stdint.h>

#define BPVM_API_VER_1 1
#define BPVM_API_VER BPVM_API_VER_1

/**********************************************
 * TYPES
 **********************************************/

/**
 * BPVM configuration
 */
typedef struct {

	// File path
	const char *path;
} bpvm_t;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**********************************************
 * RUNTIME
 **********************************************/

/**
 * Run BPVM
 * @param config BPVM configuration
 * @return STATUS_SUCCESS on success
 */
int bpvm_run(const bpvm_t *config);

/**********************************************
 * MISC.
 **********************************************/

/**
 * Retrieve BPVM error
 * @return BPVM error as string
 */
const char *bpvm_err(void);

/**
 * Retrieve BPVM version
 * @return BPVM version as string
 */
const char *bpvm_ver(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // BPVM_H_
