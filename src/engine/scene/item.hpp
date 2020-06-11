#ifndef ITEM_H
  #define ITEM_H

namespace me {

  enum ItemType {
    ITEM_NAN,
    ITEM_MESH,
    ITEM_LIGHT,
    ITEM_CAMERA,
    ITEM_CURVE,
  };

  struct Item {
    std::string identifier;
    me::ItemType type;
    me::maths::mat4 transform_matrix;

    void* ptr;

    Item(std::string identifier, me::ItemType type, me::maths::mat4 transform_matrix, void* ptr)
    {
      this->identifier = identifier;
      this->type = type;
      this->transform_matrix = transform_matrix;
      this->ptr = ptr;
    }

    Item() { }

    ~Item()
    {
    }

  };

};

#endif