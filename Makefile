# Makefile


# application executable
PROGRAM_NAME = gsierpinski


#
# compiler used
CC = gcc
# linker
LD = $(CC)

#
# PATHS
SRC_PATH=src
OBJ_PATH=obj
BIN_PATH=bin
OBJ_EXT=.o
MAKEDIFF_FILE=make.diff

#
# sources set (filenames without extension)

# sources to compile (only_new | all) - file is prepared in remake.sh script
SOURCESC     =$(shell cat build.files)
# this is needed only for objects
SOURCESC_ALL =$(shell ls -1 src/*.c | cut -f2 -d/ | cut -f1 -d.)


#
# generated objects rule
OBJECTS = $(SOURCESC_ALL:%=$(OBJ_PATH)/%$(OBJ_EXT))
#OBJECTS=$(OBJ_PATH)/$(shell ls src/*.c | cut -f2 -d/ | cut -f1 -d.)$(OBJ_EXT)
#OBJECTS=$(shell ls $(OBJ_PATH)/*$(OBJ_EXT))


#
# FLAGS

#
# compiler flags
CFLAGS_PKGCONFIG += $(shell pkg-config  --cflags glib-2.0 \
                                --cflags gtk+-2.0 \
                                --cflags gtkglext-1.0)

CFLAGS = -Wall -O2 -std=c99  $(CFLAGS_PKGCONFIG)

#
# linker flags
LDFLAGS_PKGCONFIG += $(shell pkg-config --libs glib-2.0 \
                                --libs gtk+-2.0 \
                                --libs gtkglext-1.0)

LDFLAGS = -lGL  -lGLU  -lgthread-2.0 -lm -std=gnu99  $(LDFLAGS_PKGCONFIG)

#
# STANDARD RULES

#
# `rm` alias
RM = /bin/rm -f


#
# rule for compiling all sources
all:  $(SOURCESC)  $(PROGRAM_NAME)

#
# just compile
compile:  $(SOURCESC)


#
# rule for linking objects
$(PROGRAM_NAME):  $(OBJECTS)
	$(LD)  -g  $(LDFLAGS)  $(OBJECTS)  -o  $(BIN_PATH)/$@


#
# rules for compiling c sources
$(SOURCESC):
	$(CC) -c  $(SRC_PATH)/$@.c  $(CFLAGS)  -o  $(OBJ_PATH)/$@$(OBJ_EXT)


install:
	@echo You must be root to install


# cleaning rule
clean:
	$(RM)  $(BIN_PATH)/$(PROGRAM_NAME)  $(OBJECTS)  $(MAKEDIFF_FILE)

