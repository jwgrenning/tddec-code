#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = SandBox_CppUTest
TARGET_LIB = \
	lib/lib$(COMPONENT_NAME).a
	
TEST_TARGET = \
	$(COMPONENT_NAME)_tests

#--- Inputs ----#
PROJECT_HOME_DIR = .
CPP_PLATFORM = Gcc

SRC_DIRS = \
	$(PROJECT_HOME_DIR)/src/LedDriver \

TEST_SRC_DIRS = \
	tests\
	tests/*\

INCLUDE_DIRS =\
  .\
  $(CPPUTEST_HOME)/include\
  $(PROJECT_HOME_DIR)/include/LedDriver\
  
#CPPUTEST_WARNINGFLAGS += -pedantic-errors -Wconversion -Wshadow  -Wextra
CPPUTEST_WARNINGFLAGS += -Wall -Werror -Wswitch-default -Wswitch-enum 

# Temporary setting of C++ flag to ignore C++14 compatability for gcc > 5
# Should be moved into CPPUTest make file with PR
CPPUTEST_CXX_WARNINGFLAGS = -Wno-c++14-compat

# Temporary setting in Sandbox, CppuTest makefile should also detect clang > 7
# and set flags.
ifeq ($(CPP_PLATFORM),clang)
	CPPUTEST_CXX_WARNINGFLAGS += -Wno-reserved-id-macro -Wno-keyword-macro
	CPPUTEST_C_WARNINGFLAGS += -Wno-reserved-id-macro -Wno-keyword-macro
endif

include $(CPPUTEST_HOME)/build/MakefileWorker.mk
