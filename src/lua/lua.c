/*
   This file is part of darktable,
   copyright (c) 2012 Jeremy Rosen

   darktable is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   darktable is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with darktable.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "lua/lua.h"

#if 0
printf("%s %d\n",__FUNCTION__,__LINE__);
for(int i=1 ;i<=lua_gettop(L);i++) {printf("\t%d:%s %s\n",i,lua_typename(L,lua_type(L,i)),luaL_tolstring(L,i,NULL));lua_pop(L,1);}
static void debug_table(lua_State * L,int t) {
  /* table is in the stack at index 't' */
  lua_pushnil(L);  /* first key */
  while (lua_next(L, t-1) != 0) {
    /* uses 'key' (at index -2) and 'value' (at index -1) */
    printf("%s - %s\n",
        luaL_checkstring(L,-2),
        lua_typename(L, lua_type(L, -1)));
    /* removes 'value'; keeps 'key' for next iteration */
    lua_pop(L, 1);
  }
}
#endif


int dt_lua_push_darktable_lib(lua_State* L) {
  lua_getfield(L,LUA_REGISTRYINDEX,"dt_lua_dtlib");
  if(lua_isnil(L,-1)) {
    lua_pop(L,1);
    lua_newtable(L);
    lua_pushvalue(L,-1);
    lua_setfield(L,LUA_REGISTRYINDEX,"dt_lua_dtlib");
  }
  return 1;
}


void dt_lua_goto_subtable(lua_State *L,const char* sub_name) {
  luaL_checktype(L,-1,LUA_TTABLE);
  lua_getfield(L,-1,sub_name);
  if(lua_isnil(L,-1)) {
    lua_pop(L,1);
    lua_newtable(L);
    lua_setfield(L,-2,sub_name);
    lua_getfield(L,-1,sub_name);
  }
  lua_remove(L,-2);
}

// modelines: These editor modelines have been set for all relevant files by tools/update_modelines.sh
// vim: shiftwidth=2 expandtab tabstop=2 cindent
// kate: tab-indents: off; indent-width 2; replace-tabs on; indent-mode cstyle; remove-trailing-space on;
