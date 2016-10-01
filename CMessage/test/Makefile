########################################################################
# This makefile is created by python script, please not edit it :)     #
########################################################################

include Makefile.rules

LIB_OBJS = $(OBJ_DIR)/ByteArray.o \
		   $(OBJ_DIR)/ArrayField.o \
		   $(OBJ_DIR)/ByteField.o \
		   $(OBJ_DIR)/Field.o \
		   $(OBJ_DIR)/IntField.o \
		   $(OBJ_DIR)/LongField.o \
		   $(OBJ_DIR)/ShortField.o \
		   $(OBJ_DIR)/StringField.o \
		   $(OBJ_DIR)/UByteField.o \
		   $(OBJ_DIR)/UIntField.o \
		   $(OBJ_DIR)/ULongField.o \
		   $(OBJ_DIR)/UShortField.o

TARGET_OBJS = $(LIB_OBJS) \
			  $(OBJ_DIR)/main.o \
			  $(OBJ_DIR)/TestMsg.o \
			  $(OBJ_DIR)/TestMsg2.o \
			  $(OBJ_DIR)/TestUnion.o \
			  $(OBJ_DIR)/TestUnion2.o \
			  $(OBJ_DIR)/TestUnion3.o

$(LIB_TARGET): $(LIB_OBJS)
	$(LIB) $@ $^

$(TARGET): $(TARGET_OBJS)
	$(LINK) -o $@ $^ $(CXXLIBS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/ByteArray.o: $(SRC_DIR)/comm/ByteArray.c
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/ArrayField.o: $(SRC_DIR)/field/ArrayField.c
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/ByteField.o: $(SRC_DIR)/field/ByteField.c
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/Field.o: $(SRC_DIR)/field/Field.c
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/IntField.o: $(SRC_DIR)/field/IntField.c
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/LongField.o: $(SRC_DIR)/field/LongField.c
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/ShortField.o: $(SRC_DIR)/field/ShortField.c
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/StringField.o: $(SRC_DIR)/field/StringField.c
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/UByteField.o: $(SRC_DIR)/field/UByteField.c
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/UIntField.o: $(SRC_DIR)/field/UIntField.c
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/ULongField.o: $(SRC_DIR)/field/ULongField.c
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/UShortField.o: $(SRC_DIR)/field/UShortField.c
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/TestMsg.o: $(SRC_DIR)/test/TestMsg.c
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/TestMsg2.o: $(SRC_DIR)/test/TestMsg2.c
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/TestUnion.o: $(SRC_DIR)/test/TestUnion.c
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/TestUnion2.o: $(SRC_DIR)/test/TestUnion2.c
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/TestUnion3.o: $(SRC_DIR)/test/TestUnion3.c
	$(CPP) $^ -o $@ $(CXXFLAGS)

clean:
	rm -f $(TARGET_OBJS) $(TARGET) $(LIB_TARGET)
