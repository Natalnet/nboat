# Copyright 1994-2010 The MathWorks, Inc.
#
# File    : accel_vcx64.tmf   $Revision: 1.1.6.16 $
#
# Abstract:
#       Accelerator template makefile for building a Windows-based,
#       generated mex-file of Simulink model using generated C code
#       and the
#          Microsoft Visual C/C++ compiler version 8.0 for x64
#
#       Note that this template is automatically customized by the build 
#       procedure to create "<model>.mk"
#
#       The following defines can be used to modify the behavior of the
#       build:
#
#         OPT_OPTS       - Optimization option. Specify OPT_OPTS=-g to
#                          create a mex file for debugging.
#         MEX_OPTS       - User specific mex options.
#         USER_SRCS      - Additional user sources, such as files needed by
#                          S-functions.
#         USER_INCLUDES  - Additional include paths
#                          (i.e. USER_INCLUDES="-Iwhere-ever -Iwhere-ever2")
#
#       This template makefile is designed to be used with a system target
#       file that contains 'rtwgensettings.BuildDirSuffix' see accel.tlc

#------------------------ Macros read by make_rtw -----------------------------
#
# The following macros are read by the build procedure:
#
#  MAKECMD         - This is the command used to invoke the make utility
#  HOST            - What platform this template makefile is targeted for
#                    (i.e. PC or UNIX)
#  BUILD           - Invoke make from the build procedure (yes/no)?
#  SYS_TARGET_FILE - Name of system target file.

MAKECMD         = nmake
HOST            = PC
BUILD           = yes
SYS_TARGET_FILE = accel.tlc
COMPILER_TOOL_CHAIN = vcx64

#---------------------- Tokens expanded by make_rtw ---------------------------
#
# The following tokens, when wrapped with "|>" and "<|" are expanded by the
# build procedure.
#
#  MODEL_NAME      - Name of the Simulink block diagram
#  MODEL_MODULES   - Any additional generated source modules
#  MAKEFILE_NAME   - Name of makefile created from template makefile <model>.mk
#  MATLAB_ROOT     - Path to where MATLAB is installed.
#  MATLAB_BIN      - Path to MATLAB executable.
#  S_FUNCTIONS     - List of S-functions.
#  S_FUNCTIONS_LIB - List of S-functions libraries to link.
#  SOLVER          - Solver source file name
#  NUMST           - Number of sample times
#  TID01EQ         - yes (1) or no (0): Are sampling rates of continuous task
#                    (tid=0) and 1st discrete task equal.
#  NCSTATES        - Number of continuous states
#  BUILDARGS       - Options passed in at the command line.
#  MEXEXT          - extension that a mex file has. See the MATLAB mexext 
#                    command

MODEL              = SailingYachtModel
MODULES            = SailingYachtModel_acc_data.c rtGetInf.c rtGetNaN.c rt_nonfinite.c 
MAKEFILE           = SailingYachtModel.mk
MATLAB_ROOT        = C:\Program Files\MATLAB\R2013a
ALT_MATLAB_ROOT    = C:\PROGRA~1\MATLAB\R2013a
MATLAB_BIN         = C:\Program Files\MATLAB\R2013a\bin
ALT_MATLAB_BIN     = C:\PROGRA~1\MATLAB\R2013a\bin
MASTER_ANCHOR_DIR  = 
START_DIR          = C:\Users\Davi\Desktop\SailingYachtModel
S_FUNCTIONS        = 
S_FUNCTIONS_LIB    = 
SOLVER             = 
NUMST              = 2
TID01EQ            = 1
NCSTATES           = 8
MEM_ALLOC          = RT_STATIC
BUILDARGS          = 
MEXEXT             = mexw64

MODELREFS          = 
SHARED_SRC         = 
SHARED_SRC_DIR     = 
SHARED_BIN_DIR     = 
SHARED_LIB         = 
MEX_OPT_FILE       = -f C:\Users\Davi\AppData\Roaming\MATHWO~1\MATLAB\R2013a\mexopts.bat
COMPUTER           = PCWIN64
VISUAL_VER         = 7.1SDK
OPTIMIZATION_FLAGS = /Od /Oy- /DNDEBUG
ADDITIONAL_LDFLAGS = 

