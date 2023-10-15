#################################################################
### MAKE_LOADER_ONLY = 1 : only loader is make and all the
###                        programs are "optimized" for loader
###
### MAKE_LOADER_ONLY = 0 : except loader, all the programa are
###                        created for non-loader applications
#################################################################
MAKE_LOADER_ONLY = 0


#################################################################
### MAKE_DEBUG = 1 : make debug version program (with least
###                  optimization)
### MAKE_DEBUG = 0 : make release version program with most
###                  optimization)
#################################################################
MAKE_DEBUG = 0


#################################################################
### MAKE_RELEASE = 1 : make the program for release (default)
### MAKE_RELEASE = 0 : make the program for development debug
#################################################################
MAKE_RELEASE = 0


#################################################################
###          !!!  don't modify anything below  !!!
#################################################################


#################################################################
### ROOT_PATH
#################################################################
ROOT_PATH = $(CURDIR)


#################################################################
### PUBLIC_INC_PATH
#################################################################
PUBLIC_INC_PATH = $(ROOT_PATH)/include


#################################################################
### PUBLIC_LIB_PATH
#################################################################
PUBLIC_LIB_PATH = $(ROOT_PATH)/lib


#################################################################
### MAKE_RULES
#################################################################
MAKE_RULES = $(ROOT_PATH)/make/rules.mk


#################################################################
### compiler commands and options
#################################################################
CC = armcc  
ASM = armasm
AR = armar
LINK = armlink
AR_FLAGS = --create
LINK_FLAGS = --map --info totals --debug --userlibpath $(PUBLIC_LIB_PATH)


#################################################################
### commands provide by the shell
#################################################################
DEL = rm -f
COPY = cp -f


export MAKE_LOADER_ONLY
export MAKE_DEBUG
export MAKE_RELEASE
export ROOT_PATH
export PUBLIC_INC_PATH
export PUBLIC_LIB_PATH
export MAKE_RULES
export CC ASM AR LINK
export AR_FLAGS LINK_FLAGS
export DEL COPY


all : dep
	-> include/autocfg.h
	cd drive; make $@
	cd bin; make $@

dep cleandep new: 
	-> include/autocfg.h
	cd drive; make $@
	cd bin; make $@

#clean :
#	-> include/autocfg.h
#	cd drive; make clean
#	cd lib; make clean
#	cd bin; make clean

cleansys :
	-> include/autocfg.h
	cd drive; make clean
	cd lib; make clean
	cd bin; make clean
	-@rm -rf bin/sys/{*.bin,*.axf,*.symbol,*.list,*.d}
	
obj :
	-> include/autocfg.h
	cd drive; make obj
	cd bin; make obj

help :
	@echo
	@echo "make             - Make objects and applications"
	@echo "make cleandep    - Remove dependency files"

% :
	@echo
	@echo "Not support \"$@\" target."
	@echo "Please type \"make help\" for help information."


#####
SYS_LTHA SYS_LTHB SYS_LTHC SYS_LTHD SYS_LTHE SYS_LTHF SYS_LTHG\
SYS_TTHA SYS_TTHB SYS_TTHC SYS_TTHD \
SYS_TTZA SYS_TTZB SYS_TTZC SYS_TTZD \
SYS_TTHE SYS_TTHF SYS_TTHG SYS_TTHH \
SYS_TTZE SYS_TTZF SYS_TTZG SYS_TTZH SYS_ORHC SYS_ORHE SYS_ORHF SYS_ORHG SYS_LISB SYS_LISF SYS_S:
	cd bin/sys; make all IMAGE_PREFIX=$@ -f Makefile

make_drive_all :
	cd drive; make all

make_bin_libs :
	cd bin; make libs

CMPL_CODE = $(V)$(BW)$(BX)$(BY)$(BZ)

ifneq ($(CONFIGURE),)
autocfg :
	-> include/autocfg.h
	-echo "#ifndef __autocfg_h__"				>> include/autocfg.h
	-echo "#define __autocfg_h__"				>> include/autocfg.h
	-echo "#define AUTO_CONFIG"					>> include/autocfg.h

