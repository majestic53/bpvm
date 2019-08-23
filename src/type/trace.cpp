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

#include "../../include/type/trace.h"
#include "./trace_type.h"

namespace bpvm {

	namespace type {

		void
		trace::generate(
			__in int level,
			__in const std::string &prefix,
			__in const std::string &message,
			__in const std::string &file,
			__in const std::string &function,
			__in size_t line,
			__in const char *format,
			...
			)
		{
			std::stringstream result;

			result << LEVEL_COLOR(level) << "[" << bpvm::type::trace::timestamp() << "] {" << LEVEL_STRING(level) << "} "
				<< prefix << message;

			if(format) {
				int length;
				va_list arguments;
				std::string buffer;

				va_start(arguments, format);
				length = std::vsnprintf(nullptr, 0, format, arguments);
				va_end(arguments);

				if(length > 0) {
					buffer.resize(++length);
					va_start(arguments, format);
					length = std::vsnprintf((char *)&buffer[0], buffer.size(), format, arguments);
					va_end(arguments);
				}

				if(length < 0) {
					buffer = BPVM_TYPE_TRACE_EXCEPTION_STRING(BPVM_TYPE_TRACE_EXCEPTION_FORMAT_INVALID);
				}

				if(!buffer.empty()) {

					if(!result.str().empty()) {
						result << ": ";
					}

					result << buffer;
				}
			}

#ifndef NDEBUG
			if(!result.str().empty()) {
				result << " ";
			}

			result << "(";

			if(!function.empty()) {
				result << function << ":";
			}

			if(!file.empty()) {
				result << file << "@";
			}

			result << line << ")";
#endif // NDEBUG
			result << LEVEL_COLOR(LEVEL_NONE);

			switch(level) {
				case LEVEL_ERROR:
				case LEVEL_WARNING:
					std::cerr << result.str() << std::endl;
					break;
				case LEVEL_INFORMATION:
				case LEVEL_VERBOSE:
					std::cout << result.str() << std::endl;
					break;
				default:
					break;
			}
		}

		std::string
		trace::timestamp(void)
		{
			int length;
			std::time_t time;
			std::string result;

			time = std::time(nullptr);
			result.resize(TIMESTAMP_LENGTH, 0);

			length = std::strftime((char *)&result[0], result.size(), TIMESTAMP_FORMAT, std::localtime(&time));
			if(length > 0) {
				result = result.substr(0, length);
			} else {
				result = BPVM_TYPE_TRACE_EXCEPTION_STRING(BPVM_TYPE_TRACE_EXCEPTION_TIMESTAMP_INVALID);
			}

			return result;
		}
	}
}
