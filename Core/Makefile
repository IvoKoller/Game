
OBJDIR = obj
#===========

EXT = platform.o texture-atlas.o texture-font.o vector.o
GRAPHICS = sprite.o static_sprite.o shader.o window.o batchRenderer2D.o texture.o label.o font_manager.o font.o
LAYERS =  layer.o tilelayer.o group.o
BUFFERS = buffer.o indexbuffer.o vertexarray.o
MATHS = mat4.o vec2.o vec3.o vec4.o

#============

OBJS =  main.o $(EXT) $(GRAPHICS) $(BUFFERS) $(MATHS) $(LAYERS)
CC = g++
CFLAGS =-c -Wall -Wno-c++11-extensions -Wno-pragma-once-outside-header
LFLAGS = -lglfw3 -lglew -lfreeimage -lfreetype -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
EXECUTABLE = game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXECUTABLE)
	mv *.o $(OBJDIR)/

app: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXECUTABLE).app
	mv *.o $(OBJDIR)/

#==================================

main.o: main.cpp
	$(CC) $(CFLAGS) $^

$(EXT): %.o: ext/freetype-gl/%.c
	gcc -c -I/usr/local/include/freetype2/ -L/usr/local/include/freetype2/ $^

$(GRAPHICS): %.o: src/graphics/%.cpp
	$(CC) $(CFLAGS) $^

$(LAYERS): %.o: src/graphics/layers/%.cpp
	$(CC) $(CFLAGS) $^

$(BUFFERS): %.o: src/graphics/buffers/%.cpp
	$(CC) $(CFLAGS) $^

$(MATHS): %.o: src/maths/%.cpp
	$(CC) $(CFLAGS) $^

clean:
	rm  obj/*o
	rm $(EXECUTABLE)
