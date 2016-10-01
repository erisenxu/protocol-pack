
include Makefile.rules

TEST_SRC = $(wildcard ${SRC_DIR}/*.c)
TEST_OBJS = $(patsubst %.c,${OBJ_DIR}/%.o,$(notdir ${TEST_SRC}))

TARGET_OBJS = ${TEST_OBJS} \
			  ${OBJ_DIR}/Field.o \
			  ${OBJ_DIR}/ByteArray.o

$(TARGET): $(TARGET_OBJS)
	$(LINK) -o $@ $^

${OBJ_DIR}/%.o:${SRC_DIR}/%.c
	$(CPP) $(CXXFLAGS) -c  $< -o $@

${OBJ_DIR}/Field.o:${SRC_DIR}/../field/Field.c
	$(CPP) $(CXXFLAGS) -c  $< -o $@

${OBJ_DIR}/ByteArray.o:${SRC_DIR}/../comm/ByteArray.c
	$(CPP) $(CXXFLAGS) -c  $< -o $@

clean:
	rm -f $(TARGET_OBJS) $(TARGET)

