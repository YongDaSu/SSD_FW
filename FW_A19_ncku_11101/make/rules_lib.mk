#
# The Makefile which finally includes this rule file should
# define the following macros and values:
#
#    1) TARGET = make_lib              (used by rules.mk)
#                                      
#    2) LIB_NAME = my_lib_name         (e.g. sys.a; the library name of the program in this directory)
#
#    3) OBJS  = xxx.o yyy.o            (C and/or assembly objects list)
#                                      
#    4) CDEPS = xxx.d yyy.d            (C depend file)
#                                      
#    5) SUB_DIRS = sub_dir1 sub_dir2   (furthur program directories to be made; could be empty)
#
#    6) PUBLISHED_LIB_PATH             (where the LIB_NAME will be stored)
#


#######################
### all
#######################
ifeq ($(SUB_DIRS),)
all: $(PUBLISHED_LIB_PATH)/$(LIB_NAME) 

else
all: $(PUBLISHED_LIB_PATH)/$(LIB_NAME) 
	for x in $(SUB_DIRS); do cd $$x; make $@; cd $(CURDIR); done

endif


$(PUBLISHED_LIB_PATH)/$(LIB_NAME) : $(OBJS)
	$(AR) $(AR_FLAGS) $@ $(OBJS)



#######################
### clean
#######################
ifeq ($(SUB_DIRS),)
clean:
	- $(DEL) $(OBJS)

else
clean:
	- $(DEL) $(OBJS)
	for x in $(SUB_DIRS); do cd $$x; make $@; cd $(CURDIR); done 

endif



#######################
### new
#######################
new : clean all




#######################
### obj
#######################
obj : all



###
### TODO : migrate make dependency rules to rules.mk
###
.SUFFIXES : .d .c


.c.d : $<
	$(CC) -I./ -I$(PUBLIC_INC_PATH) $< -M -o $*.o --depend=$*.d --depend_format=unix_escaped
	#-sed /$*\.d/d ./depend.mk > ./depend.tmp
	-grep --invert-match "$*.d" ./depend.mk > ./depend.tmp
	-cat ./depend.tmp > ./depend.mk
	-$(DEL) ./depend.tmp
	@echo include $*.d  >> ./depend.mk


#######################
### dep
#######################
ifeq ($(SUB_DIRS),)
dep : depend.mk $(CDEPS)

else
dep : depend.mk $(CDEPS)
	for x in $(SUB_DIRS); do cd $$x; make $@; cd $(CURDIR); done

endif


depend.mk :
	- > ./depend.mk



#######################
### cleandep
#######################
ifeq ($(SUB_DIRS),)
cleandep : 
	- $(DEL) $(CDEPS)
	- > ./depend.mk

else
cleandep : 
	- $(DEL) $(CDEPS)
	- > ./depend.mk
	for x in $(SUB_DIRS); do cd $$x; make $@; cd $(CURDIR); done

endif


include ./depend.mk

