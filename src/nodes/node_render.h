#ifndef NODE_RENDER_H
  #define NODE_RENDER_H

double node_render_get_sock_x(node_socket* socket, node* _node);
double node_render_get_sock_y(node_socket* socket, node* _node);
void node_render_update_socket_pos(node* _node);
void node_render_sockets(node* _node);
void node_render_socket_wire(double fromX, double fromY, double toX, double toY);

#endif
