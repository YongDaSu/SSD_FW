
#
# expected macroes in this file
#
#	TARGET			;make_lib or make_image	(used in this file)
#
#	IMAGE_PATH_FLAGS	;e.g. -DPROG_ROOT_PATH=\"$(ROOT_PATH)\" -DUSER_NAME=\"$(USERNAME)\"
#

.SUFFIXES : .o .c .s


EXTRA_C_FLAGS =


ifeq ($(MAKE_LOADER_ONLY), 1)
EXTRA_C_FLAGS += -DMAKE_LOADER_ONLY
endif


ifeq ($(MAKE_DEBUG), 1)
EXTRA_C_FLAGS += -g -O0 --thumb
else
EXTRA_C_FLAGS += -Ospace -O2
endif



.c.o : $<
	$(CC) -I./ -I$(PUBLIC_INC_PATH) $(IMAGE_PATH_FLAGS) --bss_threshold=0 -c --littleend --cpu=ARM968E-S $< -o $@ $(EXTRA_C_FLAGS) --apcs interwork -DMAKE_RELEASE=$(MAKE_RELEASE)
#	 -S --Interleave


.s.o : $<
	$(ASM) --apcs interwork -g --cpu=ARM968E-S $< -o $@ 




ifeq ($(TARGET), make_lib)
include $(ROOT_PATH)/make/rules_lib.mk
endif

ifeq ($(TARGET), make_image)
include $(ROOT_PATH)/make/rules_image.mk
endif

