#pragma once
#include "stdafx.h"
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <thread>
#include <time.h>
#include <vector>
#include <experimental/filesystem>
#include "json.hpp"
#include "Server_core.h"
using namespace std;
//#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
using json = nlohmann::json;
int maxItems = 10388;
#define cloth0 cloth_hair
#define cloth1 cloth_shirt
#define cloth2 cloth_pants
#define cloth3 cloth_feet
#define cloth4 cloth_face
#define cloth5 cloth_hand
#define cloth6 cloth_back
#define cloth7 cloth_mask
#define cloth8 cloth_necklace
#define cloth9 cloth_ances
#define STRINT(x, y) (*(int*)(&(x)[(y)]))
#define STR16(x, y) (*(uint16_t*)(&(x)[(y)]))
vector<string> guildmem;
vector<string> guildelder;
vector<string> guildco;
#ifdef _WIN32
#include <windows.h>
typedef __int8 __int8_t;
typedef __int16 __int16_t;
#elif __APPLE__ || __linux__
typedef unsigned int DWORD;
#endif
typedef unsigned char BYTE;
struct InventoryItem {
	__int16_t itemID;
	__int16_t itemCount;
};
struct PlayerInventory {
	vector<InventoryItem> items;
};
struct PlayerInfo {
	int geigerx = 64;
	int geigery = 64;
	string lastnormalworld = "";
	/*notvend*/
	string NickPrefix = "";
	/*Fishing*/
	bool Fishing = false;
	bool TriggerFish = false;
	int FishPosX = 0;
	int timeBanned = 0;
	int FishPosY = 0;
	bool BrowsingCategory = false;
	string LastBait = "None";
	/*OnSuperMain*/
	string zf = "";
	/*ItemSuckers*/
	int magplantitemid = 0;
	int magplantx = 0;
	int magplanty = 0;
	string suckername = "";
	int suckerid = 0;
	/*PlayerLogin*/
	string email = "";
	bool HasLogged = false;
	bool isBot = true;
	/*Buffs*/
	bool GemBuffDrop = false;
	/*Consummables*/
	bool blueBerry = false;
	int usedBerry = 0;
	int lastBerry = 0;
	bool LuckyClover = false;
	int usedClover = 0;
	int lastClover = 0;
	bool SpikeJuice = false;
	int usedSpike = 0;
	int lastSpike = 0;
	bool PunchPotion = false;
	int usedPunchPotion = 0;
	int lastPunchPotion = 0;
	bool PlacePotion = false;
	int usedPlacePotion = 0;
	int lastPlacePotion = 0;
	/*PlayerName*/
	bool isDr = false;
	/*Misc*/
	bool passedname = false;
	bool passedheight = false;
	bool passedwidth = false;
	bool passedbackground = false;
	bool passedforeground = false;
	bool passedbedrock = false;
	string chatcolor = "";
	/**/
	bool isDisableMessages = false;
	/*HPSystem | PVP*/
	int lastPVPcoord = 0;
	int lastPVPcoord2 = 0;
	int lastPVPcoord3 = 0;
	int lastPVPcoord4 = 0;
	int lastPVPcoord5 = 0;
	long long int LastScanMSG;
	int lastPVPcoord6 = 0;
	int lastPVPcoord7 = 0;
	int health = 100;
	int score = 0;
	int noobCounter = 0;
	bool Growid = false;
	// end hp
	int wrenchedBlockLocation = -1;
	int displayfg = 0;
	int displaybg = 0;
	int displaypunchx = 0;
	int LastX = 0;
	bool UpdateFinisheds = true;
	int LastY = 0;
	int displaypunchy = 0;
	int lastsavemyworld = 0;
	int SubscribtionEndDay = 0;
	int lastdailyGems = 0;
	int packetinsec = 0;
	long long int packetsec = 0;
	int timeTogetToken = 0;
	int trashgemmeritem = 0;
	int eikiscia = 0;
	int bootybreaken = 0;
	bool startkit = false;
	bool UpdateFinished = true;
	string OriName = "";
	int wrenchx;
	int wrenchy;
	long long int lastSPIN = 0;
	int lastdroppeditemid = 0;
	int lastPunchX = -1;
	string lastvendbuycount = "";
	bool blockLogin = false;
	int lastPunchY = -1;
	int lastPunchForeground;
	int lastPunchBackground;
	bool isInWorld = false;
	bool GlobalChat = false;
	bool isBannedWait = false;
	bool usedCP = false;
	int TotalKills = 0;
	string skill = "None";
	string sid = "none";
	bool Console = false;
	bool isIn = false;
	string notebook = "";
	int netID;
	long long int startedTest = 0;
	string Chatname = "";
	bool Subscriber = false;
	int lastdropitemcount = 0;
	int lastdropitem = 0;
	int lasttrashitem = 0;
	int lasttrashitemcount = 0;
	long long int lastwarn = 0;
	int lastwarnCount = 0;
	int violations = 0;
	long long int lastcurse = 0;
	int lastcurseCount = 0;
	long long int lastban = 0;
	int lastbanCount = 0;
	long long int lastsuspend2w = 0;
	int lastsuspend2wCount = 0;
	long long int lastsuspend4w = 0;
	int lastsuspend4wCount = 0;
	long long int lastsuspend8w = 0;
	int lastsuspend8wCount = 0;
	long long int lastsuspendwrench = 0;
	int lastsuspendwrenchCount = 0;
	long long int lastbanipwrench = 0;
	int lastbanipwrenchCount = 0;
	long long int lastsuspend = 0;
	int lastsuspendCount = 0;
	int Awesomeness = 0;
	long long int lastdelete = 0;
	int lastdeleteCount = 0;
	long long int lastbanip = 0;
	int lastbanipCount = 0;
	long long int lastdelstatus = 0;
	int lastdelstatusCount = 0;
	int wrenchsession = 0;
	bool ZiuriIKaire = false;
	int bitShiftTest = 0;
	bool canLeave = true;
	bool haveGrowId = false;
	bool needsaveinventory = false;
	bool haveGuestId = false;
	int valgem;
	int plantgems = 0;
	int lavaLevel = 0;
	bool RotatedLeft = false;
	int fWater = 0;
	bool isRotatedLeft = false;
	string tankIDName = "";
	string tankIDPass = "";
	string requestedName = "";
	string rawName = "";
	int warns = 0;
	int bans = 0;
	string lastworld = "";
	bool transsuccess = false;
	bool isModState = false;
	string displayName = "";
	bool wrongpass = false;
	int guildBg = 0;
	int guildFg = 0;
	string guildStatement = "";
	string guildLeader = "";
	string displayNamebackup = "";
	string displayUsername = "";
	vector<string> guildmatelist;
	vector<string> guildMembers;
	vector<string> worldsowned;
	vector<string> lastworlds;
	int guildlevel = 0;
	int guildexp = 0;
	bool isinvited = false;
	string createGuildName = "";
	string createGuildStatement = "";
	string createGuildFlagBg = "";
	string createGuildFlagFg = "";
	string guild = "";
	bool joinguild = false;
	string lastgm = "";
	string lastgmname = "";
	string lastgmworld = "";
	string guildlast = "";
	string msgName = "";
	bool isNicked = false;
	string country = "";
	string gameversion = "";
	string rid = "none";
	string gid = "none";
	string aid = "none";
	bool canExit = true;
	string vid = "none";
	string wkid = "";
	string metaip = "";
	string hash2 = "";
	string hash = "";
	string fhash = "";
	string mac = "none";
	string token = "";
	string user = "";
	string deviceversion = "";
	string doorID = "";
	string cbits = "";
	string lmode = "";
	string gdpr = "";
	string f = "";
	string fz = "";
	string hpid = "";
	string platformID = "";
	string player_age = "1";
	int adminLevel = 0;
	string currentWorld = "EXIT";
	bool radio = true;
	int x;
	int y;
	int x1;
	int y1;
	int posXY;
	int posX;
	int posY;
	int cpY;
	int cpX;
	int SignPosX;
	int playerid;
	int SignPosY;
	bool characterLoaded = false;
	string charIP = "none";
	bool isDBanned = false;
	vector<string> friendinfo;
	vector<string> createfriendtable;
	vector<string> createworldsowned;
	string lastFrn = "";
	string lastFrnName = "";
	string lastFrnWorld = "";
	string lastMsger = "";
	string lastMsgerTrue = "";
	string lastMsgWorld = "";
	string lastSdbWorld = "";
	string lastSbbWorld = "";
	string lastfriend = "";
	string lastInfo = "";
	string lastInfoname = "";
	string lastDisplayname = "";
	string lastSeller = "";
	string lastBuyer = "";
	string lastInfoAboutPlayer = "none";
	long int lastTradeAmount = 99999999999;
	string addgems = "1000 gems";
	int characterState = 0;
	int level = 1;
	int xp = 0;
	bool isUpdating = false;
	bool joinClothesUpdated = false;
	int effect = 8421376;
	int peffect = 8421376;
	bool taped = false;
	bool canCreate = false;
	int cloth_hair = 0; // 0
	int cloth_shirt = 0; // 1
	int cloth_pants = 0; // 2
	int cloth_feet = 0; // 3
	int cloth_face = 0; // 4
	int cloth_hand = 0; // 5
	int cloth_back = 0; // 6
	int cloth_mask = 0; // 7
	int cloth_necklace = 0; // 8
	int cloth_ances = 0; // 9
	int cur = 0;
	int ipID = 0;
	int ban = 0;
	bool canWalkInBlocks = false; // 1
	bool canDoubleJump = false; // 2
	bool cantsay = false;
	bool isInvisible = false; // 4
	bool noHands = false; // 8
	bool noEyes = false; // 16
	bool noBody = false; // 32	
	bool devilHorns = false; // 64
	bool goldenHalo = false; // 128
	bool isFrozen = false; // 2048
	bool isCursed = false; // 4096
	bool isDuctaped = false; // 8192
	unsigned long long int lastMuted = 0;
	unsigned long long int lastCursed = 0;
	bool haveCigar = false; // 16384
	bool isShining = false; // 32768
	bool isAncients = false; // 32768
	bool isAncients1 = false; // 32768
	bool isAncients2 = false; // 32768
	bool isAncients3 = false; // 32768
	bool isAncients4 = false; // 32768
	bool isAncients5 = false; // 32768
	bool isAncients6 = false; // 32768
	bool isZombie = false; // 65536
	bool isHitByLava = false; // 131072
	bool haveHauntedShadows = false; // 262144
	bool haveGeigerRadiation = false; // 524288
	bool haveReflector = false; // 1048576
	bool isEgged = false; // 2097152
	bool havePineappleFloag = false; // 4194304
	bool haveFlyingPineapple = false; // 8388608
	bool haveSuperSupporterName = false; // 16777216
	bool haveSupperPineapple = false; // 33554432
	bool isGhost = false;
	bool isinv = false;
	int skinColor = 0x8295C3FF;
	PlayerInventory inventory;
	/*geiger*/ 
	long long int GeigerTime = 0;
	bool GeigerCooldown = false;
	/*surgery*/
	int Ultrasound = 0;
	bool PatientHeartStopped = false;
	long long int SurgeryTime = 0;
	bool SurgeryCooldown = false;
	float PatientTemperatureRise = 0;
	bool FixIt = false;
	bool UnlockedAntibiotic = false;
	bool PerformingSurgery = false;
	int SurgerySkill = 0;
	bool RequestedSurgery = false;
	string TempColor = "";
	bool HardToSee = false;
	bool PatientLosingBlood = false;
	int SurgItem1 = 4320;
	int SurgItem2 = 4320;
	int SurgItem3 = 4320;
	int SurgItem4 = 4320;
	int SurgItem5 = 4320;
	int SurgItem6 = 4320;
	int SurgItem7 = 4320;
	int SurgItem8 = 4320;
	int SurgItem9 = 4320;
	int SurgItem10 = 4320;
	int SurgItem11 = 4320;
	int SurgItem12 = 4320;
	int SurgItem13 = 4320;
	string PatientDiagnosis = "";
	string PatientPulse = "";
	string PatientStatus = "";
	float PatientTemperature = 0;
	string OperationSite = "";
	string IncisionsColor = "";
	int PatientIncisions = 0;
	string PatientRealDiagnosis = "";
	//trade stars
	long long int lastTrade = 0;
	string lastTradeGrowid = "";
	int firefighterlevel = 0;
	int firefighterxp = 0;
	int providerlevel = 0;
	int providerxp = 0;
	int fishermanlevel = 0;
	int fishermanxp = 0;
	int geigerlevel = 0;
	int geigerxp = 0;
	string MergeItem1 = "0";
	string MergeItem2 = "0";
	string MergeItem3 = "0";
	string mySellingItem1 = "3308";
	string mySellingItem2 = "3308";
	string mySellingItem3 = "3308";
	string mySellingItem4 = "3308";
	string mySellingItem1Count = "0";
	string mySellingItem2Count = "0";
	string mySellingItem3Count = "0";
	string mySellingItem4Count = "0";
	string hisSellingItem1 = "3308";
	string hisSellingItem2 = "3308";
	string hisSellingItem3 = "3308";
	string hisSellingItem4 = "3308";
	string hisSellingItem1Count = "0";
	string hisSellingItem2Count = "0";
	string hisSellingItem3Count = "0";
	string hisSellingItem4Count = "0";
	string receivedFrom = "";
	//trade ends
	short currentInventorySize = 0;
	long long int lastSB = 0;
	long long int lastSDB = 0;
	long long int lastSSB = 0;
	long long int lastINV = 0;
	long long int lastBREAK = 0;
	long long int lastMute = 0;
	long long int lastBan = 0;
	long long int lastCurse = 0;
	long long int lastATM = 0;
	long long int lastSYNC = 0;
	long long int lastDISPLAY = 0;
	int blockx;
	int blocky;
	bool isUseCode = false;
	bool isConfirmingCode = false;
	string registercode = "";
	string registermac = "";
	string registerrid = "";
	string registersid = "";
	string registergid = "";
	string registervid = "";
	string registeraid = "";
	string registerIP = "";
	int lastUserID = 0;
	int userID = 0;
	int respawnX = 0;
	int respawnY = 0;
	bool ischeck = false;
	int checkx = 0;
	int checky = 0;
	bool loadedInventory = false;
	long long int lastPunchTime = 0;
	long long int lastHitTime = 0;
	long long int lastJoinReq = 0;
	long long int lastsendclient = 0;
	long long int lastpacketflood = 0;
	long long int lastenterdoor = 0;
	uint32_t lavaHitAt = 0;
	uint32_t deadTime = 0;
};
struct PlayerMoving {
	int packetType;
	int netID;
	float x;
	float y;
	int characterState;
	int plantingTree;
	float XSpeed;
	float YSpeed;
	int punchX;
	int punchY;
	int secondnetID;
};
struct Admin {
	string username;
	string password;
	int level = 0;
	long long int lastSB = 0;
	long long int lastWarp = 0;
	long long int lastSpawn = 0;
	long long int lastasb = 0;
};
struct GamePacket {
	BYTE* data;
	int len;
	int indexes;
};
enum ClothTypes {
	HAIR,
	SHIRT,
	PANTS,
	FEET,
	FACE,
	HAND,
	BACK,
	MASK,
	NECKLACE,
	ANCES,
	NONE
};
inline int getState(PlayerInfo* info) {
	auto val = 0;
	val |= info->canWalkInBlocks << 0;
	val |= info->canDoubleJump << 1;
	val |= info->cantsay << 13;
	val |= info->noHands << 3;
	val |= info->noEyes << 4;
	val |= info->noBody << 5;
	val |= info->goldenHalo << 7;
	val |= info->isFrozen << 8;
	val |= info->isCursed << 12;
	val |= info->isDuctaped << 13;
	val |= info->haveSuperSupporterName << 24;
	val |= info->isShining << 15;
	val |= info->isZombie << 16;
	val |= info->isHitByLava << 17;
	val |= info->haveGeigerRadiation << 19;
	return val;
}
class Player {
public:
	static void OnConsoleMessage(ENetPeer* peer, string text);
	static void OnTalkBubble(ENetPeer* peer, int netID, string text, int chatColor, bool isOverlay);
	static void OnAddNotification(ENetPeer* peer, string text, string audiosound, string interfaceimage);
	static void OnRemove(ENetPeer* peer, int netID);
	static void OnSendToServer(ENetPeer* peer, int userID, int token, string ip, int port, string doorId, int lmode); // no need other args, sub servers done&working already... using fake data etc.
	static void PlayAudio(ENetPeer* peer, string audioFile, int delayMS);
	static void OnZoomCamera(ENetPeer* peer, float value1, int value2);
	static void SmoothZoom(ENetPeer* peer);
	static void OnRaceStart(ENetPeer* peer, int netID);
	static void OnRaceEnd(ENetPeer* peer, int netID);
	static void OnSetCurrentWeather(ENetPeer* peer, int weather);
	static void OnPlayPositioned(ENetPeer* peer, string audiofile, int netID, bool broadcastInWorld, ENetPacket* pk);
	static void OnCountdownStart(ENetPeer* peer, int netID, int time, int score);
	static void OnStartTrade(ENetPeer* peer, string displayName, int netID);
	static void OnTextOverlay(ENetPeer* peer, string text);
	static void OnForceTradeEnd(ENetPeer* peer);
	static void OnFailedToEnterWorld(ENetPeer* peer);
	static void OnNameChanged(ENetPeer* peer, int netID, string name);
	static void OnDialogRequest(ENetPeer* peer, string args);
	static void OnKilled(ENetPeer* peer, int netID);
	static void OnSetFreezeState(ENetPeer* peer, int state, int netID);
	static void OnSetPos(ENetPeer* peer, int netID, int x, int y);
	static void OnInvis(ENetPeer* peer, int state, int netID);
	static void OnChangeSkin(ENetPeer* peer, int skinColor, int netID);
	static void SetRespawnPos(ENetPeer* peer, int posX, int posY, int netID);
	static void OnSetBux(ENetPeer* peer, int gems, int accountstate);
	static void OnParticleEffect(ENetPeer* peer, int effect, float x, float y, int delay);
	static void SetHasGrowID(ENetPeer* peer, int status, string username, string password);
	static void Ping(ENetPeer* peer);
};
class PlayerDB {
public:
	static string getProperName(string name);
	static string fixColors(string text);
	static int playerLogin(ENetPeer* peer, string username, string password);
	static int playerRegister(ENetPeer* peer, string username, string password, string email);
	static int guildRegister(ENetPeer* peer, string guildName, string guildStatement, string guildFlagfg, string guildFlagbg);
};
inline string PlayerDB::getProperName(string name) {
	string newS;
	for (auto c : name) newS += (c >= 'A' && c <= 'Z') ? c - ('A' - 'a') : c;
	string ret;
	for (auto i = 0; i < newS.length(); i++) {
		if (newS[i] == '`') i++;
		else ret += newS[i];
	}
	string ret2;
	for (auto c : ret) if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) ret2 += c;
	return ret2;
}
inline string PlayerDB::fixColors(string text) {
	string ret = "";
	auto colorLevel = 0;
	for (auto i = 0; i < text.length(); i++)
	{
		if (text[i] == '`')
		{
			ret += text[i];
			if (i + 1 < text.length())
				ret += text[i + 1];
			if (i + 1 < text.length() && text[i + 1] == '`')
			{
				colorLevel--;
			}
			else
			{
				colorLevel++;
			}
			i++;
		}
		else
		{
			ret += text[i];
		}
	}
	for (auto i = 0; i < colorLevel; i++)
	{
		ret += "``";
	}
	for (auto i = 0; i > colorLevel; i--)
	{
		ret += "`w";
	}
	return ret;
}

