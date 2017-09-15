#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = t2
TARGET_LIB = \
	lib/lib$(COMPONENT_NAME).a
	
TEST_TARGET = \
	$(COMPONENT_NAME)_tests

#--- Inputs ----#
PROJECT_HOME_DIR = .
CPP_PLATFORM = Gcc

SRC_DIRS = \
	src/*\

TEST_SRC_DIRS = \
	tests \
	tests/util \
	tests/devices \
	tests/HomeAutomation\
	mocks
	
INCLUDE_DIRS =\
  $(CPPUTEST_HOME)/include/\
  include/HomeAutomation\
  include/util\
  mocks\
  include/devices\
  include/MyOS\
  
include ../CppUTestCompileFlags.mk
include $(CPPUTEST_HOME)/build/MakefileWorker.mk
