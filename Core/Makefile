
#===========

EXT = platform.o texture-atlas.o texture-font.o vector.o
GRAPHICS = sprite.o static_sprite.o shader.o window.o batchRenderer2D.o layer.o tilelayer.o group.o texture.o label.o font_manager.o font.o
BUFFERS = buffer.o indexbuffer.o vertexarray.o
MATHS = mat4.o vec2.o vec3.o vec4.o

#============

OBJS = main.o $(EXT) $(GRAPHICS) $(BUFFERS) $(MATHS)
CC=g++
CFLAGS=-c -Wall -Wno-c++11-extensions -Wno-pragma-once-outside-header
LFLAGS= -lglfw3 -lglew -lfreeimage -lfreetype -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
EXECUTABLE=game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXECUTABLE)

app: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXECUTABLE).app

#===========

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

#===========
# EXT - freetype-gl
#===========
platform.o: ext/freetype-gl/platform.c
	gcc -c -I/usr/local/include/freetype2/ -L/usr/local/include/freetype2/ ext/freetype-gl/platform.c

texture-atlas.o: ext/freetype-gl/texture-atlas.c
	gcc -c -I/usr/local/include/freetype2/ -L/usr/local/include/freetype2/ ext/freetype-gl/texture-atlas.c

texture-font.o: ext/freetype-gl/texture-font.c
	gcc -c -I/usr/local/include/freetype2/ -L/usr/local/include/freetype2/ ext/freetype-gl/texture-font.c

vector.o: ext/freetype-gl/vector.c
	gcc -c -I/usr/local/include/freetype2/ -L/usr/local/include/freetype2/ ext/freetype-gl/vector.c


#===========
# graphics
#===========

font.o: src/graphics/font.cpp
	$(CC) $(CFLAGS) src/graphics/font.cpp

label.o: src/graphics/label.cpp
	$(CC) $(CFLAGS) src/graphics/label.cpp

font_manager.o: src/graphics/font_manager.cpp
	$(CC) $(CFLAGS) src/graphics/font_manager.cpp

texture.o: src/graphics/texture.cpp
	$(CC) $(CFLAGS) src/graphics/texture.cpp

group.o: src/graphics/layers/group.cpp
	$(CC) $(CFLAGS) src/graphics/layers/group.cpp

layer.o: src/graphics/layers/layer.cpp
	$(CC) $(CFLAGS) src/graphics/layers/layer.cpp

tilelayer.o: src/graphics/layers/tilelayer.cpp
	$(CC) $(CFLAGS) src/graphics/layers/tilelayer.cpp

sprite.o: src/graphics/sprite.cpp
	$(CC) $(CFLAGS) src/graphics/sprite.cpp

static_sprite.o: src/graphics/static_sprite.cpp
	$(CC) $(CFLAGS) src/graphics/static_sprite.cpp

batchRenderer2D.o: src/graphics/batchRenderer2D.cpp
	$(CC) $(CFLAGS) src/graphics/batchRenderer2D.cpp

shader.o: src/graphics/shader.cpp src/utils/fileUtils.hpp
	$(CC) $(CFLAGS) src/graphics/shader.cpp

window.o: src/graphics/window.cpp
	$(CC) $(CFLAGS) src/graphics/window.cpp

#===========
# buffers
#===========

buffer.o: src/graphics/buffers/buffer.cpp
	$(CC) $(CFLAGS) src/graphics/buffers/buffer.cpp

indexbuffer.o: src/graphics/buffers/indexbuffer.cpp
	$(CC) $(CFLAGS) src/graphics/buffers/indexbuffer.cpp

vertexarray.o: src/graphics/buffers/vertexarray.cpp
	$(CC) $(CFLAGS) src/graphics/buffers/vertexarray.cpp

#===========
#   maths
#===========

mat4.o: src/maths/mat4.cpp
	$(CC) $(CFLAGS) src/maths/mat4.cpp

vec2.o: src/maths/vec2.cpp
	$(CC) $(CFLAGS) src/maths/vec2.cpp

vec3.o: src/maths/vec3.cpp
	$(CC) $(CFLAGS) src/maths/vec3.cpp

vec4.o: src/maths/vec4.cpp
	$(CC) $(CFLAGS) src/maths/vec4.cpp

#===========

clean:
	rm  *o $(EXECUTABLE)
