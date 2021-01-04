#pragma once
#include "stdafx.h"
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <locale>
#include <regex>
#include <sstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <experimental/filesystem>
#include "json.hpp"
#ifdef _WIN32
#include <windows.h>
typedef __int8 __int8_t;
typedef __int16 __int16_t;
#elif __APPLE__ || __linux__
typedef unsigned int DWORD;
#endif
typedef unsigned char BYTE;

struct Crystal
{
	string name;
	int probability;

	Crystal(const string s, const int p) : name(s), probability(p)
	{
	}
};

struct WorldItem
{
	__int16_t foreground = 0;
	__int16_t background = 0;
	int displayblock = 0;
	int breakLevel = 0;
	long long int breakTime = 0;
	string sign = "";
	bool water = false;
	bool rotatedLeft = false;
	bool fire = false;
	bool glue = false;
	bool red = false;
	bool green = false;
	bool flipped = false;
	bool blue = false;
	int intdata = 0;
	string label = "";
	string destWorld = "";
	string destId = "";
	string currId = "";
	string password = "";
	bool activated = false;
	int yellowGems = 0;
	int blueGems = 0;
	int redGems = 0;
	int greenGems = 0;
	int purpleGems = 0;

	int clothHair = 0;
	int clothHead = 0;
	int clothMask = 0;
	int clothHand = 0;
	int clothNeck = 0;
	int clothShirt = 0;
	int clothPants = 0;
	int clothFeet = 0;
	int clothBack = 0;

	/*magplant*/
	int mid = 0;
	int mc = 0;
	bool rm = false;

	/*vending*/
	bool destroy = false;
	int vdraw = 0;
	int vid = 0;
	int vprice = 0;
	int vcount = 0;
	int breakstate = 0;
	int breakbotstate = 0;
	int placestate = 0;

	/*hmonitor*/
	string monitorname = "";
	bool monitoronline = false;

	/*entrance*/
	bool opened = false;
	/*seedai*/
	bool spliced = false;
	int growtime = 0;
	int fruitcount = 0;
	/*rocks*/
	int evolvestage = 0;
	bool atnaujino = false;
	int firehousestate = 0;



};

struct DroppedItem
{
	int id;
	int uid;
	int count;
	float x;
	float y;
};

struct WorldInfo
{
	int width = 100;
	int height = 60;
	int publicBlock = -1;
	int weather = 4;
	int droppedCount = 0;
	float rating = 0;
	int entrylevel = 1;
	bool silence = false;
	bool isNuked = false;
	bool isPublic = false;
	bool allowMod = false;
	bool DisableDrop = false;
	bool rainbow = false;
	bool isEvent = true;
	bool worker = false;
	string name = "TEST";
	string owner = "";
	string category = "None";
	WorldItem* items;
	vector<DroppedItem> droppedItems;
	vector<string> accessed;
	string notification = "";
};

struct AWorld
{
	WorldInfo* ptr;
	WorldInfo info;
	int id;
};

struct TileExtra
{
	int packetType;
	int characterState;
	float objectSpeedX;
	int punchX;
	int punchY;
	int charStat;
	int blockid;
	int visual;
	int signs;
	int backgroundid;
	int displayblock;
	int time;
	int netID;
	int weatherspeed;
	int bpm;
};

struct BlockVisual
{
	int packetType;
	int characterState;
	int punchX;
	int punchY;
	float x;
	float y;
	int plantingTree;
	float XSpeed;
	float YSpeed;
	int charStat;
	int blockid;
	int visual;
	int signs;
	int backgroundid;
	int displayblock;
	int time;
	int netID;
};

inline void decodeName(char* src, const int len, const int itemID, char* dest)
{
	const char key[] = "PBG892FXX982ABC*";
	for (auto i = 0; i < len; i++)
	{
		dest[i] = src[i] ^ key[(i + itemID) % 16];
	}
}

struct itemDataStruct
{
	string name;
	string texturefile;
	string audiofile;
	int id;
	uint8_t editableType;
	uint8_t category;
	uint8_t type;
	uint8_t solid;
	uint16_t rarity;
	uint32_t color1;
	uint32_t color2;
	uint8_t textureX;
	uint8_t textureY;
	uint8_t textureType;
	uint8_t hardness;
	uint16_t audioVol;
	uint32_t texturehash;
	uint32_t audiohash;
	uint8_t seedBase;
	uint8_t seedOverlay;
	uint8_t treeBase;
	uint8_t treeOverlay;
	int punchEffect = 0;
};

enum BlockTypes
{
	FOREGROUND,
	BACKGROUND,
	CONSUMABLE,
	SEED,
	PAIN_BLOCK,
	BEDROCK,
	MAIN_DOOR,
	SIGN,
	DOOR,
	CLOTHING,
	FIST,
	WRENCH,
	CHECKPOINT,
	LOCK,
	GATEWAY,
	TREASURE,
	WEATHER,
	TRAMPOLINE,
	TOGGLE_FOREGROUND,
	CHEMICAL_COMBINER,
	SWITCH_BLOCK,
	SFX_FOREGROUND,
	RANDOM_BLOCK,
	PORTAL,
	PLATFORM,
	MAILBOX,
	MAGIC_EGG,
	CRYSTAL,
	GEMS,
	DEADLY,
	CHEST,
	FACTION,
	BULLETIN_BOARD,
	BOUNCY,
	ANIM_FOREGROUND,
	COMPONENT,
	SUCKER,
	FISH,
	STEAM,
	GROUND_BLOCK,
	DISPLAY,
	STORAGE,
	VENDING,
	DONATION,
	PHONE,
	SEWINGMACHINE,
	CRIME_VILLAIN,
	PROVIDER,
	UNKNOWN
};

#define Property_Zero 0
#define Property_NoSeed 1
#define Property_Dropless 2
#define Property_Beta 4
#define Property_Mod 8
#define Property_Chemical 12
#define Property_Untradable 16
#define Property_Wrenchable 32
#define Property_MultiFacing 64
#define Property_Permanent 128
#define Property_AutoPickup 256
#define Property_WorldLock 512
#define Property_NoSelf 1024
#define Property_RandomGrow 2048
#define Property_Public 4096
#define Property_Foreground 8192
#define Property_NoBlock 16384

class WorldDB
{
public:
	WorldInfo get(string name);
	AWorld get2(string name);
	static void flush(WorldInfo info, MYSQL*);
	void saveAll();
	void remove2(string name);
	vector<WorldInfo> getRandomWorlds();
	WorldDB();
private:
	vector<WorldInfo> worlds;
};

inline WorldDB::WorldDB()
{
}

inline void GenerateGrowaloneLikeWorld(WorldInfo* world, const int width, const int height, const int dirtType = 2, const int lavaType = 4, const int mainDoorType = 6, const int bedrockType = 8, const int rockType = 10, const int caveBackgroundType = 14, const int wmachineid = 0, const int deco1Id = 0, const int deco2Id = 0, const int id = 0)
{
	//SendConsole("Generating new world (GenerateGrowaloneLikeWorld) details: width(" + to_string(width) + ") height(" + to_string(height) + ") dirtType(" + to_string(dirtType) + ") lavaType(" + to_string(lavaType) + ") mainDoorType(" + to_string(mainDoorType) + ") bedrockType(" + to_string(bedrockType) + ") rockType(" + to_string(rockType) + ") caveBackgroundType(" + to_string(caveBackgroundType) + ") wmachineid(" + to_string(wmachineid) + ") deco1Id(" + to_string(deco1Id) + ") deco2Id(" + to_string(deco2Id) + ") id(" + to_string(id) + ")", "INFO");
	world->weather = wmachineid;
	for (auto i = 0; i < world->width * world->height; i++)
	{
		world->items[i].foreground = 0;
	}
	const auto offset = new int[width];
	const auto offset2 = new int[width];
	offset[0] = (height - 60 < 0) ? -10 : height - 60;
	offset2[0] = offset[0] < 0 ? -10 : offset[0];
	auto settile = [](WorldInfo* w, const int x, const int y, const int id)
	{
		if (x < w->width && x >= 0 && y < w->height && y >= 0)
			w->items[x + y * w->width].foreground = id;
	};
	auto settilebg = [](WorldInfo* w, const int x, const int y, const int id)
	{
		if (x < w->width && x >= 0 && y < w->height && y >= 0)
			w->items[x + y * w->width].background = id;
	};
	auto gettile = [](WorldInfo* w, const int x, const int y)
	{
		if (x < w->width && x >= 0 && y < w->height && y >= 0)
			return w->items[x + y * w->width].foreground;
		return static_cast<short>(0);
	};
	for (auto i = 1; i < width; i++)
	{
		offset[i] = (height - 60 < 0) ? -10 : height - 60;
		const auto rnd = rand() % 30 - 10;
		if (rnd < -2)
			offset[i] = offset[i - 1] - 1; // rise
		else if (rnd > 11)
			offset[i] = offset[i - 1] + 1; // fall
		else
			offset[i] = offset[i - 1]; // no change
		offset2[i] = offset[i] < 0 ? -10 : offset[i];
	}
	for (auto j = 0; j < width; j++)
	{
		for (auto k = 26 + offset[j]; k < height - 5; k++)
		{
			settile(world, j, k, dirtType);
			settilebg(world, j, k, caveBackgroundType);
			const auto renrnd = rand() % 12;
			if (renrnd > 10)
				settile(world, j, k, rockType);
		}
		settile(world, j, 26 + offset[j], dirtType);
		settilebg(world, j, 26 + offset[j], caveBackgroundType);
		settile(world, j, height - 6, bedrockType);
		settile(world, j, height - 5, bedrockType);
		settile(world, j, height - 4, bedrockType);
		settile(world, j, height - 3, bedrockType);
		settile(world, j, height - 2, bedrockType);
		settile(world, j, height - 1, bedrockType);
		settilebg(world, j, height - 6, caveBackgroundType);
		settilebg(world, j, height - 5, caveBackgroundType);
		settilebg(world, j, height - 4, caveBackgroundType);
		settilebg(world, j, height - 3, caveBackgroundType);
		settilebg(world, j, height - 2, caveBackgroundType);
		settilebg(world, j, height - 1, caveBackgroundType);
	}
	for (auto srg = height - 10; srg < height - 6; srg++)
	{
		for (auto dhk = 0; dhk < width; dhk++)
		{
			const auto djkf = rand() % 2;
			if (djkf == 1)
			{
				settile(world, dhk, srg, lavaType);
			}
		}
	}
	if (id & BlastProperties_WaterLevelD2)
	{
		for (auto i = 0; i < width; i++)
		{
			for (auto j = deco2Id; j < height; j++)
			{
				if (gettile(world, i, j) == 0)
				{
					if (i < world->width && i >= 0 && j < world->height && j >= 0)
						world->items[i + j * world->width].water = true;
				}
			}
		}
	}
	else if (id & BlastProperties_RandomDeco1)
	{
		const auto deco1Count = rand() % 25 + 3;
		for (auto i = 0; i < deco1Count; i++)
		{
			const auto a = rand() % width;
			settile(world, a, 25 + offset[a], deco1Id);
		}
	}
	else if (id & BlastProperties_RandomDeco2)
	{
		const auto deco2Count = rand() % 25 + 3;
		for (auto i = 0; i < deco2Count; i++)
		{
			const auto a = rand() % width;
			settile(world, a, 25 + offset[a], deco2Id);
		}
	}
regenerate:
	const auto mainDoorX = (rand() % (width - 4)) + 2;
	auto f = 25 + offset[mainDoorX];
	while (gettile(world, mainDoorX, f) != 0)
	{
		f--;
		if (f < 0) goto regenerate;
	}
	settile(world, mainDoorX, f, mainDoorType);
	settile(world, mainDoorX, f + 1, bedrockType);
	delete offset;
	delete offset2;
}

inline void GenerateRegularWorld(WorldInfo* world, const int width, const int height, const int dirtType = 2, const int lavaType = 4, const int mainDoorType = 6, const int bedrockType = 8, const int rockType = 10, const int caveBackgroundType = 14, const int machineId = 0)
{
	//SendConsole("Generating new world (GenerateRegularWorld) details: width(" + to_string(width) + ") height(" + to_string(height) + ") dirtType(" + to_string(dirtType) + ") lavaType(" + to_string(lavaType) + ") mainDoorType(" + to_string(mainDoorType) + ") bedrockType(" + to_string(bedrockType) + ") rockType(" + to_string(rockType) + ") caveBackgroundType(" + to_string(caveBackgroundType) + ") machineId(" + to_string(machineId) + ")", "INFO");
	world->weather = machineId;
	const auto mainDoorX = (rand() % (world->width - 4)) + 2;
	for (auto i = 0; i < world->width * world->height; i++)
	{
		world->items[i].foreground = 0;
	}
	for (auto i = 0; i < world->width * world->height; i++)
	{
		if (i >= 3800 && i < 5400 && !(rand() % 50))
		{
			world->items[i].foreground = rockType;
		}
		else if (i >= 3700 && i < 5400)
		{
			if (i > 5000)
			{
				const auto m = rand() % 8;
				if (m < 3)
				{
					world->items[i].foreground = lavaType;
				}
				else
				{
					world->items[i].foreground = dirtType;
				}
			}
			else
			{
				world->items[i].foreground = dirtType;
			}
		}
		else if (i >= 5400)
		{
			world->items[i].foreground = bedrockType;
		}
		if (i == 3600 + mainDoorX)
		{
			world->items[i].foreground = mainDoorType;
		}
		if (i == 3700 + mainDoorX)
		{
			world->items[i].foreground = bedrockType;
		}
		if (i >= 3700)
		{
			world->items[i].background = caveBackgroundType;
		}
	}
}

inline WorldInfo generateUranusWorld(const string name, const int width, const int height) {
	WorldInfo world;
	world.name = name;
	world.isNuked = false;
	world.width = width;
	world.height = height;
	world.weather = 17;
	const auto mainDoorX = (rand() % (world.width - 4)) + 2;
	world.items = new WorldItem[world.width * world.height];
	const auto treasure = (rand() % 4400);
	for (auto i = 0; i < world.width * world.height; i++)
	{
		if (i >= 100 && i < 4470 && !(rand() % 99))
		{
			world.items[i].foreground = 9440;
		}
		else if (i == treasure)
		{
			world.items[i].foreground = 7628;
		}
		else if (i > 1200 && i < 4470 && !(rand() % 99))
		{
			world.items[i].foreground = 9442;
		}
		else if (i > 2500 && i < 4470 && !(rand() % 99))
		{
			world.items[i].foreground = 7960;
		}
		else if (i >= 0 && i < 4500)
		{
			world.items[i].foreground = 1132;
		}
		if (i >= 0 && i <= 29)
		{
			world.items[i].foreground = 8;
		}
		if (i >= 0)
		{
			world.items[i].background = 9438;
		}
		if (i == 550 + mainDoorX)
		{
			world.items[i].foreground = 6;
		}
		if (i >= 1000 && i <= 1030)
		{
			world.items[i].foreground = 9444;
		}
		if (i >= 4470)
		{
			world.items[i].foreground = 8;
		}
	}
	return world;
}

inline WorldInfo CreateWorld(const string name, const int width, const int height, const int dirtType = 2, const int lavaType = 4, const int mainDoorType = 6, const int bedrockType = 8, const int rockType = 10, const int caveBackgroundType = 14) {
	if (usedgenworld == true) {
		usedgenworld = false;
		const auto width3 = genwidth;
		const auto height3 = genheight;
		const auto dirttype3 = genforeground;
		const auto bedrocktype3 = genbedrock;
		const auto cavebackgroundtype3 = genbackground;
		WorldInfo world;
		world.name = name;
		world.width = width;
		world.height = height;
		world.items = new WorldItem[world.width * world.height];
		GenerateRegularWorld(&world, width3, height3, dirttype3, lavaType, mainDoorType, bedrocktype3, rockType, cavebackgroundtype3);
		genwidth = 0;
		genheight = 0;
		genforeground = 0;
		genbedrock = 0;
		genbackground = 0;
		return world;
	} else {
		WorldInfo world;
		world.name = name;
		world.width = width;
		world.height = height;
		world.items = new WorldItem[world.width * world.height];
		GenerateGrowaloneLikeWorld(&world, width, height, dirtType, lavaType, mainDoorType, bedrockType, rockType, caveBackgroundType, 0, 0, 0, BlastProperties_RandomDeco1);
		return world;
	}
}

inline int PlayerDB::guildRegister(ENetPeer* peer, string guildName, string guildStatement, string guildFlagfg, string guildFlagbg)
{
	SendConsole("Registering new guild (guildRegister) details: guildName(" + guildName + ") guildStatement(" + guildStatement + ") guildFlagfg(" + guildFlagfg + ") guildFlagbg(" + guildFlagbg + ")", "INFO");
	auto uname = guildName;
	if (guildName.find(" ") != string::npos || guildName.find(".") != string::npos || guildName.find(",") != string::npos || guildName.find("?") != string::npos || guildName.find("@") != string::npos || guildName.find("[") != string::npos || guildName.find("]") != string::npos || guildName.find("#") != string::npos || guildName.find("<") != string::npos || guildName.find(">") != string::npos || guildName.find(":") != string::npos || guildName.find("{") != string::npos || guildName.find("}") != string::npos || guildName.find("|") != string::npos || guildName.find("+") != string::npos || guildName.find("_") != string::npos || guildName.find("~") != string::npos || guildName.find("-") != string::npos || guildName.find("!") != string::npos || guildName.find("$") != string::npos || guildName.find("%") != string::npos || guildName.find("^") != string::npos || guildName.find("&") != string::npos || guildName.find("`") != string::npos || guildName.find("*") != string::npos || guildName.find("(") != string::npos || guildName.find(")") != string::npos || guildName.find("=") != string::npos || guildName.find("'") != string::npos || guildName.find(";") != string::npos || guildName.find("/") != string::npos)
	{
		return -1;
	}
	/*if (guildName == "prn" || guildName == "con" || guildName == "aux" || guildName == "nul" || guildName == "com1" || guildName == "com2" || guildName == "com3" || guildName == "com4" || guildName == "com5" || guildName == "com6" || guildName == "com7" || guildName == "com8" || guildName == "com9" || guildName == "lpt1" || guildName == "lpt2" || guildName == "lpt3" || guildName == "lpt4" || guildName == "lpt5" || guildName == "lpt6" || guildName == "lpt7" || guildName == "lpt8" || guildName == "lpt9")
	{
		return -1;
	}*/
	toUpperCase(uname);
	if (guildName.length() < 3)
	{
		return -2;
	}
	if (guildName.length() > 15)
	{
		return -3;
	}
	if (guildFlagfg.size() > 5 || guildFlagfg.size() < 0 || guildFlagbg.size() > 5 || guildFlagbg.size() < 0)
	{
		autoBan(peer, true, 99999, "tried to crash with guild reg things");
		return -1;
	}
	int fg;
	int bg;
	try
	{
		fg = stoi(guildFlagfg);
	}
	catch (...)
	{
		return -6;
	}
	try
	{
		bg = stoi(guildFlagbg);
	}
	catch (...)
	{
		return -5;
	}
	if (fg > maxItems || bg > maxItems)
	{
		return -1;
	}
	auto fixedguildName = PlayerDB::getProperName(guildName);
	std::ifstream ifs("guilds/" + fixedguildName + ".json");
	if (ifs.is_open())
	{
		return -4;
	}
	return 1;
}

AWorld WorldDB::get2(string name) {
	AWorld ret;
	name = getStrUpper(name);
	for (int i = 0; i < worlds.size(); i++) {
		if (i >= worlds.size()) {
			SendConsole("worlds.size() was larger than loop size", "ERROR");
			AWorld ret;
			ret.id = -1;
			return ret;
		} else {
			if (worlds.at(i).name == name) {
				ret.id = i;
				ret.info = worlds.at(i);
				ret.ptr = &worlds.at(i);
				return ret;
			}
		}
	}
	WorldLoader = mysql_init(nullptr);
	WorldLoader = mysql_real_connect(WorldLoader, ip, user, pass, database, 0, nullptr, 0);
	MYSQL_ROW WorldRows;
	string rainbows, worldname, owner, isNuked, isPublic, weather, width, height, TileData, DropData, publicBlock, silence, noclip, disabledrop, category, rating, entrylevel;
	string q = "SELECT * FROM WorldDatabase WHERE name = '" + name + "' LIMIT 1";
	if (mysql_query(WorldLoader, q.c_str())) {
		cout << mysql_error(WorldLoader) << endl;
	}
	WorldLoaderResponse = mysql_store_result(WorldLoader);
	while (WorldRows = mysql_fetch_row(WorldLoaderResponse)) {
		worldname = WorldRows[1];
		owner = WorldRows[2];
		isNuked = WorldRows[4];
		isPublic = WorldRows[5];
		weather = WorldRows[6];
		publicBlock = WorldRows[7];
		silence = WorldRows[8];
		noclip = WorldRows[9];
		disabledrop = WorldRows[10];
		category = WorldRows[11];
		rating = WorldRows[12];
		entrylevel = WorldRows[13];
		width = WorldRows[14];
		height = WorldRows[15];
		TileData = WorldRows[16];
		DropData = WorldRows[17];
		rainbows = WorldRows[18];
	}
	if (WorldLoaderResponse) mysql_free_result(WorldLoaderResponse);
	if (worldname.size() != 0) {
		WorldInfo info;
		info.name = worldname;
		info.owner = owner;
		if (isNuked == "false") info.isNuked = false;
		else if (isNuked == "true") info.isNuked = true;
		if (isPublic == "false") info.isPublic = false;
		else if (isPublic == "true") info.isPublic = true;
		if (silence == "false") info.silence = false;
		else if (silence == "true") info.silence = true;
		info.allowMod = false;
		if (disabledrop == "false") info.DisableDrop = false;
		else if (disabledrop == "true") info.DisableDrop = true;
		if (rainbows == "false") info.rainbow = false;
		else if (rainbows == "true") info.rainbow = true;
		info.weather = atoi(weather.c_str());
		info.category = category;
		//info.rating = stof(rating);
		info.rating = 0;
		info.entrylevel = atoi(entrylevel.c_str());
		info.width = atoi(width.c_str());
		info.height = atoi(height.c_str());
		info.publicBlock = atoi(publicBlock.c_str());
		auto droppedobjects = toJson(DropData.c_str());
		for (int i = 0; i < droppedobjects.size(); i++) {
			DroppedItem di;
			di.count = droppedobjects[i]["c"].get<BYTE>();
			di.id = droppedobjects[i]["id"].get<short>();
			di.x = droppedobjects[i]["x"].get<int>();
			di.y = droppedobjects[i]["y"].get<int>();
			di.uid = droppedobjects[i]["uid"].get<int>();
			info.droppedCount = di.uid + 1;
			info.droppedItems.push_back(di);
		}
		auto tiles = toJson(TileData.c_str());
		auto square = info.width * info.height;
		info.items = new WorldItem[square];
		for (int i = 0; i < square; i++) {
			info.items[i].foreground = tiles[i]["fg"].get<int>();
			info.items[i].background = tiles[i]["bg"].get<int>();
			info.items[i].flipped = tiles[i]["r"].get<bool>();
			info.items[i].sign = tiles[i]["s"].get<string>();
			info.items[i].intdata = tiles[i]["int"].get<int>();
			info.items[i].label = tiles[i]["l"].get<string>();
			info.items[i].destWorld = tiles[i]["d"].get<string>();
			info.items[i].destId = tiles[i]["did"].get<string>();
			info.items[i].currId = tiles[i]["crid"].get<string>();
			info.items[i].password = tiles[i]["p"].get<string>();
			info.items[i].mid = tiles[i]["mid"].get<int>();
			info.items[i].mc = tiles[i]["mc"].get<int>();
			info.items[i].rm = tiles[i]["rm"].get<bool>();
			info.items[i].opened = tiles[i]["open"].get<bool>();
			info.items[i].vcount = tiles[i]["vc"].get<int>();
			info.items[i].vdraw = tiles[i]["vd"].get<int>();
			info.items[i].vid = tiles[i]["vid"].get<int>();
			info.items[i].vprice = tiles[i]["vp"].get<int>();
			info.items[i].monitorname = tiles[i]["how"].get<string>();
			info.items[i].monitoronline = tiles[i]["mon"].get<bool>();
			info.items[i].spliced = tiles[i]["spl"].get<bool>();
			info.items[i].activated = tiles[i]["a"].get<bool>();
			info.items[i].growtime = tiles[i]["sgt"].get<int>();
			info.items[i].fruitcount = tiles[i]["sfc"].get<int>();
			info.items[i].water = tiles[i]["w"].get<bool>();
			info.items[i].fire = tiles[i]["f"].get<bool>();
			info.items[i].red = tiles[i]["red"].get<int>();
			info.items[i].green = tiles[i]["gre"].get<int>();
			info.items[i].blue = tiles[i]["blu"].get<int>();
			info.items[i].evolvestage = tiles[i]["es"].get<int>();
		}
		worlds.push_back(info);
		mysql_close(WorldLoader);
		ret.id = worlds.size() - 1;
		ret.info = info;
		ret.ptr = &worlds.at(worlds.size() - 1);
		return ret;
	} else {
		if (usedtinyblast == true) {
			usedtinyblast = false;
			WorldInfo info = CreateWorld(name, 60, 30);
			worlds.push_back(info);
			mysql_close(WorldLoader);
			ret.id = worlds.size() - 1;
			ret.info = info;
			ret.ptr = &worlds.at(worlds.size() - 1);
			return ret;
		} else if (usedlargeblast == true) {
			usedlargeblast = false;
			WorldInfo info = CreateWorld(name, 150, 100);
			worlds.push_back(info);
			mysql_close(WorldLoader);
			ret.id = worlds.size() - 1;
			ret.info = info;
			ret.ptr = &worlds.at(worlds.size() - 1);
			return ret;
		} else if (usedthermoblast == true) {
			usedthermoblast = false;
			WorldInfo info = CreateWorld(name, 100, 60, 0, 0, 6, 8, 0, 0);
			worlds.push_back(info);
			mysql_close(WorldLoader);
			ret.id = worlds.size() - 1;
			ret.info = info;
			ret.ptr = &worlds.at(worlds.size() - 1);
			return ret;
		} else {
			WorldInfo info = CreateWorld(name, 100, 60);
			worlds.push_back(info);
			mysql_close(WorldLoader);
			ret.id = worlds.size() - 1;
			ret.info = info;
			ret.ptr = &worlds.at(worlds.size() - 1);
			return ret;
		}
	}
}

inline WorldInfo WorldDB::get(const string name) {
	AWorld worldas = this->get2(name);
	if (worldas.id != -1) {
		return worldas.info;
	} else {
		cout << "error" << endl;
		WorldInfo info;
		AWorld ret;
		info.name = "error";
		ret.id = worlds.size() - 1;
		ret.info = info;
		ret.ptr = &worlds.at(worlds.size() - 1);
		return ret.info;	
	}
}

inline void WorldDB::flush(WorldInfo info, MYSQL*) {
	using namespace std::chrono;
	int timeS = (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
 	MYSQL_ROW WorldRows;
	string query = "SELECT EXISTS(SELECT 1 FROM WorldDatabase WHERE name ='" + info.name + "' LIMIT 1)";
	mysql_query(WorldSaver, query.c_str());
	WorldSaverResponse = mysql_store_result(WorldSaver);
	string Exists = "0";
	WorldRows = mysql_fetch_row(WorldSaverResponse);
	Exists = WorldRows[0];
	if (WorldSaverResponse) mysql_free_result(WorldSaverResponse);
	json WorldDropped = json::array();
	const int square = info.width * info.height;
	for (int i = 0; i < info.droppedItems.size(); i++) {
		json droppedJ;
		droppedJ["c"] = static_cast<BYTE>(info.droppedItems[i].count);
		droppedJ["id"] = static_cast<short>(info.droppedItems[i].id);
		droppedJ["x"] = info.droppedItems[i].x;
		droppedJ["y"] = info.droppedItems[i].y;
		droppedJ["uid"] = info.droppedItems[i].uid;
		WorldDropped.push_back(droppedJ);
	}
	json WorldTiles = json::array();
	for (int i = 0; i < square; i++) {
		json tile;
		tile["fg"] = info.items[i].foreground;
		tile["bg"] = info.items[i].background;
		tile["s"] = info.items[i].sign;
		tile["r"] = info.items[i].flipped;
		tile["int"] = info.items[i].intdata;
		tile["l"] = info.items[i].label;
		tile["d"] = info.items[i].destWorld;
		tile["did"] = info.items[i].destId;
		tile["crid"] = info.items[i].currId;
		tile["p"] = info.items[i].password;
		tile["mid"] = info.items[i].mid;
		tile["mc"] = info.items[i].mc;
		tile["rm"] = info.items[i].rm;
		tile["open"] = info.items[i].opened;
		tile["vc"] = info.items[i].vcount;
		tile["vd"] = info.items[i].vdraw;
		tile["vid"] = info.items[i].vid;
		tile["vp"] = info.items[i].vprice;
		tile["how"] = info.items[i].monitorname;
		tile["mon"] = info.items[i].monitoronline;
		tile["spl"] = info.items[i].spliced;
		tile["a"] = info.items[i].activated;
		tile["sgt"] = info.items[i].growtime;
		tile["sfc"] = info.items[i].fruitcount;
		tile["w"] = info.items[i].water;
		tile["f"] = info.items[i].fire;
		tile["red"] = info.items[i].red;
		tile["gre"] = info.items[i].green;
		tile["blu"] = info.items[i].blue;
		tile["es"] = info.items[i].evolvestage;
		WorldTiles.push_back(tile);
	}
	stringstream WorldTilesConvert;
	WorldTilesConvert << WorldTiles;
	string TileData = WorldTilesConvert.str();
	stringstream WorldDroppedConvert;
	WorldDroppedConvert << WorldDropped;
	string DropData = WorldDroppedConvert.str();
	if (Exists == "0") {
		string query3 = "INSERT INTO WorldDatabase(name, owner, admins, nuked, public, weather, publicBlock, silence, noclip, disableDrop, category, rating, entrylevel, width, height, tiles, dropped, rainbow) VALUES ('" + info.name + "', '" + info.owner + "', '', '" + (info.isNuked ? "true" : "false") + "', '" + (info.isPublic ? "true" : "false") + "', '" + to_string(info.weather) + "', '" + to_string(info.publicBlock) + "', '" + (info.silence ? "true" : "false") + "', '" + (info.allowMod ? "true" : "false") + "', '" + (info.DisableDrop ? "true" : "false") + "', '" + info.category + "', '" + to_string(info.rating) + "', '" + to_string(info.entrylevel) + "', '" + to_string(info.width) + "', '" + to_string(info.height) + "', '" + TileData + "', '" + DropData + "', '" + (info.rainbow ? "true" : "false") + "')";
		mysql_query(WorldSaver, query3.c_str());
	} else {
		string query3 = "UPDATE WorldDatabase SET name = '" + info.name + "', owner = '" + info.owner + "', admins = '', nuked = '" + (info.isNuked ? "true" : "false") + "', public = '" + (info.isPublic ? "true" : "false") + "', weather = '" + to_string(info.weather) + "', publicBlock = '" + to_string(info.publicBlock) + "', silence = '" + (info.silence ? "true" : "false") + "', noclip = '" + (info.allowMod ? "true" : "false") + "', disableDrop = '" + (info.DisableDrop ? "true" : "false") + "', category = '" + info.category + "', rating = '" + to_string(info.rating) + "', entrylevel = '" + to_string(info.entrylevel) + "', width = '" + to_string(info.width) + "', height = '" + to_string(info.height) + "', tiles = '" + TileData + "', dropped = '" + DropData + "', rainbow = '" + (info.rainbow ? "true" : "false") + "' WHERE name = '" + info.name + "' LIMIT 1";
		mysql_query(WorldSaver, query3.c_str());
	}
	int timeE = (duration_cast<seconds>(system_clock::now().time_since_epoch())).count();
	SendConsole("Saved world " + info.name + " took " + to_string(timeS - timeE) + " seconds", "SAVE");
}

inline int getPlayersCountInWorldEvent(WorldInfo world, string name) {
	if (world.items == nullptr) {
		cout << "nullptr case 369" << endl;
		return 0;
	}
	int count = 0;
	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (currentPeer->data == nullptr || currentPeer->data == NULL) {
			SendConsole("currentPeer was nullptr", "ERROR");
			continue;
		}
		if (static_cast<PlayerInfo*>(currentPeer->data)->currentWorld == name && !static_cast<PlayerInfo*>(currentPeer->data)->isinv) count++;
	}
	if (count == 0 && !GlobalMaintenance) {
		if (frozenworlds.size() != 0) {
			if (find(frozenworlds.begin(), frozenworlds.end(), name) != frozenworlds.end()) {
				return 0;
			}
		}
		for (int i = 0; i < world.width * world.height; i++) {
			if (world.items == nullptr) {
				cout << "was nullptr values" << endl;
				return 0;
			}
			if (world.width < 30 || world.height < 30 || world.droppedCount < 0 || world.entrylevel <= 0 || world.silence < 0 || world.isNuked < 0) {
				SendConsole("world corrupted structure", "ERROR");
				return 0;
			}
			if (world.width > 300 || world.height > 300) {
				SendConsole("world corrupter strucute", "ERROR");
				return 0;
			}
			if (frozenworlds.size() != 0) {
				if (find(frozenworlds.begin(), frozenworlds.end(), name) != frozenworlds.end()) {
					return 0;
				}
			}
			auto x = (i % world.width);
			auto y = (i / world.width);
			if (x == 0 || y == 0) continue;
			cout << "getworldevent x " + to_string(x) << endl;
			cout << "getworldevent y " + to_string(y) << endl;
			if (world.items[i].foreground == 10430 && world.items[i].activated) { 
				return 1;
			}
		}
	}
	return count;
}

inline int getPlayersCountInWorld(const string name)
{
	auto count = 0;
	for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (static_cast<PlayerInfo*>(currentPeer->data)->isinv == false)
		{
			if (static_cast<PlayerInfo*>(currentPeer->data)->currentWorld == name)
			{
				count++;
			}
		}
	}
	return count;
}

inline int getPlayersCountInWorldVSave(WorldInfo world, const string name) {
	auto count = 0;
	for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (static_cast<PlayerInfo*>(currentPeer->data)->currentWorld == name) {
			count++;
		}
	}
	if (count == 0 && !GlobalMaintenance) {
		for (auto i = 0; i < world.width * world.height; i++) {
			if (world.items[i].foreground == 10430 && world.items[i].activated) { 
				count = 1;
				break;
			}
		}
	}
	return count;
}