ifneq ($(BY), 0)
ifeq ($(BW), L)
endif
ifeq ($(BW), T)
	-echo "#define TOGGLE_MD"						>> include/autocfg.h
endif
ifeq ($(BW), O)
	-echo "#define ONFI_MD"							>> include/autocfg.h
endif
endif


ifneq ($(BY), 0)
ifeq ($(BX), I)
	-echo "#define INTEL_FLASH 1"							>> include/autocfg.h
	-echo "#define SAMSUNG_FLASH 0"						>> include/autocfg.h
	-echo "#define TOSHIBA_FLASH 0"						>> include/autocfg.h
#	-echo "#define BANK_PRE_READ 1"						>> include/autocfg.h
#	-echo "#define USE_TSB_NAND_CMD 0"				>> include/autocfg.h
#	-echo "#define EN_COPYBACK"								>> include/autocfg.h
endif
ifeq ($(BX), R)
	-echo "#define INTEL_FLASH 1"							>> include/autocfg.h
	-echo "#define SAMSUNG_FLASH 0"						>> include/autocfg.h
	-echo "#define TOSHIBA_FLASH 0"						>> include/autocfg.h
#	-echo "#define BANK_PRE_READ 1"						>> include/autocfg.h
#	-echo "#define USE_TSB_NAND_CMD 0"				>> include/autocfg.h
#	-echo "#define EN_SCRAMBLE_RANDOM_SEED"		>> include/autocfg.h
endif
ifeq ($(BX), S)
	-echo "#define INTEL_FLASH 0"							>> include/autocfg.h
	-echo "#define SAMSUNG_FLASH 1"						>> include/autocfg.h
	-echo "#define TOSHIBA_FLASH 0"						>> include/autocfg.h
#	-echo "#define BANK_PRE_READ 1"						>> include/autocfg.h
#	-echo "#define USE_TSB_NAND_CMD 0"				>> include/autocfg.h
#	-echo "#define EN_COPYBACK"								>> include/autocfg.h
endif
ifeq ($(BX), M)
	-echo "#define INTEL_FLASH 0"							>> include/autocfg.h
	-echo "#define SAMSUNG_FLASH 1"						>> include/autocfg.h
	-echo "#define TOSHIBA_FLASH 0"						>> include/autocfg.h
#	-echo "#define BANK_PRE_READ 0"						>> include/autocfg.h
#	-echo "#define USE_TSB_NAND_CMD 1"				>> include/autocfg.h	
#	-echo "#define EN_SCRAMBLE_RANDOM_SEED"		>> include/autocfg.h
endif
ifeq ($(BX), N)
	-echo "#define INTEL_FLASH 0"							>> include/autocfg.h
	-echo "#define SAMSUNG_FLASH 1"						>> include/autocfg.h
	-echo "#define TOSHIBA_FLASH 0"						>> include/autocfg.h
	-echo "#define BANK_PRE_READ 1"						>> include/autocfg.h
	-echo "#define USE_TSB_NAND_CMD 1"				>> include/autocfg.h
	-echo "#define EN_SLOW_RD"								>> include/autocfg.h
	-echo "#define EN_PAGE_RD"								>> include/autocfg.h
	-echo "#define EN_SLOW_RD_PAGE_PRE_READ"	>> include/autocfg.h
	-echo "#define EN_SCRAMBLE_RANDOM_SEED"		>> include/autocfg.h
endif
ifeq ($(BX), T)
	-echo "#define INTEL_FLASH 0"							>> include/autocfg.h
	-echo "#define SAMSUNG_FLASH 0"						>> include/autocfg.h
	-echo "#define TOSHIBA_FLASH 1"						>> include/autocfg.h
#	-echo "#define BANK_PRE_READ 1"						>> include/autocfg.h
#	-echo "#define USE_TSB_NAND_CMD 0"				>> include/autocfg.h
#	-echo "#define EN_COPYBACK"								>> include/autocfg.h
endif
endif


