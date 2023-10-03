
# ──────────────────────────────────── ･ ｡ﾟ☆: *.☽ .* :☆ﾟ. ────────────────────────────────────
#          
#                 Project 1: Implementing Algorithms - Matching Group Schedules
#                              CPSC 335-02: Algorithm Engineering
#                                Professor Ornella Irene Dsouza
#                                           Fall 2023
# 
# ──────────────────────────────────── ･ ｡ﾟ☆: *.☽ .* :☆ﾟ. ────────────────────────────────────
#                     
#         Name:       Tiffany Buu
#         Email:      tiffanybuu@csu.fullerton.edu
#         CWID:       885404830
# 
# ──────────────────────────────────── ･ ｡ﾟ☆: *.☽ .* :☆ﾟ. ────────────────────────────────────

#   ∘₊✧────────────────────────────────────────────────✧₊∘ *
#      
#						makefile
#     
#   ∘₊✧────────────────────────────────────────────────✧₊∘ */

# the compiler: gcc for C program, define as g++ for C++
CC := g++
 
# compiler flags:
#	-c		- Compiler source(s) to object-code (input to linker). 
#				This option is better for incremental compilation when using multiple files.
#	-g		- Builds executable with debugging symbols for GDB GNU Debugger or LLDB Clang/LLVM Debugger
#				It should only be used during development for debugging builds.
#	-Wall	- Turns on lots of compiler warning flags
#				specifically (-Waddress, -Wcomment, -Wformat, -Wbool-compare, -Wuninitialized, -Wunknown-pragmas, -Wunused-value, -Wunused-value …)
CFLAGS := -Wall -g -c -std=c++17
LINKFLAGS := -Wall -g -std=c++17

# Exceutable Names

MAIN_NAME := main
MAIN := ./$(MAIN_NAME)
#
TESTS_NAME := test
TESTS := ./$(TESTS_NAME)

MATCHING_SCHDULES_O := timeFrame.o schedule.o matchingSchedules.o

# Executables

$(MAIN): project1_starter.o $(MATCHING_SCHDULES_O)
	$(CC) $(LINKFLAGS) $^ -o $@

$(TESTS): test.o $(MATCHING_SCHDULES_O)
	$(CC) $(LINKFLAGS) $^ -o $@


# Create compiled objects

test.o: test.cpp timeFrame.hpp schedule.hpp matchingSchedules.hpp
	$(CC) $(CFLAGS) $< -o $@

project1_starter.o: project1_starter.cpp timeFrame.hpp schedule.hpp matchingSchedules.hpp
	$(CC) $(CFLAGS) $< -o $@

timeFrame.o: timeFrame.cpp timeFrame.hpp
	$(CC) $(CFLAGS) $< -o $@

schedule.o: schedule.cpp schedule.hpp
	$(CC) $(CFLAGS) $< -o $@

matchingSchedules.o: matchingSchedules.cpp matchingSchedules.hpp
	$(CC) $(CFLAGS) $< -o $@

# Commands
default:	help

help:
	@echo
	@echo "***** Makefile Menu *****"
	@echo
	@echo "make build         ==> Build source files"
	@echo
	@echo "make run           ==> Run program with no terminal output"
	@echo "make debug         ==> Debug program with gdb"
	@echo
	@echo "make run-test          ==> Run program with terminal outputs and menu"
	@echo "make debug-test    ==> Debug program with gdb"
	@echo
	@echo "make clean         ==> Clean temporary build files"
	@echo


build: $(MAIN) $(TESTS) $(TESTS_SIM)
.PHONY: build

run: $(MAIN)
	$(MAIN)
.PHONY: run

debug:	$(MAIN)
	gdb $(MAIN) -ex run
.PHONY: debug

run-test: $(TESTS)
	$(TESTS)
.PHONY: run-test

debug-test: $(TESTS)
	gdb $(TESTS) -ex run
.PHONY: debug-test

clean:
	-rm *.o
	-rm $(MAIN)
	-rm $(TESTS)
	-rm ./testoutput.txt
	-rm ./output.txt
.PHONY: clean