inline void WorldDB::saveAll() {
	//cout << "con to worldsaver" << endl;
	WorldSaver = mysql_init(nullptr);
	WorldSaver = mysql_real_connect(WorldSaver, ip, user, pass, database, 0, nullptr, 0);
	for (int i = 0; i < worlds.size(); i++) {
		if (i >= worlds.size()) {
			SendConsole("worlds.size() was larger than loop size (c963)", "ERROR");
			continue;
		}
		if (getPlayersCountInWorldVSave(worlds[i], worlds[i].name) <= 0 && worlds[i].name != "EXIT") {
			//cout << "trying to save " + worlds[i].name << endl;
			string savename = worlds[i].name;
			frozenworlds.push_back(worlds[i].name);
			flush(worlds.at(i), WorldSaver); 
			delete[] worlds.at(i).items;
			worlds.at(i).items = nullptr;
			worlds.erase(worlds.begin() + i);	
			i--;
			frozenworlds.erase(std::remove(frozenworlds.begin(), frozenworlds.end(), savename), frozenworlds.end());
			//cout << "saved " + savename << endl;
		}
	}
	mysql_close(WorldSaver);
	//cout << "after connection close" << endl;
}

inline vector<WorldInfo> WorldDB::getRandomWorlds() {
	vector<WorldInfo> ret;
	for (int i = 0; i < ((worlds.size() < 10) ? worlds.size() : 10); i++) {
		if (i >= worlds.size()) {
			//isPossible = false;
			SendConsole("worlds.size() was larger than loop size case 369", "ERROR");
			continue;
		}
		if (worlds[i].items == nullptr) {
			//isPossible = false;
			SendConsole("worlds was null at 1010", "ERROR");
			continue;
		}
		if (worlds[i].width < 30 || worlds[i].height < 30 || worlds[i].droppedCount < 0 || worlds[i].entrylevel <= 0 || worlds[i].silence < 0 || worlds[i].isNuked < 0) {
			SendConsole("world corrupted structure", "ERROR");
			continue;
		}
		if (worlds[i].width > 300 || worlds[i].height > 300) {
			SendConsole("world corrupter strucute", "ERROR");
			continue;
		}
		ret.push_back(worlds.at(i));
	}
	if (worlds.size() > 4) {
		for (int j = 0; j < 6; j++) {
			if (worlds[j].width == 0) {
				//isPossible = false;
				SendConsole("World error case 1 width 0", "ERROR");
				continue;
			}
			if (worlds[j].items == nullptr) {
				//isPossible = false;
				SendConsole("worlds was null at 1023", "ERROR");
				continue;
			}
			bool isPossible = true;
			int random_world = rand() % (worlds.size());
			cout << "getrndworld = " + to_string(random_world) << endl;
			auto world = worlds.at(random_world); // -4
			if (world.width < 30 || world.height < 30 || world.droppedCount < 0 || world.entrylevel <= 0 || world.silence < 0 || world.isNuked < 0) {
				SendConsole("world corrupted structure case 9", "ERROR");
				continue;
			}
			if (world.width > 300 || world.height > 300) {
				SendConsole("world corrupter strucute", "ERROR");
				continue;
			}
			for (int i = 0; i < ret.size(); i++) {
				if (world.width == 0) {
					isPossible = false;
					SendConsole("World error case width 0", "ERROR");
					continue;
				}
				if (world.items == nullptr) {
					isPossible = false;
					SendConsole("worlds was null at 1034", "ERROR");
					continue;
				}
				if (frozenworlds.size() != 0) {
					if (find(frozenworlds.begin(), frozenworlds.end(), world.name) != frozenworlds.end()) {
						continue;
					}
				}
				if (world.name == ret.at(i).name || world.name == "EXIT") {
					isPossible = false;
				}
			}
			if (isPossible) {
				ret.push_back(world);
			}
		}
	}
	return ret;
}

WorldDB worldDB;

inline bool isHereSave(ENetPeer* peer, ENetPeer* peer2)
{
	return static_cast<PlayerInfo*>(peer->data)->currentWorld == static_cast<PlayerInfo*>(peer2->data)->currentWorld;
}

inline int getPlayersCountInWorldSave(const string name)
{
	auto count = 0;
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (static_cast<PlayerInfo*>(currentPeer->data)->isinv == false && !static_cast<PlayerInfo*>(currentPeer->data)->Console)
		{
			if (static_cast<PlayerInfo*>(currentPeer->data)->currentWorld == name)
			{
				count++;
			}
		}
	}
	return count;
}

inline void sendPlayerLeaveSave(ENetPeer* peer, PlayerInfo* player)
{
	if (static_cast<PlayerInfo*>(peer->data)->currentWorld == "EXIT") return;
	auto p = packetEnd(appendString(appendString(createPacket(), "OnRemove"), "netID|" + std::to_string(static_cast<PlayerInfo*>(peer->data)->netID) + "\n"));
	auto p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`5<`w" + static_cast<PlayerInfo*>(peer->data)->displayName + "`` `5left, `w" + std::to_string(getPlayersCountInWorldSave(static_cast<PlayerInfo*>(peer->data)->currentWorld)) + "`` `5others here>```w"));
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (static_cast<PlayerInfo*>(currentPeer->data)->currentWorld == "EXIT") continue;
		if (static_cast<PlayerInfo*>(currentPeer->data)->isIn == false) continue;
		if (isHereSave(peer, currentPeer))
		{
			{
				const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
				{
					const auto net_packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(currentPeer, 0, net_packet);
				}
			}
			{
			}
		}
	}
	delete p.data;
	delete p2.data;
}

inline void saveAllWorlds() {
	worldDB.saveAll();
}

inline WorldInfo* getPlyersWorld(ENetPeer* peer) {
	return worldDB.get2(static_cast<PlayerInfo*>(peer->data)->currentWorld).ptr;
}

inline WorldInfo* getWorldInfoByName(string worldname)
{
	try
	{
		return worldDB.get2(worldname).ptr;
	}
	catch (...)
	{
		SendConsole("Failed returning value (getPlyersWorld)", "WARNING");
	}
	return nullptr;
}

struct ItemDefinition
{
	int id;
	string name;
	int rarity;
	int breakHits;
	int growTime;
	ClothTypes clothType;
	BlockTypes blockType;
	string description = "This item has no description.";
	string MultiFacing = "This item can be placed in both directions.";
	int properties;
	int price;
};

vector<ItemDefinition> itemDefs;
vector<DroppedItem> droppedItems;

inline ItemDefinition getItemDef(const int id)
{
	if (id < itemDefs.size() && id > 0 && id <= maxItems)
	{
		return itemDefs.at(id);
	}
	return itemDefs.at(0);
}

inline void craftItemDescriptions()
{
	SendConsole("Loading item descriptions (craftItemDescriptions)", "INFO");
	ifstream infile("Descriptions.txt");
	for (string line; getline(infile, line);)
	{
		if (line.length() > 3 && line[0] != '/' && line[1] != '/')
		{
			auto ex = explode("|", line);
			if (atoi(ex[0].c_str()) + 1 < itemDefs.size())
			{
				itemDefs.at(atoi(ex[0].c_str())).description = ex[1];
				if (!(atoi(ex[0].c_str()) % 2))
				{
					itemDefs.at(atoi(ex[0].c_str()) + 1).description = "This is a tree.";
				}
			}
		}
	}
}

inline void buildItemsDatabase()
{
	SendConsole("Building item database (buildItemsDatabase)", "INFO");
	auto current = -1;
	ifstream infile("CoreData.txt");
	for (string line; getline(infile, line);)
	{
		if (line.length() > 8 && line[0] != '/' && line[1] != '/')
		{
			auto ex = explode("|", line);
			ItemDefinition def;
			def.id = atoi(ex[0].c_str());
			def.name = ex[1];
			def.rarity = atoi(ex[2].c_str());
			def.price = atoi(ex[2].c_str());
			def.breakHits = atoi(ex[7].c_str());
			auto properties = explode(",", ex[3]);
			def.properties = Property_Zero;
			for (auto& prop : properties)
			{
				if (prop == "NoSeed")
				{
					def.properties += Property_NoSeed;
				}
				if (prop == "NoBlock")
				{
					def.properties += Property_NoBlock;
				}
				if (prop == "Dropless")
				{
					def.properties += Property_Dropless;
				}
				if (prop == "Beta")
				{
					def.properties += Property_Beta;
				}
				if (prop == "Mod")
				{
					def.properties += Property_Mod;
				}
				if (prop == "Untradable")
				{
					def.properties += Property_Untradable;
				}
				if (prop == "Wrenchable")
				{
					def.properties += Property_Wrenchable;
				}
				if (prop == "MultiFacing")
				{
					def.properties += Property_MultiFacing;
				}
				if (prop == "Permanent")
				{
					def.properties += Property_Permanent;
				}
				if (prop == "AutoPickup")
				{
					def.properties += Property_AutoPickup;
				}
				if (prop == "WorldLock")
				{
					def.properties += Property_WorldLock;
				}
				if (prop == "NoSelf")
				{
					def.properties += Property_NoSelf;
				}
				if (prop == "RandomGrow")
				{
					def.properties += Property_RandomGrow;
				}
				if (prop == "Public")
				{
					def.properties += Property_Public;
				}
				if (prop == "Foreground")
				{
					def.properties += Property_Foreground;
				}
				if (prop == "OnlyCombiner")
				{
					def.properties += Property_Chemical;
				}
			}
			auto bt = ex[4];
			if (bt == "Foreground_Block")
			{
				def.blockType = BlockTypes::FOREGROUND;
			}
			else if (bt == "Background_Block")
			{
				def.blockType = BlockTypes::BACKGROUND;
			}
			else if (bt == "Seed")
			{
				def.blockType = BlockTypes::SEED;
			}
			else if (bt == "Consummable")
			{
				def.blockType = BlockTypes::CONSUMABLE;
			}
			else if (bt == "Pain_Block")
			{
				def.blockType = BlockTypes::PAIN_BLOCK;
			}
			else if (bt == "Main_Door")
			{
				def.blockType = BlockTypes::MAIN_DOOR;
			}
			else if (bt == "Bedrock")
			{
				def.blockType = BlockTypes::BEDROCK;
			}
			else if (bt == "Door")
			{
				def.blockType = BlockTypes::DOOR;
			}
			else if (bt == "Fist")
			{
				def.blockType = BlockTypes::FIST;
			}
			else if (bt == "Sign")
			{
				def.blockType = BlockTypes::SIGN;
			}
			else if (bt == "Back")
			{
				def.blockType = BlockTypes::BACKGROUND;
			}
			else if (bt == "Sheet_Music")
			{
				def.blockType = BlockTypes::BACKGROUND;
			}
			else if (bt == "Wrench")
			{
				def.blockType = BlockTypes::WRENCH;
			}
			else if (bt == "Checkpoint")
			{
				def.blockType = BlockTypes::CHECKPOINT;
			}
			else if (bt == "Lock")
			{
				def.blockType = BlockTypes::LOCK;
			}
			else if (bt == "Gateway")
			{
				def.blockType = BlockTypes::GATEWAY;
			}
			else if (bt == "Clothing")
			{
				def.blockType = BlockTypes::CLOTHING;
			}
			else if (bt == "Platform")
			{
				def.blockType = BlockTypes::PLATFORM;
			}
			else if (bt == "SFX_Foreground")
			{
				def.blockType = BlockTypes::SFX_FOREGROUND;
			}
			else if (bt == "Gems")
			{
				def.blockType = BlockTypes::GEMS;
			}
			else if (bt == "Toggleable_Foreground")
			{
				def.blockType = BlockTypes::TOGGLE_FOREGROUND;
			}
			else if (bt == "Chemical_Combiner")
			{
				def.blockType = BlockTypes::CHEMICAL_COMBINER;
			}
			else if (bt == "Treasure")
			{
				def.blockType = BlockTypes::TREASURE;
			}
			else if (bt == "Deadly_Block")
			{
				def.blockType = BlockTypes::DEADLY;
			}
			else if (bt == "Trampoline_Block")
			{
				def.blockType = BlockTypes::TRAMPOLINE;
			}
			else if (bt == "Animated_Foreground_Block")
			{
				def.blockType = BlockTypes::ANIM_FOREGROUND;
			}
			else if (bt == "Portal")
			{
				def.blockType = BlockTypes::PORTAL;
			}
			else if (bt == "Random_Block")
			{
				def.blockType = BlockTypes::RANDOM_BLOCK;
			}
			else if (bt == "Bouncy")
			{
				def.blockType = BlockTypes::BOUNCY;
			}
			else if (bt == "Chest")
			{
				def.blockType = BlockTypes::CHEST;
			}
			else if (bt == "Switch_Block")
			{
				def.blockType = BlockTypes::SWITCH_BLOCK;
			}
			else if (bt == "Magic_Egg")
			{
				def.blockType = BlockTypes::MAGIC_EGG;
			}
			else if (bt == "Crystal")
			{
				def.blockType = BlockTypes::CRYSTAL;
			}
			else if (bt == "Mailbox")
			{
				def.blockType = BlockTypes::MAILBOX;
			}
			else if (bt == "Bulletin_Board")
			{
				def.blockType = BlockTypes::BULLETIN_BOARD;
			}
			else if (bt == "Faction")
			{
				def.blockType = BlockTypes::FACTION;
			}
			else if (bt == "Component")
			{
				def.blockType = BlockTypes::COMPONENT;
			}
			else if (bt == "Weather_Machine")
			{
				def.blockType = BlockTypes::WEATHER;
			}
			else if (bt == "ItemSucker")
			{
				def.blockType = BlockTypes::SUCKER;
			}
			else if (bt == "Fish_Tank_Port")
			{
				def.blockType = BlockTypes::FISH;
			}
			else if (bt == "Steam_Block")
			{
				def.blockType = BlockTypes::STEAM;
			}
			else if (bt == "ground_Block")
			{
				def.blockType = BlockTypes::GROUND_BLOCK;
			}
			else if (bt == "Display")
			{
				def.blockType = BlockTypes::DISPLAY;
			}
			else if (bt == "Untrade_A_Box" || bt == "Safe_Vault")
			{
				def.blockType = BlockTypes::STORAGE;
			}
			else if (bt == "Vending")
			{
				def.blockType = BlockTypes::VENDING;
			}
			else if (bt == "Donation_Box")
			{
				def.blockType = BlockTypes::DONATION;
			}
			else if (bt == "Phone_Booth")
			{
				def.blockType = BlockTypes::PHONE;
			}
			else if (bt == "Sewing_Machine")
			{
				def.blockType = BlockTypes::SEWINGMACHINE;
			}
			else if (bt == "Crime_Villain")
			{
				def.blockType = BlockTypes::CRIME_VILLAIN;
			}
			else if (bt == "Provider")
			{
				def.blockType = BlockTypes::PROVIDER;
			}
			else
			{
				def.blockType = BlockTypes::UNKNOWN;
			}
			def.breakHits = atoi(ex[7].c_str());
			def.growTime = atoi(ex[8].c_str());
			auto cl = ex[9];
			if (def.blockType == BlockTypes::CLOTHING)
			{
				if (cl == "None")
				{
					def.clothType = ClothTypes::NONE;
				}
				else if (cl == "Hat")
				{
					def.clothType = ClothTypes::HAIR;
				}
				else if (cl == "Shirt")
				{
					def.clothType = ClothTypes::SHIRT;
				}
				else if (cl == "Pants")
				{
					def.clothType = ClothTypes::PANTS;
				}
				else if (cl == "Feet")
				{
					def.clothType = ClothTypes::FEET;
				}
				else if (cl == "Face")
				{
					def.clothType = ClothTypes::FACE;
				}
				else if (cl == "Hand")
				{
					def.clothType = ClothTypes::HAND;
				}
				else if (cl == "Back")
				{
					def.clothType = ClothTypes::BACK;
				}
				else if (cl == "Hair")
				{
					def.clothType = ClothTypes::MASK;
				}
				else if (cl == "Chest")
				{
					def.clothType = ClothTypes::NECKLACE;
				}
				else
				{
					def.clothType = ClothTypes::NONE;
				}
			}
			else
			{
				def.clothType = ClothTypes::NONE;
			}
			if (++current != def.id)
			{
				SendConsole("Unordered database at item " + std::to_string(current) + "/" + std::to_string(def.id), "ERROR");
			}
			maxItems = def.id;
			itemDefs.push_back(def);
		} else {
			cout << "error reading line contents" << endl;
		}
	}
	craftItemDescriptions();
}

inline BYTE* packBlockVisual(TileExtra* dataStruct)
{
	const auto data = new BYTE[104];
	for (auto i = 0; i < 100; i++)
	{
		data[i] = 0;
	}
	memcpy(data, &dataStruct->packetType, 4);
	memcpy(data + 8, &dataStruct->netID, 4);
	memcpy(data + 12, &dataStruct->characterState, 4);
	memcpy(data + 16, &dataStruct->objectSpeedX, 4);
	memcpy(data + 44, &dataStruct->punchX, 4);
	memcpy(data + 48, &dataStruct->punchY, 4);
	memcpy(data + 52, &dataStruct->charStat, 4);
	memcpy(data + 56, &dataStruct->blockid, 2);
	memcpy(data + 58, &dataStruct->backgroundid, 2);
	memcpy(data + 60, &dataStruct->visual, 4);
	memcpy(data + 64, &dataStruct->displayblock, 4);
	return data;
}

inline BYTE* packBlockVisual(BlockVisual* dataStruct)
{
	const auto data = new BYTE[72];
	for (auto i = 0; i < 72; i++)
	{
		data[i] = 0;
	}
	memcpy(data, &dataStruct->packetType, 4);
	memcpy(data + 8, &dataStruct->netID, 4);
	memcpy(data + 12, &dataStruct->characterState, 4);
	memcpy(data + 44, &dataStruct->punchX, 4);
	memcpy(data + 48, &dataStruct->punchY, 4);
	memcpy(data + 52, &dataStruct->charStat, 4);
	memcpy(data + 56, &dataStruct->blockid, 4);
	memcpy(data + 60, &dataStruct->visual, 4);
	memcpy(data + 64, &dataStruct->displayblock, 4);
	return data;
}

inline BYTE* packStuffVisual(TileExtra* dataStruct, int options, int gravity)
{
	const auto data = new BYTE[102];
	for (auto i = 0; i < 102; i++)
	{
		data[i] = 0;
	}
	memcpy(data, &dataStruct->packetType, 4);
	memcpy(data + 8, &dataStruct->netID, 4);
	memcpy(data + 12, &dataStruct->characterState, 4);
	memcpy(data + 44, &dataStruct->punchX, 4);
	memcpy(data + 48, &dataStruct->punchY, 4);
	memcpy(data + 52, &dataStruct->charStat, 4);
	memcpy(data + 56, &dataStruct->blockid, 2);
	memcpy(data + 58, &dataStruct->backgroundid, 2);
	memcpy(data + 60, &dataStruct->visual, 4);
	memcpy(data + 64, &dataStruct->displayblock, 4);
	memcpy(data + 68, &gravity, 4);
	memcpy(data + 70, &options, 4);
	return data;
}

inline BYTE* packStuffVisual333(TileExtra* dataStruct)
{
	const auto data = new BYTE[102];
	for (auto i = 0; i < 102; i++)
	{
		data[i] = 0;
	}
	memcpy(data, &dataStruct->packetType, 4);
	memcpy(data + 8, &dataStruct->netID, 4);
	memcpy(data + 12, &dataStruct->characterState, 4);
	memcpy(data + 44, &dataStruct->punchX, 4);
	memcpy(data + 48, &dataStruct->punchY, 4);
	memcpy(data + 52, &dataStruct->charStat, 4);
	memcpy(data + 56, &dataStruct->blockid, 2);
	memcpy(data + 58, &dataStruct->backgroundid, 2);
	memcpy(data + 60, &dataStruct->visual, 4);
	memcpy(data + 64, &dataStruct->displayblock, 4);
	return data;
}

inline void SendPacketRaw3(int a1, void* packetData, const size_t packetDataSize, void* a4, ENetPeer* peer, const int packetFlag)
{
	if (peer)
	{
		const auto p = enet_packet_create(nullptr, packetDataSize + 5, packetFlag);
		memcpy(p->data, &a1, 4);
		memcpy(reinterpret_cast<char*>(p->data) + 4, packetData, packetDataSize);
		enet_peer_send(peer, 0, p);
	}
	delete static_cast<char*>(packetData);
}

inline void SendPacketRaw2(int a1, void* packetData, const size_t packetDataSize, void* a4, ENetPeer* peer, const int packetFlag)
{
	ENetPacket* p;
	if (peer)
	{
		if (a1 == 4 && *(static_cast<BYTE*>(packetData) + 12) & 8)
		{
			p = enet_packet_create(nullptr, packetDataSize + *(static_cast<DWORD*>(packetData) + 13) + 5, packetFlag);
			auto four = 4;
			memcpy(p->data, &four, 4);
			memcpy(reinterpret_cast<char*>(p->data) + 4, packetData, packetDataSize);
			memcpy(reinterpret_cast<char*>(p->data) + packetDataSize + 4, a4, *(static_cast<DWORD*>(packetData) + 13));
			enet_peer_send(peer, 0, p);
		}
		else
		{
			if (a1 == 192)
			{
				a1 = 4;
				p = enet_packet_create(nullptr, packetDataSize + 5, packetFlag);
				memcpy(p->data, &a1, 4);
				memcpy(reinterpret_cast<char*>(p->data) + 4, packetData, packetDataSize);
				enet_peer_send(peer, 0, p);
			}
			else
			{
				p = enet_packet_create(nullptr, packetDataSize + 5, packetFlag);
				memcpy(p->data, &a1, 4);
				memcpy(reinterpret_cast<char*>(p->data) + 4, packetData, packetDataSize);
				enet_peer_send(peer, 0, p);
			}
		}
	}
	// ReSharper disable once CppDeletingVoidPointer
	delete static_cast<char*>(packetData);
}

inline void updatetile(ENetPeer* peer, const int netID, const int x, const int y)
{
	BlockVisual data3;
	data3.packetType = 0x5;
	data3.characterState = 8;
	data3.charStat = 8;
	data3.blockid = 2;
	data3.backgroundid = 2;
	data3.visual = 0x03000000;
	data3.punchX = x;
	data3.punchY = y;
	data3.netID = netID;
	SendPacketRaw2(192, packBlockVisual(&data3), 100, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
}

inline void updateGuild(ENetPeer* peer)
{
	SendConsole("Function (updateGuild) Called details: guildname(" + static_cast<PlayerInfo*>(peer->data)->guild + ") playername(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "INFO");
	const auto guildname = PlayerDB::getProperName(static_cast<PlayerInfo*>(peer->data)->guild);
	if (guildname != "")
	{
		try
		{
			std::ifstream ifff("guilds/" + guildname + ".json");
			if (ifff.fail())
			{
				ifff.close();
				SendConsole("Failed loading guild (updateGuild) From " + static_cast<PlayerInfo*>(peer->data)->displayName, "ERROR");
				static_cast<PlayerInfo*>(peer->data)->guild = "";
			}
			else
			{
				json j;
				ifff >> j;
				vector<string> gmembers;
				const int gfbg = j["backgroundflag"];
				const int gffg = j["foregroundflag"];
				const auto gstatement = j["GuildStatement"].get<std::string>();
				const auto gleader = j["Leader"].get<std::string>();
				const int glevel = j["GuildLevel"];
				for (auto i = 0; i < j["Member"].size(); i++)
				{
					gmembers.push_back(j["Member"][i]);
				}
				if (find(gmembers.begin(), gmembers.end(), static_cast<PlayerInfo*>(peer->data)->rawName) == gmembers.end())
				{
					static_cast<PlayerInfo*>(peer->data)->guild = "";
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->guildBg = gfbg;
					static_cast<PlayerInfo*>(peer->data)->guildFg = gffg;
					static_cast<PlayerInfo*>(peer->data)->guildStatement = gstatement;
					static_cast<PlayerInfo*>(peer->data)->guildLeader = gleader;
					static_cast<PlayerInfo*>(peer->data)->guildMembers = gmembers;
					static_cast<PlayerInfo*>(peer->data)->guildlevel = glevel;
				}
			}
			ifff.close();
		}
		catch (std::exception&)
		{
			SendConsole("updateGuild Critical error details: rawName(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
			enet_peer_disconnect_later(peer, 0);
		}
		catch (std::runtime_error&)
		{
			SendConsole("updateGuild Critical error details: name(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
			enet_peer_disconnect_later(peer, 0);
		}
		catch (...)
		{
			SendConsole("updateGuild Critical error details: name(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
			enet_peer_disconnect_later(peer, 0);
		}
	}
}

void updateEntrance(ENetPeer* peer, int foreground, int x, int y, bool open, int bg, bool updateall) {
	BYTE* data = new BYTE[69];// memset(data, 0, 69);
	for (int i = 0; i < 69; i++) data[i] = 0;
	int four = 4; int five = 5; int eight = 8;
	int huhed = (65536 * bg) + foreground; int loled = 128;

	memcpy(data, &four, 4);
	memcpy(data + 4, &five, 4);
	memcpy(data + 16, &eight, 4);
	memcpy(data + 48, &x, 4);
	memcpy(data + 52, &y, 4);
	memcpy(data + 56, &eight, 4);
	memcpy(data + 60, &foreground, 4);
	memcpy(data + 62, &bg, 4);

	if (open) {
		int state = 0;
		memcpy(data + 66, &loled, 4);
		memcpy(data + 68, &state, 4);
	}
	else {
		int state = 100;
		int yeetus = 25600;
		memcpy(data + 67, &yeetus, 5);
		memcpy(data + 68, &state, 4);
	}
	ENetPacket* p = enet_packet_create(data, 69, ENET_PACKET_FLAG_RELIABLE);

	if (updateall)
	{
		ENetPeer* currentPeer;
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (isHere(peer, currentPeer)) {
				enet_peer_send(currentPeer, 0, p);
			}
		}
	}
	else
	{
		enet_peer_send(peer, 0, p);
	}
	delete data;
}

inline void updatepeffect(ENetPeer* peer)
{
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId)
	{
		sendPuncheffectpeer(peer, static_cast<PlayerInfo*>(peer->data)->effect);
	}
}

inline void changetile(ENetPeer* peer, const int x, const int y)
{
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			BlockVisual data3;
			data3.packetType = 0x5;
			data3.characterState = 8;
			data3.charStat = 8;
			data3.blockid = 260;
			data3.backgroundid = 260;
			data3.visual = 0x00400000;
			data3.punchX = x;
			data3.punchY = y;
			data3.netID = static_cast<PlayerInfo*>(peer->data)->netID;
			SendPacketRaw2(192, packBlockVisual(&data3), 100, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}

inline void sendPData(ENetPeer* peer, PlayerMoving* data)
{
	for (ENetPeer* currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (peer != currentPeer)
		{
			if (isHere(peer, currentPeer))
			{
				data->netID = static_cast<PlayerInfo*>(peer->data)->netID;
				SendPacketRaw(4, packPlayerMoving(data), 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
		}
	}
}

inline void sendArrow(ENetPeer* peer, const uint16_t itemid, const bool droppeditem) {
    PlayerMoving pmov;
	memset(&pmov, 0, sizeof(PlayerMoving));
	*reinterpret_cast<uint32_t*>(&pmov) = 37 | (droppeditem << 8);
	pmov.netID = itemid;
	const auto pmovpacked = packPlayerMoving(&pmov);
	const auto packet = new uint8_t[4 + 56];
	memset(packet, 0, 4 + 56);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, sizeof(PlayerMoving));
	const auto epacket = enet_packet_create(packet, 4 + 56, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, epacket);
	delete pmovpacked;
	delete packet;
}
void InitializePacketWithMannequin(BYTE* raw)
{
	int i = 0;
	raw[i] = 0x05; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x08; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x09; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x17; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x22; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x8c; i++;
	raw[i] = 0x05; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x01; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x0e; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
	raw[i] = 0x00; i++;
}
inline void updateMannequin(ENetPeer* peer, int foreground, int x, int y, int background, string text, int clothHair, int clothHead, int clothMask, int clothHand, int clothNeck, int clothShirt, int clothPants, int clothFeet, int clothBack, bool sendPacketToEveryone = true, int blockState = 0) {
	PlayerMoving sign;
	sign.packetType = 0x3;
	sign.characterState = 0x0;
	sign.x = x;
	sign.y = y;
	sign.punchX = x;
	sign.punchY = y;
	sign.XSpeed = 0;
	sign.YSpeed = 0;
	sign.netID = -1;
	sign.plantingTree = foreground;
	SendPacketRaw(4, packPlayerMoving(&sign), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);

	short textLen = text.size();
	int plength = 95 + textLen;
	BYTE* raw = new BYTE[plength];
	memset(raw, 0, plength);
	InitializePacketWithMannequin(raw);
	int negativeOne = -1;
	int adjhasdjk = 0xfdfdfdfd;
	int visor = 138;

	memcpy(raw + 44, &x, sizeof(int));
	memcpy(raw + 48, &y, sizeof(int));
	memcpy(raw + 56, &foreground, sizeof(short));
	memcpy(raw + 58, &background, sizeof(short));
	memcpy(raw + 60, &blockState, sizeof(short));
	memcpy(raw + 65, &textLen, sizeof(short));
	memcpy(raw + 67, text.c_str(), textLen);
	memcpy(raw + 68 + textLen, &negativeOne, sizeof(int));
	memcpy(raw + 72 + textLen, &clothHead, sizeof(short));
	memcpy(raw + 74 + textLen, &clothShirt, sizeof(short));
	memcpy(raw + 76 + textLen, &clothPants, sizeof(short));
	memcpy(raw + 78 + textLen, &clothFeet, sizeof(short));
	memcpy(raw + 80 + textLen, &clothMask, sizeof(short));
	memcpy(raw + 82 + textLen, &clothHand, sizeof(short));
	memcpy(raw + 84 + textLen, &clothBack, sizeof(short));
	memcpy(raw + 86 + textLen, &clothHair, sizeof(short));
	memcpy(raw + 88 + textLen, &clothNeck, sizeof(short));
	memcpy(raw + 91 + textLen, &adjhasdjk, sizeof(short));

	ENetPacket* p = enet_packet_create(0, plength + 4, ENET_PACKET_FLAG_RELIABLE);
	int four = 4;
	memcpy(p->data, &four, sizeof(int));
	memcpy((char*)p->data + 4, raw, plength);

	if (sendPacketToEveryone)
	{
		ENetPeer* currentPeer;
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (isHere(peer, currentPeer)) {
				enet_peer_send(currentPeer, 0, p);
			}
		}
		delete raw;
	}
	else
	{
		enet_peer_send(peer, 0, p);
		delete raw;
	}
}
inline void updateStuffWeather(ENetPeer* peer, int x, int y, int tile, int bg, int gravity, bool isInverted, bool isSpinning)
{
	SendConsole("Function (updateStuffWeather) Called details: x(" + to_string(x) + ") y(" + to_string(y) + ") tile(" + to_string(tile) + ") bg(" + to_string(bg) + ") gravity(" + to_string(gravity) + ") isInverted(" + to_string(isInverted) + ") isSpinning(" + to_string(isSpinning) + ")", "INFO");
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			TileExtra data;
			data.packetType = 0x5;
			data.characterState = 8;
			data.punchX = x;
			data.punchY = y;
			data.charStat = 18;
			data.blockid = 3832;
			data.backgroundid = bg;
			data.visual = 0;
			auto n = tile;
			string hex = "";
			{
				std::stringstream ss;
				ss << std::hex << n;
				auto res(ss.str());
				hex = res + "31";
			}
			auto gravi = gravity;
			string hexg = "";
			{
				auto temp = gravi;
				if (gravi < 0) temp = -gravi;
				stringstream ss;
				ss << std::hex << temp;
				auto res(ss.str());
				hexg = res + "00";
			}
			auto xx = 0;
			stringstream ss;
			ss << std::hex << hex;
			if (!ss.fail())
			{
				ss >> xx;
			}
			data.displayblock = xx;
			auto xxs = 0;
			stringstream sss;
			sss << std::hex << hexg;
			if (!sss.fail())
			{
				sss >> xxs;
			}
			if (gravi < 0) xxs = -xxs;
			if (gravi < 0)
			{
				SendPacketRaw2(192, packStuffVisual(&data, 0x03FFFFFF, xxs), 102, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
			else
			{
				SendPacketRaw2(192, packStuffVisual(&data, 0x02000000, xxs), 102, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
			auto p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), 29));
			auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet2);
			delete p2.data;
		}
	}
}

inline void restoreplayernick(ENetPeer* peer)
{
	if (serverIsFrozen) return;
	if (static_cast<PlayerInfo*>(peer->data)->currentWorld == "EXIT") return;
	if (static_cast<PlayerInfo*>(peer->data)->isIn == false) return;
	if (static_cast<PlayerInfo*>(peer->data)->isNicked) return;
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId)
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 0)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 0)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}
	else
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 0)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`2" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 0)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId)
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 1)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`#@" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 1)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`#@" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}
	else
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 1)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`#@" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 1)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`#@" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId)
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 2)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`6@" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 2)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`6@" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}
	else
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 2)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`6@" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
		else
		{
			if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 2)
			{
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->displayName = "`6@" + static_cast<PlayerInfo*>(peer->data)->tankIDName;
				}
			}
		}
	}
}

