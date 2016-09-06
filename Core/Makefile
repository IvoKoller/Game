
BINDIR = bin
#===========
FTGL = platform.o texture-atlas.o texture-font.o vector.o
GA_1 =  ga_stream.o ga.o gau.o
GA_2 = ga_openal.o
GA_3 = gc_common.o gc_thread.o
GA = $(GA_1) $(GA_2) $(GA_3)

EXT = $(FTGL) $(GA)

AUDIO = sound.o
GRAPHICS = sprite.o static_sprite.o shader.o window.o batchRenderer2D.o texture.o \
animation.o tile.o label.o font.o camera.o
LAYERS =  layer.o defaultlayer.o staticlayer.o group.o
MANAGERS = font_manager.o sound_manager.o animation_manager.o
BUFFERS = buffer.o indexbuffer.o vertexarray.o
MATHS = mat4.o vec2.o vec3.o vec4.o
UTILS = filepath.o debug.o

#============

OBJS =  main.o $(EXT) $(GRAPHICS) $(BUFFERS) $(MATHS) $(LAYERS) $(UTILS) $(AUDIO) $(MANAGERS)
CC = g++
CFLAGS =-c -Wall -Wno-c++11-extensions -Wno-pragma-once-outside-header
LFLAGS = -lglfw3 -lglew -lfreeimage -lfreetype -logg -lvorbis -lvorbisfile -framework OpenAL -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
EXECUTABLE = game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXECUTABLE)

app: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXECUTABLE).app

#==================================
#==========EXT Libraries===========
#==================================
$(FTGL): %.o: ext/freetype-gl/%.c
	gcc -c -I/usr/local/include/freetype2/ $^

$(GA_1): %.o: ext/gorilla-audio/%.c
	gcc -c $^

$(GA_2): %.o: ext/gorilla-audio/devices/%.c
	gcc -c $^

$(GA_3): %.o: ext/gorilla-audio/common/%.c
	gcc -c $^
#==================================
#==================================
#==================================

main.o: main.cpp
	$(CC) $(CFLAGS) $^

$(AUDIO): %.o: src/audio/%.cpp
	$(CC) $(CFLAGS) $^


$(GRAPHICS): %.o: src/graphics/%.cpp
	$(CC) $(CFLAGS) $^

$(LAYERS): %.o: src/graphics/layers/%.cpp
	$(CC) $(CFLAGS) $^

$(MANAGERS): %.o: src/managers/%.cpp
	$(CC) $(CFLAGS) $^

$(BUFFERS): %.o: src/graphics/buffers/%.cpp
	$(CC) $(CFLAGS) $^

$(MATHS): %.o: src/maths/%.cpp
	$(CC) $(CFLAGS) $^

$(UTILS): %.o: src/utils/%.cpp
	$(CC) $(CFLAGS) $^

clean:
	rm main.o $(GRAPHICS) $(BUFFERS) $(LAYERS) $(UTILS) $(AUDIO) $(MANAGERS)

allclean:
	rm *o $(EXECUTABLE)
