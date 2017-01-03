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
#CPPUTEST_CFLAGS = -std=c89 
CPPUTEST_CFLAGS += -Wall -Wstrict-prototypes -pedantic
LD_LIBRARIES = -lpthread
	
  
include $(CPPUTEST_HOME)/build/MakefileWorker.mk

