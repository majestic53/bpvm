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

#ifndef BPVM_COMMON_EXCEPTION_H_
#define BPVM_COMMON_EXCEPTION_H_

#define THROW_EXCEPTION(_EXCEPT_, _FORMAT_, ...) \
	bpvm::type::exception::generate(_EXCEPT_, __FILE__, __FUNCTION__, __LINE__, _FORMAT_, __VA_ARGS__)

#endif // BPVM_COMMON_EXCEPTION_H_