#--------------------------- Model and reference models -----------------------
MODELLIB                  = SailingYachtModellib.lib
MODELREF_LINK_LIBS        = 
MODELREF_INC_PATH         = 
RELATIVE_PATH_TO_ANCHOR   = ..\..\..
MODELREF_TARGET_TYPE      = NONE

!if "$(MATLAB_ROOT)" != "$(ALT_MATLAB_ROOT)"
MATLAB_ROOT = $(ALT_MATLAB_ROOT)
!endif
!if "$(MATLAB_BIN)" != "$(ALT_MATLAB_BIN)"
MATLAB_BIN = $(ALT_MATLAB_BIN)
!endif

#--------------------------- Tool Specifications ------------------------------

CPU = AMD64
!include $(MATLAB_ROOT)\rtw\c\tools\vctools.mak

MEX    = $(MATLAB_BIN)\mex
CC     = $(MATLAB_BIN)\mex -c
LIBCMD = lib
PERL   = $(MATLAB_ROOT)\sys\perl\win32\bin\perl

#----------------------------- Include/Lib Path -------------------------------
MATLAB_INCLUDES =                    $(MATLAB_ROOT)\simulink\include
MATLAB_INCLUDES = $(MATLAB_INCLUDES);$(MATLAB_ROOT)\extern\include
MATLAB_INCLUDES = $(MATLAB_INCLUDES);$(MATLAB_ROOT)\rtw\c\src

# Additional includes

MATLAB_INCLUDES = $(MATLAB_INCLUDES);$(START_DIR)\slprj\accel\SailingYachtModel
MATLAB_INCLUDES = $(MATLAB_INCLUDES);$(START_DIR)


INCLUDE = .;$(RELATIVE_PATH_TO_ANCHOR);$(MATLAB_INCLUDES);$(ADD_INCLUDES);$(INCLUDE)

!if "$(SHARED_SRC_DIR)" != ""
INCLUDE = $(INCLUDE);$(SHARED_SRC_DIR)
!endif

#----------------------- C and MEX optimization options -----------------------

DEFAULT_OPT_OPTS = -O

MEX_OPTS = 
OPT_OPTS = $(DEFAULT_OPT_OPTS)

!if "$(OPTIMIZATION_FLAGS)" != ""
MEX_OPT_OPTS = OPTIMFLAGS="$(OPTIMIZATION_FLAGS)"    # passed to 'mex -c'
!else
MEX_OPT_OPTS = $(OPT_OPTS)    # passed to 'mex -c'
!endif

!if "$(MEX_OPTS)" == "-g"
MEX_OPT_OPTS =
!endif

!if "$(ADDITIONAL_LDFLAGS)" != ""
MEX_LDFLAGS = LINKFLAGS="$$LINKFLAGS $(ADDITIONAL_LDFLAGS)"
!else
MEX_LDFLAGS =
!endif

#------------------------------- Mex Options  ---------------------------------

MEX_FLAGS = $(MODELREF_INC_PATH) $(MEX_ARCH) $(MEX_OPTS) $(MEX_OPT_OPTS) $(MEX_LDFLAGS) $(MEX_OPT_FILE)

#----------------------------- Source Files -----------------------------------
USER_SRCS =

SRCS = $(MODULES) $(USER_SRCS)

OBJS_CPP_UPPER = $(SRCS:.CPP=.obj)
OBJS_CPP_LOWER = $(OBJS_CPP_UPPER:.cpp=.obj)
OBJS_C_UPPER = $(OBJS_CPP_LOWER:.C=.obj)
OBJS = $(MODEL)_acc.obj $(OBJS_C_UPPER:.c=.obj)

SHARED_OBJS = $(SHARED_SRC:.c=.obj)

#-------------------------- Additional Libraries ------------------------------

LIBS =