inline void updateplayer(ENetPeer* peer) {
	const auto item = static_cast<PlayerInfo*>(peer->data)->cloth_back;
	if (item == 8552) {
		static_cast<PlayerInfo*>(peer->data)->isDr = true;
		static_cast<PlayerInfo*>(peer->data)->canDoubleJump = true;
	}
	else if (item == 10426 || item == 1784 || item == 1674 || item == 9434 || item == 9006 || item == 1958 || getItemDef(item).name.find("Aura") != string::npos || getItemDef(item).name.find("Wings") != string::npos || getItemDef(item).name.find("Cape") != string::npos || item == 8580 || item == 9410 || item == 9306 || item == 10020 || item == 10012 || item == 10032 || item == 9466 || item == 10016 || item == 5136 || item == 9760 || item == 10022 || item == 9478 || item == 9506 || item == 9476 || item == 1970 || item == 8286 || item == 156 || item == 9434 || item == 8552 || item == 362 || item == 678 || item == 736 || item == 7734 || item == 7762 || item == 818 || item == 1206 || item == 1460 || item == 1550 || item == 1574 || item == 1668 || item == 1672 || item == 1824 || item == 1936 || item == 1938 || item == 2254 || item == 2256 || item == 2258 || item == 2260 || item == 2262 || item == 2264 || item == 2390 || item == 2392 || item == 3120 || item == 3308 || item == 3512 || item == 4534 || item == 4986 || item == 5754 || item == 6144 || item == 6334 || item == 6694 || item == 6818 || item == 6842 || item == 1934 || item == 3134 || item == 6004 || item == 1780 || item == 2158 || item == 2160 || item == 2162 || item == 2164 || item == 2166 || item == 2168 || item == 2438 || item == 2538 || item == 2778 || item == 3858 || item == 350 || item == 998 || item == 1738 || item == 2642 || item == 2982 || item == 3104 || item == 3144 || item == 5738 || item == 3112 || item == 2722 || item == 3114 || item == 4970 || item == 4972 || item == 5020 || item == 6284 || item == 4184 || item == 4628 || item == 5322 || item == 4112 || item == 4114 || item == 3442 || item == 9466 || item == 5136 || item == 9416 || item == 9356)
	{
		static_cast<PlayerInfo*>(peer->data)->canDoubleJump = true;
		if (item == 10424) {
			GamePacket pp = packetEnd(appendInt(appendInt(appendInt(appendInt(appendInt(appendInt(appendString(createPacket(), "OnRiftCape"), 2555), 2402849791), 723421695), 2402849791), 1059267327), 30));
			ENetPacket* packetpp = enet_packet_create(pp.data, pp.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packetpp);
			delete pp.data;
		}
	}
	updatepeffect(peer);
}

inline void send_state(ENetPeer* peer) {
	if (static_cast<PlayerInfo*>(peer->data)->currentWorld == "EXIT") return;
	if (static_cast<PlayerInfo*>(peer->data)->cloth_necklace == 4656) static_cast<PlayerInfo*>(peer->data)->haveGeigerRadiation = true;
	const auto info = static_cast<PlayerInfo*>(peer->data);
	const auto netID = info->netID;
	const auto state = getState(info);
	for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			PlayerMoving data;
			auto water = 125.0f;
			data.packetType = 0x14;
			data.characterState = static_cast<PlayerInfo*>(peer->data)->characterState;
			data.x = 1000;
			if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 366) data.y = -400;
			else data.y = 400;
			data.punchX = 0;
			data.punchY = 0;
			data.XSpeed = 300;
			if (static_cast<PlayerInfo*>(peer->data)->cloth_back == 9472) data.YSpeed = 600;
			else if (static_cast<PlayerInfo*>(peer->data)->cloth_back == 10418 || static_cast<PlayerInfo*>(peer->data)->cloth_back == 10420) data.YSpeed = 250;
			else data.YSpeed = 1000;
			data.netID = netID;
			data.plantingTree = state;
			const auto raw = packPlayerMoving(&data);
			auto var = 0x818100;
			memcpy(raw + 1, &var, 3);
			memcpy(raw + 16, &water, 4);
			SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
	restoreplayernick(peer);
	Player::OnNameChanged(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->displayName);
	updateplayer(peer);
	if (static_cast<PlayerInfo*>(peer->data)->isZombie == true || static_cast<PlayerInfo*>(peer->data)->cloth_feet == 898 || static_cast<PlayerInfo*>(peer->data)->cloth_feet == 1830 || static_cast<PlayerInfo*>(peer->data)->cloth_feet == 1966) playerconfig(peer, 1150, 130, 0x14);
}

inline void end_surgery(ENetPeer* peer, bool Fail) {
	if (Fail) {
		auto world = getPlyersWorld(peer);
		Player::OnConsoleMessage(peer, "You couldn't save them!");
		Player::OnConsoleMessage(peer, "You are not allowed to perform surgery for a while! (`$Malpractice`` mod added, `$1 hour`` left)");
		ENetPeer* currentPeer;
		for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer)) {
				Player::PlayAudio(currentPeer, "audio/metal_destroy.wav", 0);
			}
		}
		if (static_cast<PlayerInfo*>(peer->data)->lastPunchX >= 0 && static_cast<PlayerInfo*>(peer->data)->lastPunchY >= 0) {
			world->items[static_cast<PlayerInfo*>(peer->data)->lastPunchX + (static_cast<PlayerInfo*>(peer->data)->lastPunchY * world->width)].foreground = 0;
			PlayerMoving data3;
			data3.packetType = 0x3;
			data3.characterState = 0x0;
			data3.x = static_cast<PlayerInfo*>(peer->data)->lastPunchX;
			data3.y = static_cast<PlayerInfo*>(peer->data)->lastPunchY;
			data3.punchX = static_cast<PlayerInfo*>(peer->data)->lastPunchX;
			data3.punchY = static_cast<PlayerInfo*>(peer->data)->lastPunchY;
			data3.XSpeed = 0;
			data3.YSpeed = 0;
			data3.netID = -1;
			data3.plantingTree = 0;
			for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
				if (isHere(peer, currentPeer)) {
					auto raw = packPlayerMoving(&data3);
					raw[2] = 0;
					raw[3] = 0;
					SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
					Player::OnParticleEffect(currentPeer, 57, static_cast<PlayerInfo*>(peer->data)->lastPunchX * 32, static_cast<PlayerInfo*>(peer->data)->lastPunchY * 32, 0);
				}
			}
		}
		static_cast<PlayerInfo*>(peer->data)->SurgeryTime = (GetCurrentTimeInternalSeconds() + (60 * 60));
	} else {
		if (SurgeryDay) {
			static_cast<PlayerInfo*>(peer->data)->SurgeryTime = (GetCurrentTimeInternalSeconds() + (30 * 60));
		} else {
			static_cast<PlayerInfo*>(peer->data)->SurgeryTime = (GetCurrentTimeInternalSeconds() + (20 * 60));
		}
	}
	static_cast<PlayerInfo*>(peer->data)->SurgeryCooldown = true;
	static_cast<PlayerInfo*>(peer->data)->PatientDiagnosis = "";
	static_cast<PlayerInfo*>(peer->data)->PatientPulse = "";
	static_cast<PlayerInfo*>(peer->data)->PatientStatus = "";
	static_cast<PlayerInfo*>(peer->data)->PatientTemperature = 0;
	static_cast<PlayerInfo*>(peer->data)->OperationSite = "";
	static_cast<PlayerInfo*>(peer->data)->PatientIncisions = 0;
	static_cast<PlayerInfo*>(peer->data)->PerformingSurgery = false;
	static_cast<PlayerInfo*>(peer->data)->HardToSee = false;
	static_cast<PlayerInfo*>(peer->data)->PatientLosingBlood = false;
	static_cast<PlayerInfo*>(peer->data)->TempColor = "";
	static_cast<PlayerInfo*>(peer->data)->UnlockedAntibiotic = false;
	static_cast<PlayerInfo*>(peer->data)->PatientHeartStopped = false;
	static_cast<PlayerInfo*>(peer->data)->SurgeryCooldown = true;
	static_cast<PlayerInfo*>(peer->data)->PatientTemperatureRise = 0;
	static_cast<PlayerInfo*>(peer->data)->IncisionsColor = "";
	static_cast<PlayerInfo*>(peer->data)->FixIt = false;
	static_cast<PlayerInfo*>(peer->data)->Ultrasound = 0;
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
}

inline void sendPlayerLeave(ENetPeer* peer) {
	if (static_cast<PlayerInfo*>(peer->data)->Fishing) {
		static_cast<PlayerInfo*>(peer->data)->TriggerFish = false;
		static_cast<PlayerInfo*>(peer->data)->FishPosX = 0;
		static_cast<PlayerInfo*>(peer->data)->FishPosY = 0;
		static_cast<PlayerInfo*>(peer->data)->Fishing = false;
		send_state(peer);
	}
	if (static_cast<PlayerInfo*>(peer->data)->PerformingSurgery) {
		end_surgery(peer, true);
	}
	static_cast<PlayerInfo*>(peer->data)->cpY = 0;
	static_cast<PlayerInfo*>(peer->data)->cpY = 0;
	static_cast<PlayerInfo*>(peer->data)->usedCP = false;
	if (find(static_cast<PlayerInfo*>(peer->data)->lastworlds.begin(), static_cast<PlayerInfo*>(peer->data)->lastworlds.end(), static_cast<PlayerInfo*>(peer->data)->currentWorld) != static_cast<PlayerInfo*>(peer->data)->lastworlds.end()) {
		static_cast<PlayerInfo*>(peer->data)->lastworlds.erase(std::remove(static_cast<PlayerInfo*>(peer->data)->lastworlds.begin(), static_cast<PlayerInfo*>(peer->data)->lastworlds.end(), static_cast<PlayerInfo*>(peer->data)->currentWorld), static_cast<PlayerInfo*>(peer->data)->lastworlds.end());
		static_cast<PlayerInfo*>(peer->data)->lastworlds.push_back(static_cast<PlayerInfo*>(peer->data)->currentWorld);
	} else {
		static_cast<PlayerInfo*>(peer->data)->lastworlds.push_back(static_cast<PlayerInfo*>(peer->data)->currentWorld);
	}
	static_cast<PlayerInfo*>(peer->data)->ischeck = false;
	auto p = packetEnd(appendString(appendString(createPacket(), "OnRemove"), "netID|" + std::to_string(static_cast<PlayerInfo*>(peer->data)->netID) + "\n"));
	auto p2 = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`5<`w" + static_cast<PlayerInfo*>(peer->data)->displayName + "`` `5left, `w" + std::to_string(getPlayersCountInWorld(static_cast<PlayerInfo*>(peer->data)->currentWorld) - 1) + "`` `5others here>```w"));
	const string text = "action|play_sfx\nfile|audio/door_shut.wav\ndelayMS|0\n";
	const auto data = new BYTE[5 + text.length()];
	BYTE zero = 0;
	auto type = 3;
	memcpy(data, &type, 4);
	memcpy(data + 4, text.c_str(), text.length());
	memcpy(data + 4 + text.length(), &zero, 1);
	for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (static_cast<PlayerInfo*>(currentPeer->data)->currentWorld == "EXIT") continue;
		if (static_cast<PlayerInfo*>(currentPeer->data)->isIn == false) continue;
		if (isHere(peer, currentPeer)) {
			const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			{
				const auto net_packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, net_packet);
				const auto packet3 = enet_packet_create(data, 5 + text.length(), ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet3);
			}
			if (static_cast<PlayerInfo*>(peer->data)->isinv == false) {
				const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2);
				auto p4 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(peer->data)->netID), "`5<`w" + static_cast<PlayerInfo*>(peer->data)->displayName + "`` `5left, `w" + std::to_string(getPlayersCountInWorld(static_cast<PlayerInfo*>(peer->data)->currentWorld) - 1) + "`` `5others here>```w"));
				const auto packet4 = enet_packet_create(p4.data, p4.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet4);
				delete p4.data;
			}
		}
	}
	delete p.data;
	delete p2.data;
	delete[] data;
}

inline void sendRoulete(ENetPeer* peer)
{
	using namespace std::chrono;
	if (static_cast<PlayerInfo*>(peer->data)->lastSPIN + 1500 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
	{
		static_cast<PlayerInfo*>(peer->data)->lastSPIN = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
	}
	else
	{
		return;
	}
	const auto val = rand() % 36;
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			auto name = static_cast<PlayerInfo*>(peer->data)->displayName;
			if (val == 1 || val == 3 || val == 5 || val == 7 || val == 9 || val == 12 || val == 14 || val == 16 || val == 18 || val == 19 || val == 21 || val == 23 || val == 25 || val == 27 || val == 30 || val == 32 || val == 34 || val == 36)
			{
				auto p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(peer->data)->netID), "`w[" + name + " `wspun the wheel and got `4" + std::to_string(val) + "`w!]"), 0));
				auto respawnTimeout = 2000;
				auto deathFlag = 0x19;
				memcpy(p2.data + 24, &respawnTimeout, 4);
				memcpy(p2.data + 56, &deathFlag, 4);
				const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2);
				delete p2.data;
				auto p2s = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`7[`w" + name + " `ospun the wheel and got `4" + std::to_string(val) + "`o!`7]"));
				memcpy(p2s.data + 24, &respawnTimeout, 4);
				memcpy(p2s.data + 56, &deathFlag, 4);
				const auto packet2s = enet_packet_create(p2s.data, p2s.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2s);
				delete p2s.data;
			}
			else if (val == 2 || val == 4 || val == 6 || val == 8 || val == 10 || val == 11 || val == 13 || val == 15 || val == 17 || val == 20 || val == 22 || val == 24 || val == 26 || val == 28 || val == 29 || val == 31 || val == 33 || val == 35)
			{
				auto p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(peer->data)->netID), "`w[" + name + " `wspun the wheel and got `b" + std::to_string(val) + "`w!]"), 0));
				auto respawnTimeout = 2000;
				auto deathFlag = 0x19;
				memcpy(p2.data + 24, &respawnTimeout, 4);
				memcpy(p2.data + 56, &deathFlag, 4);
				const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2);
				delete p2.data;
				auto p2s = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`7[`w" + name + " `ospun the wheel and got `b" + std::to_string(val) + "`o!`7]"));
				memcpy(p2s.data + 24, &respawnTimeout, 4);
				memcpy(p2s.data + 56, &deathFlag, 4);
				const auto packet2s = enet_packet_create(p2s.data, p2s.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2s);
				delete p2s.data;
			}
			else if (val == 0 || val == 37)
			{
				auto p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(peer->data)->netID), "`w[" + name + " `wspun the wheel and got `20`w!]"), 0));
				auto respawnTimeout = 2000;
				auto deathFlag = 0x19;
				memcpy(p2.data + 24, &respawnTimeout, 4);
				memcpy(p2.data + 56, &deathFlag, 4);
				const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2);
				delete p2.data;
				auto p2s = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "`7[`w" + name + " `ospun the wheel and got `20`o!`7]"));
				memcpy(p2s.data + 24, &respawnTimeout, 4);
				memcpy(p2s.data + 56, &deathFlag, 4);
				const auto packet2s = enet_packet_create(p2s.data, p2s.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packet2s);
				delete p2s.data;
			}
		}
	}
}

#include "packet_initialize/display_block.h"

void updateDoor(ENetPeer* peer, int foreground, int x, int y, int background, string text, bool locked, bool sendPacketToEveryone = true, int visuals = 0) {
	PlayerMoving sign;
	sign.packetType = 0x3;
	sign.characterState = 0x0;
	sign.x = 0x56;
	sign.y = 0x15;
	sign.punchX = 0x56;
	sign.punchY = 0x15;
	sign.XSpeed = 0;
	sign.YSpeed = 0;
	sign.netID = -1;
	sign.plantingTree = 0x0b82;
	SendPacketRaw(4, packPlayerMoving(&sign), 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
	BYTE a;
	BYTE b;
	if (!locked) a = 0x00; // 0x08 for locked
	else a = 0x08;
	if (!locked) b = 0xeb; // 0x98 for locked
	else b = 0x98;
	uint32_t c = 0xfdfdfdfd;
	short textLen = (short)text.size();
	int plength = 73 + textLen;
	BYTE* raw = new BYTE[plength];
	memset(raw, 0, plength);
	InitializePacketWithUnlockedDoor(raw);
	memcpy(raw + 44, &x, sizeof(int));
	memcpy(raw + 48, &y, sizeof(int));
	memcpy(raw + 56, &foreground, sizeof(short));
	memcpy(raw + 58, &background, sizeof(short));
	memcpy(raw + 60, &visuals, sizeof(int));
	memcpy(raw + 65, &textLen, sizeof(short));
	memcpy(raw + 67, text.c_str(), textLen);
	memcpy(raw + 67 + textLen, &a, 1);
	memcpy(raw + 68 + textLen, &b, 1);
	memcpy(raw + 69 + textLen, &c, 4);
	ENetPacket* p = enet_packet_create(0, plength + 4, ENET_PACKET_FLAG_RELIABLE);
	int four = 4;
	memcpy(p->data, &four, sizeof(int));
	memcpy((char*)p->data + 4, raw, plength);
	if (sendPacketToEveryone) {
		ENetPeer* currentPeer;
		for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer)) {
				enet_peer_send(currentPeer, 0, p);
			}
		}
		delete raw;
	}
	else {
		enet_peer_send(peer, 0, p);
		delete raw;
	}
}



inline void UpdateDisplayVisuals(ENetPeer* peer, int foreground, int x, int y, int background, int itemid, bool sendPacketToEveryone = true)
{
	PlayerMoving sign;
	sign.packetType = 0x3;
	sign.characterState = 0x0;
	sign.x = 0x56;
	sign.y = 0x15;
	sign.punchX = 0x56;
	sign.punchY = 0x15;
	sign.XSpeed = 0;
	sign.YSpeed = 0;
	sign.netID = -1;
	sign.plantingTree = 0x0b82;
	SendPacketRaw(4, packPlayerMoving(&sign), 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
	const auto plength = 73;
	const auto raw = new BYTE[plength];
	memset(raw, 0, plength);
	InitializePacketWithDisplayBlock(raw);
	memcpy(raw + 44, &x, sizeof(int));
	memcpy(raw + 48, &y, sizeof(int));
	memcpy(raw + 56, &foreground, sizeof(short));
	memcpy(raw + 58, &background, sizeof(short));
	memcpy(raw + 65, &itemid, sizeof(int));
	const auto p = enet_packet_create(nullptr, plength + 4, ENET_PACKET_FLAG_RELIABLE);
	auto four = 4;
	memcpy(p->data, &four, sizeof(int));
	memcpy(reinterpret_cast<char*>(p->data) + 4, raw, plength);
	if (sendPacketToEveryone)
	{
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				enet_peer_send(currentPeer, 0, p);
			}
		}
		delete raw;
	}
	else
	{
		enet_peer_send(peer, 0, p);
		delete raw;
	}
}

inline void UpdateTreeVisuals(ENetPeer* peer, int foreground, int x, int y, int background, int fruitCount, int timeIntoGrowth, bool forEveryone, int blockStateFlags)
{
	auto hmm = 8;
	auto packetType = 5;
	const auto yeh = hmm + 3 + 1;
	auto idk = 15 + 4;
	auto blockState = blockStateFlags;
	auto bubble_type = 4;
	const auto ok = 52 + idk;
	const auto packetSize = ok + 4;
	const auto yup = ok - 8 - idk;
	auto four = 4;
	const auto magic = 56;
	const auto wew = ok + 5 + 4;
	auto fc = static_cast<short>(fruitCount);
	auto time = static_cast<int>(timeIntoGrowth);
	blockState |= 0x100000;
	const auto data = new BYTE[packetSize];
	const auto p = enet_packet_create(nullptr, wew, ENET_PACKET_FLAG_RELIABLE);
	memset(data, 0, packetSize);
	memcpy(data, &packetType, sizeof(int));
	memcpy(data + yeh, &hmm, sizeof(int));
	memcpy(data + yup, &x, sizeof(int));
	memcpy(data + yup + 4, &y, sizeof(int));
	memcpy(data + 4 + yup + 4, &idk, sizeof(int));
	memcpy(data + magic, &foreground, sizeof(short));
	memcpy(data + magic + 2, &background, sizeof(short));
	memcpy(data + magic + 4, &blockState, sizeof(int));
	memcpy(data + magic + 8, &bubble_type, sizeof(BYTE));
	memcpy(data + magic + 9 + 0, &time, 4);
	memcpy(data + magic + 9 + 4, &fc, 1);
	memcpy(data + ok, &blockState, sizeof(int));
	memcpy(p->data, &four, four);
	memcpy(reinterpret_cast<char*>(p->data) + four, data, packetSize);
	if (forEveryone)
	{
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				enet_peer_send(currentPeer, 0, p);
			}
		}
		delete data;
	}
	else
	{
		enet_peer_send(peer, 0, p);
		delete data;
	}
}

inline void UpdateMessageVisuals(ENetPeer* peer, int foreground, int x, int y, const string text, int background, const int bubbleType_ = 2, const bool sendPacketToEveryone = true, int blockState = 0)
{
	if (text.size() > 100) return;
	PlayerMoving sign;
	sign.packetType = 0x3;
	sign.characterState = 0x0;
	sign.x = x;
	sign.y = y;
	sign.punchX = x;
	sign.punchY = y;
	sign.XSpeed = 0;
	sign.YSpeed = 0;
	sign.netID = -1;
	sign.plantingTree = foreground;
	SendPacketRaw(4, packPlayerMoving(&sign), 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
	int hmm = 8, textLen = text.size(), PacketType = 5;
	const auto yeh = hmm + 3 + 1, idk = 15 + textLen, endMarker = -1, sizeofshort = 2;
	auto bubbleType = bubbleType_;
	const auto ok = 52 + idk;
	const auto kek = ok + 4, yup = ok - 8 - idk;
	const auto sizeofint = 4, magic = 56, wew = ok + 5 + 4;
	const auto wow = magic + 4 + 5;
	const auto data = new BYTE[kek];
	const auto p = enet_packet_create(nullptr, wew, ENET_PACKET_FLAG_RELIABLE);
	for (auto i = 0; i < kek; i++) data[i] = 0;
	memcpy(data, &PacketType, sizeof(int));
	memcpy(data + yeh, &hmm, sizeof(int));
	memcpy(data + yup, &x, sizeof(int));
	memcpy(data + yup + 4, &y, sizeof(int));
	memcpy(data + 4 + yup + 4, &idk, sizeof(int));
	memcpy(data + magic, &foreground, sizeof(short));
	memcpy(data + magic + 2, &background, sizeof(short));
	memcpy(data + sizeofint + magic, &blockState, sizeof(int));
	memcpy(data + magic + 4 + sizeofint, &bubbleType, sizeof(BYTE));
	memcpy(data + wow, &textLen, sizeof(short));
	memcpy(data + sizeofshort + wow, text.c_str(), textLen);
	memcpy(data + ok, &endMarker, sizeof(int));
	memcpy(p->data, &sizeofint, sizeof(int));
	memcpy(reinterpret_cast<char*>(p->data) + sizeofint, data, kek);
	if (sendPacketToEveryone)
	{
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				enet_peer_send(currentPeer, 0, p);
			}
		}
		delete data;
	}
	else
	{
		enet_peer_send(peer, 0, p);
		delete data;
	}
}

inline void sendblockstate(ENetPeer* peer, int x, int y, int state)
{
	BlockVisual data;
	data.packetType = 0x5;
	data.characterState = 8;
	data.charStat = 8;
	data.blockid = 0;
	data.backgroundid = 0;
	data.visual = state;
	data.punchX = x;
	data.punchY = y;
	data.netID = static_cast<PlayerInfo*>(peer->data)->netID;
	SendPacketRaw2(192, packBlockVisual(&data), 100, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
}

inline void UpdateVisualsForBlock(ENetPeer* peer, const bool forEveryone, const int x, const int y, WorldInfo* worldInfo, bool useLockId = true)
{
	if (!worldInfo) return;
	const auto i = y * worldInfo->width + x;
	auto blockStateFlags = 0;
	if (worldInfo->items[i].flipped) blockStateFlags |= 0x00200000;
	if (worldInfo->items[i].water) blockStateFlags |= 0x04000000;
	if (worldInfo->items[i].glue) blockStateFlags |= 0x08000000;
	if (worldInfo->items[i].fire) blockStateFlags |= 0x10000000;
	if (worldInfo->items[i].red) blockStateFlags |= 0x20000000;
	if (worldInfo->items[i].green) blockStateFlags |= 0x40000000;
	if (worldInfo->items[i].blue) blockStateFlags |= 0x80000000;
	if (getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::MAIN_DOOR)
	{
		updateDoor(peer, worldInfo->items[i].foreground, x, y, worldInfo->items[i].background, "EXIT", false, forEveryone, blockStateFlags);
	}
	else if (worldInfo->items[i].foreground == 2946)
	{
		UpdateDisplayVisuals(peer, worldInfo->items[i].foreground, x, y, worldInfo->items[i].background, worldInfo->items[i].intdata);
	}
	else if (worldInfo->items[i].foreground % 2 == 1)
	{
		UpdateTreeVisuals(peer, worldInfo->items[i].foreground, x, y, worldInfo->items[i].background, 3, 59, true, 0);
	}
	else 
	{
		UpdateMessageVisuals(peer, worldInfo->items[i].foreground, x, y, "", worldInfo->items[i].background, 0, forEveryone, blockStateFlags);
	}
}

inline void UpdateBlockState(ENetPeer* peer, const int x, const int y, bool forEveryone, WorldInfo* worldInfo)
{
	if (!worldInfo) return;
	const auto i = y * worldInfo->width + x;
	auto blockStateFlags = 0;
	if (worldInfo->items[i].flipped)
		blockStateFlags |= 0x00200000;
	if (worldInfo->items[i].water)
		blockStateFlags |= 0x04000000;
	if (worldInfo->items[i].glue)
		blockStateFlags |= 0x08000000;
	if (worldInfo->items[i].fire)
		blockStateFlags |= 0x10000000;
	if (worldInfo->items[i].red)
		blockStateFlags |= 0x20000000;
	if (worldInfo->items[i].green)
		blockStateFlags |= 0x40000000;
	if (worldInfo->items[i].blue)
		blockStateFlags |= 0x80000000;
	if (worldInfo->items[i].activated)
		blockStateFlags |= 0x00400000;
	if (blockStateFlags != 0)
	{
		TileExtra data;
		data.packetType = 0x5;
		data.characterState = 8;
		data.charStat = 8;
		data.blockid = worldInfo->items[i].foreground;
		data.backgroundid = worldInfo->items[i].background;
		data.visual = blockStateFlags;
		data.punchX = x;
		data.punchY = y;
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				SendPacketRaw2(192, packBlockVisual(&data), 100, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
		}
	}
	else
	{
		TileExtra data;
		data.packetType = 0x5;
		data.characterState = 8;
		data.charStat = 8;
		data.blockid = worldInfo->items[i].foreground;
		data.backgroundid = worldInfo->items[i].background;
		data.visual = blockStateFlags;
		data.punchX = x;
		data.punchY = y;
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				SendPacketRaw2(192, packBlockVisual(&data), 100, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
		}
	}
}

inline int GetPlayerCountServer()
{
	auto count = 0;
	for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (static_cast<PlayerInfo*>(currentPeer->data)->isinv || static_cast<PlayerInfo*>(currentPeer->data)->displayName == "" || static_cast<PlayerInfo*>(currentPeer->data)->rawName == "") continue;
		count++;
	}
	return count;
}

inline uint8_t* SuckerTileData(const uint16_t itemid, const uint16_t itemamount, const uint8_t magnet_on, const uint8_t remote_on)
{
	const auto data = new uint8_t[15];
	memset(data, 0, 15);
	data[0] = 0x3E;
	*reinterpret_cast<uint16_t*>(data + 1) = itemid;
	*reinterpret_cast<uint16_t*>(data + 5) = itemamount;
	*static_cast<uint8_t*>(data + 9) = magnet_on;
	*static_cast<uint8_t*>(data + 10) = remote_on;
	*static_cast<uint8_t*>(data + 12) = 1;
	return data;
}

inline void SendItemSucker(ENetPeer* peer, const int blockid, const int x, const int y, const uint16_t itemid, const uint16_t itemamount, const uint8_t magneton, const uint8_t remoteon, const int background)
{
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.characterState = 8;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = -1;
	const auto pmovpacked = packPlayerMoving(&pmov);
	*reinterpret_cast<uint32_t*>(pmovpacked + 52) = 15 + 8;
	const auto packet = new uint8_t[4 + 56 + 15 + 8];
	memset(packet, 0, 4 + 56 + 15 + 8);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, 56);
	*reinterpret_cast<uint16_t*>(packet + 4 + 56) = blockid;
	*reinterpret_cast<uint16_t*>(packet + 6 + 56) = background;
	const auto tiledata = SuckerTileData(itemid, itemamount, magneton, remoteon);
	memcpy(packet + 4 + 56 + 8, tiledata, 15);
	const auto epacket = enet_packet_create(packet, 4 + 56 + 8 + 15, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, epacket);
	delete pmovpacked;
	delete packet;
	delete tiledata;
}

