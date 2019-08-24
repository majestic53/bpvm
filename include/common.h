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

#ifndef BPVM_COMMON_H_
#define BPVM_COMMON_H_

#include <SDL2/SDL.h>
#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#ifndef __in
#define __in
#endif // __in
#ifndef __in_opt
#define __in_opt
#endif // __in_opt
#ifndef __inout
#define __inout
#endif // __inout
#ifndef __inout_opt
#define __inout_opt
#endif // __inout_opt
#ifndef __out
#define __out
#endif // __out
#ifndef __out_opt
#define __out_opt
#endif // __out_opt

#include "./common/address.h"
#include "./common/color.h"
#include "./common/exception.h"
#include "./common/input.h"
#include "./common/level.h"
#include "./common/string.h"
#include "./common/trace.h"
#include "./common/version.h"

#endif // BPVM_COMMON_H_