ifeq ($(BY), A)
	-echo "#define BLOCK_SHIFT 10"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 7"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 3"      >> include/autocfg.h
	-echo "#define MULTI_DIE 0"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), B)
	-echo "#define BLOCK_SHIFT 10"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 7"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 4"      >> include/autocfg.h
	-echo "#define MULTI_DIE 0"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), C)
	-echo "#define BLOCK_SHIFT 10"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 8"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 3"      >> include/autocfg.h
	-echo "#define MULTI_DIE 0"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), D)
	-echo "#define BLOCK_SHIFT 10"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 8"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 4"      >> include/autocfg.h
	-echo "#define MULTI_DIE 0"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), E)
	-echo "#define BLOCK_SHIFT 11"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 7"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 3"      >> include/autocfg.h
	-echo "#define MULTI_DIE 0"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), F)
	-echo "#define BLOCK_SHIFT 11"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 7"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 4"      >> include/autocfg.h
	-echo "#define MULTI_DIE 0"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), G)
	-echo "#define BLOCK_SHIFT 11"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 8"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 3"      >> include/autocfg.h
	-echo "#define MULTI_DIE 0"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), H)
	-echo "#define BLOCK_SHIFT 11"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 8"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 4"      >> include/autocfg.h
	-echo "#define MULTI_DIE 0"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), I)
	-echo "#define BLOCK_SHIFT 12"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 7"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 3"      >> include/autocfg.h
	-echo "#define MULTI_DIE 0"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), J)
	-echo "#define BLOCK_SHIFT 12"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 7"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 4"      >> include/autocfg.h
	-echo "#define MULTI_DIE 0"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), K)
	-echo "#define BLOCK_SHIFT 12"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 8"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 3"      >> include/autocfg.h
	-echo "#define MULTI_DIE 0"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), L)
	-echo "#define BLOCK_SHIFT 12"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 8"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 4"      >> include/autocfg.h
	-echo "#define MULTI_DIE 0"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), M)
	-echo "#define BLOCK_SHIFT 11"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 7"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 3"      >> include/autocfg.h
	-echo "#define MULTI_DIE 1"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), N)
	-echo "#define BLOCK_SHIFT 11"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 7"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 4"      >> include/autocfg.h
	-echo "#define MULTI_DIE 1"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), O)
	-echo "#define BLOCK_SHIFT 11"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 7"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 3"      >> include/autocfg.h
	-echo "#define MULTI_DIE 1"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 1"      		>> include/autocfg.h
endif
ifeq ($(BY), P)
	-echo "#define BLOCK_SHIFT 11"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 7"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 4"      >> include/autocfg.h
	-echo "#define MULTI_DIE 1"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 1"      		>> include/autocfg.h	
endif
ifeq ($(BY), Q)
	-echo "#define BLOCK_SHIFT 11"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 6"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 3"      >> include/autocfg.h
	-echo "#define MULTI_DIE 1"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), R)
	-echo "#define BLOCK_SHIFT 11"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 8"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 3"      >> include/autocfg.h
	-echo "#define MULTI_DIE 1"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), S)
	-echo "#define BLOCK_SHIFT 11"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 8"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 4"      >> include/autocfg.h
	-echo "#define MULTI_DIE 1"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), T)
	-echo "#define BLOCK_SHIFT 10"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 7"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 4"      >> include/autocfg.h
	-echo "#define MULTI_DIE 1"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), U)
	-echo "#define BLOCK_SHIFT 10"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 7"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 4"      >> include/autocfg.h
	-echo "#define MULTI_DIE 1"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 1"      		>> include/autocfg.h
endif
ifeq ($(BY), V)
	-echo "#define BLOCK_SHIFT 10"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 8"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 4"      >> include/autocfg.h
	-echo "#define MULTI_DIE 1"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), W)
	-echo "#define BLOCK_SHIFT 12"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 7"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 3"      >> include/autocfg.h
	-echo "#define MULTI_DIE 1"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), X)
	-echo "#define BLOCK_SHIFT 11"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 6"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 3"      >> include/autocfg.h
	-echo "#define MULTI_DIE 0"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), Y)
	-echo "#define BLOCK_SHIFT 11"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 6"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 4"      >> include/autocfg.h
	-echo "#define MULTI_DIE 0"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 0"      		>> include/autocfg.h