inline void SendDonateData(ENetPeer* peer, short fg, short bg, const int x, const int y, int item)
{
	const auto ExtendedData = new BYTE[15];
	//auto state = 0x0010000;
	//auto zero = 0;
	auto extendedLen = 15;
	//auto stt = 65;
	PlayerMoving pmov;
	pmov.packetType = 0x5;
	pmov.characterState = 0x8;
	pmov.punchX = x;
	pmov.punchY = y;
	const auto raw = new BYTE[56 + 15];
	memcpy(raw, packPlayerMoving(&pmov), 56);
	memcpy(raw + 52, &extendedLen, 4);
	memcpy(ExtendedData, &fg, 2);
	memcpy(ExtendedData + 2, &bg, 2);
	ExtendedData[4] = 0;
	ExtendedData[5] = 0;
	ExtendedData[6] = 65;
	ExtendedData[7] = 0;
	memcpy(raw + 56, ExtendedData, extendedLen);
	SendPacketRaw3(4, raw, 56 + 15, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
}

inline void RemoveItemPacket(ENetPeer* peer, short fg, short bg, const int x, const int y, int item)
{
	const auto ExtendedData = new BYTE[15];
	//auto state = 0x0010000;
	//auto zero = 0;
	auto extendedLen = 15;
	//auto stt = 65;
	PlayerMoving pmov;
	pmov.packetType = 0x5;
	pmov.characterState = 0x8;
	pmov.punchX = x;
	pmov.punchY = y;
	const auto raw = new BYTE[56 + 15];
	memcpy(raw, packPlayerMoving(&pmov), 56);
	memcpy(raw + 52, &extendedLen, 4);
	memcpy(ExtendedData, &fg, 2);
	memcpy(ExtendedData + 2, &bg, 2);
	ExtendedData[4] = 0;
	ExtendedData[5] = 0;
	ExtendedData[6] = 0;
	ExtendedData[7] = 0;
	memcpy(raw + 56, ExtendedData, extendedLen);
	SendPacketRaw3(4, raw, 56 + 15, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
}

inline void SendItemPacket(ENetPeer* peer, short fg, short bg, const int x, const int y, int item)
{
	const auto ExtendedData = new BYTE[15];
	//auto state = 0x0010000;
	//auto zero = 0;
	auto extendedLen = 15;
	//auto stt = 65;
	PlayerMoving pmov;
	pmov.packetType = 0x5;
	pmov.characterState = 0x8;
	pmov.punchX = x;
	pmov.punchY = y;
	const auto raw = new BYTE[56 + 15];
	memcpy(raw, packPlayerMoving(&pmov), 56);
	memcpy(raw + 52, &extendedLen, 4);
	memcpy(ExtendedData, &fg, 2);
	memcpy(ExtendedData + 2, &bg, 2);
	ExtendedData[4] = 0;
	ExtendedData[5] = 0;
	ExtendedData[6] = 65;
	ExtendedData[7] = 0;
	memcpy(raw + 56, ExtendedData, extendedLen);
	SendPacketRaw3(4, raw, 56 + 15, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
}
void sendHMonitor(ENetPeer* peer, int x, int y, string name, bool online, const int background) {
	size_t pos;
	while ((pos = name.find("`2")) != string::npos) {
		name.replace(pos, 2, "");
	}
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.characterState = 8;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = -1;
	int len = 7 + name.length();
	uint8_t* pmovpacked = packPlayerMoving(&pmov);
	*(uint32_t*)(pmovpacked + 52) = 8 + len;
	uint8_t* packet = new uint8_t[4 + 56 + 8 + len];
	memset(packet, 0, 4 + 56 + 8 + len);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, 56);
	*(uint16_t*)(packet + 4 + 56) = 0x4D8; 
	*(uint16_t*)(packet + 4 + 56 + 6) = 1 | (online ? 0x40 : 0);
	*(uint16_t*)(packet + 6 + 56) = background;
	*(uint8_t*)(packet + 4 + 56 + 8) = 0x0B;
	*(uint16_t*)(packet + 4 + 56 + 13) = name.length();
	memcpy(packet + 4 + 56 + 15, name.data(), name.length());
	ENetPacket* epacket = enet_packet_create(packet, 4 + 56 + 8 + len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, epacket);
	delete pmovpacked;
	delete packet;
}
inline void UpdateVend(ENetPeer* peer, int x, int y, int id, bool locks, int price, int background, bool isPer = false) {
	if (price == 0) id = 0;
	auto options321 = 0;
	if (price >= 256 && price < 512) options321 = 1;
	else if (price >= 512 && price < 768) options321 = 2;
	else if (price >= 768 && price < 1024) options321 = 3;
	else if (price >= 1024 && price < 1280) options321 = 4;
	else if (price >= 1280 && price < 1536) options321 = 5;
	else if (price >= 1536 && price < 1792) options321 = 6;
	else if (price >= 1792 && price < 2048) options321 = 7;
	else if (price >= 2048 && price < 2304) options321 = 8;
	else if (price >= 2304 && price < 2560) options321 = 9;
	else if (price >= 2560 && price < 2816) options321 = 10;
	else if (price >= 2816 && price < 3072) options321 = 11;
	else if (price >= 3072 && price < 3328) options321 = 12;
	else if (price >= 3328 && price < 3584) options321 = 13;
	else if (price >= 3584 && price < 3840) options321 = 14;
	else if (price >= 3840 && price < 4096) options321 = 15;
	else if (price >= 4096 && price < 4352) options321 = 16;
	else if (price >= 4352 && price < 4608) options321 = 17;
	else if (price >= 4608 && price < 4864) options321 = 18;
	else if (price >= 4864 && price < 5120) options321 = 19;
	else if (price >= 5120 && price < 5376) options321 = 20;
	else if (price >= 5376 && price < 5632) options321 = 21;
	else if (price >= 5632 && price < 5888) options321 = 22;
	else if (price >= 5888 && price < 6144) options321 = 23;
	else if (price >= 6144 && price < 6400) options321 = 24;
	else if (price >= 6400 && price < 6656) options321 = 25;
	else if (price >= 6656 && price < 6912) options321 = 26;
	else if (price >= 6912 && price < 7168) options321 = 27;
	else if (price >= 7168 && price < 7424) options321 = 28;
	else if (price >= 7424 && price < 7680) options321 = 29;
	else if (price >= 7680 && price < 7936) options321 = 30;
	else if (price >= 7936 && price < 8192) options321 = 31;
	else if (price >= 8192 && price < 8448) options321 = 32;
	else if (price >= 8448 && price < 8704) options321 = 33;
	else if (price >= 8704 && price < 8960) options321 = 34;
	else if (price >= 8960 && price < 9216) options321 = 35;
	else if (price >= 9216 && price < 9472) options321 = 36;
	else if (price >= 9472 && price < 9728) options321 = 37;
	else if (price >= 9728 && price < 9984) options321 = 38;
	else if (price >= 9984 && price < 10240) options321 = 39;
	else if (price >= 10240 && price < 10496) options321 = 40;
	else if (price >= 10496 && price < 10752) options321 = 41;
	else if (price >= 10752 && price < 11008) options321 = 42;
	else if (price >= 11008 && price < 11264) options321 = 43;
	else if (price >= 11264 && price < 11520) options321 = 44;
	else if (price >= 11520 && price < 11776) options321 = 45;
	else if (price >= 11776 && price < 12032) options321 = 46;
	else if (price >= 12032 && price < 12288) options321 = 47;
	else if (price >= 12288 && price < 12544) options321 = 48;
	else if (price >= 12544 && price < 12800) options321 = 49;
	else if (price >= 12800 && price < 13056) options321 = 50;
	else if (price >= 13056 && price < 13312) options321 = 51;
	else if (price >= 13312 && price < 13568) options321 = 52;
	else if (price >= 13568 && price < 13824) options321 = 53;
	else if (price >= 13824 && price < 14080) options321 = 54;
	else if (price >= 14080 && price < 14336) options321 = 55;
	else if (price >= 14336 && price < 14592) options321 = 56;
	else if (price >= 14592 && price < 14848) options321 = 57;
	else if (price >= 14848 && price < 15104) options321 = 58;
	else if (price >= 15104 && price < 15360) options321 = 59;
	else if (price >= 15360 && price < 15616) options321 = 60;
	else if (price >= 15616 && price < 15872) options321 = 61;
	else if (price >= 15872 && price < 16128) options321 = 62;
	else if (price >= 16128 && price < 16384) options321 = 63;
	else if (price >= 16384 && price < 16640) options321 = 64;
	else if (price >= 16640 && price < 16896) options321 = 65;
	else if (price >= 16896 && price < 17152) options321 = 66;
	else if (price >= 17152 && price < 17408) options321 = 67;
	else if (price >= 17408 && price < 17664) options321 = 68;
	else if (price >= 17664 && price < 17920) options321 = 69;
	else if (price >= 17920 && price < 18176) options321 = 70;
	else if (price >= 18176 && price < 18432) options321 = 71;
	else if (price >= 18432 && price < 18688) options321 = 72;
	else if (price >= 18688 && price < 18944) options321 = 73;
	else if (price >= 18944 && price < 19200) options321 = 74;
	else if (price >= 19200 && price < 19456) options321 = 75;
	else if (price >= 19456 && price < 19712) options321 = 76;
	else if (price >= 19712 && price < 19968) options321 = 77;
	else if (price >= 19968 && price <= 20000) options321 = 78;
	price -= 256 * options321;
	TileExtra data;
	data.packetType = 0x5;
	data.characterState = 8;
	data.punchX = x;
	data.punchY = y;
	data.charStat = 13;
	data.blockid = 2978;
	data.backgroundid = background;
	data.visual = 0x00410000;
	if (locks == true) data.visual = 0x02410000;
	auto n = id;
	string hex = "";
	{
		std::stringstream ss;
		ss << std::hex << n;
		string res(ss.str());
		hex = res + "18";
	}
	int xx;
	std::stringstream ss;
	ss << std::hex << hex;
	ss >> xx;
	data.displayblock = xx;
	int xes; 
	{
		int wl = price;
		string basic_string = "";
		{
			std::stringstream stringstream;
			stringstream << std::hex << wl;
			string res(stringstream.str());
			basic_string = res + "00";
		}
		int i;
		std::stringstream basic_stringstream;
		basic_stringstream << std::hex << basic_string;
		basic_stringstream >> i;
		xes = i;
	}
	BYTE* raw = nullptr;
	if (isPer) {
		raw = packStuffVisual(&data, 16777215, -xes);
	} else {
		raw = packStuffVisual(&data, options321, xes);
	}
	SendPacketRaw2(192, raw, 102, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
	raw = nullptr;
}
string lockTileDatas(int visual, uint32_t owner, uint32_t adminLength, uint32_t* admins, bool isPublic = false, uint8_t bpm = 0) {
	string data;
	data.resize(4 + 2 + 4 + 4 + adminLength * 4 + 8);
	if (bpm) data.resize(data.length() + 4);
	data[2] = 0x01;
	if (isPublic) data[2] |= 0x80;
	data[4] = 3;
	data[5] = visual; 
	STRINT(data, 6) = owner;
	STRINT(data, 10) = adminLength;
	for (uint32_t i = 0; i < adminLength; i++) {
		STRINT(data, 14 + i * 4) = admins[i];
	}
	if (bpm) {
		STRINT(data, 10)++;
		STRINT(data, 14 + adminLength * 4) = -bpm;
	}
	return data;
}
void sendTileData(ENetPeer* peer, int x, int y, int visual, uint16_t fgblock, uint16_t bgblock, string tiledata) {
	if (fgblock == 202 || fgblock == 204 || fgblock == 206 || fgblock == 4994) return;
	PlayerMoving pmov;
	pmov.packetType = 5;
	pmov.characterState = 0;
	pmov.x = 0;
	pmov.y = 0;
	pmov.XSpeed = 0;
	pmov.YSpeed = 0;
	pmov.plantingTree = 0;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = 0;
	string packetstr;
	packetstr.resize(4);
	packetstr[0] = 4;
	packetstr += packPlayerMoving2(&pmov);
	packetstr[16] = 8;
	packetstr.resize(packetstr.size() + 4);
	STRINT(packetstr, 52 + 4) = tiledata.size() + 4;
	STR16(packetstr, 56 + 4) = fgblock;
	STR16(packetstr, 58 + 4) = bgblock;
	packetstr += tiledata;
	ENetPacket* packet = enet_packet_create(&packetstr[0], packetstr.length(), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
}
inline bool isWorldOwner(ENetPeer* peer, WorldInfo* world) {
	return static_cast<PlayerInfo*>(peer->data)->rawName == world->owner;
}
inline bool isWorldAdmin(ENetPeer* peer, WorldInfo* world) {
	const auto uid = static_cast<PlayerInfo*>(peer->data)->rawName;
	for (const auto i = 0; world->accessed.size();) {
		const auto x = world->accessed.at(i);
		if (uid == x.substr(0, x.find("|"))) {
			return true;
		} else {
			return false;
		}
	}
	return false;
}
void SendCanvasData(ENetPeer* peer, short fg, short bg, int x, int y, int item, string text) {
	byte* ExtendedData = new byte[15 + item + text.length()];
	int state = 0x0010000;
	int extendedLen = 15 + item + text.length();
	int TextLen = text.length();
	PlayerMoving pmov;
	pmov.packetType = 0x5;
	pmov.characterState = 0x8;
	pmov.punchX = x;
	pmov.punchY = y;
	byte* raw = new byte[56 + 15 + item + TextLen];
	memcpy(raw, packPlayerMoving(&pmov), 56);
	memcpy(raw + 52, &extendedLen, 4);
	memcpy(ExtendedData, &fg, 2);
	memcpy(ExtendedData + 2, &bg, 2);
	memcpy(ExtendedData + 4, &state, 4);
	ExtendedData[8] = 0x23;
	memcpy(ExtendedData + 9, &item, 4);
	memcpy(ExtendedData + 13, &TextLen, 2);
	memcpy(ExtendedData + 15, text.data(), TextLen);
	memcpy(raw + 56, ExtendedData, extendedLen);
	SendPacketRaw3(4, raw, 56 + 15 + item + TextLen, 0, peer, ENET_PACKET_FLAG_RELIABLE);
	delete[] ExtendedData; // fix memleak by playingo
}
inline void sendDrop(ENetPeer* peer, int netID, int x, int y, int item, int count, BYTE specialEffect) {
	if (item > maxItems) return;
	if (item < 0) return;
	for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			PlayerMoving data;
			data.packetType = 14;
			data.x = x;
			data.y = y;
			data.netID = netID;
			data.plantingTree = item;
			float val = count;
			auto val2 = specialEffect;
			const auto raw = packPlayerMoving(&data);
			memcpy(raw + 16, &val, 4);
			memcpy(raw + 1, &val2, 1);
			SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}

inline void RemoveDroppedItem(ENetPeer* peer, const int obj_id, WorldInfo* world) {
	if (!world) return;
	for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			const auto b = new BYTE[56];
			memset(b, 0, 56);
			*reinterpret_cast<int*>(&b[0]) = 0xe;
			*reinterpret_cast<int*>(&b[4]) = -2;
			*reinterpret_cast<int*>(&b[8]) = -1;
			*reinterpret_cast<int*>(&b[20]) = obj_id + 1;
			SendPacketRaw(4, b, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}
inline int processTakeServer(ENetPeer* peer, const int itemIdx) {
	auto world = getPlyersWorld(peer);
	if (!world) return -1;
	auto legit = true;
	auto atik = -1;
	for (auto i = 0; i < world->droppedItems.size(); i++) {
		if (world->droppedItems.at(i).uid == itemIdx) {
			atik = i;
			break;
		}
	}
	legit = atik != -1;
	if (legit) {
		try {
			world->droppedItems.erase(world->droppedItems.begin() + atik);
		}
		catch (...) {
			return -1;
		}
	}
	return 0;
}

inline void SendThrowEffect(ENetPeer* peer, int id, int netIDsrc, int netIDdst, int timeMs, BYTE type, int x, int y) {
	PlayerMoving data;
	data.packetType = 0x13;
	data.punchX = id;
	data.punchY = id;
	data.x = x;
	data.y = y;
	const auto raw = packPlayerMoving(&data);
	auto netIdSrc = netIDsrc;
	auto netIdDst = netIDdst;
	auto n1 = timeMs;
	memcpy(raw + 3, &type, 1);
	memcpy(raw + 4, &netIdDst, 4);
	memcpy(raw + 8, &netIdSrc, 4);
	memcpy(raw + 20, &n1, 4);
	for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			const auto raw2 = new BYTE[56];
			memcpy(raw2, raw, 56);
			SendPacketRaw(4, raw2, 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
	delete raw;
}

inline void DropItem(ENetPeer* peer, int netID, int x, int y, int item, int count, BYTE specialEffect, string history = "", bool mageffect = true) {
	if (serverIsFrozen) return;
	auto world = getPlyersWorld(peer);
	if (!world) return;
	if (item < 0) return;
	if (x == 0 || y == 0) return;
	if (static_cast<PlayerInfo*>(peer->data)->currentWorld == "EXIT") return;
	auto blockX = x / 32;
	auto blockY = y / 32;
	if (blockX < 0 || blockY < 0 || blockX > world->width || blockY > world->height) return;
	auto hasmag = false;
	for (auto i = 0; i < world->width * world->height; i++) {
		if (world->items[i].foreground == 5638 || world->items[i].foreground == 6946 || world->items[i].foreground == 6948) {
			if (world->items[i].mid != 0) {
				if (item == world->items[i].mid && world->items[i].mc <= 5000) {
					auto xx = i % world->width, yy = i / world->width;
					hasmag = true;
					world->items[i].mc += count;
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, currentPeer)) {
							if (mageffect) SendThrowEffect(currentPeer, item, static_cast<PlayerInfo*>(peer->data)->netID, -1, 200, 0, xx * 32 + 16, yy * 32 + 16);
							if (world->items[i].mc <= 0) {
								SendItemSucker(currentPeer, world->items[i].foreground, xx, yy, world->items[i].mid, 0, true, true, world->items[i].background);
							} else if (world->items[i].mc >= 5000) {
								SendItemSucker(currentPeer, world->items[i].foreground, xx, yy, world->items[i].mid, -1, true, true, world->items[i].background);
							} else {
								SendItemSucker(currentPeer, world->items[i].foreground, xx, yy, world->items[i].mid, 1, true, true, world->items[i].background);
							}
						}
					}
				}
			}
		}
	}
	if (hasmag == true) return;
	try {
		if (item == 112) {
			if (count == 1) world->items[blockX + (blockY * world->width)].yellowGems++;
			if (count == 5) world->items[blockX + (blockY * world->width)].blueGems++;
			if (count == 10) world->items[blockX + (blockY * world->width)].redGems++;
			if (count == 50) world->items[blockX + (blockY * world->width)].greenGems++;
			if (count == 100) world->items[blockX + (blockY * world->width)].purpleGems++;
			vector<int> idstoremove;
			if (world->items[blockX + (blockY * world->width)].yellowGems > 4) {
				for (auto i = 0; i < world->droppedItems.size(); i++) {
					if (blockX == static_cast<int>(world->droppedItems.at(i).x / 32) && blockY == static_cast<int>(world->droppedItems.at(i).y / 32)) {
						if (world->droppedItems.at(i).count == 1 && world->droppedItems.at(i).id == 112) {
							RemoveDroppedItem(peer, world->droppedItems.at(i).uid, world);
							idstoremove.push_back(world->droppedItems.at(i).uid);
						}
					}
				}
				world->items[blockX + (blockY * world->width)].yellowGems = 0;
				world->items[blockX + (blockY * world->width)].blueGems++;
				count = 5;
			} if (world->items[blockX + (blockY * world->width)].blueGems > 1) {
				for (auto i = 0; i < world->droppedItems.size(); i++) {
					if (blockX == static_cast<int>(world->droppedItems.at(i).x / 32) && blockY == static_cast<int>(world->droppedItems.at(i).y / 32)) {
						if (world->droppedItems.at(i).count == 5 && world->droppedItems.at(i).id == 112) {
							RemoveDroppedItem(peer, world->droppedItems.at(i).uid, world);
							idstoremove.push_back(world->droppedItems.at(i).uid);
						}
					}
				}
				world->items[blockX + (blockY * world->width)].blueGems = 0;
				world->items[blockX + (blockY * world->width)].redGems++;
				count = 10;
			} if (world->items[blockX + (blockY * world->width)].redGems > 4) {
				for (auto i = 0; i < world->droppedItems.size(); i++) {
					if (blockX == static_cast<int>(world->droppedItems.at(i).x / 32) && blockY == static_cast<int>(world->droppedItems.at(i).y / 32)) {
						if (world->droppedItems.at(i).count == 10 && world->droppedItems.at(i).id == 112) {
							RemoveDroppedItem(peer, world->droppedItems.at(i).uid, world);
							idstoremove.push_back(world->droppedItems.at(i).uid);
						}
					}
				}
				world->items[blockX + (blockY * world->width)].redGems = 0;
				world->items[blockX + (blockY * world->width)].greenGems++;
				count = 50;
			} if (world->items[blockX + (blockY * world->width)].greenGems > 1) {
				for (auto i = 0; i < world->droppedItems.size(); i++) {
					if (blockX == static_cast<int>(world->droppedItems.at(i).x / 32) && blockY == static_cast<int>(world->droppedItems.at(i).y / 32)) {
						if (world->droppedItems.at(i).count == 50 && world->droppedItems.at(i).id == 112) {
							RemoveDroppedItem(peer, world->droppedItems.at(i).uid, world);
							idstoremove.push_back(world->droppedItems.at(i).uid);
						}
					}
				}
				world->items[blockX + (blockY * world->width)].greenGems = 0;
				world->items[blockX + (blockY * world->width)].purpleGems++;
				count = 100;
			}
			for (auto i = 0; i < idstoremove.size(); i++) processTakeServer(peer, idstoremove.at(i));
		} else {
			vector<int> idstoremove;
			for (auto i = 0; i < world->droppedItems.size(); i++) {
				if (blockX == static_cast<int>(world->droppedItems.at(i).x / 32) && blockY == static_cast<int>(world->droppedItems.at(i).y / 32)) {
					if (world->droppedItems.at(i).count < 250 && world->droppedItems.at(i).id == item && world->droppedItems.at(i).count + count <= 250) {
						count = world->droppedItems.at(i).count + count;
						x = world->droppedItems.at(i).x;
						y = world->droppedItems.at(i).y;
						RemoveDroppedItem(peer, world->droppedItems.at(i).uid, world);
						idstoremove.push_back(world->droppedItems.at(i).uid);
					}
				}
			}
			for (auto i = 0; i < idstoremove.size(); i++) processTakeServer(peer, idstoremove.at(i));
		}
		DroppedItem itemDropped;
		itemDropped.id = item;
		itemDropped.count = count;
		itemDropped.x = x;
		itemDropped.y = y;
		itemDropped.uid = world->droppedCount++;
		world->droppedItems.push_back(itemDropped);
		sendDrop(peer, netID, x, y, item, count, specialEffect);
	}
	catch (...) {
		SendConsole("Dropitem failed execute", "ERROR");
	}
}
inline void SaveDroppedItem(int fItemid, int fQuantity, ENetPeer* peer, bool& success) {
	size_t invsizee = static_cast<PlayerInfo*>(peer->data)->currentInventorySize;
	auto alreadyhave = false;
	if (static_cast<PlayerInfo*>(peer->data)->inventory.items.size() == invsizee && CheckItemExists(peer, fItemid) == false) alreadyhave = true;
	auto isFullStock = false;
	auto isInInv = false;
	for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++) {
		if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemid && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount + fQuantity > 250) isFullStock = true;
		if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemid && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount <= 250) isInInv = true;
	}
	if (isFullStock == true || alreadyhave == true) {
		success = false;
	} else {
		success = true;
		if (isInInv == false) {
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
	}
	const auto p3 = packetEnd(appendFloat(appendIntx(appendFloat(appendFloat(appendFloat(appendString(createPacket(), "OnSetClothing"), (static_cast<PlayerInfo*>(peer->data))->cloth_hair, (static_cast<PlayerInfo*>(peer->data))->cloth_shirt, (static_cast<PlayerInfo*>(peer->data))->cloth_pants), (static_cast<PlayerInfo*>(peer->data))->cloth_feet, (static_cast<PlayerInfo*>(peer->data))->cloth_face, (static_cast<PlayerInfo*>(peer->data))->cloth_hand), (static_cast<PlayerInfo*>(peer->data))->cloth_back, (static_cast<PlayerInfo*>(peer->data))->cloth_mask, (static_cast<PlayerInfo*>(peer->data))->cloth_necklace), (static_cast<PlayerInfo*>(peer->data))->skinColor), (static_cast<PlayerInfo*>(peer->data))->cloth_ances, 0.0f, 0.0f));
	memcpy(p3.data + 8, &((static_cast<PlayerInfo*>(peer->data))->netID), 4);
	const auto packet = enet_packet_create(p3.data, p3.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
}
inline void SaveItemMoreTimes(int fItemid, int fQuantity, ENetPeer* peer, bool& success, string madeby = "") {
	size_t invsizee = static_cast<PlayerInfo*>(peer->data)->currentInventorySize;
	auto alreadyhave = false;
	if (static_cast<PlayerInfo*>(peer->data)->inventory.items.size() == invsizee && CheckItemExists(peer, fItemid) == false) {
		DropItem(peer, -1, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y + rand() % 16, fItemid, fQuantity, 0);
		alreadyhave = true;
	}
	auto isFullStock = false;
	auto isInInv = false;
	for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++) {
		if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemid && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 250) {
			Player::OnDialogRequest(peer, "add_label_with_icon|big|`4Whoops!|left|1048|\nadd_spacer|small|\nadd_textbox|`oSoory! You already have full stock of this item!|\nadd_spacer|small|\nadd_button|close|`5Close|0|0|");
			isFullStock = true;
		}
		if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == fItemid && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount < 250) isInInv = true;
	}
	if (isFullStock == true || alreadyhave == true) {
		success = false;
	} else {
		success = true;
		if (isInInv == false) {
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
		const auto p3 = packetEnd(appendFloat(appendIntx(appendFloat(appendFloat(appendFloat(appendString(createPacket(), "OnSetClothing"), (static_cast<PlayerInfo*>(peer->data))->cloth_hair, (static_cast<PlayerInfo*>(peer->data))->cloth_shirt, (static_cast<PlayerInfo*>(peer->data))->cloth_pants), (static_cast<PlayerInfo*>(peer->data))->cloth_feet, (static_cast<PlayerInfo*>(peer->data))->cloth_face, (static_cast<PlayerInfo*>(peer->data))->cloth_hand), (static_cast<PlayerInfo*>(peer->data))->cloth_back, (static_cast<PlayerInfo*>(peer->data))->cloth_mask, (static_cast<PlayerInfo*>(peer->data))->cloth_necklace), (static_cast<PlayerInfo*>(peer->data))->skinColor), (static_cast<PlayerInfo*>(peer->data))->cloth_ances, 0.0f, 0.0f));
		memcpy(p3.data + 8, &((static_cast<PlayerInfo*>(peer->data))->netID), 4);
		const auto packet = enet_packet_create(p3.data, p3.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
	}
}

inline int getGemCount(const int item)
{
	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	auto count = 0;
	try {
		const auto rarity = getItemDef(item).rarity;
		if (rarity == 0) return 0;
		if (rarity > 13) {
			count = rarity / 6;
		} else {
			const auto ran = rand() % 2;
			switch (ran)
			{
			case 1:
				count = 1;
				break;
			case 2:
				count = 2;
				break;
			default:
				count = 0;
				break;
			}
		}
	}
	catch (...)
	{
		return 0;
	}
	return count;
}

inline void send_item(ENetPeer* peer, const int itemid, const int item_amount, const int kindofchest)
{
	auto success = false;
	SaveItemMoreTimes(itemid, item_amount, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(kindofchest).name + "");
	Player::OnConsoleMessage(peer, "`oYou have obtained `$" + getItemDef(itemid).name + "`o");
}

inline void DailyRewardCheck(ENetPeer* peer) {
	if (static_cast<PlayerInfo*>(peer->data)->lastdailyGems <= GetCurrentTimeInternalSeconds() / 60) {
		static_cast<PlayerInfo*>(peer->data)->lastdailyGems = (GetCurrentTimeInternalSeconds() / 60) + 1440;
		bool success = true;
		if (static_cast<PlayerInfo*>(peer->data)->Subscriber && static_cast<PlayerInfo*>(peer->data)->SubscribtionEndDay - 1 >= 1)  { 
			SaveItemMoreTimes(1360, 2, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from daily reward");
		} else {
			SaveItemMoreTimes(1360, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from daily reward");
		}
		string querykodas;
		if (static_cast<PlayerInfo*>(peer->data)->Subscriber) {
			static_cast<PlayerInfo*>(peer->data)->SubscribtionEndDay -= 1;
			if (static_cast<PlayerInfo*>(peer->data)->SubscribtionEndDay <= 0) {
				querykodas = "UPDATE PlayerDatabase SET dailyrewards = '" + to_string(static_cast<PlayerInfo*>(peer->data)->lastdailyGems) + "', subtype = '', subdate = '' WHERE username = '" + static_cast<PlayerInfo*>(peer->data)->rawName + "' LIMIT 1";
			} else {
				querykodas = "UPDATE PlayerDatabase SET dailyrewards = '" + to_string(static_cast<PlayerInfo*>(peer->data)->lastdailyGems) + "', subdate = '" + to_string(static_cast<PlayerInfo*>(peer->data)->SubscribtionEndDay) + "' WHERE username = '" + static_cast<PlayerInfo*>(peer->data)->rawName + "' LIMIT 1";
			}
		} else {
			querykodas = "UPDATE PlayerDatabase SET dailyrewards = '" + to_string(static_cast<PlayerInfo*>(peer->data)->lastdailyGems) + "' WHERE username = '" + static_cast<PlayerInfo*>(peer->data)->rawName + "' LIMIT 1";
		}
		if (mysql_query(conn, querykodas.c_str())) {
			cout << mysql_error(conn) << endl;
			enet_peer_disconnect_later(peer, 0);
			return;
		}
		if (static_cast<PlayerInfo*>(peer->data)->SubscribtionEndDay == 0) {
			static_cast<PlayerInfo*>(peer->data)->Subscriber = false;
			static_cast<PlayerInfo*>(peer->data)->haveSuperSupporterName = false;
			static_cast<PlayerInfo*>(peer->data)->chatcolor = "";
			static_cast<PlayerInfo*>(peer->data)->NickPrefix = "";
			static_cast<PlayerInfo*>(peer->data)->SubscribtionEndDay = 0;
			auto iscontains = false;
			SearchInventoryItem(peer, 6260, 1, iscontains);
			if (iscontains) {
				RemoveInventoryItem(6260, 1, peer, true);
			}
			LoadPlayerData(peer);
			if (static_cast<PlayerInfo*>(peer->data)->isinv) {
				static_cast<PlayerInfo*>(peer->data)->isinv = false;
				Player::OnInvis(peer, 0, static_cast<PlayerInfo*>(peer->data)->netID);
			}
			send_state(peer);
			if (static_cast<PlayerInfo*>(peer->data)->cloth_necklace == 6260) {
				static_cast<PlayerInfo*>(peer->data)->cloth_necklace = 0;
				static_cast<PlayerInfo*>(peer->data)->effect = 8421376;
				sendPuncheffect(peer, static_cast<PlayerInfo*>(peer->data)->effect);
				string strings = "UPDATE PlayerDatabase SET ClothNeck = '0' WHERE username = '" + static_cast<PlayerInfo*>(peer->data)->rawName + "' LIMIT 1";
				if (mysql_query(conn, strings.c_str())) {
					cout << mysql_error(conn) << endl;				
					enet_peer_disconnect_later(peer, 0);
					return;
				}
			}
			sendClothes(peer);
		}
	}
	if (static_cast<PlayerInfo*>(peer->data)->startkit == false) {
		string q = "UPDATE PlayerDatabase SET startkit = 1 WHERE username = '" + static_cast<PlayerInfo*>(peer->data)->rawName + "' LIMIT 1";
		if (mysql_query(conn, q.c_str())) {
			cout << mysql_error(conn) << endl;			
			enet_peer_disconnect_later(peer, 0);
			return;
		}
		bool success = false;
		SaveItemMoreTimes(954, 150, peer, success);
		SaveItemMoreTimes(5666, 70, peer, success);
		SaveItemMoreTimes(340, 30, peer, success);
		SaveItemMoreTimes(98, 1, peer, success);
		SaveItemMoreTimes(202, 1, peer, success);
		static_cast<PlayerInfo*>(peer->data)->startkit = true;
	}
}

inline bool isWorldAdmin2(ENetPeer* peer, WorldInfo world)
{
	const auto uid = static_cast<PlayerInfo*>(peer->data)->rawName;
	for (const auto i = 0; world.accessed.size();)
	{
		const auto x = world.accessed.at(i);
		if (uid == x.substr(0, x.find("|")))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

inline void SendBreakPacket(ENetPeer* peer, const int x, const int y) {
	PlayerMoving data;
	data.netID = static_cast<PlayerInfo*>(peer->data)->netID;
	data.packetType = 0x8;
	data.plantingTree = 0;
	data.netID = -1;
	data.x = x;
	data.y = y;
	data.punchX = x;
	data.punchY = y;
	SendPacketRaw(4, packPlayerMoving(&data), 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
}



inline void sendFrozenState(ENetPeer* peer)
{
	const auto info = static_cast<PlayerInfo*>(peer->data);
	const auto netID = info->netID;
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			PlayerMoving data;
			data.packetType = 0x14;
			data.characterState = 0;
			data.x = 1000;
			data.y = 100;
			data.punchX = 0;
			data.punchY = 0;
			data.XSpeed = 300;
			data.YSpeed = 600;
			data.netID = netID;
			data.plantingTree = 2048;
			const auto raw = packPlayerMoving(&data);
			auto var = info->effect;
			memcpy(raw + 1, &var, 3);
			SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}

inline void sendWorldOffers(ENetPeer* peer) { 
	if (!static_cast<PlayerInfo*>(peer->data)->isIn) return;
	auto worlds = worldDB.getRandomWorlds();
	string worldOffers = "default|";
	if (worlds.size() > 0) {
		if (static_cast<PlayerInfo*>(peer->data)->isIn && static_cast<PlayerInfo*>(peer->data)->haveGrowId)
		{
			string lastworld = static_cast<PlayerInfo*>(peer->data)->lastnormalworld;
			if (lastworld != "EXIT" && lastworld != "") worldOffers += lastworld;
			else worldOffers += "START";
		}
		else
		{
			worldOffers += worlds[0].name;
		}
	}
	worldOffers += "\nadd_button|Showing: `wRandom Worlds``|_catselect_|0.6|3529161471|\n";
	for (auto i = 0; i < worlds.size(); i++) {
		if (i >= worlds.size()) {
			SendConsole("worlds.size() was larger than loop size (c3802)", "ERROR");
			continue;
		}
		if (getPlayersCountInWorld(worlds[i].name) <= 0) continue;
		if (worlds[i].name == "EXIT" || worlds[i].isNuked) continue;
		bool Jammed = false;
		for (auto jss = 0; jss < worlds[i].width * worlds[i].height; jss++) {
			if (worlds[i].items[jss].foreground == 226 && worlds[i].items[jss].activated) {
				Jammed = true;
				break;
			}
		}
		if (Jammed) continue;
		float size = 0.40;
		size += 0.03 * getPlayersCountInWorld(worlds[i].name);
		if (size > 0.75) size = 0.75;
		worldOffers += "add_floater|" + worlds[i].name + "|" + std::to_string(getPlayersCountInWorld(worlds[i].name)) + "|" + to_string(size) + "|3529161471\n";
	}
	int kiekp = static_cast<PlayerInfo*>(peer->data)->lastworlds.size();
	for (int i = kiekp - 1; i >= 0; --i) {
		worldOffers += "\nadd_floater|" + static_cast<PlayerInfo*>(peer->data)->lastworlds[i] + "|0|0.5|3417414143|\n";
	}
	auto p3 = packetEnd(appendString(appendString(createPacket(), "OnRequestWorldSelectMenu"), worldOffers));
	const auto packet3 = enet_packet_create(p3.data, p3.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet3);
	delete p3.data;
}



inline void SendGamePacketEveryoneInWorld(ENetPeer* peer, GamePacket* p)
{
	const auto packet1 = enet_packet_create(p->data, p->len, ENET_PACKET_FLAG_RELIABLE);
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			enet_peer_send(currentPeer, 0, packet1);
		}
	}
	delete p->data;
}

inline void SendChat(ENetPeer* peer, const int netID, string message) {
	if (static_cast<PlayerInfo*>(peer->data)->currentWorld == "EXIT") return;
	if (static_cast<PlayerInfo*>(peer->data)->isIn == false) return;
	if (message.length() >= 120) return;
	if (message.length() == 0) return;
	if (message == " ") return;
	if (1 > (message.size() - countSpaces(message))) return;
	removeExtraSpaces(message);
	message = trimString(message);
	string ccode, chatcode;
	if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 2)
	{
		ccode = "5";
		chatcode = "5";
	}
	if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 1)
	{
		ccode = "^";
		chatcode = "^";
	}
	if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 0)
	{
		ccode = "w";
		chatcode = "$";
	}
	if (static_cast<PlayerInfo*>(peer->data)->isNicked)
	{
		ccode = "w";
		chatcode = "$";
	}
	if (static_cast<PlayerInfo*>(peer->data)->Subscriber && static_cast<PlayerInfo*>(peer->data)->chatcolor != "")
	{
		ccode = static_cast<PlayerInfo*>(peer->data)->chatcolor;
		chatcode = static_cast<PlayerInfo*>(peer->data)->chatcolor;
	}
	for (auto c : message)
	{
		if (c < 0x18 || std::all_of(message.begin(), message.end(), static_cast<int(*)(int)>(isspace)))
		{
			return;
		}
	}
	ENetPeer* currentPeer;
	string name = "";
	for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (static_cast<PlayerInfo*>(currentPeer->data)->netID == netID)
		{
			name = static_cast<PlayerInfo*>(currentPeer->data)->displayName;
		}
	}
	auto p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "CP:_PL:0_OID:_CT:[W]_ `6<`w" + name + "`6> `" + chatcode + message));
	auto p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), netID), "`" + ccode + message), 0));
	for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer) || static_cast<PlayerInfo*>(currentPeer->data)->GlobalChat)
		{
			const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet);
			if (message == "" || message == " " || message == "  ") continue;
			const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet2);
		}
	}
	delete p.data;
	delete p2.data;
	
}

inline void sendWho(ENetPeer* peer)
{
	string whoisinworld = "";
	for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (static_cast<PlayerInfo*>(currentPeer->data)->isInvisible) continue;
		if (isHere(peer, currentPeer) && static_cast<PlayerInfo*>(currentPeer->data)->isinv == false)
		{
			if (static_cast<PlayerInfo*>(currentPeer->data)->Console) continue;
			auto p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(currentPeer->data)->netID), static_cast<PlayerInfo*>(currentPeer->data)->displayName), 1));
			const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet2);
			delete p2.data;
			whoisinworld += static_cast<PlayerInfo*>(currentPeer->data)->displayName + ", ";

		}
	}
	if (whoisinworld != "")
	{
		Player::OnConsoleMessage(peer, "`wWho's in `9" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "`w: " + whoisinworld);
	}
}

inline void sendAction(ENetPeer* peer, int netID, string action)
{
	auto p2 = packetEnd(appendString(appendString(createPacket(), "OnAction"), action));
	for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			memcpy(p2.data + 8, &netID, 4);
			const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet2);
		}
	}
	delete p2.data;
}

inline void SendTake(ENetPeer* peer, const int netID, const int x, const int y, const int item)
{
	if (item >= 9999) return;
	if (item < 0) return;
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			PlayerMoving data;
			data.packetType = 14;
			data.x = x;
			data.y = y;
			data.netID = netID;
			data.plantingTree = item;
			auto raw = packPlayerMoving(&data);
			SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_EVENT_TYPE_RECEIVE);
			raw = nullptr;
		}
	}
	SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
}

