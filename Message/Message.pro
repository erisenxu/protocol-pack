#-------------------------------------------------
#
# Project created by QtCreator 2014-11-25T22:39:52
#
#-------------------------------------------------

QT       -= core gui

TARGET = Message
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    comm/MByteArray.cpp \
    field/MByteField.cpp \
    field/MBytesField.cpp \
    field/MCompositeField.cpp \
    field/MField.cpp \
    field/MIntField.cpp \
    field/MLongField.cpp \
    field/MShortField.cpp \
    field/MStringField.cpp \
    field/MUByteField.cpp \
    field/MUIntField.cpp \
    field/MULongField.cpp \
	field/MUShortField.cpp

HEADERS += \
    comm/MBaseDef.h \
    comm/MBaseFuncDef.h \
    comm/MByteArray.h \
    comm/MErrorCode.h \
    field/MArrayField.h \
    field/MByteField.h \
    field/MBytesField.h \
    field/MCompositeField.h \
    field/MField.h \
    field/MFieldInc.h \
    field/MFieldInfo.cpp_bak \
    field/MFieldInfo.h_bak \
    field/MIntField.h \
    field/MLongField.h \
    field/MShortField.h \
    field/MStringField.h \
    field/MUByteField.h \
    field/MUIntField.h \
    field/MULongField.h \
	field/MUShortField.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    Makefile \
    Makefile.rules
