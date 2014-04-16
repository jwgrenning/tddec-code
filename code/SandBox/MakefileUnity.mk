#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = SandBox_Unity

#--- Inputs ----#
PROJECT_HOME_DIR = .
UNITY_HOME = ../unity.framework
CPP_PLATFORM = Gcc
UNITY_BUILD_HOME = ../unity.framework/extras/fixture/build

UNITY_CFLAGS += -DUNITY_OUTPUT_CHAR=UnityOutputCharSpy_OutputChar

SRC_DIRS = \
	$(PROJECT_HOME_DIR)/src/LedDriver \

TEST_SRC_DIRS = \
	$(PROJECT_HOME_DIR)/unity\
	$(PROJECT_HOME_DIR)/unity/LedDriver\
	$(UNITY_HOME)/src\
    $(UNITY_HOME)/extras/fixture/src\
    $(UNITY_HOME)/extras/fixture/test\

INCLUDE_DIRS =\
  .\
  $(UNITY_HOME)/src\
  $(UNITY_HOME)/src\
  $(UNITY_HOME)/extras/fixture/src\
  $(UNITY_HOME)/extras/fixture/test\
  $(PROJECT_HOME_DIR)/include/LedDriver\

include $(UNITY_BUILD_HOME)/MakefileWorker.mk