inline void sendResetState(ENetPeer* peer)
{
	if (static_cast<PlayerInfo*>(peer->data)->isCursed)
	{
		const auto info = static_cast<PlayerInfo*>(peer->data);
		const auto netID = info->netID;
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				PlayerMoving data;
				data.packetType = 0x14;
				data.characterState = 0;
				data.x = 1000;
				data.y = 100;
				data.punchX = 0;
				data.punchY = 0;
				data.XSpeed = 300;
				data.YSpeed = 600;
				data.netID = netID;
				data.plantingTree = 4096;
				const auto raw = packPlayerMoving(&data);
				auto var = info->effect;
				memcpy(raw + 1, &var, 3);
				SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
			else
			{
				if (static_cast<PlayerInfo*>(peer->data)->isDuctaped)
				{
					const auto player_info = static_cast<PlayerInfo*>(peer->data);
					const auto net_id = player_info->netID;
					for (auto peer2 = server->peers;
						peer2 < &server->peers[server->peerCount];
						++peer2)
					{
						if (peer2->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, peer2))
						{
							PlayerMoving data;
							data.packetType = 0x14;
							data.characterState = 0;
							data.x = 1000;
							data.y = 100;
							data.punchX = 0;
							data.punchY = 0;
							data.XSpeed = 300;
							data.YSpeed = 600;
							data.netID = net_id;
							data.plantingTree = 8192;
							const auto raw = packPlayerMoving(&data);
							auto var = player_info->effect;
							memcpy(raw + 1, &var, 3);
							SendPacketRaw(4, raw, 56, nullptr, peer2, ENET_PACKET_FLAG_RELIABLE);
						}
						else
						{
							PlayerMoving data;
							data.packetType = 0x14;
							data.characterState = 0;
							data.x = 1000;
							data.y = 100;
							data.punchX = 0;
							data.punchY = 0;
							data.XSpeed = 300;
							data.YSpeed = 600;
							data.netID = net_id;
							data.plantingTree = 2;
							const auto raw = packPlayerMoving(&data);
							auto var = player_info->effect;
							memcpy(raw + 1, &var, 3);
							SendPacketRaw(4, raw, 56, nullptr, peer2, ENET_PACKET_FLAG_RELIABLE);
						}
					}
				}
			}
		}
	}
}



inline void SendGamePacket(ENetPeer* peer, GamePacket* p)
{
	const auto packet1 = enet_packet_create(p->data, p->len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet1);
}

inline void DoCancelTransitionAndTeleport(ENetPeer* peer, const int x, const int y, bool entered, bool animations) {
	if (animations) {
		auto respawnTimeout = 200;
		auto deathFlag = 0x19;
		if (!entered) {
			auto p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), x * 32, y * 32));
			memcpy(p2.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
			memcpy(p2.data + 24, &respawnTimeout, 4);
			memcpy(p2.data + 56, &deathFlag, 4);
			const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet2);
			delete p2.data;
		}
		auto p23 = packetEnd(appendIntx(appendFloat(appendString(createPacket(), "OnZoomCamera"), 10000.000000), 1000));
		memcpy(p23.data + 24, &respawnTimeout, 4);
		memcpy(p23.data + 56, &deathFlag, 4);
		const auto packet2 = enet_packet_create(p23.data, p23.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet2);
		delete p23.data;

		auto p234 = packetEnd(appendIntx(appendString(createPacket(), "OnSetFreezeState"), 0));
		memcpy(p234.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
		memcpy(p234.data + 24, &respawnTimeout, 4);
		memcpy(p234.data + 56, &deathFlag, 4);
		const auto packet23 = enet_packet_create(p234.data, p234.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet23);
		delete p234.data;

		auto p2346 = packetEnd(appendString(appendString(createPacket(), "OnPlayPositioned"), "audio/door_open.wav"));
		memcpy(p2346.data + 24, &respawnTimeout, 4);
		memcpy(p2346.data + 56, &deathFlag, 4);
		const auto packet249 = enet_packet_create(p2346.data, p2346.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet249);
		delete p2346.data;
	} else {
		if (!entered) {
			GamePacket p4 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), x * 32, y * 32));
			memcpy(p4.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
			SendGamePacket(peer, &p4);
		}
		Player::OnZoomCamera(peer, 10000.000000, 1000);
		auto p2 = packetEnd(appendIntx(appendString(createPacket(), "OnSetFreezeState"), 0));
		memcpy(p2.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
		SendGamePacket(peer, &p2);
		auto psp = packetEnd(appendString(appendString(createPacket(), "OnPlayPositioned"), "audio/door_open.wav"));
		const auto packetd = enet_packet_create(psp.data, psp.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packetd);
		delete psp.data;
	}
}


inline void Respawn(ENetPeer* peer) {
	auto x = 3040;
	auto y = 736;
	const auto world = getPlyersWorld(peer);
	if (world) {
		for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer)) {
				const auto val = static_cast<PlayerInfo*>(peer->data)->x;
				const auto i = static_cast<PlayerInfo*>(peer->data)->y;
				auto psp = packetEnd(appendFloat(appendIntx(appendString(createPacket(), "OnParticleEffect"), 3), val, (i + 8)));
				const auto packetd = enet_packet_create(psp.data, psp.len, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(currentPeer, 0, packetd);
				delete psp.data;
				string text = "action|play_sfx\nfile|audio/male_scream.wav\ndelayMS|0\n";
				const auto data = new BYTE[5 + text.length()];
				BYTE zero = 0;
				auto type = 3;
				memcpy(data, &type, 4);
				memcpy(data + 4, text.c_str(), text.length());
				memcpy(data + 4 + text.length(), &zero, 1);
				{
					const auto packetres = enet_packet_create(data, 5 + text.length(), ENET_PACKET_FLAG_RELIABLE);
					if (isHere(peer, currentPeer)) {
						enet_peer_send(currentPeer, 0, packetres);
					}
				}
			}
		}
		for (auto i = 0; i < world->width * world->height; i++)
		{
			if (world->items[i].foreground == 6)
			{
				x = (i % world->width) * 32;
				y = (i / world->width) * 32;
			}
		}
		{
			PlayerMoving data;
			data.packetType = 0x0;
			data.characterState = 0x924; // animation
			data.x = x;
			data.y = y;
			data.punchX = -1;
			data.punchY = -1;
			data.XSpeed = 0;
			data.YSpeed = 0;
			data.netID = static_cast<PlayerInfo*>(peer->data)->netID;
			data.plantingTree = 0x0;
			SendPacketRaw(4, packPlayerMoving(&data), 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
		}
		{
			auto val = 3040;
			auto val2 = 736;
			for (auto i = 0; i < world->width * world->height; i++)
			{
				if (world->items[i].foreground == 6)
				{
					val = (i % world->width) * 32;
					val2 = (i / world->width) * 32;
				}
			}
			auto p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), val, val2));
			memcpy(p2.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
			const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet2);
			delete p2.data;
		}
		{
			auto p2 = packetEnd(appendIntx(appendString(createPacket(), "OnSetFreezeState"), 0));
			memcpy(p2.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
			const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet2);
			delete p2.data;
			enet_host_flush(server);
		}
	}
	if (static_cast<PlayerInfo*>(peer->data)->usedCP == false)
	{
		auto p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), x, y));
		memcpy(p2.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
		const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet2);
		delete p2.data;
	}
	else
	{
		auto p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), static_cast<PlayerInfo*>(peer->data)->cpX, static_cast<PlayerInfo*>(peer->data)->cpY));
		memcpy(p2.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
		const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet2);
		delete p2.data;
	}
}

inline void SendParticleEffect(ENetPeer* peer, int x, int y, int size, int id, int delay)
{
	PlayerMoving datx;
	datx.packetType = 0x11;
	datx.x = x;
	datx.y = y;
	datx.YSpeed = id;
	datx.XSpeed = size;
	datx.plantingTree = delay;
	SendPacketRaw(4, packPlayerMoving(&datx), 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
}

inline void SyncPlayerRoles(ENetPeer* peer, int level, string type) {
	if (type == "firefighter") {
		Player::PlayAudio(peer, "audio/levelup.wav", 0);
		Player::OnParticleEffect(peer, 46, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wFirefighter role is now level " + to_string(level) + "!", 0, true);
		if (level == 1) {
			auto success = true;
			SaveItemMoreTimes(1486, 1, peer, success, "");
		} else if (level == 2) {

		} else if (level == 3) {
			
		} else if (level == 4) {
			
		} else if (level == 5) {
			auto success = true;
			SaveItemMoreTimes(4996, 1, peer, success, "");
		} else if (level == 6) {
			
		} else if (level == 7) {
			
		} else if (level == 8) {
			auto success = true;
			SaveItemMoreTimes(6860, 1, peer, success, "");
		} else if (level == 9) {
			auto success = true;
			SaveItemMoreTimes(1486, 10, peer, success, "");
		} else if (level == 10) {
			auto success = true;
			SaveItemMoreTimes(6008, 1, peer, success, "");
		}
	} else if (type == "provider") {
		Player::PlayAudio(peer, "audio/levelup.wav", 0);
		Player::OnParticleEffect(peer, 46, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wProvider role is now level " + to_string(level) + "!", 0, true);
		if (level == 1) {
			auto success = true;
			SaveItemMoreTimes(1636, 1, peer, success, "");
		} else if (level == 2) {

		} else if (level == 3) {
			auto success = true;
			SaveItemMoreTimes(1486, 3, peer, success, "");
		} else if (level == 4) {
			
		} else if (level == 5) {
			auto success = true;
			SaveItemMoreTimes(5082, 1, peer, success, "");
		} else if (level == 6) {
			
		} else if (level == 7) {
			
		} else if (level == 8) {
			auto success = true;
			SaveItemMoreTimes(6860, 1, peer, success, "");
		} else if (level == 9) {
			auto success = true;
			SaveItemMoreTimes(1486, 10, peer, success, "");
		} else if (level == 10) {
			auto success = true;
			SaveItemMoreTimes(10420, 1, peer, success, "");
		}
	} else if (type == "geiger") {
		Player::PlayAudio(peer, "audio/levelup.wav", 0);
		Player::OnParticleEffect(peer, 46, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wGeiger Hunter role is now level " + to_string(level) + "!", 0, true);
		if (level == 1) {
			auto success = true;
			SaveItemMoreTimes(4656, 1, peer, success);
		} else if (level == 2) {

		} else if (level == 3) {

		} else if (level == 4) {
			
		} else if (level == 5) {

		} else if (level == 6) {
			
		} else if (level == 7) {
			
		} else if (level == 8) {
			auto success = true;
			SaveItemMoreTimes(10424, 1, peer, success);
		} else if (level == 9) {
			auto success = true;
			SaveItemMoreTimes(5084, 1, peer, success);
		} else if (level == 10) {
			auto success = true;
			SaveItemMoreTimes(8480, 1, peer, success);
		}
	} else if (type == "fisherman") {
		Player::PlayAudio(peer, "audio/levelup.wav", 0);
		Player::OnParticleEffect(peer, 46, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wFisherman role is now level " + to_string(level) + "!", 0, true);
		if (level == 1) {
			auto success = true;
			SaveItemMoreTimes(3010, 1, peer, success);
		} else if (level == 2) {

		} else if (level == 3) {

		} else if (level == 4) {
			auto success = true;
			SaveItemMoreTimes(3074, 1, peer, success);
		} else if (level == 5) {
			auto success = true;
			SaveItemMoreTimes(5740, 1, peer, success);
		} else if (level == 6) {
			
		} else if (level == 7) {
			auto success = true;
			SaveItemMoreTimes(1550, 1, peer, success);
		} else if (level == 8) {
			auto success = true;
			SaveItemMoreTimes(3100, 1, peer, success);
		} else if (level == 9) {
			auto success = true;
			SaveItemMoreTimes(5080, 1, peer, success);
		} else if (level == 10) {
			auto success = true;
			SaveItemMoreTimes(3040, 1, peer, success);
		}
	} else if (type == "regular") {
		for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
			if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, net_peer)) {
				Player::PlayAudio(net_peer, "audio/levelup2.wav", 0);
			}
		}
		if (level == 1) {

		} else if (level == 2) {
			auto success = true;
			SaveItemMoreTimes(340, 75, peer, success, "");
		} else if (level == 3) {
			auto success = true;
			SaveItemMoreTimes(1486, 1, peer, success, "");
		} else if (level == 4) {
			auto success = true;
			SaveItemMoreTimes(1938, 1, peer, success, "");
		} else if (level == 5) {
			auto success = true;
			SaveItemMoreTimes(1486, 5, peer, success, "");
		} else if (level == 6) {
			
		} else if (level == 7) {
			auto success = true;
			SaveItemMoreTimes(6918, 1, peer, success, "");
		} else if (level == 8) {

		} else if (level == 9) {
			std::ifstream ifsz("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
			std::string content((std::istreambuf_iterator<char>(ifsz)), (std::istreambuf_iterator<char>()));
			auto gembux = atoi(content.c_str());
			auto fingembux = gembux + 5000;
			ofstream myfile;
			myfile.open("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
			myfile << fingembux;
			myfile.close();
			auto gemcalc = gembux + 5000;
			Player::OnSetBux(peer, gemcalc, 0);
		} else if (level == 10) {
			auto success = true;
			SaveItemMoreTimes(1740, 1, peer, success, "");
		} else if (level == 11) {

		} else if (level == 12) {
			std::ifstream ifsz("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
			std::string content((std::istreambuf_iterator<char>(ifsz)), (std::istreambuf_iterator<char>()));
			auto gembux = atoi(content.c_str());
			auto fingembux = gembux + 15000;
			ofstream myfile;
			myfile.open("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
			myfile << fingembux;
			myfile.close();
			auto gemcalc = gembux + 15000;
			Player::OnSetBux(peer, gemcalc, 0);
		} else if (level == 13) {
			auto success = true;
			SaveItemMoreTimes(8452, 1, peer, success, "");
		} else if (level == 14) {
			auto success = true;
			SaveItemMoreTimes(1486, 5, peer, success, "");
		} else if (level == 15) {
			
		}
	}
}

inline void SendXP(ENetPeer* peer, int amount) {
	if (GrowganothEvent) {
		if ((rand() % 3000) <= 5) {
			Player::OnConsoleMessage(peer, "`4Growganoth `olikes your work and rewards with `2Gift Of Growganoth`o!");
			Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4Growganoth `wlikes your work and rewards with `2Gift Of Growganoth`w!", 0, false);
			DropItem(peer, -1, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 10386, 1, 0);
		}
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 125) return;
	if (static_cast<PlayerInfo*>(peer->data)->cloth_necklace == 9428) {
		amount *= 2;
	} else if (static_cast<PlayerInfo*>(peer->data)->cloth_back == 9466) {
		amount *= 3;
	} if (isYellowAnces(peer) || FarmingEvent) {
		if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5078 || FarmingEvent) {
			const auto chance = (rand() % 100) + 1;
			if (chance <= 5) {
				amount *= 2;
				Player::OnParticleEffect(peer, 49, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
			}
		} else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5126) /*lvl2*/ {
			const auto chance = (rand() % 100) + 1;
			if (chance <= 10)
			{
				amount *= 2;
				Player::OnParticleEffect(peer, 49, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5128) /*lvl3*/
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 15)
			{
				amount *= 2;
				Player::OnParticleEffect(peer, 49, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5130) /*lvl4*/
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 20)
			{
				amount *= 2;
				Player::OnParticleEffect(peer, 49, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5132) /*lvl5*/
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 25)
			{
				amount *= 2;
				Player::OnParticleEffect(peer, 49, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5134) /*lvl6*/
		{
			const auto chance = (rand() % 100) + 1;
			if (chance <= 30)
			{
				amount *= 2;
				Player::OnParticleEffect(peer, 49, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
			}
		}
	}
	static_cast<PlayerInfo*>(peer->data)->xp = static_cast<PlayerInfo*>(peer->data)->xp + amount;
	if (static_cast<PlayerInfo*>(peer->data)->xp >= (static_cast<PlayerInfo*>(peer->data)->level * 1500) && static_cast<PlayerInfo*>(peer->data)->level < 125) {
		static_cast<PlayerInfo*>(peer->data)->xp = 0;
		static_cast<PlayerInfo*>(peer->data)->level = static_cast<PlayerInfo*>(peer->data)->level + 1;
		SyncPlayerRoles(peer, static_cast<PlayerInfo*>(peer->data)->level, "regular");
		for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
			if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, net_peer)) {
				Player::OnParticleEffect(net_peer, 46, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
				Player::OnConsoleMessage(net_peer, static_cast<PlayerInfo*>(peer->data)->displayName + " `wis now level " + std::to_string(static_cast<PlayerInfo*>(peer->data)->level) + "!");
				Player::OnTalkBubble(net_peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->displayName + " `wis now level " + std::to_string(static_cast<PlayerInfo*>(peer->data)->level) + "!", 0, true);
			}
		}
	}
}

inline void find_geiger(ENetPeer* peer) {
	if (static_cast<PlayerInfo*>(peer->data)->GeigerCooldown) return;
	if (static_cast<PlayerInfo*>(peer->data)->geigerx == 0 && static_cast<PlayerInfo*>(peer->data)->geigery == 0) {
		const auto geigercounterx = rand() % 3000;
		const auto geigercountery = rand() % 1500;
		static_cast<PlayerInfo*>(peer->data)->geigerx = geigercounterx;
		static_cast<PlayerInfo*>(peer->data)->geigery = geigercountery;
	}
	if (static_cast<PlayerInfo*>(peer->data)->x >= static_cast<PlayerInfo*>(peer->data)->geigerx - 30 && static_cast<PlayerInfo*>(peer->data)->x <= static_cast<PlayerInfo*>(peer->data)->geigerx + 30 && static_cast<PlayerInfo*>(peer->data)->y >= static_cast<PlayerInfo*>(peer->data)->geigery - 30 && static_cast<PlayerInfo*>(peer->data)->y <= static_cast<PlayerInfo*>(peer->data)->geigery + 30) {
		SendParticleEffect(peer, static_cast<PlayerInfo*>(peer->data)->x + 10, static_cast<PlayerInfo*>(peer->data)->y + 10, 3, 114, 0);
		std::vector<int> list{ 6416, 2206, 3792, 3196, 4654, 3306, 1498, 1500, 2804, 2806, 8270, 8272, 8274, 2242, 2244, 2246, 2248, 2250 };
		if (ValentineEvent) list.push_back(4426);
		if (GeigerDay) {
			list.push_back(4676);
			list.push_back(4678);
			list.push_back(4680);
			list.push_back(4682);
			list.push_back(4652);
			list.push_back(4646);
			list.push_back(4648);
			list.push_back(4652);
			list.push_back(4650);
			list.push_back(10084);
			list.push_back(10086);
		}
		const int index = rand() % list.size();
		const auto value = list[index];
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wI found a `2" + getItemDef(value).name + "`w!", 0, true);
		auto success = true;
		SaveItemMoreTimes(value, 1, peer, success);
		const auto geigercounterx = rand() % 3000;
		const auto geigercountery = rand() % 1500;
		static_cast<PlayerInfo*>(peer->data)->geigerx = geigercounterx;
		static_cast<PlayerInfo*>(peer->data)->geigery = geigercountery;
		int chanceofbonus = 1;
		if (static_cast<PlayerInfo*>(peer->data)->geigerlevel >= 4) chanceofbonus = 2;
		if (static_cast<PlayerInfo*>(peer->data)->geigerlevel >= 6) chanceofbonus = 3;
		if (static_cast<PlayerInfo*>(peer->data)->geigerlevel >= 8) chanceofbonus = 4;
		if (static_cast<PlayerInfo*>(peer->data)->geigerlevel >= 10) chanceofbonus = 5;
		if (static_cast<PlayerInfo*>(peer->data)->geigerlevel >= 2 && rand() % 100 <= chanceofbonus) {
			Player::OnConsoleMessage(peer, "Infused bonus not gained irradiated mod");
		} else {
			if (GeigerDay) {
				Player::OnConsoleMessage(peer, "`oYou are aglow with radiation!. (`$Irradiated `omod added, `$15 mins `oleft)``");
				static_cast<PlayerInfo*>(peer->data)->GeigerTime = (GetCurrentTimeInternalSeconds() + (15 * 60));
			} else {
				Player::OnConsoleMessage(peer, "`oYou are aglow with radiation!. (`$Irradiated `omod added, `$30 mins `oleft)``");
				static_cast<PlayerInfo*>(peer->data)->GeigerTime = (GetCurrentTimeInternalSeconds() + (30 * 60));
			}
			static_cast<PlayerInfo*>(peer->data)->GeigerCooldown = true;
			static_cast<PlayerInfo*>(peer->data)->haveGeigerRadiation = true;
			send_state(peer);
		}

		int chanceofextrabonus = 1;
		if (static_cast<PlayerInfo*>(peer->data)->geigerlevel >= 7) chanceofextrabonus = 2;
		if (static_cast<PlayerInfo*>(peer->data)->geigerlevel >= 4 && rand() % 100 <= chanceofextrabonus) {
			std::vector<int> lists{ 6416, 2206, 3792, 3196, 4654, 3306, 1498, 1500, 2804, 2806, 8270, 8272, 8274, 2242, 2244, 2246, 2248, 2250 };
			if (ValentineEvent) lists.push_back(4426);
			if (GeigerDay) {
				lists.push_back(4676);
				lists.push_back(4678);
				lists.push_back(4680);
				lists.push_back(4682);
				lists.push_back(4652);
				lists.push_back(4646);
				lists.push_back(4648);
				lists.push_back(4652);
				lists.push_back(4650);
				lists.push_back(10084);
				lists.push_back(10086);
			}
			const int indexas = rand() % lists.size();
			const auto values = lists[indexas];
			Player::OnConsoleMessage(peer, "Weil Magic bonus gained " + getItemDef(values).name + "");
			auto success = true;
			SaveItemMoreTimes(values, 1, peer, success);
		}

		if (static_cast<PlayerInfo*>(peer->data)->geigerlevel >= 3 && rand() % 100 <= 1) {
			Player::OnConsoleMessage(peer, "Obtained Uranium Block");
			auto success = true;
			SaveItemMoreTimes(4658, 1, peer, success);
		}

		if (static_cast<PlayerInfo*>(peer->data)->geigerlevel >= 5 && rand() % 100 <= 1) {
			Player::OnConsoleMessage(peer, "Obtained Electrical Power Cube");
			auto success = true;
			SaveItemMoreTimes(6976, 1, peer, success);
		}

		if (static_cast<PlayerInfo*>(peer->data)->geigerlevel >= 10 && rand() % 100 <= 1) {
			Player::OnConsoleMessage(peer, "Obtained Growtoken");
			auto success = true;
			SaveItemMoreTimes(1486, 1, peer, success);
		}

		int targetgeigerlevel = 600;
		if (static_cast<PlayerInfo*>(peer->data)->geigerlevel > 0) targetgeigerlevel = targetgeigerlevel * static_cast<PlayerInfo*>(peer->data)->geigerlevel;
		if (static_cast<PlayerInfo*>(peer->data)->geigerlevel == 0) targetgeigerlevel = 350;
		if (static_cast<PlayerInfo*>(peer->data)->geigerxp >= targetgeigerlevel && static_cast<PlayerInfo*>(peer->data)->geigerlevel < 10) {
			static_cast<PlayerInfo*>(peer->data)->geigerlevel++;
			static_cast<PlayerInfo*>(peer->data)->geigerxp = 0;
			SyncPlayerRoles(peer, static_cast<PlayerInfo*>(peer->data)->geigerlevel, "geiger");
		} else {
			static_cast<PlayerInfo*>(peer->data)->geigerxp += 10;
		}
		SendXP(peer, 15);
	} else {
		const auto checkx = static_cast<PlayerInfo*>(peer->data)->geigerx - static_cast<PlayerInfo*>(peer->data)->x;
		const auto checky = static_cast<PlayerInfo*>(peer->data)->y - static_cast<PlayerInfo*>(peer->data)->geigery;
		if (checkx > 200 || checkx < -200) {
			SendParticleEffect(peer, static_cast<PlayerInfo*>(peer->data)->x + 10, static_cast<PlayerInfo*>(peer->data)->y + 10, 0, 114, 0);
		} else if (checky > 200 || checky < -200) {
			SendParticleEffect(peer, static_cast<PlayerInfo*>(peer->data)->x + 10, static_cast<PlayerInfo*>(peer->data)->y + 10, 1, 114, 0);
		} else {
			SendParticleEffect(peer, static_cast<PlayerInfo*>(peer->data)->x + 10, static_cast<PlayerInfo*>(peer->data)->y + 10, 2, 114, 0);
		}
	}
}

inline void updateworldremove(ENetPeer* peer)
{
	size_t pos;
	while ((pos = static_cast<PlayerInfo*>(peer->data)->displayName.find("`2")) != std::string::npos) {
		static_cast<PlayerInfo*>(peer->data)->displayName.replace(pos, 2, "");
	}
	for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			Player::OnNameChanged(currentPeer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->displayName);
		}
	}
	/*if (static_cast<PlayerInfo*>(peer->data)->isNicked) {
		size_t pos;
		while ((pos = static_cast<PlayerInfo*>(peer->data)->displayName.find("`2")) != std::string::npos) {
			static_cast<PlayerInfo*>(peer->data)->displayName.replace(pos, 2, "");
		}
		for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer)) {
				Player::OnNameChanged(currentPeer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->displayName);
			}
		}
		return;
	}
	if (static_cast<PlayerInfo*>(peer->data)->isNicked && static_cast<PlayerInfo*>(peer->data)->NickPrefix == "") return;
	if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 2)
	{
		static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->rawName;
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				Player::OnNameChanged(currentPeer, static_cast<PlayerInfo*>(peer->data)->netID, "`6@" + static_cast<PlayerInfo*>(peer->data)->rawName);
			}
		}
	}
	else if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 1)
	{
		static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->rawName;
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				Player::OnNameChanged(currentPeer, static_cast<PlayerInfo*>(peer->data)->netID, "`#@" + static_cast<PlayerInfo*>(peer->data)->rawName);
			}
		}
	}
	else if (static_cast<PlayerInfo*>(peer->data)->adminLevel == 0)
	{
		static_cast<PlayerInfo*>(peer->data)->displayName = static_cast<PlayerInfo*>(peer->data)->rawName;
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				Player::OnNameChanged(currentPeer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->rawName);
			}
		}
	}*/
}

inline void treeModify(ENetPeer* peer, const int x, const int y, const int NetID)
{
	try
	{
		PlayerMoving data_;
		data_.packetType = 0xC;
		data_.x = 0;
		data_.y = 0;
		data_.punchX = x;
		data_.punchY = y;
		data_.XSpeed = 0;
		data_.YSpeed = 0;
		data_.netID = NetID;
		data_.plantingTree = 0;
		const auto raw = packPlayerMoving(&data_);
		memset(raw + 8, 0xFF, 4);
		SendPacketRaw(4, raw, 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
	}
	catch (...)
	{
		cout << "Error while replacing the tree..." << endl;
	}
}

inline bool isSeed(const int block)
{
	return block % 2 == 1;
}

inline void accessPlayer(ENetPeer* peer, const string name, WorldInfo* world)
{
	if (!world) return;
	auto retcode = -1;
	string player = "";
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) return;
	if (world->owner != static_cast<PlayerInfo*>(peer->data)->rawName) return;
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (peer != currentPeer)
		{
			if (isHere(peer, currentPeer))
			{
				if (static_cast<PlayerInfo*>(currentPeer->data)->rawName == name)
				{
					world->accessed.push_back(static_cast<PlayerInfo*>(currentPeer->data)->rawName + "|" + static_cast<PlayerInfo*>(currentPeer->data)->displayName);
					retcode = 0;
					player = static_cast<PlayerInfo*>(currentPeer->data)->displayName;
					break;
				}
			}
		}
	}
	if (retcode == 0)
	{
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Successfully given access to " + player, 0, true);
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				Player::PlayAudio(peer, "audio/secret.wav", 250);
			}
		}
	}
}

inline void DropBlock(ENetPeer* peer, const int x, const int y, const int foreground) {
	if (getItemDef(foreground).properties & Property_Dropless || getItemDef(foreground).properties & Property_NoBlock) return;
	if (foreground == 4762 || foreground == 7382 || foreground == 9460 || foreground == 9468 || foreground == 10028 || foreground == 10024) return;
	DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), foreground, 1, 0);
}

inline void SendDropSeed(ENetPeer* peer, const int x, const int y, const int foreground)
{
	if (getItemDef(foreground).properties & Property_NoSeed || getItemDef(foreground).properties & Property_Dropless) return;
	if (specialdrop != 0)
	{
		if ((rand() % 1200) <= 6)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), specialdrop, 1, 0);
		}
	}
	if ((rand() % 180000) <= 3)
	{
		DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5018, 1, 0);
	}
	/*fire chi*/
	if (getItemDef(foreground).blockType == BlockTypes::PAIN_BLOCK)
	{
		if ((rand() % 1800) <= 6)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5024, 1, 0);
		}
	}
	/*water chi*/
	if (foreground == 5034 || foreground == 5048 || foreground == 7520 || foreground == 7522 || foreground == 7772 || foreground == 7774 || foreground == 8240 || foreground == 3506 || foreground == 3584)
	{
		if ((rand() % 1800) <= 6)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5026, 1, 0);
		}
	}
	/*earth chi*/
	if (getItemDef(foreground).blockType == BlockTypes::FOREGROUND && foreground != 5034 && foreground != 5048 && foreground != 7520 && foreground != 7522 && foreground != 7772 && foreground != 7774 && foreground != 2794 || foreground != 2796 || foreground != 2810 && foreground != 8240 && foreground != 3506 && foreground != 3584)
	{
		if ((rand() % 1800) <= 6)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5028, 1, 0);
		}
	}
	/*wind chi*/
	if (foreground == 2794 || foreground == 2796 || foreground == 2810)
	{
		if ((rand() % 1800) <= 6)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5030, 1, 0);
		}
	}
	int chance;
	if (isSeed(foreground)) {
		SendXP(peer, 1);
		chance = (rand() % 350) + 1;
	}
	else if (getItemDef(foreground).rarity < 25) {
		SendXP(peer, 1);
		chance = (rand() % 110) + 1;
	}
	else if (getItemDef(foreground).rarity >= 25 && getItemDef(foreground).rarity < 40) {
		SendXP(peer, 2);
		chance = (rand() % 115) + 1;
	}
	else if (getItemDef(foreground).rarity >= 40 && getItemDef(foreground).rarity < 60) {
		SendXP(peer, 3);
		chance = (rand() % 120) + 1;
	}
	else if (getItemDef(foreground).rarity >= 60 && getItemDef(foreground).rarity < 80) {
		SendXP(peer, 4);
		chance = (rand() % 125) + 1;
	}
	else if (getItemDef(foreground).rarity >= 80 && getItemDef(foreground).rarity < 100) {
		SendXP(peer, 5);
		chance = (rand() % 130) + 1;
	}
	else if (getItemDef(foreground).rarity >= 100) {
		SendXP(peer, 6);
		chance = (rand() % 135) + 1;
	}
	if (chance <= 20) {
		if (isSeed(foreground)) {
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), foreground, 1, 0);
		} else {
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), foreground + 1, 1, 0);
		}
	}
}

inline void SendTradeEffect(ENetPeer* peer, const int id, const int netIDsrc, const int netIDdst, const int timeMs)
{
	PlayerMoving data;
	data.packetType = 0x13;
	data.punchX = id;
	data.punchY = id;
	const auto raw = packPlayerMoving(&data);
	auto netIdSrc = netIDsrc;
	auto netIdDst = netIDdst;
	auto three = 3;
	auto n1 = timeMs;
	memcpy(raw + 3, &three, 1);
	memcpy(raw + 4, &netIdDst, 4);
	memcpy(raw + 8, &netIdSrc, 4);
	memcpy(raw + 20, &n1, 4);
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			const auto raw2 = new BYTE[56];
			memcpy(raw2, raw, 56);
			SendPacketRaw(4, raw2, 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
	delete raw;
}

inline void DropGem(ENetPeer* peer, const int x, const int y)
{
	const auto world = getPlyersWorld(peer);
	auto b = getGemCount(world->items[x + (y * world->width)].foreground) + rand() % 1;
	if (b == 0 && static_cast<PlayerInfo*>(peer->data)->GemBuffDrop) b += 1;
	while (b > 0)
	{
		if (b >= 100)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 100, 0);
			b -= 100;
			for (auto i = 0; i < rand() % 1; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 10, 0);
			for (auto i = 0; i < rand() % 4; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
			continue;
		}
		if (b >= 50)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 50, 0);
			b -= 50;
			for (auto i = 0; i < rand() % 1; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 5, 0);
			for (auto i = 0; i < rand() % 3; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
			continue;
		}
		if (b >= 10)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 10, 0);
			b -= 10;
			for (auto i = 0; i < rand() % 4; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
			continue;
		}
		if (b >= 7)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 10, 0);
			b -= 5;
			for (auto i = 0; i < rand() % 2; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
			continue;
		}
		if (b >= 5)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 5, 0);
			b -= 5;
			for (auto i = 0; i < rand() % 2; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
			continue;
		}
		if (b >= 1)
		{
			DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
			b -= 1;
			for (auto i = 0; i < rand() % 1; i++) DropItem(peer, -1, x * 32 + (rand() % 8), y * 32 + (rand() % 16), 112, 1, 0);
			continue;
		}
	}
}