LIBUT          = $(MATLAB_ROOT)\extern\lib\win64\microsoft\libut.lib
LIBMWMATHUTIL  = $(MATLAB_ROOT)\extern\lib\win64\microsoft\libmwmathutil.lib
LIBMWIPP = $(MATLAB_ROOT)\lib\win64\libippmwipt.lib
LIBMWSL_FILEIO = $(MATLAB_ROOT)\extern\lib\win64\microsoft\libmwsl_fileio.lib
LIBS     = $(LIBS) $(LIBUT) $(LIBMWMATHUTIL) $(LIBMWSL_FILEIO) $(LIBMWIPP)

CMD_FILE = $(MODEL).lnk
GEN_LNK_SCRIPT = $(MATLAB_ROOT)\rtw\c\tools\mkvc_lnk.pl

#--------------------------------- Rules ---------------------------------------
all: set_environment_variables ..\$(MODEL)_acc.$(MEXEXT)

..\$(MODEL)_acc.$(MEXEXT) : $(OBJS) $(SHARED_LIB) $(LIBS)
	@echo ### Linking ...
	$(PERL) $(GEN_LNK_SCRIPT) $(CMD_FILE) $(OBJS)
	$(MEX) $(MEX_FLAGS) @$(CMD_FILE) $(S_FUNCTIONS_LIB) $(SHARED_LIB) $(LIBS) -outdir $(RELATIVE_PATH_TO_ANCHOR)
	@echo ### Created mex file: $(MODEL)_acc.$(MEXEXT)

# Look in simulink/src helper files

{$(MATLAB_ROOT)\simulink\src}.c.obj :
	@echo ### Compiling $<
	$(CC) $(MEX_FLAGS) $<

# Additional sources

{$(MATLAB_ROOT)\rtw\c\src}.c.obj :
	@echo ### Compiling $<
	$(CC) $(MEX_FLAGS) $<

{$(MATLAB_ROOT)\simulink\src}.c.obj :
	@echo ### Compiling $<
	$(CC) $(MEX_FLAGS) $<



{$(MATLAB_ROOT)\rtw\c\src}.cpp.obj : 
	@echo ### Compiling $< 
	$(CC) $(MEX_FLAGS) $< 

{$(MATLAB_ROOT)\simulink\src}.cpp.obj : 
	@echo ### Compiling $< 
	$(CC) $(MEX_FLAGS) $< 

 

# Put these rules last, otherwise nmake will check toolboxes first

{$(RELATIVE_PATH_TO_ANCHOR)}.c.obj :
	@echo ### Compiling $<
	$(CC) $(MEX_FLAGS) $(USER_INCLUDES) $<

{$(RELATIVE_PATH_TO_ANCHOR)}.cpp.obj :
	@echo ### Compiling $<
	$(CC) $(MEX_FLAGS) $(USER_INCLUDES) $<

.c.obj :
	@echo ### Compiling $<
	@if exist $*.pdb del $*.pdb
	@if exist ..\$(MODEL)_acc.pdb del ..\$(MODEL)_acc.pdb
	$(CC) $(MEX_FLAGS) $(USER_INCLUDES) $<

.cpp.obj :
	@echo ### Compiling $<
	@if exist $*.pdb del $*.pdb
	@if exist ..\$(MODEL)_acc.pdb del ..\$(MODEL)_acc.pdb
	$(CC) $(MEX_FLAGS) $(USER_INCLUDES) $<

!if "$(SHARED_LIB)" != ""
$(SHARED_LIB) : $(SHARED_SRC)
	@echo ### Creating $@
	@$(CC) $(MEX_FLAGS) -outdir $(SHARED_BIN_DIR)\ @<<
$?
<<
	@$(LIBCMD) /nologo /out:$@ $(SHARED_OBJS)
	@echo ### Created $@
!endif

set_environment_variables:
	@set INCLUDE=$(INCLUDE)
	@set LIB=$(LIB)
	@set MATLAB=$(MATLAB_ROOT)

# Libraries:





#----------------------------- Dependencies -----------------------------------

$(OBJS) : $(MAKEFILE) rtw_proj.tmw
