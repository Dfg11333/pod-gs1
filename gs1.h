#include <stdint.h>

enum GS1ArenaMsgEP {
	GS1ArenaMsgEP_Router = 0x01,
	GS1ArenaMsgEP_Server = 0x02,
	GS1ArenaMsgEP_Client = 0x04,
	GS1ArenaMsgEP_Mask =
		GS1ArenaMsgEP_Router |
		GS1ArenaMsgEP_Server |
		GS1ArenaMsgEP_Client
};

enum GS1ArenaMsgID {
	GS1ArenaMsgID_Connect                 = 0x00,
	GS1ArenaMsgID_NewUserRequest          = 0x01,
	GS1ArenaMsgID_ConnectionRequest       = 0x04,
	GS1ArenaMsgID_PlayerNew               = 0x06,
	GS1ArenaMsgID_Disconnection           = 0x0A,
	GS1ArenaMsgID_PlayerRemoved           = 0x0B,
	GS1ArenaMsgID_GetLastNews             = 0x0C,
	GS1ArenaMsgID_News                    = 0x0D,
	GS1ArenaMsgID_SearchPlayer            = 0x0E,
	GS1ArenaMsgID_RemoveAccount           = 0x0F,
	GS1ArenaMsgID_GetServers              = 0x11,
	GS1ArenaMsgID_ServerList              = 0x12,
	GS1ArenaMsgID_GetSessions             = 0x13,
	GS1ArenaMsgID_SessionList             = 0x14,
	GS1ArenaMsgID_GetPlayers              = 0x15,
	GS1ArenaMsgID_PlayerList              = 0x16,
	GS1ArenaMsgID_GetSessionInfo          = 0x17,
	GS1ArenaMsgID_SessionInfo             = 0x18,
	GS1ArenaMsgID_GetPlayerInfo           = 0x19,
	GS1ArenaMsgID_PlayerInfo              = 0x1A,
	GS1ArenaMsgID_ChatAll                 = 0x1B,
	GS1ArenaMsgID_ChatList                = 0x1C,
	GS1ArenaMsgID_ChatSession             = 0x1D,
	GS1ArenaMsgID_ChatPlayer              = 0x1E,
	GS1ArenaMsgID_Chat                    = 0x1F,
	GS1ArenaMsgID_GeneralChat             = 0x20,
	GS1ArenaMsgID_CreateSession           = 0x21,
	GS1ArenaMsgID_SessionNew              = 0x24,
	GS1ArenaMsgID_JoinSession             = 0x25,
	GS1ArenaMsgID_LoadLevel               = 0x26,
	GS1ArenaMsgID_JoinNew                 = 0x28,
	GS1ArenaMsgID_LeaveSession            = 0x29,
	GS1ArenaMsgID_JoinLeave               = 0x2A,
	GS1ArenaMsgID_SessionRemoved          = 0x2B,
	GS1ArenaMsgID_InvitePlayers           = 0x2C,
	GS1ArenaMsgID_Success                 = 0x2F,
	GS1ArenaMsgID_Fail                    = 0x30,
	GS1ArenaMsgID_BeginGame               = 0x31,
	GS1ArenaMsgID_GameBegun               = 0x32,
	GS1ArenaMsgID_GameFinish              = 0x33,
	GS1ArenaMsgID_SessionResults          = 0x34,
	GS1ArenaMsgID_ModifyUserRequest       = 0x35,
	GS1ArenaMsgID_UpdatePlayerInfo        = 0x36,
	GS1ArenaMsgID_ExcludePlayer           = 0x38,
	GS1ArenaMsgID_ModifySession           = 0x39,
	GS1ArenaMsgID_Connect_Shareware       = 0x3A,
	GS1ArenaMsgID_StillAlive_Shareware    = 0x3B,
	GS1ArenaMsgID_UpdateAllSession        = 0x3C,
	GS1ArenaMsgID_UrgentMessage           = 0x3D,
	GS1ArenaMsgID_ChangeModule            = 0x3E,
	GS1ArenaMsgID_NewWaitModule           = 0x3F,
	GS1ArenaMsgID_KillModule              = 0x40,
	GS1ArenaMsgID_PlayerId                = 0x41,
	GS1ArenaMsgID_StillAlive              = 0x43,
	GS1ArenaMsgID_ConnectPlayer           = 0x44,
	GS1ArenaMsgID_AddPlayer               = 0x45,
	GS1ArenaMsgID_NetLibConnectionResult1 = 0x46,
	GS1ArenaMsgID_NetLibConnectionResult0 = 0x47,
	GS1ArenaMsgID_GetPort                 = 0x48,
	GS1ArenaMsgID_CheckPassword           = 0x4A,
	GS1ArenaMsgID_DeleteUserRequest       = 0x4B,
	GS1ArenaMsgID_GetRouters              = 0x4C,
	GS1ArenaMsgID_ServiceMessage          = 0x4D,
	GS1ArenaMsgID_RouterList              = 0x4E,
	GS1ArenaMsgID_SessionModify           = 0x4F,
	GS1ArenaMsgID_PingValue               = 0x64
};