inline void SendTileData(WorldInfo* world, ENetPeer* peer, const int x, const int y, const int punchX, const int punchY)
{
	if (getItemDef(world->items[x + (y * world->width)].foreground).properties & Property_Dropless) return;
	/*The Basic Everything*/
	if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9454 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9456 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9458) return;
	if (!isSeed(world->items[x + (y * world->width)].foreground)) {
	DropGem(peer, x, y);
	if ((rand() % 300) <= 3) {
		DropBlock(peer, x, y, world->items[x + (y * world->width)].foreground);
	}
	if (static_cast<PlayerInfo*>(peer->data)->LuckyClover) /*luckyclover*/
	{
		const auto chance = (rand() % 125) + 1;
		if (chance <= 20)
		{
			static_cast<PlayerInfo*>(peer->data)->GemBuffDrop = true;
			Player::OnParticleEffect(peer, 49, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
			DropGem(peer, x, y);
		}
	}
	if (isRedAnces(peer) || FarmingEvent)
	{
		if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5084 || FarmingEvent)
		{
			const auto chance = (rand() % 125) + 1;
			if (chance <= 5)
			{
				static_cast<PlayerInfo*>(peer->data)->GemBuffDrop = true;
				Player::OnParticleEffect(peer, 29, punchX * 32, punchY * 32, 0);
				DropGem(peer, x, y);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5180) /*lvl2*/
		{
			const auto chance = (rand() % 125) + 1;
			if (chance <= 10)
			{
				static_cast<PlayerInfo*>(peer->data)->GemBuffDrop = true;
				Player::OnParticleEffect(peer, 29, punchX * 32, punchY * 32, 0);
				DropGem(peer, x, y);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5182) /*lvl3*/
		{
			const auto chance = (rand() % 125) + 1;
			if (chance <= 15)
			{
				static_cast<PlayerInfo*>(peer->data)->GemBuffDrop = true;
				Player::OnParticleEffect(peer, 29, punchX * 32, punchY * 32, 0);
				DropGem(peer, x, y);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5184) /*lvl4*/
		{
			const auto chance = (rand() % 125) + 1;
			if (chance <= 20)
			{
				static_cast<PlayerInfo*>(peer->data)->GemBuffDrop = true;
				Player::OnParticleEffect(peer, 29, punchX * 32, punchY * 32, 0);
				DropGem(peer, x, y);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5186) /*lvl5*/
		{
			const auto chance = (rand() % 125) + 1;
			if (chance <= 25)
			{
				static_cast<PlayerInfo*>(peer->data)->GemBuffDrop = true;
				Player::OnParticleEffect(peer, 29, punchX * 32, punchY * 32, 0);
				DropGem(peer, x, y);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5188) /*lvl6*/
		{
			const auto chance = (rand() % 125) + 1;
			if (chance <= 30)
			{
				static_cast<PlayerInfo*>(peer->data)->GemBuffDrop = true;
				Player::OnParticleEffect(peer, 29, punchX * 32, punchY * 32, 0);
				DropGem(peer, x, y);
			}
		}
	}
	else if (isBlueAnces(peer) || FarmingEvent)
	{
		if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5080 || FarmingEvent) /*lvl1*/
		{
			const auto chance = (rand() % 125) + 1;
			if (chance <= 3)
			{
				Player::OnParticleEffect(peer, 374, punchX * 32 + 20, punchY * 32 + 30, 0);
				DropBlock(peer, x, y, world->items[x + (y * world->width)].foreground);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5144) /*lvl2*/
		{
			const auto chance = (rand() % 125) + 1;
			if (chance <= 6)
			{
				Player::OnParticleEffect(peer, 374, punchX * 32 + 20, punchY * 32 + 30, 0);
				DropBlock(peer, x, y, world->items[x + (y * world->width)].foreground);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5146) /*lvl3*/
		{
			const auto chance = (rand() % 125) + 1;
			if (chance <= 9)
			{
				Player::OnParticleEffect(peer, 374, punchX * 32 + 20, punchY * 32 + 30, 0);
				DropBlock(peer, x, y, world->items[x + (y * world->width)].foreground);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5148) /*lvl4*/
		{
			const auto chance = (rand() % 125) + 1;
			if (chance <= 12)
			{
				Player::OnParticleEffect(peer, 374, punchX * 32 + 20, punchY * 32 + 30, 0);
				DropBlock(peer, x, y, world->items[x + (y * world->width)].foreground);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5150) /*lvl5*/
		{
			const auto chance = (rand() % 125) + 1;
			if (chance <= 15)
			{
				Player::OnParticleEffect(peer, 374, punchX * 32 + 20, punchY * 32 + 30, 0);
				DropBlock(peer, x, y, world->items[x + (y * world->width)].foreground);
			}
		}
		else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 5152) /*lvl6*/
		{
			const auto chance = (rand() % 125) + 1;
			if (chance <= 18)
			{
				Player::OnParticleEffect(peer, 374, punchX * 32 + 20, punchY * 32 + 30, 0);
				DropBlock(peer, x, y, world->items[x + (y * world->width)].foreground);
			}
		}
	}
	}
	SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
}

inline void SendGuildPoints(ENetPeer* peer, int amount)
{
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) return;
	if (static_cast<PlayerInfo*>(peer->data)->guild != "")
	{
		try
		{
			auto currentgpoints = 0;
			ifstream guildstream1("guildrewards/guildpoints/" + static_cast<PlayerInfo*>(peer->data)->guild + ".txt");
			guildstream1 >> currentgpoints;
			guildstream1.close();
			if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9508)
			{
				amount *= 2;
				auto newgpoints = currentgpoints + amount;
				ofstream guildstream3("guildrewards/guildpoints/" + static_cast<PlayerInfo*>(peer->data)->guild + ".txt");
				guildstream3 << newgpoints;
				guildstream3.close();
			}
			else
			{
				auto newgpoints = currentgpoints + amount;
				ofstream guildstream3("guildrewards/guildpoints/" + static_cast<PlayerInfo*>(peer->data)->guild + ".txt");
				guildstream3 << newgpoints;
				guildstream3.close();
			}
			// M CONTRIBUTION
			auto currentplayercontribution = 0;
			namespace fs = std::experimental::filesystem;
			if (!fs::is_directory("guildrewards/contribution/" + static_cast<PlayerInfo*>(peer->data)->guild) || !fs::exists("guildrewards / contribution / " + static_cast<PlayerInfo*>(peer->data)->guild))
			{
				fs::create_directory("guildrewards/contribution/" + static_cast<PlayerInfo*>(peer->data)->guild);
				ifstream mcontr("guildrewards/contribution/" + static_cast<PlayerInfo*>(peer->data)->guild + "/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
				mcontr >> currentplayercontribution;
				mcontr.close();
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9508)
				{
					amount *= 2;
					auto newcontr = currentplayercontribution + amount;
					ofstream savecon("guildrewards/contribution/" + static_cast<PlayerInfo*>(peer->data)->guild + "/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
					savecon << newcontr;
					savecon.close();
				}
				else
				{
					auto newcontr = currentplayercontribution + amount;
					ofstream savecon("guildrewards/contribution/" + static_cast<PlayerInfo*>(peer->data)->guild + "/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
					savecon << newcontr;
					savecon.close();
				}
			}
			else
			{
				ifstream mcontr("guildrewards/contribution/" + static_cast<PlayerInfo*>(peer->data)->guild + "/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
				mcontr >> currentplayercontribution;
				mcontr.close();
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9508)
				{
					amount *= 2;
					auto newcontr = currentplayercontribution + amount;
					ofstream savecon("guildrewards/contribution/" + static_cast<PlayerInfo*>(peer->data)->guild + "/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
					savecon << newcontr;
					savecon.close();
				}
				else
				{
					auto newcontr = currentplayercontribution + amount;
					ofstream savecon("guildrewards/contribution/" + static_cast<PlayerInfo*>(peer->data)->guild + "/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
					savecon << newcontr;
					savecon.close();
				}
			}
		}
		catch (...)
		{
			cout << "SendGuildPoints Function Failed" << endl;
		}
	}
}

inline void SendFarmableDrop(ENetPeer* peer, int chance, int x, int y)
{
	try
	{
		x *= 32;
		y *= 32;
		if (static_cast<PlayerInfo*>(peer->data)->skill == "Farmer") chance += 100;
		auto valgem = rand() % chance;
		if (static_cast<PlayerInfo*>(peer->data)->LuckyClover)
		{
			const auto luckychance = (rand() % 100) + 1;
			if (luckychance <= 20)
			{
				valgem += 100;
				for (auto currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, currentPeer))
					{
						Player::OnParticleEffect(currentPeer, 49, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
					}
				}
			}
		}

		while (valgem >= 100) {
			valgem -= 100;
			DropItem(peer, -1, x + rand() % 18, y + rand() % 18, 112, 100, 0);
		}

		while (valgem >= 50) {
			valgem -= 50;
			DropItem(peer, -1, x + rand() % 18, y + rand() % 18, 112, 50, 0);
		}

		while (valgem >= 10) {
			valgem -= 10;
			DropItem(peer, -1, x + rand() % 18, y + rand() % 18, 112, 10, 0);
		}

		while (valgem >= 5) {
			valgem -= 5;
			DropItem(peer, -1, x + rand() % 18, y + rand() % 18, 112, 5, 0);
		}

		while (valgem >= 1) {
			valgem -= 1;
			DropItem(peer, -1, x + rand() % 18, y + rand() % 18, 112, 1, 0);
		}

		/*ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
		const string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`^You found `9" + std::to_string(valgem) + " `2Gems`w!", 0, false);
		const auto gembux = atoi(content.c_str());
		const auto fingembux = gembux + valgem;
		ofstream myfile;
		myfile.open("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
		myfile << fingembux;
		myfile.close();
		const auto gemcalc = gembux + valgem;
		Player::OnSetBux(peer, gemcalc, 0);*/

	}
	catch (...)
	{
		cout << "SendFarmableDrop Function Failed" << endl;
	}
}
inline void SendFarmableDropCustom(ENetPeer* peer, int chance_start, int chance_end)
{
	try
	{
		if (static_cast<PlayerInfo*>(peer->data)->skill == "Farmer") chance_end += 10;
		auto valgem = rand() % chance_end + chance_start;
		if (static_cast<PlayerInfo*>(peer->data)->LuckyClover)
		{
			const auto luckychance = (rand() % 100) + 1;
			if (luckychance <= 20)
			{
				valgem += 10;
				for (auto currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, currentPeer))
					{
						Player::OnParticleEffect(currentPeer, 49, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
					}
				}
			}
		}
		ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
		const string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`^You found `9" + std::to_string(valgem) + " `2Gems`w!", 0, false);
		const auto gembux = atoi(content.c_str());
		const auto fingembux = gembux + valgem;
		ofstream myfile;
		myfile.open("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
		myfile << fingembux;
		myfile.close();
		const auto gemcalc = gembux + valgem;
		Player::OnSetBux(peer, gemcalc, 0);
	}
	catch (...)
	{
		cout << "SendFarmableDrop Function Failed" << endl;
	}
}
inline void SendPlacingEffect(ENetPeer* peer, const int punchX, const int punchY, const int effect)
{
	const float hi = punchX * 32;
	const float hi2 = punchY * 32;
	for (auto currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			Player::OnParticleEffect(currentPeer, effect, hi, hi2, 0);
		}
	}
}

inline void SendHarvestFestivalDrop(ENetPeer* peer, const int x, const int y, const int rarity)
{
	// ReSharper disable once CppInitializedValueIsAlwaysRewritten
	auto TargetChance = 0;
	if (rarity <= 15) TargetChance = 6;
	else if (rarity <= 25) TargetChance = 10;
	else if (rarity <= 35) TargetChance = 12;
	else if (rarity <= 45) TargetChance = 14;
	else if (rarity <= 55) TargetChance = 18;
	else if (rarity <= 65) TargetChance = 20;
	else if (rarity <= 75) TargetChance = 23;
	else if (rarity <= 85) TargetChance = 25;
	else if (rarity <= 95) TargetChance = 28;
	else if (rarity <= 115) TargetChance = 30;
	else TargetChance = 30;
	const auto chance = (rand() % 100) + 1;
	if (chance <= TargetChance)
	{
		vector<int> CakeBase{ 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 3870, 7058, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 7058, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1828, 3870, 3870, 7058, 1058, 1094, 1096, 1098, 1058, 1828, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 10030, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1094, 1096, 1098, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1094, 1096, 1098, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1094, 1096, 1098, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098, 1058, 1094, 1096, 1098 };
		srand(GetTickCount());
		const int Index = rand() % CakeBase.size();
		const auto ItemID = CakeBase[Index];
		DropItem(peer, -1, x * 32, y * 32, ItemID, 1, 0);
		for (auto currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				Player::OnParticleEffect(currentPeer, 50, x * 32, y * 32, 0);
			}
		}
	}
}

inline void SendCombiner(ENetPeer* peer, const int x, const int y, const int ItemID1, const int ItemID2, const int ItemID3, const int ItemID1Count, const int ItemID2Count, const int ItemID3Count, const int ResultItemID, const bool HarvestFestivalOnly, const int ResultItemCount = 1)
{
	//if (HarvestFestivalOnly && !HarvestEvent) return;
	auto TwoIngredients = false;
	if (ItemID3 == 0) TwoIngredients = true;
	auto world = getPlyersWorld(peer);
	/*auto TotalUid = 0;
	const int itemcount = world->droppedItems.size();
	for (auto i = 0; i < itemcount; i++)
	{
		TotalUid = world->droppedItems[i].uid;
	}
	TotalUid += 1;
	if (world->droppedCount != TotalUid)
	{
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "There are too much items floating in this world!", 0, true);
		return;
	}*/
	for (auto i = 0; i < world->droppedItems.size(); i++)
	{
		if (round(world->droppedItems.at(i).x / 32) == x && round(world->droppedItems.at(i).y / 32) == y || round(world->droppedItems.at(i).x / 32) + 1 == x && round(world->droppedItems.at(i).y / 32) == y)
		{
			if (world->droppedItems.at(i).id == ItemID1 && world->droppedItems.at(i).count == ItemID1Count)
			{
				for (auto pos1 = 0; pos1 < world->droppedItems.size(); pos1++)
				{
					if (world->droppedItems.at(pos1).id == ItemID2 && world->droppedItems.at(pos1).count == ItemID2Count)
					{
						for (auto pos = 0; pos < world->droppedItems.size(); pos++)
						{
							if (TwoIngredients)
							{
								vector<int> ItemBase;
								vector<int> ItemBase2;
								RemoveDroppedItem(peer, world->droppedItems.at(i).uid, world);
								RemoveDroppedItem(peer, world->droppedItems.at(pos1).uid, world);
								ItemBase2.push_back(world->droppedItems.at(i).uid);
								ItemBase.push_back(world->droppedItems.at(pos1).uid);
								for (auto ClearItem = 0; ClearItem < ItemBase.size(); ClearItem++) processTakeServer(peer, ItemBase.at(ClearItem));
								for (auto ClearItem2 = 0; ClearItem2 < ItemBase2.size(); ClearItem2++) processTakeServer(peer, ItemBase2.at(ClearItem2));
								DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), ResultItemID, ResultItemCount, 0);
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Science!", 0, true);
								break;
							}
							else
							{
								if (world->droppedItems.at(pos).id == ItemID3 && world->droppedItems.at(pos).count == ItemID3Count)
								{
									vector<int> ItemBase;
									vector<int> ItemBase2;
									vector<int> ItemBase3;
									RemoveDroppedItem(peer, world->droppedItems.at(i).uid, world);
									RemoveDroppedItem(peer, world->droppedItems.at(pos1).uid, world);
									RemoveDroppedItem(peer, world->droppedItems.at(pos).uid, world);
									ItemBase2.push_back(world->droppedItems.at(i).uid);
									ItemBase.push_back(world->droppedItems.at(pos1).uid);
									ItemBase3.push_back(world->droppedItems.at(pos).uid);
									for (auto ClearItem = 0; ClearItem < ItemBase.size(); ClearItem++) processTakeServer(peer, ItemBase.at(ClearItem));
									for (auto ClearItem2 = 0; ClearItem2 < ItemBase2.size(); ClearItem2++) processTakeServer(peer, ItemBase2.at(ClearItem2));
									for (auto ClearItem3 = 0; ClearItem3 < ItemBase3.size(); ClearItem3++) processTakeServer(peer, ItemBase3.at(ClearItem3));
									DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), ResultItemID, ResultItemCount, 0);
									Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "SCIENCE!", 0, true);
									break;
								}
							}
						}
						break;
					}
				}
				break;
			}
		}
	}
}

inline void SendFishing(ENetPeer* peer, const int netID, const int x, const int y)
{
	PlayerMoving p;
	p.packetType = 0x1F;
	p.netID = netID;
	p.punchX = x;
	p.punchY = y;
	SendPacketRaw(4, packPlayerMoving(&p), 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
}

inline void SendGhost(ENetPeer* peer) {
	if (static_cast<PlayerInfo*>(peer->data)->canWalkInBlocks == false) {
		if (static_cast<PlayerInfo*>(peer->data)->skinColor == 0x8295C3FF || static_cast<PlayerInfo*>(peer->data)->skinColor == 2190853119 || static_cast<PlayerInfo*>(peer->data)->skinColor == 2527912447 || static_cast<PlayerInfo*>(peer->data)->skinColor == 2864971775 || static_cast<PlayerInfo*>(peer->data)->skinColor == 3033464831 || static_cast<PlayerInfo*>(peer->data)->skinColor == 3370516479) {
			static_cast<PlayerInfo*>(peer->data)->skinColor = -2450;
			sendClothes(peer);
		}
		static_cast<PlayerInfo*>(peer->data)->canWalkInBlocks = true;
		send_state(peer);
		sendClothes(peer);
		Player::OnConsoleMessage(peer, "`oYour atoms are suddenly aware of quantum tunneling. (`$Ghost in the Shell `omod added)``");
		Player::PlayAudio(peer, "audio/dialog_confirm.wav", 0);
	} else {
		if (static_cast<PlayerInfo*>(peer->data)->skinColor == -2450) {
			static_cast<PlayerInfo*>(peer->data)->skinColor = 0x8295C3FF;
			sendClothes(peer);
		}
		static_cast<PlayerInfo*>(peer->data)->canWalkInBlocks = false;
		send_state(peer);
		Player::OnConsoleMessage(peer, "`oYour body stops shimmering and returns to normal. (`$Ghost in the Shell `omod removed)``");
		Player::PlayAudio(peer, "audio/dialog_confirm.wav", 0);
	}
}

inline void SendVendDialog(ENetPeer* peer, WorldInfo* world) {
	auto x = static_cast<PlayerInfo*>(peer->data)->lastPunchX;
	auto y = static_cast<PlayerInfo*>(peer->data)->lastPunchY;
	auto squaresign = x + (y * world->width);
	string type = "";
	if (world->items[x + (y * world->width)].rm) {
		type = "\nadd_checkbox|chk_peritem|World Locks per Item|1\nadd_checkbox|chk_perlock|Items per World Lock|0";
	}
	if (world->items[x + (y * world->width)].opened) {
		type = "\nadd_checkbox|chk_peritem|World Locks per Item|0\nadd_checkbox|chk_perlock|Items per World Lock|1";
	}
	if (world->items[x + (y * world->width)].rm && world->items[x + (y * world->width)].opened) {
		type = "\nadd_checkbox|chk_peritem|World Locks per Item|1\nadd_checkbox|chk_perlock|Items per World Lock|1";
	}
	auto currentworld = static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign);
	string withdrawdialog = "";
	if (world->items[x + (y * world->width)].vdraw > 0) withdrawdialog = "\nadd_smalltext|`oYou have earned " + to_string(world->items[x + (y * world->width)].vdraw) + " World Locks.``|left|\nadd_button|withdraw|Withdraw World Locks|";
	if (world->items[x + (y * world->width)].vid == 0 || world->items[x + (y * world->width)].vcount == 0) {
		Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_textbox|This machine is empty.|left|\nadd_item_picker|stockitem|`wPut an item in``|Choose an item to put in the machine!|" + withdrawdialog + "|\nend_dialog|vending|Close||");
	}
	else if (world->items[x + (y * world->width)].vcount != 0) {
		string addthemdialog = "";
		auto mtitems = 0;
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++) {
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == world->items[x + (y * world->width)].vid) {
				mtitems = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
				break;
			}
		}
		if (mtitems != 0) {
			addthemdialog = "\nadd_smalltext|`oYou have " + to_string(mtitems) + " " + getItemDef(world->items[x + (y * world->width)].vid).name + " in your backpack.``|left|\nadd_button|addvend|Add them to the machine|";
		}
		string saledialog = "\nadd_textbox|Not currently for sale!|left|";
		if (world->items[x + (y * world->width)].vprice != 0) {
			if (world->items[x + (y * world->width)].opened) saledialog = "\nadd_textbox|For a cost of:|left|\nadd_label_with_icon|small|1 x `8World Lock``|left|242|\nadd_spacer|small|\nadd_textbox|You will get:|left|\nadd_label_with_icon|small|" + to_string(world->items[x + (y * world->width)].vprice) + " x `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|";
			else saledialog = "\nadd_textbox|For a cost of:|left|\nadd_label_with_icon|small|" + to_string(world->items[x + (y * world->width)].vprice) + " x `8World Lock``|left|242|\nadd_spacer|small|\nadd_textbox|You will get:|left|\nadd_label_with_icon|small|1 x `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|";
		}
		Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label_with_icon|sml|The machine contains a total of " + to_string(world->items[x + (y * world->width)].vcount) + " `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``.|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|" + saledialog + "|" + addthemdialog + "|\nadd_button|pullstock|Empty the machine|noflags|0|0|\nadd_smalltext|`5(Vending Machine will not function when price is set to 0)``|left|\nadd_text_input|setprice|Price|" + to_string(world->items[x + (y * world->width)].vprice) + "|5|" + type + "|" + withdrawdialog + "|\nend_dialog|vending|Close|Update|");
	}
	else if (world->items[x + (y * world->width)].vcount != 0 && world->items[x + (y * world->width)].vprice != 0) {
		if (world->items[x + (y * world->width)].opened) Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label_with_icon|sml|The machine contains a total of " + to_string(world->items[x + (y * world->width)].vcount) + " `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``.|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_textbox|For a cost of:|left|\nadd_label_with_icon|small|1 x `8World Lock``|left|242|\nadd_spacer|small|\nadd_textbox|You will get:|left|\nadd_label_with_icon|small|" + to_string(world->items[x + (y * world->width)].vprice) + " x `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_button|pullstock|Empty the machine|noflags|0|0|\nadd_smalltext|`5(Vending Machine will not function when price is set to 0)``|left|\nadd_text_input|setprice|Price|" + to_string(world->items[x + (y * world->width)].vprice) + "|5|" + type + "|" + withdrawdialog + "|\nend_dialog|vending|Close|Update|");
		else Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label_with_icon|sml|The machine contains a total of " + to_string(world->items[x + (y * world->width)].vcount) + " `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``.|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_textbox|For a cost of:|left|\nadd_label_with_icon|small|" + to_string(world->items[x + (y * world->width)].vprice) + " x `8World Lock``|left|242|\nadd_spacer|small|\nadd_textbox|You will get:|left|\nadd_label_with_icon|small|1 x `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_button|pullstock|Empty the machine|noflags|0|0|\nadd_smalltext|`5(Vending Machine will not function when price is set to 0)``|left|\nadd_text_input|setprice|Price|" + to_string(world->items[x + (y * world->width)].vprice) + "|5|" + type + "|" + withdrawdialog + "|\nend_dialog|vending|Close|Update|");
	}
}

inline void SendBuyerVendDialog(ENetPeer* peer, WorldInfo* world) {
	int x = static_cast<PlayerInfo*>(peer->data)->lastPunchX;
	int y = static_cast<PlayerInfo*>(peer->data)->lastPunchY;
	auto squaresign = x + (y * world->width);
	auto currentworld = static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign);
	if (world->items[x + (y * world->width)].vid == 0 || world->items[x + (y * world->width)].vcount == 0 || world->items[x + (y * world->width)].vprice == 0 || world->items[x + (y * world->width)].vcount < world->items[x + (y * world->width)].vprice && world->items[x + (y * world->width)].opened) {
		Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_textbox|This machine is out of order.|left|\nend_dialog|vending|Close||");
	}
	else if (world->items[x + (y * world->width)].vcount != 0 && world->items[x + (y * world->width)].vprice == 0) {
		if (world->items[x + (y * world->width)].opened) Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label_with_icon|sml|The machine contains a total of " + to_string(world->items[x + (y * world->width)].vcount) + " `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``.|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_textbox|For a cost of:|left|\nadd_label_with_icon|small|1 x `8World Lock``|left|242|\nadd_spacer|small|\nadd_textbox|You will get:|left|\nadd_label_with_icon|small|" + to_string(world->items[x + (y * world->width)].vprice) + " x `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_textbox|You'll need to wait for the owner to stock up to at least 1 World Lock's worth before you can buy.|left|\nend_dialog|vending|Close||");
		else Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label_with_icon|sml|The machine contains a total of " + to_string(world->items[x + (y * world->width)].vcount) + " `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``.|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_textbox|For a cost of:|left|\nadd_label_with_icon|small|" + to_string(world->items[x + (y * world->width)].vprice) + " x `8World Lock``|left|242|\nadd_spacer|small|\nadd_textbox|You will get:|left|\nadd_label_with_icon|small|1 x `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_textbox|You'll need to wait for the owner to stock up to at least 1 World Lock's worth before you can buy.|left|\nend_dialog|vending|Close||");
	}
	else if (world->items[x + (y * world->width)].vcount != 0) {
		auto worldlocks = 0;
		auto diamondlocks = 0;
		auto locks = 0;
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++) {
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 242) {
				worldlocks = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
			}
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1796) {
				diamondlocks = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
			}
		}
		if (diamondlocks > 0) {
			locks = diamondlocks * 100;
		}
		locks += worldlocks;
		if (world->items[x + (y * world->width)].opened) Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label_with_icon|sml|The machine contains a total of " + to_string(world->items[x + (y * world->width)].vcount) + " `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``.|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_textbox|For a cost of:|left|\nadd_label_with_icon|small|1 x `8World Lock``|left|242|\nadd_spacer|small|\nadd_textbox|You will get:|left|\nadd_label_with_icon|small|" + to_string(world->items[x + (y * world->width)].vprice) + " x `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_textbox|You have " + to_string(locks) + " World Locks.|left|\nadd_text_input|buycount|How many would you like to buy?|0|3|\nend_dialog|vending|Close|Buy|");
		else Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wVending Machine``|left|2978|\nadd_spacer|small|\nadd_label_with_icon|sml|The machine contains a total of " + to_string(world->items[x + (y * world->width)].vcount) + " `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``.|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_textbox|For a cost of:|left|\nadd_label_with_icon|small|" + to_string(world->items[x + (y * world->width)].vprice) + " x `8World Lock``|left|242|\nadd_spacer|small|\nadd_textbox|You will get:|left|\nadd_label_with_icon|small|1 x `2" + getItemDef(world->items[x + (y * world->width)].vid).name + "``|left|" + to_string(world->items[x + (y * world->width)].vid) + "|\nadd_spacer|small|\nadd_textbox|You have " + to_string(locks) + " World Locks.|left|\nadd_text_input|buycount|How many would you like to buy?|0|3|\nend_dialog|vending|Close|Buy|");
	}
}

