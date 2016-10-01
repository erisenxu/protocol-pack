
include Makefile.rules

TEST_SRC = $(wildcard ${SRC_DIR}/*.cpp)
TEST_OBJS = $(patsubst %.cpp,${OBJ_DIR}/%.o,$(notdir ${TEST_SRC}))

HDR_SRC = $(wildcard ${SRC_DIR}/handler/*.cpp)
HDR_OBJS = $(patsubst %.cpp,${OBJ_DIR}/handler/%.o,$(notdir ${HDR_SRC}))

TARGET_OBJS = ${TEST_OBJS} \
			  ${HDR_OBJS} \
			  ${OBJ_DIR}/MField.o \
			  ${OBJ_DIR}/MFieldHandler.o \
			  ${OBJ_DIR}/MByteArray.o

$(TARGET): $(TARGET_OBJS)
	$(LINK) -o $@ $^

${OBJ_DIR}/%.o:${SRC_DIR}/%.cpp
	$(CPP) $(CXXFLAGS) -c  $< -o $@

${OBJ_DIR}/MField.o:${SRC_DIR}/../field/MField.cpp
	$(CPP) $(CXXFLAGS) -c  $< -o $@

${OBJ_DIR}/MFieldHandler.o:${SRC_DIR}/../field/MFieldHandler.cpp
	$(CPP) $(CXXFLAGS) -c  $< -o $@

${OBJ_DIR}/MByteArray.o:${SRC_DIR}/../comm/MByteArray.cpp
	$(CPP) $(CXXFLAGS) -c  $< -o $@

clean:
	rm -f $(TARGET_OBJS) $(TARGET)