static char * ArenaMsgTxt[] = {
"Connect", "NewUserRequest", "", "",
"ConnectionRequest", "", "PlayerNew", "",
"", "", "Disconnection", "PlayerRemoved",
"GetLastNews", "News", "SearchPlayer", "RemoveAccount", /*0x0F */
"", "GetServers", "ServerList", "GetSessions",
"SessionList", "GetPlayers", "PlayerList", "GetSessionInfo",
"SessionInfo", "GetPlayerInfo", "PlayerInfo", "ChatAll",
"ChatList", "ChatSession", "ChatPlayer", "Chat", /* 0x1f */
"GeneralChat", "CreateSession", "", "",
"SessionNew", "JoinSession", "LoadLevel", "",
"JoinNew", "LeaveSession", "JoinLeave", "SessionRemoved",
"InvitePlayers", "", "", "Success", /* 0x2f */
"Fail", "BeginGame", "GameBegun", "GameFinish",
"SessionResults", "ModifyUserRequest", "UpdatePlayerInfo", "",
"ExcludePlayer", "ModifySession", "Connect_Shareware", "StillAlive_Shareware",
"UpdateAllSession", "UrgentMessage", "ChangeModule", "NewWaitModule", /* 0x3f */
"KillModule", "PlayerId", "", "StillAlive",
"ConnectPlayer", "AddPlayer", "NetLibConnectionResult1", "NetLibConnectionResult0",
"GetPort", "", "CheckPassword", "DeleteUserRequest",
"GetRouters", "ServiceMessage", "RouterList", "SessionModify", /* 0x4f */
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", /* 0x5f */
"", "", "", "", "PingValue" /* 0x64 */
};

//NOTE: Only for documentation purposes (bitfields aren't portable).
struct GS1ArenaPacket {
	uint16_t Size;          // network byte order
	uint8_t  Source   : 3;  // enum GS1ArenaMsgEP
	uint8_t  Target   : 3;  // enum GS1ArenaMsgEP
	uint8_t  Reserved : 1;  // ignored (always 0)
	uint8_t  IsGameMsg: 1;  // has to be 0 (else struct GS1GamePacket)
	uint8_t  MsgID;         // enum GS1ArenaMsgID
};

enum GS1GameMsgID {
	GS1GameMsgID_SendToAllPlayers_0 = 0x02,
	GS1GameMsgID_SendToOnePlayer    = 0x03,
	GS1GameMsgID_SendToPlayers      = 0x04,  // unused
	GS1GameMsgID_DestroyGroup       = 0x0A,  // unused
	GS1GameMsgID_AddPlayerToGroup   = 0x0B,  // unused
	GS1GameMsgID_RmPlayerFromGroup  = 0x0C,  // unused
	GS1GameMsgID_GetPlayersId       = 0x0F,  // unused
	GS1GameMsgID_QuitSession        = 0x10,
	GS1GameMsgID_SendToAllPlayers_1 = 0x11,
	GS1GameMsgID_SendToGroup_0      = 0x13,  // unused
	GS1GameMsgID_SendToGroup_1      = 0x14,  // unused
	GS1GameMsgID_CreateGroup        = 0x15   // unused
};

//NOTE: Only for documentation purposes (bitfields aren't portable).
struct GS1GamePacket {
	uint16_t Size;          // network byte order
	uint8_t  MsgID    : 7;  // enum GS1GameMsgID
	uint8_t  IsGameMsg: 1;  // has to be 1 (else struct GS1ArenaPacket)
	uint8_t  unknown_0: 7;
	uint8_t  unknown_1: 1;
	union Info {
		uint8_t ID;         // PlayerID or GroupID
		// Sending game messages with Lists are broken
		// due to a bug in the Message_MakeGamePacket!
		struct List {
			uint8_t Count;
		//	uint8_t IDs[Count];
		}       List;
	}        Info;
};

extern int gs1_server_clients;
extern int gs1_server_sessions;

typedef enum {
	gs1_data_elemtype_string = 0,
	gs1_data_elemtype_list = 1
}gs1_data_elemtype_t;

typedef struct gs1_data_elem{
	gs1_data_elemtype_t type;
	char* string;
	struct gs1_data_elem *sub;
	int nsub;
}gs1_data_elem_t;

int gs1_data_size(gs1_data_elem_t *list);
void gs1_data_encode(gs1_data_elem_t *list, char* data);

void gs1_PrepareNews(struct GS1ArenaPacket *reply, int *data_size_ptr, char **data_ptr);
void gs1_PrepareSuccessPassword(struct GS1ArenaPacket *reply, int *data_size_ptr, char **data_ptr);
void gs1_PrepareStillAlive(struct GS1ArenaPacket *reply, int *data_size_ptr, char **data_ptr);
void gs1_PrepareServerList(struct GS1ArenaPacket *reply, int *data_size_ptr, char **data_ptr);
void gs1_PrepareSuccessSconnect(struct GS1ArenaPacket *reply, int *data_size_ptr, char **data_ptr);

