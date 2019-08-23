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

#include "../include/type/singleton.h"
#include "../include/bpvm.h"
#include "./launcher_type.h"

namespace bpvm {

	namespace tool {

		class launcher :
				public bpvm::type::singleton<bpvm::tool::launcher> {

			public:

				~launcher(void)
				{
					TRACE_ENTRY();
					TRACE_EXIT();
				}

				int run(
					__in const std::vector<std::string> &arguments
					)
				{
					int result = EXIT_SUCCESS;

					TRACE_ENTRY_FORMAT("Argument[%u]=%p", arguments.size(), &arguments);

					if(arguments.size() >= ARGUMENT_MIN) {

						try {
							initialize();
							parse(arguments);

							if(m_help) {
								std::cout << usage(true) << std::endl;
							} else if(m_version) {
								std::cout << version(false) << std::endl;
							} else {
								TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "Launcher path", "%s", m_configuration.path);

								result = bpvm_run(&m_configuration);
								if(result != EXIT_SUCCESS) {
									THROW_BPVM_TOOL_LAUNCHER_EXCEPTION_FORMAT(
										BPVM_TOOL_LAUNCHER_EXCEPTION_INTERNAL, "%s", bpvm_err());
								}
							}
						} catch(bpvm::type::exception &exc) {
							std::cerr << "Error: " << exc.to_string() << std::endl;
							result = EXIT_FAILURE;
						} catch(std::exception &exc) {
							std::cerr << "Error: " << exc.what() << std::endl;
							result = EXIT_FAILURE;
						}

						uninitialize();
					} else {
						std::cout << usage(false) << std::endl;
					}

					TRACE_EXIT_FORMAT("Result=%i(%x)", result, result);
					return result;
				}

			protected:

				friend class bpvm::type::singleton<bpvm::tool::launcher>;

				launcher(void) :
					m_configuration({}),
					m_help(false),
					m_version(false)
				{
					TRACE_ENTRY();
					TRACE_EXIT();
				}

				launcher(
					__in const launcher &other
					) = delete;

				launcher &operator=(
					__in const launcher &other
					) = delete;

				void on_initialize(
					__in const void *context
					) override
				{
					TRACE_ENTRY_FORMAT("Context=%p", context);

					m_configuration = {};
					m_help = false;
					m_version = false;

					TRACE_EXIT();
				}

				void on_uninitialize(void) override
				{
					TRACE_ENTRY();

					m_version = false;
					m_help = false;
					m_configuration = {};

					TRACE_EXIT();
				}

				void parse(
					__in const std::vector<std::string> &arguments
					)
				{
					std::vector<std::string>::const_iterator argument;

					TRACE_ENTRY_FORMAT("Argument[%u]=%p", arguments.size(), &arguments);

					for(argument = (arguments.begin() + 1); argument != arguments.end(); ++argument) {

						if(argument->front() == std::string(ARGUMENT_DELIMITER).front()) {

							if(!ARGUMENT_SUPPORTED(*argument)) {
								THROW_BPVM_TOOL_LAUNCHER_EXCEPTION_FORMAT(
									BPVM_TOOL_LAUNCHER_EXCEPTION_ARGUMENT_UNSUPPORTED, "%s", STRING(*argument));
							}

							switch(ARGUMENT_TYPE(*argument)) {
								case ARGUMENT_HELP:
									m_help = true;
									break;
								case ARGUMENT_VERSION:
									m_version = true;
									break;
								default:
									THROW_BPVM_TOOL_LAUNCHER_EXCEPTION_FORMAT(
										BPVM_TOOL_LAUNCHER_EXCEPTION_ARGUMENT_UNSUPPORTED,
										"%s", STRING(*argument));
							}

							if(m_help || m_version) {
								break;
							}
						} else if(!m_configuration.path) {
							m_configuration.path = STRING(*argument);
						} else {
							THROW_BPVM_TOOL_LAUNCHER_EXCEPTION_FORMAT(BPVM_TOOL_LAUNCHER_EXCEPTION_ARGUMENT_REDEFINED,
								"%s", STRING(*argument));
						}
					}

					if(!m_help && !m_version && !m_configuration.path) {
						THROW_BPVM_TOOL_LAUNCHER_EXCEPTION(BPVM_TOOL_LAUNCHER_EXCEPTION_ARGUMENT_UNDEFINED);
					}

					TRACE_EXIT();
				}

				std::string usage(
					__in bool verbose
					) const
				{
					std::stringstream result;

					TRACE_ENTRY_FORMAT("Verbose=%x", verbose);

					if(verbose) {
						result << version(true) << std::endl << std::endl;
					}

					result << USAGE;

					if(verbose) {
						int argument = 0;

						result << std::endl;

						for(; argument <= ARGUMENT_MAX; ++argument) {
							std::stringstream stream;

							stream << ARGUMENT_SHORT_STRING(argument) << "|" << ARGUMENT_LONG_STRING(argument);
							result << std::endl << STRING_COLUMN() << stream.str()
								<< ARGUMENT_DESCRIPTION_STRING(argument);
						}
					}

					TRACE_EXIT();
					return result.str();
				}

				std::string version(
					__in bool verbose
					) const
				{
					std::stringstream result;

					TRACE_ENTRY_FORMAT("Verbose=%x", verbose);

					if(verbose) {
						result << BPVM " ";
					}

					result << bpvm_ver();

					if(verbose) {
						result << std::endl << BPVM_NOTICE;
					}

					TRACE_EXIT();
					return result.str();
				}

				bpvm_t m_configuration;

				bool m_help;

				bool m_version;
		};
	}
}

int
main(
	__in int argc,
	__in const char *argv[]
	)
{
	int result;

	TRACE_ENTRY_FORMAT("Argument[%u]=%p", argc, argv);

	result = bpvm::tool::launcher::instance().run(std::vector<std::string>(argv, argv + argc));

	TRACE_EXIT_FORMAT("Result=%i(%x)", result, result);
	return result;
}
