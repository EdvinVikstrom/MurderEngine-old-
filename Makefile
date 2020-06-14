NAME = MurderEngine
SRC = ./src/Main.cpp ./src/engine/MurderEngine.cpp ./src/engine/EngineInit.cpp ./src/engine/audio/audio_system.cpp ./src/engine/kernel/string.cpp ./src/engine/kernel/io/filebuff.cpp ./src/engine/kernel/io/bytebuff.cpp ./src/engine/loader/shader_loader.cpp ./src/engine/loader/formats/image_format.cpp ./src/engine/loader/formats/scene_format.cpp ./src/engine/loader/formats/bmp/bmp_format.cpp ./src/engine/math/maths.cpp ./src/engine/math/vector_utils.cpp ./src/engine/math/vector/vector2.cpp ./src/engine/math/vector/vector3.cpp ./src/engine/math/vector/vector4.cpp ./src/engine/renderer/opengl/opengl_api.cpp ./src/engine/script/script_manager.cpp ./src/engine/utilities/TimeUtils.cpp 
OBJ = ./MakeItFiles/src/Main.o ./MakeItFiles/src/engine/MurderEngine.o ./MakeItFiles/src/engine/EngineInit.o ./MakeItFiles/src/engine/audio/audio_system.o ./MakeItFiles/src/engine/kernel/string.o ./MakeItFiles/src/engine/kernel/io/filebuff.o ./MakeItFiles/src/engine/kernel/io/bytebuff.o ./MakeItFiles/src/engine/loader/shader_loader.o ./MakeItFiles/src/engine/loader/formats/image_format.o ./MakeItFiles/src/engine/loader/formats/scene_format.o ./MakeItFiles/src/engine/loader/formats/bmp/bmp_format.o ./MakeItFiles/src/engine/math/maths.o ./MakeItFiles/src/engine/math/vector_utils.o ./MakeItFiles/src/engine/math/vector/vector2.o ./MakeItFiles/src/engine/math/vector/vector3.o ./MakeItFiles/src/engine/math/vector/vector4.o ./MakeItFiles/src/engine/renderer/opengl/opengl_api.o ./MakeItFiles/src/engine/script/script_manager.o ./MakeItFiles/src/engine/utilities/TimeUtils.o 

CC = g++
CFLAGS = -Wall -std=c++17
OUTD = MakeItFiles
LIBD = -L./external/vulkan/x86_64/lib -L./src/external/libpng/libpng.so -L./src/external/portaudio 
INCD = 
LIBS = -lglfw -lGLEW -lGL -lGLU -lvulkan -lportaudio 

$(OUTD)/%.o: %.cpp $(SRC)
	$(CC) -c -o $@ $< $(INCD) $(CFLAGS)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LIBD) $(LIBS) $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OUTD)/*.o
