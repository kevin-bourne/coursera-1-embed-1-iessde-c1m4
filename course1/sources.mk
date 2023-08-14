#******************************************************************************
# Copyright (C) 2017 by Alex Fosdick - University of Colorado
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are
# permitted to modify this and use it to learn about the field of embedded
# software. Alex Fosdick and the University of Colorado are not liable for any
# misuse of this material.
#
#*****************************************************************************
#
# @file sources.mk
# @brief Define the sources for c1m4
# @author Kevin Bourne
# @date 14.08.2023
#
#*****************************************************************************

ifdef COURSE1_FLAG
  COURSE1_SOURCES = src/course1.c
else
  COURSE1_SOURCES =
endif

COMMON_SOURCES = \
	src/main.c \
	src/memory.c \
	$(COURSE1_SOURCES)

ifeq ($(PLATFORM),MSP432)
  SOURCES = \
		$(COMMON_SOURCES) \
		src/interrupts_msp432p401r_gcc.c \
		srcstartup_msp432p401r_gcc.c \
		system_msp432p401r.c

  INCLUDES = \
		-Iinclude/common \
		-Iinclude/msp432 \
		-Iinclude/CMSIS
else
  SOURCES = $(COMMON_SOURCES)
  INCLUDES = -Iinclude/common
endif
