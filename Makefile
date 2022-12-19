COMPILER = g++
GLAD = glad/src/glad.c
CFLAGS = -O3 -Wall -fPIC -g -w
INCLUDE = -Iinclude/
CLIBS = -lGL -lGLU -lglfw -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl -lXinerama -lXcursor
ILIBS = -Iglad/include/
SOURCE = source/*.cpp
DEST = export/pc/


all: ${SOURCE}
	${COMPILER} ${GLAD} ${ILIBS} ${INCLUDE} ${SOURCE} ${CFLAGS} ${CLIBS} -o ${DEST}main; 