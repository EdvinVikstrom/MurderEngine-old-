#ifndef MESH_LOADER_H
  #define MESH_LOADER_H

namespace me {

  namespace fformat {

    class mesh_reader : public file_format {

    public:

      mesh_reader() : file_format(me::fformat::format_type.MESH) { }

      virtual int read_mesh(const std::string &file_name, unsigned char* data, uint32_t data_size, me::mesh* mesh, std::vector<me::item*> &items) = 0;
      inline int read_file(const std::string &file_name, unsigned char* data, uint32_t data_size, std::vector<me::item*> &items) override
      {
        int result = read_mesh(file_name, data, data_size, mesh, items);
        if (result != ME_FINE)
          return result;
        return ME_FINE;
      }

      virtual bool recognized(const std::string &file_name, unsigned char* data, uint32_t data_size) = 0;
      virtual std::vector<std::string> get_file_exts() = 0;

    }

  };

  void loadMesh(me::mesh* mesh, int usage);
  void processMeshFaces(me::mesh* mesh, unsigned int* faces, unsigned int faceCount, int vertexOffset, int normalOffset, int texCoordOffset);
  std::vector<me::item*> loadMeshFromFile(const char* filepath, unsigned int& itemCount);

};

#endif
