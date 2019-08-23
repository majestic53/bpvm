# BPVM
# Copyright (C) 2019 David Jolly
#
# BPVM is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# BPVM is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

BUILD_FLAGS_DBG=BUILD_FLAGS=-g
BUILD_FLAGS_REL=BUILD_FLAGS=-O3\ -DNDEBUG
DIR_BIN=./bin/
DIR_BIN_INC=./bin/include/
DIR_BIN_LIB=./bin/lib/
DIR_BUILD=./build/
DIR_ROOT=./
DIR_SRC=./src/
DIR_TOOL=./tool/
JOB_SLOTS=4
TRACE?=0
TRACE_FLAGS_DBG=TRACE_FLAGS=-DTRACE_COLOR\ -DTRACE=
TRACE_FLAGS_REL=TRACE_FLAGS=-DTRACE_COLOR\ -DTRACE=

all: debug

debug: begin_debug clean init lib_debug exe_debug end

release: begin_release clean init lib_release exe_release end

### SETUP ###

begin_debug:
	@echo ''
	@echo '============================================'
	@echo 'BUILDING BPVM (DEBUG)'
	@echo '============================================'

begin_release:
	@echo ''
	@echo '============================================'
	@echo 'BUILDING BPVM'
	@echo '============================================'

clean:
	rm -rf $(DIR_BIN)
	rm -rf $(DIR_BUILD)

end:
	@echo ''
	@echo '============================================'
	@echo 'BUILD DONE'
	@echo '============================================'
	@echo ''

init:
	mkdir -p $(DIR_BIN_INC)
	mkdir -p $(DIR_BIN_LIB)
	mkdir -p $(DIR_BUILD)

### LIBRARY ###

lib_debug:
	@echo ''
	@echo '============================================'
	@echo 'BUILDING LIBRARIES (DEBUG)'
	@echo '============================================'
	cd $(DIR_SRC) && make $(BUILD_FLAGS_DBG) $(TRACE_FLAGS_DBG)$(TRACE) build -j$(JOB_SLOTS)
	cd $(DIR_SRC) && make archive

lib_release:
	@echo ''
	@echo '============================================'
	@echo 'BUILDING LIBRARIES'
	@echo '============================================'
	cd $(DIR_SRC) && make $(BUILD_FLAGS_REL) $(TRACE_FLAGS_REL)$(TRACE) build -j$(JOB_SLOTS)
	cd $(DIR_SRC) && make archive

### EXECUTABLE ###

exe_debug:
	@echo ''
	@echo '============================================'
	@echo 'BUILDING EXECUTABLES (DEBUG)'
	@echo '============================================'
	cd $(DIR_TOOL) && make $(BUILD_FLAGS_DBG) $(TRACE_FLAGS_DBG)$(TRACE)

exe_release:
	@echo ''
	@echo '============================================'
	@echo 'BUILDING EXECUTABLES'
	@echo '============================================'
	cd $(DIR_TOOL) && make $(BUILD_FLAGS_REL) $(TRACE_FLAGS_REL)$(TRACE)

### MISC ###

lines:
	@echo ''
	@echo '============================================'
	@echo 'CALCULATING LINE COUNT'
	@echo '============================================'
	cloc $(DIR_ROOT)

static:
	@echo ''
	@echo '============================================'
	@echo 'RUNNING STATIC ANALYSIS'
	@echo '============================================'
	cppcheck --enable=all --std=c++11 $(DIR_SRC) $(DIR_TEST) $(DIR_TOOL)
