#include "lua_lang.hpp"

extern "C" {
  
#include "../../../../external/lua/src/lua.h"
#include "../../../../external/lua/src/luaxlib.h"
#include "../../../../external/lua/src/lualib.h"
  
};

int me::lang::lua::load_lua_script(const std::string &filepath)
{
  lua_State* L = luaL_newstate();
  int r = luaL_dostring(L, source);
  if (r != LUA_OK)
  {
    std::cout << "[LUA] [ERR]: " << lua_tostring(L, -1) << "\n";
    return ME_ERR;
  }
  // lua_getglobal(L, "a");
  // lua_isnumber(L, -1);
  // float number = (float) lua_tonumber(L, -1);
  lua_close(L);
  return ME_FINE;
}
