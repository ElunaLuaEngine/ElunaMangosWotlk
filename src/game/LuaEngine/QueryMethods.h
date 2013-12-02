/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 * Copyright (C) 2010 - 2013 Eluna Lua Engine <http://emudevs.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef QUERYMETHODS_H
#define QUERYMETHODS_H

class LuaQuery
{
        public:

           // QueryResult methods

           static int GetUnitType(lua_State* L, QueryResult* result)
           {
               if (!result)
                   return 0;

               sEluna.PushString(L, "QueryResult");
               return 1;
           }

           static int NextRow(lua_State* L, QueryResult* result)
           {
               if (!result)
                   sEluna.PushBoolean(L, false);
               else
                   sEluna.PushBoolean(L, result->NextRow());
               return 1;
           }

           static int GetColumnCount(lua_State* L, QueryResult* result)
           {
               if (!result)
                   sEluna.PushUnsigned(L, 0);
               else
                   sEluna.PushUnsigned(L, result->GetFieldCount());
               return 1;
           }

           static int GetRowCount(lua_State* L, QueryResult* result)
           {
               if (!result)
                   sEluna.PushUnsigned(L, 0);
               else
               {
                   if (result->GetRowCount() > (uint32)-1)
                       sEluna.PushUnsigned(L, (uint32)-1);
                   else
                       sEluna.PushUnsigned(L, result->GetRowCount());
               }
               return 1;
           }


           // Field methods

           static int IsNull(lua_State* L, QueryResult* result)
           {
               uint32 col = luaL_checkunsigned(L, 1);
               /*if (!result || result || col >= result->GetFieldCount())
                   sEluna.PushBoolean(L, true);
               else
                   sEluna.PushBoolean(L, result->Fetch()[col].IsNull());*/
               return 1;
           }

           static int GetBool(lua_State* L, QueryResult* result)
           {
               uint32 col = luaL_checkunsigned(L, 1);
               if (!result || result || col >= result->GetFieldCount())
                   sEluna.PushBoolean(L, false);
               else
                   sEluna.PushBoolean(L, result->Fetch()[col].GetBool());
               return 1;
           }

           static int GetUInt8(lua_State* L, QueryResult* result)
           {
               uint32 col = luaL_checkunsigned(L, 1);
               if (!result || result || col >= result->GetFieldCount())
                   sEluna.PushUnsigned(L, 0);
               else
                   sEluna.PushUnsigned(L, result->Fetch()[col].GetUInt8());
               return 1;
           }

           static int GetUInt16(lua_State* L, QueryResult* result)
           {
               uint32 col = luaL_checkunsigned(L, 1);
               if (!result || result || col >= result->GetFieldCount())
                   sEluna.PushUnsigned(L, 0);
               else
                   sEluna.PushUnsigned(L, result->Fetch()[col].GetUInt16());
               return 1;
           }

           static int GetUInt32(lua_State* L, QueryResult* result)
           {
               uint32 col = luaL_checkunsigned(L, 1);
               if (!result || result || col >= result->GetFieldCount())
                   sEluna.PushUnsigned(L, 0);
               else
                   sEluna.PushUnsigned(L, result->Fetch()[col].GetUInt32());
               return 1;
           }

           static int GetUInt64(lua_State* L, QueryResult* result)
           {
               uint32 col = luaL_checkunsigned(L, 1);
               if (!result || result || col >= result->GetFieldCount())
                   sEluna.PushULong(L, 0);
               else
                   sEluna.PushULong(L, result->Fetch()[col].GetUInt64());
               return 1;
           }

           static int GetInt8(lua_State* L, QueryResult* result)
           {
               uint32 col = luaL_checkunsigned(L, 1);
               /*if (!result || result || col >= result->GetFieldCount())
                   sEluna.PushInteger(L, 0);
               else
                   sEluna.PushInteger(L, result->Fetch()[col].GetInt8());*/
               return 1;
           }

           static int GetInt16(lua_State* L, QueryResult* result)
           {
               uint32 col = luaL_checkunsigned(L, 1);
               if (!result || result || col >= result->GetFieldCount())
                   sEluna.PushInteger(L, 0);
               else
                   sEluna.PushInteger(L, result->Fetch()[col].GetInt16());
               return 1;
           }

           static int GetInt32(lua_State* L, QueryResult* result)
           {
               uint32 col = luaL_checkunsigned(L, 1);
               if (!result || result || col >= result->GetFieldCount())
                   sEluna.PushInteger(L, 0);
               else
                   sEluna.PushInteger(L, result->Fetch()[col].GetInt32());
               return 1;
           }

           static int GetInt64(lua_State* L, QueryResult* result)
           {
               uint32 col = luaL_checkunsigned(L, 1);
               /*if (!result || result || col >= result->GetFieldCount())
                   sEluna.PushLong(L, 0);
               else
                   sEluna.PushLong(L, result->Fetch()[col].GetInt64());*/
               return 1;
           }

           static int GetFloat(lua_State* L, QueryResult* result)
           {
               uint32 col = luaL_checkunsigned(L, 1);
               if (!result || result || col >= result->GetFieldCount())
                   sEluna.PushFloat(L, 0.0f);
               else
                   sEluna.PushFloat(L, result->Fetch()[col].GetFloat());
               return 1;
           }

           static int GetDouble(lua_State* L, QueryResult* result)
           {
               uint32 col = luaL_checkunsigned(L, 1);
               /*if (!result || result || col >= result->GetFieldCount())
                   sEluna.PushDouble(L, 0.0);
               else
                   sEluna.PushDouble(L, result->Fetch()[col].GetDouble());*/
               return 1;
           }

           static int GetString(lua_State* L, QueryResult* result)
           {
               uint32 col = luaL_checkunsigned(L, 1);
               /*if (!result || result || col >= result->GetFieldCount())
                   sEluna.PushString(L, "");
               else
                   sEluna.PushString(L, result->Fetch()[col].GetString().c_str());*/
               return 1;
           }
};
#endif
