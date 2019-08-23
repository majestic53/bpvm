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

#ifndef BPVM_COMMON_VERSION_H_
#define BPVM_COMMON_VERSION_H_

#define BPVM "BPVM"
#define BPVM_NOTICE "Copyright (C) 2019 David Jolly"

#define RELEASE "alpha"

#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_REVISION 1
#define VERSION_WEEK 1934

#define VERSION_STRING() \
	AS_STRING(VERSION_MAJOR) "." \
	AS_STRING(VERSION_MINOR) "." \
	AS_STRING(VERSION_WEEK) "." \
	AS_STRING(VERSION_REVISION) "-" \
	RELEASE

#endif // BPVM_COMMON_VERSION_H_
