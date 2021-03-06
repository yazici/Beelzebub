################################################################################
#                                   PROLOGUE                                   #
################################################################################

.SUFFIXES:  

# There is no default target.
all:
	@ echo -n "Currently supported target architectures are: " 1>&2
	@ echo "amd64, ia32pae, ia32" 1>&2
	@ echo "Please choose one of them as a target!" 1>&2
	@ return 42 # Yes, the answer to 'all', basically.

# Solution directories
PROJ_SUBDIR	:= apps/loadtest
PREFIX2		:= ./../..
PREFIX		:= ./../../build
INC_COMMON	:= ./../../sysheaders

# Local directories
SRC_DIR		:= ./src
INC_DIR		:= ./inc
ARC_DIR		:= .
AUX_DIR		:= .
BUILD_HOST	:= ./build

# Common settings
include ../../Beelzebub.mk

# Fake targets.
.PHONY: all install uninstall clean linku build $(ARC) $(SETTINGS)

# Output files
BUILD_DIR			:= $(BUILD_HOST)/$(ARC)
APP_BIN				:= loadtest.exe
APP_PATH			:= $(BUILD_HOST)/$(APP_BIN)
APP_INSTALL_DIR		:= $(SYSROOT)/apps
APP_INSTALL_PATH	:= $(APP_INSTALL_DIR)/$(APP_BIN)

################################################################################
#                             TOOLCHAIN & SETTINGS                             #
################################################################################

# Toolchain
include ../../Toolchain.mk

# Common options for GCC
GCCFLAGS	:= $(GCC_PRECOMPILER_FLAGS) -D __BEELZEBUB_APPLICATION 
GCCFLAGS	+= -Wall -Wsystem-headers -fno-omit-frame-pointer 
GCCFLAGS	+= -O2 -flto -pipe 
GCCFLAGS	+= --sysroot=$(SYSROOT) 

# C/C++ options
CFLAGS		:= $(GCCFLAGS) -std=gnu99
CXXFLAGS	:= $(GCCFLAGS) -std=gnu++14 -fno-rtti -fno-exceptions

# Assembler options
ASFLAGS		:= $(GCC_PRECOMPILER_FLAGS)

# Linker options, with optimization
LOFLAGS		:= -Wl,-z,max-page-size=0x1000 -fuse-linker-plugin 
LOFLAGS		+= -Wall -Wsystem-headers -fno-omit-frame-pointer 
LOFLAGS		+= -O2 -flto=jobserver -pipe 
LOFLAGS		+= --sysroot=$(SYSROOT) 

# Linker options, without optimization
LDFLAGS		:= -z max-page-size=0x1000 -nostdlib -nodefaultlibs 

# Strip options
STRIPFLAGS	:= -s 

################################################################################
#                        ARCHITECTURE-SPECIFIC SETTINGS                        #
################################################################################

##############
# 64-bit x86 #
ifeq ($(ARC),amd64)
	ASFLAGS		+= -f elf64
	CFLAGS		+= -m64
	CXXFLAGS	+= -m64

####################################
# 32-bit x86 with 36-bit addresses #
else ifeq ($(ARC),ia32pae)
	ASFLAGS		+= -f elf32
	CFLAGS		+= -m32
	CXXFLAGS	+= -m32

##############
# 32-bit x86 #
else ifeq ($(ARC),ia32)
	ASFLAGS		+= -f elf32
	CFLAGS		+= -m32
	CXXFLAGS	+= -m32

endif

##############
# Common x86 #
ifeq ($(AUX),x86)
	ifneq (,$(MTUNE))
		CFLAGS		+= -mtune=$(MTUNE)
		CXXFLAGS	+= -mtune=$(MTUNE)
	endif
endif

# Linker script
LDFILE		:= ./link.$(ARC).ld

################################################################################
#                             OBJECTS AND SOURCES                              #
################################################################################

include ../../Sources.mk

# Bootstrapping
CFLAGS		+= $(INCFLAGS) 
CXXFLAGS	+= $(INCFLAGS) 

################################################################################
#                                   TARGETS                                    #
################################################################################

# Do nothing for the architecture as a target.
$(ARC):
	@ true

###############################
# Install to prefix directory #
install: $(APP_INSTALL_PATH)
	@ true

####################################
# Uninstalls from prefix directory #
uninstall:
	@ rm $(APP_INSTALL_PATH)

##############################
# Cleans the build directory #
clean:
#	@ echo "/REM:" $(BUILD_HOST)
	@ rm -Rf $(BUILD_HOST)

##########################
# Link the target binary #
linku: $(OBJECTS)
#	@ echo "/LNK/UNO:" $(APP_PATH)
	@ $(LD) $(LDFLAGS) -o $(APP_PATH) $(OBJECTS) 

##########################
# Build all object files #
build: $(OBJECTS)
	@ true

####################################### BINARY BLOBS ##########

###########################################
# Install binary blob to prefix directory #
$(APP_INSTALL_PATH): $(APP_PATH)
#	@ echo "/STRIP:" $< ">" $@
	@ mkdir -p $(APP_INSTALL_DIR)
#	@ cp $< $@
	@ $(STRIP) $(STRIPFLAGS) -o $@ $<

##################################################
# Link the target binary with extra optimization #
$(APP_PATH): $(OBJECTS)
#	@ echo "/LNK/OPT:" $@
	@ mkdir -p $(@D)
	+@ $(LO) $(LOFLAGS) -o $@ $(OBJECTS)

####################################### CODE FILES ##########

include ../../Files.mk
