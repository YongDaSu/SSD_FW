image_Makefiles =

local_lib_makes  = rvct/Makefile
#local_lib_makes  += ftl_src/Makefile
#local_lib_makes += ata/Makefile

###
### It requires to generate different libraries under a directory.
### Hence, change local_lib_dirs to local_lib_makes and apply the
### same rules used by image_Makefiles.
###


###
### loader
###
ifeq ($(MAKE_LOADER_ONLY), 1)
#image_Makefiles += loader/Makefile_ldr_rom
#image_Makefiles += loader/Makefile_ldr_sram

#image_Makefiles += test/Makefile_test_rom
#image_Makefiles += test/Makefile_test_sram

image_Makefiles += gdp/Makefile_gdp_sram
#image_Makefiles += gdp/Makefile_dram_sram
#image_Makefiles += gdp/Makefile_satatest_sram
#image_Makefiles += gdp/Makefile_pb_sram
endif




###
### ssd micro code
###
ifneq ($(MAKE_LOADER_ONLY), 1)
image_Makefiles += sys/Makefile
endif






all dep cleandep obj :
	for x in $(local_lib_makes); do cd `dirname $$x`; make $@ -f `basename $$x`; cd $(CURDIR); done 
	for x in $(image_Makefiles); do cd `dirname $$x`; make $@ -f `basename $$x`; cd $(CURDIR); done

clean :
	for x in $(local_lib_makes); do cd `dirname $$x`; make $@ -f `basename $$x`; cd $(CURDIR); done 
	for x in $(image_Makefiles); do cd `dirname $$x`; make $@ -f `basename $$x`; cd $(CURDIR); done

new : clean all

libs :
	for x in $(local_lib_makes); do cd `dirname $$x`; make all -f `basename $$x`; cd $(CURDIR); done 
