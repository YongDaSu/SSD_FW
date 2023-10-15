TARGET = make_lib

LIB_NAME = rvct.a

OBJS =	rvctHeap.o	\
	rvctISR.o	\
	rvctRetarget.o	\
	rvctStack.o	\
	bget.o	\
	dpd.o	\
	dram_init.o	\
	rvctSubMain.o
	
		

CDEPS =	rvctISR.d	\
	rvctRetarget.d

SUB_DIRS =

IMAGE_PATH_FLAGS =

PUBLISHED_LIB_PATH = $(PUBLIC_LIB_PATH)

include $(MAKE_RULES)
