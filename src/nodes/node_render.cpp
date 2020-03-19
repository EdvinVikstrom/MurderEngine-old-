#include "node.h"
#include "node_render.h"
#include "../renderer/render_helper.h"

double node_render_get_sock_x(node_socket* socket, node* _node)
{
  return (socket->dir==NODE_SOCKET_OUT?_node->scaleX:0) + _node->posX + socket->offX;
}

double node_render_get_sock_y(node_socket* socket, node* _node)
{
  return _node->posY + NODE_PANEL_HEIGHT + 16 + socket->offY;
}

void node_render_update_socket_pos(node* _node)
{
  for (int i = 0; i < _node->info.sockets.size(); i++)
  {
    node_socket* socket = _node->info.sockets.at(i);
    socket->posX = node_render_get_sock_x(socket, _node);
    socket->posY = node_render_get_sock_y(socket, _node);
  }
}

void node_render_sockets(node* _node)
{
  for (int i = 0; i < _node->info.sockets.size(); i++)
  {
    node_socket* socket = _node->info.sockets.at(i);
    render_lozenge(socket->data_type, socket->posX, socket->posY, NODE_SOCKET_SIZE, NODE_SOCKET_SIZE, true);
    render_lozenge(0xFF000000, socket->posX, socket->posY, NODE_SOCKET_SIZE, NODE_SOCKET_SIZE, false);
    for (node_socket* connection : socket->connections)
    {
      node_render_socket_wire(socket->posX+(NODE_SOCKET_SIZE/2), socket->posY+(NODE_SOCKET_SIZE/2), connection->posX+(NODE_SOCKET_SIZE/2), connection->posY+(NODE_SOCKET_SIZE/2));
    }
  }
}

const double CURVE_AMOUNT = 0.5D;
mVec2d* BEZIER_CURVE = new mVec2d[4]{{0, 0},{0, 0},{0, 0},{0, 0}};
void node_render_socket_wire(double fromX, double fromY, double toX, double toY)
{
  double width = toX-fromX;
  BEZIER_CURVE[0].x = fromX;
  BEZIER_CURVE[0].y = fromY;
  double v = toX > fromX ? (width * CURVE_AMOUNT) : (width * CURVE_AMOUNT * -1);
  BEZIER_CURVE[1].x = fromX + v;
  BEZIER_CURVE[1].y = fromY;
  BEZIER_CURVE[2].x = toX - v;
  BEZIER_CURVE[2].y = toY;
  BEZIER_CURVE[3].x = toX;
  BEZIER_CURVE[3].y = toY;
  render_start();
  render_enable_smooth_line();
  render_line_width(NODE_SOCKET_WIRE_WIDTH);
  render_color(0xFFFFFFFF);
  render_bezier(BEZIER_CURVE, 0.025D, true, 0x0003, 0, 4);
  render_line_width(1);
  render_disable_smooth_line();
  render_end();
}