inline void SendWeather(ENetPeer* peer, int tile, WorldInfo* world, int x, int y)
{
	if (tile == 18)
	{
		if (world->items[x + (y * world->width)].foreground == 1490)
		{
			if (world->weather == 10)
			{
				world->weather = 0;
			}
			else
			{
				world->weather = 10;
			}
			ENetPeer* currentPeer;
			for (currentPeer = server->peers;
				currentPeer < &server->peers[server->peerCount];
				++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
					continue;
				if (isHere(peer, currentPeer))
				{
					GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
					ENetPacket* packet2 = enet_packet_create(p2.data,
						p2.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(currentPeer, 0, packet2);
					delete p2.data;
					continue;
				}
			}
		}
	}
	if (tile == 18)
	{
		if (world->items[x + (y * world->width)].foreground == 934)
		{
			if (world->weather == 2)
			{
				world->weather = 0;
			}
			else
			{
				world->weather = 2;
			}
			ENetPeer* currentPeer;
			for (currentPeer = server->peers;
				currentPeer < &server->peers[server->peerCount];
				++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
					continue;
				if (isHere(peer, currentPeer))
				{
					GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
					ENetPacket* packet2 = enet_packet_create(p2.data,
						p2.len,
						ENET_PACKET_FLAG_RELIABLE);
					enet_peer_send(currentPeer, 0, packet2);
					delete p2.data;
					continue;
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 946)
			{
				if (world->weather == 3)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 3;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 1490)
			{
				if (world->weather == 10)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 10;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 932)
			{
				if (world->weather == 4)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 4;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 984)
			{
				if (world->weather == 5)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 5;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 1210)
			{
				if (world->weather == 8)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 8;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 1364)
			{
				if (world->weather == 11)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 11;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 1750)
			{
				if (world->weather == 15)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 15;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 2046)
			{
				if (world->weather == 17)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 17;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 2284)
			{
				if (world->weather == 18)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 18;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 2744)
			{
				if (world->weather == 19)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 19;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 3252)
			{
				if (world->weather == 20)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 20;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 3446)
			{
				if (world->weather == 21)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 21;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 3534)
			{
				if (world->weather == 22)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 22;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 3694)
			{
				if (world->weather == 25)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 25;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 32)
		{
			if (world->items[x + (y * world->width)].foreground == 3832)
			{ // stuff weather dialog
				if (x != 0)
				{
					static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
				}
				if (y != 0)
				{
					static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
				}
				GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`o\n\nadd_label_with_icon|big|`wStuff Weather Machine``|left|3832|\nadd_item_picker|stuffitem|Edit Item|Choose any item you want to pick|\nadd_spacer|small|\nadd_text_input|gravity|Gravity Value||4|\nadd_spacer|small|\nadd_quick_exit|\nend_dialog|stuff|Nevermind||"));
				ENetPacket* packet = enet_packet_create(p.data,
					p.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
				delete p.data;
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 1490)
			{
				if (world->weather == 10)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 10;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 4242)
			{
				if (world->weather == 30)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 30;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 4486)
			{
				if (world->weather == 31)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 31;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 4776)
			{
				if (world->weather == 32)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 32;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 4892)
			{
				if (world->weather == 33)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 33;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 5000)
			{
				if (world->weather == 34)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 34;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 5112)
			{
				if (world->weather == 35)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 35;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 5654)
			{
				if (world->weather == 36)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 36;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 5716)
			{
				if (world->weather == 37)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 37;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 5958)
			{
				if (world->weather == 38)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 38;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 6854)
			{
				if (world->weather == 42)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 42;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
	{
		if (tile == 18)
		{
			if (world->items[x + (y * world->width)].foreground == 7644)
			{
				if (world->weather == 44)
				{
					world->weather = 0;
				}
				else
				{
					world->weather = 44;
				}
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
						ENetPacket* packet2 = enet_packet_create(p2.data,
							p2.len,
							ENET_PACKET_FLAG_RELIABLE);
						enet_peer_send(currentPeer, 0, packet2);
						delete p2.data;
						continue;
					}
				}
			}
		}
	}
}



inline void complete_surgery(ENetPeer* peer)
{

	if (static_cast<PlayerInfo*>(peer->data)->SurgerySkill < 100) static_cast<PlayerInfo*>(peer->data)->SurgerySkill++;
	vector<int> surg_rewards{ 3172, 1258, 1260, 1262, 1264, 1266, 1268, 1270, 4308, 4310, 4312, 4314, 4316, 4318, 3172, 1258, 1260, 1262, 1264, 1266, 1268, 1270, 4308, 4310, 4312, 4314, 4316, 4318, 4296, 1242, 1244, 1246, 1248, 1282, 1284, 1286, 1290, 1288, 1292, 1294, 1256, 2586, 782, 3536, 764, 4176, 4322, 4080, 2992, 2976, 3790, 4990, 1506, 1274, 9000, 1252, 8284, 8954, 8534, 8478, 8480, 8486, 8484, 8482, 8468, 8494, 8466, 8490, 8456, 8458, 8496, 8472, 6398, 6426, 6340, 6342, 6350, 6818, 8244, 8242, 8240, 8452, 8454, 8488, 8498, 8474, 8476, 8492 };


	
	if (static_cast<PlayerInfo*>(peer->data)->cloth_face == 312) 
	{
		surg_rewards.push_back(5482);
	}
	if (WinterfestEvent)
	{
		surg_rewards.push_back(2240);
		surg_rewards.push_back(3204);
	}
	if (SuperpineappleEvent)
	{
		surg_rewards.push_back(6114);
	}
	if (SurgeryDay)
	{
		surg_rewards.push_back(4328);
		surg_rewards.push_back(4326);
		surg_rewards.push_back(4330);
		surg_rewards.push_back(4324);
		surg_rewards.push_back(4334);
	}

	auto reward_id = surg_rewards[rand() % surg_rewards.size()];

	auto count = 1;

	if (reward_id == 1290) count = 10;
	if (reward_id == 1288) count = 5;
	if (reward_id == 1292) count = 5;
	if (reward_id == 1294) count = 5;

	if (reward_id == 1258) count = 5;
	if (reward_id == 1260) count = 5;
	if (reward_id == 1262) count = 5;
	if (reward_id == 1264) count = 5;
	if (reward_id == 1266) count = 5;
	if (reward_id == 1268) count = 5;
	if (reward_id == 1270) count = 5;
	if (reward_id == 4308) count = 5;
	if (reward_id == 4310) count = 5;
	if (reward_id == 4312) count = 5;
	if (reward_id == 4314) count = 5;
	if (reward_id == 4316) count = 5;
	if (reward_id == 4318) count = 5;
	if (reward_id == 4296) count = 5;



	if (reward_id == 8284)
	{
		if ((rand() % 10000) <= 5) {}
		else reward_id = 1244;
	}
	if (reward_id == 1506)
	{
		if ((rand() % 50) <= 5) {}
		else reward_id = 1242;
	}
	if (reward_id == 8452)
	{
		if ((rand() % 50) <= 5) {}
		else reward_id = 1246;
	}
	if (reward_id == 8488)
	{
		if ((rand() % 50) <= 5) {}
		else reward_id = 1248;
	}
	if (reward_id == 8492)
	{
		if ((rand() % 50) <= 5) {}
		else reward_id = 1242;
	}
	if (reward_id == 8494)
	{
		if ((rand() % 50) <= 5) {}
		else reward_id = 1244;
	}
	if (reward_id == 8496)
	{
		if ((rand() % 50) <= 5) {}
		else reward_id = 1246;
	}
	if (reward_id == 1252)
	{
		if ((rand() % 50) <= 5) {}
		else reward_id = 1248;
	}
	if (reward_id == 8954)
	{
		if ((rand() % 50) <= 5) {}
		else reward_id = 2586;
	}

	auto success = true;
	SaveItemMoreTimes(reward_id, count, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery");
	SaveItemMoreTimes(4298, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery");
	Player::PlayAudio(peer, "audio/double_chance.wav", 0);
	Player::OnConsoleMessage(peer, "`oYou got " + to_string(count) + " `2" + getItemDef(reward_id).name + " `oand a `3Caduceus`o!");
	Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wAfter a surgery like that, you decide you deserve `w" + to_string(count) + " " + getItemDef(reward_id).name + "`w.", 0, true);
	if (SurgeryDay) Player::OnConsoleMessage(peer, "Congratulations on your successful surgery! (`$Recovery`` mod added, `$30 min`` left)");
	else Player::OnConsoleMessage(peer, "Congratulations on your successful surgery! (`$Recovery`` mod added, `$20 min`` left)");
	ENetPeer* currentPeer;
	for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			Player::PlayAudio(currentPeer, "audio/metal_destroy.wav", 0);
		}
	}
	const auto world = getPlyersWorld(peer);
	if (static_cast<PlayerInfo*>(peer->data)->lastPunchX >= 0 && static_cast<PlayerInfo*>(peer->data)->lastPunchY >= 0)
	{
		world->items[static_cast<PlayerInfo*>(peer->data)->lastPunchX + (static_cast<PlayerInfo*>(peer->data)->lastPunchY * world->width)].foreground = 0;
		PlayerMoving data3;
		data3.packetType = 0x3;
		data3.characterState = 0x0;
		data3.x = static_cast<PlayerInfo*>(peer->data)->lastPunchX;
		data3.y = static_cast<PlayerInfo*>(peer->data)->lastPunchY;
		data3.punchX = static_cast<PlayerInfo*>(peer->data)->lastPunchX;
		data3.punchY = static_cast<PlayerInfo*>(peer->data)->lastPunchY;
		data3.XSpeed = 0;
		data3.YSpeed = 0;
		data3.netID = -1;
		data3.plantingTree = 0;
		for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				auto raw = packPlayerMoving(&data3);
				raw[2] = 0;
				raw[3] = 0;
				SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
				Player::OnParticleEffect(currentPeer, 57, static_cast<PlayerInfo*>(peer->data)->lastPunchX * 32, static_cast<PlayerInfo*>(peer->data)->lastPunchY * 32, 0);
			}
		}
	}
	end_surgery(peer, false);

}

inline bool surgery_skill_fail(ENetPeer* peer) {
	const auto chance = 85 + static_cast<PlayerInfo*>(peer->data)->SurgerySkill;
	if (rand() % 200 < chance) return false; /*nera*/
	else return true;
}

inline void DayTimer() {
	while (DayTimer) {
		sleep(15);
		LoadEvents();
		TimerHandler = mysql_init(nullptr);
		TimerHandler = mysql_real_connect(TimerHandler, ip, user, pass, database, 0, nullptr, 0);
		ENetPeer* currentPeer;
		for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (currentPeer->data == nullptr) continue;
			if (!static_cast<PlayerInfo*>(currentPeer->data)->haveGrowId || static_cast<PlayerInfo*>(currentPeer->data)->currentWorld == "EXIT" || !static_cast<PlayerInfo*>(currentPeer->data)->isIn) continue;
			if (static_cast<PlayerInfo*>(currentPeer->data)->isCursed) {
				auto cooldownleft = calcBanDuration(static_cast<PlayerInfo*>(currentPeer->data)->lastCursed);
				if (cooldownleft < 1) {
					Player::OnConsoleMessage(currentPeer, "You are no longer bound to the netherworld, you're free to go. (`$Curse ``mod removed)");
					static_cast<PlayerInfo*>(currentPeer->data)->skinColor = 0x8295C3FF;
					sendClothes(currentPeer);
					static_cast<PlayerInfo*>(currentPeer->data)->isCursed = false;
					send_state(currentPeer);
					string q = "UPDATE PlayerDatabase SET timecursed = '0' WHERE username = '" + static_cast<PlayerInfo*>(currentPeer->data)->rawName + "' LIMIT 1";
					if (mysql_query(TimerHandler, q.c_str())) {
						cout << mysql_error(TimerHandler) << endl;
						enet_peer_disconnect_later(currentPeer, 0);
						continue;
					}
				}
			}
			if (static_cast<PlayerInfo*>(currentPeer->data)->Fishing && !static_cast<PlayerInfo*>(currentPeer->data)->TriggerFish && static_cast<PlayerInfo*>(currentPeer->data)->FishPosX != 0 && static_cast<PlayerInfo*>(currentPeer->data)->FishPosY != 0) {
				if (rand() % 100 <= 50) {
					static_cast<PlayerInfo*>(currentPeer->data)->TriggerFish = true;
					for (auto currentPeers = server->peers; currentPeers < &server->peers[server->peerCount]; ++currentPeers) {
						if (currentPeers->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(currentPeer, currentPeers))  {
							Player::OnParticleEffect(currentPeers, 36, static_cast<PlayerInfo*>(currentPeer->data)->FishPosX, static_cast<PlayerInfo*>(currentPeer->data)->FishPosY, 0);
							Player::PlayAudio(currentPeers, "audio/splash.wav", 0);
						}
					}
				}
			}
			if (static_cast<PlayerInfo*>(currentPeer->data)->isDuctaped) {
				auto cooldownleft = calcBanDuration(static_cast<PlayerInfo*>(currentPeer->data)->lastMuted);
				if (cooldownleft < 1) {
					Player::OnConsoleMessage(currentPeer, "You've free to talk again! (`$Muted`` mod removed)");
					static_cast<PlayerInfo*>(currentPeer->data)->taped = false;
					static_cast<PlayerInfo*>(currentPeer->data)->isDuctaped = false;
					static_cast<PlayerInfo*>(currentPeer->data)->cantsay = false;
					send_state(currentPeer);
					sendClothes(currentPeer);
					string q = "UPDATE PlayerDatabase SET timemuted = '0' WHERE username = '" + static_cast<PlayerInfo*>(currentPeer->data)->rawName + "' LIMIT 1";
					if (mysql_query(TimerHandler, q.c_str())) {
						cout << mysql_error(TimerHandler) << endl;
						enet_peer_disconnect_later(currentPeer, 0);
						continue;
					}
				}
			}
			if (static_cast<PlayerInfo*>(currentPeer->data)->SurgeryCooldown) {
				auto cooldownleft = calcBanDuration(static_cast<PlayerInfo*>(currentPeer->data)->SurgeryTime);
				if (cooldownleft < 1) {
					Player::OnConsoleMessage(currentPeer, "You've paid your debt to society! (`$Malpractice`` mod removed)");
					sendSound(currentPeer, "audio/dialog_confirm.wav");
					static_cast<PlayerInfo*>(currentPeer->data)->SurgeryCooldown = false;
					static_cast<PlayerInfo*>(currentPeer->data)->SurgeryTime = 0;
				}
			}
			if (static_cast<PlayerInfo*>(currentPeer->data)->GeigerCooldown) {
				auto cooldownleft = calcBanDuration(static_cast<PlayerInfo*>(currentPeer->data)->GeigerTime);
				if (cooldownleft < 1) {
					Player::OnConsoleMessage(currentPeer, "You've no longer radioactive! (`$Irradiated`` mod removed)");
					sendSound(currentPeer, "audio/dialog_confirm.wav");
					if (static_cast<PlayerInfo*>(currentPeer->data)->cloth_necklace != 4656) {
						static_cast<PlayerInfo*>(currentPeer->data)->haveGeigerRadiation = false;
						send_state(currentPeer);
					}
					static_cast<PlayerInfo*>(currentPeer->data)->GeigerCooldown = false;
					static_cast<PlayerInfo*>(currentPeer->data)->GeigerTime = 0;
				}
			}
			if (static_cast<PlayerInfo*>(currentPeer->data)->needsaveinventory) {
				json items, jj;
				auto jjall = json::array();
				for (auto i = 0; i < 200; i++) {
					if (i < static_cast<PlayerInfo*>(currentPeer->data)->inventory.items.size()) {
						jj["aposition"] = i + 1;
						jj["itemid"] = static_cast<PlayerInfo*>(currentPeer->data)->inventory.items.at(i).itemID;
						jj["quantity"] = static_cast<PlayerInfo*>(currentPeer->data)->inventory.items.at(i).itemCount;
						jjall.push_back(jj);
					} else {
						jj["aposition"] = i + 1;
						jj["itemid"] = 0;
						jj["quantity"] = 0;
						jjall.push_back(jj);
					}
				}
				items["items"] = jjall;
				stringstream ss;
				ss << "UPDATE PlayerDatabase SET inventory = '" + JsonToString(items) + "' WHERE username = '" + static_cast<PlayerInfo*>(currentPeer->data)->rawName + "' LIMIT 1";
				auto query = ss.str();
				const auto q = query.c_str();
				if (mysql_query(TimerHandler, q)) {
					cout << mysql_error(TimerHandler) << endl;
					enet_peer_disconnect_later(currentPeer, 0);
					continue;
				}
				static_cast<PlayerInfo*>(currentPeer->data)->needsaveinventory = false;
			}
			string worlds_owned = "";
			for (int i = 0; i < static_cast<PlayerInfo*>(currentPeer->data)->worldsowned.size(); i++) {
				worlds_owned += static_cast<PlayerInfo*>(currentPeer->data)->worldsowned[i] + ",";
			}
			string isGhost = "false";
			if (static_cast<PlayerInfo*>(currentPeer->data)->canWalkInBlocks) isGhost = "true";
			string q = "UPDATE PlayerDatabase SET ClothBack = '" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->cloth_back) + "', ClothHand = '" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->cloth_hand) + "', ClothFace = '" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->cloth_face) + "', ClothShirt = '" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->cloth_shirt) + "', ClothPants = '" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->cloth_pants) + "', ClothNeck = '" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->cloth_necklace) + "', ClothHair = '" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->cloth_hair) + "', ClothFeet = '" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->cloth_feet) + "', ClothMask = '" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->cloth_mask) + "', ClothAnces = '" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->cloth_ances) + "', effect='" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->effect) + "', worldsowned = '" + worlds_owned + "', surgeonlevel = '" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->SurgerySkill) + "', skin = '" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->skinColor) + "', lastworld = '" + static_cast<PlayerInfo*>(currentPeer->data)->currentWorld + "', surgerycooldown = '" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->SurgeryTime) + "', lastnormalworld = '" + static_cast<PlayerInfo*>(currentPeer->data)->lastnormalworld + "', xp = '" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->xp) + "', firefighterlevel='" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->firefighterlevel) + "', firefighterxp='" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->firefighterxp) + "', providerlevel='" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->providerlevel) + "', providerxp='" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->providerxp) + "', level = '" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->level) + "', geigercooldown = '" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->GeigerTime) + "', geigerlevel='" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->geigerlevel) + "', geigerxp='" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->geigerxp) + "', fishermanlevel='" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->fishermanlevel) + "', fishermanxp='" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->fishermanxp) + "', ghost='" + isGhost + "' WHERE username = '" + static_cast<PlayerInfo*>(currentPeer->data)->rawName + "' LIMIT 1";
			if (mysql_query(TimerHandler, q.c_str())) {
				cout << mysql_error(TimerHandler) << endl;				
				enet_peer_disconnect_later(currentPeer, 0);
				continue;
			}
		}
		mysql_close(TimerHandler);
		//mysql_free_result(res); /*free memory upk*/
		saveAllWorlds();
	}
}

inline void TradeMainMenu(ENetPeer* peer)
{
	string user = static_cast<PlayerInfo*>(peer->data)->lastTradeGrowid;
	if (user == "") return;
	bool isonline = false;

	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (static_cast<PlayerInfo*>(currentPeer->data)->rawName == PlayerDB::getProperName(user))
		{
			isonline = true;
			GTDialog tradedialog;
			tradedialog.addLabelWithIcon("`wTrade with `$" + user, 1434, LABEL_SMALL);

			tradedialog.addSpacer(SPACER_SMALL);
			tradedialog.addSmallText("`$Add items that you want to sell.");
			tradedialog.addSmallText("`$(click on the boxes below)");
			tradedialog.addSpacer(SPACER_SMALL);

			if (static_cast<PlayerInfo*>(peer->data)->mySellingItem1 == "3308" || static_cast<PlayerInfo*>(peer->data)->mySellingItem1Count == "0")
			{
				tradedialog.addStaticBlueFrameWithIdCountText("10036", "0", "empty", "putMySellingItem_1", false);
			}
			else
			{
				tradedialog.addStaticBlueFrameWithIdCountText(static_cast<PlayerInfo*>(peer->data)->mySellingItem1, static_cast<PlayerInfo*>(peer->data)->mySellingItem1Count, getItemDef(atoi(static_cast<PlayerInfo*>(peer->data)->mySellingItem1.c_str())).name, "putMySellingItem_1", false);
			}

			if (static_cast<PlayerInfo*>(peer->data)->mySellingItem2 == "3308" || static_cast<PlayerInfo*>(peer->data)->mySellingItem2Count == "0")
			{
				tradedialog.addStaticBlueFrameWithIdCountText("10036", "0", "empty", "putMySellingItem_2", false);
			}
			else
			{
				tradedialog.addStaticBlueFrameWithIdCountText(static_cast<PlayerInfo*>(peer->data)->mySellingItem2, static_cast<PlayerInfo*>(peer->data)->mySellingItem2Count, getItemDef(atoi(static_cast<PlayerInfo*>(peer->data)->mySellingItem2.c_str())).name, "putMySellingItem_2", false);
			}

			if (static_cast<PlayerInfo*>(peer->data)->mySellingItem3 == "3308" || static_cast<PlayerInfo*>(peer->data)->mySellingItem3Count == "0")
			{
				tradedialog.addStaticBlueFrameWithIdCountText("10036", "0", "empty", "putMySellingItem_3", false);
			}
			else
			{
				tradedialog.addStaticBlueFrameWithIdCountText(static_cast<PlayerInfo*>(peer->data)->mySellingItem3, static_cast<PlayerInfo*>(peer->data)->mySellingItem3Count, getItemDef(atoi(static_cast<PlayerInfo*>(peer->data)->mySellingItem3.c_str())).name, "putMySellingItem_3", false);
			}

			if (static_cast<PlayerInfo*>(peer->data)->mySellingItem4 == "3308" || static_cast<PlayerInfo*>(peer->data)->mySellingItem4Count == "0")
			{
				tradedialog.addStaticBlueFrameWithIdCountText("10036", "0", "empty", "putMySellingItem_4", false);
			}
			else
			{
				tradedialog.addStaticBlueFrameWithIdCountText(static_cast<PlayerInfo*>(peer->data)->mySellingItem4, static_cast<PlayerInfo*>(peer->data)->mySellingItem4Count, getItemDef(atoi(static_cast<PlayerInfo*>(peer->data)->mySellingItem4.c_str())).name, "putMySellingItem_4", false);
			}
			tradedialog.addNewLineAfterFrame();

			tradedialog.addSpacer(SPACER_SMALL);
			tradedialog.addSpacer(SPACER_SMALL);
			tradedialog.addSpacer(SPACER_SMALL);
			tradedialog.addSmallText("`$Add items that you want to get.");
			tradedialog.addSmallText("`$(click on the boxes below)");
			tradedialog.addSpacer(SPACER_SMALL);

			if (static_cast<PlayerInfo*>(peer->data)->hisSellingItem1 == "3308" || static_cast<PlayerInfo*>(peer->data)->hisSellingItem1Count == "0")
			{
				tradedialog.addStaticBlueFrameWithIdCountText("10036", "0", "empty", "putHisSellingItem_1", false);
			}
			else
			{
				tradedialog.addStaticBlueFrameWithIdCountText(static_cast<PlayerInfo*>(peer->data)->hisSellingItem1, static_cast<PlayerInfo*>(peer->data)->hisSellingItem1Count, getItemDef(atoi(static_cast<PlayerInfo*>(peer->data)->hisSellingItem1.c_str())).name, "putHisSellingItem_1", false);
			}

			if (static_cast<PlayerInfo*>(peer->data)->hisSellingItem2 == "3308" || static_cast<PlayerInfo*>(peer->data)->hisSellingItem2Count == "0")
			{
				tradedialog.addStaticBlueFrameWithIdCountText("10036", "0", "empty", "putHisSellingItem_2", false);
			}
			else
			{
				tradedialog.addStaticBlueFrameWithIdCountText(static_cast<PlayerInfo*>(peer->data)->hisSellingItem2, static_cast<PlayerInfo*>(peer->data)->hisSellingItem2Count, getItemDef(atoi(static_cast<PlayerInfo*>(peer->data)->hisSellingItem2.c_str())).name, "putHisSellingItem_2", false);
			}

			if (static_cast<PlayerInfo*>(peer->data)->hisSellingItem3 == "3308" || static_cast<PlayerInfo*>(peer->data)->hisSellingItem3Count == "0")
			{
				tradedialog.addStaticBlueFrameWithIdCountText("10036", "0", "empty", "putHisSellingItem_3", false);
			}
			else
			{
				tradedialog.addStaticBlueFrameWithIdCountText(static_cast<PlayerInfo*>(peer->data)->hisSellingItem3, static_cast<PlayerInfo*>(peer->data)->hisSellingItem3Count, getItemDef(atoi(static_cast<PlayerInfo*>(peer->data)->hisSellingItem3.c_str())).name, "putHisSellingItem_3", false);
			}

			if (static_cast<PlayerInfo*>(peer->data)->hisSellingItem4 == "3308" || static_cast<PlayerInfo*>(peer->data)->hisSellingItem4Count == "0")
			{
				tradedialog.addStaticBlueFrameWithIdCountText("10036", "0", "empty", "putHisSellingItem_4", false);
			}
			else
			{
				tradedialog.addStaticBlueFrameWithIdCountText(static_cast<PlayerInfo*>(peer->data)->hisSellingItem4, static_cast<PlayerInfo*>(peer->data)->hisSellingItem4Count, getItemDef(atoi(static_cast<PlayerInfo*>(peer->data)->hisSellingItem4.c_str())).name, "putHisSellingItem_4", false);
			}
			tradedialog.addNewLineAfterFrame();

			tradedialog.addSpacer(SPACER_SMALL);
			tradedialog.addSpacer(SPACER_SMALL);
			tradedialog.addButton("sendtrade", "`2Send Trade Request.");
			tradedialog.addSpacer(SPACER_SMALL);
			tradedialog.addSpacer(SPACER_SMALL);
			tradedialog.addButton("closetrade", "Cancel Trade.");
			tradedialog.addQuickExit();
			tradedialog.endDialog("", "", "");
			Player::OnDialogRequest(peer, tradedialog.finishDialog());
		}
	}
	if (!isonline)
	{
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4This player is not online.", 0, true);
	}
}

vector<itemDataStruct> items;
void serializeItems();

itemDataStruct getItem(int id)
{
	if (itemsDat == nullptr)
	{
		itemDataStruct ret;
		ret.id = -1;
		return ret;
	}
	auto itemsPtr = itemsDat + 60;
	itemsPtr += 4;
	while (true)
	{
		itemsPtr += *reinterpret_cast<uint16_t*>(itemsPtr) + 2;
		if (*reinterpret_cast<uint16_t*>(itemsPtr) == id)
		{
			itemDataStruct item;
			item.id = *reinterpret_cast<uint16_t*>(itemsPtr);
			itemsPtr += 2;
			itemsPtr += 2;
			item.editableType = *static_cast<uint8_t*>(itemsPtr++);
			item.category = *static_cast<uint8_t*>(itemsPtr++);
			item.type = *static_cast<uint8_t*>(itemsPtr++);
			itemsPtr++;
			int nameLen = *reinterpret_cast<uint16_t*>(itemsPtr);
			itemsPtr += 2;
			string name;
			name.resize(nameLen);
			decodeName(reinterpret_cast<char*>(itemsPtr), nameLen, id, &name[0]);
			item.name = name;
			itemsPtr += nameLen;
			int textureLen = *reinterpret_cast<uint16_t*>(itemsPtr);
			itemsPtr += 2;
			string texturefile;
			texturefile.resize(textureLen);
			memcpy(&texturefile[0], itemsPtr, textureLen);
			item.texturefile = texturefile;
			itemsPtr += textureLen;
			item.texturehash = *reinterpret_cast<uint32_t*>(itemsPtr);
			itemsPtr += 4;
			itemsPtr += 5;
			item.textureX = *static_cast<uint8_t*>(itemsPtr++);
			item.textureY = *static_cast<uint8_t*>(itemsPtr++);
			item.textureType = *static_cast<uint8_t*>(itemsPtr);
			itemsPtr += 2;
			item.solid = *static_cast<uint8_t*>(itemsPtr++);
			item.hardness = *static_cast<uint8_t*>(itemsPtr++);
			itemsPtr += 1;
			itemsPtr += 4;
			item.rarity = *reinterpret_cast<uint16_t*>(itemsPtr);
			itemsPtr += 2;
			itemsPtr += 1;
			int audioLen = *reinterpret_cast<uint16_t*>(itemsPtr);
			itemsPtr += 2;
			string audiofile;
			audiofile.resize(audioLen);
			memcpy(&audiofile[0], itemsPtr, audioLen);
			item.audiofile = audiofile;
			itemsPtr += audioLen;
			item.audiohash = *reinterpret_cast<uint32_t*>(itemsPtr);
			itemsPtr += 4;
			item.audioVol = *reinterpret_cast<uint16_t*>(itemsPtr);
			itemsPtr += 2;
			itemsPtr += 16;
			item.seedBase = *static_cast<uint8_t*>(itemsPtr++);
			item.seedOverlay = *static_cast<uint8_t*>(itemsPtr++);
			item.treeBase = *static_cast<uint8_t*>(itemsPtr++);
			item.treeOverlay = *static_cast<uint8_t*>(itemsPtr++);
			item.color1 = *reinterpret_cast<uint32_t*>(itemsPtr);
			itemsPtr += 4;
			item.color2 = *reinterpret_cast<uint32_t*>(itemsPtr);
			itemsPtr += 4;
			return item;
		}
		else
		{
			itemsPtr += 8;
			itemsPtr += *reinterpret_cast<uint16_t*>(itemsPtr) + 2;
			itemsPtr += *reinterpret_cast<uint16_t*>(itemsPtr) + 2;
			itemsPtr += 23;
			itemsPtr += *reinterpret_cast<uint16_t*>(itemsPtr) + 2;
			itemsPtr += 8;
			for (int i = 0; i < 4; i++) itemsPtr += *reinterpret_cast<uint16_t*>(itemsPtr) + 2;
			itemsPtr += 24;
			itemsPtr += *reinterpret_cast<uint16_t*>(itemsPtr) + 2;
			itemsPtr += *reinterpret_cast<uint16_t*>(itemsPtr) + 2;
			itemsPtr += *reinterpret_cast<uint16_t*>(itemsPtr) + 2;
			itemsPtr += *reinterpret_cast<uint16_t*>(itemsPtr) + 2;
			itemsPtr += 78;
		}
		if (itemsPtr - itemsDat >= itemsDatSize)
		{
			itemDataStruct item;
			item.id = -1;
			return item;
		}
	}
}

void serializeItems()
{
	SendConsole("Loading all items...", "INFO");
	auto i = 0;
	while (true)
	{
		auto item = getItem(i++);
		if (item.id == -1) break;
		items.push_back(item);
		coredatasize++;
	}
	SendConsole("Finished loading all items...", "INFO");
}

void ApplyLockPacket(WorldInfo* world, ENetPeer* peer, int x, int y, int id, int lockowner) {
	if (lockowner == -3) {
		lockowner = static_cast<PlayerInfo*>(peer->data)->netID;
	}
	int locksize = 0;
	if (id == 202) locksize = 25;
	PlayerMoving pmov;
	pmov.packetType = 0xf;
	pmov.characterState = 0;
	pmov.x = 0;
	pmov.y = 0;
	pmov.XSpeed = 0;
	pmov.YSpeed = 0;
	pmov.plantingTree = id;
	pmov.punchX = x;
	pmov.punchY = y;
	pmov.netID = lockowner;
	byte* pmovp = packPlayerMoving(&pmov);
	byte* packet = new byte[64 + locksize * 2];
	memset(packet, 0, 64 + locksize * 2);
	packet[0] = 4;
	memcpy(packet + 4, pmovp, 56);
	delete pmovp;
	packet[12] = locksize;
	packet[16] = 8;
	int locksz = locksize * 2;
	memcpy(packet + 56, &locksz, 4);
	bool lock_above = false;
	bool mid_lock = false;
	bool mid_low = false;
	bool mid_lowest = false;
	int vidur_ten = 2;
	int vidur = 2;
	int vidur_cia = 2;
	int lock_above_lock = 2;
	int lock_lowers_lock = 2;
	for (int i = 0; i < locksize; i++) {
		if (!lock_above) {
			int fml = y * world->width - 200 + x - 4 + lock_above_lock;
			memcpy(packet + world->height + i * 2, &fml, 2);
			lock_above_lock++;
			if (lock_above_lock >= 7) lock_above = true;
			continue;
		}
		if (mid_lowest) {
			int fml = y * world->width + 200 + x - 4 + lock_lowers_lock;
			memcpy(packet + world->height + i * 2, &fml, 2);
			lock_lowers_lock++;
		}
		else if (mid_low) {
			int fml = y * world->width + 100 + x - 4 + vidur_cia;
			memcpy(packet + world->height + i * 2, &fml, 2);
			vidur_cia++;
			if (vidur_cia >= 7) mid_lowest = true;
		}
		else if (mid_lock) {
			int fml = y * world->width + x - 4 + vidur;
			memcpy(packet + world->height + i * 2, &fml, 2);
			vidur++;
			if (vidur >= 7) mid_low = true;
		}
		else if (lock_above) {
			int fml = y * world->width - 100 + x - 4 + vidur_ten;
			memcpy(packet + world->height + i * 2, &fml, 2);
			vidur_ten++;
			if (vidur_ten >= 7) mid_lock = true;
		}
	}
	ENetPacket* packetenet = enet_packet_create(packet, 64 + locksize * 2, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packetenet);
	delete packet;
}

inline void SendPunishView(ENetPeer* peer, string PlayerName) {
	if (!isMod(peer)) return;
	static_cast<PlayerInfo*>(peer->data)->lastInfo = PlayerName;
	std::ifstream ifs7("gemdb/" + PlayerName + ".txt");
	std::string contentp((std::istreambuf_iterator<char>(ifs7)), (std::istreambuf_iterator<char>()));
	ifs7.close();
	int warns = 0;
	string email, ipid, Warns, nick, username, playerid, mac, rid, sid, gid, vid, aid, ip, account_notes;
	MYSQL_ROW row;
	string q = "SELECT * FROM PlayerDatabase WHERE username = '" + PlayerName + "' LIMIT 1";
	if (mysql_query(conn, q.c_str())) {
		cout << mysql_error(conn) << endl;
		return;
	}
	res = mysql_store_result(conn);
	while (row = mysql_fetch_row(res)) {
		playerid = row[0];
		username = row[1];
		email = row[3];
		ipid = row[15];
		Warns = row[18];
		mac = row[32];
		rid = row[33];
		sid = row[34];
		gid = row[35];
		vid = row[36];
		aid = row[37];
		ip = row[38];
		nick = row[44];	
		account_notes = row[68];	
	}
	if (username.size() == 0) {
		Player::OnConsoleMessage(peer, PlayerName + " does not exist");
		return;
	}
	if (nick == "") nick = username;
	string accounts;
	if (ipid == "8421376") ipid = "-1";
	string q111 = "SELECT * FROM PlayerDatabase WHERE ip = '" + ip + "' OR email = '" + email + "' OR ipID = '" + ipid + "'";
	if (mysql_query(conn, q111.c_str())) {
		cout << mysql_error(conn) << endl;
		return;
	}
	string test;
	res = mysql_store_result(conn);
	while (row = mysql_fetch_row(res)) {
		if (row[1] == PlayerName) continue;
		test = row[1];
		accounts += test + "|";
	}
	GTDialog allinfo;
	allinfo.addCustom("add_label|mid|`wEditing " + username + " `w(" + nick + "`w) - #" + playerid + "|right\n");
	allinfo.addSpacer(SPACER_SMALL);
	bool HaveOnlineAccounts = false;
	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (static_cast<PlayerInfo*>(currentPeer->data)->rawName == username || static_cast<PlayerInfo*>(currentPeer->data)->charIP == ip || static_cast<PlayerInfo*>(currentPeer->data)->email == email) {
			if (static_cast<PlayerInfo*>(currentPeer->data)->rawName == "") continue;
			allinfo.addLabelWithIconButton("`oON: `5" + static_cast<PlayerInfo*>(currentPeer->data)->rawName + " `w(" + static_cast<PlayerInfo*>(currentPeer->data)->displayName + "`w) #" + to_string(static_cast<PlayerInfo*>(currentPeer->data)->playerid) + " `oHrs: `w" + to_string(rand() % 3000) + " `oIP: `w" + static_cast<PlayerInfo*>(currentPeer->data)->charIP + "", 658, "viewinfo_" + static_cast<PlayerInfo*>(currentPeer->data)->rawName + "");
			allinfo.addButton("warpto_" + static_cast<PlayerInfo*>(currentPeer->data)->currentWorld + "", "`oWarp To User (in `5" + static_cast<PlayerInfo*>(currentPeer->data)->currentWorld + "`o)");
			HaveOnlineAccounts = true;
		}
	}
	if (HaveOnlineAccounts) allinfo.addSpacer(SPACER_SMALL);
	if (account_notes != "") {
		allinfo.addTextBox("`oAccount notes/activity:");
		vector<string> info_dat = explode("|", account_notes);
		for (int i = 0; i < info_dat.size(); i++) {
			if (info_dat[i] == "") continue;
			allinfo.addTextBox(info_dat[i]);
		}
		allinfo.addSpacer(SPACER_SMALL);
	}
	if (account_notes != "" && isDev(peer)) allinfo.addLabelWithIconButton("`o<-- Clear account notes", 32, "clearaccountnotes_" + username + "");
	allinfo.addLabelWithIconButton("`o<-- View inventory", 6128, "showuserinventoryoffline_" + username + "");
	allinfo.addLabelWithIconButton("`o<-- 2 week DGH", 732, "suspend2w");
	allinfo.addLabelWithIconButton("`o<-- 4 week DGH", 732, "suspend4w");
	allinfo.addLabelWithIconButton("`o<-- 8 week DGH", 732, "suspend8w");
	allinfo.addLabelWithIconButton("`o<-- Perma ban DGH", 732, "suspend");
	allinfo.addLabelWithIconButton("`o<-- Perma ban for bad stuff on alt(s)", 732, "suspendalts");
	allinfo.addLabelWithIconButton("`o<-- Perma ban for hacker", 732, "suspend");
	allinfo.addLabelWithIconButton("`o<-- IP ban (online only)", 732, "ipbanwrench");
	allinfo.addSpacer(SPACER_SMALL);
	allinfo.addLabelWithIconButton("`o<-- Fake auto-ban (use for hackers, confuses them, online only)", 546, "fakeautoban");
	allinfo.addSpacer(SPACER_SMALL);
	if (accounts != "") {
		vector<string> info_dat = explode("|", accounts);
		for (int i = 0; i < info_dat.size(); i++) {
			if (info_dat[i] == "") continue;
			string aplayerid, aip, ausername, anickname;
			MYSQL_ROW row;
			string q = "SELECT * FROM PlayerDatabase WHERE username = '" + info_dat[i] + "' LIMIT 1";
			if (mysql_query(conn, q.c_str())) {
				cout << mysql_error(conn) << endl;
				continue;
			}
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res)) {
				aplayerid = row[0];
				ausername = row[1];
				aip = row[38];
				anickname = row[44];	
			}
			if (anickname == "") anickname = info_dat[i];
			allinfo.addLabelWithIconButton("`5" + info_dat[i] + " `w(" + anickname + "`w) #" + aplayerid + " `oHrs: `w" + to_string(rand() % 3000) + " `oIP: `w" + aip + "", 658, "viewinfo_" + info_dat[i] + "");
		}
		allinfo.addSpacer(SPACER_SMALL);
	}
	allinfo.endDialog("Close", "", "Close");
	Player::OnDialogRequest(peer, allinfo.finishDialog());			
}