endif
ifeq ($(BY), Z)
	-echo "#define BLOCK_SHIFT 11"			>> include/autocfg.h
	-echo "#define PAGE_SHIFT 8"      	>> include/autocfg.h
	-echo "#define SECTOR_SHIFT 4"      >> include/autocfg.h
	-echo "#define MULTI_DIE 1"      		>> include/autocfg.h
	-echo "#define GAP_SHIFT 1"      		>> include/autocfg.h
endif
ifneq ($(BY), 0)
	-echo "#define PLANE_B_BH"					>> include/autocfg.h
endif


ifeq ($(BZ), A)
	-echo "#define CHAN_SHIFT 3"				>> include/autocfg.h
	-echo "#define BANK_SHIFT 0"				>> include/autocfg.h
endif
ifeq ($(BZ), B)
	-echo "#define CHAN_SHIFT 3"				>> include/autocfg.h
	-echo "#define BANK_SHIFT 1"				>> include/autocfg.h
endif
ifeq ($(BZ), C)
	-echo "#define CHAN_SHIFT 3"				>> include/autocfg.h
	-echo "#define BANK_SHIFT 2" 				>> include/autocfg.h
endif
ifeq ($(BZ), D)
	-echo "#define CHAN_SHIFT 3"				>> include/autocfg.h
	-echo "#define BANK_SHIFT 3"				>> include/autocfg.h
endif
ifeq ($(BZ), E)
	-echo "#define CHAN_SHIFT 2"				>> include/autocfg.h
	-echo "#define BANK_SHIFT 0"				>> include/autocfg.h
endif
ifeq ($(BZ), F)
	-echo "#define CHAN_SHIFT 2"				>> include/autocfg.h
	-echo "#define BANK_SHIFT 1"				>> include/autocfg.h
endif
ifeq ($(BZ), G)
	-echo "#define CHAN_SHIFT 2"				>> include/autocfg.h
	-echo "#define BANK_SHIFT 2" 				>> include/autocfg.h
endif
ifeq ($(BZ), H)
	-echo "#define CHAN_SHIFT 2"				>> include/autocfg.h
	-echo "#define BANK_SHIFT 3"				>> include/autocfg.h
endif
ifeq ($(BZ), I)
	-echo "#define CHAN_SHIFT 1"				>> include/autocfg.h
	-echo "#define BANK_SHIFT 0"				>> include/autocfg.h
endif
ifeq ($(BZ), J)
	-echo "#define CHAN_SHIFT 1"				>> include/autocfg.h
	-echo "#define BANK_SHIFT 1"				>> include/autocfg.h
endif
ifeq ($(BZ), K)
	-echo "#define CHAN_SHIFT 1"				>> include/autocfg.h
	-echo "#define BANK_SHIFT 2" 				>> include/autocfg.h
endif
ifeq ($(BZ), L)
	-echo "#define CHAN_SHIFT 1"				>> include/autocfg.h
	-echo "#define BANK_SHIFT 3"				>> include/autocfg.h
endif
ifeq ($(BZ), M)
	-echo "#define CHAN_SHIFT 0"				>> include/autocfg.h
	-echo "#define BANK_SHIFT 0"				>> include/autocfg.h
endif
ifeq ($(BZ), N)
	-echo "#define CHAN_SHIFT 0"				>> include/autocfg.h
	-echo "#define BANK_SHIFT 1"				>> include/autocfg.h
endif
ifeq ($(BZ), O)
	-echo "#define CHAN_SHIFT 0"				>> include/autocfg.h
	-echo "#define BANK_SHIFT 2" 				>> include/autocfg.h
endif
ifeq ($(BZ), P)
	-echo "#define CHAN_SHIFT 0"				>> include/autocfg.h
	-echo "#define BANK_SHIFT 3"				>> include/autocfg.h
endif
ifeq ($(BZ), 0)
endif

	-echo "#define __CMPL_CODE__ \"$(CMPL_CODE)\"" 		>> include/autocfg.h
	-echo "#endif"                   >> include/autocfg.h
endif

onesys : clean cleandep autocfg make_drive_all make_bin_libs $(CONFIGURE)
	
#####

