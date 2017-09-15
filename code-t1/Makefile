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

CPPUTEST_USE_EXTENSIONS = Y
include ../CppUTestCompileFlags.mk
include $(CPPUTEST_HOME)/build/MakefileWorker.mk
