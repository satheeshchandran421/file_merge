CC = g++
FLAGS = -O0 -Wall -L/opt/lib -std=c++17 -fPIC -Wno-unused-but-set-variable -fpermissive 
FS_FLAG = -lstdc++fs
BIN_DIR = bin
SRC_DIR = src

PROJ  = $(BIN_DIR)/fmerge
OBJDIR = obj
LIST  = >> cc.lst 2>&1
PLATFORM_LINKER=$(CC)

ALL_CFLAGS = $(PLATFORM_CFLAGS)
VPATH = $(SRC_DIR) $(BIN_DIR)
EXE = $(EXEDIR)$(PROJ)
MAP = $(EXEDIR)$(PROJ).map

CPPOBJS = \
	$(OBJDIR)/imerge.o \
	$(OBJDIR)/logmerge.o \
	$(OBJDIR)/main.o \
	$(OBJDIR)/merge_run.o
	
$(EXE): $(CPPOBJS)
	rm -f $(EXE)
	$(PLATFORM_LINKER) $(FLAGS) \
	  -o$(EXE) $(CPPOBJS) $(FS_FLAG) \
	  $(LIBS) \
	  -Xlinker -Map=$(MAP)
	echo "FINISHED GENERATING $(EXE) EXECUTABLE" $(LIST)
	echo "-----------------------------------------------------" $(LIST)
clean:
	rm -f $(CPPOBJS)
	rm -f $(EXE)
	echo "Finished clean" $(LIST)

$(OBJDIR)/%.o : %.cpp
	echo Compiling: $< $(LIST)
	$(CC) -c $(FLAGS) $< -o $@ $(LIST)

$(OBJDIR)/imerge.o:	imerge.cpp $(INCLUDES)
$(OBJDIR)/logmerge.o:	logmerge.cpp $(INCLUDES)
$(OBJDIR)/main.o:	main.cpp $(INCLUDES)
$(OBJDIR)/merge_run.o:	merge_run.cpp $(INCLUDES)

