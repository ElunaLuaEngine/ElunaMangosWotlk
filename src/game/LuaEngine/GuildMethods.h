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

#ifndef GUILDMETHODS_H
#define GUILDMETHODS_H

class LuaGuild
{
    public:

        static int GetMembers(lua_State* L, Guild* guild) // TODO: Implementation
        {
            if (!guild)
                return 0;

            lua_newtable(L);
            int tbl = lua_gettop(L);
            uint32 i = 0;

            SessionMap const& sessions = sWorld.GetAllSessions();
            for (SessionMap::const_iterator it = sessions.begin(); it != sessions.end(); ++it)
            {
                if (Player* player = it->second->GetPlayer())
                {
                    if (player->GetSession() && (player->GetGuildId() == guild->GetId()))
                    {
                        ++i;
                        sEluna.PushUnsigned(L, i);
                        sEluna.PushUnit(L, player);
                        lua_settable(L, tbl);
                    }
                }
            }

            lua_settop(L, tbl); // push table to top of stack
            return 1;
        }

        static int GetMemberCount(lua_State* L, Guild* guild) // TODO: Implementation
        {
            if (!guild)
                return 0;
            
            sEluna.PushULong(L, guild->GetMemberSize());
            return 1;
        }

        static int GetObjectType(lua_State* L, Guild* guild)
        {
            if (!guild)
                return 0;

            sEluna.PushString(L, "Guild");
            return 1;
        }

        static int GetLeader(lua_State* L, Guild* guild)
        {
            if (!guild)
                return 0;

            sEluna.PushUnit(L, sObjectMgr.GetPlayer(guild->GetLeaderGuid()));
            return 1;
        }

        static int SetLeader(lua_State* L, Guild* guild)
        {
            if (!guild)
                return 0;

            Player* player = sEluna.CHECK_PLAYER(L, 1);
            if (!player)
                return 0;

            guild->SetLeader(player->GetObjectGuid());
            return 0;
        }

        static int GetLeaderGUID(lua_State* L, Guild* guild)
        {
            if (!guild)
                return 0;

            sEluna.PushULong(L, guild->GetLeaderGuid());
            return 1;
        }

        // SendPacketToGuild(packet)
        static int SendPacket(lua_State* L, Guild* guild)
        {
            if (!guild)
                return 0;

            WorldPacket* data = sEluna.CHECK_PACKET(L, 1);

            if (data)
                guild->BroadcastPacket(data);
            return 0;
        }

        // SendPacketToRankedInGuild(packet, rankId)
        static int SendPacketToRanked(lua_State* L, Guild* guild)
        {
            if (!guild)
                return 0;

            WorldPacket* data = sEluna.CHECK_PACKET(L, 1);
            uint8 ranked = luaL_checkunsigned(L, 2);

            if (data)
                guild->BroadcastPacketToRank(data, ranked);
            return 0;
        }

        static int Disband(lua_State* L, Guild* guild)
        {
            if (!guild)
                return 0;

            guild->Disband();
            return 0;
        }

        static int GetId(lua_State* L, Guild* guild)
        {
            if (!guild)
                return 0;

            sEluna.PushUnsigned(L, guild->GetId());
            return 1;
        }

        static int GetName(lua_State* L, Guild* guild)
        {
            if (!guild)
                return 0;

            sEluna.PushString(L, guild->GetName().c_str());
            return 1;
        }

        static int GetMOTD(lua_State* L, Guild* guild)
        {
            if (!guild)
                return 0;

            sEluna.PushString(L, guild->GetMOTD().c_str());
            return 1;
        }

        static int GetInfo(lua_State* L, Guild* guild)
        {
            if (!guild)
                return 0;

            sEluna.PushString(L, guild->GetGINFO().c_str());
            return 1;
        }

        static int AddMember(lua_State* L, Guild* guild)
        {
            if (!guild)
                return 0;

            Player* player = sEluna.CHECK_PLAYER(L, 1);
            uint8 rankId = luaL_optint(L, 2, GUILD_RANK_NONE);

            if (player)
                guild->AddMember(player->GetObjectGuid(), rankId);
            return 0;
        }

        static int DeleteMember(lua_State* L, Guild* guild)
        {
            if (!guild)
                return 0;

            Player* player = sEluna.CHECK_PLAYER(L, 1);
            bool isDisbanding = luaL_optbool(L, 2, false);
            // bool isKicked = luaL_optbool(L, 3, false); Not supported in MaNGOS

            if (player)
                guild->DelMember(player->GetObjectGuid(), isDisbanding);
            return 0;
        }

        static int ChangeMemberRank(lua_State* L, Guild* guild)
        {
            if (!guild)
                return 0;

            Player* player = sEluna.CHECK_PLAYER(L, 1);
            uint8 newRank = luaL_checkunsigned(L, 2);

            if (player)
                guild->ChangeMemberRank(player->GetObjectGuid(), newRank); // TODO: Implementation
            return 0;
        }

        static int SetBankTabText(lua_State* L, Guild* guild)
        {
            if (!guild)
                return 0;

            uint8 tabId = luaL_checkunsigned(L, 1);
            const char* text = luaL_checkstring(L, 2);
            guild->SetGuildBankTabText(tabId, text);
            return 0;
        }

        static int GetBankMoney(lua_State* L, Guild* guild)
        {
            if (!guild)
                return 0;

            sEluna.PushULong(L, guild->GetGuildBankMoney());
            return 1;
        }

        static int WithdrawBankMoney(lua_State* L, Guild* guild)
        {
            Player* player = sEluna.CHECK_PLAYER(L, 1);
            uint32 money = luaL_checknumber(L, 2);

            if (!guild || !player || (guild->GetGuildBankMoney()-money) < 0)
                return 0;

            player->SetMoney(player->GetMoney()+money);
            guild->SetBankMoney(guild->GetGuildBankMoney()-money);
            return 0;
        }

        static int DepositBankMoney(lua_State* L, Guild* guild)
        {
            Player* player = sEluna.CHECK_PLAYER(L, 1);
            uint32 money = luaL_checknumber(L, 2);

            if (!guild || !player || (player->GetMoney()-money) < 0)
                return 0;

            player->SetMoney(player->GetMoney()-money);
            guild->SetBankMoney(guild->GetGuildBankMoney()+money);
            return 0;
        }
};
#endif
