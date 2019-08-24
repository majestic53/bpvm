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

DIR_BIN_INC=../bin/include/
DIR_BIN_LIB=../bin/lib/
DIR_BUILD=../build/
DIR_INC=../include/
DIR_INC_SYSTEM=../include/system/
DIR_INC_TYPE=../include/type/
DIR_SRC=./
DIR_SRC_SYSTEM=./system/
DIR_SRC_TYPE=./type/
FLAGS=-march=native -std=c++17 -Wall -Werror
LIB=libbpvm.a

all: build archive

### LIBRARY ###

archive:
	@echo ''
	@echo '--- BUILDING LIBRARY -----------------------'
	ar rcs $(DIR_BIN_LIB)$(LIB) $(DIR_BUILD)base_bpvm.o \
		$(DIR_BUILD)system_memory.o $(DIR_BUILD)system_processor.o $(DIR_BUILD)system_video.o \
		$(DIR_BUILD)type_buffer.o $(DIR_BUILD)type_exception.o $(DIR_BUILD)type_trace.o
	cp $(DIR_INC)bpvm.h $(DIR_BIN_INC)
	@echo '--- DONE -----------------------------------'

build: build_base build_system build_type

### BASE ###

build_base: base_bpvm.o

base_bpvm.o: $(DIR_SRC)bpvm.cpp $(DIR_INC)bpvm.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) $(TRACE_FLAGS) -c $(DIR_SRC)bpvm.cpp -o $(DIR_BUILD)base_bpvm.o

### SYSTEM ###

build_system: system_memory.o system_processor.o system_video.o

system_memory.o: $(DIR_SRC_SYSTEM)memory.cpp $(DIR_INC_SYSTEM)memory.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) $(TRACE_FLAGS) -c $(DIR_SRC_SYSTEM)memory.cpp -o $(DIR_BUILD)system_memory.o

system_processor.o: $(DIR_SRC_SYSTEM)processor.cpp $(DIR_INC_SYSTEM)processor.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) $(TRACE_FLAGS) -c $(DIR_SRC_SYSTEM)processor.cpp -o $(DIR_BUILD)system_processor.o

system_video.o: $(DIR_SRC_SYSTEM)video.cpp $(DIR_INC_SYSTEM)video.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) $(TRACE_FLAGS) -c $(DIR_SRC_SYSTEM)video.cpp -o $(DIR_BUILD)system_video.o

### TYPE ###

build_type: type_buffer.o type_exception.o type_trace.o

type_buffer.o: $(DIR_SRC_TYPE)buffer.cpp $(DIR_INC_TYPE)buffer.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) $(TRACE_FLAGS) -c $(DIR_SRC_TYPE)buffer.cpp -o $(DIR_BUILD)type_buffer.o

type_exception.o: $(DIR_SRC_TYPE)exception.cpp $(DIR_INC_TYPE)exception.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) $(TRACE_FLAGS) -c $(DIR_SRC_TYPE)exception.cpp -o $(DIR_BUILD)type_exception.o

type_trace.o: $(DIR_SRC_TYPE)trace.cpp $(DIR_INC_TYPE)trace.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) $(TRACE_FLAGS) -c $(DIR_SRC_TYPE)trace.cpp -o $(DIR_BUILD)type_trace.o