inline GamePacket appendFloat(GamePacket p, float val)
{
	const auto n = new BYTE[p.len + 2 + 4];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	n[p.len] = p.indexes;
	n[p.len + 1] = 1;
	memcpy(n + p.len + 2, &val, 4);
	p.len = p.len + 2 + 4;
	p.indexes++;
	return p;
}

inline GamePacket appendFloat(GamePacket p, float val, float val2)
{
	const auto n = new BYTE[p.len + 2 + 8];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	n[p.len] = p.indexes;
	n[p.len + 1] = 3;
	memcpy(n + p.len + 2, &val, 4);
	memcpy(n + p.len + 6, &val2, 4);
	p.len = p.len + 2 + 8;
	p.indexes++;
	return p;
}

inline GamePacket appendFloat(GamePacket p, float val, float val2, float val3)
{
	const auto n = new BYTE[p.len + 2 + 12];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	n[p.len] = p.indexes;
	n[p.len + 1] = 4;
	memcpy(n + p.len + 2, &val, 4);
	memcpy(n + p.len + 6, &val2, 4);
	memcpy(n + p.len + 10, &val3, 4);
	p.len = p.len + 2 + 12;
	p.indexes++;
	return p;
}

inline GamePacket appendInt(GamePacket p, int val)
{
	const auto n = new BYTE[p.len + 2 + 4];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	n[p.len] = p.indexes;
	n[p.len + 1] = 9;
	memcpy(n + p.len + 2, &val, 4);
	p.len = p.len + 2 + 4;
	p.indexes++;
	return p;
}

inline GamePacket appendIntx(GamePacket p, int val)
{
	const auto n = new BYTE[p.len + 2 + 4];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	n[p.len] = p.indexes;
	n[p.len + 1] = 5;
	memcpy(n + p.len + 2, &val, 4);
	p.len = p.len + 2 + 4;
	p.indexes++;
	return p;
}

inline GamePacket appendString(GamePacket p, string str)
{
	const auto n = new BYTE[p.len + 2 + str.length() + 4];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	n[p.len] = p.indexes;
	n[p.len + 1] = 2;
	int sLen = str.length();
	memcpy(n + p.len + 2, &sLen, 4);
	memcpy(n + p.len + 6, str.c_str(), sLen);
	p.len = p.len + 2 + str.length() + 4;
	p.indexes++;
	return p;
}

inline GamePacket createPacket()
{
	const auto data = new BYTE[61];
	string asdf = "0400000001000000FFFFFFFF00000000080000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	for (auto i = 0; i < asdf.length(); i += 2)
	{
		char x = ch2n(asdf[i]);
		x = x << 4;
		x += ch2n(asdf[i + 1]);
		memcpy(data + (i / 2), &x, 1);
		if (asdf.length() > 61 * 2) throw 0;
	}
	GamePacket packet;
	packet.data = data;
	packet.len = 61;
	packet.indexes = 0;
	return packet;
}

inline GamePacket packetEnd(GamePacket p)
{
	const auto n = new BYTE[p.len + 1];
	memcpy(n, p.data, p.len);
	delete p.data;
	p.data = n;
	char zero = 0;
	memcpy(p.data + p.len, &zero, 1);
	p.len += 1;
	*reinterpret_cast<int*>(p.data + 56) = p.indexes;
	*static_cast<BYTE*>(p.data + 60) = p.indexes;
	return p;
}

inline BYTE* packPlayerMoving(PlayerMoving* dataStruct)
{
	const auto data = new BYTE[64];
	for (auto i = 0; i < 64; i++)
	{
		data[i] = 0;
	}
	memcpy(data, &dataStruct->packetType, 4);
	memcpy(data + 4, &dataStruct->netID, 4);
	memcpy(data + 12, &dataStruct->characterState, 4);
	memcpy(data + 20, &dataStruct->plantingTree, 4);
	memcpy(data + 24, &dataStruct->x, 4);
	memcpy(data + 28, &dataStruct->y, 4);
	memcpy(data + 32, &dataStruct->XSpeed, 4);
	memcpy(data + 36, &dataStruct->YSpeed, 4);
	memcpy(data + 44, &dataStruct->punchX, 4);
	memcpy(data + 48, &dataStruct->punchY, 4);
	return data;
}

string packPlayerMoving2(PlayerMoving* dataStruct)
{
	string data;
	data.resize(56);
	STRINT(data, 0) = dataStruct->packetType;
	STRINT(data, 4) = dataStruct->netID;
	STRINT(data, 12) = dataStruct->characterState;
	STRINT(data, 20) = dataStruct->plantingTree;
	STRINT(data, 24) = *(int*)&dataStruct->x;
	STRINT(data, 28) = *(int*)&dataStruct->y;
	STRINT(data, 32) = *(int*)&dataStruct->XSpeed;
	STRINT(data, 36) = *(int*)&dataStruct->YSpeed;
	STRINT(data, 44) = dataStruct->punchX;
	STRINT(data, 48) = dataStruct->punchY;
	return data;
}

inline PlayerMoving* unpackPlayerMoving(BYTE* data)
{
	auto dataStruct = new PlayerMoving;
	memcpy(&dataStruct->packetType, data, 4);
	memcpy(&dataStruct->netID, data + 4, 4);
	memcpy(&dataStruct->characterState, data + 12, 4);
	memcpy(&dataStruct->plantingTree, data + 20, 4);
	memcpy(&dataStruct->x, data + 24, 4);
	memcpy(&dataStruct->y, data + 28, 4);
	memcpy(&dataStruct->XSpeed, data + 32, 4);
	memcpy(&dataStruct->YSpeed, data + 36, 4);
	memcpy(&dataStruct->punchX, data + 44, 4);
	memcpy(&dataStruct->punchY, data + 48, 4);
	return dataStruct;
}

inline long long GetCurrentTimeInternal()
{
	using namespace std::chrono;
	return (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
}

inline long long GetCurrentTimeInternalSeconds()
{
	using namespace std::chrono;
	return (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
}

inline int calcBanDuration(const long long banDuration)
{
	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	auto duration = 0;
	duration = banDuration - GetCurrentTimeInternalSeconds();
	if (duration <= 0) return 0;
	else return duration;
}

inline string OutputBanTime(int n) {
	string x;
	const auto day = n / (24 * 3600);
	if (day != 0) x.append(to_string(day) + " Days ");
	n = n % (24 * 3600);
	const auto hour = n / 3600;
	if (hour != 0) x.append(to_string(hour) + " Hours ");
	n %= 3600;
	const auto minutes = n / 60;
	if (minutes != 0) x.append(to_string(minutes) + " Minutes ");
	n %= 60;
	const auto seconds = n;
	if (seconds != 0) x.append(to_string(seconds) + " Seconds");
	return x;
}

inline void banLoginDevice(ENetPeer* peer, const long long banDurationDefault, string sid, string mac)
{
	const auto bantimeleft = calcBanDuration(banDurationDefault);
	if (bantimeleft < 1) return;
	const auto text = "action|log\nmsg|`4Sorry, this device or location is still banned for `w" + OutputBanTime(calcBanDuration(banDurationDefault)) + " Need help? Contact Sebia#0001!";
	const string dc = "https://discord.gg/VCSQ8ZhprK";
	const auto url = "action|set_url\nurl|" + dc + "\nlabel|Join Towntopia Discord\n";
	const auto data = new BYTE[5 + text.length()];
	const auto dataurl = new BYTE[5 + url.length()];
	BYTE zero = 0;
	auto type = 3;
	memcpy(data, &type, 4);
	memcpy(data + 4, text.c_str(), text.length());
	memcpy(data + 4 + text.length(), &zero, 1);
	memcpy(dataurl, &type, 4);
	memcpy(dataurl + 4, url.c_str(), url.length());
	memcpy(dataurl + 4 + url.length(), &zero, 1);
	const auto p = enet_packet_create(data, 5 + text.length(), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, p);
	const auto p3 = enet_packet_create(dataurl, 5 + url.length(), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, p3);
	delete data;
	delete dataurl;
	static_cast<PlayerInfo*>(peer->data)->blockLogin = true;
}

inline void SendInventory(ENetPeer* peer, PlayerInventory inventory) {
	if (static_cast<PlayerInfo*>(peer->data)->currentWorld == "EXIT") return;
	const int inventoryLen = inventory.items.size();
	const auto packetLen = 66 + (inventoryLen * 4) + 4;
	auto* data2 = new BYTE[packetLen];
	auto MessageType = 0x4;
	auto PacketType = 0x9;
	auto NetID = -1;
	auto CharState = 0x8;
	memset(data2, 0, packetLen);
	memcpy(data2, &MessageType, 4);
	memcpy(data2 + 4, &PacketType, 4);
	memcpy(data2 + 8, &NetID, 4);
	memcpy(data2 + 16, &CharState, 4);
	int endianInvVal = __builtin_bswap32(inventoryLen);
	memcpy(data2 + 66 - 4, &endianInvVal, 4);
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId) endianInvVal = __builtin_bswap32(static_cast<PlayerInfo*>(peer->data)->currentInventorySize - 1);
	else endianInvVal = __builtin_bswap32(2);
	memcpy(data2 + 66 - 8, &endianInvVal, 4);
	int val = 0;
	for (int i = 0; i < inventoryLen; i++) {
		val = 0;
		val |= inventory.items.at(i).itemID;
		val |= inventory.items.at(i).itemCount << 16;
		val &= 0x00FFFFFF;
		val |= 0x00 << 24;
		memcpy(data2 + (i * 4) + 66, &val, 4);
	}
	const auto packet3 = enet_packet_create(data2, packetLen, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet3);
	delete data2;
}

inline bool CheckItemExists(ENetPeer* peer, const int fItemId)
{
	auto isExists = false;
	for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
	{
		if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemId)
		{
			isExists = true;
			break;
		}
	}
	return isExists;
}

