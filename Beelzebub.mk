###
# I assume $(PREFIX) and $(MAKECMDGOALS) are set!
###

##########
# Target #
KERNEL_NAME				:= beelzebub
ARC						:=
AUX						:=

############
# Settings #
PRECOMPILER_FLAGS		:= __BEELZEBUB 
SETTINGS 				:=

SMP						:= true
#	Defaults to enabled.

################################################
#	ARCHITECTURE-SPECIFIC SETTINGS AND FLAGS   #
################################################

##############
# 64-bit x86 #
ifneq (,$(findstring amd64,$(MAKECMDGOALS)))
	ARC					:= amd64
	AUX					:= x86

	PRECOMPILER_FLAGS	+= __BEELZEBUB__ARCH_AMD64 __BEELZEBUB__ARCH_X86 

####################################
# 32-bit x86 with 36-bit addresses #
else ifneq (,$(findstring ia32pae,$(MAKECMDGOALS)))
	ARC					:= ia32pae
	AUX					:= x86

	PRECOMPILER_FLAGS	+= __BEELZEBUB__ARCH_IA32PAE __BEELZEBUB__ARCH_IA32 
	PRECOMPILER_FLAGS	+= __BEELZEBUB__ARCH_X86 

##############
# 32-bit x86 #
else ifneq (,$(findstring ia32,$(MAKECMDGOALS)))
	ARC					:= ia32
	AUX					:= x86

	PRECOMPILER_FLAGS	+= __BEELZEBUB__ARCH_IA32 __BEELZEBUB__ARCH_X86 

endif

################
#	SETTINGS   #
################

####################################### CONFIGURATION ##########

#########
# Debug #
ifneq (,$(findstring conf-profile,$(MAKECMDGOALS)))
	PRECOMPILER_FLAGS	+= __BEELZEBUB__PROFILE __BEELZEBUB__RELEASE 
	PRECOMPILER_FLAGS	+= __JEGUDIEL__PROFILE __JEGUDIEL__RELEASE 

	SETTINGS			+= conf-profile
else ifneq (,$(findstring conf-release,$(MAKECMDGOALS)))
	PRECOMPILER_FLAGS	+= __BEELZEBUB__RELEASE 
	PRECOMPILER_FLAGS	+= __JEGUDIEL__RELEASE 

	SETTINGS			+= conf-release
else
	#	Yes, debug is default!

	PRECOMPILER_FLAGS	+= __BEELZEBUB__DEBUG 
	PRECOMPILER_FLAGS	+= __JEGUDIEL__DEBUG 

	SETTINGS			+= conf-debug
endif

####################################### FLAGS ##########

###############
# SMP disable #
ifneq (,$(findstring no-smp,$(MAKECMDGOALS)))
	SMP					:=

	PRECOMPILER_FLAGS	+= __BEELZEBUB_SETTINGS_NO_SMP 
	PRECOMPILER_FLAGS	+= __JEGUDIEL_SETTINGS_NO_SMP 

	SETTINGS			+= no-smp
else
	PRECOMPILER_FLAGS	+= __BEELZEBUB_SETTINGS_SMP 
	PRECOMPILER_FLAGS	+= __JEGUDIEL_SETTINGS_SMP 

	SETTINGS			+= smp
endif

#############################################
# Lock type for fixed-size object allocator #
ifneq (,$(findstring obja-rrspinlock,$(MAKECMDGOALS)))
	SMP					:=

	PRECOMPILER_FLAGS	+= __BEELZEBUB_SETTINGS_OBJA_RRSPINLOCK 

	SETTINGS			+= obja-rrspinlock
else
	PRECOMPILER_FLAGS	+= __BEELZEBUB_SETTINGS_OBJA_SPINLOCK 

	SETTINGS			+= obja-spinlock
endif

####################################### Tests ##########

############
# ALL!!!1! #
ifneq (,$(findstring test-all,$(MAKECMDGOALS)))
	PRECOMPILER_FLAGS	+= __BEELZEBUB__TEST_ALL 

	#	Aye, these are added explicitly.
	PRECOMPILER_FLAGS	+= __BEELZEBUB__TEST_MT 
	PRECOMPILER_FLAGS	+= __BEELZEBUB__TEST_STR 
	PRECOMPILER_FLAGS	+= __BEELZEBUB__TEST_OBJA 

	SETTINGS			+= test-all
else
	ifneq (,$(findstring test-mt,$(MAKECMDGOALS)))
		PRECOMPILER_FLAGS	+= __BEELZEBUB__TEST_MT 

		SETTINGS			+= test-mt
	else ifneq (,$(findstring test-str,$(MAKECMDGOALS)))
		PRECOMPILER_FLAGS	+= __BEELZEBUB__TEST_STR 

		SETTINGS			+= test-str
	else ifneq (,$(findstring test-obja,$(MAKECMDGOALS)))
		PRECOMPILER_FLAGS	+= __BEELZEBUB__TEST_OBJA 

		SETTINGS			+= test-obja
	else
		#	Do somethin'.
	endif
endif

####################################### PRECOMPILER FLAGS ##########

GCC_PRECOMPILER_FLAGS	:= $(patsubst %,-D %,$(PRECOMPILER_FLAGS))

# When architecture files are present...
ifneq (,$(ARC))
	GCC_PRECOMPILER_FLAGS	+= -D __BEELZEBUB__ARCH=$(ARC)
endif

# When auxiliary files are present...
ifneq (,$(AUX))
	GCC_PRECOMPILER_FLAGS	+= -D __BEELZEBUB__AUX=$(AUX)
endif

####################################### COMMON PATHS ##########

# Binary blobs
KERNEL_BIN				:= $(KERNEL_NAME).$(ARC).bin

# Installation
KERNEL_INSTALL_DIR		:= $(PREFIX)/bin
KERNEL_INSTALL_PATH		:= $(KERNEL_INSTALL_DIR)/$(KERNEL_BIN)

# ISO
ISO_PATH				:= $(PREFIX)/$(KERNEL_NAME).$(ARC).$(AUX).iso

####################################### WRAP UP ##########

$(SETTINGS):: $(ARC)
	@ true
#	Just makin' sure these don't error out. Adding '@ true' stops GNU Make from
#	displaying 'Nothing to be done for ...', which gets annoying when there are
#	more settings.
