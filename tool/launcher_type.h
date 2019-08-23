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

#ifndef BPVM_TOOL_LAUNCHER_H_
#define BPVM_TOOL_LAUNCHER_H_

#include "../include/type/exception.h"

namespace bpvm {

	namespace tool {

		#define BPVM_TOOL_LAUNCHER_HEADER "[BPVM::TOOL::LAUNCHER]"
#ifndef NDEBUG
		#define BPVM_TOOL_LAUNCHER_EXCEPTION_HEADER BPVM_TOOL_LAUNCHER_HEADER " "
#else
		#define BPVM_TOOL_LAUNCHER_EXCEPTION_HEADER
#endif // NDEBUG

		enum {
			BPVM_TOOL_LAUNCHER_EXCEPTION_ARGUMENT_REDEFINED = 0,
			BPVM_TOOL_LAUNCHER_EXCEPTION_ARGUMENT_UNDEFINED,
			BPVM_TOOL_LAUNCHER_EXCEPTION_ARGUMENT_UNSUPPORTED,
			BPVM_TOOL_LAUNCHER_EXCEPTION_INTERNAL,
		};

		#define BPVM_TOOL_LAUNCHER_EXCEPTION_MAX BPVM_TOOL_LAUNCHER_EXCEPTION_INTERNAL

		static const std::string BPVM_TOOL_LAUNCHER_EXCEPTION_STR[] = {
			BPVM_TOOL_LAUNCHER_EXCEPTION_HEADER "Argument redefined",
			BPVM_TOOL_LAUNCHER_EXCEPTION_HEADER "Argument undefined",
			BPVM_TOOL_LAUNCHER_EXCEPTION_HEADER "Argument unsupported",
			BPVM_TOOL_LAUNCHER_EXCEPTION_HEADER "Internal exception",
			};

		#define BPVM_TOOL_LAUNCHER_EXCEPTION_STRING(_TYPE_) \
			(((_TYPE_) > BPVM_TOOL_LAUNCHER_EXCEPTION_MAX) ? STRING_UNKNOWN : \
				STRING(BPVM_TOOL_LAUNCHER_EXCEPTION_STR[_TYPE_]))

		#define THROW_BPVM_TOOL_LAUNCHER_EXCEPTION(_EXCEPT_) \
			THROW_BPVM_TOOL_LAUNCHER_EXCEPTION_FORMAT(_EXCEPT_, "", "")
		#define THROW_BPVM_TOOL_LAUNCHER_EXCEPTION_FORMAT(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION(BPVM_TOOL_LAUNCHER_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		#define ARGUMENT_DELIMITER "-"

		enum {
			ARGUMENT_HELP = 0,
			ARGUMENT_VERSION,
		};

		#define ARGUMENT_MAX ARGUMENT_VERSION
		#define ARGUMENT_MIN 2

		static const std::string ARGUMENT_DESCRIPTION_STR[] = {
			"Display help information", // ARGUMENT_HELP
			"Display version information", // ARGUMENT_VERSION
			};

		#define ARGUMENT_DESCRIPTION_STRING(_TYPE_) \
			(((_TYPE_) > ARGUMENT_MAX) ? STRING_UNKNOWN : \
				STRING(ARGUMENT_DESCRIPTION_STR[_TYPE_]))

		static const std::string ARGUMENT_LONG_STR[] = {
			ARGUMENT_DELIMITER ARGUMENT_DELIMITER "help", // ARGUMENT_HELP
			ARGUMENT_DELIMITER ARGUMENT_DELIMITER "version", // ARGUMENT_VERSION
			};

		#define ARGUMENT_LONG_STRING(_TYPE_) \
			(((_TYPE_) > ARGUMENT_MAX) ? STRING_UNKNOWN : \
				STRING(ARGUMENT_LONG_STR[_TYPE_]))

		static const std::string ARGUMENT_SHORT_STR[] = {
			ARGUMENT_DELIMITER "h", // ARGUMENT_HELP
			ARGUMENT_DELIMITER "v", // ARGUMENT_VERSION
			};

		#define ARGUMENT_SHORT_STRING(_TYPE_) \
			(((_TYPE_) > ARGUMENT_MAX) ? STRING_UNKNOWN : \
				STRING(ARGUMENT_SHORT_STR[_TYPE_]))

		std::map<std::string, int> ARGUMENT_MAP = {
			std::make_pair(ARGUMENT_LONG_STRING(ARGUMENT_HELP), ARGUMENT_HELP), // ARGUMENT_HELP
			std::make_pair(ARGUMENT_LONG_STRING(ARGUMENT_VERSION), ARGUMENT_VERSION), // ARGUMENT_VERSION
			std::make_pair(ARGUMENT_SHORT_STRING(ARGUMENT_HELP), ARGUMENT_HELP), // ARGUMENT_HELP
			std::make_pair(ARGUMENT_SHORT_STRING(ARGUMENT_VERSION), ARGUMENT_VERSION), // ARGUMENT_VERSION
			};

		#define ARGUMENT_SUPPORTED(_ARGUMENT_) \
			(ARGUMENT_MAP.find(_ARGUMENT_) != ARGUMENT_MAP.end())

		#define ARGUMENT_TYPE(_ARGUMENT_) \
			ARGUMENT_MAP.find(_ARGUMENT_)->second

		#define USAGE "bpvm [args] path"
	}
}

#endif // BPVM_TOOL_LAUNCHER_H_