inline void SearchInventoryItem(ENetPeer* peer, const int fItemid, const int fQuantity, bool& iscontains) {
	iscontains = false;
	for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++) {
		if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemid && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= fQuantity) {
			iscontains = true;
			break;
		}
	}
}

inline bool isHere(ENetPeer* peer, ENetPeer* peer2) {
	return static_cast<PlayerInfo*>(peer->data)->currentWorld == static_cast<PlayerInfo*>(peer2->data)->currentWorld;
}

inline void SendPacketRaw(int a1, void* packetData, const size_t packetDataSize, void* a4, ENetPeer* peer, const int packetFlag) {
	ENetPacket* p;
	if (peer) {
		if (a1 == 4 && *(static_cast<BYTE*>(packetData) + 12) & 8) {
			p = enet_packet_create(nullptr, packetDataSize + *(static_cast<DWORD*>(packetData) + 13) + 5, packetFlag);
			auto four = 4;
			memcpy(p->data, &four, 4);
			memcpy(reinterpret_cast<char*>(p->data) + 4, packetData, packetDataSize);
			memcpy(reinterpret_cast<char*>(p->data) + packetDataSize + 4, a4, *(static_cast<DWORD*>(packetData) + 13));
			enet_peer_send(peer, 0, p);
		} else {
			try {
				p = enet_packet_create(nullptr, packetDataSize + 5, packetFlag);
				memcpy(p->data, &a1, 4);
				memcpy(reinterpret_cast<char*>(p->data) + 4, packetData, packetDataSize);
				enet_peer_send(peer, 0, p);
			}
			catch (...) {
				SendConsole("Failed to send packet raw (sendpacketraw)", "ERROR");
			}
		}
	}
	delete static_cast<char*>(packetData);
}

inline void playerconfig(ENetPeer* peer, const int yspeed, const int xspeed, const int packettype) {
	const auto info = static_cast<PlayerInfo*>(peer->data);
	const auto netID = info->netID;
	const auto state = getState(info);
	for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			PlayerMoving data;
			auto water = 125.0f;
			data.packetType = packettype;
			data.characterState = static_cast<PlayerInfo*>(peer->data)->characterState;
			data.x = 1000;
			if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 366) {
				data.y = -400;
			} else {
				data.y = 400;
			}
			data.punchX = 0;
			data.punchY = 0;
			data.XSpeed = xspeed;
			data.YSpeed = yspeed;
			data.netID = netID;
			data.plantingTree = state;
			const auto raw = packPlayerMoving(&data);
			auto var = 0x818100;
			memcpy(raw + 1, &var, 3);
			memcpy(raw + 16, &water, 4);
			SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}

inline void sendPuncheffectpeer(ENetPeer* peer, const int punch) {
	const auto info = static_cast<PlayerInfo*>(peer->data);
	const auto netID = info->netID;
	const auto state = getState(info);
	PlayerMoving data;
	auto water = 125.0f;
	data.packetType = 0x14;
	data.characterState = static_cast<PlayerInfo*>(peer->data)->characterState;
	data.x = 1000;
	if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 366) {
		data.y = -400;
	} else {
		data.y = 400;
	}
	data.punchX = -1;
	data.punchY = -1;
	data.XSpeed = 300;
	if (static_cast<PlayerInfo*>(peer->data)->cloth_back == 9472) {
		data.YSpeed = 600;
	} else if (static_cast<PlayerInfo*>(peer->data)->cloth_back == 10418 || static_cast<PlayerInfo*>(peer->data)->cloth_back == 10420) {
		data.YSpeed = 250;
	} else {
		data.YSpeed = 1000;
	}
	data.netID = netID;
	data.plantingTree = state;
	const auto raw = packPlayerMoving(&data);
	auto var = punch;
	memcpy(raw + 1, &var, 3);
	memcpy(raw + 16, &water, 4);
	SendPacketRaw(4, raw, 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
	if (static_cast<PlayerInfo*>(peer->data)->isZombie == true) {
		playerconfig(peer, 1150, 130, 0x14);
	}
}

inline void sendPuncheffect(ENetPeer* peer, int punch) {
	const auto info = static_cast<PlayerInfo*>(peer->data);
	const auto netID = info->netID;
	const auto state = getState(info);
	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			if (peer != currentPeer) {
				PlayerMoving data;
				data.packetType = 0x14;
				data.characterState = static_cast<PlayerInfo*>(peer->data)->characterState;
				data.x = 1000;
				data.y = 100;
				data.x = 1000;
				data.y = 1000;
				data.punchX = 0;
				data.punchY = 0;
				data.XSpeed = 300;
				data.YSpeed = 600;
				data.netID = netID;
				data.plantingTree = state;
				const auto raw = packPlayerMoving(&data);
				auto var = punch;
				memcpy(raw + 1, &var, 3);
				SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
		}
	}
	if (static_cast<PlayerInfo*>(peer->data)->isZombie == true) {
		playerconfig(peer, 1150, 130, 0x14);
	}
}

inline void sendClothes(ENetPeer* peer) {
	if (static_cast<PlayerInfo*>(peer->data)->currentWorld == "EXIT") return;
	auto p3 = packetEnd(appendFloat(appendIntx(appendFloat(appendFloat(appendFloat(appendString(createPacket(), "OnSetClothing"), (static_cast<PlayerInfo*>(peer->data))->cloth_hair, (static_cast<PlayerInfo*>(peer->data))->cloth_shirt, (static_cast<PlayerInfo*>(peer->data))->cloth_pants), (static_cast<PlayerInfo*>(peer->data))->cloth_feet, (static_cast<PlayerInfo*>(peer->data))->cloth_face, (static_cast<PlayerInfo*>(peer->data))->cloth_hand), (static_cast<PlayerInfo*>(peer->data))->cloth_back, (static_cast<PlayerInfo*>(peer->data))->cloth_mask, (static_cast<PlayerInfo*>(peer->data))->cloth_necklace), (static_cast<PlayerInfo*>(peer->data))->skinColor), (static_cast<PlayerInfo*>(peer->data))->cloth_ances, 0.0f, 0.0f));
	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			memcpy(p3.data + 8, &((static_cast<PlayerInfo*>(peer->data))->netID), 4);
			const auto packet3 = enet_packet_create(p3.data, p3.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet3);
		}
	}
	delete p3.data;
}

inline void updateplayerset(ENetPeer* peer, int targetitem) {
	const auto clothitem = static_cast<PlayerInfo*>(peer->data)->cloth_hand;
	const auto clothface = static_cast<PlayerInfo*>(peer->data)->cloth_face;
	const auto clothneck = static_cast<PlayerInfo*>(peer->data)->cloth_necklace;
	const auto clothshirt = static_cast<PlayerInfo*>(peer->data)->cloth_shirt;
	const auto clothback = static_cast<PlayerInfo*>(peer->data)->cloth_back;
	const auto clothances = static_cast<PlayerInfo*>(peer->data)->cloth_ances;
	const auto clothpants = static_cast<PlayerInfo*>(peer->data)->cloth_pants;
	const auto clothfeet = static_cast<PlayerInfo*>(peer->data)->cloth_feet;
	const auto clothhair = static_cast<PlayerInfo*>(peer->data)->cloth_hair;
	const auto clothmask = static_cast<PlayerInfo*>(peer->data)->cloth_mask;
	const auto item = targetitem;
	if (clothmask == item)
	{
		auto iscontains = false;
		SearchInventoryItem(peer, item, 1, iscontains);
		if (!iscontains)
		{
			static_cast<PlayerInfo*>(peer->data)->cloth_mask = 0;
			sendClothes(peer);
		}
	}
	if (clothitem == item)
	{
		auto iscontains = false;
		SearchInventoryItem(peer, item, 1, iscontains);
		if (!iscontains)
		{
			static_cast<PlayerInfo*>(peer->data)->cloth_hand = 0;
			sendClothes(peer);
			static_cast<PlayerInfo*>(peer->data)->effect = 8421376;
			sendPuncheffectpeer(peer, static_cast<PlayerInfo*>(peer->data)->effect);
			sendPuncheffect(peer, static_cast<PlayerInfo*>(peer->data)->effect);
		}
	}
	if (clothface == item)
	{
		auto iscontains = false;
		SearchInventoryItem(peer, item, 1, iscontains);
		if (!iscontains)
		{
			static_cast<PlayerInfo*>(peer->data)->cloth_face = 0;
			sendClothes(peer);
		}
	}

	if (clothneck == item)
	{
		auto iscontains = false;
		SearchInventoryItem(peer, item, 1, iscontains);
		if (!iscontains)
		{
			static_cast<PlayerInfo*>(peer->data)->cloth_necklace = 0;
			sendClothes(peer);
		}
	}

	if (clothshirt == item)
	{
		auto iscontains = false;
		SearchInventoryItem(peer, item, 1, iscontains);
		if (!iscontains)
		{
			static_cast<PlayerInfo*>(peer->data)->cloth_shirt = 0;
			sendClothes(peer);
		}
	}

	if (clothback == item)
	{
		auto iscontains = false;
		SearchInventoryItem(peer, item, 1, iscontains);
		if (!iscontains)
		{
			static_cast<PlayerInfo*>(peer->data)->cloth_back = 0;
			sendClothes(peer);
		}
	}

	if (clothances == item)
	{
		auto iscontains = false;
		SearchInventoryItem(peer, item, 1, iscontains);
		if (!iscontains)
		{
			static_cast<PlayerInfo*>(peer->data)->cloth_ances = 0;
			sendClothes(peer);
		}
	}

	if (clothpants == item)
	{
		auto iscontains = false;
		SearchInventoryItem(peer, item, 1, iscontains);
		if (!iscontains)
		{
			static_cast<PlayerInfo*>(peer->data)->cloth_pants = 0;
			sendClothes(peer);
		}
	}

	if (clothfeet == item)
	{
		auto iscontains = false;
		SearchInventoryItem(peer, item, 1, iscontains);
		if (!iscontains)
		{
			static_cast<PlayerInfo*>(peer->data)->cloth_feet = 0;
			sendClothes(peer);
		}
	}

	if (clothhair == item)
	{
		auto iscontains = false;
		SearchInventoryItem(peer, item, 1, iscontains);
		if (!iscontains)
		{
			static_cast<PlayerInfo*>(peer->data)->cloth_hair = 0;
			sendClothes(peer);
		}
	}
}

inline void checkTimeBan(ENetPeer* peer, string username)
{
	auto exist = experimental::filesystem::exists("timebanned/" + PlayerDB::getProperName(username) + ".txt");
	if (exist) {
		ifstream fd("timebanned/" + PlayerDB::getProperName(username) + ".txt");
		long long banDuration = 0;
		string bannedBy;
		string bannedReason;
		if (fd.fail()) {
			cout << "[Stream-ERROR]: failed to check whether '" + username + "' is time banned." << endl;
			enet_peer_disconnect_later(peer, 0);
		}
		else {
			fd >> banDuration;
			fd >> bannedBy;
			fd.ignore();
			getline(fd, bannedReason);
			fd.close();
		}
		auto bantimeleft = calcBanDuration(banDuration);
		if (bantimeleft < 1) return;
		auto text = "action|log\nmsg|`4Sorry, this account is temporary banned by `w" + bannedBy + " `4for `w" + OutputBanTime(calcBanDuration(banDuration)) + " `4for `w" + bannedReason + ". `4Need help? `8Contact Sebia#0001!";
		string dc = "https://discord.gg/VCSQ8ZhprK";
		auto url = "action|set_url\nurl|" + dc + "\nlabel|Join Towntopia Discord\n";
		auto data = new BYTE[5 + text.length()];
		auto* dataurl = new BYTE[5 + url.length()];
		BYTE zero = 0;
		auto type = 3;
		memcpy(data, &type, 4);
		memcpy(data + 4, text.c_str(), text.length());
		memcpy(data + 4 + text.length(), &zero, 1);
		memcpy(dataurl, &type, 4);
		memcpy(dataurl + 4, url.c_str(), url.length());
		memcpy(dataurl + 4 + url.length(), &zero, 1);
		auto p = enet_packet_create(data, 5 + text.length(), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, p);
		auto p3 = enet_packet_create(dataurl, 5 + url.length(), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, p3);
		delete data;
		delete dataurl;
		static_cast<PlayerInfo*>(peer->data)->blockLogin = true;
	}
}

inline bool EventWorld(ENetPeer* peer2, string WorldName) {
	return static_cast<PlayerInfo*>(peer2->data)->currentWorld == WorldName;
}

