#This makefile makes all the main book code with CppUTest test harness

#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = BookCode_CppUTest

#--- Inputs ----#
#CPPUTEST_HOME = CppUTest
CPP_PLATFORM = Gcc
PROJECT_HOME_DIR = .

SRC_DIRS = \
	src/HomeAutomation \
	src/util\
	src/LedDriver \
	src/dvr\
	src/IO \
	src/MyOS \
	src/MyOS/posix \
	src/zune \

TEST_SRC_DIRS = \
	.\
	mocks\
	mocks\
	tests/LedDriver\
	tests/stdio\
	tests/util\
	tests/IO\
	tests/zune\
	tests/HomeAutomation\
	tests/dvr\
	tests\
	tests/MyOS\

	
INCLUDE_DIRS =\
  .\
  $(CPPUTEST_HOME)/include\
  include/IO\
  mocks\
  include/util\
  include/HomeAutomation\
  include/LedDriver\
  include/MyOS\
  include/dvr\
  include/zune\

MOCKS_SRC_DIRS = \
	mocks\
	
CPPUTEST_WARNINGFLAGS = -Wall -Wswitch-default -Werror 
CPPUTEST_WARNINGFLAGS += -Wno-missing-prototypes -Wno-format-nonliteral -Wno-sign-conversion -Wno-pedantic 
CPPUTEST_WARNINGFLAGS += -Wno-shadow -Wno-missing-field-initializers -Wno-unused-parameter
CPPUTEST_WARNINGFLAGS += -Wno-unknown-warning-option
#CPPUTEST_CFLAGS = -std=c89 
CPPUTEST_CFLAGS += -Wall -Wstrict-prototypes -pedantic
LD_LIBRARIES = -lpthread
	
# Temporary setting of C++ flag to ignore C++14 compatability for gcc > 5
# Should be moved into CPPUTest make file with PR
CPPUTEST_CXX_WARNINGFLAGS = -Wno-c++14-compat
# Flags to ignore keywords with OS X (clang and gcc wrapper)
# Should be moved into CPPUTest make file with PR
CPPUTEST_CXX_WARNINGFLAGS += -Wno-reserved-id-macro -Wno-keyword-macro
CPPUTEST_C_WARNINGFLAGS += -Wno-reserved-id-macro -Wno-keyword-macro

include $(CPPUTEST_HOME)/build/MakefileWorker.mk

