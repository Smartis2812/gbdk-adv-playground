#
# Simple Makefile that compiles all .c and .s files in the same folder
#

# If you move this project you can change the directory 
# to match your GBDK root directory (ex: GBDK_HOME = "C:/GBDK/"
GBDK_HOME = $(GBDKDIR)

LCC = $(GBDK_HOME)bin/lcc 
PNG2ASSET = $(GBDK_HOME)bin/png2asset 

# You can uncomment the line below to turn on debug output
# LCC = $(LCC) -debug

# You can set the name of the .gb ROM file here
PROJECTNAME    = MUSICPLAYER

GENDIR = gen
RESDIR = res
SRCDIR = src
DSTDIR = build

BINS	    = $(PROJECTNAME).gb
CSOURCES   := $(wildcard $(SRCDIR)/*.c) $(wildcard $(GENDIR)/*.c)

all: clean prepare $(BINS)

prepare:
	mkdir -p $(GENDIR)
	mkdir -p $(DSTDIR)

compile.bat: Makefile
	@echo "REM Automatically generated from Makefile" > compile.bat
	@make -sn | sed y/\\//\\\\/ | grep -v make >> compile.bat

# Compile and link all source files in a single call to LCC
$(BINS):	$(CSOURCES)
	$(LCC) -I$(GENDIR) -o $(DSTDIR)/$@ $(CSOURCES)

clean:
	rm -f  $(DSTDIR)/*.*
	rm -f  $(GENDIR)/*.*
	rm -f *.o *.lst *.map *.gb *.ihx *.sym *.cdb *.adb *.asm