inline bool isDev(ENetPeer* peer) {
	if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 2) return true;
	else return false;
}

inline void autoBan(ENetPeer* peer, bool isInvalid, long long timeInH, string infoText) {
	SendConsole("" + static_cast<PlayerInfo*>(peer->data)->rawName + " banned for " + to_string(timeInH) + " reason " + infoText + "", "BAN");
	string name;
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == true) name = static_cast<PlayerInfo*>(peer->data)->rawName;
	else name = "PLAYER WITHOUT GROW-ID";
	char clientConnection[16];
	enet_address_get_host_ip(&peer->address, clientConnection, 16);
	string hisIp = clientConnection;
	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		Player::OnConsoleMessage(currentPeer, "`4** `$" + name + " `4AUTO-BANNED BY SYSTEM **`` (`$/rules ``to view rules)");
	}
	if (timeInH == 0) {
		enet_peer_disconnect_later(peer, 0);
		return;
	}
	auto registermac = static_cast<PlayerInfo*>(peer->data)->registermac;
	auto registerrid = static_cast<PlayerInfo*>(peer->data)->registerrid;
	auto registersid = static_cast<PlayerInfo*>(peer->data)->registersid;
	auto registergid = static_cast<PlayerInfo*>(peer->data)->registergid;
	auto registervid = static_cast<PlayerInfo*>(peer->data)->registervid;
	auto registeraid = static_cast<PlayerInfo*>(peer->data)->registeraid;
	auto registerIP = static_cast<PlayerInfo*>(peer->data)->registerIP;
	if (registermac != "02:00:00:00:00:00" && registermac != "" && registermac != "none") {
		Remove(registermac, ":");
		std::ofstream outfile2("ipbans/mac/" + registermac + ".txt");
		outfile2 << "user who banned this ID: System" << endl;
		outfile2 << "Ban-ip reason: " + infoText << endl;
		outfile2 << "Banned user name is: " + static_cast<PlayerInfo*>(peer->data)->rawName;
		outfile2.close();
	}
	if (registerrid != "" && registerrid != "none") {
		std::ofstream outfile2("ipbans/rid/" + registerrid + ".txt");
		outfile2 << "user who banned this ID: System" << endl;
		outfile2 << "Ban-ip reason: " + infoText << endl;
		outfile2 << "Banned user name is: " + static_cast<PlayerInfo*>(peer->data)->rawName;
		outfile2.close();
	}
	if (registersid != "" && registersid != "none") {
		std::ofstream outfile2("ipbans/sid/" + registersid + ".txt");
		outfile2 << "user who banned this ID: System" << endl;
		outfile2 << "Ban-ip reason: " + infoText << endl;
		outfile2 << "Banned user name is: " + static_cast<PlayerInfo*>(peer->data)->rawName;
		outfile2.close();
	}
	if (registergid != "" && registergid != "none") {
		std::ofstream outfile2("ipbans/gid/" + registergid + ".txt");
		outfile2 << "user who banned this ID: System" << endl;
		outfile2 << "Ban-ip reason: " + infoText << endl;
		outfile2 << "Banned user name is: " + static_cast<PlayerInfo*>(peer->data)->rawName;
		outfile2.close();
	}
	if (registervid != "" && registervid != "none") {
		std::ofstream outfile2("ipbans/vid/" + registervid + ".txt");
		outfile2 << "user who banned this ID: System" << endl;
		outfile2 << "Ban-ip reason: " + infoText << endl;
		outfile2 << "Banned user name is: " + static_cast<PlayerInfo*>(peer->data)->rawName;
		outfile2.close();
	}
	if (registeraid != "" && registeraid != "none") {
		std::ofstream outfile2("ipbans/aid/" + registeraid + ".txt");
		outfile2 << "user who banned this ID: System" << endl;
		outfile2 << "Ban-ip reason: " + infoText << endl;
		outfile2 << "Banned user name is: " + static_cast<PlayerInfo*>(peer->data)->rawName;
		outfile2.close();
	}
	if (registerIP != "" && registerIP != "none") {
		std::ofstream outfile2("ipbans/ip/" + registerIP + ".txt");
		outfile2 << "user who banned this ID: System" << endl;
		outfile2 << "Ban-ip reason: " + infoText << endl;
		outfile2 << "Banned user name is: " + static_cast<PlayerInfo*>(peer->data)->rawName;
		outfile2.close();
	}
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == true) {
		MYSQL_ROW row;
		string q = "SELECT * FROM PlayerDatabase WHERE username = '" + static_cast<PlayerInfo*>(peer->data)->rawName + "' LIMIT 1";
		string account_history;
		mysql_query(conn, q.c_str());
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) {
			account_history = row[68];
		}
		time_t currentTime;
		time(&currentTime);
		const auto localTime = localtime(&currentTime);
		const auto Hour = localTime->tm_hour;
		const auto Min = localTime->tm_min;
		const auto Sec = localTime->tm_sec;
		const auto Year = localTime->tm_year + 1900;
		const auto Day = localTime->tm_mday;
		const auto Month = localTime->tm_mon + 1;
		account_history += "" + to_string(Month) + "/" + to_string(Day) + "/" + to_string(Year) + " " + to_string(Hour) + ":" + to_string(Min) + ":" + to_string(Sec) + ": System - BAN: " + infoText + " for " + to_string(timeInH) + " hours|";
		string string = "UPDATE PlayerDatabase SET accountnotes = '" + account_history + "' WHERE username = '" + static_cast<PlayerInfo*>(peer->data)->rawName + "' LIMIT 1";
		mysql_query(conn, string.c_str());
	}
	enet_peer_disconnect_later(peer, 0);
}

inline void checkIpBan(ENetPeer* peer)
{
	auto rid = static_cast<PlayerInfo*>(peer->data)->rid;
	auto sid = static_cast<PlayerInfo*>(peer->data)->sid;
	auto gid = static_cast<PlayerInfo*>(peer->data)->gid;
	auto vid = static_cast<PlayerInfo*>(peer->data)->vid;
	auto aid = static_cast<PlayerInfo*>(peer->data)->aid;
	auto mac = static_cast<PlayerInfo*>(peer->data)->mac;
	Remove(mac, ":");
	auto ip_id = to_string(peer->address.host);
	char clientConnection[16];
	enet_address_get_host_ip(&peer->address, clientConnection, 16);
	string ip = clientConnection;
	auto exist = experimental::filesystem::exists("ipbans/rid/" + rid + ".txt") || experimental::filesystem::exists("ipbans/gid/" + gid + ".txt") || experimental::filesystem::exists("ipbans/vid/" + vid + ".txt") || experimental::filesystem::exists("ipbans/aid/" + aid + ".txt") || experimental::filesystem::exists("ipbans/sid/" + sid + ".txt") || experimental::filesystem::exists("ipbans/mac/" + mac + ".txt") || experimental::filesystem::exists("ipbans/ip_id/" + ip_id + ".txt") || experimental::filesystem::exists("ipbans/ip/" + ip + ".txt");
	if (exist)
	{
		string text = "action|log\nmsg|`4Sorry, this device or location is perma banned.";
		string text3 = "action|logon_fail\n";
		string dc = "https://discord.gg/VCSQ8ZhprK";
		auto url = "action|set_url\nurl|" + dc + "\nlabel|Join Towntopia Discord\n";
		auto data = new BYTE[5 + text.length()];
		auto data3 = new BYTE[5 + text3.length()];
		auto dataurl = new BYTE[5 + url.length()];
		BYTE zero = 0;
		auto type = 3;
		memcpy(data, &type, 4);
		memcpy(data + 4, text.c_str(), text.length());
		memcpy(data + 4 + text.length(), &zero, 1);
		memcpy(dataurl, &type, 4);
		memcpy(dataurl + 4, url.c_str(), url.length());
		memcpy(dataurl + 4 + url.length(), &zero, 1);
		memcpy(data3, &type, 4);
		memcpy(data3 + 4, text3.c_str(), text3.length());
		memcpy(data3 + 4 + text3.length(), &zero, 1);
		auto p = enet_packet_create(data, 5 + text.length(), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, p);
		auto p3 = enet_packet_create(dataurl, 5 + url.length(), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, p3);
		auto p2 = enet_packet_create(data3, 5 + text3.length(), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, p2);
		enet_peer_disconnect_later(peer, 0);
		delete data;
		delete dataurl;
		delete data3;
	}
}

inline int PlayerDB::playerLogin(ENetPeer* peer, string username, string password) {
	auto uname = username;
	toUpperCase(uname);
	auto username1 = static_cast<PlayerInfo*>(peer->data)->tankIDName;
	if (username.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != string::npos) return -10;
	if (username.length() < 3) return -2;
	if (username.length() > 20) return -2;
	if (uname == "" || uname == " " || uname == "  " || uname == "   " || uname == "    ") return -5;
	if (username1.find(" ") != string::npos || username1.find(".") != string::npos || username1.find(",") != string::npos || username1.find("@") != string::npos || username1.find("?") != string::npos || username1.find("[") != string::npos || username1.find("]") != string::npos || username1.find("#") != string::npos || username1.find("<") != string::npos || username1.find(">") != string::npos || username1.find(":") != string::npos || username1.find("{") != string::npos || username1.find("}") != string::npos || username1.find("|") != string::npos || username1.find("+") != string::npos || username1.find("_") != string::npos || username1.find("~") != string::npos || username1.find("-") != string::npos || username1.find("!") != string::npos || username1.find("$") != string::npos || username1.find("%") != string::npos || username1.find("^") != string::npos || username1.find("&") != string::npos || username1.find("`") != string::npos || username1.find("*") != string::npos || username1.find("(") != string::npos || username1.find(")") != string::npos || username1.find("=") != string::npos || username1.find("'") != string::npos || username1.find(";") != string::npos || username1.find("/") != string::npos) return -5;
	auto rid = static_cast<PlayerInfo*>(peer->data)->rid;
	auto sid = static_cast<PlayerInfo*>(peer->data)->sid;
	auto gid = static_cast<PlayerInfo*>(peer->data)->gid;
	auto vid = static_cast<PlayerInfo*>(peer->data)->vid;
	auto aid = static_cast<PlayerInfo*>(peer->data)->aid;
	auto mac = static_cast<PlayerInfo*>(peer->data)->mac;
	char clientConnection[16];
	enet_address_get_host_ip(&peer->address, clientConnection, 16);
	string ipe = clientConnection;
	Remove(mac, ":");
	auto ip_id = to_string(peer->address.host);
	auto existtwo = experimental::filesystem::exists("ipbans/rid/" + rid + ".txt") || experimental::filesystem::exists("ipbans/gid/" + gid + ".txt") || experimental::filesystem::exists("ipbans/vid/" + vid + ".txt") || experimental::filesystem::exists("ipbans/aid/" + aid + ".txt") || experimental::filesystem::exists("ipbans/sid/" + sid + ".txt") || experimental::filesystem::exists("ipbans/mac/" + mac + ".txt") || experimental::filesystem::exists("ipbans/ip_id/" + ip_id + ".txt") || experimental::filesystem::exists("ipbans/ip/" + ipe + ".txt");
	if (existtwo) return -9;
	MYSQL_ROW row;
	string q = "SELECT * FROM PlayerDatabase WHERE username = '" + username + "' LIMIT 1";
	if (mysql_query(conn, q.c_str())) {
		cout << mysql_error(conn) << endl;		
		return 0;
	}
	string timebanned = "", connectionip = "", verified = "", Password = "", InventorySize = "", DailyRewards = "", Skill = "", Banned = "", email = "";
	res = mysql_store_result(conn);
	while (row = mysql_fetch_row(res)) {
		Password = row[2];
		email = row[3];
		InventorySize = row[27];
		Skill = row[28];
		DailyRewards = row[29];
		Banned = row[14];
		connectionip = row[50];
		verified = row[51];
		timebanned = row[56];
	} if (password == Password) {
		if (Banned == "1") {
			SendConsole("person was banned", "ERROR");
			return -3;
		}
		static_cast<PlayerInfo*>(peer->data)->email = email;
		if (connectionip != static_cast<PlayerInfo*>(peer->data)->charIP && static_cast<PlayerInfo*>(peer->data)->charIP != "127.0.0.1" || verified == "false" && static_cast<PlayerInfo*>(peer->data)->charIP != "127.0.0.1") return -6;
		if (calcBanDuration(atoi(timebanned.c_str())) != 0) {
			static_cast<PlayerInfo*>(peer->data)->timeBanned = atoi(timebanned.c_str());
			return -8;
		}
		for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
			if (net_peer->state != ENET_PEER_STATE_CONNECTED || net_peer == peer) continue;
			if (static_cast<PlayerInfo*>(net_peer->data)->rawName == PlayerDB::getProperName(username)) {
				Player::OnConsoleMessage(peer, "`4ALREADY ON?! `o: This account was already online, kicking it off so you can log on. (if you were just playing before, this is nothing to worry about)");
				enet_peer_disconnect_later(net_peer, 0);
			}
		}
		static_cast<PlayerInfo*>(peer->data)->currentInventorySize = atoi(InventorySize.c_str());
		static_cast<PlayerInfo*>(peer->data)->skill = Skill;
		static_cast<PlayerInfo*>(peer->data)->lastdailyGems = atoi(DailyRewards.c_str());
		return 1;
	}
	else return -1;
}

