#
# The Makefile which finally includes this rule file should
# define the following macros and values:
#
#    1) TARGET = make_image              (used by rules.mk)
#                                      
#    2) IMAGE_PREFIX = image_name_prefix (e.g. image; finally image.axf, image.list, etc will be output)
#
#    3) OBJS  = xxx.o yyy.o              (C and/or assembly objects list)
#                                      
#    4) CDEPS = xxx.d yyy.d              (C depend file)
#
#    5) IMAGE_PATH_FLAGS =               (e.g. -DPROG_ROOT_PATH=\"$(ROOT_PATH)\" -DUSER_NAME=\"$(USERNAME)\")
#
#    6) LIBS = xxx.a yyy.a               (libraries)
#
#    7) LDS = rvctScatter                (linker script file; arm scatter file)
#
#    8) ENTRY = Reset_Handler            (your program image entry point)
#
#    9) DEPENDENCY = my_dependency_file	 (the file name of the dependency file used the Makefile)
#
#   10) COMPILATION_LOCAL_RULES		 (before any compilation, the specified rules will be applied)
#
#   11) COMPILATION_LOCAL_RULES_POST     (after all compilation, the specified rules will be applied)
#


#TODO : convert LIBS to ABS_LIS and let the image to depend on them

IMAGE_AXF = $(IMAGE_PREFIX).axf
IMAGE_BIN = $(IMAGE_PREFIX).bin
IMAGE_LST = $(IMAGE_PREFIX).list
IMAGE_SYM = $(IMAGE_PREFIX).symbol


#######################
### all
#######################
all: $(COMPILATION_LOCAL_RULES) $(IMAGE_BIN) $(COMPILATION_LOCAL_RULES_POST)


$(IMAGE_BIN) : $(IMAGE_AXF)
	fromelf --bin --output $@ $(IMAGE_AXF)

$(IMAGE_AXF) : $(OBJS) $(LIBS)
	@echo " necessary to replace the dependency"
	@echo " necessary to replace the dependency"
	@echo " necessary to replace the dependency"
	$(LINK) $(LINK_FLAGS) 	--entry $(ENTRY)	\
				--scatter $(LDS)	\
				--list $(IMAGE_LST)	\
				--output $@		\
				--list_mapping_symbols	\
				--symdefs $(IMAGE_SYM)	\
				--info libraries	\
				$(OBJS)			\
				$(LIBS)


$(LIBS) : $(PUBLIC_LIB_PATH)/$@
	@echo examine $@



#######################
### clean
#######################
clean:
	- $(DEL) $(OBJS) *.a $(IMAGE_AXF) $(IMAGE_BIN) $(IMAGE_LST) $(IMAGE_SYM)




#######################
### new
#######################
new : clean all




#######################
### obj
#######################
obj : $(COMPILATION_LOCAL_RULES) $(OBJS)



###
### TODO : migrate make dependency rules to rules.mk
###
.SUFFIXES : .d .c


.c.d : $<
	$(CC) -I./ -I$(PUBLIC_INC_PATH) $(IMAGE_PATH_FLAGS) $< -M -o $*.o --depend=$*.d --depend_format=unix_escaped
	#-sed /$*\.d/d ./$(DEPENDENCY) > ./depend.tmp
	-grep --invert-match "$*.d" ./$(DEPENDENCY) > ./depend.tmp
	-cat ./depend.tmp > ./$(DEPENDENCY)
	-$(DEL) ./depend.tmp
	@echo include $*.d  >> ./$(DEPENDENCY)


#######################
### dep
#######################
dep : $(DEPENDENCY) $(CDEPS)



$(DEPENDENCY) :
	- > $(DEPENDENCY)



#######################
### cleandep
#######################
cleandep : 
	- $(DEL) $(CDEPS) $(DEPENDENCY)
	#- > $(DEPENDENCY)


include ./$(DEPENDENCY)

