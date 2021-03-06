#==========
#operating system
#==========
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
LFLAGS = -lglfw3 -lglew -lfreeimage -lfreetype -logg -lvorbis -lvorbisfile \
-framework OpenAL -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
endif
ifeq ($(UNAME), Linux)
LFLAGS = -lGL -lGLU -lGLEW -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor \
-lfreeimage -lfreetype -logg -lvorbis -lvorbisfile -lopenal
endif



#===========
BINDIR = bin
#===========
FTGL = platform.o texture-atlas.o texture-font.o vector.o
GA_1 =  ga_stream.o ga.o gau.o
GA_2 = ga_openal.o
GA_3 = gc_common.o gc_thread.o
GA = $(GA_1) $(GA_2) $(GA_3)

EXT = $(FTGL) $(GA)

AUDIO = sound.o
GRAPHICS = sprite.o static_sprite.o shader.o window.o BatchRenderer2D.o texture.o \
label.o font.o camera.o
GUI = button.o menuButton.o textfield.o countButton.o editor.o tileButton.o gridButton.o
LAYERS =  layer.o defaultlayer.o staticlayer.o group.o
MANAGERS = manager.o sound_manager.o animation_manager.o
BUFFERS = buffer.o indexbuffer.o vertexarray.o
MATHS = mat4.o vec2.o vec3.o vec4.o
PHYSICS = collider.o
UTILS = filepath.o debug.o

#============

OBJS = $(EXT) $(GRAPHICS) $(GUI) $(BUFFERS) $(MATHS) $(PHYSICS) $(LAYERS) $(UTILS) $(AUDIO) $(MANAGERS)
CC = g++
CFLAGS =-std=gnu++11 -c -Wall -Wno-c++11-extensions -Wno-pragma-once-outside-header
EXECUTABLE = game

game: $(EXECUTABLE)

$(EXECUTABLE): gameMain.o $(OBJS)
	$(CC) gameMain.o $(OBJS) -o $(EXECUTABLE) $(LFLAGS)

test: testMain.o $(OBJS)
	$(CC) testMain.o $(OBJS) -o test $(LFLAGS)

editor: editorMain.o $(OBJS)
	$(CC) editorMain.o $(OBJS) -o editor $(LFLAGS)

app: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXECUTABLE).app

#==================================
#==========EXT Libraries===========
#==================================

ifeq ($(UNAME), Linux)
$(FTGL): %.o: ext/freetype-gl/%.c
	gcc -c -I/usr/include/freetype2/ $^
endif
ifeq ($(UNAME), Darwin)
$(FTGL): %.o: ext/freetype-gl/%.c
	gcc -c -I/usr/local/include/freetype2/ $^
endif
$(GA_1): %.o: ext/gorilla-audio/%.c
	gcc -c $^

$(GA_2): %.o: ext/gorilla-audio/devices/%.c
	gcc -c $^

$(GA_3): %.o: ext/gorilla-audio/common/%.c
	gcc -c $^

#==================================
#==================================
#==================================

testMain.o: testMain.cpp
	$(CC) $(CFLAGS) $^

gameMain.o: gameMain.cpp
	$(CC) $(CFLAGS) $^

editorMain.o: editorMain.cpp
	$(CC) $(CFLAGS) $^

$(AUDIO): %.o: src/audio/%.cpp
	$(CC) $(CFLAGS) $^

$(GRAPHICS): %.o: src/graphics/%.cpp
	$(CC) $(CFLAGS) $^

$(GUI): %.o: src/graphics/gui/%.cpp
	$(CC) $(CFLAGS) $^

$(LAYERS): %.o: src/graphics/layers/%.cpp
	$(CC) $(CFLAGS) $^

$(MANAGERS): %.o: src/managers/%.cpp
	$(CC) $(CFLAGS) $^

$(BUFFERS): %.o: src/graphics/buffers/%.cpp
	$(CC) $(CFLAGS) $^

$(MATHS): %.o: src/maths/%.cpp
	$(CC) $(CFLAGS) $^

$(PHYSICS): %.o: src/physics/%.cpp
	$(CC) $(CFLAGS) $^

$(UTILS): %.o: src/utils/%.cpp
	$(CC) $(CFLAGS) $^

clean:
	rm editorMain.o gameMain.o $(GUI) $(GRAPHICS) $(BUFFERS) $(LAYERS) $(UTILS) $(AUDIO) $(MANAGERS)

allclean:
	rm *o $(EXECUTABLE)