inline int PlayerDB::playerRegister(ENetPeer* peer, string username, string password, string email) {
	if (username.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != string::npos) return -10;
	if (email.find("@") == string::npos || email.length() <= 0 || email.length() > 30) return -15;
	if (username.length() < 3) return -2;
	if (username.length() > 20) return -2;
	if (username == "" || username == " " || username == "  " || username == "   " || username == "    ") return -11;
	username = PlayerDB::getProperName(username);
	auto existGems = std::experimental::filesystem::exists("gemdb/" + username + ".txt");
	if (!existGems) {
		ofstream pGems("gemdb/" + username + ".txt");
		pGems << 0;
		pGems.close();
	}
	MYSQL_ROW row;
	string name;
	string q = "SELECT * FROM PlayerDatabase WHERE username = '" + username + "' LIMIT 1";
	if (mysql_query(conn, q.c_str())) {
		cout << mysql_error(conn) << endl;	
		return 0;
	}
	res = mysql_store_result(conn);
	while (row = mysql_fetch_row(res)) {
		name = row[1];
	}
	if (name.length() > 0) return -1;
	char clientConnection[16];
	enet_address_get_host_ip(&peer->address, clientConnection, 16);
	string hisIp = clientConnection;
	string checkrid = static_cast<PlayerInfo*>(peer->data)->rid == "none" ? "aw5g1a5sdg" : static_cast<PlayerInfo*>(peer->data)->rid;
	string checksid = static_cast<PlayerInfo*>(peer->data)->sid == "none" ? "aw5g1a5sdg" : static_cast<PlayerInfo*>(peer->data)->sid;
	string checkgid = static_cast<PlayerInfo*>(peer->data)->gid == "none" ? "aw5g1a5sdg" : static_cast<PlayerInfo*>(peer->data)->gid;
	string checkmac = static_cast<PlayerInfo*>(peer->data)->mac == "none" || static_cast<PlayerInfo*>(peer->data)->mac == "02:00:00:00:00:00" ? "aw5g1a5sdg" : static_cast<PlayerInfo*>(peer->data)->mac;
	string checkvid = static_cast<PlayerInfo*>(peer->data)->vid == "none" ? "aw5g1a5sdg" : static_cast<PlayerInfo*>(peer->data)->vid;
	short altcount = 0;	
	string qds = "SELECT * FROM PlayerDatabase WHERE ip = '" + hisIp + "' OR email = '" + email + "' OR rid = '" + checkrid + "' OR sid = '" + checksid + "' OR gid = '" + checkgid + "' OR mac = '" + checkmac + "' OR vid = '" + checkvid + "'";
	if (mysql_query(conn, qds.c_str())) {
		cout << mysql_error(conn) << endl;	
		return -14;
	}
	res = mysql_store_result(conn);
	while (row = mysql_fetch_row(res)) {
		altcount++;
	}
	if (altcount >= 2) return -14;
	json items;
	json jjall = json::array();
	json jj;
	jj["aposition"] = 1;
	jj["itemid"] = 18;
	jj["quantity"] = 1;
	jjall.push_back(jj);
	jj["aposition"] = 2;
	jj["itemid"] = 32;
	jj["quantity"] = 1;
	jjall.push_back(jj);
	for (int i = 2; i < 200; i++) {
		jj["aposition"] = i + 1;
		jj["itemid"] = 0;
		jj["quantity"] = 0;
		jjall.push_back(jj);
	}
	items["items"] = jjall;
	string qsd = "INSERT INTO PlayerDatabase(username, password, email, ClothBack, ClothHand, ClothFace, ClothShirt, ClothPants, ClothNeck, ClothHair, ClothFeet, ClothMask, ClothAnces, isBanned, ipID, effect, friends, receivedwarns, adminLevel, guild, joinguild, level, xp, worldsowned, notebook, kills, inventorysize, skill, dailyrewards, lastonline, online, mac, rid, sid, gid, vid, aid, ip, subtype, subdate, title, surgeonlevel, nick, invis, ghost, skin, chatcolor, code, signedip, verified, gems, lastworld, timecursed, timemuted, timebanned, surgerycooldown, lastnormalworld, inventory, dailyBundle, firefighterlevel, firefighterxp, providerlevel, providerxp, geigercooldown, geigerlevel, geigerxp, accountnotes, fishermanlevel, fishermanxp) VALUES ('" + username + "', '" + password + "', '" + email + "', '" + std::to_string(0) + "', '" + std::to_string(0) + "', '" + std::to_string(0) + "', '" + std::to_string(0) + "', '0', '0', '0', '0', '" + std::to_string(0) + "', '0', '0', '" + to_string(peer->address.host) + "', '8421376', '', '" + to_string(static_cast<PlayerInfo*>(peer->data)->warns) + "', '0', '', 'false', '1', '0', '', '', '0', '30', 'None', '0', '0', 'false', '" + static_cast<PlayerInfo*>(peer->data)->mac + "', '" + static_cast<PlayerInfo*>(peer->data)->rid + "', '" + static_cast<PlayerInfo*>(peer->data)->sid + "', '" + static_cast<PlayerInfo*>(peer->data)->gid + "', '" + static_cast<PlayerInfo*>(peer->data)->vid + "', '" + static_cast<PlayerInfo*>(peer->data)->aid + "', '" + hisIp + "', '', '', '', '0', '', 'false', 'false', '0x8295C3FF', '', '', '" + static_cast<PlayerInfo*>(peer->data)->charIP + "', 'true', '0', '', '0', '0', '0', '0', 'START', '" + JsonToString(items) + "', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '0')";
	if (mysql_query(conn, qsd.c_str())) {
		cout << mysql_error(conn) << endl;		
		return 0;
	}
	return 1;
}

inline bool isMod(ENetPeer* peer)
{
	if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 1 || static_cast<PlayerInfo*>(peer->data)->adminLevel == 2) return true;
	else return false;
}

inline bool isPlayer(ENetPeer* peer)
{
	if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 0) return true;
	else return false;
}

inline bool isPickaxe(ENetPeer* peer)
{
	if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 2754 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 7830 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 930 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 1874 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 6368 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 2572 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 1484 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 734 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 98 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 1438 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 4956 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 1708)
	{
		return true;
	}
	else
	{
		return false;
	}
}

inline bool isRedAnces(ENetPeer* peer)
{
	if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5084 || static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5180 || static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5182 || static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5184 || static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5186 || static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5188)
	{
		return true;
	}
	else
	{
		return false;
	}
}

inline bool isGreenAnces(ENetPeer* peer)
{
	if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5082 || static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5162 || static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5164 || static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5166 || static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5168 || static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5170)
	{
		return true;
	}
	else
	{
		return false;
	}
}

inline bool isBlueAnces(ENetPeer* peer)
{
	if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5080 || static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5144 || static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5146 || static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5148 || static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5150 || static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5152)
	{
		return true;
	}
	else
	{
		return false;
	}
}

inline bool isYellowAnces(ENetPeer* peer)
{
	if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5078 || static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5126 || static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5128 || static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5130 || static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5132 || static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5134)
	{
		return true;
	}
	else
	{
		return false;
	}
}

inline bool isFishingRod(ENetPeer* peer)
{
	if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 2912 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3008 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3010 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3040 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3100 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 5740)
	{
		return true;
	}
	else
	{
		return false;
	}
}

inline string getModsOnlineCount()
{
	auto modCount = 0;
	string text = "No mods are online";
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isMod(currentPeer))
		{
			if (static_cast<PlayerInfo*>(currentPeer->data)->isinv == true) continue;
			if (static_cast<PlayerInfo*>(currentPeer->data)->isNicked == true) continue;

			modCount++;
		}
	}
	if (modCount == 1)
	{
		text = to_string(modCount) + " mod is online";
	}
	if (modCount > 1)
	{
		text = to_string(modCount) + " mods are online";
	}
	return text;
}

inline void showModLogs(const string textInfo)
{

}

inline void AutoDemote(string playerName, string his_rank, string ipAddress, string whyDemote)
{

}

inline void GiveRank(string rankName, string playerName, bool& success) {
	int rankLevel = 0;
	if (rankName == "player") {
		rankLevel = 0;
	} else if (rankName == "mod") {
		rankLevel = 1;
	} else if (rankName == "dev") {
		rankLevel = 2;
	}
	stringstream ss;
	ss << "UPDATE PlayerDatabase SET adminLevel = '" + to_string(rankLevel) + "' WHERE username = '" + playerName + "' LIMIT 1";
	const auto query = ss.str();
	const auto q = query.c_str();
	if (mysql_query(conn, q)) {
		cout << mysql_error(conn) << endl;			
		return;
	}
	success = true;
}

inline bool SaveConvertedItemDls(int fItemid, int fQuantity, ENetPeer* peer) {
	bool doesItemInInventryAlready = false;
	for (int i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++) {
		if (static_cast<PlayerInfo*>(peer->data)->inventory.items[i].itemID == fItemid) {
			doesItemInInventryAlready = true;
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items[i].itemCount >= 151) return false;
			break;
		}
	}
	if (doesItemInInventryAlready == false) {
		static_cast<PlayerInfo*>(peer->data)->needsaveinventory = true;
		InventoryItem item;
		item.itemID = fItemid;
		item.itemCount = fQuantity;
		static_cast<PlayerInfo*>(peer->data)->inventory.items.push_back(item);
		SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
	} else {
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++) {
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemid) {
				static_cast<PlayerInfo*>(peer->data)->needsaveinventory = true;
				static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount += fQuantity;
				SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
				break;
			}
		}
	}
	return true;
}

