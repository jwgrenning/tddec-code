#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = t1
TARGET_LIB = \
	lib/lib$(COMPONENT_NAME).a
	
TEST_TARGET = \
	$(COMPONENT_NAME)_tests

#--- Inputs ----#
PROJECT_HOME_DIR = .
CPP_PLATFORM = Gcc

CPPUTEST_USE_EXTENSIONS = Y
CPPUTEST_WARNINGFLAGS += -Wall 
CPPUTEST_WARNINGFLAGS += -Werror 
CPPUTEST_WARNINGFLAGS += -Wswitch-default 
CPPUTEST_WARNINGFLAGS += -Wswitch-enum  
CPPUTEST_WARNINGFLAGS += -Wno-unused-parameter
CPPUTEST_WARNINGFLAGS += -Wno-shadow
CPPUTEST_WARNINGFLAGS += -Wno-covered-switch-default
CPPUTEST_CFLAGS += -std=c99
CPPUTEST_CFLAGS += -Wextra 
CPPUTEST_CFLAGS += -pedantic 
CPPUTEST_CFLAGS += -Wstrict-prototypes

SRC_DIRS = \
	src/*\
	src/MyOS/Acme\

TEST_SRC_DIRS = \
	tests \
	tests/MyOS \
	tests/util \
	tests/devices \
	tests/HomeAutomation\
	tests/IO \
	mocks/IO \
	mocks
	
INCLUDE_DIRS =\
  .\
  $(CPPUTEST_HOME)/include/\
  include/*\
  mocks/IO \
  mocks

  
include $(CPPUTEST_HOME)/build/MakefileWorker.mk