inline void SendGrowpedia(ENetPeer* peer) {
	string level1 = "", level2 = "", level3 = "", level4 = "", level5 = "", level6 = "", level7 = "", level8 = "", level9 = "", level10 = "", level11 = "", level12 = "", level13 = "", level14 = "", level15 = "", level16 = "", level17 = "", level18 = "", level19 = "", level20 = "";
	if (static_cast<PlayerInfo*>(peer->data)->level >= 1) {
		level1 = "`oUnlocked: 1000 Gems``";
	} else {
		level1 = "`a(Locked) 1000 Gems``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 2) {
		level2 = "`oUnlocked: 75 Chandelier``";
	} else {
		level2 = "`a(Locked) 75 Chandelier``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 3) {
		level3 = "`oUnlocked: Growtoken``";
	} else {
		level3 = "`a(Locked) Growtoken``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 4) {
		level4 = "`oUnlocked: Earth Mastery: 1% chance to break dirt in a single hit``|left|5050|\nadd_label_with_icon|sml|`oUnlocked: Diamond Wings``";
	} else {
		level4 = "`a(Locked) Earth Mastery: 1% chance to break dirt in a single hit``|left|5050|\nadd_label_with_icon|sml|`a(Locked) Diamond Wings``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 5) {
		level5 = "`oUnlocked: 5 Growtokens``";
	} else {
		level5 = "`a(Locked) 5 Growtokens``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 6) {
		level6 = "`oUnlocked: Earth Mastery (level 2) - Chance increase to 2%``";
	} else {
		level6 = "`a(Locked) Earth Mastery (level 2) - Chance increase to 2%``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 7) {
		level7 = "`oUnlocked: Punch Potion``";
	} else {
		level7 = "`a(Locked) Punch Potion``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 8) {
		level8 = "`oUnlocked: Flawless: 1% chance to decrease seed grow time when planting``|left|7186|\nadd_label_with_icon|sml|`oUnlocked: Earth Mastery (level 3) - Chance increase to 3%``";
	} else {
		level8 = "`a(Locked) Flawless: 1% chance to decrease seed grow time when planting``|left|7186|\nadd_label_with_icon|sml|`a(Locked) Earth Mastery (level 3) - Chance increase to 3%``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 9) {
		level9 = "`oUnlocked: 5000 Gems``";
	} else {
		level9 = "`a(Locked) 5000 Gems``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 10) {
		level10 = "`oUnlocked: Harvester: 1% chance to obtain extra block drop when harvesting trees``|left|1966|\nadd_label_with_icon|sml|`oUnlocked: Unique Prize``";
	} else {
		level10 = "`a(Locked) Harvester: 1% chance to obtain extra block drop when harvesting trees``|left|1966|\nadd_label_with_icon|sml|`a(Locked) Unique Prize``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 11) {
		level11 = "`oUnlocked: Flawless (level 2) - Chance increase to 2%``";
	} else {
		level11 = "`a(Locked) Flawless (level 2) - Chance increase to 2%``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 12) {
		level12 = "`oUnlocked: 15000 Gems``";
	} else {
		level12 = "`a(Locked) 15000 Gems``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 13) {
		level13 = "`oUnlocked: Harvester (level 2) - Chance increase to 2%``|left|1966|\nadd_label_with_icon|sml|`oUnlocked: Hands of the Void``";
	} else {
		level13 = "`a(Locked) Harvester (level 2) - Chance increase to 2%``|left|1966|\nadd_label_with_icon|sml|`a(Locked) Hands of the Void``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 14) {
		level14 = "`oUnlocked: 5 Growtokens``";
	} else {
		level14 = "`a(Locked) 5 Growtokens``";
	}
	if (static_cast<PlayerInfo*>(peer->data)->level >= 15) {
		level15 = "`oUnlocked: Ultimate Seediary Ability: Randomize all seed recipes into higher tier``";
	} else {
		level15 = "`a(Locked) Ultimate Seediary Ability: Randomize all seed recipes into higher tier``";
	}
	Player::OnDialogRequest(peer, "add_label_with_icon|big|`wLevel up Rewards``|left|18|\nadd_spacer|small|\nadd_textbox|`9Here are all the Level up rewards that you have earned so far!``|left|\nadd_spacer|small|\nadd_spacer|small|\nadd_smalltext|Level 1 rewards:|left|\nadd_label_with_icon|sml|" + level1 + "|left|112|\nadd_spacer|small|\nadd_smalltext|Level 2 rewards:|left|\nadd_label_with_icon|sml|" + level2 + "|left|340|\nadd_spacer|small|\nadd_smalltext|Level 3 rewards:|left|\nadd_label_with_icon|sml|" + level3 + "|left|1486|\nadd_spacer|small|\nadd_smalltext|Level 4 rewards:|left|\nadd_label_with_icon|sml|" + level4 + "|left|1938|\nadd_spacer|small|\nadd_smalltext|Level 5 rewards:|left|\nadd_label_with_icon|sml|" + level5 + "|left|1486|\nadd_spacer|small|\nadd_smalltext|Level 6 rewards:|left|\nadd_label_with_icon|sml|" + level6 + "|left|5050|\nadd_spacer|small|\nadd_smalltext|Level 7 rewards:|left|\nadd_label_with_icon|sml|" + level7 + "|left|6918|\nadd_spacer|small|\nadd_smalltext|Level 8 rewards:|left|\nadd_label_with_icon|sml|" + level8 + "|left|5050|\nadd_spacer|small|\nadd_smalltext|Level 9 rewards:|left|\nadd_label_with_icon|sml|" + level9 + "|left|112|\nadd_spacer|small|\nadd_smalltext|Level 10 rewards:|left|\nadd_label_with_icon|sml|" + level10 + "|left|2478|\nadd_spacer|small|\nadd_smalltext|Level 11 rewards:|left|\nadd_label_with_icon|sml|" + level11 + "|left|7186|\nadd_spacer|small|\nadd_smalltext|Level 12 rewards:|left|\nadd_label_with_icon|sml|" + level12 + "|left|112|\nadd_smalltext|Level 13 rewards:|left|\nadd_label_with_icon|sml|" + level13 + "|left|8452|\nadd_spacer|small|\nadd_smalltext|Level 14 rewards:|left|\nadd_label_with_icon|sml|" + level14 + "|left|1486|\nadd_spacer|small|\nadd_smalltext|Level 15 rewards:|left|\nadd_label_with_icon|sml|" + level15 + "|left|6128|\nadd_spacer|small|\nadd_button|back|Close|noflags|0|0||\nadd_quick_exit|");
}

inline void SendFishingState(ENetPeer* peer) {
	const auto info = static_cast<PlayerInfo*>(peer->data);
	const auto netID = info->netID;
	const auto state = getState(info);
	for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			PlayerMoving data;
			data.packetType = 0x14;
			data.characterState = static_cast<PlayerInfo*>(peer->data)->characterState;
			data.x = 0;
			data.y = 9999999999;
			data.punchX = 0;
			data.punchY = 0;
			data.XSpeed = 0;
			data.YSpeed = 9999999999;
			data.netID = netID;
			data.plantingTree = state;
			const auto raw = packPlayerMoving(&data);
			auto var = info->effect;
			memcpy(raw + 1, &var, 3);
			SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}

inline void SyncFish(ENetPeer* peer) {
	if (static_cast<PlayerInfo*>(peer->data)->Fishing && static_cast<PlayerInfo*>(peer->data)->TriggerFish) {
		static_cast<PlayerInfo*>(peer->data)->FishPosX = 0;
		static_cast<PlayerInfo*>(peer->data)->FishPosY = 0;
		static_cast<PlayerInfo*>(peer->data)->Fishing = false;
		send_state(peer);
		if (static_cast<PlayerInfo*>(peer->data)->TriggerFish) {
			static_cast<PlayerInfo*>(peer->data)->TriggerFish = false;
			vector<int> FishBase{ 3000, 3024, 3026, 3030, 3032, 3034, 3036, 3038, 3092, 3094, 3096, 3220, 3222, 3224, 3226, 3434, 3436, 3438, 3440, 3450, 3452, 3454, 3456, 3458, 3460, 3544, 3550, 3620, 3746, 3814, 3820, 4958, 5100, 5448, 5450, 5538, 5542, 5548, 5552, 5574, 5580, 7744, 8460 };
			const int Index = rand() % FishBase.size();
			const auto ItemID = FishBase[Index];
			vector<int> GearBase{ 344, 242, 3042, 3016, 10032, 5232, 5604, 5606, 5608, 6902, 6996, 9746 };
			const int GearIndex = rand() % GearBase.size();
			const auto GearID = GearBase[GearIndex];
			vector<int> BlockBase{ 444, 242, 1522, 3016, 3810, 4658, 5530, 5602, 5614, 5624, 6328, 7002, 8964, 8966 };
			const int BlockIndex = rand() % BlockBase.size();
			const auto BlockID = BlockBase[BlockIndex];
			auto count = 1;
			int ChanceOfGear = 0;
			int HowMuchLbs;
			int ChanceOfBlock = 0;
			if (static_cast<PlayerInfo*>(peer->data)->LastBait == "Fishing Fly")
			{
				ChanceOfBlock = (rand() % 400) + 1;
			}
			if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 2912) /*regular*/
			{
				HowMuchLbs = (rand() % 25) + 1;
			}
			else if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3008) /*ezrod*/
			{
				HowMuchLbs = (rand() % 40) + 1;
			}
			else if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3010) /*licorice*/
			{
				HowMuchLbs = (rand() % 60) + 1;
				ChanceOfGear = (rand() % 450) + 1;
			}
			else if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3100) /*cursed*/
			{
				HowMuchLbs = (rand() % 150) + 1;
				ChanceOfGear = (rand() % 250) + 1;
			}
			else if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3040) /*golden*/
			{
				HowMuchLbs = (rand() % 200) + 1;
				ChanceOfGear = (rand() % 200) + 1;
			}
			else if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 5740) /*magical*/
			{
				HowMuchLbs = (rand() % 90) + 1;
				ChanceOfGear = (rand() % 350) + 1;
			} else {
				return;
			}

			int chanceofbonus = 1;
			if (static_cast<PlayerInfo*>(peer->data)->fishermanlevel >= 4) chanceofbonus = 2;
			if (static_cast<PlayerInfo*>(peer->data)->fishermanlevel >= 6) chanceofbonus = 3;
			if (static_cast<PlayerInfo*>(peer->data)->fishermanlevel >= 8) chanceofbonus = 4;
			if (static_cast<PlayerInfo*>(peer->data)->fishermanlevel >= 10) chanceofbonus = 5;
			if (static_cast<PlayerInfo*>(peer->data)->fishermanlevel >= 2 && rand() % 100 <= chanceofbonus) {
				vector<int> newGearBase{ 344, 242, 3042, 3016, 10032, 5232, 5604, 5606, 5608, 6902, 6996, 9746 };
				const int newGearIndex = rand() % newGearBase.size();
				const auto newGearID = newGearBase[newGearIndex];
				Player::OnConsoleMessage(peer, "Quantum bonus obtained " + getItemDef(newGearID).name + "");
				auto success = true;
				SaveItemMoreTimes(newGearID, 1, peer, success);
				auto Gems = (rand() % 600) + 1;
				if (static_cast<PlayerInfo*>(peer->data)->fishermanlevel == 10 && rand() % 100 <= 1) {
					Gems *= 2;
					Player::OnConsoleMessage(peer, "Obtained double gems");
				}
				auto currentGems = 0;
				ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
				ifs >> currentGems;
				ifs.close();
				currentGems += Gems;
				ofstream ofs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
				ofs << currentGems;
				ofs.close();
				SendXP(peer, 5);
				Player::OnSetBux(peer, currentGems, 0);
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, currentPeer)) {
						Player::OnConsoleMessage(currentPeer, "`$" + static_cast<PlayerInfo*>(peer->data)->displayName + " `oCaught `$" + getItemDef(newGearID).name + " `oand got `$" + to_string(Gems) + " `ogems");
						Player::PlayAudio(currentPeer, "audio/getpoint.wav", 0);
						SendTradeEffect(peer, BlockID, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
					}
				}
			} 
			else if (static_cast<PlayerInfo*>(peer->data)->fishermanlevel >= 3 && rand() % 100 <= 1) {
				bool success = true;
				SaveItemMoreTimes(260, 1, peer, success, "");
				Player::OnConsoleMessage(peer, "Obtained Golden Block");
			}

			count = HowMuchLbs;
			if (ChanceOfBlock <= 30 && ChanceOfBlock != 0) {
				auto success = true;
				SaveItemMoreTimes(BlockID, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from fishing");
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou caught a `2" + getItemDef(BlockID).name + "`2!", 0, false);
				auto Gems = (rand() % 500) + 1;
				if (static_cast<PlayerInfo*>(peer->data)->fishermanlevel == 10 && rand() % 100 <= 1) {
					Gems *= 2;
					Player::OnConsoleMessage(peer, "Obtained double gems");
				}
				auto currentGems = 0;
				ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
				ifs >> currentGems;
				ifs.close();
				currentGems += Gems;
				ofstream ofs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
				ofs << currentGems;
				ofs.close();
				SendXP(peer, 3);
				Player::OnSetBux(peer, currentGems, 0);
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, currentPeer)) {
						Player::OnConsoleMessage(currentPeer, "`$" + static_cast<PlayerInfo*>(peer->data)->displayName + " `oCaught `$" + getItemDef(BlockID).name + " `oand got `$" + to_string(Gems) + " `ogems");
						Player::PlayAudio(currentPeer, "audio/getpoint.wav", 0);
						SendTradeEffect(peer, BlockID, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
					}
				}
				Player::OnSetPos(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y);
				int targetfishlevel = 1600;
				if (static_cast<PlayerInfo*>(peer->data)->fishermanlevel > 0) targetfishlevel = targetfishlevel * static_cast<PlayerInfo*>(peer->data)->fishermanlevel;
				if (static_cast<PlayerInfo*>(peer->data)->fishermanlevel == 0) targetfishlevel = 900;
				if (static_cast<PlayerInfo*>(peer->data)->fishermanxp >= targetfishlevel && static_cast<PlayerInfo*>(peer->data)->fishermanlevel < 10) {
					static_cast<PlayerInfo*>(peer->data)->fishermanlevel++;
					static_cast<PlayerInfo*>(peer->data)->fishermanxp = 0;
					SyncPlayerRoles(peer, static_cast<PlayerInfo*>(peer->data)->fishermanlevel, "fisherman");
				} else {
					static_cast<PlayerInfo*>(peer->data)->fishermanxp += 3;
				}
				return;
			}
			if (ChanceOfGear <= 10 && ChanceOfGear != 0)
			{
				auto success = true;
				SaveItemMoreTimes(GearID, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from fishing");
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou caught a `2" + getItemDef(GearID).name + "`2!", 0, false);
				auto Gems = (rand() % 600) + 1;
				if (static_cast<PlayerInfo*>(peer->data)->fishermanlevel == 10 && rand() % 100 <= 1) {
					Gems *= 2;
					Player::OnConsoleMessage(peer, "Obtained double gems");
				}
				auto currentGems = 0;
				ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
				ifs >> currentGems;
				ifs.close();
				currentGems += Gems;
				ofstream ofs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
				ofs << currentGems;
				ofs.close();
				SendXP(peer, 5);
				Player::OnSetBux(peer, currentGems, 0);
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, currentPeer)) {
						Player::OnConsoleMessage(currentPeer, "`$" + static_cast<PlayerInfo*>(peer->data)->displayName + " `oCaught `$" + getItemDef(GearID).name + " `oand got `$" + to_string(Gems) + " `ogems");
						Player::PlayAudio(currentPeer, "audio/getpoint.wav", 0);
						SendTradeEffect(currentPeer, GearID, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
					}	
				}
				Player::OnSetPos(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y);
				int targetfishlevel = 1600;
				if (static_cast<PlayerInfo*>(peer->data)->fishermanlevel > 0) targetfishlevel = targetfishlevel * static_cast<PlayerInfo*>(peer->data)->fishermanlevel;
				if (static_cast<PlayerInfo*>(peer->data)->fishermanlevel == 0) targetfishlevel = 900;
				if (static_cast<PlayerInfo*>(peer->data)->fishermanxp >= targetfishlevel && static_cast<PlayerInfo*>(peer->data)->fishermanlevel < 10) {
					static_cast<PlayerInfo*>(peer->data)->fishermanlevel++;
					static_cast<PlayerInfo*>(peer->data)->fishermanxp = 0;
					SyncPlayerRoles(peer, static_cast<PlayerInfo*>(peer->data)->fishermanlevel, "fisherman");
				} else {
					static_cast<PlayerInfo*>(peer->data)->fishermanxp += 5;
				}
				return;
			}
			auto iscontains = false;
			SearchInventoryItem(peer, ItemID, 1, iscontains);
			if (!iscontains) {
				auto success = true;
				SaveItemMoreTimes(ItemID, count, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from fishing");
			} else {
				DropItem(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, ItemID, count, 0);
			}
			if (getItemDef(ItemID).blockType == BlockTypes::FISH) {
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou caught a `2" + to_string(count) + " lb. " + getItemDef(ItemID).name + "`2!", 0, false);
			} else {
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou caught a `2" + getItemDef(ItemID).name + "`2!", 0, false);
			}
			auto Gems = 0;
			if (count >= 1 && count < 30)
			{
				Gems = (rand() % 150) + 1;
			}
			else if (count >= 30 && count < 60)
			{
				Gems = (rand() % 250) + 1;
			}
			else if (count >= 60 && count < 90)
			{
				Gems = (rand() % 400) + 1;
			}
			else if (count >= 90 && count < 120)
			{
				Gems = (rand() % 450) + 1;
			}
			else if (count >= 120 && count < 150)
			{
				Gems = (rand() % 500) + 1;
			}
			else if (count >= 150 && count < 199)
			{
				Gems = (rand() % 550) + 1;
			}
			else if (count >= 200)
			{
				Gems = (rand() % 900) + 1;
			}
			if (static_cast<PlayerInfo*>(peer->data)->fishermanlevel == 10 && rand() % 100 <= 1) {
				Gems *= 2;
				Player::OnConsoleMessage(peer, "Obtained double gems");
			}
			auto currentGems = 0;
			ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
			ifs >> currentGems;
			ifs.close();
			currentGems += Gems;
			ofstream ofs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
			ofs << currentGems;
			ofs.close();
			SendXP(peer, 2);
			Player::OnSetBux(peer, currentGems, 0);
			for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
				if (isHere(peer, currentPeer)) {
					Player::OnConsoleMessage(currentPeer, "`$" + static_cast<PlayerInfo*>(peer->data)->displayName + " `oCaught `$" + to_string(count) + " lb. " + getItemDef(ItemID).name + " `oand got `$" + to_string(Gems) + " `ogems");
					Player::PlayAudio(currentPeer, "audio/getpoint.wav", 0);
					SendTradeEffect(currentPeer, ItemID, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
				}
			}
			int targetfishlevel = 1600;
			if (static_cast<PlayerInfo*>(peer->data)->fishermanlevel > 0) targetfishlevel = targetfishlevel * static_cast<PlayerInfo*>(peer->data)->fishermanlevel;
			if (static_cast<PlayerInfo*>(peer->data)->fishermanlevel == 0) targetfishlevel = 900;
			if (static_cast<PlayerInfo*>(peer->data)->fishermanxp >= targetfishlevel && static_cast<PlayerInfo*>(peer->data)->fishermanlevel < 10) {
				static_cast<PlayerInfo*>(peer->data)->fishermanlevel++;
				static_cast<PlayerInfo*>(peer->data)->fishermanxp = 0;
				SyncPlayerRoles(peer, static_cast<PlayerInfo*>(peer->data)->fishermanlevel, "fisherman");
			} else {
				static_cast<PlayerInfo*>(peer->data)->fishermanxp += 2;
			}
		} 
		Player::OnSetPos(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y);
		return;
	} else if (static_cast<PlayerInfo*>(peer->data)->Fishing && !static_cast<PlayerInfo*>(peer->data)->TriggerFish) {
		static_cast<PlayerInfo*>(peer->data)->FishPosX = 0;
		static_cast<PlayerInfo*>(peer->data)->FishPosY = 0;
		static_cast<PlayerInfo*>(peer->data)->Fishing = false;
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wSit perfectly while fishing`w!", 0, true);
	}
}

inline void SendGScan(ENetPeer* peer, WorldInfo* world, int x, int y) {
	string EditableDialog = "";
	string ButtonDialog = "";
	string allowFloat = "0";
	string allowDrop = "0";
	string endDialog = "";
	if (world->items[x + (y * world->width)].rm) allowFloat = "1";
	if (world->items[x + (y * world->width)].opened) allowDrop = "1";
	if (isWorldOwner(peer, world) || isMod(peer)) {
		endDialog = "\nend_dialog|statsblock|Cancel|Apply|";
		ButtonDialog = "\nadd_textbox|`wWhich stats would you like to view?|left\nadd_button|worldBlocks|World Blocks|noflags|0|0|\nadd_button|floatingItems|Floating Items|noflags|0|0|";
		EditableDialog = "\nadd_textbox|`wYou can set the stats to be usable by the public.|left\nadd_checkbox|isStatsWorldBlockUsableByPublic|World blocks is usable by public|" + allowDrop + "\nadd_checkbox|isStatsFloatingItemsUsableByPublic|Floating items is usable by public|" + allowFloat + "\nadd_spacer|small|";
	} else if (world->items[x + (y * world->width)].rm && world->items[x + (y * world->width)].opened) {
		endDialog = "\nend_dialog|statsblock|Cancel||";
		ButtonDialog = "\nadd_textbox|`wWhich stats would you like to view?|left\nadd_button|worldBlocks|World Blocks|noflags|0|0|\nadd_button|floatingItems|Floating Items|noflags|0|0|";
	} else if (world->items[x + (y * world->width)].rm) {
		endDialog = "\nend_dialog|statsblock|Cancel||";
		ButtonDialog = "\nadd_textbox|`wWhich stats would you like to view?|left\nadd_button|floatingItems|Floating Items|noflags|0|0|";
	} else if (world->items[x + (y * world->width)].opened) {
		endDialog = "\nend_dialog|statsblock|Cancel||";
		ButtonDialog = "\nadd_textbox|`wWhich stats would you like to view?|left\nadd_button|worldBlocks|World Blocks|noflags|0|0|";
	} else {
		endDialog = "\nend_dialog|statsblock|Cancel||";
		ButtonDialog = "\nadd_textbox|`wThis growscan options are set to private!|left";
	}
	Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wWorld Stats``|left|6016|\nadd_spacer|small|\nadd_textbox|`wThis amazing block can show the stats for the whole world!|left\nadd_spacer|small|" + ButtonDialog + "\nadd_spacer|small|" + EditableDialog + "" + endDialog + "");
}

inline void LogAccountActivity(ENetPeer* peer, string log) {
	MYSQL_ROW row;
	string qss = "SELECT * FROM PlayerDatabase WHERE username = '" + static_cast<PlayerInfo*>(peer->data)->rawName + "' LIMIT 1";
	string account_history;
	mysql_query(conn, qss.c_str());
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
	account_history += "" + to_string(Month) + "/" + to_string(Day) + "/" + to_string(Year) + " " + to_string(Hour) + ":" + to_string(Min) + ":" + to_string(Sec) + ": " + static_cast<PlayerInfo*>(peer->data)->rawName + " - >> " + log + "|";
	string stringsa = "UPDATE PlayerDatabase SET accountnotes = '" + account_history + "' WHERE username = '" + static_cast<PlayerInfo*>(peer->data)->rawName + "' LIMIT 1";
	mysql_query(conn, stringsa.c_str());
}

bool RestrictedArea_check(WorldInfo* world, const int x, const int y) {
	bool scan_area = false;
	int where_lock_x = -1;
	int where_lock_y = -1;
	bool is_public = false;
	bool can_interact = false;
	for (int i = 0; i < world->width * world->height; i++) {
		if (world->items[i].foreground == 202 || world->items[i].foreground == 204 || world->items[i].foreground == 206 || world->items[i].foreground == 4994) {
			where_lock_x = i % world->width;
			where_lock_y = i / world->width;
			scan_area = true;
			if (x == where_lock_x + 1 && where_lock_y == y) can_interact = true;
			if (x == where_lock_x + 2 && where_lock_y == y) can_interact = true;
			if (x == where_lock_x - 1 && where_lock_y == y) can_interact = true;
			if (x == where_lock_x - 2 && where_lock_y == y) can_interact = true;
			if (y == where_lock_y + 1 && where_lock_x == x) can_interact = true;
			if (y == where_lock_y + 2 && where_lock_x == x) can_interact = true;
			if (y == where_lock_y - 1 && where_lock_x == x) can_interact = true;
			if (y == where_lock_y - 2 && where_lock_x == x) can_interact = true;
			if (x == where_lock_x + 1 && where_lock_y + 1 == y) can_interact = true;
			if (x == where_lock_x + 2 && where_lock_y + 2 == y) can_interact = true;
			if (x == where_lock_x - 1 && where_lock_y - 1 == y) can_interact = true;
			if (x == where_lock_x - 2 && where_lock_y - 2 == y) can_interact = true;
			if (y == where_lock_y + 1 && where_lock_x + 1 == x) can_interact = true;
			if (y == where_lock_y + 2 && where_lock_x + 2 == x) can_interact = true;
			if (y == where_lock_y - 1 && where_lock_x - 1 == x) can_interact = true;
			if (y == where_lock_y - 2 && where_lock_x - 2 == x) can_interact = true;
			if (x == where_lock_x + 1 && where_lock_y - 1 == y) can_interact = true;
			if (x == where_lock_x + 2 && where_lock_y - 2 == y) can_interact = true;
			if (x == where_lock_x - 1 && where_lock_y + 1 == y) can_interact = true;
			if (x == where_lock_x - 2 && where_lock_y + 2 == y) can_interact = true;
			if (y == where_lock_y + 1 && where_lock_x - 1 == x) can_interact = true;
			if (y == where_lock_y + 2 && where_lock_x - 2 == x) can_interact = true;
			if (y == where_lock_y - 1 && where_lock_x + 1 == x) can_interact = true;
			if (y == where_lock_y - 2 && where_lock_x + 2 == x) can_interact = true;
			if (x == where_lock_x + 2 && where_lock_y + 1 == y) can_interact = true;
			if (x == where_lock_x - 2 && where_lock_y - 1 == y) can_interact = true;
			if (x == where_lock_x + 1 && where_lock_y + 2 == y) can_interact = true;
			if (x == where_lock_x - 1 && where_lock_y - 2 == y) can_interact = true;
			if (x == where_lock_x - 1 && where_lock_y + 2 == y) can_interact = true;
			if (x == where_lock_x + 1 && where_lock_y - 2 == y) can_interact = true;
			if (x == where_lock_x + 2 && where_lock_y - 1 == y) can_interact = true;
			if (x == where_lock_x + 2 && where_lock_y + 1 == y) can_interact = true;
			if (x == where_lock_x - 2 && where_lock_y + 1 == y) can_interact = true;
		}
	}
	if (!scan_area) return true;
	if (!can_interact) return true;
	return false;
}

bool RestrictedArea(ENetPeer* peer, WorldInfo* world, const int x, const int y) {
	bool scan_area = false;
	int where_lock_x = 0;
	int where_lock_y = 0;
	bool is_public = false;
	bool can_interact = false;
	bool bound_area = false;
	for (int i = 0; i < world->width * world->height; i++) {
		if (world->items[i].foreground == 202 || world->items[i].foreground == 204 || world->items[i].foreground == 206 || world->items[i].foreground == 4994) {
			scan_area = true;
			if (world->items[i].opened || world->items[i].monitorname == static_cast<PlayerInfo*>(peer->data)->rawName) {
				where_lock_x = i % world->width;
				where_lock_y = i / world->width;
				if (x == where_lock_x + 1 && where_lock_y == y) can_interact = true;
				if (x == where_lock_x + 2 && where_lock_y == y) can_interact = true;
				if (x == where_lock_x - 1 && where_lock_y == y) can_interact = true;
				if (x == where_lock_x - 2 && where_lock_y == y) can_interact = true;
				if (y == where_lock_y + 1 && where_lock_x == x) can_interact = true;
				if (y == where_lock_y + 2 && where_lock_x == x) can_interact = true;
				if (y == where_lock_y - 1 && where_lock_x == x) can_interact = true;
				if (y == where_lock_y - 2 && where_lock_x == x) can_interact = true;
				if (x == where_lock_x + 1 && where_lock_y + 1 == y) can_interact = true;
				if (x == where_lock_x + 2 && where_lock_y + 2 == y) can_interact = true;
				if (x == where_lock_x - 1 && where_lock_y - 1 == y) can_interact = true;
				if (x == where_lock_x - 2 && where_lock_y - 2 == y) can_interact = true;
				if (y == where_lock_y + 1 && where_lock_x + 1 == x) can_interact = true;
				if (y == where_lock_y + 2 && where_lock_x + 2 == x) can_interact = true;
				if (y == where_lock_y - 1 && where_lock_x - 1 == x) can_interact = true;
				if (y == where_lock_y - 2 && where_lock_x - 2 == x) can_interact = true;
				if (x == where_lock_x + 1 && where_lock_y - 1 == y) can_interact = true;
				if (x == where_lock_x + 2 && where_lock_y - 2 == y) can_interact = true;
				if (x == where_lock_x - 1 && where_lock_y + 1 == y) can_interact = true;
				if (x == where_lock_x - 2 && where_lock_y + 2 == y) can_interact = true;
				if (y == where_lock_y + 1 && where_lock_x - 1 == x) can_interact = true;
				if (y == where_lock_y + 2 && where_lock_x - 2 == x) can_interact = true;
				if (y == where_lock_y - 1 && where_lock_x + 1 == x) can_interact = true;
				if (y == where_lock_y - 2 && where_lock_x + 2 == x) can_interact = true;
				if (x == where_lock_x + 2 && where_lock_y + 1 == y) can_interact = true;
				if (x == where_lock_x - 2 && where_lock_y - 1 == y) can_interact = true;
				if (x == where_lock_x + 1 && where_lock_y + 2 == y) can_interact = true;
				if (x == where_lock_x - 1 && where_lock_y - 2 == y) can_interact = true;
				if (x == where_lock_x - 1 && where_lock_y + 2 == y) can_interact = true;
				if (x == where_lock_x + 1 && where_lock_y - 2 == y) can_interact = true;
				if (x == where_lock_x + 2 && where_lock_y - 1 == y) can_interact = true;
				if (x == where_lock_x + 2 && where_lock_y + 1 == y) can_interact = true;
				if (x == where_lock_x - 2 && where_lock_y + 1 == y) can_interact = true;
			} else if (world->owner == "") {
				where_lock_x = i % world->width;
				where_lock_y = i / world->width;
				if (x == where_lock_x + 1 && where_lock_y == y) bound_area = true;
				if (x == where_lock_x + 2 && where_lock_y == y) bound_area = true;
				if (x == where_lock_x - 1 && where_lock_y == y) bound_area = true;
				if (x == where_lock_x - 2 && where_lock_y == y) bound_area = true;
				if (y == where_lock_y + 1 && where_lock_x == x) bound_area = true;
				if (y == where_lock_y + 2 && where_lock_x == x) bound_area = true;
				if (y == where_lock_y - 1 && where_lock_x == x) bound_area = true;
				if (y == where_lock_y - 2 && where_lock_x == x) bound_area = true;
				if (x == where_lock_x + 1 && where_lock_y + 1 == y) bound_area = true;
				if (x == where_lock_x + 2 && where_lock_y + 2 == y) bound_area = true;
				if (x == where_lock_x - 1 && where_lock_y - 1 == y) bound_area = true;
				if (x == where_lock_x - 2 && where_lock_y - 2 == y) bound_area = true;
				if (y == where_lock_y + 1 && where_lock_x + 1 == x) bound_area = true;
				if (y == where_lock_y + 2 && where_lock_x + 2 == x) bound_area = true;
				if (y == where_lock_y - 1 && where_lock_x - 1 == x) bound_area = true;
				if (y == where_lock_y - 2 && where_lock_x - 2 == x) bound_area = true;
				if (x == where_lock_x + 1 && where_lock_y - 1 == y) bound_area = true;
				if (x == where_lock_x + 2 && where_lock_y - 2 == y) bound_area = true;
				if (x == where_lock_x - 1 && where_lock_y + 1 == y) bound_area = true;
				if (x == where_lock_x - 2 && where_lock_y + 2 == y) bound_area = true;
				if (y == where_lock_y + 1 && where_lock_x - 1 == x) bound_area = true;
				if (y == where_lock_y + 2 && where_lock_x - 2 == x) bound_area = true;
				if (y == where_lock_y - 1 && where_lock_x + 1 == x) bound_area = true;
				if (y == where_lock_y - 2 && where_lock_x + 2 == x) bound_area = true;
				if (x == where_lock_x + 2 && where_lock_y + 1 == y) bound_area = true;
				if (x == where_lock_x - 2 && where_lock_y - 1 == y) bound_area = true;
				if (x == where_lock_x + 1 && where_lock_y + 2 == y) bound_area = true;
				if (x == where_lock_x - 1 && where_lock_y - 2 == y) bound_area = true;
				if (x == where_lock_x - 1 && where_lock_y + 2 == y) bound_area = true;
				if (x == where_lock_x + 1 && where_lock_y - 2 == y) bound_area = true;
				if (x == where_lock_x + 2 && where_lock_y - 1 == y) bound_area = true;
				if (x == where_lock_x + 2 && where_lock_y + 1 == y) bound_area = true;
				if (x == where_lock_x - 2 && where_lock_y + 1 == y) bound_area = true;
			}
		}
	}
	if (!can_interact && world->owner == "" && !bound_area || isWorldOwner(peer, world)) return false;
	else if (!scan_area) return true;
	else if (!can_interact) return true;
	else if (can_interact) return false;
}

void SendRainbowShitData(ENetPeer* peer, short fg, short bg, int x, int y, bool rainbow, int netid) {
	byte* ExtendedData = new byte[26];
	int state = 0x0010000;
	int extendedLen = 26;
	PlayerMoving pmov;
	pmov.packetType = 0x5;
	pmov.characterState = 0x8;
	pmov.punchX = x;
	pmov.punchY = y;
	int NetID = netid;
	byte* raw = new byte[56 + 26];
	memcpy(raw, packPlayerMoving(&pmov), 56);
	memcpy(raw + 52, &extendedLen, 4);
	memcpy(ExtendedData, &fg, 2);
	memcpy(ExtendedData + 2, &bg, 2);
	memcpy(ExtendedData + 4, &state, 4);
	ExtendedData[8] = 0x3;
	int flags = 0;
	if (rainbow) {
		flags = 128;
	} else {
		flags = 0;
	}
	ExtendedData[9] = flags; 
	memcpy(ExtendedData + 10, &NetID, 4);
	ExtendedData[15] = 0;
	ExtendedData[16] = 0;
	ExtendedData[17] = 0;
	ExtendedData[18] = 0;
	ExtendedData[19] = 1;
	ExtendedData[20] = 0;
	ExtendedData[21] = 0;
	ExtendedData[22] = 0;
	ExtendedData[23] = 0;
	ExtendedData[24] = 0;
	ExtendedData[25] = 0;
	ExtendedData[26] = 0;
	memcpy(raw + 56, ExtendedData, extendedLen);
	SendPacketRaw3(4, raw, 56 + 26, 0, peer, ENET_PACKET_FLAG_RELIABLE);
	delete[] ExtendedData; 

}

void sendNPC(ENetPeer* peer, float fromX, float fromY, float toX, float toY, float speed, uint8_t npc_id, uint8_t npc_type, uint8_t command) {
	PlayerMoving pmov;
	memset(&pmov, 0, sizeof(PlayerMoving));
	*(uint32_t*)(&pmov) = 34 | (npc_type << 8) | (npc_id << 16) | (command << 24);
	*(float*)(&pmov + 40) = speed; 
	pmov.x = fromX;
	pmov.y = fromY;
	pmov.XSpeed = toX;
	pmov.YSpeed = toY;
	uint8_t* pmovpacked = packPlayerMoving(&pmov);
	uint8_t* packet = new uint8_t[4 + 56];
	memset(packet, 0, 4 + 56);
	packet[0] = 4;
	memcpy(packet + 4, pmovpacked, sizeof(PlayerMoving));
	ENetPacket* epacket = enet_packet_create(packet, 4 + 56, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, epacket);
	delete pmovpacked;
	delete packet;
}

void sendDice(ENetPeer* peer, int number, int x, int y) {
	PlayerMoving data;
	BYTE* raw = packPlayerMoving(&data);
	memcpy(raw + 1, &number, 3);
	data.netID = ((PlayerInfo*)(peer->data))->netID;
	data.packetType = 0x8;
	data.plantingTree = 0;
	data.netID = -1;
	data.x = x;
	data.y = y;
	data.punchX = x;
	data.punchY = y;
	SendPacketRaw(4, raw, 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
}
