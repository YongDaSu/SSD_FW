TARGET = make_image

###
### change this macro value for this image prefix
###
ifeq ($(IMAGE_PREFIX),)
IMAGE_PREFIX = SYS_S
endif


###
### add obj filenames of your program (xxx.c --> xxx.o; yyy.s --> yyy.o)
###
OBJS =	main.o \
        bget.o \
	sysCPU_a.o \
	rvctVectors.o \
	rvctRstHdlr.o \
	rvctSubMain.o \
	ver_sata.o \
	uart_cmd_channel.o \
	ftl1.o \
	ftl_wbm.o \
	dpd.o \
	dram_init.o


###
### add dependency filenames of your C program (xxx.c --> xxx.d)
###
CDEPS =	main.d \
        bget.d \
	rvctSubMain.d \
	uart_cmd_channel.d \
	ftl1.d \
	ftl_wbm.d \
	dpd.d \
	dram_init.d







IMAGE_PATH_FLAGS = -DPROG_ROOT_PATH=\"$(ROOT_PATH)\" -DUSER_NAME=\"$(USERNAME)\"

LIBS = driver.a rvct.a

LDS = rvctScatter


ENTRY = 0

DEPENDENCY = $(IMAGE_PREFIX).d

COMPILATION_LOCAL_RULES = renew rvctVectors.s ver_sata.c

COMPILATION_LOCAL_RULES_POST = checksum



include $(MAKE_RULES)


###
### local rules should be after  "include $(MAKE_RULES)"  statement
###
renew : 
	- rm rvctVectors.*
	- touch rvctVectors_source.s
	- rm ver_sata.*
	- rm main.o
	- rm uart_cmd_channel.o

rvctVectors.s : rvctVectors_source.s
	armcc -DWITH_SATA_ID_TABLE -E rvctVectors_source.s > rvctVectors.s

ver_sata.c : ver.c
	armcc -I$(PUBLIC_INC_PATH) -DINTERFACE_SATA -E ver.c > ver_sata.c


copy :
	cp $(IMAGE_PREFIX).bin SYS_S.bin

checksum :
	SUM.exe $(IMAGE_PREFIX).bin