inline bool SaveConvertedItem(int fItemid, int fQuantity, ENetPeer* peer) {
	bool doesItemInInventryAlready = false;
	for (int i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++) {
		if (static_cast<PlayerInfo*>(peer->data)->inventory.items[i].itemID == fItemid) {
			doesItemInInventryAlready = true;
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items[i].itemCount >= 250) return false;
			break;
		}
	}
	if (doesItemInInventryAlready == false) {
		static_cast<PlayerInfo*>(peer->data)->needsaveinventory = true;
		InventoryItem item;
		item.itemID = fItemid;
		item.itemCount = fQuantity; 
		static_cast<PlayerInfo*>(peer->data)->inventory.items.push_back(item);
		SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
	} else {
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++) {
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemid) {
				static_cast<PlayerInfo*>(peer->data)->needsaveinventory = true;
				static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount += fQuantity;
				SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
				break;
			}
		}
	}
	return true;
}
inline bool CheckItemMaxed(ENetPeer* peer, const int fItemId, const int fQuantityAdd) {
	auto isMaxed = false;
	for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++) {
		if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemId && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount + fQuantityAdd > 250) {
			isMaxed = true;
			break;
		}
	}
	return isMaxed;
}
inline int GetQuantityOfItem(ENetPeer* peer, const int fItemId) {
	auto quantity = 0;
	for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++) {
		if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemId) {
			quantity = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
			break;
		}
	}
	return quantity;
}
inline void SaveFindsItem(int fItemid, int fQuantity, ENetPeer* peer) {
	static_cast<PlayerInfo*>(peer->data)->needsaveinventory = true;
	InventoryItem item;
	item.itemID = fItemid;
	item.itemCount = fQuantity;
	static_cast<PlayerInfo*>(peer->data)->inventory.items.push_back(item);
	SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
	const auto p3 = packetEnd(appendFloat(appendIntx(appendFloat(appendFloat(appendFloat(appendString(createPacket(), "OnSetClothing"), (static_cast<PlayerInfo*>(peer->data))->cloth_hair, (static_cast<PlayerInfo*>(peer->data))->cloth_shirt, (static_cast<PlayerInfo*>(peer->data))->cloth_pants), (static_cast<PlayerInfo*>(peer->data))->cloth_feet, (static_cast<PlayerInfo*>(peer->data))->cloth_face, (static_cast<PlayerInfo*>(peer->data))->cloth_hand), (static_cast<PlayerInfo*>(peer->data))->cloth_back, (static_cast<PlayerInfo*>(peer->data))->cloth_mask, (static_cast<PlayerInfo*>(peer->data))->cloth_necklace), (static_cast<PlayerInfo*>(peer->data))->skinColor), (static_cast<PlayerInfo*>(peer->data))->cloth_ances, 0.0f, 0.0f));
	memcpy(p3.data + 8, &((static_cast<PlayerInfo*>(peer->data))->netID), 4);
	const auto packet = enet_packet_create(p3.data, p3.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
}
inline void RemoveInventoryItem(int fItemid, int fQuantity, ENetPeer* peer, bool update, bool plant = false) {
	static_cast<PlayerInfo*>(peer->data)->needsaveinventory = true;
	for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++) {
		if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemid) {
			if (static_cast<unsigned int>(static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount) > fQuantity && static_cast<unsigned int>(static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount) != fQuantity) {
				static_cast<PlayerInfo*>(peer->data)->needsaveinventory = true;
				static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount -= fQuantity;
			} else {
				static_cast<PlayerInfo*>(peer->data)->needsaveinventory = true;
				static_cast<PlayerInfo*>(peer->data)->inventory.items.erase(static_cast<PlayerInfo*>(peer->data)->inventory.items.begin() + i);
			}
			if (!plant) SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
			if (update) {
				const auto p3 = packetEnd(appendFloat(appendIntx(appendFloat(appendFloat(appendFloat(appendString(createPacket(), "OnSetClothing"), (static_cast<PlayerInfo*>(peer->data))->cloth_hair, (static_cast<PlayerInfo*>(peer->data))->cloth_shirt, (static_cast<PlayerInfo*>(peer->data))->cloth_pants), (static_cast<PlayerInfo*>(peer->data))->cloth_feet, (static_cast<PlayerInfo*>(peer->data))->cloth_face, (static_cast<PlayerInfo*>(peer->data))->cloth_hand), (static_cast<PlayerInfo*>(peer->data))->cloth_back, (static_cast<PlayerInfo*>(peer->data))->cloth_mask, (static_cast<PlayerInfo*>(peer->data))->cloth_necklace), (static_cast<PlayerInfo*>(peer->data))->skinColor), (static_cast<PlayerInfo*>(peer->data))->cloth_ances, 0.0f, 0.0f));
				memcpy(p3.data + 8, &((static_cast<PlayerInfo*>(peer->data))->netID), 4);
				const auto packet = enet_packet_create(p3.data, p3.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
			}
			break;
		}
	}
}
inline void GiveChestPrizeGems(ENetPeer* peer, int gemsAmount) {
	int currentGems = 0;
	ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
	ifs >> currentGems;
	ifs.close();
	currentGems += gemsAmount;
	ofstream ofs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
	ofs << currentGems;
	ofs.close();
	GamePacket pp = packetEnd(appendInt(appendString(createPacket(), "OnSetBux"), currentGems));
	ENetPacket* packetpp = enet_packet_create(pp.data, pp.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packetpp);
	delete pp.data;
	Player::OnConsoleMessage(peer, "`oYou have obtained `$" + to_string(gemsAmount) + " `ogems");
	Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, " `wYou obtained " + to_string(gemsAmount) + " `wgems", 0, true);
	const int effect = 30;
	const int x = static_cast<PlayerInfo*>(peer->data)->x;
	const int y = static_cast<PlayerInfo*>(peer->data)->y;
	Player::OnParticleEffect(peer, effect, x, y, 0);
}
inline void onPeerConnect(ENetPeer* peer) {
	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (peer != currentPeer) {
			if (isHere(peer, currentPeer)) {
				string netIdS = std::to_string(static_cast<PlayerInfo*>(currentPeer->data)->netID);
				GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + netIdS + "\nuserID|" + netIdS + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(static_cast<PlayerInfo*>(currentPeer->data)->x) + "|" + std::to_string(static_cast<PlayerInfo*>(currentPeer->data)->y) + "\nname|``" + static_cast<PlayerInfo*>(currentPeer->data)->displayName + "``\ncountry|" + static_cast<PlayerInfo*>(currentPeer->data)->country + "\ninvis|0\nmstate|0\nsmstate|0\n")); // ((PlayerInfo*)(server->peers[i].data))->tankIDName
				ENetPacket* packet = enet_packet_create(p.data,	p.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
				delete p.data;
				string netIdS2 = std::to_string(static_cast<PlayerInfo*>(peer->data)->netID);
				GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + netIdS2 + "\nuserID|" + netIdS2 + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(static_cast<PlayerInfo*>(peer->data)->x) + "|" + std::to_string(static_cast<PlayerInfo*>(peer->data)->y) + "\nname|``" + static_cast<PlayerInfo*>(peer->data)->displayName + "``\ncountry|" + static_cast<PlayerInfo*>(peer->data)->country + "\ninvis|0\nmstate|0\nsmstate|0\n")); // ((PlayerInfo*)(server->peers[i].data))->tankIDName
				ENetPacket* packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2);
				delete p2.data;
			}
		}
	}
}
inline void sendSound(ENetPeer* peer, const string sound) {
	const auto text = "action|play_sfx\nfile|audio/" + sound + "\ndelayMS|0\n";
	const auto data = new BYTE[5 + text.length()];
	BYTE zero = 0;
	auto type = 3;
	memcpy(data, &type, 4);
	memcpy(data + 4, text.c_str(), text.length());
	memcpy(data + 4 + text.length(), &zero, 1);
	const auto packet2 = enet_packet_create(data, 5 + text.length(), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2);
	delete data;
}
inline void sendTime(ENetPeer* peer) {
	using namespace std::chrono;
	auto _tm = time(nullptr);
	const auto curtime = localtime(&_tm);
	const string test = asctime(curtime);
	Player::OnConsoleMessage(peer, "`2Growtopia Time (EDT/UTC-5): " + test + "");
}
inline void updateInvis(ENetPeer* peer) {
	for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			auto p2 = packetEnd(appendInt(appendString(createPacket(), "OnInvis"), static_cast<PlayerInfo*>(peer->data)->isinv));
			memcpy(p2.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
			const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet2);
			delete p2.data;
			auto p3 = packetEnd(appendInt(appendString(createPacket(), "OnInvis"), static_cast<PlayerInfo*>(currentPeer->data)->isinv));
			memcpy(p3.data + 8, &(static_cast<PlayerInfo*>(currentPeer->data)->netID), 4);
			const auto packet3 = enet_packet_create(p3.data, p3.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet3);
			delete p3.data;
			if (static_cast<PlayerInfo*>(peer->data)->level >= 100)
			{
				auto p2ww = packetEnd(appendString(appendString(createPacket(), "OnCountryState"), static_cast<PlayerInfo*>(peer->data)->country + "|showGuild"));
				memcpy(p2ww.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
				const auto packet2ww = enet_packet_create(p2ww.data, p2ww.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2ww);
				delete p2ww.data;
				auto p2wwee = packetEnd(appendString(appendString(createPacket(), "OnCountryState"), static_cast<PlayerInfo*>(currentPeer->data)->country + "|showGuild"));
				memcpy(p2wwee.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
				const auto packet2wwee = enet_packet_create(p2wwee.data, p2wwee.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet2wwee);
				delete p2wwee.data;
			} else {
				auto p2ww = packetEnd(appendString(appendString(createPacket(), "OnCountryState"), static_cast<PlayerInfo*>(peer->data)->country + "|showGuild"));
				memcpy(p2ww.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
				const auto packet2ww = enet_packet_create(p2ww.data, p2ww.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2ww);
				delete p2ww.data;
				auto p2wwee = packetEnd(appendString(appendString(createPacket(), "OnCountryState"), static_cast<PlayerInfo*>(currentPeer->data)->country + "|showGuild"));
				memcpy(p2wwee.data + 8, &(static_cast<PlayerInfo*>(currentPeer->data)->netID), 4);
				const auto packet2wwee = enet_packet_create(p2wwee.data, p2wwee.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet2wwee);
				delete p2wwee.data;
			}
			const auto flag1 = (65536 * static_cast<PlayerInfo*>(peer->data)->guildBg) + static_cast<PlayerInfo*>(peer->data)->guildFg;
			if (static_cast<PlayerInfo*>(currentPeer->data)->rawName == static_cast<PlayerInfo*>(currentPeer->data)->guildLeader) {
				auto p2gg = packetEnd(appendIntx(appendIntx(appendIntx(appendIntx(appendString(createPacket(), "OnGuildDataChanged"), 41179607), 41179607), flag1), 0));
				memcpy(p2gg.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
				const auto packet2gg = enet_packet_create(p2gg.data, p2gg.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2gg);
				delete p2gg.data;
				const auto flag2 = (65536 * static_cast<PlayerInfo*>(currentPeer->data)->guildBg) + static_cast<PlayerInfo*>(currentPeer->data)->guildFg;
				auto p2xd = packetEnd(appendIntx(appendIntx(appendIntx(appendIntx(appendString(createPacket(), "OnGuildDataChanged"), 41179607), 41179607), flag2), 0));
				memcpy(p2xd.data + 8, &(static_cast<PlayerInfo*>(currentPeer->data)->netID), 4);
				const auto packet2xd = enet_packet_create(p2xd.data, p2xd.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet2xd);
				delete p2xd.data;
			} else {
				auto p2gg = packetEnd(appendIntx(appendIntx(appendIntx(appendIntx(appendString(createPacket(), "OnGuildDataChanged"), 41179607), 41179607), flag1), 0));
				memcpy(p2gg.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
				const auto packet2gg = enet_packet_create(p2gg.data, p2gg.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2gg);
				delete p2gg.data;
				const auto flag2 = (65536 * static_cast<PlayerInfo*>(currentPeer->data)->guildBg) + static_cast<PlayerInfo*>(currentPeer->data)->guildFg;
				auto p2xd = packetEnd(appendIntx(appendIntx(appendIntx(appendIntx(appendString(createPacket(), "OnGuildDataChanged"), 41179607), 41179607), flag2), 0));
				memcpy(p2xd.data + 8, &(static_cast<PlayerInfo*>(currentPeer->data)->netID), 4);
				const auto packet2xd = enet_packet_create(p2xd.data, p2xd.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet2xd);
				delete p2xd.data;
			}
		}
	}
}
inline void updateAllClothes(ENetPeer* peer) {
	for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			auto p3 = packetEnd(appendFloat(appendIntx(appendFloat(appendFloat(appendFloat(appendString(createPacket(), "OnSetClothing"), static_cast<PlayerInfo*>(peer->data)->cloth_hair, static_cast<PlayerInfo*>(peer->data)->cloth_shirt, static_cast<PlayerInfo*>(peer->data)->cloth_pants), static_cast<PlayerInfo*>(peer->data)->cloth_feet, static_cast<PlayerInfo*>(peer->data)->cloth_face, static_cast<PlayerInfo*>(peer->data)->cloth_hand), static_cast<PlayerInfo*>(peer->data)->cloth_back, static_cast<PlayerInfo*>(peer->data)->cloth_mask, static_cast<PlayerInfo*>(peer->data)->cloth_necklace), static_cast<PlayerInfo*>(peer->data)->skinColor), static_cast<PlayerInfo*>(peer->data)->cloth_ances, 0.0f, 0.0f));
			memcpy(p3.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
			const auto packet3 = enet_packet_create(p3.data, p3.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet3);
			delete p3.data;
			auto p4 = packetEnd(appendFloat(appendIntx(appendFloat(appendFloat(appendFloat(appendString(createPacket(), "OnSetClothing"), static_cast<PlayerInfo*>(currentPeer->data)->cloth_hair, static_cast<PlayerInfo*>(currentPeer->data)->cloth_shirt, static_cast<PlayerInfo*>(currentPeer->data)->cloth_pants), static_cast<PlayerInfo*>(currentPeer->data)->cloth_feet, static_cast<PlayerInfo*>(currentPeer->data)->cloth_face, static_cast<PlayerInfo*>(currentPeer->data)->cloth_hand), static_cast<PlayerInfo*>(currentPeer->data)->cloth_back, static_cast<PlayerInfo*>(currentPeer->data)->cloth_mask, static_cast<PlayerInfo*>(currentPeer->data)->cloth_necklace), static_cast<PlayerInfo*>(currentPeer->data)->skinColor), static_cast<PlayerInfo*>(currentPeer->data)->cloth_ances, 0.0f, 0.0f));
			memcpy(p4.data + 8, &(static_cast<PlayerInfo*>(currentPeer->data)->netID), 4);
			const auto packet4 = enet_packet_create(p4.data, p4.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet4);
			delete p4.data;
		}
	}
}
inline void Player::OnInvis(ENetPeer* peer, const int state, int netID)
{
	GamePacket p = packetEnd(appendInt(appendString(createPacket(), "OnInvis"), state));
	memcpy(p.data + 8, &netID, 4);
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
inline void Player::OnFailedToEnterWorld(ENetPeer* peer)
{
	GamePacket p = packetEnd(appendIntx(appendString(createPacket(), "OnFailedToEnterWorld"), 1));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
inline void Player::OnTextOverlay(ENetPeer* peer, string text)
{
	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnTextOverlay"), text));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
inline void Player::OnKilled(ENetPeer* peer, int netID)
{
	GamePacket p = packetEnd(appendString(createPacket(), "OnKilled"));
	memcpy(p.data + 8, &netID, 4);
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
inline void Player::SetRespawnPos(ENetPeer* peer, int posX, int posY, int netID)
{
	GamePacket p22 = packetEnd(appendInt(appendString(createPacket(), "SetRespawnPos"), posX + posY)); // (world->width * posY)
	memcpy(p22.data + 8, &netID, 4);
	ENetPacket* packet22 = enet_packet_create(p22.data,
		p22.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet22);
	delete p22.data;
}
inline void Player::OnZoomCamera(ENetPeer* peer, float value1, int value2)
{
	GamePacket p = packetEnd(appendIntx(appendFloat(appendString(createPacket(), "OnZoomCamera"), value1), value2));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
inline void Player::SmoothZoom(ENetPeer* peer)
{
	GamePacket p = packetEnd(appendIntx(appendFloat(appendString(createPacket(), "OnZoomCamera"), 10000.0f), 1000));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
inline void Player::OnRaceStart(ENetPeer* peer, int netID)
{
	GamePacket p = packetEnd(appendString(createPacket(), "OnRaceStart"));
	memcpy(p.data + 8, &netID, 4);
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
inline void Player::OnRaceEnd(ENetPeer* peer, int netID)
{
	GamePacket p = packetEnd(appendString(createPacket(), "OnRaceStart"));
	memcpy(p.data + 8, &netID, 4);
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
inline void Player::Ping(ENetPeer* peer)
{
	GamePacket p = packetEnd(appendString(createPacket(), "Ping"));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
inline void Player::OnDialogRequest(ENetPeer* peer, string args)
{
	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), args));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}

inline void Player::OnSetPos(ENetPeer* peer, int netID, int x, int y)
{
	GamePacket p = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), x, y));
	memcpy(p.data + 8, &netID, 4);
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}

inline void Player::OnSetFreezeState(ENetPeer* peer, int state, int netID)
{
	GamePacket p = packetEnd(appendInt(appendString(createPacket(), "OnSetFreezeState"), state));
	memcpy(p.data + 8, &netID, 4);
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}

inline void Player::OnSetCurrentWeather(ENetPeer* peer, const int weather)
{
	
	auto p = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), weather));
	const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}

inline void Player::OnSetBux(ENetPeer* peer, const int gems, const int accountstate)
{
	
	if (static_cast<PlayerInfo*>(peer->data)->Subscriber) {
		auto p = packetEnd(appendInt(appendInt(appendInt(appendString(createPacket(), "OnSetBux"), gems), accountstate), 1));
		const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	} else {
		auto p = packetEnd(appendInt(appendInt(appendString(createPacket(), "OnSetBux"), gems), accountstate));
		const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
}

inline void Player::OnParticleEffect(ENetPeer* peer, const int effect, const float x, const float y, int delay)
{
	
	auto p = packetEnd(appendFloat(appendIntx(appendString(createPacket(), "OnParticleEffect"), effect), x + 15, y + 15)); // + 15 to fix float and int things
	auto deathFlag = 0x19;
	memcpy(p.data + 24, &delay, 4);
	memcpy(p.data + 56, &deathFlag, 4);
	const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}

inline void Player::SetHasGrowID(ENetPeer* peer, int status, string username, string password)
{
	
	GamePacket p2 = packetEnd(appendString(appendString(appendInt(appendString(createPacket(), "SetHasGrowID"), status), username), password));
	ENetPacket* packet2 = enet_packet_create(p2.data,
		p2.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2);
	delete p2.data;
}
inline void Player::OnNameChanged(ENetPeer* peer, int netID, string name)
{
	GamePacket p3 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), "`0`0" + name));
	memcpy(p3.data + 8, &netID, 4);
	ENetPacket* packet3 = enet_packet_create(p3.data,
		p3.len,
		ENET_PACKET_FLAG_RELIABLE);
	for (ENetPeer* currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer))
		{
			enet_peer_send(currentPeer, 0, packet3);
		}
	}
	delete p3.data;
}
inline void Player::OnSendToServer(ENetPeer* peer, int userID, int token, string ip, int port, string doorId, int lmode)
{
	
	auto p = packetEnd(appendInt(appendString(appendInt(appendInt(appendInt(appendString(createPacket(), "OnSendToServer"), port), token), userID), ip + "|" + doorId), lmode));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
inline void Player::OnChangeSkin(ENetPeer* peer, const int skinColor, int netID)
{
	
	auto p = packetEnd(appendInt(appendString(createPacket(), "OnChangeSkin"), skinColor));
	memcpy(p.data + 8, &netID, 4);
	const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
inline void Player::OnCountdownStart(ENetPeer* peer, int netID, int time, int score)
{
	
	if (score == -1)
	{
		auto p = packetEnd(appendInt(appendString(createPacket(), "OnCountdownStart"), time));
		memcpy(p.data + 8, &netID, 4);
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
	else
	{
		auto p = packetEnd(appendInt(appendInt(appendString(createPacket(), "OnCountdownStart"), time), score));
		memcpy(p.data + 8, &netID, 4);
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
}
inline void Player::OnPlayPositioned(ENetPeer* peer, string audiofile, int netID, bool broadcastInWorld, ENetPacket* pk) // packet only externally used when broadcasting / sending to multiple players to reduce memory leaks / cpu usage cuz we dont want to loop creating the packet for each player that would be insanely stupid.
{
	
	if (broadcastInWorld)
	{
		for (ENetPeer* currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (isHere(peer, currentPeer))
			{
				enet_peer_send(currentPeer, 0, pk);
			}
		}
	}
	else
	{
		auto p = packetEnd(appendString(appendString(createPacket(), "OnPlayPositioned"), audiofile));
		memcpy(p.data + 8, &netID, 4);
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
}

inline void Player::OnStartTrade(ENetPeer* peer, string displayName, int netID)
{
	
	auto p = packetEnd(appendInt(appendString(appendString(createPacket(), "OnStartTrade"), displayName), netID));
	const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
inline void Player::OnForceTradeEnd(ENetPeer* peer)
{
	
	GamePacket p = packetEnd(appendString(createPacket(), "OnForceTradeEnd"));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
inline void Player::PlayAudio(ENetPeer* peer, string audioFile, int delayMS) {
	const string text = "action|play_sfx\nfile|" + audioFile + "\ndelayMS|" + to_string(delayMS) + "\n";
	BYTE* data = new BYTE[5 + text.length()];
	BYTE zero = 0;
	int type = 3;
	memcpy(data, &type, 4);
	memcpy(data + 4, text.c_str(), text.length());
	memcpy(data + 4 + text.length(), &zero, 1);
	ENetPacket* packet = enet_packet_create(data,
		5 + text.length(),
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete data;
}
inline void Player::OnRemove(ENetPeer* peer, int netID)
{
	
	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnRemove"), "netID|" + std::to_string(netID) + "\n"));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}
inline void Player::OnConsoleMessage(ENetPeer* peer, string text)
{
	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), text));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}

inline void Player::OnTalkBubble(ENetPeer* peer, const int netID, const string text, const int chatColor, const bool isOverlay)
{
	if (text == ":)" || text == ":(" || text == ":*" || text == ":o" || text == ":O" || text == ":D") return;
	if (isOverlay == true)
	{
		auto p = packetEnd(appendIntx(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), netID), text), chatColor), 1));
		const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
	else
	{
		auto p = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), netID), text), chatColor));
		const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
}

