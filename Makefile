COMPILER = g++
GLAD = glad/src/glad.c
CFLAGS = -O3 -Wall -fPIC -g -w
INCLUDE = -Iinclude/
CLIBS = -lGL -lGLU -lglfw -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl -lXinerama -lXcursor
ILIBS = -I./glad/include/
SOURCE = source/*.cpp
EXSOURCE = source/**
DEST = export/pc/


all: ${EXSOURCE}
	${COMPILER} ${GLAD} ${ILIBS} ${INCLUDE} ${EXSOURCE} ${CFLAGS} ${CLIBS} -o ${DEST}main; 
