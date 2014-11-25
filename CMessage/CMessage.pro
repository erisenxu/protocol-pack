#-------------------------------------------------
#
# Project created by QtCreator 2014-11-25T22:07:50
#
#-------------------------------------------------

QT       -= core gui

TARGET = FMessage
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    main.c \
    field/ArrayField.c \
    field/ByteField.c \
    field/Field.c \
    field/IntField.c \
    field/LongField.c \
    field/ShortField.c \
    field/StringField.c \
    field/UByteField.c \
    field/UIntField.c \
    field/ULongField.c \
    field/UShortField.c \
    comm/ByteArray.c

HEADERS += \
    field/ArrayField.h \
    field/ByteField.h \
    field/Field.h \
    field/FieldInc.h \
    field/IntField.h \
    field/LongField.h \
    field/MsgBase.h \
    field/ShortField.h \
    field/StringField.h \
    field/UByteField.h \
    field/UIntField.h \
    field/ULongField.h \
    field/UShortField.h \
    comm/BaseDef.h \
    comm/BaseFuncDef.h \
    comm/ByteArray.h \
    comm/ErrorCode.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    Makefile \
    Makefile.rules