inline void Player::OnAddNotification(ENetPeer* peer, string text, string audiosound, string interfaceimage) {
	auto p = packetEnd(appendInt(appendString(appendString(appendString(appendString(createPacket(), "OnAddNotification"), interfaceimage), text), audiosound), 0));
	ENetPacket* packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	delete p.data;
}

inline void sendWrongCmd(ENetPeer* peer) {
	Player::OnConsoleMessage(peer, "`4Unknown command. `oEnter `$/help `ofor a list of valid commands.");
}

inline void LoadPlayerData(ENetPeer* peer) {
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId && static_cast<PlayerInfo*>(peer->data)->rawName != "") {
		MYSQL_ROW row;
		string q = "SELECT * FROM PlayerDatabase WHERE username = '" + static_cast<PlayerInfo*>(peer->data)->rawName + "' LIMIT 1";
		if (mysql_query(conn, q.c_str())) {
			cout << mysql_error(conn) << endl;	
			return;
		}
		string mac = "", rid = "", sid = "", gid = "", vid = "", aid = "", ip = "", playerid = "", lastnormalworld = "", email = "", timemuted = "", timecursed = "", surgerycooldown = "", geigercooldown = "", lastworld = "", effect = "", nick = "", invis = "", ghost = "", skin = "", chatcolor = "", ClothBack = "", ClothHand = "", ClothFace = "", ClothHair = "", ClothFeet = "", ClothPants = "", ClothNeck = "", ClothShirt = "", ClothMask = "", ClothAnces = "", Friends = "", WorldOwned = "", AdminLevel = "", Level = "", Experience = "", KillsCount = "", GuildName = "", InventorySize = "", PersonalNote = "", SkillName = "", JoinedGuild = "", subtype = "", subdate = "", title = "", surglvl = "", startkit = "", inventoryData = "", firefighterlevel = "", firefighterxp = "", providerlevel = "", providerxp = "", geigerlevel = "", geigerxp = "", fishermanlevel = "", fishermanxp = "";
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) {
			playerid = row[0];
			email = row[3];
			ClothBack = row[4];
			ClothHand = row[5];
			ClothFace = row[6];
			ClothShirt = row[7];
			ClothPants = row[8];
			ClothNeck = row[9];
			ClothHair = row[10];
			ClothFeet = row[11];
			ClothMask = row[12];
			ClothAnces = row[13];
			effect = row[16];
			Friends = row[17];
			AdminLevel = row[19];
			GuildName = row[20];
			JoinedGuild = row[21];
			Level = row[22];
			Experience = row[23];
			WorldOwned = row[24];
			PersonalNote = row[25];
			KillsCount = row[26];
			InventorySize = row[27];
			SkillName = row[28];
			mac = row[32];
			rid = row[33];
			sid = row[34];
			gid = row[35];
			vid = row[36];
			aid = row[37];
			ip = row[38];
			subtype = row[39];
			subdate = row[40];
			title = row[41];
			surglvl = row[42];
			startkit = row[43];
			nick = row[44];
			invis = row[45];
			ghost = row[46];
			skin = row[47];
			chatcolor = row[48];
			lastworld = row[53];
			timecursed = row[54];
			timemuted = row[55];
			surgerycooldown = row[57];
			lastnormalworld = row[58];
			inventoryData = row[59];
			firefighterlevel = row[61];
			firefighterxp = row[62];
			providerlevel = row[63];
			providerxp = row[64];
			geigercooldown = row[65];
			geigerlevel = row[66];
			geigerxp = row[67];
			fishermanlevel = row[69];
			fishermanxp = row[70];
		}
		if (startkit == "1") static_cast<PlayerInfo*>(peer->data)->startkit = true;
		if (subtype != "" && subdate != "" && subtype != "0" && subdate != "0") {
			static_cast<PlayerInfo*>(peer->data)->haveSuperSupporterName = true;
			static_cast<PlayerInfo*>(peer->data)->Subscriber = true;
			static_cast<PlayerInfo*>(peer->data)->SubscribtionEndDay = atoi(subdate.c_str());
		}
		if (timecursed != "0") {
			static_cast<PlayerInfo*>(peer->data)->isCursed = true;
			static_cast<PlayerInfo*>(peer->data)->lastCursed = atoi(timecursed.c_str());
		}
		if (timemuted != "0") {
			static_cast<PlayerInfo*>(peer->data)->taped = true;
			static_cast<PlayerInfo*>(peer->data)->isDuctaped = true;
			static_cast<PlayerInfo*>(peer->data)->cantsay = true;
			static_cast<PlayerInfo*>(peer->data)->lastMuted = atoi(timemuted.c_str());
		}
		if (surgerycooldown != "0") {
			static_cast<PlayerInfo*>(peer->data)->SurgeryCooldown = true;
			static_cast<PlayerInfo*>(peer->data)->SurgeryTime = atoi(surgerycooldown.c_str());
		}
		if (geigercooldown != "0") {
			static_cast<PlayerInfo*>(peer->data)->haveGeigerRadiation = true;
			static_cast<PlayerInfo*>(peer->data)->GeigerCooldown = true;
			static_cast<PlayerInfo*>(peer->data)->GeigerTime = atoi(geigercooldown.c_str());
		}
		string str = "UPDATE PlayerDatabase SET mac = '" + static_cast<PlayerInfo*>(peer->data)->mac + "', rid = '" + static_cast<PlayerInfo*>(peer->data)->rid + "', sid = '" + static_cast<PlayerInfo*>(peer->data)->sid + "', gid = '" + static_cast<PlayerInfo*>(peer->data)->gid + "', vid = '" + static_cast<PlayerInfo*>(peer->data)->vid + "', aid = '" + static_cast<PlayerInfo*>(peer->data)->aid + "', ip = '" + static_cast<PlayerInfo*>(peer->data)->charIP + "' WHERE username = '" + static_cast<PlayerInfo*>(peer->data)->rawName + "' LIMIT 1";
		if (mysql_query(conn, str.c_str())) {
			cout << mysql_error(conn) << endl;		
			return;
		}
		if (static_cast<PlayerInfo*>(peer->data)->registerIP.find('.') == std::string::npos) {
			char clientConnection[16];
			enet_address_get_host_ip(&peer->address, clientConnection, 16);
			string hisIp = clientConnection;
			string text = "UPDATE PlayerDatabase SET ip = '" + hisIp + "' WHERE username = '" + static_cast<PlayerInfo*>(peer->data)->rawName + "' LIMIT 1";
			if (mysql_query(conn, text.c_str())) {
				cout << mysql_error(conn) << endl;			
				return;
			}
		}
		static_cast<PlayerInfo*>(peer->data)->adminLevel = atoi(AdminLevel.c_str());
		switch (static_cast<PlayerInfo*>(peer->data)->adminLevel) {
		case 2:
			{
				static_cast<PlayerInfo*>(peer->data)->displayName = "`6@" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				static_cast<PlayerInfo*>(peer->data)->displayNamebackup = "`6@" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				break;
			}
		case 1:
			{
				static_cast<PlayerInfo*>(peer->data)->displayName = "`#@" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				static_cast<PlayerInfo*>(peer->data)->displayNamebackup = "`#@" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				break;
			}
		case 0:
			{
				static_cast<PlayerInfo*>(peer->data)->displayName = "`w" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				static_cast<PlayerInfo*>(peer->data)->displayNamebackup = "`w" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				break;
			}
		default:
			{
				enet_peer_disconnect_later(peer, 0);
				break;
			}
		}
		if (title != "" && subtype != "" && subdate != "" && subtype != "0" && subdate != "0") {
			static_cast<PlayerInfo*>(peer->data)->NickPrefix = title;
			static_cast<PlayerInfo*>(peer->data)->displayName = title + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
		}
		static_cast<PlayerInfo*>(peer->data)->cloth_back = atoi(ClothBack.c_str());
		static_cast<PlayerInfo*>(peer->data)->cloth_hand = atoi(ClothHand.c_str());
		static_cast<PlayerInfo*>(peer->data)->cloth_face = atoi(ClothFace.c_str());
		static_cast<PlayerInfo*>(peer->data)->cloth_hair = atoi(ClothHair.c_str());
		static_cast<PlayerInfo*>(peer->data)->cloth_feet = atoi(ClothFeet.c_str());
		static_cast<PlayerInfo*>(peer->data)->cloth_pants = atoi(ClothPants.c_str());
		static_cast<PlayerInfo*>(peer->data)->cloth_necklace = atoi(ClothNeck.c_str());
		static_cast<PlayerInfo*>(peer->data)->cloth_shirt = atoi(ClothShirt.c_str());
		static_cast<PlayerInfo*>(peer->data)->cloth_mask = atoi(ClothMask.c_str());
		static_cast<PlayerInfo*>(peer->data)->cloth_ances = atoi(ClothAnces.c_str());
		static_cast<PlayerInfo*>(peer->data)->guild = GuildName;
		if (JoinedGuild == "false") static_cast<PlayerInfo*>(peer->data)->joinguild = false;
		else if (JoinedGuild == "true") static_cast<PlayerInfo*>(peer->data)->joinguild = true;
		static_cast<PlayerInfo*>(peer->data)->level = atoi(Level.c_str());
		static_cast<PlayerInfo*>(peer->data)->xp = atoi(Experience.c_str());
		static_cast<PlayerInfo*>(peer->data)->notebook = PersonalNote;
		static_cast<PlayerInfo*>(peer->data)->TotalKills = atoi(KillsCount.c_str());
		static_cast<PlayerInfo*>(peer->data)->skill = SkillName;			
		static_cast<PlayerInfo*>(peer->data)->SurgerySkill = atoi(surglvl.c_str());
		static_cast<PlayerInfo*>(peer->data)->effect = atoi(effect.c_str());
		static_cast<PlayerInfo*>(peer->data)->lastworld = lastworld;
		static_cast<PlayerInfo*>(peer->data)->lastnormalworld = lastnormalworld;
		static_cast<PlayerInfo*>(peer->data)->email = email;
		static_cast<PlayerInfo*>(peer->data)->firefighterlevel = atoi(firefighterlevel.c_str());
		static_cast<PlayerInfo*>(peer->data)->firefighterxp = atoi(firefighterxp.c_str());
		static_cast<PlayerInfo*>(peer->data)->providerlevel = atoi(providerlevel.c_str());
		static_cast<PlayerInfo*>(peer->data)->providerxp = atoi(providerxp.c_str());
		static_cast<PlayerInfo*>(peer->data)->geigerlevel = atoi(geigerlevel.c_str());
		static_cast<PlayerInfo*>(peer->data)->geigerxp = atoi(geigerxp.c_str());
		static_cast<PlayerInfo*>(peer->data)->playerid = atoi(playerid.c_str());
		static_cast<PlayerInfo*>(peer->data)->fishermanlevel = atoi(fishermanlevel.c_str());
		static_cast<PlayerInfo*>(peer->data)->fishermanxp = atoi(fishermanxp.c_str());
		static_cast<PlayerInfo*>(peer->data)->registermac = mac;
		static_cast<PlayerInfo*>(peer->data)->registerrid = rid;
		static_cast<PlayerInfo*>(peer->data)->registersid = sid;
		static_cast<PlayerInfo*>(peer->data)->registergid = gid;
		static_cast<PlayerInfo*>(peer->data)->registervid = vid;
		static_cast<PlayerInfo*>(peer->data)->registeraid = aid;
		static_cast<PlayerInfo*>(peer->data)->registerIP = ip;	
		if (static_cast<PlayerInfo*>(peer->data)->cloth_back == 8552) static_cast<PlayerInfo*>(peer->data)->NickPrefix = "`4Dr";				
		stringstream ssf(Friends);
		while (ssf.good()) {
			string substr;
			getline(ssf, substr, ',');
			if (substr.size() == 0) continue;
			static_cast<PlayerInfo*>(peer->data)->friendinfo.push_back(substr);
		}
		stringstream ssfs(WorldOwned);
		while (ssfs.good()) {
			string substr;
			getline(ssfs, substr, ',');
			if (substr.size() == 0) continue;
			static_cast<PlayerInfo*>(peer->data)->worldsowned.push_back(substr);
		}
		if (skin != "0x8295C3FF") static_cast<PlayerInfo*>(peer->data)->skinColor = atoi(skin.c_str());
		if (isMod(peer) || static_cast<PlayerInfo*>(peer->data)->Subscriber) {
			if (nick != "" && isMod(peer)) {
				static_cast<PlayerInfo*>(peer->data)->isNicked = true;
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "") {
					static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + nick;
				} else {
					static_cast<PlayerInfo*>(peer->data)->displayName = nick;
				}
				static_cast<PlayerInfo*>(peer->data)->OriName = nick;
			}
			if (invis == "true") static_cast<PlayerInfo*>(peer->data)->isinv = true;
			if (ghost == "true") static_cast<PlayerInfo*>(peer->data)->canWalkInBlocks = true;
			if (chatcolor != "" && static_cast<PlayerInfo*>(peer->data)->Subscriber) {
				static_cast<PlayerInfo*>(peer->data)->chatcolor = chatcolor;
			}
		}
		static_cast<PlayerInfo*>(peer->data)->currentInventorySize = atoi(InventorySize.c_str());
		updateAllClothes(peer);
		try {
			json j = toJson(inventoryData.c_str());
			PlayerInventory inventory;
			{
				InventoryItem item;
				for (int i = 0; i < static_cast<PlayerInfo*>(peer->data)->currentInventorySize; i++) {
					int itemid = j["items"][i]["itemid"];
					int quantity = j["items"][i]["quantity"];
					if (itemid != 0 && quantity != 0) {
						item.itemCount = quantity;
						item.itemID = itemid;
						inventory.items.push_back(item);
					}
				}
			}
			SendInventory(peer, inventory);
			static_cast<PlayerInfo*>(peer->data)->inventory = inventory;
		} catch (std::exception&) {
			SendConsole("Failed to load player inventory", "ERROR");
			enet_peer_disconnect_later(peer, 0);
			return;
		}
		if (static_cast<PlayerInfo*>(peer->data)->isDuctaped) sendClothes(peer);
	}
}

