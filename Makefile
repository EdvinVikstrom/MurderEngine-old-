NAME = MurderEngine
SRC = ./src/Main.cpp ./src/engine/MurderEngine.cpp ./src/engine/EngineInit.cpp ./src/engine/algorithm/deflate/deflate_algorithm.cpp ./src/engine/algorithm/lzw/lzw_algorithm.cpp ./src/engine/audio/audio_system.cpp ./src/engine/kernel/string.cpp ./src/engine/kernel/io/file_reader.cpp ./src/engine/kernel/io/bytebuff.cpp ./src/engine/loader/file_format.cpp ./src/engine/loader/scene_format.cpp ./src/engine/loader/formats/bmp/bmp_format.cpp ./src/engine/loader/formats/collada/collada_format.cpp ./src/engine/loader/formats/ffmpeg/ffmpeg_format.cpp ./src/engine/loader/formats/flac/flac_format.cpp ./src/engine/loader/formats/gif/gif_format.cpp ./src/engine/loader/formats/glsl/glsl_format.cpp ./src/engine/loader/formats/ico/ico_format.cpp ./src/engine/loader/formats/jpeg/jpeg_format.cpp ./src/engine/loader/formats/png/png_format.cpp ./src/engine/loader/formats/targa/targa_format.cpp ./src/engine/loader/formats/tiff/tiff_format.cpp ./src/engine/loader/formats/wave/wave_format.cpp ./src/engine/loader/formats/zip/zip_format.cpp ./src/engine/math/maths.cpp ./src/engine/math/vector_utils.cpp ./src/engine/math/vector2.cpp ./src/engine/math/vector3.cpp ./src/engine/math/vector4.cpp ./src/engine/renderer/vulkan/vulkan_api.cpp ./src/engine/renderer/opengl/opengl_api.cpp ./src/engine/scene/scene.cpp ./src/engine/scene/scenes/scene_2d_viewport.cpp ./src/engine/utilities/TimeUtils.cpp 
OBJ = ./MakeItFiles/src/Main.o ./MakeItFiles/src/engine/MurderEngine.o ./MakeItFiles/src/engine/EngineInit.o ./MakeItFiles/src/engine/algorithm/deflate/deflate_algorithm.o ./MakeItFiles/src/engine/algorithm/lzw/lzw_algorithm.o ./MakeItFiles/src/engine/audio/audio_system.o ./MakeItFiles/src/engine/kernel/string.o ./MakeItFiles/src/engine/kernel/io/file_reader.o ./MakeItFiles/src/engine/kernel/io/bytebuff.o ./MakeItFiles/src/engine/loader/file_format.o ./MakeItFiles/src/engine/loader/scene_format.o ./MakeItFiles/src/engine/loader/formats/bmp/bmp_format.o ./MakeItFiles/src/engine/loader/formats/collada/collada_format.o ./MakeItFiles/src/engine/loader/formats/ffmpeg/ffmpeg_format.o ./MakeItFiles/src/engine/loader/formats/flac/flac_format.o ./MakeItFiles/src/engine/loader/formats/gif/gif_format.o ./MakeItFiles/src/engine/loader/formats/glsl/glsl_format.o ./MakeItFiles/src/engine/loader/formats/ico/ico_format.o ./MakeItFiles/src/engine/loader/formats/jpeg/jpeg_format.o ./MakeItFiles/src/engine/loader/formats/png/png_format.o ./MakeItFiles/src/engine/loader/formats/targa/targa_format.o ./MakeItFiles/src/engine/loader/formats/tiff/tiff_format.o ./MakeItFiles/src/engine/loader/formats/wave/wave_format.o ./MakeItFiles/src/engine/loader/formats/zip/zip_format.o ./MakeItFiles/src/engine/math/maths.o ./MakeItFiles/src/engine/math/vector_utils.o ./MakeItFiles/src/engine/math/vector2.o ./MakeItFiles/src/engine/math/vector3.o ./MakeItFiles/src/engine/math/vector4.o ./MakeItFiles/src/engine/renderer/vulkan/vulkan_api.o ./MakeItFiles/src/engine/renderer/opengl/opengl_api.o ./MakeItFiles/src/engine/scene/scene.o ./MakeItFiles/src/engine/scene/scenes/scene_2d_viewport.o ./MakeItFiles/src/engine/utilities/TimeUtils.o 

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
