#ifndef FILE_FORMAT_H
  #define FILE_FORMAT_H

#include "../MurderEngine.hpp"
#include "../kernel/io/file_reader.hpp"
#include "../scene/scene_content.hpp"
#include "../audio/audio.hpp"
#include <vector>

#define FLAG_COMPRESSION_NONE                       0x0000000000000001
#define FLAG_COMPRESSION_LZW                        0x0000000000000002
#define FLAG_COMPRESSION_PACK_BITS                  0x0000000000000004
#define FLAG_COMPRESSION_DEFLATE                    0x0000000000000008
#define FLAG_COMPRESSION_DWAA                       0x0000000000000010
#define FLAG_COMPRESSION_PXR24                      0x0000000000000020
#define FLAG_COMPRESSION_B44A                       0x0000000000000040
#define FLAG_COMPRESSION_B44                        0x0000000000000080
#define FLAG_COMPRESSION_CCITT3                     0x0000000000000100
#define FLAG_COMPRESSION_CCITT4                     0x0000000000000200
#define FLAG_COMPRESSION_CCITT6                     0x0000000000000400

#define FLAG_METADATA_ALL                           0x0000000000000800
#define FLAG_METADATA_FILE                          0x0000000000001000
#define FLAG_METADATA_NAME                          0x0000008000000000
#define FLAG_METADATA_DESC                          0x0000000000002000
#define FLAG_METADATA_ARTIST                        0x0000000000004000
#define FLAG_METADATA_DATE                          0x0000000000008000
#define FLAG_METADATA_TIME                          0x0000000000010000
#define FLAG_METADATA_SOFTWARE                      0x0000000000020000
#define FLAG_METADATA_HOST_NAME                     0x0000000000040000
#define FLAG_METADATA_CAMERA                        0x0000000000080000
#define FLAG_METADATA_COMMENT                       0x0000200000000000
#define FLAG_METADATA_SUBJECT                       0x0004000000000000
#define FLAG_METADATA_SOUND                         0x0200000000000000
#define FLAG_METADATA_MEMORY                        0x0000000000200000
#define FLAG_METADATA_FRAME                         0x0000000000400000
#define FLAG_METADATA_FRAME_RATE                    0x0000000000800000
#define FLAG_METADATA_FRAME_RANGE                   0x0000000001000000
#define FLAG_METADATA_MARKER                        0x0000000002000000
#define FLAG_METADATA_SCENE                         0x0000000004000000
#define FLAG_METADATA_STRIP_NAME                    0x0000000008000000
#define FLAG_METADATA_USE_STRIP                     0x0000000010000000
#define FLAG_METADATA_COPYRIGHT                     0x0000004000000000

  #define FLAG_OVERWRITE                              0x0000000020000000
  #define FLAG_FILE_EXT                               0x0000000040000000

#define FLAG_IMAGE_BW                               0x0000000080000000
#define FLAG_IMAGE_RGB                              0x0000000100000000
#define FLAG_IMAGE_RGBA                             0x0000000200000000
#define FLAG_IMAGE_DEPTH8                           0x0000000400000000
#define FLAG_IMAGE_DEPTH16                          0x0000000800000000
#define FLAG_IMAGE_DEPTH24                          0x0000001000000000
#define FLAG_IMAGE_DEPTH32                          0x0000002000000000


#define FLAG_METADATA_SCENE2                         0x0010000000000000
#define FLAG_METADATA_SUBJECT_LOCATION                            0x0400000000000000
#define FLAG_METADATA_F_NUMBER                            0x0020000000000000
#define FLAG_METADATA_ISO_SPEED_RATINGS                            0x0040000000000000
#define FLAG_METADATA_SUBJECT_AREA                            0x0080000000000000
#define FLAG_METADATA_COLOR_SPACE                            0x0100000000000000
#define FLAG_METADATA_METERING_MODE                            0x0008000000000000
#define FLAG_METADATA_APERTURE                            0x0000400000000000
#define FLAG_METADATA_BRIGHTNESS                            0x0000800000000000
#define FLAG_METADATA_EXPOSURE_BIAS                            0x0001000000000000
#define FLAG_METADATA_MAX_APERTURE                            0x0002000000000000
#define FLAG_METADATA_                            0x0800000000000000
#define FLAG_METADATA_SHUTTER_SPEED                            0x1000000000000000
#define FLAG_METADATA_SHUTTER_SPEED                            0x2000000000000000
#define FLAG_METADATA_SHUTTER_SPEED                            0x4000000000000000
#define FLAG_METADATA_SHUTTER_SPEED                            0x8000000000000000
#define FLAG_METADATA_LENS                          0x0000000000100000
#define FLAG_METADATA_EXPOSURE_INFO                 0x0000010000000000
#define FLAG_METADATA_FOCAL_LENGTH                  0x0000020000000000
#define FLAG_METADATA_SHUTTER_SPEED                 0x0000040000000000
#define FLAG_METADATA_EXPOSURE_PROGRAM                            0x0000080000000000
#define FLAG_METADATA_FLASH                            0x0000100000000000

namespace me {

  namespace format {

    enum FileType {
      FTYPE_INSTANCE = 0,
      FTYPE_IMAGE = 1,
      FTYPE_SCENE = 2,
      FTYPE_AUDIO = 3,
      FTYPE_ARCHIVE = 4
    };

    enum ImageFileFormat {
      IFF_PNG,
      IFF_JPEG,
      IFF_GIF,
      IFF_TIFF,
      IFF_TARGA,
      IFF_BMP,
      IFF_EXR,
      IFF_HDR,
      IFF_ICO,
      IFF_FFMPEG,
      IFF_RAW
    };

    enum AudioFileFormat {
      AFF_FLAC,
      AFF_ALAC,
      AFF_WAVE,
      AFF_MP3,
      AFF_OGG,
      AFF_RAW
    };

    enum SceneFileFormat {
      SFF_COLLADA,
      SFF_WAVEFRONT,
      SFF_STANFORD,
      SFF_STL,
      SFF_FBX,
      SFF_USD
    };

    enum ArchiveFileFormat {
      AFF_ZIP
    };

};

#endif