inline void SendRegisterDialog(ENetPeer* peer) {
	auto p2 = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "text_scaling_string|Dirttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt|\nset_default_color|`o\nadd_label_with_icon|big|`wGet a GrowID``|left|206|\nadd_spacer|small|\nadd_textbox|By choosing a `wGrowID``, you can use a name and password to logon from any device. Your `wname`` will be shown to other players!|left|\nadd_spacer|small|\nadd_text_input|username|Name||18|\nadd_textbox|Your `wpassword`` must contain `w8 to 18 characters, 1 letter, 1 number`` and `w1 special character: @#!$^&*.,``|left|\nadd_text_input_password|password|Password||18|\nadd_text_input_password|password_verify|Password Verify||18|\nadd_textbox|Your `wemail`` will only be used for account verification and support. If you enter a fake email, you can't verify your account, recover or change your password.|left|\nadd_text_input|email|Email||64|\nadd_textbox|We will never ask you for your password or email, never share it with anyone!|left|\nend_dialog|register|Cancel|Get My GrowID!|\n"));
	auto respawnTimeout = 500;
	auto deathFlag = 0x19;
	memcpy(p2.data + 24, &respawnTimeout, 4);
	memcpy(p2.data + 56, &deathFlag, 4);
	const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2);
	delete p2.data;
}

inline void FailLogin(ENetPeer* peer, string text, bool withurl) {
	if (withurl) {
		const string dc = "https://discord.gg/VCSQ8ZhprK";
		const auto url = "action|set_url\nurl|" + dc + "\nlabel|Join Towntopia Discord\n";
		const auto data = new BYTE[5 + text.length()];
		const auto dataurl = new BYTE[5 + url.length()];
		BYTE zero = 0;
		auto type = 3;
		memcpy(data, &type, 4);
		memcpy(data + 4, text.c_str(), text.length());
		memcpy(data + 4 + text.length(), &zero, 1);
		memcpy(dataurl, &type, 4);
		memcpy(dataurl + 4, url.c_str(), url.length());
		memcpy(dataurl + 4 + url.length(), &zero, 1);
		const auto p = enet_packet_create(data, 5 + text.length(), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, p);
		const auto p3 = enet_packet_create(dataurl, 5 + url.length(), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, p3);
		delete data;
		delete dataurl;
	} else {
		const auto data = new BYTE[5 + text.length()];
		BYTE zero = 0;
		auto type = 3;
		memcpy(data, &type, 4);
		memcpy(data + 4, text.c_str(), text.length());
		memcpy(data + 4 + text.length(), &zero, 1);
		const auto p = enet_packet_create(data, 5 + text.length(), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, p);
		delete data;
	}
	static_cast<PlayerInfo*>(peer->data)->blockLogin = true;
}

inline void SendAAPNotification(const string email, const string ip, const string growid) {
	const auto text = email + " " + ip + " " + growid;
	const auto themessage = "php aap.php " + text + "";
	const auto c = themessage.c_str();
	system(c);
}

inline string GetItemCount(ENetPeer* peer, int itemid) {
	auto KiekTuri = 0;
	for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++) {
		if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == itemid && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1) {
			KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
		}
	}
	if (KiekTuri != 0) return to_string(KiekTuri);
	else return "";
}

inline void UpdateSurgeryItems(ENetPeer* peer)
{


	static_cast<PlayerInfo*>(peer->data)->SurgItem1 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem2 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem3 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem4 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem5 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem6 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem7 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem8 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem9 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem10 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem11 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem12 = 4320;
	static_cast<PlayerInfo*>(peer->data)->SurgItem13 = 4320;

	bool iscontains = false;
	vector<int> Tools;
	SearchInventoryItem(peer, 1258, 1, iscontains);
	if (iscontains)
	{
		auto KiekTuri = 0;
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
		{
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1258 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
			{
				KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
			}
		}
		//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Sponge ";

		if (KiekTuri != 0) Tools.push_back(1258);

	}
	//else Tools.push_back(4320);
	SearchInventoryItem(peer, 1260, 1, iscontains);
	if (iscontains)
	{
		auto KiekTuri = 0;
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
		{
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1260 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
			{
				KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
			}
		}
		//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Scalpel ";

		if (KiekTuri != 0) Tools.push_back(1260);

	}
	//else Tools.push_back(4320);
	SearchInventoryItem(peer, 1262, 1, iscontains);
	if (iscontains)
	{
		auto KiekTuri = 0;
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
		{
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1262 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
			{
				KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
			}
		}
		//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Anesthetic ";

		if (KiekTuri != 0) Tools.push_back(1262);

	}
	//else Tools.push_back(4320);
	SearchInventoryItem(peer, 1264, 1, iscontains);
	if (iscontains)
	{
		auto KiekTuri = 0;
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
		{
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1264 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
			{
				KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
			}
		}
		//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Antiseptic ";

		if (KiekTuri != 0) Tools.push_back(1264);

	}
	//else Tools.push_back(4320);
	SearchInventoryItem(peer, 1266, 1, iscontains);
	if (iscontains)
	{
		auto KiekTuri = 0;
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
		{
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1266 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
			{
				KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
			}
		}
		//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Antibiotics ";

		if (KiekTuri != 0 && static_cast<PlayerInfo*>(peer->data)->UnlockedAntibiotic) Tools.push_back(1266);

	}
	//else Tools.push_back(4320);
	SearchInventoryItem(peer, 1268, 1, iscontains);
	if (iscontains)
	{
		auto KiekTuri = 0;
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
		{
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1268 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
			{
				KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
			}
		}
		//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Splint ";

		if (KiekTuri != 0) Tools.push_back(1268);

	}
	//else Tools.push_back(4320);
	SearchInventoryItem(peer, 1270, 1, iscontains);
	if (iscontains)
	{
		auto KiekTuri = 0;
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
		{
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1270 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
			{
				KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
			}
		}
		//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Stitches ";

		if (KiekTuri != 0) Tools.push_back(1270);

	}
	//else Tools.push_back(4320);
	SearchInventoryItem(peer, 4308, 1, iscontains);
	if (iscontains)
	{
		auto KiekTuri = 0;
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
		{
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 4308 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
			{
				KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
			}
		}
		//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Pins ";

		if (KiekTuri != 0) Tools.push_back(4308);

	}
	//else Tools.push_back(4320);
	SearchInventoryItem(peer, 4310, 1, iscontains);
	if (iscontains)
	{
		auto KiekTuri = 0;
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
		{
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 4310 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
			{
				KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
			}
		}
		//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Transfusion ";

		if (KiekTuri != 0) Tools.push_back(4310);

	}
	//else Tools.push_back(4320);
	SearchInventoryItem(peer, 4312, 1, iscontains);
	if (iscontains)
	{
		auto KiekTuri = 0;
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
		{
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 4312 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
			{
				KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
			}
		}
		//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Defibrillator ";

		if (KiekTuri != 0 && static_cast<PlayerInfo*>(peer->data)->PatientHeartStopped) Tools.push_back(4312);

	}
	//else Tools.push_back(4320);
	SearchInventoryItem(peer, 4314, 1, iscontains);
	if (iscontains)
	{
		auto KiekTuri = 0;
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
		{
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 4314 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
			{
				KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
			}
		}
		//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Clamp ";

		if (KiekTuri != 0) Tools.push_back(4314);

	}
	//else Tools.push_back(4320);
	SearchInventoryItem(peer, 4316, 1, iscontains);
	if (iscontains)
	{
		auto KiekTuri = 0;
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
		{
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 4316 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
			{
				KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
			}
		}
		//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Ultrasound ";

		if (KiekTuri != 0) Tools.push_back(4316);

	}
	//else Tools.push_back(4320);
	SearchInventoryItem(peer, 4318, 1, iscontains);
	if (iscontains)
	{
		auto KiekTuri = 0;
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
		{
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 4318 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
			{
				KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
			}
		}
		//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Lab Kit";

		if (KiekTuri != 0 && !static_cast<PlayerInfo*>(peer->data)->UnlockedAntibiotic) Tools.push_back(4318);

	}

	if (static_cast<PlayerInfo*>(peer->data)->FixIt) Tools.push_back(1296);

	//else Tools.push_back(4320);

	for (int i = 0; i < Tools.size(); i++)
	{
	
		if (i == 0) static_cast<PlayerInfo*>(peer->data)->SurgItem1 = Tools[i];
		if (i == 1) static_cast<PlayerInfo*>(peer->data)->SurgItem2 = Tools[i];
		if (i == 2) static_cast<PlayerInfo*>(peer->data)->SurgItem3 = Tools[i];

		if (i == 3) static_cast<PlayerInfo*>(peer->data)->SurgItem4 = Tools[i];
		if (i == 4) static_cast<PlayerInfo*>(peer->data)->SurgItem5 = Tools[i];
		if (i == 5) static_cast<PlayerInfo*>(peer->data)->SurgItem6 = Tools[i];

		if (i == 6) static_cast<PlayerInfo*>(peer->data)->SurgItem7 = Tools[i];
		if (i == 7) static_cast<PlayerInfo*>(peer->data)->SurgItem8 = Tools[i];
		if (i == 8) static_cast<PlayerInfo*>(peer->data)->SurgItem9 = Tools[i];

		if (i == 9) static_cast<PlayerInfo*>(peer->data)->SurgItem10 = Tools[i];
		if (i == 10) static_cast<PlayerInfo*>(peer->data)->SurgItem11 = Tools[i];
		if (i == 11) static_cast<PlayerInfo*>(peer->data)->SurgItem12 = Tools[i];

		if (i == 12) static_cast<PlayerInfo*>(peer->data)->SurgItem13 = Tools[i];

	}
	
}

inline void showWrong(ENetPeer* peer, string listFull, string itemFind)
{
	Player::OnDialogRequest(peer, "add_label_with_icon|big|`9Find item: " + itemFind + "``|left|3146|\n" + listFull + "add_textbox|Enter a word below to find the item|\nadd_text_input|item|Item Name||30|\nend_dialog|findid|Cancel|Find the item!|\n");
}
