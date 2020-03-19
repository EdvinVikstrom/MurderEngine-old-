#ifndef NODE_SOCKET_H
  #define NODE_SOCKET_H

struct node_socket {
  item* parent;
  unsigned int dir;
  unsigned int data_type;
  float* value;
  unsigned int valueLength;
  double offX, offY;
  double posX, posY;
  std::vector<node_socket*> connections;

  node_socket(unsigned int dir, unsigned int data_type, float* value, int valueLength, int index)
  {
    this->dir = dir;
    this->data_type = data_type;
    this->value = value;
    this->valueLength = valueLength;
    this->posX = 0;
    this->posY = 0;
    this->offX = -NODE_SOCKET_SIZE/2;
    this->offY = (NODE_SOCKET_SIZE+16)*index;
  }

  void setParent(item* parent)
  {
    this->parent = parent;
  }

};

#endif
