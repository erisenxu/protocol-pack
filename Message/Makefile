########################################################################
# This makefile is created by python script, please not edit it :)     #
########################################################################

include Makefile.rules

TARGET_OBJS = $(OBJ_DIR)/MByteArray.o \
              $(OBJ_DIR)/MByteField.o \
			  $(OBJ_DIR)/MBytesField.o \
			  $(OBJ_DIR)/MCompositeField.o \
			  $(OBJ_DIR)/MField.o \
			  $(OBJ_DIR)/MIntField.o \
			  $(OBJ_DIR)/MLongField.o \
			  $(OBJ_DIR)/MShortField.o \
			  $(OBJ_DIR)/MStringField.o \
			  $(OBJ_DIR)/MUByteField.o \
			  $(OBJ_DIR)/MUIntField.o \
			  $(OBJ_DIR)/MULongField.o \
			  $(OBJ_DIR)/MUShortField.o

$(TARGET): $(TARGET_OBJS)
	$(LINK) -o $@ $^

$(OBJ_DIR)/MByteArray.o: $(SRC_DIR)/comm/MByteArray.cpp
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/MByteField.o: $(SRC_DIR)/field/MByteField.cpp
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/MBytesField.o: $(SRC_DIR)/field/MBytesField.cpp
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/MCompositeField.o: $(SRC_DIR)/field/MCompositeField.cpp
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/MField.o: $(SRC_DIR)/field/MField.cpp
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/MIntField.o: $(SRC_DIR)/field/MIntField.cpp
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/MLongField.o: $(SRC_DIR)/field/MLongField.cpp
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/MShortField.o: $(SRC_DIR)/field/MShortField.cpp
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/MStringField.o: $(SRC_DIR)/field/MStringField.cpp
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/MUByteField.o: $(SRC_DIR)/field/MUByteField.cpp
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/MUIntField.o: $(SRC_DIR)/field/MUIntField.cpp
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/MULongField.o: $(SRC_DIR)/field/MULongField.cpp
	$(CPP) $^ -o $@ $(CXXFLAGS)

$(OBJ_DIR)/MUShortField.o: $(SRC_DIR)/field/MUShortField.cpp
	$(CPP) $^ -o $@ $(CXXFLAGS)

clean:
	rm -f $(TARGET_OBJS) $(TARGET)
