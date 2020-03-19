#include <vector>

#define MATH_NODE_OPERATION_MULTIPLY               0x1
#define MATH_NODE_OPERATION_DIVIDE                 0x2
#define MATH_NODE_OPERATION_ADDITION               0x3
#define MATH_NODE_OPERATION_SUBTRACT               0x4
#define MATH_NODE_OPERATION_POWER                  0x5
#define MATH_NODE_OPERATION_SQUARE_ROOT            0x6

static void math_node_do_math(unsigned int operation, float a, float b, float& result)
{
  switch(operation)
  {
    case MATH_NODE_OPERATION_MULTIPLY: result = a * b; break;
    case MATH_NODE_OPERATION_DIVIDE: result = a / b; break;
    case MATH_NODE_OPERATION_ADDITION: result = a + b; break;
    case MATH_NODE_OPERATION_SUBTRACT: result = a - b; break;
    case MATH_NODE_OPERATION_POWER: result = a * b; break;
    case MATH_NODE_OPERATION_SQUARE_ROOT: result = a * b; break;
  }
}

static void math_node_on_update(node_info* info)
{
  node_socket* in1 = info->sockets.at(1);
  node_socket* in2 = info->sockets.at(2);
  unsigned int operation = MATH_NODE_OPERATION_MULTIPLY;
  unsigned int newValueLength = in1->valueLength > in2->valueLength ? in1->valueLength : in2->valueLength;
  float newValue[newValueLength];
  delete[] info->sockets.at(0)->value; // error
  info->sockets.at(0)->value = newValue;
  for (int i = 0; i < newValueLength; i++)
  {
    float a = in1->value[i%in1->valueLength];
    float b = in2->value[i%in2->valueLength];
    math_node_do_math(operation, a, b, newValue[i]);
  }
}

static node_info math_node_create_info()
{
  std::vector<node_socket*> sockets;
  node_socket* s_out1 = new node_socket(NODE_SOCKET_OUT, NODE_SOCKET_DATA_TYPE_FLOAT, new float[1]{0.0F}, 1, 0);
  node_socket* s_in1 = new node_socket(NODE_SOCKET_IN, NODE_SOCKET_DATA_TYPE_FLOAT, new float[1]{0.5F}, 1, 1);
  node_socket* s_in2 = new node_socket(NODE_SOCKET_IN, NODE_SOCKET_DATA_TYPE_FLOAT, new float[1]{0.5F}, 1, 2);
  sockets.push_back(s_out1);
  sockets.push_back(s_in1);
  sockets.push_back(s_in2);
  node_info info = {
    "Math",
    NODE_CATEGORY_CONVERTER,
    {145, 256},
    sockets,
    math_node_on_update
  };
  return info;
}
