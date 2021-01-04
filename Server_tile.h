// ReSharper disable All
#pragma once
#include "stdafx.h"
#include <fstream>
// ReSharper disable once CppUnusedIncludeDirective
#include <iostream>
#include "Server_player.h"
#include "Server_world.h"
// ReSharper disable once CppUnusedIncludeDirective
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <locale>
#include <regex>
#include <string>
#include <thread>
#include <vector>
#include <experimental/filesystem>
#include "json.hpp"
// ReSharper disable once CppUnusedIncludeDirective
#include "Player_mods.h"
#ifdef _WIN32
#include <windows.h>
typedef __int8 __int8_t;
typedef __int16 __int16_t;
#elif __APPLE__ || __linux__
typedef unsigned int DWORD;
#endif
typedef unsigned char BYTE;

inline void sendTileUpdate(int x, int y, int tile, int causedBy, ENetPeer* peer, WorldInfo* world) {
	Player::Ping(peer); 
	if (tile > itemDefs.size()) return;
	if (static_cast<PlayerInfo*>(peer->data)->isIn == false) return;
	if (static_cast<PlayerInfo*>(peer->data)->currentWorld == "EXIT") return;
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) return;
	auto dicenr = 0;
	PlayerMoving data;        
 	data.packetType = 0x3;
	data.characterState = 0x0;
	data.x = x;
	data.y = y;
	data.punchX = x;
	data.punchY = y;
	data.XSpeed = 0;
	data.YSpeed = 0;
	data.netID = causedBy;
	data.plantingTree = tile;
	auto isTree = false;
	auto isLock = false;
	auto isSmallLock = false;
	auto isHeartMonitor = false;
	bool isMannequin = false;
	auto isScience = false;
	auto isMagplant = false;
	auto isgateway = false;
	auto squaresign = x + (y * world->width);
	auto iscontains = false;
	auto VendUpdate = false;
	bool isDoor = false;
	if (world == nullptr) return;
	if (x < 0 || y < 0 || x > world->width - 1 || y > world->height - 1 || tile > itemDefs.size()) return;
	if (world->name == "HELL" && static_cast<PlayerInfo*>(peer->data)->isCursed) return;
	if (!isDev(peer)) {
		auto contains = false;
		SearchInventoryItem(peer, tile, 1, contains);
		if (!contains) return;
	}
	if (getItemDef(tile).blockType == BlockTypes::SEED && !world->items[x + (y * world->width)].fire) {
		if (world->items[x + (y * world->width)].foreground != 0) {
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SEED) {
				if (world->isPublic || isWorldAdmin(peer, world) || static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || world->owner == "" || isMod(peer) || !RestrictedArea(peer, world, x, y)) {
					if (calcBanDuration(world->items[x + (y * world->width)].growtime) == 0) {
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "This tree is already too big to splice another seed with.", 0, true);
						return;
					}
					if (getItemDef(world->items[x + (y * world->width)].foreground).name == getItemDef(tile).name || getItemDef(world->items[x + (y * world->width)].foreground).rarity == 999 || getItemDef(tile).rarity == 999) {
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Hmm, it looks like `w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`` and `w" + getItemDef(tile).name + "`` can't be spliced.", 0, true);
						return;
					}
					auto iscontains = false;
					SearchInventoryItem(peer, tile, 1, iscontains);
					if (!iscontains) return;
					if (!world->items[x + (y * world->width)].spliced) {
						auto targetvalue = getItemDef(world->items[x + (y * world->width)].foreground).rarity + getItemDef(tile).rarity;
						if (static_cast<PlayerInfo*>(peer->data)->level >= 15) targetvalue += 1;
						for (auto i = 0; i < 10016; i++) {
							if (getItemDef(i).rarity == targetvalue) {
								world->items[x + (y * world->width)].spliced = true;
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`` and `w" + getItemDef(tile).name + "`` have been spliced to make a `$" + getItemDef(i + 1).name + "``!", 0, true);
								Player::PlayAudio(peer, "audio/success.wav", 0);
								world->items[x + (y * world->width)].foreground = i + 1;
								int growTimeSeed = getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity;
								growTimeSeed += 30 * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity;
								if (world->items[x + (y * world->width)].foreground - 1 == 954) growTimeSeed = 1800;
								if (world->items[x + (y * world->width)].foreground - 1 == 340) growTimeSeed = 3600;
								if (world->items[x + (y * world->width)].foreground - 1 == 5666) growTimeSeed = 2700;
								if (world->items[x + (y * world->width)].foreground - 1 == 4584) growTimeSeed = 2400;
								if (world->items[x + (y * world->width)].foreground - 1 == 4762) growTimeSeed = 14544;
								if (world->items[x + (y * world->width)].foreground - 1 == 7382) growTimeSeed = 22544;
								if (world->items[x + (y * world->width)].foreground - 1 == 9460) growTimeSeed = 29544;
								if (world->items[x + (y * world->width)].foreground - 1 == 9468) growTimeSeed = 36544;
								if (world->items[x + (y * world->width)].foreground - 1 == 10024) growTimeSeed = 56544;
								if (world->items[x + (y * world->width)].foreground - 1 == 10028) growTimeSeed = 86400;
								world->items[x + (y * world->width)].growtime = (GetCurrentTimeInternalSeconds() + growTimeSeed);
								if (getItemDef(world->items[x + (y * world->width)].foreground).rarity == 999) {
									world->items[x + (y * world->width)].fruitcount = (rand() % 1) + 1;
								} else {
									world->items[x + (y * world->width)].fruitcount = (rand() % 3) + 1;
								}
								if (getItemDef(world->items[x + (y * world->width)].foreground - 1).blockType == BlockTypes::CLOTHING) world->items[x + (y * world->width)].fruitcount = 1;
								UpdateTreeVisuals(peer, world->items[x + (y * world->width)].foreground, x, y, world->items[x + (y * world->width)].background, world->items[x + (y * world->width)].fruitcount, 0, true, 0);
								RemoveInventoryItem(tile, 1, peer, true);
								break;
							} else if (i >= 10015) {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Hmm, it looks like `w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`` and `w" + getItemDef(tile).name + "`` can't be spliced.", 0, true);
								break;
							}
						}
					} else {
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "It would be too dangerous to try to mix three seeds.", 0, true);
					}
				}
				return;
			}
		} else {
			isTree = true;
		}
	}
	switch (tile) {
	case 18: /*punch*/
		{
			if (world->items[x + (y * world->width)].foreground == 5638) {
				bool canuseremote = true;
				if (canuseremote) {
					if (static_cast<PlayerInfo*>(peer->data)->inventory.items.size() == static_cast<PlayerInfo*>(peer->data)->currentInventorySize) {
						//Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wInventory is full!", 0, true);
					} else {
						bool iscontainss = false;
						SearchInventoryItem(peer, 5640, 1, iscontainss);
						if (!iscontainss) {
							if (isWorldOwner(peer, world) && world->items[x + (y * world->width)].mid != 0 && world->items[x + (y * world->width)].mc != 0 || world->items[x + (y * world->width)].rm && world->items[x + (y * world->width)].mid != 0 && world->items[x + (y * world->width)].mc != 0) {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou received a MAGPLANT 5000 Remote.", 0, true);
								bool success = true;
								SaveItemMoreTimes(5640, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from MAGPLANT 5000");
								static_cast<PlayerInfo*>(peer->data)->magplantitemid = world->items[x + (y * world->width)].mid;
								static_cast<PlayerInfo*>(peer->data)->magplantx = x;
								static_cast<PlayerInfo*>(peer->data)->magplanty = y;
							}
						} else {
							static_cast<PlayerInfo*>(peer->data)->magplantitemid = world->items[x + (y * world->width)].mid;
							static_cast<PlayerInfo*>(peer->data)->magplantx = x;
							static_cast<PlayerInfo*>(peer->data)->magplanty = y;
							//Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou received a MAGPLANT 5000 Remote.", 0, true);
						}
					}
				}
			}
			if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3066) {
                if (world->items[x + (y * world->width)].fire) {
					int chanceofgems = 1;
					if (static_cast<PlayerInfo*>(peer->data)->firefighterlevel >= 4) chanceofgems = 2;
					if (static_cast<PlayerInfo*>(peer->data)->firefighterlevel >= 6) chanceofgems = 3;
					if (static_cast<PlayerInfo*>(peer->data)->firefighterlevel >= 8) chanceofgems = 4;
					if (static_cast<PlayerInfo*>(peer->data)->firefighterlevel >= 10) chanceofgems = 5;
					if (static_cast<PlayerInfo*>(peer->data)->firefighterlevel >= 2 && rand() % 100 <= chanceofgems) {
						auto Gems = (rand() % 25) + 1;
						auto currentGems = 0;
						ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
						ifs >> currentGems;
						ifs.close();
						currentGems += Gems;
						ofstream ofs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
						ofs << currentGems;
						ofs.close();
						Player::OnConsoleMessage(peer, "Fire King bonus obtained " + to_string(Gems) + " gems");
						Player::OnSetBux(peer, currentGems, 0);
					} else if (static_cast<PlayerInfo*>(peer->data)->firefighterlevel >= 3 && rand() % 100 <= 1) {
						bool success = true;
						SaveItemMoreTimes(4762, 1, peer, success, "");
						Player::OnConsoleMessage(peer, "Obtained Amethyst Block");
					} else if (static_cast<PlayerInfo*>(peer->data)->firefighterlevel >= 4 && rand() % 100 <= 2) {
						bool success = true;
						SaveItemMoreTimes(7156, 1, peer, success, "");
						Player::OnConsoleMessage(peer, "Obtained Fallen Pillar");
					} else if (static_cast<PlayerInfo*>(peer->data)->firefighterlevel >= 7 && rand() % 100 <= 1) {
						bool success = true;
						SaveItemMoreTimes(9468, 1, peer, success, "");
						Player::OnConsoleMessage(peer, "Obtained Diamond Stone");
					} else if (static_cast<PlayerInfo*>(peer->data)->firefighterlevel == 10 && rand() % 300 <= 1 && getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::BACKGROUND || static_cast<PlayerInfo*>(peer->data)->firefighterlevel == 10 && rand() % 300 <= 1 && getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SFX_FOREGROUND || static_cast<PlayerInfo*>(peer->data)->firefighterlevel == 10 && rand() % 300 <= 1 && getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::FOREGROUND) {
						bool success = true;
						SaveItemMoreTimes(world->items[x + (y * world->width)].foreground, 1, peer, success, "");
						Player::OnConsoleMessage(peer, "Obtained " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
					}
					int targetfirelevel = 1500;
					if (static_cast<PlayerInfo*>(peer->data)->firefighterlevel > 0) targetfirelevel = targetfirelevel * static_cast<PlayerInfo*>(peer->data)->firefighterlevel;
					if (static_cast<PlayerInfo*>(peer->data)->firefighterlevel == 0) targetfirelevel = 750;
					if (static_cast<PlayerInfo*>(peer->data)->firefighterxp >= targetfirelevel && static_cast<PlayerInfo*>(peer->data)->firefighterlevel < 10) {
						static_cast<PlayerInfo*>(peer->data)->firefighterlevel++;
						static_cast<PlayerInfo*>(peer->data)->firefighterxp = 0;
						SyncPlayerRoles(peer, static_cast<PlayerInfo*>(peer->data)->firefighterlevel, "firefighter");
					} else {
						static_cast<PlayerInfo*>(peer->data)->firefighterxp++;
					}
                    world->items[x + (y * world->width)].fire = false;
                    UpdateBlockState(peer, x, y, true, world);
                    ENetPeer* net_peer;
                    for (net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
                        if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
                        if (isHere(peer, net_peer)) {
                            Player::OnParticleEffect(net_peer, 149, x * 32, y * 32, 0);
                        }
                    }
                 }
                return;
            }
			if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 4996 && !world->items[x + (y * world->width)].fire) {
				if (isSeed(world->items[x + (y * world->width)].foreground) || world->items[x + (y * world->width)].water || world->items[x + (y * world->width)].foreground == 6952 || world->items[x + (y * world->width)].foreground == 6954 || world->items[x + (y * world->width)].foreground == 5638 || world->items[x + (y * world->width)].foreground == 6946 || world->items[x + (y * world->width)].foreground == 6948 || world->items[x + (y * world->width)].foreground == 2978 || world->items[x + (y * world->width)].foreground == 1420 || world->items[x + (y * world->width)].foreground == 6214 || world->items[x + (y * world->width)].foreground == 1006 || world->items[x + (y * world->width)].foreground == 656 || world->items[x + (y * world->width)].foreground == 1420 || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::DONATION || world->items[x + (y * world->width)].foreground == 3528  || world->items[x + (y * world->width)].foreground == 0 && world->items[x + (y * world->width)].background == 6864 || world->items[x + (y * world->width)].foreground == 0 && world->items[x + (y * world->width)].background == 0 || world->items[x + (y * world->width)].foreground == 6 || world->items[x + (y * world->width)].foreground == 8 || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::DISPLAY) {
					if (world->items[x + (y * world->width)].background != 6864) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wCan't burn that!", 0, true);
					return;
				}
				world->items[x + (y * world->width)].fire = true;
				for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
					if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, net_peer)) {
						Player::OnParticleEffect(net_peer, 150, x * 32 + 16, y * 32 + 16, 0);
					}
				}
				UpdateVisualsForBlock(peer, true, x, y, world);
				return;
			}
			if (world->items[x + (y * world->width)].fire) return;
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::PROVIDER) {
				if (world->owner == "" || static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || isMod(peer)) {
					if (calcBanDuration(world->items[x + (y * world->width)].growtime) == 0) {
						int chanceofdouble = 1;
						int weedmagic = 1;
						if (static_cast<PlayerInfo*>(peer->data)->providerlevel >= 4) chanceofdouble = 2;
						if (static_cast<PlayerInfo*>(peer->data)->providerlevel >= 6) chanceofdouble = 3;
						if (static_cast<PlayerInfo*>(peer->data)->providerlevel >= 8) chanceofdouble = 4;
						if (static_cast<PlayerInfo*>(peer->data)->providerlevel >= 10) chanceofdouble = 5;
						if (static_cast<PlayerInfo*>(peer->data)->providerlevel >= 2 && rand() % 100 <= chanceofdouble) {
							weedmagic = 2;
							Player::OnConsoleMessage(peer, "Weed Magic bonus doubled item");
						}
						else if (static_cast<PlayerInfo*>(peer->data)->providerlevel >= 4 && rand() % 100 <= 1) {
							bool success = true;
							SaveItemMoreTimes(9460, 1, peer, success, "");
							Player::OnConsoleMessage(peer, "Obtained Smaraged Block");
						}
						else if (static_cast<PlayerInfo*>(peer->data)->providerlevel >= 7 && rand() % 100 <= 1) {
							bool success = true;
							SaveItemMoreTimes(2410, 1, peer, success, "");
							Player::OnConsoleMessage(peer, "Obtained Emerald Shard");
						}
						else if (static_cast<PlayerInfo*>(peer->data)->providerlevel == 10 && rand() % 300 <= 1) {
							Player::OnConsoleMessage(peer, "The " + getItemDef(world->items[x + (y * world->width)].foreground).name + " has dropped himself");
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), world->items[x + (y * world->width)].foreground, 1, 0);
						}
						int targetproviderlevel = 1300;
						if (static_cast<PlayerInfo*>(peer->data)->providerlevel > 0) targetproviderlevel = targetproviderlevel * static_cast<PlayerInfo*>(peer->data)->providerlevel;
						if (static_cast<PlayerInfo*>(peer->data)->providerlevel == 0) targetproviderlevel = 600;
						if (static_cast<PlayerInfo*>(peer->data)->providerxp >= targetproviderlevel && static_cast<PlayerInfo*>(peer->data)->providerlevel < 10) {
							static_cast<PlayerInfo*>(peer->data)->providerlevel++;
							static_cast<PlayerInfo*>(peer->data)->providerxp = 0;
							SyncPlayerRoles(peer, static_cast<PlayerInfo*>(peer->data)->providerlevel, "provider");
						} else {
							static_cast<PlayerInfo*>(peer->data)->providerxp++;
						}

						if (world->items[x + (y * world->width)].foreground == 872) {						
							if (rand() % 100 <= 25) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 874, 2 * weedmagic, 0);
							else DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 874, 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 866) {
							if (rand() % 100 <= 25) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 868, 2 * weedmagic, 0);
							else DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 868, 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 3888) {
							if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3914) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 3890, rand() % 5 + 1 * weedmagic, 0);
							else DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 3890, rand() % 2 + 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 928) {
							vector<int> Dailyb{ 914, 916, 918, 920, 924 };
							const int Index = rand() % Dailyb.size();
							const auto ItemID = Dailyb[Index];
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), ItemID, 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 1044) {
							if (rand() % 100 <= 25) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 868, 2 * weedmagic, 0);
							else DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 868, 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 2798) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 822, 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 1008) {
							SendFarmableDrop(peer, 500, x, y);
						}

						if (world->items[x + (y * world->width)].foreground == 1636) {
							vector<int> Dailyb{ 728, 360, 308, 306, 2966, 1646, 3170, 1644, 1642, 3524, 1640, 1638, 2582, 3198, 8838, 6794, 10110 };
							const int Index = rand() % Dailyb.size();
							const auto ItemID = Dailyb[Index];
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), ItemID, 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 3044) {
							vector<int> Dailyb{ 2914, 3012, 3014, 3016, 3018, 5528, 5526 };
							const int Index = rand() % Dailyb.size();
							const auto ItemID = Dailyb[Index];
							if (rand() % 100 <= 25) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), ItemID, 2 * weedmagic, 0);
							else DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), ItemID, 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 6212) {
							vector<int> Dailyb{ 1258, 1260, 1262, 1264, 1266, 1268, 1270, 4308, 4310, 4312, 4314, 4316, 4318 };
							const int Index = rand() % Dailyb.size();
							const auto ItemID = Dailyb[Index];
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), ItemID, 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 6414) {
							vector<int> Dailyb{ 6520, 6538, 6522, 6528, 6540, 6518, 6530, 6524, 6536, 6534, 6532, 6526, 6416 };
							const int Index = rand() % Dailyb.size();
							const auto ItemID = Dailyb[Index];
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), ItemID, 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 5116) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5114, 1 * weedmagic, 0);
						}

						if (world->items[x + (y * world->width)].foreground == 1632) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 1634, 1 * weedmagic, 0);
						}





						int buvoid = world->items[x + (y * world->width)].foreground;
						world->items[x + (y * world->width)].foreground = 0;
						PlayerMoving data3;
						data3.packetType = 0x3;
						data3.characterState = 0x0;
						data3.x = x;
						data3.y = y;
						data3.punchX = x;
						data3.punchY = y;
						data3.XSpeed = 0;
						data3.YSpeed = 0;
						data3.netID = -1;
						data3.plantingTree = 0;
						ENetPeer* currentPeer;
						for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer)) {
								auto raw = packPlayerMoving(&data3);
								raw[2] = dicenr;
								raw[3] = dicenr;
								SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
							}
						}
						world->items[x + (y * world->width)].foreground = buvoid;
						PlayerMoving data4;
						data4.packetType = 0x3;
						data4.characterState = 0x0;
						data4.x = x;
						data4.y = y;
						data4.punchX = x;
						data4.punchY = y;
						data4.XSpeed = 0;
						data4.YSpeed = 0;
						data4.netID = -1;
						data4.plantingTree = buvoid;
						for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer)) {
								auto raw = packPlayerMoving(&data4);
								raw[2] = dicenr;
								raw[3] = dicenr;
								SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
							}
						}
						world->items[x + (y * world->width)].growtime = (GetCurrentTimeInternalSeconds() + getItemDef(world->items[x + (y * world->width)].foreground).growTime);
					}
				}
			}
			if (world->items[x + (y * world->width)].foreground == 1420 || world->items[x + (y * world->width)].foreground == 6214)
			{
				if (world->owner == "" || static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner))
				{
					auto seedexist = std::experimental::filesystem::exists("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					if (seedexist)
					{
						json j;
						ifstream fs("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						fs >> j;
						fs.close();
						bool found = false, success = false;
						if (j["clothHead"].get<string>() != "0")
						{
							SaveItemMoreTimes(atoi(j["clothHead"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
							found = true;
							j["clothHead"] = "0";
						}
						else if (j["clothHair"].get<string>() != "0")
						{
							SaveItemMoreTimes(atoi(j["clothHair"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
							found = true;
							j["clothHair"] = "0";
						}
						else if (j["clothMask"].get<string>() != "0")
						{
							SaveItemMoreTimes(atoi(j["clothMask"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
							found = true;
							j["clothMask"] = "0";
						}
						else if (j["clothNeck"].get<string>() != "0")
						{
							SaveItemMoreTimes(atoi(j["clothNeck"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
							found = true;
							j["clothNeck"] = "0";
						}
						else if (j["clothBack"].get<string>() != "0")
						{
							SaveItemMoreTimes(atoi(j["clothBack"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
							found = true;
							j["clothBack"] = "0";
						}
						else if (j["clothShirt"].get<string>() != "0")
						{
							SaveItemMoreTimes(atoi(j["clothShirt"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
							found = true;
							j["clothShirt"] = "0";
						}
						else if (j["clothPants"].get<string>() != "0")
						{
							SaveItemMoreTimes(atoi(j["clothPants"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
							found = true;
							j["clothPants"] = "0";
						}
						else if (j["clothFeet"].get<string>() != "0")
						{
							SaveItemMoreTimes(atoi(j["clothFeet"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
							found = true;
							j["clothFeet"] = "0";
						}
						else if (j["clothHand"].get<string>() != "0")
						{
							SaveItemMoreTimes(atoi(j["clothHand"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
							found = true;
							j["clothHand"] = "0";
						}

						if (found)
						{
							updateMannequin(peer, world->items[x + (y * world->width)].foreground, x, y, world->items[x + (y * world->width)].background, world->items[x + (y * world->width)].sign,
								atoi(j["clothHair"].get<string>().c_str()), atoi(j["clothHead"].get<string>().c_str()),
								atoi(j["clothMask"].get<string>().c_str()), atoi(j["clothHand"].get<string>().c_str()), atoi(j["clothNeck"].get<string>().c_str()),
								atoi(j["clothShirt"].get<string>().c_str()), atoi(j["clothPants"].get<string>().c_str()), atoi(j["clothFeet"].get<string>().c_str()),
								atoi(j["clothBack"].get<string>().c_str()), true, 0);

							ofstream of("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							of << j;
							of.close();
						}
					}
				}
			}
			if (world->items[x + (y * world->width)].foreground == 758) sendRoulete(peer);
			bool hassmallock = false;
			for (int i = 0; i < world->width * world->height; i++) {
				if (world->items[i].foreground == 202 || world->items[i].foreground == 204 || world->items[i].foreground == 206 || world->items[i].foreground == 4994) {
					hassmallock = true;
					break;
				}
			}
			if (hassmallock && !isMod(peer) || world->owner != "" && !isWorldOwner(peer, world)) {
				if (!isMod(peer)) {
					if (!RestrictedArea(peer, world, x, y)) {
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK) {
							string whoslock = world->owner;
							if (world->items[x + (y * world->width)].foreground == 202 || world->items[x + (y * world->width)].foreground == 204 || world->items[x + (y * world->width)].foreground == 206 || world->items[x + (y * world->width)].foreground == 4994) {
								whoslock = world->items[x + (y * world->width)].monitorname;
							}
							if (static_cast<PlayerInfo*>(peer->data)->rawName != whoslock) {
							MYSQL_ROW row;
							string nickname, adminlevel;
							string q = "SELECT * FROM PlayerDatabase WHERE username = '" + whoslock + "' LIMIT 1";
							if (mysql_query(conn, q.c_str())) {
								cout << mysql_error(conn) << endl;
								enet_peer_disconnect_later(peer, 0);
								return;
							}
							res = mysql_store_result(conn);
							while (row = mysql_fetch_row(res)) {
								adminlevel = row[19];
								nickname = row[44];
							}
							if (nickname == "") {
								if (adminlevel == "1") {
									nickname = "`#@" + whoslock;
								} else if (adminlevel == "2") {
									nickname = "`6@" + whoslock;
								} else {
									nickname = whoslock;
								}
							} 
							if (world->items[x + (y * world->width)].opened) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
							else Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`4No Access`w)", 0, true);
							Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
							return;
							}
						}
					}
					else if (isWorldAdmin(peer, world)) {
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK) {
							MYSQL_ROW row;
							string nickname, adminlevel;
							string q = "SELECT * FROM PlayerDatabase WHERE username = '" + world->owner + "' LIMIT 1";
							if (mysql_query(conn, q.c_str())) {
								cout << mysql_error(conn) << endl;
								enet_peer_disconnect_later(peer, 0);
								return;
							}
							res = mysql_store_result(conn);
							while (row = mysql_fetch_row(res)) {
								adminlevel = row[19];
								nickname = row[44];
							}
							if (nickname == "") {
								if (adminlevel == "1") {
									nickname = "`#@" + world->owner;
								} else if (adminlevel == "2") {
									nickname = "`6@" + world->owner;
								} else {
									nickname = world->owner;
								}
							} 
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`2Access Granted`w)", 0, true);
							Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
							return;
						}
					}
					else if (world->isPublic)
					{
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							MYSQL_ROW row;
							string nickname, adminlevel;
							string q = "SELECT * FROM PlayerDatabase WHERE username = '" + world->owner + "' LIMIT 1";
							if (mysql_query(conn, q.c_str())) {
								cout << mysql_error(conn) << endl;
								enet_peer_disconnect_later(peer, 0);
								return;
							}
							res = mysql_store_result(conn);
							while (row = mysql_fetch_row(res)) {
								adminlevel = row[19];
								nickname = row[44];
							}
							if (nickname == "") {
								if (adminlevel == "1") {
									nickname = "`#@" + world->owner;
								} else if (adminlevel == "2") {
									nickname = "`6@" + world->owner;
								} else {
									nickname = world->owner;
								}
							} 
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
							Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
							return;
						}
					} else if (world->isEvent) {
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							string whoslock = world->owner;
							if (world->items[x + (y * world->width)].foreground == 202 || world->items[x + (y * world->width)].foreground == 204 || world->items[x + (y * world->width)].foreground == 206 || world->items[x + (y * world->width)].foreground == 4994) {
								whoslock = world->items[x + (y * world->width)].monitorname;
							}
							if (static_cast<PlayerInfo*>(peer->data)->rawName != whoslock) {
							MYSQL_ROW row;
							string nickname, adminlevel;
							string q = "SELECT * FROM PlayerDatabase WHERE username = '" + whoslock + "' LIMIT 1";
							if (mysql_query(conn, q.c_str())) {
								cout << mysql_error(conn) << endl;
								enet_peer_disconnect_later(peer, 0);
								return;
							}
							res = mysql_store_result(conn);
							while (row = mysql_fetch_row(res)) {
								adminlevel = row[19];
								nickname = row[44];
							}
							if (nickname == "") {
								if (adminlevel == "1") {
									nickname = "`#@" + whoslock;
								} else if (adminlevel == "2") {
									nickname = "`6@" + whoslock;
								} else {
									nickname = whoslock;
								}
							} 
							if (world->items[x + (y * world->width)].opened) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
							else Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`4No Access`w)", 0, true);
							Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
							return;
							}
						}
						else if (world->items[x + (y * world->width)].foreground != world->publicBlock && causedBy != -1) {
							if (world->items[x + (y * world->width)].foreground != 0) Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
							else if (world->items[x + (y * world->width)].background != 0) Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
							return;
						}
					} else {
						Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
						return;
					}
				}
				if (tile == 18 && isMod(peer))
				{
					if (isWorldAdmin(peer, world) && !isWorldOwner(peer, world))
					{
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							MYSQL_ROW row;
							string nickname, adminlevel;
							string q = "SELECT * FROM PlayerDatabase WHERE username = '" + world->owner + "' LIMIT 1";
							if (mysql_query(conn, q.c_str())) {
								cout << mysql_error(conn) << endl;
								enet_peer_disconnect_later(peer, 0);
								return;
							}
							res = mysql_store_result(conn);
							while (row = mysql_fetch_row(res)) {
								adminlevel = row[19];
								nickname = row[44];
							}
							if (nickname == "") {
								if (adminlevel == "1") {
									nickname = "`#@" + world->owner;
								} else if (adminlevel == "2") {
									nickname = "`6@" + world->owner;
								} else {
									nickname = world->owner;
								}
							} 
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`2Access Granted`w)", 0, true);
						}
					}
					else if (world->isPublic && !isWorldOwner(peer, world))
					{
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							MYSQL_ROW row;
							string nickname, adminlevel;
							string q = "SELECT * FROM PlayerDatabase WHERE username = '" + world->owner + "' LIMIT 1";
							if (mysql_query(conn, q.c_str())) {
								cout << mysql_error(conn) << endl;
								enet_peer_disconnect_later(peer, 0);
								return;
							}
							res = mysql_store_result(conn);
							while (row = mysql_fetch_row(res)) {
								adminlevel = row[19];
								nickname = row[44];
							}
							if (nickname == "") {
								if (adminlevel == "1") {
									nickname = "`#@" + world->owner;
								} else if (adminlevel == "2") {
									nickname = "`6@" + world->owner;
								} else {
									nickname = world->owner;
								}
							} 
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
						}
					}
					else if (world->isEvent && !isWorldOwner(peer, world))
					{
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							string whoslock = world->owner;
							if (world->items[x + (y * world->width)].foreground == 202 || world->items[x + (y * world->width)].foreground == 204 || world->items[x + (y * world->width)].foreground == 206 || world->items[x + (y * world->width)].foreground == 4994) {
								whoslock = world->items[x + (y * world->width)].monitorname;
							}
							if (static_cast<PlayerInfo*>(peer->data)->rawName != whoslock) {
							MYSQL_ROW row;
							string nickname, adminlevel;
							string q = "SELECT * FROM PlayerDatabase WHERE username = '" + whoslock + "' LIMIT 1";
							if (mysql_query(conn, q.c_str())) {
								cout << mysql_error(conn) << endl;
								enet_peer_disconnect_later(peer, 0);
								return;
							}
							res = mysql_store_result(conn);
							while (row = mysql_fetch_row(res)) {
								adminlevel = row[19];
								nickname = row[44];
							}
							if (nickname == "") {
								if (adminlevel == "1") {
									nickname = "`#@" + whoslock;
								} else if (adminlevel == "2") {
									nickname = "`6@" + whoslock;
								} else {
									nickname = whoslock;
								}
							} 
							if (world->items[x + (y * world->width)].opened) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
							else Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`4No Access`w)", 0, true);
							}
						}
					}
				}
			} if (!isDev(peer)) {
				if (world->items[x + (y * world->width)].foreground == 6) {
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wIt's too strong to break.", 0, true);
					return;
				} if (world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 7372 || world->items[x + (y * world->width)].foreground == 3760) {
					if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 8452) {
					} else {
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wIt's too strong to break.", 0, true);
						return;
					}
				} if (tile == 9444) {
					if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 2952 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9430 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9448 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9452 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 2592) {
					} else {
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5This stone is too strong!", 0, true);
						return;
					}
				}
				if (tile == 6 || tile == 3760 || tile == 1000 || tile == 7372 || tile == 1770 || tile == 1832 || tile == 4720) {
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wIt's too heavy to place.", 0, true);
					return;
				}
			}
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::WEATHER && isWorldOwner(peer, world) || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::WEATHER && isWorldAdmin(peer, world) || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::WEATHER && isMod(peer)) SendWeather(peer, tile, world, x, y);
			if (world->items[x + (y * world->width)].foreground == 2946) {
				if (world->isPublic || isWorldAdmin(peer, world)) {
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That area is owned by " + world->owner + "", 0, true);
					return;
				}
			}
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::RANDOM_BLOCK) {
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, currentPeer)) {
						sendDice(currentPeer, rand() % 5 + 1, x, y);
					}
				}
			}
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::TOGGLE_FOREGROUND || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::CHEMICAL_COMBINER || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::CHEST) {
				if (isWorldOwner(peer, world) || world->owner == "" || isMod(peer) || isWorldAdmin(peer, world)) {
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::CHEMICAL_COMBINER) {
						if (world->items[x + (y * world->width)].activated) {
							SendCombiner(peer, x, y, 1096, 1098, 1828, 4, 4, 6, 1056, true); /*Songpyeon*/
							SendCombiner(peer, x, y, 1056, 1096, 1828, 15, 30, 15, 1804, true); /*Zeus Lightning Bolt*/
							SendCombiner(peer, x, y, 611, 874, 0, 100, 15, 0, 1552, false); /*Pet Bunny Recipe*/
							SendCombiner(peer, x, y, 1056, 1804, 3870, 5, 10, 15, 1824, true); /*AutumnWings*/
							SendCombiner(peer, x, y, 1056, 7058, 10030, 3, 10, 1, 1826, true); /*AutumnBomb*/
							SendCombiner(peer, x, y, 1056, 1804, 10030, 1, 5, 1, 3074, true); /*FloatingLeaf*/
							SendCombiner(peer, x, y, 10322, 10324, 10326, 1, 1, 1, 10328, false); /*Dark Kings Offering*/
							SendCombiner(peer, x, y, 898, 4538, 5018, 2, 1, 1, 5022, false); /*Chicken Plow*/
							SendCombiner(peer, x, y, 2274, 5026, 5028, 1, 5, 20, 5060, false); /*Verdant Gate*/
							SendCombiner(peer, x, y, 2274, 5028, 5024, 1, 5, 20, 5054, false); /*Inferno Gate*/
							SendCombiner(peer, x, y, 2274, 5024, 5030, 1, 5, 20, 5058, false); /*Typhoon Gate*/
							SendCombiner(peer, x, y, 2274, 5030, 5026, 1, 5, 20, 5056, false); /*Tidal Gate*/
							SendCombiner(peer, x, y, 2492, 5028, 5026, 1, 20, 5, 5050, false); /*Earth Asteroid*/
							SendCombiner(peer, x, y, 2492, 5024, 5028, 1, 20, 5, 5046, false); /*Fire Asteroid*/
							SendCombiner(peer, x, y, 2492, 5030, 5024, 1, 20, 5, 5052, false); /*Wind Asteroid*/
							SendCombiner(peer, x, y, 2492, 5026, 5030, 1, 20, 5, 5048, false); /*Water Asteroid*/
							SendCombiner(peer, x, y, 3946, 5060, 5028, 100, 4, 5, 5070, false); /*Crystallized Reality*/
							SendCombiner(peer, x, y, 3838, 5054, 5024, 200, 4, 5, 5072, false); /*Crystallized Wealth*/
							SendCombiner(peer, x, y, 340, 5058, 5030, 200, 4, 5, 5074, false); /*Crystallized Brilliance*/
							SendCombiner(peer, x, y, 2272, 5056, 5026, 30, 4, 5, 5076, false); /*Crystallized Nature*/
							SendCombiner(peer, x, y, 5050, 5048, 5028, 2, 2, 5, 5066, false); /*Ancient Bracket*/
							SendCombiner(peer, x, y, 5046, 5052, 5024, 2, 2, 5, 5062, false); /*Ancient Hinge*/
							SendCombiner(peer, x, y, 5052, 5050, 5030, 2, 2, 5, 5068, false); /*Ancient Lens*/
							SendCombiner(peer, x, y, 5048, 5046, 5026, 2, 2, 5, 5064, false); /*Ancient Pin*/
							SendCombiner(peer, x, y, 5070, 5066, 5064, 1, 2, 5, 5080, false); /*Ancestral Tesseract of Dimensions*/
							SendCombiner(peer, x, y, 5076, 5068, 5066, 1, 2, 5, 5082, false); /*Ancestral Seed of Life*/
							SendCombiner(peer, x, y, 5072, 5064, 5062, 1, 2, 5, 5084, false); /*Ancestral Lens of Riches*/
							SendCombiner(peer, x, y, 5074, 5062, 5068, 1, 2, 5, 5078, false); /*Ancestral Totem of Wisdom*/			
							SendCombiner(peer, x, y, 362, 386, 1458, 1, 200, 1, 1460, false); /*Golden Angel Wings*/
							SendCombiner(peer, x, y, 364, 386, 1458, 1, 200, 1, 1462, false); /*Golden Diaper*/
							SendCombiner(peer, x, y, 1470, 386, 1458, 1, 200, 1, 1466, false); /*Golden Diamond Necklace*/
							SendCombiner(peer, x, y, 366, 386, 1458, 1, 200, 1, 1464, false); /*Golden Heartbow*/
							SendCombiner(peer, x, y, 2388, 386, 1458, 1, 20, 1, 2386, false); /*Heavenly Scythe*/
							SendCombiner(peer, x, y, 2390, 386, 1458, 1, 20, 1, 2392, false); /*Teeny Golden Wings*/
							SendCombiner(peer, x, y, 2384, 386, 1458, 1, 20, 1, 2394, false); /*Golden Love Bug*/
							SendCombiner(peer, x, y, 4412, 386, 1458, 1, 20, 1, 4414, false); /*Golden Pegasus*/
							SendCombiner(peer, x, y, 4416, 386, 1458, 1, 20, 1, 4420, false); /*Golden Heart Glasses*/
							SendCombiner(peer, x, y, 5644, 386, 1458, 1, 20, 1, 5646, false); /*Golden Heart Shirt*/
							SendCombiner(peer, x, y, 5648, 386, 1458, 1, 20, 1, 5650, false); /*Golden Talaria*/
							SendCombiner(peer, x, y, 7826, 386, 1458, 1, 200, 1, 7828, false); /*Golden Heartstaff*/
							SendCombiner(peer, x, y, 7830, 386, 1458, 1, 200, 1, 7832, false); /*Golden Heartsword*/
							SendCombiner(peer, x, y, 7826, 7830, 1458, 1, 1, 1, 7834, false); /*Stained Glass Heartwings*/
							SendCombiner(peer, x, y, 9320, 386, 1458, 1, 200, 1, 9322, false); /*Golden Sunset Cape*/
							SendCombiner(peer, x, y, 9342, 9340, 1458, 1, 1, 1, 9344, false); /*Datemaster's Heart Locket*/
							SendCombiner(peer, x, y, 9324, 386, 1458, 1, 200, 1, 9326, false); /*Golden Heartthrob Helm*/
							SendCombiner(peer, x, y, 9314, 1800, 186, 1, 1, 200, 9316, false); /*Beefy Biceps*/
							SendCombiner(peer, x, y, 1506, 8794, 4406, 1, 1, 1, 9318, false); /*Snuggly Kitty Scarf*/
							SendCombiner(peer, x, y, 914, 916, 924, 5, 5, 10, 770, false); /*Combover*/
							SendCombiner(peer, x, y, 914, 916, 920, 30, 4, 1, 906, false); /*Shocking Hair*/
							SendCombiner(peer, x, y, 914, 916, 918, 10, 5, 1, 902, false, 3); /*Shockinator*/
							SendCombiner(peer, x, y, 914, 924, 920, 5, 4, 2, 926, false, 5); /*Steel Table*/							
							SendCombiner(peer, x, y, 914, 924, 918, 6, 3, 4, 1114, false); /*Dragon Tail*/
							SendCombiner(peer, x, y, 914, 920, 918, 15, 4, 2, 978, false, 4); /*Slime*/
							SendCombiner(peer, x, y, 916, 924, 918, 10, 3, 3, 772, false); /*Lab Coat*/
							SendCombiner(peer, x, y, 916, 920, 918, 2, 4, 3, 904, false); /*Ze Goggles*/
							SendCombiner(peer, x, y, 924, 920, 918, 20, 10, 5, 922, false); /*Mysterious Chemical*/
							SendCombiner(peer, x, y, 914, 916, 922, 20, 10, 1, 1162, false); /*Forcefield*/
							SendCombiner(peer, x, y, 914, 920, 922, 10, 2, 1, 1746, false, 5); /*Fuel Pack*/
							SendCombiner(peer, x, y, 914, 918, 922, 20, 15, 10, 1542, false); /*Battle Trout*/
							SendCombiner(peer, x, y, 916, 924, 922, 8, 4, 1, 2588, false); /*Sassy Boots*/
							SendCombiner(peer, x, y, 916, 918, 922, 1, 1, 1, 1866, false); /*Block Glue*/
							SendCombiner(peer, x, y, 924, 920, 922, 3, 3, 3, 908, false); /*Enchanced Intellect*/
							SendCombiner(peer, x, y, 924, 918, 922, 4, 3, 1, 1310, false); /*Thingamajig*/
							SendCombiner(peer, x, y, 920, 918, 922, 200, 200, 200, 910, false); /*Reanimator Remote*/
							SendCombiner(peer, x, y, 914, 922, 1962, 10, 10, 10, 4582, false); /*Food Grinder*/
							SendCombiner(peer, x, y, 916, 924, 1962, 9, 5, 1, 4552, false); /*Synthetic Oculum*/
							UpdateBlockState(peer, x, y, true, world);
							world->items[x + (y * world->width)].activated = false;
						} else {
							UpdateBlockState(peer, x, y, true, world);
							world->items[x + (y * world->width)].activated = true;
						}
					} else {
						if (world->items[x + (y * world->width)].activated) {
							UpdateBlockState(peer, x, y, true, world);
							world->items[x + (y * world->width)].activated = false;
						} else {
							UpdateBlockState(peer, x, y, true, world);
							world->items[x + (y * world->width)].activated = true;
						}
					}
				}
			}
			if (isSeed(world->items[x + (y * world->width)].foreground) && calcBanDuration(world->items[x + (y * world->width)].growtime) == 0 && static_cast<PlayerInfo*>(peer->data)->cloth_hand != 3066) {
				if (world->isPublic || isWorldAdmin(peer, world) || isWorldOwner(peer, world) || world->owner == "" || isMod(peer) || !RestrictedArea(peer, world, x, y)) {
					for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
						if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, net_peer)) {
							treeModify(net_peer, x, y, static_cast<PlayerInfo*>(peer->data)->netID);
						}
					}
					auto chance = (rand() % 100) + 1;
					int numb = world->items[x + (y * world->width)].fruitcount;
					DropGem(peer, x, y);
					if (chance < 15 && getItemDef(world->items[x + (y * world->width)].foreground).rarity != 999) {
						if (getItemDef(world->items[x + (y * world->width)].foreground - 1).blockType != BlockTypes::CLOTHING) {
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "A " + getItemDef(world->items[x + (y * world->width)].foreground).name + " seed falls out!", 0, true);
							DropItem(peer, -1, x * 32 - (rand() % 8), y * 32 + (rand() % 8), world->items[x + (y * world->width)].foreground, 1, 0);
						}
					}
					if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 6840) {
						auto chance1 = (rand() % 100) + 1;
						if (chance1 <= 30) {
							numb += 1;
							Player::OnParticleEffect(peer, 49, data.punchX * 32, data.punchY * 32, 0);
						}
					}
					int chanceofbuff = 1;
					if (static_cast<PlayerInfo*>(peer->data)->level >= 10) chanceofbuff = 1;
					if (static_cast<PlayerInfo*>(peer->data)->level >= 13) chanceofbuff = 2;
					if (static_cast<PlayerInfo*>(peer->data)->level >= 10 && rand() % 100 <= chanceofbuff) {
						numb += 1;
						Player::OnConsoleMessage(peer, "Harvester bonus extra block drop");
					}
					DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), world->items[x + (y * world->width)].foreground - 1, numb, 0);
					world->items[x + (y * world->width)].spliced = false;
					world->items[x + (y * world->width)].growtime = 0;
					world->items[x + (y * world->width)].fruitcount = 0;
					if (HarvestEvent) {
						SendHarvestFestivalDrop(peer, x, y, getItemDef(world->items[x + (y * world->width)].foreground).rarity);
					}
					if (getItemDef(world->items[x + (y * world->width)].foreground).rarity < 25) {
						SendXP(peer, 1);
					} else if (getItemDef(world->items[x + (y * world->width)].foreground).rarity >= 25 && getItemDef(world->items[x + (y * world->width)].foreground).rarity < 40) {
						SendXP(peer, 2);
					} else if (getItemDef(world->items[x + (y * world->width)].foreground).rarity >= 40 && getItemDef(world->items[x + (y * world->width)].foreground).rarity < 60) {
						SendXP(peer, 3);
					} else if (getItemDef(world->items[x + (y * world->width)].foreground).rarity >= 60 && getItemDef(world->items[x + (y * world->width)].foreground).rarity < 80) {
						SendXP(peer, 4);
					} else if (getItemDef(world->items[x + (y * world->width)].foreground).rarity >= 80 && getItemDef(world->items[x + (y * world->width)].foreground).rarity < 100) {
						SendXP(peer, 5);
					} else if (getItemDef(world->items[x + (y * world->width)].foreground).rarity >= 100) {
						SendXP(peer, 6);
					}
					world->items[x + (y * world->width)].foreground = 0;
					return;
				}
				return;
			} 
			if (!static_cast<PlayerInfo*>(peer->data)->Fishing) break;
			SyncFish(peer);
		}
	case 32: /*wrench*/
		{
		 	if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK) {
				if (isWorldOwner(peer, world) || isMod(peer) || static_cast<PlayerInfo*>(peer->data)->rawName == world->items[x + (y * world->width)].monitorname) {
					static_cast<PlayerInfo*>(peer->data)->wrenchedBlockLocation = x + (y * world->width);
					if (world->items[x + (y * world->width)].foreground == 202 || world->items[x + (y * world->width)].foreground == 204 || world->items[x + (y * world->width)].foreground == 206 || world->items[x + (y * world->width)].foreground == 4994) {
						string allow_dialog = "\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|0";
						if (world->items[x + (y * world->width)].opened) {
							allow_dialog = "\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|1";
						}
						Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wEdit Small Lock``|left|202|\nadd_label|small|`wAccess list:``|left\nadd_spacer|small|\nadd_label|small|Currently, you're the only one with access.``|left\nadd_spacer|small|\nadd_player_picker|playerNetID|`wAdd``|" + allow_dialog + "\nadd_checkbox|checkbox_ignore|Ignore empty air|0\nadd_button|recalcLock|`wRe-apply lock``|noflags|0|0|\nend_dialog|lock_edit|Cancel|OK|");
						return;
					}
					int ispub = world->isPublic;
					string str = "";
					for (auto i = 0; i < world->accessed.size(); i++) {
						auto st = world->accessed.at(i);
						str += "\nadd_label|small|" + st.substr(st.find("|") + 1, st.length()) + "|left|";
					}
					int muted = world->silence;
					string wlmenu = "";
					if (world->items[x + (y * world->width)].foreground == 4802) {
						string rainbows = "0";
						if (world->rainbow) rainbows = "1";
						if (str == "") {
							wlmenu = "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_label|small|`wAccess list:``|left\nadd_spacer|small|\nadd_label|small|Currently, you're the only one with access.``|left\nadd_spacer|small|\nadd_player_picker|playerNetID|`wAdd``|\nadd_button|WorldDropPickup|`wEnable/Disable Collecting Items``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + to_string(ispub) + "\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|0|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|\nadd_checkbox|checkbox_rainbow|Enable Rainbows!|" + rainbows + "\nadd_checkbox|checkbox_muted|Silence, Peasants!|" + to_string(muted) + "|noflags|0|0|\nadd_text_input|minimum_entry_level|World Level: |1|3|\nadd_smalltext|Set minimum world entry level.|\nadd_button|changecat|`wCategory: " + world->category + "``|noflags|0|0|\nend_dialog|lock_edit|Cancel|OK|";
						} else {
							wlmenu = "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_label|small|`wAccess list:``|left\nadd_spacer|small|\nadd_label|small|" + str + "|left\nadd_spacer|small|\nadd_player_picker|playerNetID|`wAdd``|\nadd_button|WorldDropPickup|`wEnable/Disable Collecting Items``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + to_string(ispub) + "\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|0|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|\nadd_checkbox|checkbox_rainbow|Enable Rainbows!|" + rainbows + "\nadd_checkbox|checkbox_muted|Silence, Peasants!|" + to_string(muted) + "|noflags|0|0|\nadd_text_input|minimum_entry_level|World Level: |1|3|\nadd_smalltext|Set minimum world entry level.|\nadd_button|changecat|`wCategory: " + world->category + "``|noflags|0|0|\nend_dialog|lock_edit|Cancel|OK|";
						}
						Player::OnDialogRequest(peer, wlmenu);
					} else {
						if (str == "") {
							wlmenu = "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_label|small|`wAccess list:``|left\nadd_spacer|small|\nadd_label|small|Currently, you're the only one with access.``|left\nadd_spacer|small|\nadd_player_picker|playerNetID|`wAdd``|\nadd_button|WorldDropPickup|`wEnable/Disable Collecting Items``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + to_string(ispub) + "\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|0|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|noflags|0|0|\nadd_text_input|minimum_entry_level|World Level: |" + to_string(world->entrylevel) + "|3|\nadd_smalltext|Set minimum world entry level.|\nadd_button|changecat|`wCategory: " + world->category + "``|noflags|0|0|\nend_dialog|lock_edit|Cancel|OK|";
						} else {
							wlmenu = "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "`|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_label|small|`wAccess list:``|left\nadd_spacer|small|\nadd_label|small|" + str + "|left\nadd_spacer|small|\nadd_player_picker|playerNetID|`wAdd``|\nadd_button|WorldDropPickup|`wEnable/Disable Collecting Items``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + to_string(ispub) + "\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|0|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|noflags|0|0|\nadd_text_input|minimum_entry_level|World Level: |" + to_string(world->entrylevel) + "|3|\nadd_smalltext|Set minimum world entry level.|\nadd_button|changecat|`wCategory: " + world->category + "``|noflags|0|0|\nend_dialog|lock_edit|Cancel|OK|";
						}
						Player::OnDialogRequest(peer, wlmenu);
					}
				} else {
					if (isWorldAdmin(peer, world)) {
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK) {
							string whoslock = world->owner;
							if (world->items[x + (y * world->width)].foreground == 202 || world->items[x + (y * world->width)].foreground == 204 || world->items[x + (y * world->width)].foreground == 206 || world->items[x + (y * world->width)].foreground == 4994) {
								whoslock = world->items[x + (y * world->width)].monitorname;
							}
							MYSQL_ROW row;
							string nickname, adminlevel;
							string q = "SELECT * FROM PlayerDatabase WHERE username = '" + whoslock + "' LIMIT 1";
							if (mysql_query(conn, q.c_str())) {
								cout << mysql_error(conn) << endl;
								enet_peer_disconnect_later(peer, 0);
								return;
							}
							res = mysql_store_result(conn);
							while (row = mysql_fetch_row(res)) {
								adminlevel = row[19];
								nickname = row[44];
							}
							if (nickname == "") {
								if (adminlevel == "1") {
									nickname = "`#@" + whoslock;
								} else if (adminlevel == "2") {
									nickname = "`6@" + whoslock;
								} else {
									nickname = whoslock;
								}
							}  
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`2Access Granted`w)", 0, true);
							Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
							return;
						}
					} else if (world->isPublic) {
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK) {
							string whoslock = world->owner;
							if (world->items[x + (y * world->width)].foreground == 202 || world->items[x + (y * world->width)].foreground == 204 || world->items[x + (y * world->width)].foreground == 206 || world->items[x + (y * world->width)].foreground == 4994) {
								whoslock = world->items[x + (y * world->width)].monitorname;
							}
							MYSQL_ROW row;
							string nickname, adminlevel;
							string q = "SELECT * FROM PlayerDatabase WHERE username = '" + whoslock + "' LIMIT 1";
							if (mysql_query(conn, q.c_str())) {
								cout << mysql_error(conn) << endl;
								enet_peer_disconnect_later(peer, 0);
								return;
							}
							res = mysql_store_result(conn);
							while (row = mysql_fetch_row(res)) {
								adminlevel = row[19];
								nickname = row[44];
							}
							if (nickname == "") {
								if (adminlevel == "1") {
									nickname = "`#@" + whoslock;
								} else if (adminlevel == "2") {
									nickname = "`6@" + whoslock;
								} else {
									nickname = whoslock;
								}
							}  
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
							Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
							return;
						}
					} else if (world->isEvent) {
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK) {
							string whoslock = world->owner;
							if (world->items[x + (y * world->width)].foreground == 202 || world->items[x + (y * world->width)].foreground == 204 || world->items[x + (y * world->width)].foreground == 206 || world->items[x + (y * world->width)].foreground == 4994) {
								whoslock = world->items[x + (y * world->width)].monitorname;
							}
							if (static_cast<PlayerInfo*>(peer->data)->rawName != whoslock) {
							MYSQL_ROW row;
							string nickname, adminlevel;
							string q = "SELECT * FROM PlayerDatabase WHERE username = '" + whoslock + "' LIMIT 1";
							if (mysql_query(conn, q.c_str())) {
								cout << mysql_error(conn) << endl;
								enet_peer_disconnect_later(peer, 0);
								return;
							}
							res = mysql_store_result(conn);
							while (row = mysql_fetch_row(res)) {
								adminlevel = row[19];
								nickname = row[44];
							}
							if (nickname == "") {
								if (adminlevel == "1") {
									nickname = "`#@" + whoslock;
								} else if (adminlevel == "2") {
									nickname = "`6@" + whoslock;
								} else {
									nickname = whoslock;
								}
							}  
							if (world->items[x + (y * world->width)].opened) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
							else Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`4No Access`w)", 0, true);
							Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
							return;
							}
						}
					}
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 6952) {
				if (world->isPublic) return; 
				if (world->owner == "" || static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || isMod(peer)) {
					static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
					static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
					string PoolDialog = "\nadd_item_picker|autobreakitem|No block type selected!|Choose the target item!|";
					string StopDialog = "";
					if (world->items[x + (y * world->width)].mid != 0) {
						PoolDialog = "\nadd_item_picker|autobreakitem|Target block is: `2" + getItemDef(world->items[x + (y * world->width)].mid).name +"``|Choose the target item!|";
						StopDialog = "\nadd_button|manipulatorstop|Stop the machine|";
					}
					string AutoHarvestDialog = "\nadd_checkbox|checkbox_autoharvest|`oAuto harvest trees|0|";
					if (world->items[x + (y * world->width)].rm) {
						AutoHarvestDialog = "\nadd_checkbox|checkbox_autoharvest|`oAuto harvest trees|1|";
					}
					Player::OnDialogRequest(peer, "set_default_color|\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_textbox|`oThis machine will break blocks for you! Select one and it will start breaking it immediately! Just make sure to select the right one|left||" + PoolDialog + "|" + StopDialog + "|" + AutoHarvestDialog + "\nend_dialog|autobreak|Close|OK|");
				}
				return;
			}

			if (world->items[x + (y * world->width)].foreground == 6954) {
				if (world->isPublic) return; 
				if (world->owner == "" || static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || isMod(peer)) {
					static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
					static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
					string PoolDialog = "\nadd_item_picker|autoplaceitem|No auto place block selected!|Choose the target block!|";
					string addthemdialog = "";
					string stopdialog = "";
					if (world->items[x + (y * world->width)].mid != 0) {
						PoolDialog = "\nadd_item_picker|autoplaceitem|Target auto place block is: `2" + getItemDef(world->items[x + (y * world->width)].mid).name +"`` (`2" + to_string(world->items[x + (y * world->width)].mc) + "/5000``)|Choose the target block!|";
						auto mtitems = 0;
						for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++) {
							if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == world->items[x + (y * world->width)].mid) {
								mtitems = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
								break;
							}
						}
						if (mtitems != 0 && world->items[x + (y * world->width)].mc + mtitems <= 5000) {
							addthemdialog = "\nadd_smalltext|`oYou have " + to_string(mtitems) + " " + getItemDef(world->items[x + (y * world->width)].mid).name + " in your backpack.``|left|\nadd_button|addorganic|Add them to the machine|";
						}
						if (world->items[x + (y * world->width)].mc > 0) stopdialog = "\nadd_button|organicstop|Retrieve Items|";
					}
					string PoolDialogs = "\nadd_item_picker|autoplaceidentityitem|No ident block selected!|Choose the identification block!|";
					if (world->items[x + (y * world->width)].vid != 0) {
						PoolDialogs = "\nadd_item_picker|autoplaceidentityitem|Target ident block is: `2" + getItemDef(world->items[x + (y * world->width)].vid).name +"``|Choose the identification block!|";
					}
					string MagplantsStoragesList = "";
					string UseMagDialog = "";
					if (world->items[x + (y * world->width)].mid != 0) {
						for (auto i = 0; i < world->width * world->height; i++) {
							if (world->items[i].foreground == 5638 && world->items[i].mid == world->items[x + (y * world->width)].mid) {
								MagplantsStoragesList += "\nadd_label_with_icon|small|`2" + getItemDef(world->items[i].mid).name + " `oMagplant (`2" + to_string(world->items[i].mc) + "`o)|left|" + to_string(world->items[i].mid) + "|";
							}
						}
						if (MagplantsStoragesList != "") {
							UseMagDialog = "\nadd_checkbox|checkbox_publicremote|`oUse magplants storage with the " + getItemDef(world->items[x + (y * world->width)].vid).name + "|0|";
							if (world->items[x + (y * world->width)].rm) {
								UseMagDialog = "\nadd_checkbox|checkbox_publicremote|`oUse magplants storage with the " + getItemDef(world->items[x + (y * world->width)].vid).name + "|1|";
							}
						}
					}
					Player::OnDialogRequest(peer, "set_default_color|\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_textbox|`oSelect the block you want this machine to automatically place for you, also you will need to select the second foreground block which will be used as identification for the first one, let's say we will select that we want to place Dirt automatically, and in the identification block we will set Wooden Platform, so that will cause our Dirt to placed above Wooden Platforms in your world!|left||" + PoolDialog + "|" + addthemdialog + "|" + PoolDialogs + "|" + MagplantsStoragesList + "|" + UseMagDialog +"|" + stopdialog + "\nend_dialog|autoplace|Close|OK|");
				}
				return;
			}

			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SUCKER) {
				if (world->isPublic) return; 
				auto squaresign = x + (y * world->width);
				auto currentworld = static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign);
				string Sucker = "";
				if (world->items[x + (y * world->width)].foreground == 5638) {
					Sucker = "magplant";
					static_cast<PlayerInfo*>(peer->data)->suckername = "magplant";
					static_cast<PlayerInfo*>(peer->data)->suckerid = 5638;
				}
				if (world->items[x + (y * world->width)].foreground == 6946) {
					Sucker = "gaiabeacon";
					static_cast<PlayerInfo*>(peer->data)->suckername = "gaiabeacon";
					static_cast<PlayerInfo*>(peer->data)->suckerid = 6946;
				}
				if (world->items[x + (y * world->width)].foreground == 6948) {
					Sucker = "unstabletesseract";
					static_cast<PlayerInfo*>(peer->data)->suckername = "unstabletesseract";
					static_cast<PlayerInfo*>(peer->data)->suckerid = 6948;
				}
				static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
				static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
				if (static_cast<PlayerInfo*>(peer->data)->rawName != world->owner && !isMod(peer)) {
					if (world->items[x + (y * world->width)].rm) {
						string label = "`6The machine is currently empty!";
						string RemoteDialog = "";
						if (world->items[x + (y * world->width)].mc >= 1) {
							RemoteDialog = "\nadd_textbox|`oUse the " + getItemDef(world->items[x + (y * world->width)].foreground).name + " Remote to build `2" + getItemDef(world->items[x + (y * world->width)].mid).name + " `odirectly from the " + getItemDef(world->items[x + (y * world->width)].foreground).name + "'s storage.|\nadd_button|getremote|`oGet Remote|";
							label = "`oThe machine contains " + to_string(world->items[x + (y * world->width)].mc) + " `2" + getItemDef(world->items[x + (y * world->width)].mid).name + ""; /*The message if something exists in item sucker*/
						}
						Player::OnDialogRequest(peer, "set_default_color|\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_spacer|small|\nadd_label_with_icon|small|`5" + getItemDef(world->items[x + (y * world->width)].mid).name + "|left|" + to_string(world->items[x + (y * world->width)].mid) + "|\nadd_textbox|" + label + "|" + RemoteDialog + "|\nend_dialog|magplantupdate|Close||");
					}
					else {
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "This magplant public mode is disabled!", 0, false);
					}
					return;
				}
				if (world->items[x + (y * world->width)].mid != 0) {
					string label = "`6The machine is currently empty!"; 
					string RemoteDialog = "";
					string publicremotecheck = "";
					string gemDialog = "";
					bool Farmable = false;
					if (world->items[x + (y * world->width)].mid == 7382 || world->items[x + (y * world->width)].mid == 4762 || world->items[x + (y * world->width)].mid == 10024 || world->items[x + (y * world->width)].mid == 9468 || world->items[x + (y * world->width)].mid == 9460 || world->items[x + (y * world->width)].mid == 10028 || world->items[x + (y * world->width)].mid == 340 || world->items[x + (y * world->width)].mid == 954 || world->items[x + (y * world->width)].mid == 5666) Farmable = true;
					if (Sucker == "magplant" && getItemDef(world->items[x + (y * world->width)].mid).blockType == BlockTypes::FOREGROUND || Sucker == "magplant" && Farmable || Sucker == "magplant" && getItemDef(world->items[x + (y * world->width)].mid).blockType == BlockTypes::BACKGROUND || Sucker == "magplant" && getItemDef(world->items[x + (y * world->width)].mid).blockType == BlockTypes::GROUND_BLOCK) {
						if (world->items[x + (y * world->width)].rm) {
							publicremotecheck = "\nadd_checkbox|checkbox_publicremote|`oAllow visitors to take remote|1|";
						}
						else {
							publicremotecheck = "\nadd_checkbox|checkbox_publicremote|`oAllow visitors to take remote|0|";
						}
						RemoteDialog = "\nadd_textbox|`oUse the " + getItemDef(world->items[x + (y * world->width)].foreground).name + " Remote to build `2" + getItemDef(world->items[x + (y * world->width)].mid).name + " `odirectly from the " + getItemDef(world->items[x + (y * world->width)].foreground).name + "'s storage.|\nadd_button|getremote|`oGet Remote|";
					}
					if (Sucker == "magplant") {
						if (world->items[x + (y * world->width)].mid == 112) {
							gemDialog = "\nadd_checkbox|checkbox_gemcollection|`oEnable gem collection|1|";
						} else {
							gemDialog = "\nadd_checkbox|checkbox_gemcollection|`oEnable gem collection|0|";
						}
					}
					if (world->items[x + (y * world->width)].mc >= 1) {
						label = "`oThe machine contains " + to_string(world->items[x + (y * world->width)].mc) + " `2" + getItemDef(world->items[x + (y * world->width)].mid).name + ""; /*The message if something exists in item sucker*/
						Player::OnDialogRequest(peer, "set_default_color|\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_spacer|small|\nadd_label_with_icon|small|`5" + getItemDef(world->items[x + (y * world->width)].mid).name + "|left|" + to_string(world->items[x + (y * world->width)].mid) + "|\nadd_textbox|" + label + "|\nadd_button|retrieveitem|`oRetrieve Items|" + RemoteDialog + "|" + publicremotecheck + "|\nend_dialog|magplantupdate|Close|`wUpdate|");
					}
					else {
						Player::OnDialogRequest(peer, "set_default_color|\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_spacer|small|\nadd_label_with_icon|small|`5" + getItemDef(world->items[x + (y * world->width)].mid).name + "|left|" + to_string(world->items[x + (y * world->width)].mid) + "|\nadd_textbox|" + label + "|\nadd_item_picker|magplantitem|Change Item|Choose an item to put in the " + getItemDef(world->items[x + (y * world->width)].foreground).name + "!|" + publicremotecheck + "|" + gemDialog + "\nend_dialog|magplantupdate|Close|`wUpdate|");
					}
				}
				else {
					if (Sucker == "magplant") Player::OnDialogRequest(peer, "set_default_color|\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_spacer|small|\nadd_textbox|`6The machine is empty.|\nadd_item_picker|magplantitem|Choose Item|Choose an item to put in the " + getItemDef(world->items[x + (y * world->width)].foreground).name + "!|\nadd_checkbox|checkbox_gemcollection|`oEnable gem collection|0|\nend_dialog|magplantcheck|Close|`wUpdate|");
					else Player::OnDialogRequest(peer, "set_default_color|\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_spacer|small|\nadd_textbox|`6The machine is empty.|\nadd_item_picker|magplantitem|Choose Item|Choose an item to put in the " + getItemDef(world->items[x + (y * world->width)].foreground).name + "!|\nend_dialog|magplant|Close||");
				}
				return;
			}
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::DOOR || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::PORTAL) {
				if (isWorldOwner(peer, world) || isWorldAdmin(peer, world) || isMod(peer) || world->owner == "" || !RestrictedArea(peer, world, x, y)) {
					static_cast<PlayerInfo*>(peer->data)->wrenchsession = x + (y * world->width);
					auto item = world->items[x + (y * world->width)];
					string DestWorldDialog = world->items[x + (y * world->width)].destWorld;
					if (world->items[x + (y * world->width)].destId != "") {
						DestWorldDialog += ":" + world->items[x + (y * world->width)].destId;
					}
					string IdDialog = "\nadd_text_input|door_id|ID|" + world->items[x + (y * world->width)].currId + "|11|\nadd_smalltext|Set a unique `2ID`` to target this door as a Destination from another!|left|";
					if (world->items[x + (y * world->width)].foreground == 762) {
						IdDialog = "\nadd_text_input|door_id|Password|" + world->items[x + (y * world->width)].password + "|23|";
					}
					Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(item.foreground) + "|\nadd_text_input|door_name|Label|" + world->items[x + (y * world->width)].label + "|100|\nadd_text_input|door_target|Destination|" + DestWorldDialog + "|24|\nadd_smalltext|Enter a Destination in this format: `2WORLDNAME:ID``|left|\nadd_smalltext|Leave `2WORLDNAME`` blank (:ID) to go to the door with `2ID`` in the `2Current World``.|left|" + IdDialog + "\nend_dialog|door_edit|Cancel|OK|");
				}
				return;
			}
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SIGN || world->items[x + (y * world->width)].foreground == 6214 || world->items[x + (y * world->width)].foreground == 1420) {
				if (world->owner == "" || isWorldOwner(peer, world) || isWorldAdmin(peer, world) || isMod(peer) || !RestrictedArea(peer, world, x, y)) {
					auto signtext = world->items[x + (y * world->width)].sign;
					static_cast<PlayerInfo*>(peer->data)->wrenchedBlockLocation = x + (y * world->width);
					if (world->items[x + (y * world->width)].foreground == 6214 || world->items[x + (y * world->width)].foreground == 1420) {
						Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_textbox|To dress, select a clothing item then use on the mannequin. To remove clothes, punch it or select which item to remove.<CR><CR>It will go into your backpack if you have room.|\nadd_textbox|<CR><CR>What would you like to write on its sign?``|left|\nadd_text_input|sign_textas||" + signtext + "|128|\nend_dialog|mannequin_edit|Cancel|OK|");
						return;
					}
					Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_textbox|What would you like to write on this sign?``|left|\nadd_text_input|signtextas||" + signtext + "|128|\nend_dialog|editsign|Cancel|OK|");
				}
				return;
			}
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::GATEWAY) {
				if (isWorldOwner(peer, world) || world->owner == "" || isWorldAdmin(peer, world) || isMod(peer) || !RestrictedArea(peer, world, x, y)) {
					if (world->owner == "") {
						Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_textbox|This object has additional properties to edit if in a locked area.|left|\nend_dialog|gateway_edit|Cancel|OK|");
						return;
					}
					static_cast<PlayerInfo*>(peer->data)->wrenchx = x;
					static_cast<PlayerInfo*>(peer->data)->wrenchy = y;
					if (!world->items[x + (y * world->width)].opened) {
						Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_checkbox|checkbox_public|Is open to public|0\nend_dialog|gateway_edit|Cancel|OK|");
					} else {
						Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_checkbox|checkbox_public|Is open to public|1\nend_dialog|gateway_edit|Cancel|OK|");				
					}
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 2978)
			{
				if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
				{
					static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
					static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
					if (world->owner != "" && !isWorldOwner(peer, world) && !isMod(peer))
					{
						SendBuyerVendDialog(peer, world);
						return;
					}
					SendVendDialog(peer, world);
				} else {
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Get closer!", 0, false);
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 4296) {
				if (world->owner == "" || isWorldOwner(peer, world) || isMod(peer)) {
					if (static_cast<PlayerInfo*>(peer->data)->SurgeryCooldown) {
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "I know it's just a robot, but the authorities don't even trust you operating on that with your malpractice issues.", 0, true);
						return;
					}
					if (static_cast<PlayerInfo*>(peer->data)->PerformingSurgery) end_surgery(peer, true);
					static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
					static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
					string surgerywarning = "";
					vector<int> Tools;
					SearchInventoryItem(peer, 1258, 20, iscontains);
					if (!iscontains) {
						auto KiekTuri = 0;
						for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++) {
							if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1258 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1) {
								KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
							}
						}
						if (KiekTuri != 0) Tools.push_back(1258);
					}
					else Tools.push_back(1258);
					SearchInventoryItem(peer, 1260, 20, iscontains);
					if (!iscontains)
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
					else Tools.push_back(1260);
					SearchInventoryItem(peer, 1262, 20, iscontains);
					if (!iscontains)
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
					else Tools.push_back(1262);
					SearchInventoryItem(peer, 1264, 20, iscontains);
					if (!iscontains)
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
					else Tools.push_back(1264);
					SearchInventoryItem(peer, 1266, 20, iscontains);
					if (!iscontains)
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
					else if (static_cast<PlayerInfo*>(peer->data)->UnlockedAntibiotic) Tools.push_back(1266);
					SearchInventoryItem(peer, 1268, 20, iscontains);
					if (!iscontains)
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
					else Tools.push_back(1268);
					SearchInventoryItem(peer, 1270, 20, iscontains);
					if (!iscontains)
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
					else Tools.push_back(1270);
					SearchInventoryItem(peer, 4308, 20, iscontains);
					if (!iscontains)
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
					else Tools.push_back(4308);
					SearchInventoryItem(peer, 4310, 20, iscontains);
					if (!iscontains)
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
					else Tools.push_back(4310);
					SearchInventoryItem(peer, 4312, 20, iscontains);
					if (!iscontains)
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
					else if (static_cast<PlayerInfo*>(peer->data)->PatientHeartStopped) Tools.push_back(4312);
					SearchInventoryItem(peer, 4314, 20, iscontains);
					if (!iscontains)
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
					else Tools.push_back(4314);
					SearchInventoryItem(peer, 4316, 20, iscontains);
					if (!iscontains)
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
					else Tools.push_back(4316);
					SearchInventoryItem(peer, 4318, 20, iscontains);
					if (!iscontains)
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

						if (KiekTuri != 0) Tools.push_back(4318);

					}
					else Tools.push_back(4318);

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

					vector<int> VisiTools{ 1258, 1260, 1262, 1264, 1266, 1268, 1270, 4308, 4310, 4312, 4314, 4316, 4318 };

					int TuriKartu = 1;
					bool Taip = false;
					for (int isd = 0; isd < VisiTools.size(); isd++)
					{
						bool Pirmas = false;
						SearchInventoryItem(peer, VisiTools[isd], 20, Pirmas);
						if (Pirmas)
						{
							continue;
						}
						bool Antras = false;
						SearchInventoryItem(peer, VisiTools[isd], 20, Antras);
						if (!Antras)
						{
							//cout << "keistas yra " + to_string(TuriKartu) << endl;
							int arrayd = VisiTools.size() - TuriKartu;
							//cout << "array yra " + to_string(arrayd) << endl;
							auto KiekTuri = 0;
							for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
							{
								if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == VisiTools[isd] && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
								{
									KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
								}
							}
							if (!Taip) surgerywarning += "You only have `4" + to_string(KiekTuri) + "`` " + getItemDef(VisiTools[isd]).name + ", ";
							else if (isd == arrayd)  surgerywarning += "and `4" + to_string(KiekTuri) + "`` " + getItemDef(VisiTools[isd]).name + " ";
							else surgerywarning += "`4" + to_string(KiekTuri) + "`` " + getItemDef(VisiTools[isd]).name + ", ";
							Taip = true;
						}
					}
					static_cast<PlayerInfo*>(peer->data)->RequestedSurgery = true;
					string LowSupplyWarning = "";
					if (surgerywarning != "") LowSupplyWarning = "\nadd_smalltext|`9Low Supply Warning: ``" + surgerywarning + "``|left|";
					Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`9Surg-E Anatomical Dummy``|left|4296|\nadd_spacer|small|\nadd_smalltext|Surgeon Skill: " + to_string(static_cast<PlayerInfo*>(peer->data)->SurgerySkill) + "|left|\nadd_textbox|Are you sure you want to perform surgery on this robot? Whether you succeed or fail, the robot will be destroyed in the process.|left|" + LowSupplyWarning + "\nend_dialog|surge|Cancel|Okay!|");
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 6016) {
				static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
				static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
				SendGScan(peer, world, x, y);
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 3898)
			{
				Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wTelephone`|left|3898|\n\nadd_spacer|small|\nadd_label|small|`oDial a number to call somebody in Growtopia. Phone numbers have 5 digits. Most numbers are not in service!|\nadd_spacer|small|\nadd_text_input|telephonenumber|Phone #||5|\nend_dialog|usetelephone|Hang Up|`wDial|\n");
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 658)
			{
				auto squaresign = x + (y * world->width);
				auto isdbox = std::experimental::filesystem::exists("bulletinboard/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (!isdbox)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the bulletin board.", 0, true);
				}
				else
				{
					if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isMod(peer))
					{
						GTDialog myLetterBox;
						myLetterBox.addLabelWithIcon("`wBulletin Board", 658, LABEL_BIG);
						myLetterBox.addSpacer(SPACER_SMALL);
						try
						{
							ifstream ifff("bulletinboard/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							json j;
							ifff >> j;
							ifff.close();
							if (j["inmail"] <= 0)
							{
								myLetterBox.addTextBox("`oThe Bulletin Board is empty.");
								myLetterBox.addSpacer(SPACER_SMALL);
							}
							else
							{
								for (int i = 0; i < 20; i++)
								{
									if (j["mails"][i]["growid"] != "")
									{
										if (j["hidenames"] == 0)
										{
											int apos = j["mails"][i]["aposition"];
											myLetterBox.addLabelWithIconButton("`w" + j["mails"][i]["growid"].get<string>() + ":`2 " + j["mails"][i]["text"].get<string>() + "", 660, "removeselectedbulletin_" + to_string(squaresign) + "_" + to_string(apos));
											//myLetterBox.addSpacer(SPACER_SMALL);
										}
										else
										{
											myLetterBox.addTextBox("`2" + j["mails"][i]["text"].get<string>());
											//myLetterBox.addSpacer(SPACER_SMALL);
										}
									}
								}
							}

							if (j["inmail"] < 90)
							{
								myLetterBox.addTextBox("`oAdd to conversation?");
								myLetterBox.addInputBox("addbulletinletterinput", "", "", 50);
								myLetterBox.addSpacer(SPACER_SMALL);
								myLetterBox.addButton("addbulletinletter_" + to_string(squaresign), "`2Add");
								myLetterBox.addSpacer(SPACER_SMALL);
							}

							myLetterBox.addLabelWithIcon("`wOwner Options", 242, LABEL_BIG);
							myLetterBox.addSpacer(SPACER_SMALL);
							if (j["hidenames"] == 1)
							{
								myLetterBox.addTextBox("`oUncheck `5Hide names `oto enable individual comment removal options.");
								myLetterBox.addSpacer(SPACER_SMALL);
							}
							else
							{
								myLetterBox.addTextBox("`oTo remove an individual comment, press the icon to the left of it.");
								myLetterBox.addSpacer(SPACER_SMALL);
							}
							if (j["inmail"] > 0)
							{
								myLetterBox.addButton("bulletinboardclear_" + to_string(squaresign), "`4Clear Board");
								myLetterBox.addSpacer(SPACER_SMALL);
							}
							if (j["publiccanadd"] == 1)
								myLetterBox.addCheckbox("publiccanaddbulletinboard", "`oPublic can add", CHECKBOX_SELECTED);
							else
								myLetterBox.addCheckbox("publiccanaddbulletinboard", "`oPublic can add", CHECKBOX_NOT_SELECTED);

							if (j["hidenames"] == 1)
								myLetterBox.addCheckbox("hidenamesbulletinboard", "`oHide names", CHECKBOX_SELECTED);
							else
								myLetterBox.addCheckbox("hidenamesbulletinboard", "`oHide names", CHECKBOX_NOT_SELECTED);
							myLetterBox.addSpacer(SPACER_SMALL);
							myLetterBox.addButton("bulletinletterok_" + to_string(squaresign), "`wOK");
							myLetterBox.addQuickExit();
							myLetterBox.endDialog("Close", "", "Cancel");
							Player::OnDialogRequest(peer, myLetterBox.finishDialog());
						}
						catch (std::exception&)
						{
							cout << "bulletin tile failed" << endl;
							return; /*tipo jeigu nera*/
						}
					}
					else
					{
						GTDialog myLetterBox;
						myLetterBox.addLabelWithIcon("`wBulletin Board", 658, LABEL_BIG);
						myLetterBox.addSpacer(SPACER_SMALL);
						try
						{
							ifstream ifff("bulletinboard/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							json j;
							ifff >> j;
							ifff.close();

							if (j["inmail"] > 0)
							{
								for (int i = 0; i < 20; i++)
								{
									if (j["mails"][i]["growid"] != "")
									{
										if (j["hidenames"] == 0)
										{
											myLetterBox.addLabelWithIcon("`w" + j["mails"][i]["growid"].get<string>() + ":`2 " + j["mails"][i]["text"].get<string>() + "", 660, LABEL_SMALL);
											myLetterBox.addSpacer(SPACER_SMALL);
										}
										else
										{
											myLetterBox.addTextBox("`2" + j["mails"][i]["text"].get<string>());
											myLetterBox.addSpacer(SPACER_SMALL);
										}
									}
								}
							}

							if (j["publiccanadd"] == 1 && j["inmail"] < 90)
							{
								myLetterBox.addSpacer(SPACER_SMALL);
								myLetterBox.addTextBox("`oAdd to conversation?");
								myLetterBox.addInputBox("addbulletinletterinput", "", "", 50);
								myLetterBox.addSpacer(SPACER_SMALL);
								myLetterBox.addButton("addbulletinletter_" + to_string(squaresign), "`2Add");
								myLetterBox.addSpacer(SPACER_SMALL);
							}

							myLetterBox.addQuickExit();
							myLetterBox.endDialog("Close", "", "Cancel");
							Player::OnDialogRequest(peer, myLetterBox.finishDialog());
						}
						catch (std::exception&)
						{
							cout << "bulletin tile failed" << endl;
							return; /*tipo jeigu nera*/
						}
					}
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 656)
			{
				auto squaresign = x + (y * world->width);
				auto isdbox = std::experimental::filesystem::exists("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (!isdbox)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the mailbox.", 0, true);
				}
				else
				{
					if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isMod(peer))
					{
						GTDialog myLetterBox;
						myLetterBox.addLabelWithIcon("`wMail Box", 656, LABEL_BIG);
						ifstream ifff("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();
						if (j["inmail"] <= 0)
						{
							myLetterBox.addTextBox("`oThe mailbox is currently empty.");
						}
						else
						{
							int donated = j["inmail"];

							myLetterBox.addTextBox("`oYou have `w" + to_string(donated) + " `oletters:");
							myLetterBox.addSpacer(SPACER_SMALL);
							for (int i = 0; i < 20; i++)
							{
								if (j["mails"][i]["growid"] != "")
								{
									myLetterBox.addLabelWithIcon("`5\"" + j["mails"][i]["text"].get<string>() + "\" - `w" + j["mails"][i]["growid"].get<string>() + "", 660, LABEL_SMALL);
									myLetterBox.addSpacer(SPACER_SMALL);
								}
							}
							myLetterBox.addSpacer(SPACER_SMALL);
							myLetterBox.addButton("mailempty_" + to_string(squaresign), "`4Empty mailbox");
						}
						myLetterBox.addTextBox("`oWrite a letter to yourself?");
						myLetterBox.addInputBox("addletterinput_" + to_string(squaresign), "", "", 50);
						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addButton("addletter", "`2Send Letter");
						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addQuickExit();
						myLetterBox.endDialog("Close", "", "Cancel");
						Player::OnDialogRequest(peer, myLetterBox.finishDialog());
					}
					else
					{
						GTDialog myLetterBox;
						myLetterBox.addLabelWithIcon("`wMail Box", 656, LABEL_BIG);
						ifstream ifff("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();

						myLetterBox.addTextBox("`$Want to leave a message for the owner?");
						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addInputBox("addletterinput_" + to_string(squaresign), "", "", 50);
						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addButton("addletter", "`2Send Letter");

						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addQuickExit();
						myLetterBox.endDialog("Close", "", "Cancel");
						Player::OnDialogRequest(peer, myLetterBox.finishDialog());
					}
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 6286)
			{
				auto squaresign = x + (y * world->width);
				auto isdbox = std::experimental::filesystem::exists("storageboxlvl1/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (!isdbox)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the box.", 0, true);
				}
				else
				{
					if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isMod(peer))
					{
						GTDialog myBox;
						myBox.addLabelWithIcon("`wStorage Box Xtreme - Level 1", 6286, LABEL_BIG);
						ifstream ifff("storageboxlvl1/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();

						int stored = j["instorage"];

						if (stored > 0)
						{
							myBox.addSpacer(SPACER_SMALL);
						}

						int count = 0;
						int id = 0;
						int aposition = 0;
						for (int i = 0; i < 20; i++)
						{
							if (j["storage"][i]["itemid"] != 0)
							{
								count = j["storage"][i]["itemcount"];
								id = j["storage"][i]["itemid"];
								aposition = j["storage"][i]["aposition"];

								if (i % 6 == 0 && i != 0)
								{
									myBox.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "boxlvl1DepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), true);
								}
								else
								{
									myBox.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "boxlvl1DepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), false);
								}
							}
						}

						if (stored > 0)
						{
							myBox.addNewLineAfterFrame();
						}

						myBox.addTextBox("`w" + to_string(stored) + "/20 `$items stored.");
						myBox.addSpacer(SPACER_SMALL);
						myBox.addPicker("boxlvl1deposit_" + to_string(squaresign), "Deposit item", "Select an item");
						myBox.addSpacer(SPACER_SMALL);
						myBox.addQuickExit();
						myBox.endDialog("Close", "", "Exit");
						Player::OnDialogRequest(peer, myBox.finishDialog());
					}
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 6288)
			{
				auto squaresign = x + (y * world->width);
				auto isdbox = std::experimental::filesystem::exists("storageboxlvl2/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (!isdbox)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the box.", 0, true);
				}
				else
				{
					if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isMod(peer))
					{
						GTDialog myBox;
						myBox.addLabelWithIcon("`wStorage Box Xtreme - Level 2", 6288, LABEL_BIG);
						ifstream ifff("storageboxlvl2/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();

						int stored = j["instorage"];

						if (stored > 0)
						{
							myBox.addSpacer(SPACER_SMALL);
						}

						int count = 0;
						int id = 0;
						int aposition = 0;
						for (int i = 0; i < 40; i++)
						{
							if (j["storage"][i]["itemid"] != 0)
							{
								count = j["storage"][i]["itemcount"];
								id = j["storage"][i]["itemid"];
								aposition = j["storage"][i]["aposition"];

								if (i % 6 == 0 && i != 0)
								{
									myBox.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "boxlvl2DepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), true);
								}
								else
								{
									myBox.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "boxlvl2DepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), false);
								}
							}
						}

						if (stored > 0)
						{
							myBox.addNewLineAfterFrame();
						}

						myBox.addTextBox("`w" + to_string(stored) + "/40 `$items stored.");
						myBox.addSpacer(SPACER_SMALL);
						myBox.addPicker("boxlvl2deposit_" + to_string(squaresign), "Deposit item", "Select an item");
						myBox.addSpacer(SPACER_SMALL);
						myBox.addQuickExit();
						myBox.endDialog("Close", "", "Exit");
						Player::OnDialogRequest(peer, myBox.finishDialog());
					}
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 6290)
			{
				auto squaresign = x + (y * world->width);
				auto isdbox = std::experimental::filesystem::exists("storageboxlvl3/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (!isdbox)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the box.", 0, true);
				}
				else
				{
					if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isMod(peer))
					{
						GTDialog myBox;
						myBox.addLabelWithIcon("`wStorage Box Xtreme - Level 3", 6290, LABEL_BIG);
						ifstream ifff("storageboxlvl3/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();

						int stored = j["instorage"];

						if (stored > 0)
						{
							myBox.addSpacer(SPACER_SMALL);
						}

						int count = 0;
						int id = 0;
						int aposition = 0;
						for (int i = 0; i < 90; i++)
						{
							if (j["storage"][i]["itemid"] != 0)
							{
								count = j["storage"][i]["itemcount"];
								id = j["storage"][i]["itemid"];
								aposition = j["storage"][i]["aposition"];

								if (i % 6 == 0 && i != 0)
								{
									myBox.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "boxlvl3DepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), true);
								}
								else
								{
									myBox.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "boxlvl3DepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), false);
								}
							}
						}

						if (stored > 0)
						{
							myBox.addNewLineAfterFrame();
						}

						myBox.addTextBox("`w" + to_string(stored) + "/90 `$items stored.");
						myBox.addSpacer(SPACER_SMALL);
						myBox.addPicker("boxlvl3deposit_" + to_string(squaresign), "Deposit item", "Select an item");
						myBox.addSpacer(SPACER_SMALL);
						myBox.addQuickExit();
						myBox.endDialog("Close", "", "Exit");
						Player::OnDialogRequest(peer, myBox.finishDialog());
					}
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 8878)
			{
				auto squaresign = x + (y * world->width);
				auto isdbox = std::experimental::filesystem::exists("safevault/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (!isdbox)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the safe.", 0, true);
				}
				else
				{
					if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isMod(peer))
					{
						ifstream ifff("safevault/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();

						int stored = j["insafe"];
						string password = j["password"];

						if (password != "")
						{
							GTDialog mySafeConfirm;
							mySafeConfirm.addLabelWithIcon("`wSafe Vault", 8878, LABEL_BIG);
							mySafeConfirm.addTextBox("Please enter your password to access the Save Vault.");
							mySafeConfirm.addInputBox("safeconfirmpassInput_" + to_string(squaresign), "", "", 18);
							mySafeConfirm.addButton("safe_confirmpass", "Enter Password");
							mySafeConfirm.addButton("saferecoverPasswordInConfirm_" + to_string(squaresign), "Recover Password");
							mySafeConfirm.addSpacer(SPACER_SMALL);
							mySafeConfirm.addQuickExit();
							mySafeConfirm.endDialog("Close", "", "Exit");
							Player::OnDialogRequest(peer, mySafeConfirm.finishDialog());
							return;
						}

						GTDialog mySafe;
						mySafe.addLabelWithIcon("`wSafe Vault", 8878, LABEL_BIG);

						if (stored > 0)
						{
							mySafe.addSpacer(SPACER_SMALL);
						}

						int count = 0;
						int id = 0;
						int aposition = 0;
						for (int i = 0; i < 20; i++)
						{
							if (j["safe"][i]["itemid"] != 0)
							{
								count = j["safe"][i]["itemcount"];
								id = j["safe"][i]["itemid"];
								aposition = j["safe"][i]["aposition"];

								if (i % 3 == 0 && i != 0)
								{
									mySafe.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "safeBoxDepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), true);
								}
								else
								{
									mySafe.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "safeBoxDepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), false);
								}
							}
						}

						if (stored > 0)
						{
							mySafe.addNewLineAfterFrame();
						}

						mySafe.addTextBox("`w" + to_string(stored) + "/20 `$items stored.");
						mySafe.addSpacer(SPACER_SMALL);
						mySafe.addPicker("safedeposit_" + to_string(squaresign), "Deposit item", "Select an item");
						if (j["password"] == "")
						{
							mySafe.addTextBox("`$This Safe Vault is not `4password protected`$!");
						}
						else
						{
							mySafe.addTextBox("`$This Safe Vault is `2password protected`$!");
						}
						mySafe.addSpacer(SPACER_SMALL);
						mySafe.addTextBox("`$Change your password.");
						mySafe.addButton("safeupdatepass_" + to_string(squaresign), "Update Password");

						mySafe.addSpacer(SPACER_SMALL);
						mySafe.addQuickExit();
						mySafe.endDialog("Close", "", "Exit");
						Player::OnDialogRequest(peer, mySafe.finishDialog());
					}
				}
				return;
			}
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::DONATION)
			{
				auto squaresign = x + (y * world->width);
				auto isdbox = std::experimental::filesystem::exists("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (!isdbox)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the donation box.", 0, true);
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
					static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
					static_cast<PlayerInfo*>(peer->data)->lastPunchForeground = world->items[x + (y * world->width)].foreground;
					static_cast<PlayerInfo*>(peer->data)->lastPunchBackground = world->items[x + (y * world->width)].background;
					if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isMod(peer))
					{
						GTDialog myDbox;
						myDbox.addLabelWithIcon("`wDonation Box", world->items[x + (y * world->width)].foreground, LABEL_BIG);
						ifstream ifff("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();
						if (j["donated"] <= 0)
						{
							myDbox.addTextBox("`$The box is currently empty.");
						}
						else
						{
							int donated = j["donated"];
							int count = 0;
							myDbox.addTextBox("`oYou have `w" + to_string(donated) + " `ogifts waiting:");
							myDbox.addSpacer(SPACER_SMALL);
							for (int i = 0; i < 20; i++)
							{
								if (j["donatedItems"][i]["itemid"] != 0)
								{
									count = j["donatedItems"][i]["itemcount"];
									myDbox.addLabelWithIcon("`o" + getItemDef(j["donatedItems"][i]["itemid"]).name + " (`w" + to_string(count) + "`o) from `w" + j["donatedItems"][i]["sentBy"].get<string>() + "`#- '" + j["donatedItems"][i]["note"].get<string>() + "'", j["donatedItems"][i]["itemid"], LABEL_SMALL);
									myDbox.addSpacer(SPACER_SMALL);
								}
							}
							myDbox.addSpacer(SPACER_SMALL);
							myDbox.addButton("retrieveGifts_" + to_string(squaresign), "`4Retrieve Gifts");
						}
						myDbox.addSpacer(SPACER_SMALL);
						myDbox.addPicker("addDonationItem_" + to_string(squaresign), "`wGive Gift `o(Min rarity: `52`o)", "Select an item");
						myDbox.addSpacer(SPACER_SMALL);
						myDbox.addQuickExit();
						myDbox.endDialog("Close", "", "Cancel");
						Player::OnDialogRequest(peer, myDbox.finishDialog());
					}
					else
					{
						GTDialog myDbox;
						myDbox.addLabelWithIcon("`wDonation Box", world->items[x + (y * world->width)].foreground, LABEL_BIG);
						ifstream ifff("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();

						int donated = j["donated"];

						myDbox.addTextBox("`$You see `w" + to_string(donated) + "`$ gifts in the box!");
						myDbox.addTextBox("`$Want to leave a gift for the owner?");
						myDbox.addSpacer(SPACER_SMALL);

						myDbox.addPicker("addDonationItem_" + to_string(squaresign), "`wGive Gift `o(Min rarity: `52`o)", "Select an item");

						myDbox.addSpacer(SPACER_SMALL);
						myDbox.addQuickExit();
						myDbox.endDialog("Close", "", "Cancel");
						Player::OnDialogRequest(peer, myDbox.finishDialog());
					}
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 1006)
			{
				auto squaresign = x + (y * world->width);
				auto isdbox = std::experimental::filesystem::exists("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (!isdbox)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the mailbox.", 0, true);
				}
				else
				{
					if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isMod(peer))
					{
						GTDialog myLetterBox;
						myLetterBox.addLabelWithIcon("`wBlue Mail Box", 1006, LABEL_BIG);
						ifstream ifff("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();
						if (j["inmail"] <= 0)
						{
							myLetterBox.addTextBox("`oThe mailbox is currently empty.");
						}
						else
						{
							int donated = j["inmail"];

							myLetterBox.addTextBox("`oYou have `w" + to_string(donated) + " `oletters:");
							myLetterBox.addSpacer(SPACER_SMALL);
							for (int i = 0; i < 20; i++)
							{
								if (j["mails"][i]["growid"] != "")
								{
									myLetterBox.addLabelWithIcon("`5\"" + j["mails"][i]["text"].get<string>() + "\" - `w" + j["mails"][i]["growid"].get<string>() + "", 660, LABEL_SMALL);
									myLetterBox.addSpacer(SPACER_SMALL);
								}
							}
							myLetterBox.addSpacer(SPACER_SMALL);
							myLetterBox.addButton("bluemailempty_" + to_string(squaresign), "`4Empty mailbox");
						}
						myLetterBox.addTextBox("`oWrite a letter to yourself?");
						myLetterBox.addInputBox("addblueletterinput_" + to_string(squaresign), "", "", 50);
						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addButton("addblueletter", "`2Send Letter");
						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addQuickExit();
						myLetterBox.endDialog("Close", "", "Cancel");
						Player::OnDialogRequest(peer, myLetterBox.finishDialog());
					}
					else
					{
						GTDialog myLetterBox;
						myLetterBox.addLabelWithIcon("`wMail Box", 1006, LABEL_BIG);
						ifstream ifff("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();

						myLetterBox.addTextBox("`$Want to leave a message for the owner?");
						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addInputBox("addblueletterinput_" + to_string(squaresign), "", "", 50);
						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addButton("addblueletter", "`2Send Letter");

						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addQuickExit();
						myLetterBox.endDialog("Close", "", "Cancel");
						Player::OnDialogRequest(peer, myLetterBox.finishDialog());
					}
				}
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 2946)
			{
				if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || world->owner == "" || world->isPublic || isMod(peer))
				{
					int itemid = world->items[x + (y * world->width)].foreground;
					int itembg = world->items[x + (y * world->width)].background;
					static_cast<PlayerInfo*>(peer->data)->displayfg = itemid;
					static_cast<PlayerInfo*>(peer->data)->displaybg = itembg;
					static_cast<PlayerInfo*>(peer->data)->displaypunchx = data.punchX;
					static_cast<PlayerInfo*>(peer->data)->displaypunchy = data.punchY;
					if (world->items[x + (y * world->width)].intdata != 0 && static_cast<PlayerInfo*>(peer->data)->rawName == world->owner)
					{
						Player::OnDialogRequest(peer, "add_label_with_icon|big|`wDisplay Block|left|" + to_string(itemid) + "|\nadd_spacer|small||\nadd_label|small|`oA " + getItemDef(world->items[x + (y * world->width)].intdata).name + " is on display here.|\nadd_button|pickupdisplayitem|Pick it up|0|0|\nadd_quick_exit|\n");
					}
					else if (world->items[x + (y * world->width)].intdata != 0 && (isMod(peer)))
					{
						Player::OnDialogRequest(peer, "add_label_with_icon|big|`wDisplay Block|left|" + to_string(itemid) + "|\nadd_spacer|small||\nadd_label|small|`oA " + getItemDef(world->items[x + (y * world->width)].intdata).name + " is on display here.|\nadd_button|chc000|Okay|0|0|\nadd_quick_exit|\n");
					}
					else if (world->isPublic && world->items[x + (y * world->width)].intdata != 0 && static_cast<PlayerInfo*>(peer->data)->rawName != world->owner)
					{
						Player::OnDialogRequest(peer, "add_label_with_icon|big|`wDisplay Block|left|" + to_string(itemid) + "|\nadd_spacer|small||\nadd_label|small|`oA " + getItemDef(world->items[x + (y * world->width)].intdata).name + " is on display here.|\nadd_button|chc000|Okay|0|0|\nadd_quick_exit|\n");
					}
					else if (world->owner == "" && world->items[x + (y * world->width)].intdata != 0)
					{
						Player::OnDialogRequest(peer, "add_label_with_icon|big|`wDisplay Block|left|" + to_string(itemid) + "|\nadd_spacer|small||\nadd_label|small|`oA " + getItemDef(world->items[x + (y * world->width)].intdata).name + " is on display here.|\nadd_button|pickupdisplayitem|Pick it up|0|0|\nadd_quick_exit|\n");
					}
					else
					{
						Player::OnDialogRequest(peer, "add_label_with_icon|big|`wDisplay Block|left|" + to_string(itemid) + "|\nadd_spacer|small||\nadd_label|small|`oThe Display Block is empty. Use an item on it to display the item!|\nend_dialog||Close||\n");
					}
					return;
				}
				else
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That area is owned by " + world->owner + "", 0, true);
					return;
				}
				return;
			}
			return;
		}
	case 6336:
		{
			SendGrowpedia(peer);
			return;
		}
	case 764:
		{
			if (static_cast<PlayerInfo*>(peer->data)->isZombie == true) return;
			if (static_cast<PlayerInfo*>(peer->data)->canWalkInBlocks == true)
			{
				static_cast<PlayerInfo*>(peer->data)->canWalkInBlocks = false;
				static_cast<PlayerInfo*>(peer->data)->skinColor = 0x8295C3FF;
				send_state(peer);
			}
			sendSound(peer, "skel.wav");
			static_cast<PlayerInfo*>(peer->data)->isZombie = true;
			send_state(peer);
			RemoveInventoryItem(764, 1, peer, true);
			playerconfig(peer, 1150, 130, 0x14);
			return;
		}
	case 782:
		{
			if (static_cast<PlayerInfo*>(peer->data)->isZombie == false) return;
			static_cast<PlayerInfo*>(peer->data)->isZombie = false;
			send_state(peer);
			RemoveInventoryItem(782, 1, peer, true);
			playerconfig(peer, 1150, 300, 0x14);
			return;
		}
	case 6286: case 6288: case 6290: case 6214: case 1420: case 656: case 658: case 1006: case 8878: case 1240: case 762: case 6016:
		{
			if (world->owner == "" || isWorldOwner(peer, world) || isMod(peer) || isWorldAdmin(peer, world))
			{
				//if (world->name == "CON" || world->name == "PRN" || world->name == "AUX" || world->name == "NUL" || world->name == "COM1" || world->name == "COM2" || world->name == "COM3" || world->name == "COM4" || world->name == "COM5" || world->name == "COM6" || world->name == "COM7" || world->name == "COM8" || world->name == "COM9" || world->name == "LPT1" || world->name == "LPT2" || world->name == "LPT3" || world->name == "LPT4" || world->name == "LPT5" || world->name == "LPT6" || world->name == "LPT7" || world->name == "LPT8" || world->name == "LPT9") return;
				if (tile == 6016) {
					if (world->owner == "") {
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "This item can only be used in World-Locked worlds!", 0, true);
						return;
					}
				}
				if (tile == 762) {
					world->items[x + (y * world->width)].label = getItemDef(tile).name;
					isDoor = true;
				}
				if (tile == 6286 || tile == 6288 || tile == 6290)
				{
					auto Space = 20;
					string Directory = "storageboxlvl1";
					if (tile == 6288)
					{
						Space = 40; 
						Directory = "storageboxlvl2";
					}
					else if (tile == 6290)
					{
						Space = 90;
						Directory = "storageboxlvl3";
					}
					namespace fs = std::experimental::filesystem;
					if (!fs::is_directory(Directory + "/" + world->name) || !fs::exists(Directory + "/" + world->name))
					{
						fs::create_directory(Directory + "/" + world->name);
					}
					ofstream of(Directory + "/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					json j;
					j["instorage"] = 0;
					auto jArray = json::array();
					json jmid;
					for (auto i = 1; i <= Space; i++)
					{
						jmid["aposition"] = i;
						jmid["itemid"] = 0;
						jmid["placedby"] = static_cast<PlayerInfo*>(peer->data)->rawName;
						jmid["itemcount"] = 0;
						jArray.push_back(jmid);
					}
					j["storage"] = jArray;
					of << j << std::endl;
					of.close();
				}
				if (tile == 1240) {
					isHeartMonitor = true;
				}
				if (tile == 8878)
				{
					namespace fs = std::experimental::filesystem;
					if (!fs::is_directory("safevault/" + world->name) || !fs::exists("safevault/" + world->name))
					{
						fs::create_directory("safevault/" + world->name);
					}
					ofstream of("safevault/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					json j;
					j["insafe"] = 0;
					j["password"] = "";
					j["recovery"] = "";
					json jArray = json::array();
					json jmid;
					for (int i = 1; i <= 20; i++)
					{
						jmid["aposition"] = i;
						jmid["itemid"] = 0;
						jmid["placedby"] = static_cast<PlayerInfo*>(peer->data)->rawName;
						jmid["itemcount"] = 0;
						jArray.push_back(jmid);
					}
					j["safe"] = jArray;
					of << j << std::endl;
					of.close();
				}
				if (tile == 656)
				{
					namespace fs = std::experimental::filesystem;
					if (!fs::is_directory("mailbox/" + world->name) || !fs::exists("mailbox/" + world->name))
					{
						fs::create_directory("mailbox/" + world->name);
					}
					ofstream of("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					json j;
					j["x"] = x;
					j["y"] = y;
					j["inmail"] = 0;
					json jArray = json::array();
					json jmid;
					for (int i = 1; i <= 90; i++)
					{
						jmid["aposition"] = i;
						jmid["growid"] = "";
						jmid["text"] = "";
						jArray.push_back(jmid);
					}
					j["mails"] = jArray;
					of << j << std::endl;
					of.close();
				}
				if (tile == 658)
				{
					namespace fs = std::experimental::filesystem;
					if (!fs::is_directory("bulletinboard/" + world->name) || !fs::exists("bulletinboard/" + world->name))
					{
						fs::create_directory("bulletinboard/" + world->name);
					}
					ofstream of("bulletinboard/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					json j;
					j["inmail"] = 0;
					j["publiccanadd"] = 1;
					j["hidenames"] = 0;
					json jArray = json::array();
					json jmid;
					for (int i = 1; i <= 90; i++)
					{
						jmid["aposition"] = i;
						jmid["growid"] = "";
						jmid["text"] = "";
						jArray.push_back(jmid);
					}
					j["mails"] = jArray;
					of << j << std::endl;
					of.close();
				}
				if (tile == 1006)
				{
					namespace fs = std::experimental::filesystem;
					if (!fs::is_directory("bluemailbox/" + world->name) || !fs::exists("bluemailbox/" + world->name))
					{
						fs::create_directory("bluemailbox/" + world->name);
					}
					ofstream of("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					json j;
					j["x"] = x;
					j["y"] = y;
					j["inmail"] = 0;
					json jArray = json::array();
					json jmid;
					for (int i = 1; i <= 90; i++)
					{
						jmid["aposition"] = i;
						jmid["growid"] = "";
						jmid["text"] = "";
						jArray.push_back(jmid);
					}
					j["mails"] = jArray;

					of << j << std::endl;
					of.close();
				}
				if (tile == 6214 || tile == 1420)
				{
					isMannequin = true;
					namespace fs = std::experimental::filesystem;
					if (!fs::is_directory("mannequin/" + world->name) || !fs::exists("mannequin/" + world->name))
					{
						fs::create_directory("mannequin/" + world->name);
					}
					json j;
					auto seedexist = std::experimental::filesystem::exists("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					if (!seedexist)
					{
						j["clothHead"] = "0";
						j["clothHair"] = "0";
						j["clothMask"] = "0";
						j["clothNeck"] = "0";
						j["clothBack"] = "0";
						j["clothShirt"] = "0";
						j["clothPants"] = "0";
						j["clothFeet"] = "0";
						j["clothHand"] = "0";
						ofstream of("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						of << j;
						of.close();
					}
				}
				break;
			}
		}
	case 2978: /*vend*/
		{
			if (world->owner == "" || isWorldOwner(peer, world) || isMod(peer) || isWorldAdmin(peer, world)) {
				VendUpdate = true;
				world->items[squaresign].vcount = 0;
				world->items[squaresign].vprice = 0;
				world->items[squaresign].vid = 0;
				world->items[squaresign].vdraw = 0;
				world->items[squaresign].opened = true;
				world->items[squaresign].rm = false;
				break;
			}
			else return;
		}
	case 2410: case 4426: case 1212: case 1234: case 3110: case 1976: case 2000: case 3122: case 10386: case 5664: case 5662: case 9644: case 10414: case 10416:
		{

			if (tile == 9644)
			{
				SearchInventoryItem(peer, 9644, 1, iscontains);
				if (!iscontains) return;
				else
				{
					if (CheckItemMaxed(peer, 1258, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1258).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 1260, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1260).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 1262, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1262).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 1264, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1264).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 1266, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1266).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 1268, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1268).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 1270, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1270).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 4308, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4308).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 4310, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4310).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 4312, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4312).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 4314, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4314).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 4316, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4316).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 4318, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4318).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}

					if (CheckItemMaxed(peer, 4296, 5))
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4296).name + " wouldnt fit into my inventory!", 0, true);
						return;
					}


					RemoveInventoryItem(9644, 1, peer, true);
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou received 5 Surgical Sponge, 5 Surgical Scalpel, 5 Surgical Anesthetic, 5 Surgical Antiseptic, 5 Surgical Antibiotics, 5 Surgical Splint, 1 Surgical Stitches, 5 Surgical Pins, 5 Surgical Transfusion, 5 Surgical Defibrillator, 5 Surgical Clamp, 5 Surgical Ultrasound, 5 Surgical Lab Kit and a 1 Surg-E", 0, true);
					Player::OnConsoleMessage(peer, "`oYou received 5 Surgical Sponge, 5 Surgical Scalpel, 5 Surgical Anesthetic, 5 Surgical Antiseptic, 5 Surgical Antibiotics, 5 Surgical Splint, 1 Surgical Stitches, 5 Surgical Pins, 5 Surgical Transfusion, 5 Surgical Defibrillator, 5 Surgical Clamp, 5 Surgical Ultrasound, 5 Surgical Lab Kit and a 1 Surg-E");
					bool success = true;
					SaveItemMoreTimes(1258, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(1260, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(1262, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(1264, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(1266, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(1268, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(1270, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(4308, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(4310, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(4312, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(4314, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(4316, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(4318, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
					SaveItemMoreTimes(4296, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");

					ENetPeer* currentPeer;
					for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
					{
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, currentPeer))
						{
							SendTradeEffect(currentPeer, 1258, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 1260, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 1262, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 1264, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 1266, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 1268, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 1270, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 4308, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 4310, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 4312, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 4314, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 4316, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 4318, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
							SendTradeEffect(currentPeer, 4296, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);

						}
					}


				}
			}

			if (tile == 5662)
			{
				SearchInventoryItem(peer, 5662, 200, iscontains);
				if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6You will need more dust than that!", 0, true);
				else
				{
					RemoveInventoryItem(5662, 200, peer, true);
					bool success = true;
					SaveItemMoreTimes(5642, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5The dust stirs and begins to swirl! Cupid appears before you.", 0, true);
					static_cast<PlayerInfo*>(peer->data)->cloth_hand = 5642;
					sendClothes(peer);
				}
			}

			if (tile == 5664)
			{
				SearchInventoryItem(peer, 5664, 1, iscontains);
				if (!iscontains) return;
				else
				{
					RemoveInventoryItem(5664, 1, peer, true);
					bool success = true;
					SaveItemMoreTimes(5662, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					//Player::OnConsoleMessage(peer, "`oYou received `21 " + getItemDef(itemid).name + " `ofrom the Gift of Growganoth.");
				}
			}
			if (tile == 10386)
			{
				SearchInventoryItem(peer, 10386, 1, iscontains);
				if (!iscontains) return;
				else
				{
					RemoveInventoryItem(10386, 1, peer, true);
					int itemuMas[59] = { 1216, 1218, 1992, 1982, 1994, 1972, 1980, 1988, 1984, 3116, 3102, 3106, 3110, 4160, 4162, 4164, 4154, 4158, 5224, 5222, 5232, 5240, 5248, 5238, 5256, 7116, 7108, 7110, 7128, 7112, 7114, 7130, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 1230, 1194, 1192, 1226, 1196, 1236, 1182, 1184, 1186, 1188, 1170, 10198, 10196, 10202, 10204, 10326, 10324, 10322 };
					auto randIndex = rand() % 59;
					int itemid = itemuMas[randIndex];
					bool success = true;
					SaveItemMoreTimes(itemid, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnConsoleMessage(peer, "`oYou received `21 " + getItemDef(itemid).name + " `ofrom the Gift of Growganoth.");
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou received `21 " + getItemDef(itemid).name + " `wfrom the Gift of Growganoth.", 0, true);
				}
			}

			if (tile == 10414) {
				SearchInventoryItem(peer, 10414, 75, iscontains);
				if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6There's just not enough earth pigments here to make anything. Get more!", 0, true);
				else {
					RemoveInventoryItem(10414, 75, peer, true);
					bool success = true;
					SaveItemMoreTimes(10420, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The fragments forms into a earth wings!", 0, true);
					static_cast<PlayerInfo*>(peer->data)->cloth_back = 10420;
					Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
					sendClothes(peer);
				}
			}

			if (tile == 10416) {
				SearchInventoryItem(peer, 10416, 75, iscontains);
				if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6There's just not enough lava pigments here to make anything. Get more!", 0, true);
				else {
					RemoveInventoryItem(10416, 75, peer, true);
					bool success = true;
					SaveItemMoreTimes(10418, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The fragments forms into a magma wings!", 0, true);
					static_cast<PlayerInfo*>(peer->data)->cloth_back = 10418;
					Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
					sendClothes(peer);
				}
			}

			if (tile == 3122)
			{
				SearchInventoryItem(peer, 3122, 16, iscontains);
				if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6There's just not enough fragments here to make anything. Get more!", 0, true);
				else
				{
					RemoveInventoryItem(3122, 16, peer, true);
					bool success = true;
					SaveItemMoreTimes(3120, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The fragments forms into a teeny devil wings!", 0, true);
					static_cast<PlayerInfo*>(peer->data)->cloth_back = 3120;
					Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
					sendClothes(peer);
				}
			}
			if (tile == 2000)
			{
				SearchInventoryItem(peer, 2000, 20, iscontains);
				if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6There's just not enough bones here to make anything. Get more!", 0, true);
				else
				{
					RemoveInventoryItem(2000, 20, peer, true);
					bool success = true;
					SaveItemMoreTimes(1998, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The bones forms into a skeletal dragon claw!", 0, true);
					static_cast<PlayerInfo*>(peer->data)->cloth_hand = 1998;
					Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
					sendClothes(peer);
				}
			}
			if (tile == 1976)
			{
				SearchInventoryItem(peer, 1976, 10, iscontains);
				if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6There's just not enough skulls here to make anything. Get more!", 0, true);
				else
				{
					RemoveInventoryItem(1976, 10, peer, true);
					bool success = true;
					SaveItemMoreTimes(1974, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The skulls forms into a nightmare magnifying glass!", 0, true);
					static_cast<PlayerInfo*>(peer->data)->cloth_hand = 1974;
					Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
					sendClothes(peer);
				}
			}
			if (tile == 1212)
			{
				SearchInventoryItem(peer, 1212, 25, iscontains);
				if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6There's just not enough fur here to make anything. Get more!", 0, true);
				else
				{
					RemoveInventoryItem(1212, 25, peer, true);
					bool success = true;
					SaveItemMoreTimes(1190, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The fur forms into a cuddly black cat!", 0, true);
					static_cast<PlayerInfo*>(peer->data)->cloth_hand = 1190;
					Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
					sendClothes(peer);
				}
			}
			if (tile == 1234)
			{
				SearchInventoryItem(peer, 1234, 4, iscontains);
				if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6There's just not enough shards here to make anything. Get more!", 0, true);
				else
				{
					RemoveInventoryItem(1234, 4, peer, true);
					bool success = true;
					SaveItemMoreTimes(1206, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The shards forms into a devil wings!", 0, true);
					static_cast<PlayerInfo*>(peer->data)->cloth_back = 1206;
					Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
					sendClothes(peer);
				}
			}
			if (tile == 3110)
			{
				SearchInventoryItem(peer, 3110, 25, iscontains);
				if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6There's just not enough tatters here to make anything. Get more!", 0, true);
				else
				{
					RemoveInventoryItem(3110, 25, peer, true);
					if ((rand() % 100) <= 15)
					{
						bool success = true;
						SaveItemMoreTimes(3112, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The tatters forms into a inside-out vampire cape!", 0, true);
						static_cast<PlayerInfo*>(peer->data)->cloth_back = 3112;
						Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
						sendClothes(peer);
					}
					else
					{
						bool success = true;
						SaveItemMoreTimes(1166, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The tatters forms into a vampire cape!", 0, true);
						static_cast<PlayerInfo*>(peer->data)->cloth_back = 1166;
						Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
						sendClothes(peer);
					}
				}
			}
			if (tile == 2410)
			{
				SearchInventoryItem(peer, 2410, 200, iscontains);
				if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`oYou will need more `^Emerald Shards `oFor that!", 0, true);
				else
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`oThe power of `^Emerald Shards `oCompressed into `2Emerald Lock`o!", 0, true);
					RemoveInventoryItem(2410, 200, peer, true);
					bool success = true;
					SaveItemMoreTimes(2408, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnConsoleMessage(peer, "`o>> You received emerald lock!");
				}
			}
			if (tile == 4426)
			{
				SearchInventoryItem(peer, 4426, 200, iscontains);
				if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`oYou will need more `4Ruby Shards `oFor that!", 0, true);
				else
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`oThe power of `4Ruby Shards `oCompressed into `4Ruby Lock`o!", 0, true);
					RemoveInventoryItem(4426, 200, peer, true);
					auto success = true;
					SaveItemMoreTimes(4428, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnConsoleMessage(peer, "`o>> You received ruby lock!");
				}
			}
			return;
		}
	case 6856: case 6858: case 6860: case 6862: case 9266: /*subtokens*/
		{
			auto Sub_Days = 3;
			string Sub_Type = "free";
			if (tile == 9266) Sub_Days = 1;
			if (tile == 6856) Sub_Days = 3;
			if (tile == 6858) Sub_Days = 14;
			if (tile == 6860) Sub_Days = 30; Sub_Type = "premium";
			if (tile == 6862) Sub_Days = 365; Sub_Type = "premium";
			if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32) {
				if (static_cast<PlayerInfo*>(peer->data)->Subscriber) {
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You already have a Subscription!", 0, false);
					return;
				}
				string q = "UPDATE PlayerDatabase SET subtype = '" + Sub_Type + "', subdate = '" + to_string(Sub_Days) + "' WHERE username = '" + static_cast<PlayerInfo*>(peer->data)->rawName + "' LIMIT 1";
				if (mysql_query(conn, q.c_str())) {
					cout << mysql_error(conn) << endl;	
					enet_peer_disconnect_later(peer, 0);
					return;
				}
				RemoveInventoryItem(tile, 1, peer, true);
				SendTradeEffect(peer, tile, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
				static_cast<PlayerInfo*>(peer->data)->Subscriber = true;
				static_cast<PlayerInfo*>(peer->data)->haveSuperSupporterName = true;
				static_cast<PlayerInfo*>(peer->data)->SubscribtionEndDay = Sub_Days;
				Player::OnParticleEffect(peer, 46, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
				Player::OnAddNotification(peer, "`wYou've unlocked `5Premium Subscribtion `$benefits`w!", "audio/hub_open.wav", "interface/cash_icon_overlay.rttex");
				Player::PlayAudio(peer, "audio/thunderclap.wav", 0);
				MYSQL_ROW row;
				string text = "SELECT * FROM PlayerDatabase WHERE username = '" + static_cast<PlayerInfo*>(peer->data)->rawName + "' LIMIT 1";
				if (mysql_query(conn, text.c_str())) {
					cout << mysql_error(conn) << endl;		
					enet_peer_disconnect_later(peer, 0);
					return;
				}
				string title;
				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res)) {
					title = row[41];
				}
				static_cast<PlayerInfo*>(peer->data)->NickPrefix = title;
				if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "") {
					restoreplayernick(peer);
					GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName));
					memcpy(p7.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
					ENetPacket* packet7 = enet_packet_create(p7.data, p7.len, ENET_PACKET_FLAG_RELIABLE);
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, currentPeer)) {
							enet_peer_send(currentPeer, 0, packet7);
						}
					}
					delete p7.data;
				}
				string chatcolor;
				string strings = "SELECT * FROM PlayerDatabase WHERE username = '" + static_cast<PlayerInfo*>(peer->data)->rawName + "' LIMIT 1";
				if (mysql_query(conn, strings.c_str())) {
					cout << mysql_error(conn) << endl;		
					enet_peer_disconnect_later(peer, 0);
					return;
				}
				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res)) {
					chatcolor = row[48];
				}
				static_cast<PlayerInfo*>(peer->data)->chatcolor = chatcolor;
				send_state(peer);
				auto iscontains = false;
				SearchInventoryItem(peer, 6260, 1, iscontains);
				if (!iscontains) {
					bool success = true;
					SaveItemMoreTimes(6260, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from subscription");
					Player::OnAddNotification(peer, "`wYou've obtained `5Amulet Of Force`w!", "audio/hub_open.wav", "interface/cash_icon_overlay.rttex");
				}
			} else {
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Must be used on a person.", 0, true); 
			}
			return;
		}
	case 196: case 528: case 540: case 6918: case 6924: case 1662: case 3062: case 822: case 5706: /*consumables*/
		{

			if (tile == 5706) /*ssp*/
			{
				if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32) {
					RemoveInventoryItem(5706, 1, peer, true);
					int Seed1 = 0;
					int Seed2 = 0;
					int Seed3 = 0;
					int Seed4 = 0;
					int Seed5 = 0;
					int AVGRarity = rand() % 9 + 1;
					while (Seed1 == 0 || Seed2 == 0 || Seed3 == 0 || Seed4 == 0 || Seed5 == 0) {
						for (int i = 0; i < maxItems; i++) {
							if (i >= 1000) {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Something went wrong.", 0, true);
								break;
							}
							if (isSeed(i) && getItemDef(i).rarity == AVGRarity || isSeed(i) && getItemDef(i).rarity == AVGRarity + 1) {
								if (Seed1 == 0) Seed1 = i;
								else if (Seed2 == 0) Seed2 = i;
								else if (Seed3 == 0) Seed3 = i;
								else if (Seed4 == 0) Seed4 = i;
								else if (Seed5 == 0) Seed5 = i;
								else break;
								if (Seed4 != 0 && Seed5 == 0) AVGRarity = rand() % 9 + 1;
								else AVGRarity = rand() % 5 + 10;
							} else if (i == maxItems - 1) {
								break;
							}
						}
					}
					bool success = true;
					SaveItemMoreTimes(Seed1, 1, peer, success, "From small seed pack");
					SaveItemMoreTimes(Seed2, 1, peer, success, "From small seed pack");
					SaveItemMoreTimes(Seed3, 1, peer, success, "From small seed pack");
					SaveItemMoreTimes(Seed4, 1, peer, success, "From small seed pack");
					SaveItemMoreTimes(Seed5, 1, peer, success, "From small seed pack");
				} else {
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Must be used on a person.", 0, true); 
				}
			}

			if (tile == 196) /*blueberry*/
			{
				if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
				{
					SendTradeEffect(peer, 196, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
					string txt = "A `1blueberry`o slides down your throat! (`$Feelin' Blue`o mod added, `$5 secs`o left)";
					static_cast<PlayerInfo*>(peer->data)->skinColor = 4278190335;
					sendClothes(peer);
					sendSound(peer, "audio/spray.wav");
					RemoveInventoryItem(196, 1, peer, true);
					if (static_cast<PlayerInfo*>(peer->data)->blueBerry == false)
					{
						Player::OnConsoleMessage(peer, txt);
						static_cast<PlayerInfo*>(peer->data)->lastBerry = 5;
						static_cast<PlayerInfo*>(peer->data)->usedBerry = GetCurrentTimeInternalSeconds();
					}
					static_cast<PlayerInfo*>(peer->data)->blueBerry = true;
				}
				ENetPeer* peer2;
				for (peer2 = server->peers; peer2 < &server->peers[server->peerCount]; ++peer2)
				{
					if (peer2->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, peer2))
					{
						PlayerInfo* cpinfo = static_cast<PlayerInfo*>(peer2->data);
						if (x == cpinfo->x / 32 && y == cpinfo->y / 32)
						{
							SendTradeEffect(peer2, 196, static_cast<PlayerInfo*>(peer->data)->netID, cpinfo->netID, 150);
							SendTradeEffect(peer, 196, static_cast<PlayerInfo*>(peer->data)->netID, cpinfo->netID, 150);
							string txt = "A `1blueberry`o slides down your throat! (`$Feelin' Blue`o mod added, `$5 secs`o left)";
							cpinfo->skinColor = 4278190335;
							sendClothes(peer2);
							sendSound(peer2, "audio/spray.wav");
							if (cpinfo->blueBerry == false)
							{
								Player::OnConsoleMessage(peer2, txt);
								static_cast<PlayerInfo*>(peer2->data)->lastBerry = 5;
								static_cast<PlayerInfo*>(peer2->data)->usedBerry = GetCurrentTimeInternalSeconds();
							}
							cpinfo->blueBerry = true;
							break;
						}
					}
				}
			} 
			if (tile == 528) /*luckyclover*/
			{
				if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
				{
					if (static_cast<PlayerInfo*>(peer->data)->LuckyClover == false)
					{
						SendTradeEffect(peer, 528, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						sendSound(peer, "audio/spray.wav");
						RemoveInventoryItem(528, 1, peer, true);
						Player::OnConsoleMessage(peer, "You're `$luckier `othan before! (`$Lucky! `omod added, `$5 mins`o left)");
						static_cast<PlayerInfo*>(peer->data)->lastClover = 300;
						static_cast<PlayerInfo*>(peer->data)->usedClover = GetCurrentTimeInternalSeconds();
						static_cast<PlayerInfo*>(peer->data)->LuckyClover = true;
					}
					else Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You already have active lucky clover!", 0, true);
				}
			}
			if (tile == 6918) /*punchpotion*/
			{
				if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
				{
					if (static_cast<PlayerInfo*>(peer->data)->PunchPotion == false)
					{
						SendTradeEffect(peer, 6918, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						sendSound(peer, "audio/spray.wav");
						RemoveInventoryItem(6918, 1, peer, true);
						Player::OnConsoleMessage(peer, "You're `$stronger `othan before! (`$One HIT! `omod added, `$5 mins`o left)");
						static_cast<PlayerInfo*>(peer->data)->lastPunchPotion = 300;
						static_cast<PlayerInfo*>(peer->data)->usedPunchPotion = GetCurrentTimeInternalSeconds();
						static_cast<PlayerInfo*>(peer->data)->PunchPotion = true;
					}
					else Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You already have active punch potion!", 0, true);
				}
			}
			if (tile == 6924) /*placepotion*/
			{
				if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
				{
					if (static_cast<PlayerInfo*>(peer->data)->PlacePotion == false)
					{
						SendTradeEffect(peer, 6924, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						sendSound(peer, "audio/spray.wav");
						RemoveInventoryItem(6924, 1, peer, true);
						Player::OnConsoleMessage(peer, "Your hands are `$exceeding`o! (`$Triple Place! `omod added, `$5 mins`o left)");
						static_cast<PlayerInfo*>(peer->data)->lastPlacePotion = 300;
						static_cast<PlayerInfo*>(peer->data)->usedPlacePotion = GetCurrentTimeInternalSeconds();
						static_cast<PlayerInfo*>(peer->data)->PlacePotion = true;
					}
					else Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You already have active place potion!", 0, true);
				}
			}
			if (tile == 1662) /*spikejuice*/
			{
				if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
				{
					if (static_cast<PlayerInfo*>(peer->data)->SpikeJuice == false)
					{
						SendTradeEffect(peer, 1662, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						sendSound(peer, "audio/spray.wav");
						RemoveInventoryItem(1662, 1, peer, true);
						Player::OnConsoleMessage(peer, "You are immune to spikes and lava! (`$Spikeproof! `omod added, `$5 secs`o left)");
						static_cast<PlayerInfo*>(peer->data)->lastSpike = 5;
						static_cast<PlayerInfo*>(peer->data)->usedSpike = GetCurrentTimeInternalSeconds();
						static_cast<PlayerInfo*>(peer->data)->SpikeJuice = true;
					}
					else Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You already have active spike juice!", 0, true);
				}
			}
			if (tile == 540)
			{
				RemoveInventoryItem(540, 1, peer, true);
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`2BURRRPPP...!", 0, true);
			}
			if (tile == 3062)
			{
				if (world->items[x + (y * world->width)].fire == false && world->items[x + (y * world->width)].water == false)
				{
					if (isSeed(world->items[x + (y * world->width)].foreground)  || world->items[x + (y * world->width)].foreground == 0 && world->items[x + (y * world->width)].background == 6864 || world->items[x + (y * world->width)].water || world->items[x + (y * world->width)].foreground == 6952 || world->items[x + (y * world->width)].foreground == 6954 || world->items[x + (y * world->width)].foreground == 5638 || world->items[x + (y * world->width)].foreground == 6946 || world->items[x + (y * world->width)].foreground == 6948 || world->items[x + (y * world->width)].foreground == 2978 || world->items[x + (y * world->width)].foreground == 1420 || world->items[x + (y * world->width)].foreground == 6214 || world->items[x + (y * world->width)].foreground == 1006 || world->items[x + (y * world->width)].foreground == 656 || world->items[x + (y * world->width)].foreground == 1420 || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::DONATION || world->items[x + (y * world->width)].foreground == 3528 || world->items[x + (y * world->width)].foreground == 0 && world->items[x + (y * world->width)].background == 0 || world->items[x + (y * world->width)].foreground == 6 || world->items[x + (y * world->width)].foreground == 8 || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::DISPLAY) {
						if (world->items[x + (y * world->width)].background != 6864) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wCan't burn that!", 0, true);
						return;
					}
					if (world->items[x + (y * world->width)].foreground != 6 && world->items[x + (y * world->width)].foreground != 8 && getItemDef(world->items[x + (y * world->width)].foreground).blockType != BlockTypes::LOCK)
					{
						if (world->items[x + (y * world->width)].foreground == 0 && world->items[x + (y * world->width)].background == 0)
						{
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wTheres nothing to burn!", 0, true);
							return;
						}
						world->items[x + (y * world->width)].fire = !world->items[x + (y * world->width)].fire;
						ENetPeer* net_peer;
						for (net_peer = server->peers;
							net_peer < &server->peers[server->peerCount];
							++net_peer)
						{
							if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, net_peer))
							{
								Player::OnParticleEffect(net_peer, 150, x * 32 + 16, y * 32 + 16, 0);
								Player::OnTalkBubble(net_peer, static_cast<PlayerInfo*>(peer->data)->netID, "`7[```4MWAHAHAHA!! FIRE FIRE FIRE```7]``", 0, false);
							}
						}
						RemoveInventoryItem(3062, 1, peer, true);
						UpdateVisualsForBlock(peer, true, x, y, world);
						if (world->items[x + (y * world->width)].foreground == 0)
						{
							if (getItemDef(tile).rarity != 999)
							{
								int b = getGemCount(tile) + rand() % 1;
								while (b > 0)
								{
									if (b >= 100)
									{
										DropItem(
											peer, -1,
											x * 32 + (rand() % 16),
											y * 32 + (rand() % 16),
											112,
											100, 0);
										b -= 100;
										for (int i = 0; i < rand() % 1; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 10, 0);
										for (int i = 0; i < rand() % 4; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
										continue;
									}
									if (b >= 50)
									{
										DropItem(
											peer, -1,
											x * 32 + (rand() % 16),
											y * 32 + (rand() % 16),
											112,
											50, 0);
										b -= 50;
										for (int i = 0; i < rand() % 1; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 5, 0);
										for (int i = 0; i < rand() % 3; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
										continue;
									}
									if (b >= 10)
									{
										DropItem(
											peer, -1,
											x * 32 + (rand() % 16),
											y * 32 + (rand() % 16),
											112,
											10, 0);
										b -= 10;
										for (int i = 0; i < rand() % 4; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
										continue;
									}
									if (b >= 7)
									{
										DropItem(
											peer, -1,
											x * 32 + (rand() % 16),
											y * 32 + (rand() % 16),
											112,
											10, 0);
										b -= 5;
										for (int i = 0; i < rand() % 2; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
										continue;
									}
									if (b >= 5)
									{
										DropItem(
											peer, -1,
											x * 32 + (rand() % 16),
											y * 32 + (rand() % 16),
											112,
											5, 0);
										b -= 5;
										for (int i = 0; i < rand() % 2; i++) DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
										continue;
									}
									if (b >= 1)
									{
										DropItem(
											peer, -1,
											x * 32 + (rand() % 16),
											y * 32 + (rand() % 16),
											112,
											1, 0);
										b -= 1;
										for (int i = 0; i < rand() % 1; i++) DropItem(peer, -1, x * 32 + (rand() % 8), y * 32 + (rand() % 16), 112, 1, 0);
										continue;
									}
								}
							}
						}
					}
				} 
				return;
			}
			if (tile == 822) {
				if (world->items[x + (y * world->width)].fire) {
					SendThrowEffect(peer, 822, static_cast<PlayerInfo*>(peer->data)->netID, -1, 150, 0, x * 32 + 16, y * 32 + 16);
					RemoveInventoryItem(822, 1, peer, true);
					world->items[x + (y * world->width)].fire = false;
					UpdateBlockState(peer, x, y, true, world);
					for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
						if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, net_peer)) {
							Player::OnParticleEffect(net_peer, 149, x * 32, y * 32, 0);
						}
					}
					return;
				}
				if (world->items[x + (y * world->width)].foreground != 6 && world->items[x + (y * world->width)].foreground != 8 && getItemDef(world->items[x + (y * world->width)].foreground).blockType != BlockTypes::LOCK) {
					if (isWorldOwner(peer, world) || world->owner == "" || isMod(peer)) {
						if (world->items[x + (y * world->width)].water) {
							world->items[x + (y * world->width)].water = false;
							UpdateBlockState(peer, x, y, false, world);
							if ((rand() % 99) + 1 < 40) {
								bool success = true;
								SaveItemMoreTimes(822, 1, peer, success);
							}
							UpdateVisualsForBlock(peer, false, x, y, world);
						} else { 
							world->items[x + (y * world->width)].water = true;
							UpdateBlockState(peer, x, y, true, world);
							RemoveInventoryItem(822, 1, peer, true);
							SendThrowEffect(peer, 822, static_cast<PlayerInfo*>(peer->data)->netID, -1, 150, 0, x * 32 + 16, y * 32 + 16);
							UpdateVisualsForBlock(peer, true, x, y, world);
						}
					}
				}
			}
			return;
		}
	case 1866:
		{
			if (world->owner == "" || isWorldOwner(peer, world) || isMod(peer)) {
				if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK) {
					return;
				}
				world->items[x + (y * world->width)].glue = !world->items[x + (y * world->width)].glue;
				UpdateVisualsForBlock(peer, true, x, y, world);
			}
			return;
		}
	case 8428:
		{
			Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wUranus Blast`|left|8428|\nadd_textbox|`oThis item creates a new world!  Enter a unique name for it.|left|\nadd_text_input|uranusname|New World Name||24|\nend_dialog|useuranusblast|Cancel|`5Create!|\n");
			return;
		}
	case 10434:
		{
			Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wTiny Blast`|left|10434|\nadd_textbox|This item creates a new world!  Enter a unique name for it.|left|\nadd_text_input|tinyname|New World Name||24|\nend_dialog|usetinyblast|Cancel|`5Create!|\n");
			return;
		}
	case 10428:
		{
			Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wLarge Blast`|left|10428|\nadd_textbox|This item creates a new world!  Enter a unique name for it.|left|\nadd_text_input|largename|New World Name||24|\nend_dialog|uselargeblast|Cancel|`5Create!|\n");
			return;
		}
	case 1402:
		{
			Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wThermonuclear Blast`|left|1402|\nadd_textbox|This item creates a new world!  Enter a unique name for it.|left|\nadd_text_input|thermoname|New World Name||24|\nend_dialog|usethermoblast|Cancel|`5Create!|\n");
			return;
		}
	case 1826:
		{
			if (!isWorldOwner(peer, world)) return;
			auto iscontainsss = false;
			SearchInventoryItem(peer, 1826, 1, iscontainsss);
			if (!iscontainsss) {
				return;
			} else {
				auto FoundSomething = false;
				for (auto i = 0; i < world->width * world->height; i++) {
					if (isSeed(world->items[i].foreground)) {
						sendTileUpdate((i % world->width), (i / world->width), 18, static_cast<PlayerInfo*>(peer->data)->netID, peer, world);
						ENetPeer* net_peer;
						for (net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
							if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, net_peer)) {
								Player::OnParticleEffect(net_peer, 182, (i % world->width) * 32, (i / world->width) * 32, 0);
							}
						}
						FoundSomething = true;
					}
				}
				if (FoundSomething) RemoveInventoryItem(1826, 1, peer, true);
			}
			return;
		}
	case 5640: /*magplantremote*/
		{
			bool aryra = false;
			for (int i = 0; i < world->width * world->height; i++) {
				if (world->items[i].foreground == 5638) {
					aryra = true;
				}
			}
			if (aryra == true) {
				if (static_cast<PlayerInfo*>(peer->data)->magplantx != 0 && static_cast<PlayerInfo*>(peer->data)->magplanty != 0) {
					int squaresign = static_cast<PlayerInfo*>(peer->data)->magplantx + (static_cast<PlayerInfo*>(peer->data)->magplanty * world->width);
					string currentworld = static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign);
					if (world->items[static_cast<PlayerInfo*>(peer->data)->magplantx + (static_cast<PlayerInfo*>(peer->data)->magplanty * world->width)].mid == static_cast<PlayerInfo*>(peer->data)->magplantitemid && world->items[static_cast<PlayerInfo*>(peer->data)->magplantx + (static_cast<PlayerInfo*>(peer->data)->magplanty * world->width)].mc > 0) {
						int magplantid = static_cast<PlayerInfo*>(peer->data)->magplantitemid;
						bool RotatedRight = false;
						auto xpos = x * 32;
						auto ppos = static_cast<PlayerInfo*>(peer->data)->x;
						if (static_cast<PlayerInfo*>(peer->data)->x < x * 32) RotatedRight = true;
						if (RotatedRight) ppos += 19;
						xpos = xpos / 32;
						ppos = ppos / 32;
						if (world->items[x + (y * world->width)].foreground != 0 && getItemDef(magplantid).blockType != BlockTypes::BACKGROUND && getItemDef(magplantid).blockType != BlockTypes::GROUND_BLOCK) return;
						ENetPeer* currentPeer;
						for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer)) {
								bool RotatedRight = false;
								auto xpos = x * 32;
								auto ppos = static_cast<PlayerInfo*>(currentPeer->data)->x;
								if (static_cast<PlayerInfo*>(currentPeer->data)->x < x * 32) RotatedRight = true;
								if (RotatedRight) ppos += 19;
								xpos = xpos / 32;
								ppos = ppos / 32;
								if (ppos == xpos && static_cast<PlayerInfo*>(currentPeer->data)->y / 32 == y && getItemDef(magplantid).properties != Property_NoSeed && getItemDef(magplantid).properties != Property_Foreground && getItemDef(magplantid).properties != Property_MultiFacing && getItemDef(magplantid).blockType != BlockTypes::SEED && getItemDef(magplantid).blockType != BlockTypes::STEAM && getItemDef(magplantid).blockType != BlockTypes::UNKNOWN && getItemDef(magplantid).blockType != BlockTypes::VENDING && getItemDef(magplantid).blockType != BlockTypes::ANIM_FOREGROUND && getItemDef(magplantid).blockType != BlockTypes::BULLETIN_BOARD && getItemDef(magplantid).blockType != BlockTypes::FACTION && getItemDef(magplantid).blockType != BlockTypes::CHEST && getItemDef(magplantid).blockType != BlockTypes::GEMS && getItemDef(magplantid).blockType != BlockTypes::MAGIC_EGG && getItemDef(magplantid).blockType != BlockTypes::CRYSTAL && getItemDef(magplantid).blockType != BlockTypes::MAILBOX && getItemDef(magplantid).blockType != BlockTypes::PORTAL && getItemDef(magplantid).blockType != BlockTypes::PLATFORM && getItemDef(magplantid).blockType != BlockTypes::SFX_FOREGROUND && getItemDef(magplantid).blockType != BlockTypes::CHEMICAL_COMBINER && getItemDef(magplantid).blockType != BlockTypes::SWITCH_BLOCK && getItemDef(magplantid).blockType != BlockTypes::TRAMPOLINE && getItemDef(magplantid).blockType != BlockTypes::TOGGLE_FOREGROUND && getItemDef(magplantid).blockType != BlockTypes::GROUND_BLOCK && getItemDef(magplantid).blockType != BlockTypes::BACKGROUND && getItemDef(magplantid).blockType != BlockTypes::MAIN_DOOR && getItemDef(magplantid).blockType != BlockTypes::SIGN && getItemDef(magplantid).blockType != BlockTypes::DOOR && getItemDef(magplantid).blockType != BlockTypes::CHECKPOINT && getItemDef(magplantid).blockType != BlockTypes::GATEWAY && getItemDef(magplantid).blockType != BlockTypes::TREASURE && getItemDef(magplantid).blockType != BlockTypes::WEATHER) return;
							}
						}
						if (world->isPublic || isWorldAdmin(peer, world) || static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || world->owner == "" || isMod(peer) || !RestrictedArea(peer, world, x, y)) {
							world->items[x + (y * world->width)].foreground = magplantid;
							world->items[static_cast<PlayerInfo*>(peer->data)->magplantx + (static_cast<PlayerInfo*>(peer->data)->magplanty * world->width)].mc -= 1;
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x;
							data3.y = y;
							data3.punchX = x;
							data3.punchY = y;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = magplantid;
							for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
								if (isHere(peer, currentPeer)) {
									auto raw = packPlayerMoving(&data3);
									raw[2] = dicenr;
									raw[3] = dicenr;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
								if (isHere(peer, currentPeer)) {
									if (world->items[static_cast<PlayerInfo*>(peer->data)->magplantx + (static_cast<PlayerInfo*>(peer->data)->magplanty * world->width)].mc <= 0) {
										SendItemSucker(currentPeer, 5638, static_cast<PlayerInfo*>(peer->data)->magplantx, static_cast<PlayerInfo*>(peer->data)->magplanty, world->items[static_cast<PlayerInfo*>(peer->data)->magplantx + (static_cast<PlayerInfo*>(peer->data)->magplanty * world->width)].mid, 0, true, true, world->items[static_cast<PlayerInfo*>(peer->data)->magplantx + (static_cast<PlayerInfo*>(peer->data)->magplanty * world->width)].background);
									}
									else if (world->items[static_cast<PlayerInfo*>(peer->data)->magplantx + (static_cast<PlayerInfo*>(peer->data)->magplanty * world->width)].mc >= 5000) {
										SendItemSucker(currentPeer, 5638, static_cast<PlayerInfo*>(peer->data)->magplantx, static_cast<PlayerInfo*>(peer->data)->magplanty, world->items[static_cast<PlayerInfo*>(peer->data)->magplantx + (static_cast<PlayerInfo*>(peer->data)->magplanty * world->width)].mid, -1, true, true, world->items[static_cast<PlayerInfo*>(peer->data)->magplantx + (static_cast<PlayerInfo*>(peer->data)->magplanty * world->width)].background);
									}
									else {
										SendItemSucker(currentPeer, 5638, static_cast<PlayerInfo*>(peer->data)->magplantx, static_cast<PlayerInfo*>(peer->data)->magplanty, world->items[static_cast<PlayerInfo*>(peer->data)->magplantx + (static_cast<PlayerInfo*>(peer->data)->magplanty * world->width)].mid, 1, true, true, world->items[static_cast<PlayerInfo*>(peer->data)->magplantx + (static_cast<PlayerInfo*>(peer->data)->magplanty * world->width)].background);
									}
								}
							}
						}
					}
					else {
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wThe `2MAGPLANT 5000 `wis empty!", 0, false);
					}
				}
			}
			return;
		}
	case 6204: case 6202: case 6200: case 7484: case 7954: case 1360: /*chest*/
		{
			if (tile == 1360) {
				vector<int> Dailyb{ 242, 242, 242, 828, 68, 82, 10032, 98, 404, 400, 3402, 3400 };
				const int Index = rand() % Dailyb.size();
				const auto ItemID = Dailyb[Index];
				RemoveInventoryItem(1360, 1, peer, true);
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou received " + getItemDef(ItemID).name + "", 0, true);
				Player::OnConsoleMessage(peer, "`oYou received " + getItemDef(ItemID).name + "");
				bool success = true;
				SaveItemMoreTimes(ItemID, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from daily gift");
			}
			if (tile == 6204) {
				if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) return;
				auto iscontains = false;
				SearchInventoryItem(peer, 6204, 1, iscontains);
				if (!iscontains) {
					return;
				} else {
					RemoveInventoryItem(6204, 1, peer, true);
					auto kuriPrizaDuot = rand() % 2 + 1;
					if (kuriPrizaDuot == 1)
					{
						auto gemChance = rand() % 20000;
						GiveChestPrizeGems(peer, gemChance);
					}
					if (kuriPrizaDuot == 2)
					{
						int itemuMas[5] = { 7912, 7912, 7912, 5078, 8834 };
						auto randIndex = rand() % 5;
						auto itemId = itemuMas[randIndex];
						send_item(peer, itemId, 1, 6204);
					}
				}
			}
			if (tile == 6202)
			{
				if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) return;
				auto iscontains = false;
				SearchInventoryItem(peer, 6202, 1, iscontains);
				if (!iscontains)
				{
					return;
				}
				else
				{
					RemoveInventoryItem(6202, 1, peer, true);
					auto kuriPrizaDuot = rand() % 2 + 1;
					if (kuriPrizaDuot == 1)
					{
						auto gemChance = rand() % 70000;
						GiveChestPrizeGems(peer, gemChance);
					}
					if (kuriPrizaDuot == 2)
					{
						int itemuMas[5] = { 7912, 5078, 5078, 5078, 8834 };
						auto randIndex = rand() % 5;
						auto itemId = itemuMas[randIndex];
						send_item(peer, itemId, 1, 6202);
					}
				}
			}
			if (tile == 6200)
			{
				if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) return;
				auto iscontains = false;
				SearchInventoryItem(peer, 6200, 1, iscontains);
				if (!iscontains)
				{
					return;
				}
				else
				{
					RemoveInventoryItem(6200, 1, peer, true);
					auto kuriPrizaDuot = rand() % 2 + 1;
					if (kuriPrizaDuot == 1)
					{
						auto gemChance = rand() % 120000;
						GiveChestPrizeGems(peer, gemChance);
					}
					if (kuriPrizaDuot == 2)
					{
						int itemuMas[8] = { 7912, 7912, 7912, 7912, 5078, 5078, 5078, 8834 };
						auto randIndex = rand() % 8;
						auto itemId = itemuMas[randIndex];
						send_item(peer, itemId, 1, 6200);
					}
				}
			}
			if (tile == 7484)
			{
				if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) return;
				auto iscontains = false;
				SearchInventoryItem(peer, 7484, 1, iscontains);
				if (!iscontains)
				{
					return;
				}
				else
				{
					RemoveInventoryItem(7484, 1, peer, true);
					auto kuriPrizaDuot = rand() % 2 + 1;
					if (kuriPrizaDuot == 1)
					{
						auto gemChance = rand() % 170000;
						GiveChestPrizeGems(peer, gemChance);
					}
					if (kuriPrizaDuot == 2)
					{
						int itemuMas[12] = { 7912, 7912, 7912, 7912, 5078, 5078, 5078, 8834, 8834, 8834, 8834, 8834 };
						auto randIndex = rand() % 12;
						int itemId = itemuMas[randIndex];
						send_item(peer, itemId, 1, 7484);
					}
				}
			}
			if (tile == 7954)
			{
				if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) return;
				auto iscontains = false;
				SearchInventoryItem(peer, 7954, 1, iscontains);
				if (!iscontains)
				{
					return;
				}
				else
				{
					RemoveInventoryItem(7954, 1, peer, true);
					auto kuriPrizaDuot = rand() % 2 + 1;
					if (kuriPrizaDuot == 1)
					{
						int gemChance = rand() % 200000;
						GiveChestPrizeGems(peer, gemChance);
					}
					if (kuriPrizaDuot == 2)
					{
						int itemuMas[12] = { 7912, 7912, 7912, 7912, 5078, 5078, 5078, 8834, 8834, 8834, 8834, 8834 };
						auto randIndex = rand() % 12;
						auto itemId = itemuMas[randIndex];
						send_item(peer, itemId, 1, 7954);
					}
				}
			}
			return;
		}
	case 1404: /*doormover*/
		{
		if (static_cast<PlayerInfo*>(peer->data)->rawName != world->owner && !isMod(peer) && world->owner != "") return;
			if (world->items[x + (y * world->width)].foreground != 0) {
				Player::OnTextOverlay(peer, "`@There Is `4No `@Space For `wMain Door`@!");
				return;
			} else {
				RemoveInventoryItem(1404, 1, peer, true);
				for (int i = 0; i < world->width * world->height; i++) {
					if (i >= 5400) {
						world->items[i].foreground = 8;
					} else if (world->items[i].foreground == 6) {
						world->items[i].foreground = 0;
					} else if (world->items[i].foreground != 6) {
						world->items[x + (y * world->width)].foreground = 6;
					}
				}
				for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
					if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, net_peer)) {
						//string act = static_cast<PlayerInfo*>(peer->data)->currentWorld;
						sendPlayerLeave(net_peer);
						Player::OnTextOverlay(peer, "`^You Have `2Used `wDoor Mover`^!");
					}
				}
			}
			return;
		}
	case 5460: case 4520: case 382: case 3116: case 1792: case 732: case 2994: case 4368: case 274: case 276: case 278: case 5708: case 5709: case 5780: case 5781: case 5782: case 5783: case 5784: case 5785: case 5710: case 5711: case 5786: case 5787: case 5788: case 5789: case 5790: case 5791: case 6146: case 6147: case 6148: case 6149: case 6150: case 6151: case 6152: case 6153: case 5670: case 5671: case 5798: case 5799: case 5800: case 5801: case 5802: case 5803: case 5668: case 5669: case 5792: case 5793: case 5794: case 5795: case 5796: case 5797: case 544: case 54600: case 1902: case 1508: case 428: case 3808: case 5132: case 7166: case 5078: case 5080: case 5082: case 5084: case 5126: case 5128: case 5130: case 5144: case 5146: case 5148: case 5150: case 5162: case 5164: case 5166: case 5168: case 5180: case 5182: case 5184: case 5186: case 7168: case 7170: case 7172: case 7174: case 2480: case 9999: case 980: case 3212: case 4742: case 3496: case 3270: case 4722: case 9212: case 5134: case 5152: case 5170: case 5188: case 611:
		{
			return;
		}
	default:
		{
			if (world->items[x + (y * world->width)].fire && tile != 18) return;
			if (tile == 6954) {
				isMagplant = true;
			}
			if (getItemDef(tile).blockType == BlockTypes::PROVIDER) {
				isScience = true;
			}
			if (getItemDef(tile).blockType == BlockTypes::DONATION)
			{
				namespace fs = std::experimental::filesystem;
				if (!fs::is_directory("donationboxes/" + world->name) || !fs::exists("donationboxes/" + world->name))
				{
					fs::create_directory("donationboxes/" + world->name);
				}
				ofstream of("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				json j;
				j["donated"] = 0;
				json jArray = json::array();
				json jmid;
				for (int i = 1; i <= 20; i++)
				{
					jmid["aposition"] = i;
					jmid["sentBy"] = "";
					jmid["note"] = "";
					jmid["itemid"] = 0;
					jmid["itemcount"] = 0;
					jArray.push_back(jmid);
				}
				j["donatedItems"] = jArray;
				of << j << std::endl;
				of.close();
			}

			if (getItemDef(tile).blockType == BlockTypes::GATEWAY) {
				world->items[squaresign].opened = true;
				isgateway = true;
			}

			if (world->items[x + (y * world->width)].foreground == 1420 || world->items[x + (y * world->width)].foreground == 6214 && tile != 18) {
				if (getItemDef(tile).blockType == BlockTypes::CLOTHING)
				{
					if (world->owner == "" || static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner))
					{
						if (getItemDef(tile).properties & Property_Untradable) {
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You can't use untradeable items with mannequins.", 0, true);
							return;
						}
						auto seedexist = std::experimental::filesystem::exists("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						if (seedexist)
						{
							json j;
							ifstream fs("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							fs >> j;
							fs.close();

							int c = getItemDef(tile).clothType;
							if (c == 0) {
								//world->items[x + (y * world->width)].clothHead = tile;
								if (j["clothHead"].get<string>() != "0") return;
								j["clothHead"] = to_string(tile);
							}
							else if (c == 7) {
								//world->items[x + (y * world->width)].clothHair = tile;
								if (j["clothHair"].get<string>() != "0") return;
								j["clothHair"] = to_string(tile);
							}
							else if (c == 4) {
								//world->items[x + (y * world->width)].clothMask = tile;
								if (j["clothMask"].get<string>() != "0") return;
								j["clothMask"] = to_string(tile);
							}
							else if (c == 8) {
								//world->items[x + (y * world->width)].clothNeck = tile;
								if (j["clothNeck"].get<string>() != "0") return;
								j["clothNeck"] = to_string(tile);
							}
							else if (c == 6) {
								//world->items[x + (y * world->width)].clothBack = tile;
								if (j["clothBack"].get<string>() != "0") return;
								j["clothBack"] = to_string(tile);
							}
							else if (c == 1) {
								//world->items[x + (y * world->width)].clothShirt = tile;
								if (j["clothShirt"].get<string>() != "0") return;
								j["clothShirt"] = to_string(tile);
							}
							else if (c == 2) {
								//world->items[x + (y * world->width)].clothPants = tile;
								if (j["clothPants"].get<string>() != "0") return;
								j["clothPants"] = to_string(tile);
							}
							else if (c == 3) {
								//world->items[x + (y * world->width)].clothFeet = tile;
								if (j["clothFeet"].get<string>() != "0") return;
								j["clothFeet"] = to_string(tile);
							}
							else if (c == 5) {
								//world->items[x + (y * world->width)].clothHand = tile;
								if (j["clothHand"].get<string>() != "0") return;
								j["clothHand"] = to_string(tile);
							}

							if (c != 10) {
								auto iscontains = false;
								SearchInventoryItem(peer, tile, 1, iscontains);
								if (iscontains)
								{
									updateMannequin(peer, world->items[x + (y * world->width)].foreground, x, y, world->items[x + (y * world->width)].background, world->items[x + (y * world->width)].sign,
										atoi(j["clothHair"].get<string>().c_str()), atoi(j["clothHead"].get<string>().c_str()),
										atoi(j["clothMask"].get<string>().c_str()), atoi(j["clothHand"].get<string>().c_str()), atoi(j["clothNeck"].get<string>().c_str()),
										atoi(j["clothShirt"].get<string>().c_str()), atoi(j["clothPants"].get<string>().c_str()), atoi(j["clothFeet"].get<string>().c_str()),
										atoi(j["clothBack"].get<string>().c_str()), true, 0);

									ofstream of("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
									of << j;
									of.close();
									RemoveInventoryItem(tile, 1, peer, true);
								}
							}
						}
					}
				}
			}
			if (world->owner == "" && getItemDef(tile).blockType == BlockTypes::LOCK && tile != 202 && tile != 204 && tile != 206 && tile != 4994) {
				bool block_place = false;
				string whosowner = "";
				for (int i = 0; i < world->width * world->height; i++) {
					if (world->items[i].foreground == 202 && world->items[i].monitorname != static_cast<PlayerInfo*>(peer->data)->rawName || world->items[i].foreground == 204 && world->items[i].monitorname != static_cast<PlayerInfo*>(peer->data)->rawName || world->items[i].foreground == 206 && world->items[i].monitorname != static_cast<PlayerInfo*>(peer->data)->rawName || world->items[i].foreground && world->items[i].monitorname != static_cast<PlayerInfo*>(peer->data)->rawName == 4994) {
						whosowner = world->items[i].monitorname;
						block_place = true;
						break;
					}
				}
				if (block_place) {
					MYSQL_ROW row;
					string nickname, adminlevel;
					string q = "SELECT * FROM PlayerDatabase WHERE username = '" + whosowner + "' LIMIT 1";
					if (mysql_query(conn, q.c_str())) {
						cout << mysql_error(conn) << endl;
						enet_peer_disconnect_later(peer, 0);
						return;
					}
					res = mysql_store_result(conn);
					while (row = mysql_fetch_row(res)) {
						adminlevel = row[19];
						nickname = row[44];
					}
					if (nickname == "") {
						if (adminlevel == "1") {
							nickname = "`#@" + whosowner;
						} else if (adminlevel == "2") {
							nickname = "`6@" + whosowner;
						} else {
							nickname = whosowner;
						}
					} 
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wThat area is owned by " + nickname + "", 0, false);
					return;
				}
			}
			if (tile == 242 || tile == 2408 || tile == 1796 || tile == 4428 || tile == 7188 || tile == 8470 || tile == 9290 || tile == 9308 || tile == 9504 || tile == 2950 || tile == 4802 || tile == 5260 || tile == 5814 || tile == 5980 || tile == 9640) {
				if (world->owner != "") {
					if (!isWorldOwner(peer, world)) {
						MYSQL_ROW row;
						string nickname, adminlevel;
						string q = "SELECT * FROM PlayerDatabase WHERE username = '" + world->owner + "' LIMIT 1";
						if (mysql_query(conn, q.c_str())) {
							cout << mysql_error(conn) << endl;
							enet_peer_disconnect_later(peer, 0);
							return;
						}
						res = mysql_store_result(conn);
						while (row = mysql_fetch_row(res)) {
							adminlevel = row[19];
							nickname = row[44];
						}
						if (nickname == "") {
							if (adminlevel == "1") {
								nickname = "`#@" + world->owner;
							} else if (adminlevel == "2") {
								nickname = "`6@" + world->owner;
							} else {
								nickname = world->owner;
							}
						} 
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wThat area is owned by " + nickname + "", 0, false);
					} else {
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`0Only one `$World Lock `0Can be placed in a world!", 0, true);
					}
					return;
				}
			}
			if (getItemDef(tile).blockType == BlockTypes::LOCK) {
				if (tile == 202 || tile == 204 || tile == 206 || tile == 4994) {
					if (!RestrictedArea_check(world, x, y)) {
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Cant place " + getItemDef(tile).name + " here!", 0, false);
						return;
					}
					world->items[x + (y * world->width)].monitorname = static_cast<PlayerInfo*>(peer->data)->rawName;
					isSmallLock = true;	
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Area locked.", 0, false);	
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, currentPeer)) {
							Player::PlayAudio(currentPeer, "audio/use_lock.wav", 0);
						}
					}	
				} else {
					world->owner = static_cast<PlayerInfo*>(peer->data)->rawName;
					world->isPublic = false;
					static_cast<PlayerInfo*>(peer->data)->worldsowned.push_back(static_cast<PlayerInfo*>(peer->data)->currentWorld);
					for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, currentPeer)) {
							Player::OnConsoleMessage(currentPeer, "`3[`w" + world->name + " `ohas been `$" + getItemDef(tile).name + "ed `oBy " + static_cast<PlayerInfo*>(peer->data)->displayName + "`3]");
							Player::PlayAudio(currentPeer, "audio/use_lock.wav", 0);
						}
					}
					if (static_cast<PlayerInfo*>(peer->data)->displayName.find("`") != string::npos) {} else {
						static_cast<PlayerInfo*>(peer->data)->displayName = "`2" + static_cast<PlayerInfo*>(peer->data)->displayName;
						auto p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), "`2" + static_cast<PlayerInfo*>(peer->data)->displayName));
						memcpy(p7.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
						auto packet7 = enet_packet_create(p7.data, p7.len, ENET_PACKET_FLAG_RELIABLE);
						delete p7.data;
						for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer)) {
								if (static_cast<PlayerInfo*>(peer->data)->adminLevel >= 0) {
									enet_peer_send(currentPeer, 0, packet7);
								}
							}
						}
					}
					isLock = true;
				}
			}
			SyncFish(peer);
			if (tile == 2914 && isFishingRod(peer) || tile == 3016 && isFishingRod(peer))
			{
				if (world->items[x + (y * world->width)].water)
				{
					int PlayerPos = round(static_cast<PlayerInfo*>(peer->data)->x / 32);
					int PlayerPosY = round(static_cast<PlayerInfo*>(peer->data)->y / 32);
					if (PlayerPos != x && PlayerPos + 1 != x && PlayerPos - 1 != x || PlayerPosY != y && PlayerPosY + 1 != y)
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Too far away...", 0, true);
						return;
					}
					if (static_cast<PlayerInfo*>(peer->data)->x != 0 && !static_cast<PlayerInfo*>(peer->data)->Fishing)
					{
						RemoveInventoryItem(tile, 1, peer, true);
						static_cast<PlayerInfo*>(peer->data)->FishPosX = x * 32;
						static_cast<PlayerInfo*>(peer->data)->FishPosY = y * 32;
						static_cast<PlayerInfo*>(peer->data)->Fishing = true;
						static_cast<PlayerInfo*>(peer->data)->LastBait = getItemDef(tile).name;
						SendFishingState(peer);
						for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer)) {
								SendFishing(currentPeer, static_cast<PlayerInfo*>(peer->data)->netID, x, y);
							}
						}
					}
					else
					{
						static_cast<PlayerInfo*>(peer->data)->FishPosX = 0;
						static_cast<PlayerInfo*>(peer->data)->FishPosY = 0;
						static_cast<PlayerInfo*>(peer->data)->Fishing = false;
						send_state(peer);
						Player::OnSetPos(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y);
					}
				}
				return;
			}
			if (static_cast<PlayerInfo*>(peer->data)->Fishing)
			{
				static_cast<PlayerInfo*>(peer->data)->FishPosX = 0;
				static_cast<PlayerInfo*>(peer->data)->FishPosY = 0;
				static_cast<PlayerInfo*>(peer->data)->Fishing = false;
				send_state(peer);
				Player::OnSetPos(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y);
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wSit perfectly while fishing`w!", 0, true);
				return;
			}
			if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3494)
			{
				if (world->owner == "" || static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || isMod(peer))
				{
					switch (tile)
					{
						case 3478:
						{
							if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::MAIN_DOOR || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 8)
							{
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That's too special to paint.", 0, false);
								return;
							}
							if (world->items[x + (y * world->width)].red && !world->items[x + (y * world->width)].green && !world->items[x + (y * world->width)].blue) {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That block is already painted that color!", 0, false);
								return;
							}
							if (world->items[x + (y * world->width)].foreground == 0 && world->items[x + (y * world->width)].background == 0) {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "There's nothing to paint!", 0, false);
								return;
							}
							RemoveInventoryItem(3478, 1, peer, true);
							if (world->items[x + (y * world->width)].foreground == 0 || isSeed(world->items[x + (y * world->width)].foreground)) {
								if (rand() % 100 <= 15) {
									DropItem(peer, -1, data.punchX * 32 + rand() % 18, data.punchY * 32 + rand() % 18, 3479, 1, 0);
								}
								else if (rand() % 100 <= 35) {
									SendFarmableDrop(peer, 5, data.punchX, data.punchY);
								}
							}
							world->items[x + (y * world->width)].red = true;
							world->items[x + (y * world->width)].green = false;
							world->items[x + (y * world->width)].blue = false;
							UpdateVisualsForBlock(peer, true, x, y, world);
							for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
								if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
								if (isHere(peer, net_peer)) {
									SendParticleEffect(net_peer, x * 32 + 16, y * 32 + 16, 1953289573, 168, 0);
								}
							}
							return;
						}
						case 3480:
						{
							if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::MAIN_DOOR || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 8)
							{
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That's too special to paint.", 0, false);
								return;
							}
							if (world->items[x + (y * world->width)].red && world->items[x + (y * world->width)].green && !world->items[x + (y * world->width)].blue) {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That block is already painted that color!", 0, false);
								return;
							}
							if (world->items[x + (y * world->width)].foreground == 0 && world->items[x + (y * world->width)].background == 0) {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "There's nothing to paint!", 0, false);
								return;
							}
							RemoveInventoryItem(3480, 1, peer, true);
							if (world->items[x + (y * world->width)].foreground == 0 || isSeed(world->items[x + (y * world->width)].foreground)) {
								if (rand() % 100 <= 15) {
									DropItem(peer, -1, data.punchX * 32 + rand() % 18, data.punchY * 32 + rand() % 18, 3481, 1, 0);
								}
								else if (rand() % 100 <= 35) {
									SendFarmableDrop(peer, 5, data.punchX, data.punchY);
								}
							}
							world->items[x + (y * world->width)].red = true;
							world->items[x + (y * world->width)].green = true;
							world->items[x + (y * world->width)].blue = false;
							UpdateVisualsForBlock(peer, true, x, y, world);
							for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
								if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
								if (isHere(peer, net_peer)) {
									SendParticleEffect(net_peer, x * 32 + 16, y * 32 + 16, 1153289573, 168, 0);
								}
							}
							return;
						}
						case 3482:
						{
							if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::MAIN_DOOR || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 8)
							{
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That's too special to paint.", 0, false);
								return;
							}
							if (!world->items[x + (y * world->width)].red && world->items[x + (y * world->width)].green && !world->items[x + (y * world->width)].blue) {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That block is already painted that color!", 0, false);
								return;
							}
							if (world->items[x + (y * world->width)].foreground == 0 && world->items[x + (y * world->width)].background == 0) {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "There's nothing to paint!", 0, false);
								return;
							}
							RemoveInventoryItem(3482, 1, peer, true);
							if (world->items[x + (y * world->width)].foreground == 0 || isSeed(world->items[x + (y * world->width)].foreground)) {
								if (rand() % 100 <= 15) {
									DropItem(peer, -1, data.punchX * 32 + rand() % 18, data.punchY * 32 + rand() % 18, 3483, 1, 0);
								}
								else if (rand() % 100 <= 35) {
									SendFarmableDrop(peer, 5, data.punchX, data.punchY);
								}
							}
							world->items[x + (y * world->width)].red = false;
							world->items[x + (y * world->width)].green = true;
							world->items[x + (y * world->width)].blue = false;
							UpdateVisualsForBlock(peer, true, x, y, world);
							for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
								if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
								if (isHere(peer, net_peer)) {
									SendParticleEffect(net_peer, x * 32 + 16, y * 32 + 16, 94634864, 168, 0);
								}
							}
							return;
						}
						case 3484:
						{
							if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::MAIN_DOOR || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 8)
							{
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That's too special to paint.", 0, false);
								return;
							}
							if (!world->items[x + (y * world->width)].red && world->items[x + (y * world->width)].green && world->items[x + (y * world->width)].blue) {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That block is already painted that color!", 0, false);
								return;
							}
							if (world->items[x + (y * world->width)].foreground == 0 && world->items[x + (y * world->width)].background == 0) {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "There's nothing to paint!", 0, false);
								return;
							}
							RemoveInventoryItem(3484, 1, peer, true);
							if (world->items[x + (y * world->width)].foreground == 0 || isSeed(world->items[x + (y * world->width)].foreground)) {
								if (rand() % 100 <= 15) {
									DropItem(peer, -1, data.punchX * 32 + rand() % 18, data.punchY * 32 + rand() % 18, 3485, 1, 0);
								}
								else if (rand() % 100 <= 35) {
									SendFarmableDrop(peer, 5, data.punchX, data.punchY);
								}
							}
							world->items[x + (y * world->width)].red = false;
							world->items[x + (y * world->width)].green = true;
							world->items[x + (y * world->width)].blue = true;
							UpdateVisualsForBlock(peer, true, x, y, world);
							for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
								if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
								if (isHere(peer, net_peer)) {
									SendParticleEffect(net_peer, x * 32 + 16, y * 32 + 16, 3253289573, 168, 0);
								}
							}
							return;
						}
						case 3486:
						{
							if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::MAIN_DOOR || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 8)
							{
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That's too special to paint.", 0, false);
								return;
							}
							if (!world->items[x + (y * world->width)].red && !world->items[x + (y * world->width)].green && world->items[x + (y * world->width)].blue) {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That block is already painted that color!", 0, false);
								return;
							}
							if (world->items[x + (y * world->width)].foreground == 0 && world->items[x + (y * world->width)].background == 0) {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "There's nothing to paint!", 0, false);
								return;
							}
							RemoveInventoryItem(3486, 1, peer, true);
							if (world->items[x + (y * world->width)].foreground == 0 || isSeed(world->items[x + (y * world->width)].foreground)) {
								if (rand() % 100 <= 15) {
									DropItem(peer, -1, data.punchX * 32 + rand() % 18, data.punchY * 32 + rand() % 18, 3486, 1, 0);
								}
								else if (rand() % 100 <= 35) {
									SendFarmableDrop(peer, 5, data.punchX, data.punchY);
								}
							}
							world->items[x + (y * world->width)].red = false;
							world->items[x + (y * world->width)].green = false;
							world->items[x + (y * world->width)].blue = true;
							UpdateVisualsForBlock(peer, true, x, y, world);
							for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
								if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
								if (isHere(peer, net_peer)) {
									SendParticleEffect(net_peer, x * 32 + 16, y * 32 + 16, 2553289573, 168, 0);
								}
							}
							return;
						}
						case 3488:
						{
							if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::MAIN_DOOR || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 8)
							{
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That's too special to paint.", 0, false);
								return;
							}
							if (world->items[x + (y * world->width)].red && !world->items[x + (y * world->width)].green && world->items[x + (y * world->width)].blue) {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That block is already painted that color!", 0, false);
								return;
							}
							if (world->items[x + (y * world->width)].foreground == 0 && world->items[x + (y * world->width)].background == 0) {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "There's nothing to paint!", 0, false);
								return;
							}
							RemoveInventoryItem(3488, 1, peer, true);
							if (world->items[x + (y * world->width)].foreground == 0 || isSeed(world->items[x + (y * world->width)].foreground)) {
								if (rand() % 100 <= 15) {
									DropItem(peer, -1, data.punchX * 32 + rand() % 18, data.punchY * 32 + rand() % 18, 3489, 1, 0);
								}
								else if (rand() % 100 <= 35) {
									SendFarmableDrop(peer, 5, data.punchX, data.punchY);
								}
							}
							world->items[x + (y * world->width)].red = true;
							world->items[x + (y * world->width)].green = false;
							world->items[x + (y * world->width)].blue = true;
							UpdateVisualsForBlock(peer, true, x, y, world);
							for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
								if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
								if (isHere(peer, net_peer)) {
									SendParticleEffect(net_peer, x * 32 + 16, y * 32 + 16, 3205873253, 168, 0);
								}
							}
							return;
						}
						case 3490:
						{
							if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::MAIN_DOOR || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 8)
							{
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That's too special to paint.", 0, false);
								return;
							}
							if (world->items[x + (y * world->width)].red && world->items[x + (y * world->width)].green && world->items[x + (y * world->width)].blue) {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That block is already painted that color!", 0, false);
								return;
							}
							if (world->items[x + (y * world->width)].foreground == 0 && world->items[x + (y * world->width)].background == 0) {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "There's nothing to paint!", 0, false);
								return;
							}
							RemoveInventoryItem(3490, 1, peer, true);
							if (world->items[x + (y * world->width)].foreground == 0 || isSeed(world->items[x + (y * world->width)].foreground)) {
								if (rand() % 100 <= 15) {
									DropItem(peer, -1, data.punchX * 32 + rand() % 18, data.punchY * 32 + rand() % 18, 3491, 1, 0);
								}
								else if (rand() % 100 <= 35) {
									SendFarmableDrop(peer, 5, data.punchX, data.punchY);
								}
							}
							world->items[x + (y * world->width)].red = true;
							world->items[x + (y * world->width)].green = true;
							world->items[x + (y * world->width)].blue = true;
							UpdateVisualsForBlock(peer, true, x, y, world);
							for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
								if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
								if (isHere(peer, net_peer)) {
									SendParticleEffect(net_peer, x * 32 + 16, y * 32 + 16, 0, 168, 0);
								}
							}
							return;
						}
						case 3492:
						{
							if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::MAIN_DOOR || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 8)
							{
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That's too special to paint.", 0, false);
								return;
							}
							if (!world->items[x + (y * world->width)].red && !world->items[x + (y * world->width)].green && !world->items[x + (y * world->width)].blue) {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Don't waste your varnish on an unpainted block!", 0, false);
								return;
							}
							if (world->items[x + (y * world->width)].foreground == 0 && world->items[x + (y * world->width)].background == 0) {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "There's nothing to paint!", 0, false);
								return;
							}
							RemoveInventoryItem(3492, 1, peer, true);
							if (world->items[x + (y * world->width)].foreground == 0 || isSeed(world->items[x + (y * world->width)].foreground)) {
								if (rand() % 100 <= 15) {
									DropItem(peer, -1, data.punchX * 32 + rand() % 18, data.punchY * 32 + rand() % 18, 3493, 1, 0);
								}
								else if (rand() % 100 <= 35) {
									SendFarmableDrop(peer, 5, data.punchX, data.punchY);
								}
							}
							world->items[x + (y * world->width)].red = false;
							world->items[x + (y * world->width)].green = false;
							world->items[x + (y * world->width)].blue = false;
							UpdateVisualsForBlock(peer, true, x, y, world);
							for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
								if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
								if (isHere(peer, net_peer)) {
									SendParticleEffect(net_peer, x * 32 + 16, y * 32 + 16, -1, 168, 0);
								}
							}
							return;
						}
						default: break;
					}
				}
			}
			bool hassmallock = false;
			for (int i = 0; i < world->width * world->height; i++) {
				if (world->items[i].foreground == 202 || world->items[i].foreground == 204 || world->items[i].foreground == 206 || world->items[i].foreground == 4994) {
					hassmallock = true;
					break;
				}
			}
			if (hassmallock && !isMod(peer) || world->owner != "" && !isWorldOwner(peer, world) && !isWorldAdmin(peer, world) && !isMod(peer)) {
				if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || isMod(peer) || tile == world->publicBlock || causedBy == -1 || tile == 5640 || hassmallock && !RestrictedArea(peer, world, x, y)) {

				}
				else if (isWorldAdmin(peer, world)) {
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK) {
						MYSQL_ROW row;
						string nickname, adminlevel;
						string q = "SELECT * FROM PlayerDatabase WHERE username = '" + world->owner + "' LIMIT 1";
						if (mysql_query(conn, q.c_str())) {
							cout << mysql_error(conn) << endl;
							enet_peer_disconnect_later(peer, 0);
							return;
						}
						res = mysql_store_result(conn);
						while (row = mysql_fetch_row(res)) {
							adminlevel = row[19];
							nickname = row[44];
						}
						if (nickname == "") {
							if (adminlevel == "1") {
								nickname = "`#@" + world->owner;
							} else if (adminlevel == "2") {
								nickname = "`6@" + world->owner;
							} else {
								nickname = world->owner;
							}
						} 
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`2Access Granted`w)", 0, true);
						Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
						return;
					}
				} else if (world->isPublic) {
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK) {
						MYSQL_ROW row;
						string nickname, adminlevel;
						string q = "SELECT * FROM PlayerDatabase WHERE username = '" + world->owner + "' LIMIT 1";
						if (mysql_query(conn, q.c_str())) {
							cout << mysql_error(conn) << endl;
							enet_peer_disconnect_later(peer, 0);
							return;
						}
						res = mysql_store_result(conn);
						while (row = mysql_fetch_row(res)) {
							adminlevel = row[19];
							nickname = row[44];
						}
						if (nickname == "") {
							if (adminlevel == "1") {
								nickname = "`#@" + world->owner;
							} else if (adminlevel == "2") {
								nickname = "`6@" + world->owner;
							} else {
								nickname = world->owner;
							}
						} 
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
						Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
						return;
					}
				} else if (world->isEvent) {
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK) {
						string whoslock = world->owner;
						if (world->items[x + (y * world->width)].foreground == 202 || world->items[x + (y * world->width)].foreground == 204 || world->items[x + (y * world->width)].foreground == 206 || world->items[x + (y * world->width)].foreground == 4994) {
							whoslock = world->items[x + (y * world->width)].monitorname;
						}
						if (static_cast<PlayerInfo*>(peer->data)->rawName != whoslock) {
						MYSQL_ROW row;
						string nickname, adminlevel;
						string q = "SELECT * FROM PlayerDatabase WHERE username = '" + whoslock + "' LIMIT 1";
						if (mysql_query(conn, q.c_str())) {
							cout << mysql_error(conn) << endl;
							enet_peer_disconnect_later(peer, 0);
							return;
						}
						res = mysql_store_result(conn);
						while (row = mysql_fetch_row(res)) {
							adminlevel = row[19];
							nickname = row[44];
						}
						if (nickname == "") {
							if (adminlevel == "1") {
								nickname = "`#@" + whoslock;
							} else if (adminlevel == "2") {
								nickname = "`6@" + whoslock;
							} else {
								nickname = whoslock;
							}
						}  
						if (world->items[x + (y * world->width)].opened) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
						else Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`4No Access`w)", 0, true);
						Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
						return;
						}
					} else if (world->items[x + (y * world->width)].foreground != world->publicBlock && causedBy != -1) {
						Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
						return;
					}
				} else {
					Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
					return;
				}
				if (tile == 18 && isMod(peer)) {
					if (isWorldAdmin(peer, world) && !isWorldOwner(peer, world)) {
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK) {
							MYSQL_ROW row;
							string nickname, adminlevel;
							string q = "SELECT * FROM PlayerDatabase WHERE username = '" + world->owner + "' LIMIT 1";
							if (mysql_query(conn, q.c_str())) {
								cout << mysql_error(conn) << endl;
								enet_peer_disconnect_later(peer, 0);
								return;
							}
							res = mysql_store_result(conn);
							while (row = mysql_fetch_row(res)) {
								adminlevel = row[19];
								nickname = row[44];
							}
							if (nickname == "") {
								if (adminlevel == "1") {
									nickname = "`#@" + world->owner;
								} else if (adminlevel == "2") {
									nickname = "`6@" + world->owner;
								} else {
									nickname = world->owner;
								}
							} 
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`2Access Granted`w)", 0, true);
						}
					} else if (world->isPublic && !isWorldOwner(peer, world) || world->items[x + (y * world->width)].foreground == 202 && world->items[x + (y * world->width)].opened || world->items[x + (y * world->width)].foreground == 204 && world->items[x + (y * world->width)].opened || world->items[x + (y * world->width)].foreground == 206 && world->items[x + (y * world->width)].opened || world->items[x + (y * world->width)].foreground == 4994 && world->items[x + (y * world->width)].opened) {
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK) {
							MYSQL_ROW row;
							string nickname, adminlevel;
							string q = "SELECT * FROM PlayerDatabase WHERE username = '" + world->owner + "' LIMIT 1";
							if (mysql_query(conn, q.c_str())) {
								cout << mysql_error(conn) << endl;
								enet_peer_disconnect_later(peer, 0);
								return;
							}
							res = mysql_store_result(conn);
							while (row = mysql_fetch_row(res)) {
								adminlevel = row[19];
								nickname = row[44];
							}
							if (nickname == "") {
								if (adminlevel == "1") {
									nickname = "`#@" + world->owner;
								} else if (adminlevel == "2") {
									nickname = "`6@" + world->owner;
								} else {
									nickname = world->owner;
								}
							} 
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
						}
					} else if (world->isEvent && !isWorldOwner(peer, world) || world->items[x + (y * world->width)].foreground == 202 || world->items[x + (y * world->width)].foreground == 204 || world->items[x + (y * world->width)].foreground == 206 || world->items[x + (y * world->width)].foreground == 4994) {
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK) {
							string whoslock = world->owner;
							if (world->items[x + (y * world->width)].foreground == 202 || world->items[x + (y * world->width)].foreground == 204 || world->items[x + (y * world->width)].foreground == 206 || world->items[x + (y * world->width)].foreground == 4994) {
								whoslock = world->items[x + (y * world->width)].monitorname;
							}
							if (static_cast<PlayerInfo*>(peer->data)->rawName != whoslock) {
							MYSQL_ROW row;
							string nickname, adminlevel;
							string q = "SELECT * FROM PlayerDatabase WHERE username = '" + whoslock + "' LIMIT 1";
							if (mysql_query(conn, q.c_str())) {
								cout << mysql_error(conn) << endl;
								enet_peer_disconnect_later(peer, 0);
								return;
							}
							res = mysql_store_result(conn);
							while (row = mysql_fetch_row(res)) {
								adminlevel = row[19];
								nickname = row[44];
							}
							if (nickname == "") {
								if (adminlevel == "1") {
									nickname = "`#@" + whoslock;
								} else if (adminlevel == "2") {
									nickname = "`6@" + whoslock;
								} else {
									nickname = whoslock;
								}
							} 
							if (world->items[x + (y * world->width)].opened) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
							else Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + nickname + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`4No Access`w)", 0, true);
							}
						}
					}
				}
			}
			if (world->items[x + (y * world->width)].foreground == 10 && tile == 3400)
			{
				if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || isMod(peer) || world->owner == "")
				{
					RemoveInventoryItem(3400, 1, peer, true);
					world->items[x + (y * world->width)].foreground = 392;
					PlayerMoving data3;
					data3.packetType = 0x3;
					data3.characterState = 0x0;
					data3.x = x;
					data3.y = y;
					data3.punchX = x;
					data3.punchY = y;
					data3.XSpeed = 0;
					data3.YSpeed = 0;
					data3.netID = -1;
					data3.plantingTree = 392;
					ENetPeer* currentPeer;
					for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
					{
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, currentPeer))
						{
							auto raw = packPlayerMoving(&data3);
							raw[2] = dicenr;
							raw[3] = dicenr;
							SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
						}
					}
					for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
					{
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						Player::OnParticleEffect(currentPeer, 44, x * 32, y * 32, 0);
					}
				}
			}

			if (isSeed(world->items[x + (y * world->width)].foreground) && tile == 228 || isSeed(world->items[x + (y * world->width)].foreground) && tile == 1778) {
					if (calcBanDuration(world->items[x + (y * world->width)].growtime) == 0) {
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "This tree has already bloomed, don't waste your spray on it!", 0, true);
						return;
					}
				 	int NewGrowTime = 0;
					int InternalGrowTime = 0;
					if (tile == 228) {
						NewGrowTime = calcBanDuration(world->items[x + (y * world->width)].growtime) - 3600;
						RemoveInventoryItem(228, 1, peer, true);
					}
					if (tile == 1778) {
						NewGrowTime = calcBanDuration(world->items[x + (y * world->width)].growtime) - 86400;
						RemoveInventoryItem(1778, 1, peer, true);
					}
					if (NewGrowTime < 0) NewGrowTime = 0;
					world->items[x + (y * world->width)].growtime = (GetCurrentTimeInternalSeconds() + NewGrowTime);	
					int growTimeSeed = getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity;
					growTimeSeed += 30 * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity;
					if (world->items[x + (y * world->width)].foreground - 1 == 954) growTimeSeed = 1800;
					if (world->items[x + (y * world->width)].foreground - 1 == 340) growTimeSeed = 3600;
					if (world->items[x + (y * world->width)].foreground - 1 == 5666) growTimeSeed = 2700;
					if (world->items[x + (y * world->width)].foreground - 1 == 4584) growTimeSeed = 2400;
					if (world->items[x + (y * world->width)].foreground - 1 == 4762) growTimeSeed = 14544;
					if (world->items[x + (y * world->width)].foreground - 1 == 7382) growTimeSeed = 22544;
					if (world->items[x + (y * world->width)].foreground - 1 == 9460) growTimeSeed = 29544;
					if (world->items[x + (y * world->width)].foreground - 1 == 9468) growTimeSeed = 36544;
					if (world->items[x + (y * world->width)].foreground - 1 == 10024) growTimeSeed = 56544;
					if (world->items[x + (y * world->width)].foreground - 1 == 10028) growTimeSeed = 86400;
					InternalGrowTime = growTimeSeed - calcBanDuration(world->items[x + (y * world->width)].growtime);
					UpdateTreeVisuals(peer, world->items[x + (y * world->width)].foreground, x, y, world->items[x + (y * world->width)].background, world->items[x + (y * world->width)].fruitcount, InternalGrowTime, true, 0);
					if (calcBanDuration(world->items[x + (y * world->width)].growtime) == 0) { 
						Player::OnTextOverlay(peer, "" + getItemDef(world->items[x + (y * world->width)].foreground - 1).name + " Tree grew to full size!");
					}
					else if (tile == 228) {
						Player::OnTextOverlay(peer, "" + getItemDef(world->items[x + (y * world->width)].foreground - 1).name + " Tree aged `$1`` hours");
					}
					else if (tile == 1778) {
						Player::OnTextOverlay(peer, "" + getItemDef(world->items[x + (y * world->width)].foreground - 1).name + " Tree aged `$1`` day");
					}
					Player::PlayAudio(peer, "audio/spray.wav", 0);
					return;
			}
			if (world->items[x + (y * world->width)].foreground == 2946 && tile != 18 && tile != 32 && tile > 0)
			{
				if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || isMod(peer))
				{
					using namespace std::chrono;
					if (static_cast<PlayerInfo*>(peer->data)->lastDISPLAY + 1000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
					{
						static_cast<PlayerInfo*>(peer->data)->lastDISPLAY = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
						auto iscontains = false;
						SearchInventoryItem(peer, tile, 1, iscontains);
						if (!iscontains) return;
						else
						{
							auto xSize = world->width;
							auto ySize = world->height;
								auto n = tile;
								if (getItemDef(n).properties & Property_Untradable || n == 6336 || n == 8552 || n == 9472 || n == 5640 || n == 9482 || n == 9356 || n == 9492 || n == 9498 || n == 8774 || n == 1790 || n == 2592 || n == 1784 || n == 1792 || n == 1794 || n == 7734 || n == 8306 || n == 9458)
								{
									Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You can't display untradeable items.", 0, true);
									return;
								}
								if (getItemDef(n).blockType == BlockTypes::LOCK || n == 2946)
								{
									Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Sorry, no displaying Display Blocks or Locks.", 0, true);
									return;
								}
								if (world->items[x + (y * world->width)].intdata == 0)
								{
									world->items[x + (y * world->width)].intdata = tile;
									ENetPeer* currentPeer;
									for (currentPeer = server->peers;
										currentPeer < &server->peers[server->peerCount];
										++currentPeer)
									{
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
										if (isHere(peer, currentPeer))
										{
											UpdateVisualsForBlock(currentPeer, true, x, y, world);
											SendThrowEffect(currentPeer, tile, static_cast<PlayerInfo*>(peer->data)->netID, -1, 150, 0, x * 32 + 16, y * 32 + 16);
										}
									}
									RemoveInventoryItem(n, 1, peer, true);
									updateplayerset(peer, n);
								}
								else
								{
									Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Remove what's in there first!", 0, true);
								}
								return;
						}
					}
					else
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Slow down while using display blocks!", 0, true);;
						return;
					}
				}
				else
				{
					if (world->owner == "")
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "This area must be locked to put your item on display!", 0, true);
					}
					else if (world->isPublic)
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That area is owned by " + world->owner + "", 0, true);
					}
					else
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That area is owned by " + world->owner + "", 0, true);
					}
					return;
				}
			}
			if (world->items[x + (y * world->width)].foreground == 3528 && tile != 18 && tile != 32 && tile > 0)
			{
				if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || isMod(peer))
				{
					auto iscontains = false;
					SearchInventoryItem(peer, tile, 1, iscontains);
					if (!iscontains) return;
					else
					{
						auto xSize = world->width;
						auto ySize = world->height;
						if (xSize == 100 && ySize == 60)
						{
							auto n = tile;
							world->items[x + (y * world->width)].intdata = tile;
							ENetPeer* currentPeer;
							for (currentPeer = server->peers;
								currentPeer < &server->peers[server->peerCount];
								++currentPeer)
							{
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
								if (isHere(peer, currentPeer))
								{
									SendCanvasData(peer, world->items[x + (y * world->width)].foreground, world->items[x + (y * world->width)].background, x, y, tile, getItemDef(tile).name);
									SendThrowEffect(currentPeer, tile, static_cast<PlayerInfo*>(peer->data)->netID, -1, 150, 0, x * 32 + 16, y * 32 + 16);
								}
							}
							return;
						}
						else
						{
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Painting easels cannot be used in uranus worlds!", 0, true);
							return;
						}
					}
				}
				else
				{
					if (world->owner == "")
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "This area must be locked to put your item on display!", 0, true);
					}
					else if (world->isPublic)
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That area is owned by " + world->owner + "", 0, true);
					}
					else
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That area is owned by " + world->owner + "", 0, true);
					}
					return;
				}
			}
			if (getItemDef(tile).blockType == BlockTypes::CONSUMABLE || getItemDef(tile).blockType == BlockTypes::CLOTHING) return;		
			break;
		}
	}
	if (causedBy != -1)
	{
		if (!isDev(peer))
		{
			auto iscontains = false;
			SearchInventoryItem(peer, tile, 1, iscontains);
			if (!iscontains) return;
		}
	}
	ENetPeer* currentPeer;
	if (tile == 18) {
		if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3066 && tile == 18) return;
		if (world->items[x + (y * world->width)].background == 6864 && world->items[x + (y * world->width)].foreground == 0) return;
		if (world->items[x + (y * world->width)].background == 0 && world->items[x + (y * world->width)].foreground == 0) return;
		if (world->items[x + (y * world->width)].fire) return;
		ItemDefinition brak;
		if (world->items[x + (y * world->width)].foreground != 0) {
			brak = getItemDef(world->items[x + (y * world->width)].foreground);
		} else {
			brak = getItemDef(world->items[x + (y * world->width)].background);
		}
		data.packetType = 0x8;
		data.plantingTree = 6;
		using namespace std::chrono;
		if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 2952 && tile == 18) {
			if (isWorldOwner(peer, world) || isMod(peer) || world->isPublic || world->owner == "") {
				int kek = world->items[x + (y * world->width)].foreground;
				if (world->items[x + (y * world->width)].foreground != 0) kek = world->items[x + (y * world->width)].foreground;
				else kek = world->items[x + (y * world->width)].background;
				for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
					if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, net_peer)) {
						SendParticleEffect(net_peer, x * 32 + 16, y * 32, kek, 97, 0);
					}
				}
			}
		}
		bool EarthMastery = false;
		int ChanceOfEarth = 0;
		if (static_cast<PlayerInfo*>(peer->data)->level >= 4) ChanceOfEarth = 1;
		if (static_cast<PlayerInfo*>(peer->data)->level >= 6) ChanceOfEarth = 2;
		if (static_cast<PlayerInfo*>(peer->data)->level >= 8) ChanceOfEarth = 3;
		if (world->items[x + (y * world->width)].foreground == 2 && tile == 18 && rand() % 100 <= ChanceOfEarth && static_cast<PlayerInfo*>(peer->data)->level >= 4) {
			if (isWorldOwner(peer, world) || isMod(peer) || world->isPublic || world->owner == "") {
				EarthMastery = true;
				int kek = world->items[x + (y * world->width)].foreground;
				if (world->items[x + (y * world->width)].foreground != 0) kek = world->items[x + (y * world->width)].foreground;
				else kek = world->items[x + (y * world->width)].background;
				for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
					if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, net_peer)) {
						SendParticleEffect(net_peer, x * 32 + 16, y * 32, kek, 97, 0);
					}
				}
			}
		}
		if (static_cast<PlayerInfo*>(peer->data)->PunchPotion && tile == 18 || static_cast<PlayerInfo*>(peer->data)->cloth_necklace == 6260 && tile == 18) {
			if (isWorldOwner(peer, world) || isMod(peer) || world->isPublic || world->owner == "") {
				int kek = world->items[x + (y * world->width)].foreground;
				if (world->items[x + (y * world->width)].foreground != 0) kek = world->items[x + (y * world->width)].foreground;
				else kek = world->items[x + (y * world->width)].background;
				for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
					if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, net_peer)) {
						SendParticleEffect(net_peer, x * 32 + 16, y * 32, kek, 97, 0);
					}
				}
			}
		}
		if ((duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count() - world->items[x + (y * world->width)].breakTime >= 4000 && !EarthMastery && !static_cast<PlayerInfo*>(peer->data)->PunchPotion && static_cast<PlayerInfo*>(peer->data)->cloth_necklace != 6260 && static_cast<PlayerInfo*>(peer->data)->cloth_hand != 2952) {
			world->items[x + (y * world->width)].breakTime = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
			world->items[x + (y * world->width)].breakLevel = 4;
		} else { 
			if (isPickaxe(peer)) brak.breakHits -= 1;
			if (y < world->height && world->items[x + (y * world->width)].breakLevel + 4 >= brak.breakHits * 4 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 2952 && tile == 18 || EarthMastery && tile == 18 || static_cast<PlayerInfo*>(peer->data)->PunchPotion && tile == 18 || static_cast<PlayerInfo*>(peer->data)->cloth_necklace == 6260 && tile == 18) {
			data.packetType = 0x3;
			data.netID = causedBy;
			data.plantingTree = 18;
			data.punchX = x;
			data.punchY = y;
			world->items[x + (y * world->width)].breakLevel = 0;
			auto hi = data.punchX * 32;
			auto hi2 = data.punchY * 32;
			if (world->items[x + (y * world->width)].foreground == 10024) {
				std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4426 };
				int index = rand() % list.size();
				auto value = list[index];
				if (value == 4426) {
					srand(GetTickCount());
					auto droploc = rand() % 18;
					auto droplocs = rand() % 18;
					DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 4426, 1, 0);
				}
			}
			else if (world->items[x + (y * world->width)].foreground == 9460) {
				std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2410 };
				int index = rand() % list.size(); // pick a random index
				int value = list[index];
				if (value == 2410) {
					bool success = true;
					srand(GetTickCount());
					int droploc = rand() % 18;
					int droplocs = rand() % 18;
					DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 2410, 1, 0);
					int hi = data.punchX * 32;
					int hi2 = data.punchY * 32;
				}
			}
			else if (world->items[x + (y * world->width)].foreground == 3402 || world->items[x + (y * world->width)].foreground == 392 || world->items[x + (y * world->width)].foreground == 9350) {
				if (world->items[x + (y * world->width)].foreground == 3402) static_cast<PlayerInfo*>(peer->data)->bootybreaken++;
				if (static_cast<PlayerInfo*>(peer->data)->bootybreaken >= 30) {
					static_cast<PlayerInfo*>(peer->data)->bootybreaken = 0;
					bool success = true;
					SaveItemMoreTimes(9350, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
					SendTradeEffect(peer, 9350, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
				}
				vector<int> list{ 362, 3398, 386, 4422, 364, 9340, 9342, 9332, 9334, 9336, 9338, 366, 2388, 7808, 7810, 4416, 7818, 7820, 5652, 7822, 7824, 5644, 390, 7826, 7830, 9324, 5658, 3396, 2384, 5660, 3400, 4418, 4412, 388, 3408, 1470, 3404, 3406, 2390, 5656, 5648, 2396, 384, 5664, 4424, 4400, 1458 };
				int itemid = list[rand() % list.size()];
				if (itemid == 1458) { 
					int target = 5;
					if (world->items[x + (y * world->width)].foreground == 9350) target = 10;
					if ((rand() % 10000) <= target) { }
					else itemid = 7808;
				}
				DropItem(peer, -1, x * 32 + rand() % 18, y * 32 + rand() % 18, itemid, 1, 0);
			}
			else if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 8452) {
				Player::OnParticleEffect(peer, 149, data.punchX * 32, data.punchY * 32, 0);
			}
			if (world->items[x + (y * world->width)].foreground != 0) {
				if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::DOOR) {
					if (isWorldOwner(peer, world) || world->owner == "" || isMod(peer)) {
						world->items[x + (y * world->width)].label = "";
						world->items[x + (y * world->width)].destWorld = "";
						world->items[x + (y * world->width)].destId = "";
						world->items[x + (y * world->width)].currId = "";
						world->items[x + (y * world->width)].password = "";
					}
				}
				if (world->items[x + (y * world->width)].foreground == 10026) {
					int itemid = rand() % maxItems;
					if (getItemDef(itemid).name.find("null_item") != string::npos) itemid = 10026;
					if (getItemDef(itemid).name.find("Subscription") != string::npos) itemid = 10026;
					if (itemid % 2 == 0) {
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "The power of the dark stone dropped " + getItemDef(itemid).name + "!", 0, true);
						DropItem(peer, -1, x * 32 + rand() % 18, y * 32 + rand() % 18, itemid, 1, 0);
						int x1 = data.punchX * 32;
						int y1 = data.punchY * 32;
						for (ENetPeer* peer2 = server->peers; peer2 < &server->peers[server->peerCount]; ++peer2) {
							if (peer2->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, peer2)) {
								Player::OnParticleEffect(peer2, 182, x1, y1, 0);
							}
						}
					} else {
						itemid += 1;
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "The power of the dark stone dropped " + getItemDef(itemid).name + "!", 0, true);
						DropItem(peer, -1, x * 32 + rand() % 18, y * 32 + rand() % 18, itemid, 1, 0);
						for (ENetPeer* peer2 = server->peers; peer2 < &server->peers[server->peerCount]; ++peer2) {
							if (peer2->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, peer2)) {
								Player::OnParticleEffect(peer2, 182, data.punchX * 32, data.punchY * 32, 0);
							}
						}
					}
				}
				if (world->items[x + (y * world->width)].foreground == 10402) {
					if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3932) {
						if ((rand() % 100) <= 50) {
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wThe Rock was so hard to break that it broke your Rock Hammer!", 0, true);
							RemoveInventoryItem(3932, 1, peer, true);
							auto iscontains = false;
							SearchInventoryItem(peer, 3932, 1, iscontains);
							if (!iscontains) {
								static_cast<PlayerInfo*>(peer->data)->cloth_hand = 0;
								Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
								static_cast<PlayerInfo*>(peer->data)->effect = 8421376;
								sendPuncheffect(peer, static_cast<PlayerInfo*>(peer->data)->effect);
								send_state(peer); //here
								sendClothes(peer);
							}
						}
						SendXP(peer, 30);
						SendParticleEffect(peer, x * 32 + 16, y * 32 + 16, 3, 114, 0);
						DropItem(peer, -1, x * 32 + rand() % 18, y * 32 + rand() % 18, 10412, 1, 0);
					}
					SendFarmableDrop(peer, 5, x, y);
				}
				if (world->items[x + (y * world->width)].foreground == 10404) {
					if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3932) {
						if ((rand() % 100) <= 50) {
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wThe Rock was so hard to break that it broke your Rock Hammer!", 0, true);
							RemoveInventoryItem(3932, 1, peer, true);
							auto iscontains = false;
							SearchInventoryItem(peer, 3932, 1, iscontains);
							if (!iscontains) {
								static_cast<PlayerInfo*>(peer->data)->cloth_hand = 0;
								Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
								static_cast<PlayerInfo*>(peer->data)->effect = 8421376;
								sendPuncheffect(peer, static_cast<PlayerInfo*>(peer->data)->effect);
								send_state(peer); //here
								sendClothes(peer);
							}
						}
						SendXP(peer, 30);
						SendParticleEffect(peer, x * 32 + 16, y * 32 + 16, 3, 114, 0);
						DropItem(peer, -1, x * 32 + rand() % 18, y * 32 + rand() % 18, 10414, 1, 0);
					}
					SendFarmableDrop(peer, 5, x, y);
				}
				if (world->items[x + (y * world->width)].foreground == 10406) {
					if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3932) {
						if ((rand() % 100) <= 50) {
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wThe Rock was so hard to break that it broke your Rock Hammer!", 0, true);
							RemoveInventoryItem(3932, 1, peer, true);
							auto iscontains = false;
							SearchInventoryItem(peer, 3932, 1, iscontains);
							if (!iscontains) {
								static_cast<PlayerInfo*>(peer->data)->cloth_hand = 0;
								Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
								static_cast<PlayerInfo*>(peer->data)->effect = 8421376;
								sendPuncheffect(peer, static_cast<PlayerInfo*>(peer->data)->effect);
								send_state(peer); //here
								sendClothes(peer);
							}
						}
						SendXP(peer, 30);
						SendParticleEffect(peer, x * 32 + 16, y * 32 + 16, 3, 114, 0);
						DropItem(peer, -1, x * 32 + rand() % 18, y * 32 + rand() % 18, 10416, 1, 0);
					}
					SendFarmableDrop(peer, 5, x, y);
					world->items[x + (y * world->width)].fire = true;
					if (y + 1 <= 100) world->items[x + 1 + (y * world->width)].fire = true;
					if (x - 1 >= 0) world->items[x - 1 + (y * world->width)].fire = true;
					if (y - 1 >= 0) world->items[x + (y * world->width - 100)].fire = true;
					if (y + 1 <= 60) world->items[x + (y * world->width + 100)].fire = true;
					UpdateVisualsForBlock(peer, true, x, y, world);
					if (y + 1 <= 100) UpdateVisualsForBlock(peer, true, x + 1, y, world);
					if (x - 1 >= 0) UpdateVisualsForBlock(peer, true, x - 1, y, world);
					if (y - 1 >= 0) UpdateVisualsForBlock(peer, true, x, y - 1, world);
					if (y + 1 <= 60) UpdateVisualsForBlock(peer, true, x, y + 1, world);
				}
				if (world->items[x + (y * world->width)].foreground == 10408) {
					if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3932) {
						if ((rand() % 100) <= 50) {
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wThe Rock was so hard to break that it broke your Rock Hammer!", 0, true);
							RemoveInventoryItem(3932, 1, peer, true);
							auto iscontains = false;
							SearchInventoryItem(peer, 3932, 1, iscontains);
							if (!iscontains) {
								static_cast<PlayerInfo*>(peer->data)->cloth_hand = 0;
								Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
								static_cast<PlayerInfo*>(peer->data)->effect = 8421376;
								sendPuncheffect(peer, static_cast<PlayerInfo*>(peer->data)->effect);
								send_state(peer); //here
								sendClothes(peer);
							}
						}
						SendXP(peer, 30);
						SendParticleEffect(peer, x * 32 + 16, y * 32 + 16, 3, 114, 0);
						DropItem(peer, -1, x * 32 + rand() % 18, y * 32 + rand() % 18, 10410, 1, 0);
					}
					SendFarmableDrop(peer, 5, x, y);
				}
				if (world->items[x + (y * world->width)].foreground == 4762)
				{ /*amethyst*/
					SendFarmableDrop(peer, 10, x, y);
					//SendGuildPoints(peer, 1);
					SendXP(peer, 2);
					//SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
				}
				if (world->items[x + (y * world->width)].foreground == 7382)
				{ /*Onyx*/
					SendFarmableDrop(peer, 20, x, y);
					//SendGuildPoints(peer, 2);
					SendXP(peer, 2);
					//SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
				}
				if (world->items[x + (y * world->width)].foreground == 9468)
				{ /*Diamondstone*/
					SendFarmableDrop(peer, 40, x, y);
					//SendGuildPoints(peer, 5);
					SendXP(peer, 10);
					//SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
				}
				if (world->items[x + (y * world->width)].foreground == 10024)
				{ /*Pinkdiamond*/
					SendFarmableDrop(peer, 50, x, y);
					//SendGuildPoints(peer, 7);
					SendXP(peer, 10);
					//SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
				}
				if (world->items[x + (y * world->width)].foreground == 10028)
				{ /*Citrine*/
					SendFarmableDrop(peer, 60, x, y);
					//SendGuildPoints(peer, 10);
					SendXP(peer, 15);
					//SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
				}
				if (world->items[x + (y * world->width)].foreground == 9460)
				{ /*Smaraged*/
					SendFarmableDrop(peer, 30, x, y);
					//SendGuildPoints(peer, 3);
					SendXP(peer, 5);
					//SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
				}
				if (world->items[x + (y * world->width)].foreground == 1420 || world->items[x + (y * world->width)].foreground == 6214) {
					auto squaresign = x + (y * world->width);
					auto ismannequin = std::experimental::filesystem::exists("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					if (ismannequin) {
						remove(("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
					}
					world->items[x + (y * world->width)].sign = "";
				} 
				if (world->items[x + (y * world->width)].foreground == 656) {
					auto squaresign = x + (y * world->width);
					auto isdbox = std::experimental::filesystem::exists("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					if (isdbox) {
						ifstream ifff("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();
						int count = j["inmail"];
						if (j["inmail"] > 0) {
							Player::OnTextOverlay(peer, "`wThere are `5" + to_string(count) + " `wletter(s) in the mailbox.");
						}
						remove(("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
					}
				} 
				if (world->items[x + (y * world->width)].foreground == 658) {
					auto squaresign = x + (y * world->width);
					auto isdbox = std::experimental::filesystem::exists("bulletinboard/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					if (isdbox) {
						remove(("bulletinboard/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
					}
				} 
				if (world->items[x + (y * world->width)].foreground == 1006) {
					auto squaresign = x + (y * world->width);
					auto isdbox = std::experimental::filesystem::exists("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					if (isdbox) {
						ifstream ifff("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();
						int count = j["inmail"];
						if (j["inmail"] > 0) {
							Player::OnTextOverlay(peer, "`wThere are `5" + to_string(count) + " `wletter(s) in the mailbox.");
						}
						remove(("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
					}
				}
				if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::DONATION) {
					auto squaresign = x + (y * world->width);
					auto isdbox = std::experimental::filesystem::exists("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					if (isdbox) {
						ifstream ifff("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();
						if (j["donated"] > 0) {
							Player::OnTextOverlay(peer, "Empty donation box first!");
							return;
						}
						remove(("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
					}
				}
				if (world->items[x + (y * world->width)].foreground == 1240) {
					world->items[x + (y * world->width)].monitorname = "";
					world->items[x + (y * world->width)].monitoronline = false;
				} 
				if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::GATEWAY) {
					world->items[x + (y * world->width)].opened = false;
				}
				if (getItemDef(world->items[x + (y * world->width)].foreground).properties & Property_AutoPickup) {
					bool SuccessBreak = false;
					if (world->items[x + (y * world->width)].foreground == 2978) {
						if (world->items[x + (y * world->width)].vcount != 0 || world->items[x + (y * world->width)].vdraw != 0) {
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Empty the machine before breaking it!", 0, true);
							return;
						}
						world->items[x + (y * world->width)].vcount = 0;
						world->items[x + (y * world->width)].vprice = 0;
						world->items[x + (y * world->width)].vid = 0;
						world->items[x + (y * world->width)].vdraw = 0;
						world->items[x + (y * world->width)].opened = false;
						world->items[x + (y * world->width)].rm = false;
						auto success = true;
						SaveItemMoreTimes(2978, 1, peer, success);
					} else if (world->items[x + (y * world->width)].foreground == 6286) {
						auto squaresign = x + (y * world->width);
						auto isdbox = std::experimental::filesystem::exists("storageboxlvl1/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						if (isdbox) {
							ifstream ifff("storageboxlvl1/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							json j;
							ifff >> j;
							ifff.close();
							if (j["instorage"] > 0) {
								Player::OnTextOverlay(peer, "Empty the box first!");
								return;
							}
							remove(("storageboxlvl1/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
						}
						bool success = true;
						SaveItemMoreTimes(6286, 1, peer, success);
					} else if (world->items[x + (y * world->width)].foreground == 6288) {
						auto squaresign = x + (y * world->width);
						auto isdbox = std::experimental::filesystem::exists("storageboxlvl2/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						if (isdbox) {
							ifstream ifff("storageboxlvl2/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							json j;
							ifff >> j;
							ifff.close();
							if (j["instorage"] > 0) {
								Player::OnTextOverlay(peer, "Empty the box first!");
								return;
							}
							remove(("storageboxlvl2/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
						}
						bool success = true;
						SaveItemMoreTimes(6288, 1, peer, success);
					} else if (world->items[x + (y * world->width)].foreground == 6290) {
						auto squaresign = x + (y * world->width);
						auto isdbox = std::experimental::filesystem::exists("storageboxlvl3/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						if (isdbox) {
							ifstream ifff("storageboxlvl3/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							json j;
							ifff >> j;
							ifff.close();
							if (j["instorage"] > 0) {
								Player::OnTextOverlay(peer, "Empty the box first!");
								return;
							}
							remove(("storageboxlvl3/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
						}
						bool success = true;
						SaveItemMoreTimes(6290, 1, peer, success);
					} else if (world->items[x + (y * world->width)].foreground == 8878) {
						auto squaresign = x + (y * world->width);
						auto isdbox = std::experimental::filesystem::exists("safevault/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						if (isdbox) {
							ifstream ifff("safevault/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							json j;
							ifff >> j;
							ifff.close();
							if (j["insafe"] > 0) {
								Player::OnTextOverlay(peer, "Empty the safe first!");
								return;
							}
							remove(("safevault/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
						}
						bool success = true;
						SaveItemMoreTimes(8878, 1, peer, success);
					} else if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK) {
						if (world->items[x + (y * world->width)].foreground == 202 || world->items[x + (y * world->width)].foreground == 204 || world->items[x + (y * world->width)].foreground == 206 || world->items[x + (y * world->width)].foreground == 4994) {
							world->items[x + (y * world->width)].monitorname = "";
							world->items[x + (y * world->width)].opened = false;
							auto success = true;
							SaveItemMoreTimes(world->items[x + (y * world->width)].foreground, 1, peer, success);
							for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
								if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
								if (isHere(peer, net_peer)) {
									Player::PlayAudio(net_peer, "audio/metal_destroy.wav", 0);
								}
							}
						} else {
							for (auto i = 0; i < world->width * world->height; i++) {
								if (getItemDef(world->items[i].foreground).properties & Property_Untradable && world->items[i].foreground != 0) {
									Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Take all untradeable blocks before breaking the " + getItemDef(world->items[x + (y * world->width)].foreground).name + "", 0, true);
									return;
								}
							}
							if (static_cast<PlayerInfo*>(peer->data)->NickPrefix == "") updateworldremove(peer);
							auto success = true;
							auto nameworld = world->name;
							SaveItemMoreTimes(world->items[x + (y * world->width)].foreground, 1, peer, success);
							for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
								if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
								if (isHere(peer, net_peer)) {
									Player::OnConsoleMessage(net_peer, "`5[`w" + nameworld + " `ohas had its `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + " `oremoved!`5]");
									Player::PlayAudio(net_peer, "audio/metal_destroy.wav", 0);
								}
							} if (world->owner != static_cast<PlayerInfo*>(peer->data)->rawName) {
								bool PlayerFound = false;
								for (ENetPeer* net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer) {
									if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
									if (world->owner == static_cast<PlayerInfo*>(net_peer->data)->rawName) {
										PlayerFound = true;
										static_cast<PlayerInfo*>(net_peer->data)->worldsowned.erase(std::remove(static_cast<PlayerInfo*>(net_peer->data)->worldsowned.begin(), static_cast<PlayerInfo*>(net_peer->data)->worldsowned.end(), static_cast<PlayerInfo*>(net_peer->data)->currentWorld), static_cast<PlayerInfo*>(net_peer->data)->worldsowned.end());
										break;
									}
								} if (!PlayerFound) {
									MYSQL_ROW row;
									string q = "SELECT * FROM PlayerDatabase WHERE username = '" + world->owner + "' LIMIT 1";
									if (mysql_query(conn, q.c_str())) {
										cout << mysql_error(conn) << endl;			
										return;
									}
									string WorldOwned;
									res = mysql_store_result(conn);
									while (row = mysql_fetch_row(res)) {
										WorldOwned = row[24];
									}
									vector<string> editworldsowned;
									stringstream ssfs(WorldOwned);
									while (ssfs.good()) {
										string substr;
										getline(ssfs, substr, ',');
										if (substr.size() == 0) continue;
										editworldsowned.push_back(substr);
									}
									editworldsowned.erase(std::remove(editworldsowned.begin(), editworldsowned.end(), static_cast<PlayerInfo*>(peer->data)->currentWorld), editworldsowned.end());
									string worldstring = "";
									for (int i = 0; i < editworldsowned.size(); i++) {
										worldstring += editworldsowned[i] + ",";
									}
									string qs = "UPDATE PlayerDatabase SET worldsowned = '" + worldstring + "' WHERE username = '" + world->owner + "' LIMIT 1";
									if (mysql_query(conn, qs.c_str())) {
										cout << mysql_error(conn) << endl;			
										return;
									}
								}
							} else {
								static_cast<PlayerInfo*>(peer->data)->worldsowned.erase(std::remove(static_cast<PlayerInfo*>(peer->data)->worldsowned.begin(), static_cast<PlayerInfo*>(peer->data)->worldsowned.end(), static_cast<PlayerInfo*>(peer->data)->currentWorld), static_cast<PlayerInfo*>(peer->data)->worldsowned.end());
							}
							world->allowMod = false;
							world->rainbow = false;
							world->entrylevel = 1;
							world->owner = "";
							world->isPublic = false;
							world->accessed.clear();
							world->silence = false;
							world->publicBlock = -1;
							world->DisableDrop = false;
						}
						if (world->items[x + (y * world->width)].foreground == 4802) {
							for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
								if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
								if (isHere(peer, currentPeer)) {
									SendRainbowShitData(currentPeer, world->items[x + (y * world->width)].foreground, world->items[x + (y * world->width)].background, x, y, false, -1);
								}
							}
						}
					} else if (world->items[x + (y * world->width)].foreground == 6954) {
						if (world->items[x + (y * world->width)].mc != 0) {
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Empty the machine before breaking it!", 0, true);
							return;
						}
						world->items[x + (y * world->width)].mc = 0;
						world->items[x + (y * world->width)].mid = 0;
						world->items[x + (y * world->width)].vid = 0;
						world->items[x + (y * world->width)].rm = false;
						auto success = true;
						SaveItemMoreTimes(6954, 1, peer, success, "");
					} else if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::WEATHER) {
						auto success = true;
						SaveItemMoreTimes(world->items[x + (y * world->width)].foreground, 1, peer, success, "");
						world->weather = 0;
						for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer)) {
								GamePacket p2 = packetEnd(appendInt(appendString(createPacket(), "OnSetCurrentWeather"), world->weather));
								ENetPacket* packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(currentPeer, 0, packet2);
								delete p2.data;
							}
						}
					} else if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SUCKER) {
						if (world->items[x + (y * world->width)].mid != 0 && world->items[x + (y * world->width)].mc != 0) {
							if (world->items[x + (y * world->width)].mc == 0) {
								world->items[x + (y * world->width)].mc = 0;
								world->items[x + (y * world->width)].mid = 0;
								world->items[x + (y * world->width)].rm = false;
								//world->items[x + (y * world->width)].foreground = 0;
								auto success = true;
								SaveItemMoreTimes(world->items[x + (y * world->width)].foreground, 1, peer, success, "");
							} else {
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Empty the " + getItemDef(world->items[x + (y * world->width)].foreground).name + " before breaking it!", 0, true);
								return;
							}
						} else {
							world->items[x + (y * world->width)].mc = 0;
							world->items[x + (y * world->width)].mid = 0;
							world->items[x + (y * world->width)].rm = false;
							//world->items[x + (y * world->width)].foreground = 0;
							auto success = true;
							SaveItemMoreTimes(world->items[x + (y * world->width)].foreground, 1, peer, success, "");
						}
					} else {
						auto success = true;
						SaveItemMoreTimes(world->items[x + (y * world->width)].foreground, 1, peer, success, "");
						world->items[x + (y * world->width)].mc = 0;
						world->items[x + (y * world->width)].mid = 0;
						world->items[x + (y * world->width)].rm = false;
						world->items[x + (y * world->width)].vcount = 0;
						world->items[x + (y * world->width)].vprice = 0;
						world->items[x + (y * world->width)].vid = 0;
						world->items[x + (y * world->width)].vdraw = 0;
						world->items[x + (y * world->width)].monitorname = "";
						world->items[x + (y * world->width)].monitoronline = false;
						world->items[x + (y * world->width)].opened = false;
						world->items[x + (y * world->width)].intdata = 0;
						//world->items[x + (y * world->width)].foreground = 0;
					}
				} if (world->items[x + (y * world->width)].foreground == 3528) {
					if (world->items[x + (y * world->width)].intdata != 0) {
						world->items[x + (y * world->width)].intdata = 0;
					}
				} if (world->items[x + (y * world->width)].foreground == 2946) {
					if (world->items[x + (y * world->width)].intdata != 0) {
						auto success = true;
						SaveItemMoreTimes(world->items[x + (y * world->width)].intdata, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You picked up 1 " + getItemDef(world->items[x + (y * world->width)].intdata).name + ".", 0, true);
						world->items[x + (y * world->width)].intdata = 0;
					}
				} if (getItemDef(world->items[x + (y * world->width)].foreground).rarity != 999) {
					SendTileData(world, peer, x, y, data.punchX, data.punchY);
				}
				/*log mod dev*/
				if (!isWorldOwner(peer, world) && !isWorldAdmin(peer, world) && isMod(peer)) {
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
					account_history += "" + to_string(Month) + "/" + to_string(Day) + "/" + to_string(Year) + " " + to_string(Hour) + ":" + to_string(Min) + ":" + to_string(Sec) + ": " + static_cast<PlayerInfo*>(peer->data)->rawName + " - >> Break " + getItemDef(world->items[x + (y * world->width)].foreground).name + " (" + world->name + ")|";
					string stringsa = "UPDATE PlayerDatabase SET accountnotes = '" + account_history + "' WHERE username = '" + static_cast<PlayerInfo*>(peer->data)->rawName + "' LIMIT 1";
					mysql_query(conn, stringsa.c_str());
				}
				world->items[x + (y * world->width)].foreground = 0;
			} else {
				if (getItemDef(world->items[x + (y * world->width)].background).rarity != 999 && tile == 18) {
					if (getItemDef(world->items[x + (y * world->width)].background).properties & Property_Dropless) return;
					SendTileData(world, peer, x, y, data.punchX, data.punchY);
				}
				SendDropSeed(peer, x, y, world->items[x + (y * world->width)].background);
				world->items[x + (y * world->width)].background = 6864;
				if (world->items[x + (y * world->width)].foreground == 1008 || world->items[x + (y * world->width)].foreground == 1796 || world->items[x + (y * world->width)].foreground == 242 || world->items[x + (y * world->width)].foreground == 9290 || world->items[x + (y * world->width)].foreground == 8470 || world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 9308) {
					world->items[x + (y * world->width)].foreground = 0;
				}
			}
		} else {
			if (y < world->height) {
				world->items[x + (y * world->width)].breakTime = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
				world->items[x + (y * world->width)].breakLevel += 4;
			}
		}
		}
	}
	else
	{
		if (world->items[x + (y * world->width)].foreground != 0 && getItemDef(tile).blockType != BlockTypes::BACKGROUND && getItemDef(tile).blockType != BlockTypes::GROUND_BLOCK) return;
		for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				bool RotatedRight = false;
				auto xpos = x * 32;
				auto ppos = static_cast<PlayerInfo*>(currentPeer->data)->x;
				if (static_cast<PlayerInfo*>(currentPeer->data)->x < x * 32) RotatedRight = true;
				if (RotatedRight) ppos += 19;
				xpos = xpos / 32;
				ppos = ppos / 32;
				if (ppos == xpos && static_cast<PlayerInfo*>(currentPeer->data)->y / 32 == y && getItemDef(tile).properties != Property_NoSeed && getItemDef(tile).properties != Property_Foreground && getItemDef(tile).properties != Property_MultiFacing && getItemDef(tile).blockType != BlockTypes::SEED && getItemDef(tile).blockType != BlockTypes::STEAM && getItemDef(tile).blockType != BlockTypes::UNKNOWN && getItemDef(tile).blockType != BlockTypes::VENDING && getItemDef(tile).blockType != BlockTypes::ANIM_FOREGROUND && getItemDef(tile).blockType != BlockTypes::BULLETIN_BOARD && getItemDef(tile).blockType != BlockTypes::FACTION && getItemDef(tile).blockType != BlockTypes::CHEST && getItemDef(tile).blockType != BlockTypes::GEMS && getItemDef(tile).blockType != BlockTypes::MAGIC_EGG && getItemDef(tile).blockType != BlockTypes::CRYSTAL && getItemDef(tile).blockType != BlockTypes::MAILBOX && getItemDef(tile).blockType != BlockTypes::PORTAL && getItemDef(tile).blockType != BlockTypes::PLATFORM && getItemDef(tile).blockType != BlockTypes::SFX_FOREGROUND && getItemDef(tile).blockType != BlockTypes::CHEMICAL_COMBINER && getItemDef(tile).blockType != BlockTypes::SWITCH_BLOCK && getItemDef(tile).blockType != BlockTypes::TRAMPOLINE && getItemDef(tile).blockType != BlockTypes::TOGGLE_FOREGROUND && getItemDef(tile).blockType != BlockTypes::GROUND_BLOCK && getItemDef(tile).blockType != BlockTypes::BACKGROUND && getItemDef(tile).blockType != BlockTypes::MAIN_DOOR && getItemDef(tile).blockType != BlockTypes::SIGN && getItemDef(tile).blockType != BlockTypes::DOOR && getItemDef(tile).blockType != BlockTypes::CHECKPOINT && getItemDef(tile).blockType != BlockTypes::GATEWAY && getItemDef(tile).blockType != BlockTypes::TREASURE && getItemDef(tile).blockType != BlockTypes::WEATHER) return;
			}
		}
		if (causedBy != -1)
		{
			if (!isDev(peer))
			{
				auto iscontains = false;
				SearchInventoryItem(peer, tile, 1, iscontains);
				if (!iscontains) return;
			}
		}
		/*log mod dev*/
		if (!isWorldOwner(peer, world) && !isWorldAdmin(peer, world) && isMod(peer)) {
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
			account_history += "" + to_string(Month) + "/" + to_string(Day) + "/" + to_string(Year) + " " + to_string(Hour) + ":" + to_string(Min) + ":" + to_string(Sec) + ": " + static_cast<PlayerInfo*>(peer->data)->rawName + " - >> Place " + getItemDef(tile).name + " (" + world->name + ")|";
			string stringsa = "UPDATE PlayerDatabase SET accountnotes = '" + account_history + "' WHERE username = '" + static_cast<PlayerInfo*>(peer->data)->rawName + "' LIMIT 1";
			mysql_query(conn, stringsa.c_str());
		}
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
		{
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == tile)
			{
				if (static_cast<unsigned int>(static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount) > 1)
				{
					static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount--;
					static_cast<PlayerInfo*>(peer->data)->needsaveinventory = true;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->inventory.items.erase(static_cast<PlayerInfo*>(peer->data)->inventory.items.begin() + i);
					static_cast<PlayerInfo*>(peer->data)->needsaveinventory = true;
				}
			}
		}
		if (tile != 18 && tile != 32 && getItemDef(tile).blockType != BlockTypes::CONSUMABLE)
		{
			bool Farmable = false;
			if (tile == 7382 || tile == 4762 || tile == 10024 || tile == 9468 || tile == 9460 || tile == 10028 || tile == 340 || tile == 954 || tile == 5666) Farmable = true;
			if (static_cast<PlayerInfo*>(peer->data)->PlacePotion && Farmable)
			{
				SendPlacingEffect(peer, data.punchX, data.punchY, 229);
			}
			else if (static_cast<PlayerInfo*>(peer->data)->cloth_back == 9466)
			{
				SendPlacingEffect(peer, data.punchX, data.punchY, 125);
			}
		}
		if (getItemDef(tile).blockType == BlockTypes::BACKGROUND || getItemDef(tile).blockType == BlockTypes::GROUND_BLOCK) {
			world->items[x + (y * world->width)].background = tile;
		} else if (getItemDef(tile).blockType == BlockTypes::SEED) {
			world->items[x + (y * world->width)].foreground = tile;
		} else {
			world->items[x + (y * world->width)].foreground = tile;
		}
		world->items[x + (y * world->width)].breakLevel = 0;
	}
	for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			auto raw = packPlayerMoving(&data);
			raw[2] = dicenr;
			raw[3] = dicenr;
			SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
	if (getItemDef(tile).properties & Property_MultiFacing)
	{
		if (static_cast<PlayerInfo*>(peer->data)->isRotatedLeft)
		{
			world->items[x + (y * world->width)].flipped = true;
			UpdateBlockState(peer, x, y, true, world);
		}
	}
	if (VendUpdate)
	{
		if (world->items[x + (y * world->width)].opened && world->items[x + (y * world->width)].vcount < world->items[x + (y * world->width)].vprice) {
			UpdateVend(peer, x, y, 0, false, world->items[x + (y * world->width)].vprice, world->items[x + (y * world->width)].background, world->items[x + (y * world->width)].opened);
		}
		else UpdateVend(peer, x, y, world->items[x + (y * world->width)].vid, false, world->items[x + (y * world->width)].vprice, world->items[x + (y * world->width)].background, world->items[x + (y * world->width)].opened);
	}
	if (isLock) {
		sendTileData(peer, x, y, 0x10, world->items[x + (y * world->width)].foreground, world->items[x + (y * world->width)].background, lockTileDatas(0x20, ((PlayerInfo*)(peer->data))->netID, 0, 0, false, 100));
	}
	if (isMannequin) {
		updateMannequin(peer, world->items[x + (y * world->width)].foreground, x, y, world->items[x + (y * world->width)].background, world->items[x + (y * world->width)].sign, 0, 0, 0, 0, 0, 0, 0, 0, 0, true, 0);
	}
	if (isSmallLock) {
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer)) {
				if (world->items[x + (y * world->width)].monitorname == static_cast<PlayerInfo*>(peer->data)->rawName) ApplyLockPacket(world, currentPeer, x, y, world->items[x + (y * world->width)].foreground, static_cast<PlayerInfo*>(peer->data)->netID);
				else ApplyLockPacket(world, currentPeer, x, y, world->items[x + (y * world->width)].foreground, -1);
			}
		}
	}
	if (isTree) {
		int growTimeSeed = getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity;
		growTimeSeed += 30 * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity;
		if (world->items[x + (y * world->width)].foreground - 1 == 954) growTimeSeed = 1800;
		if (world->items[x + (y * world->width)].foreground - 1 == 340) growTimeSeed = 3600;
		if (world->items[x + (y * world->width)].foreground - 1 == 5666) growTimeSeed = 2700;
		if (world->items[x + (y * world->width)].foreground - 1 == 4584) growTimeSeed = 2400;
		if (world->items[x + (y * world->width)].foreground - 1 == 4762) growTimeSeed = 14544;
		if (world->items[x + (y * world->width)].foreground - 1 == 7382) growTimeSeed = 22544;
		if (world->items[x + (y * world->width)].foreground - 1 == 9460) growTimeSeed = 29544;
		if (world->items[x + (y * world->width)].foreground - 1 == 9468) growTimeSeed = 36544;
		if (world->items[x + (y * world->width)].foreground - 1 == 10024) growTimeSeed = 56544;
		if (world->items[x + (y * world->width)].foreground - 1 == 10028) growTimeSeed = 86400;
		world->items[x + (y * world->width)].growtime = (GetCurrentTimeInternalSeconds() + growTimeSeed);
		if (getItemDef(world->items[x + (y * world->width)].foreground).rarity == 999) {
			world->items[x + (y * world->width)].fruitcount = (rand() % 1) + 1;
		}
		else {
			world->items[x + (y * world->width)].fruitcount = (rand() % 6) + 1;
		}
		if (getItemDef(world->items[x + (y * world->width)].foreground - 1).blockType == BlockTypes::CLOTHING) world->items[x + (y * world->width)].fruitcount = (rand() % 2) + 1;

		int chanceofbuff = 1;
		if (static_cast<PlayerInfo*>(peer->data)->level >= 8) chanceofbuff = 1;
		if (static_cast<PlayerInfo*>(peer->data)->level >= 11) chanceofbuff = 2;
		if (static_cast<PlayerInfo*>(peer->data)->level >= 8 && rand() % 100 <= chanceofbuff) {
			Player::OnConsoleMessage(peer, "Flawless bonus reduced 1 hour grow time");
			int NewGrowTime = 0;
			int InternalGrowTime = 0;
			NewGrowTime = calcBanDuration(world->items[x + (y * world->width)].growtime) - 3600;
			if (NewGrowTime < 0) NewGrowTime = 0;
			world->items[x + (y * world->width)].growtime = (GetCurrentTimeInternalSeconds() + NewGrowTime);	
			int growTimeSeed = getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity;
			growTimeSeed += 30 * getItemDef(world->items[x + (y * world->width)].foreground - 1).rarity;
			if (world->items[x + (y * world->width)].foreground - 1 == 954) growTimeSeed = 1800;
			if (world->items[x + (y * world->width)].foreground - 1 == 340) growTimeSeed = 3600;
			if (world->items[x + (y * world->width)].foreground - 1 == 5666) growTimeSeed = 2700;
			if (world->items[x + (y * world->width)].foreground - 1 == 4584) growTimeSeed = 2400;
			if (world->items[x + (y * world->width)].foreground - 1 == 4762) growTimeSeed = 14544;
			if (world->items[x + (y * world->width)].foreground - 1 == 7382) growTimeSeed = 22544;
			if (world->items[x + (y * world->width)].foreground - 1 == 9460) growTimeSeed = 29544;
			if (world->items[x + (y * world->width)].foreground - 1 == 9468) growTimeSeed = 36544;
			if (world->items[x + (y * world->width)].foreground - 1 == 10024) growTimeSeed = 56544;
			if (world->items[x + (y * world->width)].foreground - 1 == 10028) growTimeSeed = 86400;
			InternalGrowTime = growTimeSeed - calcBanDuration(world->items[x + (y * world->width)].growtime);
			UpdateTreeVisuals(peer, world->items[x + (y * world->width)].foreground, x, y, world->items[x + (y * world->width)].background, world->items[x + (y * world->width)].fruitcount, InternalGrowTime, true, 0);
		}
	}
	if (isScience) {
		world->items[x + (y * world->width)].growtime = (GetCurrentTimeInternalSeconds() + getItemDef(world->items[x + (y * world->width)].foreground).growTime);
	}
	if (isHeartMonitor)
	{
		world->items[x + (y * world->width)].monitorname = static_cast<PlayerInfo*>(peer->data)->displayName;
		world->items[x + (y * world->width)].monitoronline = true;
		sendHMonitor(peer, x, y, static_cast<PlayerInfo*>(peer->data)->displayName, true, world->items[x + (y * world->width)].background);
	}
	if (isgateway)
	{
		updateEntrance(peer, world->items[x + (y * world->width)].foreground, x, y, 0, world->items[x + (y * world->width)].background, true);
	}
	if (isDoor) {
		updateDoor(peer, world->items[x + (y * world->width)].foreground, x, y, world->items[x + (y * world->width)].background, getItemDef(world->items[x + (y * world->width)].foreground).name, false, true);
	}
	if (isMagplant) {
		for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
				if (isHere(peer, currentPeer)) {
				SendItemSucker(currentPeer, world->items[x + (y * world->width)].foreground, x, y, world->items[x + (y * world->width)].mid, -1, true, true, world->items[x + (y * world->width)].background);
			}
		}
	}
}

inline void sendWorld(ENetPeer* peer, WorldInfo* worldInfo) {
	if (!worldInfo) return;
	if (worldInfo->items == nullptr) return;
	auto zero = 0;
	static_cast<PlayerInfo*>(peer->data)->joinClothesUpdated = false;
	string asdf = "0400000004A7379237BB2509E8E0EC04F8720B050000000000000000FBBB0000010000007D920100FDFDFDFD04000000040000000000000000000000070000000000";
	auto worldName = worldInfo->name;
	auto xSize = worldInfo->width;
	auto ySize = worldInfo->height;
	auto square = xSize * ySize;
	auto nameLen = static_cast<__int16_t>(worldName.length());
	int payloadLen = asdf.length() / 2;
	auto dataLen = payloadLen + 2 + nameLen + 12 + (square * 8) + 4 + 100;
	auto offsetData = dataLen - 100;
	int allocMem = payloadLen + 2 + nameLen + 12 + (square * 8) + 4 + 16000 + 100 + (worldInfo->droppedItems.size() * 20);
	auto data = new BYTE[allocMem];
	memset(data, 0, allocMem);
	for (auto i = 0; i < asdf.length(); i += 2)
	{
		char x = ch2n(asdf[i]);
		x = x << 4;
		x += ch2n(asdf[i + 1]);
		memcpy(data + (i / 2), &x, 1);
	}
	__int16_t item = 0;
	auto smth = 0;
	for (auto i = 0; i < square * 8; i += 4) memcpy(data + payloadLen + i + 14 + nameLen, &zero, 4);
	for (auto i = 0; i < square * 8; i += 8) memcpy(data + payloadLen + i + 14 + nameLen, &item, 2);
	memcpy(data + payloadLen, &nameLen, 2);
	memcpy(data + payloadLen + 2, worldName.c_str(), nameLen);
	memcpy(data + payloadLen + 2 + nameLen, &xSize, 4);
	memcpy(data + payloadLen + 6 + nameLen, &ySize, 4);
	memcpy(data + payloadLen + 10 + nameLen, &square, 4);
	auto blockPtr = data + payloadLen + 14 + nameLen;
	auto sizeofblockstruct = 8;
	for (auto i = 0; i < square; i++)
	{
		int tile = worldInfo->items[i].foreground;
		sizeofblockstruct = 8;
		if (tile == 6)
		{
			auto type = 0x00000000;
			if (worldInfo->items[i].activated)
				type |= 0x00200000;
			if (worldInfo->items[i].flipped)
				type |= 0x00400000;
			if (worldInfo->items[i].water)
				type |= 0x04000000;
			if (worldInfo->items[i].glue)
				type |= 0x08000000;
			if (worldInfo->items[i].fire)
				type |= 0x10000000;
			if (worldInfo->items[i].red)
				type |= 0x20000000;
			if (worldInfo->items[i].green)
				type |= 0x40000000;
			if (worldInfo->items[i].blue)
				type |= 0x80000000;
			memcpy(blockPtr, &tile, 2);
			memcpy(blockPtr + 4, &type, 4);
			BYTE btype = 1;
			memcpy(blockPtr + 8, &btype, 1);
			string doorText = "EXIT";
			auto doorTextChars = doorText.c_str();
			auto length = static_cast<short>(doorText.size());
			memcpy(blockPtr + 9, &length, 2);
			memcpy(blockPtr + 11, doorTextChars, length);
			sizeofblockstruct += 4 + length;
			dataLen += 4 + length;
		}
		else if (getItemDef(tile).blockType == BlockTypes::SIGN || tile == 1420 || tile == 6124)
		{
			auto type = 0x00000000;
			if (worldInfo->items[i].activated)
				type |= 0x00200000;
			if (worldInfo->items[i].flipped)
				type |= 0x00400000;
			if (worldInfo->items[i].water)
				type |= 0x04000000;
			if (worldInfo->items[i].glue)
				type |= 0x08000000;
			if (worldInfo->items[i].fire)
				type |= 0x10000000;
			if (worldInfo->items[i].red)
				type |= 0x20000000;
			if (worldInfo->items[i].green)
				type |= 0x40000000;
			if (worldInfo->items[i].blue)
				type |= 0x80000000;
			memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
			memcpy(blockPtr + 4, &type, 4);
			BYTE btype = 2;
			memcpy(blockPtr + 8, &btype, 1);
			auto signText = worldInfo->items[i].sign;
			auto signTextChars = signText.c_str();
			auto length = static_cast<short>(signText.size());
			memcpy(blockPtr + 9, &length, 2);
			memcpy(blockPtr + 11, signTextChars, length);
			auto minus1 = -1;
			memcpy(blockPtr + 11 + length, &minus1, 4);
			sizeofblockstruct += 3 + length + 4;
			dataLen += 3 + length + 4;
		}
		else if (tile == 2946)
		{
			auto type = 0x00000000;
			if (worldInfo->items[i].activated)
				type |= 0x00200000;
			if (worldInfo->items[i].flipped)
				type |= 0x00400000;
			if (worldInfo->items[i].water)
				type |= 0x04000000;
			if (worldInfo->items[i].glue)
				type |= 0x08000000;
			if (worldInfo->items[i].fire)
				type |= 0x10000000;
			if (worldInfo->items[i].red)
				type |= 0x20000000;
			if (worldInfo->items[i].green)
				type |= 0x40000000;
			if (worldInfo->items[i].blue)
				type |= 0x80000000;
			memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
			memcpy(blockPtr + 4, &type, 4);
			BYTE btype = 0x17;
			memcpy(blockPtr + 8, &btype, 1);
			auto item1 = worldInfo->items[i].intdata;
			memcpy(blockPtr + 9, &item1, 4);
			sizeofblockstruct += 5;
			dataLen += 5;
		}
		else if (getItemDef(tile).blockType == BlockTypes::DOOR || getItemDef(tile).blockType == BlockTypes::PORTAL)
		{
			auto type = 0x00000000;
			if (worldInfo->items[i].activated)
				type |= 0x00200000;
			if (worldInfo->items[i].flipped)
				type |= 0x00400000;
			if (worldInfo->items[i].water)
				type |= 0x04000000;
			if (worldInfo->items[i].glue)
				type |= 0x08000000;
			if (worldInfo->items[i].fire)
				type |= 0x10000000;
			if (worldInfo->items[i].red)
				type |= 0x20000000;
			if (worldInfo->items[i].green)
				type |= 0x40000000;
			if (worldInfo->items[i].blue)
				type |= 0x80000000;
			memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
			memcpy(blockPtr + 4, &type, 4);
			BYTE btype = 1;
			memcpy(blockPtr + 8, &btype, 1);
			auto doorText = worldInfo->items[i].sign;
			auto doorTextChars = doorText.c_str();
			auto length = static_cast<short>(doorText.size());
			memcpy(blockPtr + 9, &length, 2);
			memcpy(blockPtr + 11, doorTextChars, length);
			auto minus1 = -1;
			memcpy(blockPtr + 11 + length, &minus1, 4);
			sizeofblockstruct += 4 + length;
			dataLen += 4 + length;
		}
		else if (getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::PROVIDER)
		{
			auto type = 0x00000000;
			if (worldInfo->items[i].activated)
				type |= 0x00200000;
			if (worldInfo->items[i].flipped)
				type |= 0x00400000;
			if (worldInfo->items[i].water)
				type |= 0x04000000;
			if (worldInfo->items[i].glue)
				type |= 0x08000000;
			if (worldInfo->items[i].fire)
				type |= 0x10000000;
			if (worldInfo->items[i].red)
				type |= 0x20000000;
			if (worldInfo->items[i].green)
				type |= 0x40000000;
			if (worldInfo->items[i].blue)
				type |= 0x80000000;

			BYTE btype = 9;
			auto timeIntoGrowth = getItemDef(worldInfo->items[i].foreground).growTime - calcBanDuration(worldInfo->items[i].growtime);
			memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
			memcpy(blockPtr + 4, &type, 4);
			memcpy(blockPtr + 8, &btype, 1);
			memcpy(blockPtr + 9, &timeIntoGrowth, 4);
			sizeofblockstruct += 5;
			dataLen += 5;
		}
		else if ((worldInfo->items[i].foreground == 0) || (worldInfo->items[i].foreground == 2) || (worldInfo->items[i].foreground == 8) || (worldInfo->items[i].foreground == 100) || (worldInfo->items[i].foreground == 4) || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::FOREGROUND || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::BACKGROUND || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::TOGGLE_FOREGROUND || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::CHEMICAL_COMBINER || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::CHEST || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::SWITCH_BLOCK)
		{
			memcpy(blockPtr, &worldInfo->items[i].foreground, 2);
			auto type = 0;
			if (worldInfo->items[i].activated)
				type |= 0x00400000;
			if (worldInfo->items[i].flipped)
				type |= 0x00200000;
			if (worldInfo->items[i].water)
				type |= 0x04000000;
			if (worldInfo->items[i].glue)
				type |= 0x08000000;
			if (worldInfo->items[i].fire)
				type |= 0x10000000;
			if (worldInfo->items[i].red)
				type |= 0x20000000;
			if (worldInfo->items[i].green)
				type |= 0x40000000;
			if (worldInfo->items[i].blue)
				type |= 0x80000000;
			memcpy(blockPtr + 4, &type, 4);
		}
		else
		{
			memcpy(blockPtr, &zero, 2);
		}
		memcpy(blockPtr + 2, &worldInfo->items[i].background, 2);
		blockPtr += sizeofblockstruct;
	}
	dataLen += 8;
	int itemcount = worldInfo->droppedItems.size();
	auto itemuid = worldInfo->droppedCount;
	memcpy(blockPtr, &itemcount, 4);
	memcpy(blockPtr + 4, &itemuid, 4);
	blockPtr += 8;
	auto iteminfosize = 16;
	for (auto i = 0; i < itemcount; i++)
	{
		auto item1 = worldInfo->droppedItems[i].id;
		auto count = worldInfo->droppedItems[i].count;
		auto uid = worldInfo->droppedItems[i].uid + 1;
		auto x = static_cast<float>(worldInfo->droppedItems[i].x);
		auto y = static_cast<float>(worldInfo->droppedItems[i].y);
		memcpy(blockPtr, &item1, 2);
		memcpy(blockPtr + 2, &x, 4);
		memcpy(blockPtr + 6, &y, 4);
		memcpy(blockPtr + 10, &count, 2);
		memcpy(blockPtr + 12, &uid, 4);
		blockPtr += iteminfosize;
		dataLen += iteminfosize;
	}
	dataLen += 100;
	blockPtr += 4;
	memcpy(blockPtr, &worldInfo->weather, 4);
	blockPtr += 4;
	offsetData = dataLen - 100;
	auto data2 = new BYTE[101];
	memset(data2, 0, 101);
	memcpy(data2 + 0, &zero, 4);
	auto weather = worldInfo->weather;
	memcpy(data2 + 4, &weather, 4);
	memcpy(data + dataLen - 4, &smth, 4);
	auto packet2 = enet_packet_create(data, dataLen, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2);
	static_cast<PlayerInfo*>(peer->data)->currentWorld = worldInfo->name;
	for (auto i = 0; i < square; i++)
	{
		switch (worldInfo->items[i].foreground)
		{
			case 3528: //Painting Easel
			{
				int xx = i % xSize, yy = i / xSize;
				SendCanvasData(peer, worldInfo->items[i].foreground, worldInfo->items[i].background, xx, yy, worldInfo->items[i].intdata, getItemDef(worldInfo->items[i].intdata).name);
				break;
			}
			case 6952:
			{
				if (worldInfo->items[i].mid != 0) SendItemSucker(peer, worldInfo->items[i].foreground, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].mid, 1, false, false, worldInfo->items[i].background);
				else SendItemSucker(peer, worldInfo->items[i].foreground, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].mid, 0, false, false, worldInfo->items[i].background);
				break;
			}
			case 6954:
			{
				if (worldInfo->items[i].mid > 0 && worldInfo->items[i].mc > 0) {
					SendItemSucker(peer, worldInfo->items[i].foreground, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].mid, 1, true, true, worldInfo->items[i].background);
				} else {
					SendItemSucker(peer, worldInfo->items[i].foreground, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].mid, -1, true, true, worldInfo->items[i].background);
				}
				break;
			}
			case 5638: case 6946: case 6948: //MAGPLANTS
			{
				if (worldInfo->items[i].mc <= 0) {
					SendItemSucker(peer, worldInfo->items[i].foreground, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].mid, 0, true, true, worldInfo->items[i].background);
				}
				else if (worldInfo->items[i].mc >= 5000) {
					SendItemSucker(peer, worldInfo->items[i].foreground, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].mid, -1, true, true, worldInfo->items[i].background);
				}
				else {
					SendItemSucker(peer, worldInfo->items[i].foreground, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].mid, 1, true, true, worldInfo->items[i].background);
				}
				break;
			}
			case 2978: //Vending Machine
			{
				auto islocks = false;
				if (worldInfo->items[i].vdraw >= 1) {
					islocks = true;
				}
				if (worldInfo->items[i].vcount == 0 && worldInfo->items[i].vprice == 0 && worldInfo->items[i].vid != 0) {
					UpdateVend(peer, i % worldInfo->width, i / worldInfo->width, 0, islocks, 0, worldInfo->items[i].background, worldInfo->items[i].opened);
				}
				else if (worldInfo->items[i].opened && worldInfo->items[i].vcount < worldInfo->items[i].vprice) {
					UpdateVend(peer, i % worldInfo->width, i / worldInfo->width, 0, islocks, worldInfo->items[i].vprice, worldInfo->items[i].background, worldInfo->items[i].opened);
				}
				else UpdateVend(peer, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].vid, islocks, worldInfo->items[i].vprice, worldInfo->items[i].background, worldInfo->items[i].opened);
				break;
			}
			case 1420: case 6214: //Mannequin
			{
				auto ismannequin = std::experimental::filesystem::exists("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(i) + ".json");
				if (ismannequin)
				{
					json j;
					ifstream fs("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(i) + ".json");
					fs >> j;
					fs.close();
					auto x = i % worldInfo->width;
					auto y = i / worldInfo->width;
					//0x00200000
					updateMannequin(peer, worldInfo->items[i].foreground, x, y, worldInfo->items[i].background, worldInfo->items[i].sign, atoi(j["clothHair"].get<string>().c_str()), atoi(j["clothHead"].get<string>().c_str()), atoi(j["clothMask"].get<string>().c_str()), atoi(j["clothHand"].get<string>().c_str()), atoi(j["clothNeck"].get<string>().c_str()), atoi(j["clothShirt"].get<string>().c_str()), atoi(j["clothPants"].get<string>().c_str()), atoi(j["clothFeet"].get<string>().c_str()), atoi(j["clothBack"].get<string>().c_str()), false, 0);
				}
				break;
			}
			case 1006: //Blue Mailbox
			{
				auto isbluemail = std::experimental::filesystem::exists("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(i) + ".json");
				if (isbluemail)
				{
					ifstream ifff("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(i) + ".json");
					json basic_json;
					ifff >> basic_json;
					ifff.close();
					if (basic_json["inmail"] > 0)
					{
						auto x = i % worldInfo->width;
						auto y = i / worldInfo->width;
						SendItemPacket(peer, worldInfo->items[i].foreground, worldInfo->items[i].background, x, y, 1);
					}
				}
				break;
			}
			case 656: //Mailbox
			{
				auto ismailbox = std::experimental::filesystem::exists("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(i) + ".json");
				if (ismailbox)
				{
					ifstream ifff("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(i) + ".json");
					json basic_json;
					ifff >> basic_json;
					ifff.close();
					if (basic_json["inmail"] > 0)
					{
						auto x = i % worldInfo->width;
						auto y = i / worldInfo->width;
						SendItemPacket(peer, worldInfo->items[i].foreground, worldInfo->items[i].background, x, y, 1);
					}
				}
				break;
			}
			case 1240: //Heart Monitor
			{
				bool found = false;
				ENetPeer* currentPeer;
				for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (static_cast<PlayerInfo*>(currentPeer->data)->displayName == worldInfo->items[i].monitorname) {
						found = true;
						sendHMonitor(peer, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].monitorname, true, worldInfo->items[i].background);
						break;
					}
				}
				if (!found) sendHMonitor(peer, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].monitorname, false, worldInfo->items[i].background);
				break;
			}
			case 0: case 6: case 2946: case 1008: case 866: case 6414: case 6212: case 5116: case 4858: case 3888: case 3044: case 2798: case 1632: case 1636: case 1044: case 928: case 872: case 5000: case 4: case 2: case 8: case 100:
			{
				if (worldInfo->items[i].destroy && worldInfo->items[i].foreground != 0) {
					for (int asd = 0; asd < getItemDef(worldInfo->items[i].foreground).breakHits; asd++) {
						if (worldInfo->items[i].foreground != 0) sendTileUpdate(i % worldInfo->width, i / worldInfo->width, 18, -1, peer, worldInfo);
					}
					worldInfo->items[i].destroy = false;
				}
				break;
			}
			default:
			{
				if (worldInfo->items[i].destroy && worldInfo->items[i].foreground != 0) {
					for (int asd = 0; asd <= getItemDef(worldInfo->items[i].foreground).breakHits; asd++) {
						if (worldInfo->items[i].foreground != 0) sendTileUpdate(i % worldInfo->width, i / worldInfo->width, 18, -1, peer, worldInfo);
					}
					worldInfo->items[i].destroy = false;
				}
				else if (getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::FOREGROUND || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::BACKGROUND || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::CHEST || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::SWITCH_BLOCK || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::TOGGLE_FOREGROUND || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::CHEMICAL_COMBINER || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::SIGN || getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::PORTAL) {
					break;
				}
				else if (getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::DONATION)
				{
					auto isdbox = std::experimental::filesystem::exists("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(i) + ".json");
					if (isdbox)
					{
						ifstream ifff("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(i) + ".json");
						json basic_json;
						ifff >> basic_json;
						ifff.close();
						if (basic_json["donated"] > 0)
						{
							SendItemPacket(peer, worldInfo->items[i].foreground, worldInfo->items[i].background, i % worldInfo->width, i / worldInfo->width, 1);
						}
					}
					break;
				}
				else if (getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::SEED) {
					int growTimeSeed = getItemDef(worldInfo->items[i].foreground - 1).rarity * getItemDef(worldInfo->items[i].foreground - 1).rarity * getItemDef(worldInfo->items[i].foreground - 1).rarity;
					growTimeSeed += 30 * getItemDef(worldInfo->items[i].foreground - 1).rarity;
					if (worldInfo->items[i].foreground - 1 == 954) growTimeSeed = 1800;
					if (worldInfo->items[i].foreground - 1 == 340) growTimeSeed = 3600;
					if (worldInfo->items[i].foreground - 1 == 5666) growTimeSeed = 2700;
					if (worldInfo->items[i].foreground - 1 == 4584) growTimeSeed = 2400;
					if (worldInfo->items[i].foreground - 1 == 4762) growTimeSeed = 14544;
					if (worldInfo->items[i].foreground - 1 == 7382) growTimeSeed = 22544;
					if (worldInfo->items[i].foreground - 1 == 9460) growTimeSeed = 29544;
					if (worldInfo->items[i].foreground - 1 == 9468) growTimeSeed = 36544;
					if (worldInfo->items[i].foreground - 1 == 10024) growTimeSeed = 56544;
					if (worldInfo->items[i].foreground - 1 == 10028) growTimeSeed = 86400;
					UpdateTreeVisuals(peer, worldInfo->items[i].foreground, i % xSize, i / xSize, worldInfo->items[i].background, worldInfo->items[i].fruitcount, growTimeSeed - calcBanDuration(worldInfo->items[i].growtime), false, 0);
				}
				else if (getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::GATEWAY) {
					updateEntrance(peer, worldInfo->items[i].foreground, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].opened, worldInfo->items[i].background, false);
				}
				else if (getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::DOOR)
				{
					updateDoor(peer, worldInfo->items[i].foreground, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].background, worldInfo->items[i].label == "" ? (worldInfo->items[i].destId == "" ? worldInfo->items[i].destWorld : worldInfo->items[i].destWorld + "...") : worldInfo->items[i].label, false, false);
				}
				else if (getItemDef(worldInfo->items[i].foreground).blockType == BlockTypes::LOCK) {
					if (worldInfo->items[i].foreground == 202 || worldInfo->items[i].foreground == 204 || worldInfo->items[i].foreground == 206 || worldInfo->items[i].foreground == 4994) {
						if (worldInfo->items[i].monitorname == static_cast<PlayerInfo*>(peer->data)->rawName) ApplyLockPacket(worldInfo, peer, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].foreground, static_cast<PlayerInfo*>(peer->data)->netID);
						else if (worldInfo->items[i].opened) ApplyLockPacket(worldInfo, peer, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].foreground, -3);
						else ApplyLockPacket(worldInfo, peer, i % worldInfo->width, i / worldInfo->width, worldInfo->items[i].foreground, -1);
					}
					else if (isWorldOwner(peer, worldInfo)) sendTileData(peer, i % worldInfo->width, i / worldInfo->width, 0x10, worldInfo->items[i].foreground, worldInfo->items[i].background, lockTileDatas(0x20, static_cast<PlayerInfo*>(peer->data)->netID, 0, 0, false, 100));
					else if (isWorldAdmin(peer, worldInfo)) sendTileData(peer, i % worldInfo->width, i / worldInfo->width, 0x10, worldInfo->items[i].foreground, worldInfo->items[i].background, lockTileDatas(0x20, static_cast<PlayerInfo*>(peer->data)->netID, 0, 0, true, 100));
					else {
						PlayerMoving moving;
						moving.packetType = 0x3;
						moving.characterState = 0x0;
						moving.x = i % worldInfo->width;
						moving.y = i / worldInfo->height;
						moving.punchX = i % worldInfo->width;
						moving.punchY = i / worldInfo->width;
						moving.XSpeed = 0;
						moving.YSpeed = 0;
						moving.netID = -1;
						moving.plantingTree = worldInfo->items[i].foreground;
						SendPacketRaw(4, packPlayerMoving(&moving), 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
					}
					if (worldInfo->items[i].foreground == 4802 && worldInfo->rainbow && isWorldOwner(peer, worldInfo)) {
						SendRainbowShitData(peer, worldInfo->items[i].foreground, worldInfo->items[i].background, i % worldInfo->width, i / worldInfo->width, true, static_cast<PlayerInfo*>(peer->data)->netID);
						for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer) && !isWorldOwner(currentPeer, worldInfo)) {
								SendRainbowShitData(currentPeer, worldInfo->items[i].foreground, worldInfo->items[i].background, i % worldInfo->width, i / worldInfo->width, true, static_cast<PlayerInfo*>(peer->data)->netID);
							}
						}
					} else if (worldInfo->items[i].foreground == 4802 && !isWorldOwner(peer, worldInfo)) {
						for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer) && isWorldOwner(currentPeer, worldInfo)) {
								SendRainbowShitData(peer, worldInfo->items[i].foreground, worldInfo->items[i].background, i % worldInfo->width, i / worldInfo->width, true, static_cast<PlayerInfo*>(currentPeer->data)->netID);
								break;
							}
						}
					}
				}
				else
				{
					PlayerMoving moving;
					moving.packetType = 0x3;
					moving.characterState = 0x0;
					moving.x = i % worldInfo->width;
					moving.y = i / worldInfo->height;
					moving.punchX = i % worldInfo->width;
					moving.punchY = i / worldInfo->width;
					moving.XSpeed = 0;
					moving.YSpeed = 0;
					moving.netID = -1;
					moving.plantingTree = worldInfo->items[i].foreground;
					SendPacketRaw(4, packPlayerMoving(&moving), 56, nullptr, peer, ENET_PACKET_FLAG_RELIABLE);
				}
				break;
			}
		}
	}
	static_cast<PlayerInfo*>(peer->data)->lastnormalworld = static_cast<PlayerInfo*>(peer->data)->currentWorld;
	ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
	string content((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
	auto gembux = atoi(content.c_str());
	Player::OnSetBux(peer, gembux, 1);
	Player::PlayAudio(peer, "audio/door_open.wav", 0);
	delete data;
	delete data2;
	if (worldInfo->allowMod != true && !isMod(peer))
	{
		static_cast<PlayerInfo*>(peer->data)->canWalkInBlocks = false;
	}
	else
	{
		if (isMod(peer))
		{
		}
		else if (static_cast<PlayerInfo*>(peer->data)->isZombie == false)
		{
			Player::OnConsoleMessage(peer, "`2Owner `ohas `2enabled `5Mod-Noclip `oin this world.");
			static_cast<PlayerInfo*>(peer->data)->canWalkInBlocks = true;
			send_state(peer);
		}
	}
	if (static_cast<PlayerInfo*>(peer->data)->cloth_feet == 898 || static_cast<PlayerInfo*>(peer->data)->cloth_feet == 1830 || static_cast<PlayerInfo*>(peer->data)->cloth_feet == 1966)
	{
		send_state(peer);
	}
	if (static_cast<PlayerInfo*>(peer->data)->effect != 8421376)
	{
		// ReSharper disable once CppIdenticalOperandsInBinaryExpression
		static_cast<PlayerInfo*>(peer->data)->effect = static_cast<PlayerInfo*>(peer->data)->effect;
		send_state(peer);
		sendPuncheffectpeer(peer, static_cast<PlayerInfo*>(peer->data)->effect);
	}
}

inline void joinWorld(ENetPeer* peer, string act, int x2, int y2)
{
	if (serverIsFrozen)
	{
		return;
	}
	if (static_cast<PlayerInfo*>(peer->data)->isBot == true)
	{
		enet_peer_disconnect_later(peer, 0);
	}
	if (static_cast<PlayerInfo*>(peer->data)->isConfirmingCode == true)
	{
		enet_peer_disconnect_later(peer, 0);
	}
	if (act.length() > 24 || act.length() < 0)
	{
		Player::OnConsoleMessage(peer, "`4Sorry, but world names with more than 24 characters are not allowed!");
		Player::OnFailedToEnterWorld(peer);
	}
	else
	{
		auto upsd = act;
		transform(upsd.begin(), upsd.end(), upsd.begin(), ::toupper);
		if (upsd == "EXIT")
		{
			static_cast<PlayerInfo*>(peer->data)->currentWorld = "EXIT";
			Player::OnConsoleMessage(peer, "`4To reduce confusion, this is not a valid world name`w. `oTry another one`w?``");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
		if (upsd.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != string::npos)
		{
			Player::OnTextOverlay(peer, "Symbols not allowed!");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
		if (frozenworlds.size() != 0) {
			if (find(frozenworlds.begin(), frozenworlds.end(), upsd) != frozenworlds.end()) {
				SendConsole("Saved server from crashing! in world " + upsd + "", "ERROR");
				Player::OnConsoleMessage(peer, "This world is busy... Try again");
				Player::OnFailedToEnterWorld(peer);
				return;
			}
		}
		/*using namespace std::chrono;
		if (static_cast<PlayerInfo*>(peer->data)->lastJoinReq + 1500 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
		{
			static_cast<PlayerInfo*>(peer->data)->lastJoinReq = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
		}
		else
		{
			Player::OnConsoleMessage(peer, "`oSlow down when entering worlds, jeez!``");
			Player::OnFailedToEnterWorld(peer);
			return;
		}*/
		if (static_cast<PlayerInfo*>(peer->data)->isCursed) act = "HELL";
		auto info = worldDB.get(act);
		if (info.name == "error") {
			Player::OnConsoleMessage(peer, "An error occured while trying to enter this world, please try again!");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
		const auto playeriai = getPlayersCountInWorldSave(info.name);
		if (playeriai >= 60)
		{
			Player::OnConsoleMessage(peer, "World is at max capacity. Try again later...");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
		const auto existsban = std::experimental::filesystem::exists("worldbans/" + info.name + "/" + static_cast<PlayerInfo*>(peer->data)->rawName);
		if (existsban) {
			Player::OnConsoleMessage(peer, "`4Oh no! ``You've been banned from that world by its owner! Try again later after ban wears off.");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
		if (static_cast<PlayerInfo*>(peer->data)->haveGrowId) {
			DailyRewardCheck(peer);
			auto iscontains = false;
			SearchInventoryItem(peer, 6336, 1, iscontains);
			if (!iscontains) {
				auto success = true;
				SaveItemMoreTimes(6336, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from system");
			}
			/*magplant*/
			auto iscontainss = false;
			SearchInventoryItem(peer, 5640, 1, iscontainss);
			if (iscontainss) {
				static_cast<PlayerInfo*>(peer->data)->magplantitemid = 0;
				RemoveInventoryItem(5640, 1, peer, true);
			}
		}
		static_cast<PlayerInfo*>(peer->data)->netID = cId;
		if (static_cast<PlayerInfo*>(peer->data)->isinv == false) {
			for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
				if (isHere(peer, currentPeer)) {
					if (static_cast<PlayerInfo*>(currentPeer->data)->currentWorld == "EXIT") continue;
					Player::OnConsoleMessage(currentPeer, "`5<`w" + static_cast<PlayerInfo*>(peer->data)->displayName + " `5entered, `w" + std::to_string(getPlayersCountInWorld(static_cast<PlayerInfo*>(peer->data)->currentWorld) - 1) + "`` others here>``");
				}
			}
		}
		string Definitions = " `0["; 
		if (info.category != "None") Definitions += "`9" + info.category;
		for (auto jss = 0; jss < info.width * info.height; jss++) {
			if (info.items[jss].foreground == 226 && info.items[jss].activated) { 
				if (Definitions == " `0[") Definitions += "`4JAMMED";
				else Definitions += "``, `4JAMMED";
			}
			if (info.items[jss].foreground == 1276 && info.items[jss].activated) { 
				if (Definitions == " `0[") Definitions += "`2NOPUNCH";
				else Definitions += "``, `2NOPUNCH";
			}
			if (info.items[jss].foreground == 1278 && info.items[jss].activated) { 
				if (Definitions == " `0[") Definitions += "`2IMMUNE";
				else Definitions += "``, `2IMMUNE";
			}
			if (info.items[jss].foreground == 4992 && info.items[jss].activated) { 
				if (Definitions == " `0[") Definitions += "`2ANTIGRAVITY";
				else Definitions += "``, `2ANTIGRAVITY";
			}
			if (info.items[jss].foreground == 10422 && info.items[jss].activated) { 
				if (Definitions == " `0[") Definitions += "`2NOEVENT";
				else Definitions += "``, `2NOEVENT";
			}
			if (info.items[jss].foreground == 10432 && info.items[jss].activated) { 
				if (Definitions == " `0[") Definitions += "`#PHYSICS";
				else Definitions += "``, `#PHYSICS";
			}
			if (info.items[jss].foreground == 10430 && info.items[jss].activated) { 
				if (Definitions == " `0[") Definitions += "`4WORKER";
				else Definitions += "``, `4WORKER";
			}
		}
		if (info.isNuked) {
			if (Definitions == " `0[") Definitions += "`4World is banned, can't be reached by users";
			else Definitions += "``, `4World is banned, can't be reached by users";
		}
		Definitions += "`0]";
		if (Definitions == " `0[`0]") Definitions = "";
		Player::OnConsoleMessage(peer, "World `w" + info.name + "``" + Definitions + " `oentered. There are `w" + to_string(getPlayersCountInWorld(info.name)) + "`` other people here, `w" + to_string(GetPlayerCountServer()) + "`` online.");
		string nickname = "";
		if (info.owner != "") {
			MYSQL_ROW row;
			stringstream sse;
			string adminlevel = "0";
			sse << "SELECT * FROM PlayerDatabase WHERE username = '" + info.owner + "' LIMIT 1";
			auto query = sse.str();
			auto q = query.c_str();
			if (mysql_query(conn, q)) {
				cout << mysql_error(conn) << endl;
				enet_peer_disconnect_later(peer, 0);
				return;
			}
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res)) {
				adminlevel = row[19];
				nickname = row[44];
			}
			if (nickname == "") {
				if (adminlevel == "1") {
					nickname = "`#@" + info.owner;
				} else if (adminlevel == "2") {
					nickname = "`6@" + info.owner;
				} else {
					nickname = info.owner;
				}
			} 
			//if (res) mysql_free_result(res);
			if (info.owner == static_cast<PlayerInfo*>(peer->data)->rawName || nickname == static_cast<PlayerInfo*>(peer->data)->displayName || isWorldAdmin2(peer, info)) {
				Player::OnConsoleMessage(peer, "`5[`w" + info.name + "`$ World Locked`o by " + nickname + " ``(`2ACCESS GRANTED``)`5]");
				if (info.notification != "") {
					Player::OnConsoleMessage(peer, info.notification);
					info.notification = "";
				}
				if (info.owner == static_cast<PlayerInfo*>(peer->data)->rawName || nickname == static_cast<PlayerInfo*>(peer->data)->displayName) {
					if (static_cast<PlayerInfo*>(peer->data)->displayName.find("`") != string::npos) {} else {
						static_cast<PlayerInfo*>(peer->data)->displayName = "`2" + static_cast<PlayerInfo*>(peer->data)->displayName;
						auto p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), "`2" + static_cast<PlayerInfo*>(peer->data)->displayName));
						memcpy(p7.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
						auto packet7 = enet_packet_create(p7.data, p7.len, ENET_PACKET_FLAG_RELIABLE);
						delete p7.data;
						for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer)) {
								if (static_cast<PlayerInfo*>(peer->data)->adminLevel >= 0) {
									enet_peer_send(currentPeer, 0, packet7);
								}
							}
						}
					}
				}
			}
			else if (info.publicBlock != -1 && info.publicBlock != 0) {
				Player::OnConsoleMessage(peer, "`5[`w" + info.name + "`$ World Locked`o by " + nickname + " ``(`^BFG``)`5]");
			} else {
				Player::OnConsoleMessage(peer, "`5[`w" + info.name + "`$ World Locked`o by " + nickname + "`5]");
			}
		}
		if (info.owner != static_cast<PlayerInfo*>(peer->data)->rawName && nickname != static_cast<PlayerInfo*>(peer->data)->displayName) {
			if (static_cast<PlayerInfo*>(peer->data)->displayName.find("`2") != string::npos) {
				size_t pos;
				while ((pos = static_cast<PlayerInfo*>(peer->data)->displayName.find("`2")) != string::npos) {
					static_cast<PlayerInfo*>(peer->data)->displayName.replace(pos, 2, "");
				}
				auto p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), static_cast<PlayerInfo*>(peer->data)->displayName));
				memcpy(p7.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
				auto packet7 = enet_packet_create(p7.data, p7.len, ENET_PACKET_FLAG_RELIABLE);
				delete p7.data;
				for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, currentPeer)) {
						if (static_cast<PlayerInfo*>(peer->data)->adminLevel >= 0) {
							enet_peer_send(currentPeer, 0, packet7);
						}
					}
				}
			}
		}
		sendWorld(peer, &info);
		SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
		auto x = 3040;
		auto y = 736;
		for (auto j = 0; j < info.width * info.height; j++) {
			if (info.items[j].foreground == 6) {
				x = (j % info.width) * 32;
				y = (j / info.width) * 32;
			}
		}
		if (x2 != 0 && y2 != 0) {
			x = x2;
			y = y2;
		}
		static_cast<PlayerInfo*>(peer->data)->x = x;
		static_cast<PlayerInfo*>(peer->data)->x = y;
		if (static_cast<PlayerInfo*>(peer->data)->adminLevel >= 1) {
			auto p = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + std::to_string(cId) + "\nuserID|" + std::to_string(cId) + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(x) + "|" + std::to_string(y) + "\nname|``" + static_cast<PlayerInfo*>(peer->data)->displayName + "``\ncountry|" + static_cast<PlayerInfo*>(peer->data)->country + "\ninvis|0\nmstate|0\nsmstate|1\nonlineID|\ntype|local\n"));
			const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			delete p.data;
		} else {
			auto p = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + std::to_string(cId) + "\nuserID|" + std::to_string(cId) + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(x) + "|" + std::to_string(y) + "\nname|``" + static_cast<PlayerInfo*>(peer->data)->displayName + "``\ncountry|" + static_cast<PlayerInfo*>(peer->data)->country + "\ninvis|0\nmstate|0\nsmstate|0\nonlineID|\ntype|local\n"));
			const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			delete p.data;
		} 
		static_cast<PlayerInfo*>(peer->data)->netID = cId;
		onPeerConnect(peer);
		cId++;
	}
}

inline void sendPlayerToWorld(ENetPeer* peer, PlayerInfo* player, string wrldname)
{
	if (serverIsFrozen) return;
	toUpperCase(wrldname);

	const auto playeriai = getPlayersCountInWorldSave(wrldname);

	if (wrldname == "EXIT")
	{
		Player::OnConsoleMessage(peer, "You cannot warp to that world!");
	}
	else if (playeriai >= 60)
	{
		Player::OnConsoleMessage(peer, "World is at max capacity. Try again later...");
	}
	else if (wrldname == "GROWGANOTH" && !GrowganothEvent && !isDev(peer))
	{
		Player::OnTextOverlay(peer, "Growganoth is currently closed!");
	}
	else if (frozenworlds.size() != 0) {
		if (find(frozenworlds.begin(), frozenworlds.end(), wrldname) != frozenworlds.end()) {
			SendConsole("Saved server from crashing! in world " + wrldname + "", "ERROR");
			Player::OnConsoleMessage(peer, "This world is busy... Try again");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
	}
	else if (static_cast<PlayerInfo*>(peer->data)->isConfirmingCode == true)
	{
		enet_peer_disconnect_later(peer, 0);
	}
	else
	{
		sendPlayerLeave(peer);
		auto info = worldDB.get(wrldname);
		if (info.name == "error") {
			Player::OnConsoleMessage(peer, "An error occured while trying to enter this world, please try again!");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
		sendWorld(peer, &info);
		auto x = 3040;
		auto y = 736;
		for (auto j = 0; j < info.width * info.height; j++)
		{
			if (info.items[j].foreground == 6)
			{
				x = (j % info.width) * 32;
				y = (j / info.width) * 32;
			}
		}
		/*magplant*/
		auto iscontainss = false;
		SearchInventoryItem(peer, 5640, 1, iscontainss);
		if (iscontainss)
		{
			static_cast<PlayerInfo*>(peer->data)->magplantitemid = 0;
			RemoveInventoryItem(5640, 1, peer, true);
		}
		if (!static_cast<PlayerInfo*>(peer->data)->Console)
		{
			auto p = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + std::to_string(cId) + "\nuserID|" + std::to_string(cId) + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(x) + "|" + std::to_string(y) + "\nname|``" + static_cast<PlayerInfo*>(peer->data)->displayName + "``\ncountry|" + static_cast<PlayerInfo*>(peer->data)->country + "\ninvis|0\nmstate|0\nsmstate|0\ntype|local\n"));
			const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			delete p.data;
		}
		static_cast<PlayerInfo*>(peer->data)->netID = cId;
		onPeerConnect(peer);
		cId++;
		SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
	}
}

inline void sendPlayerToWorld2(ENetPeer* peer, PlayerInfo* player, string wrldname, const int x_ = -1, const int y_ = -1)
{
	if (serverIsFrozen) return;
	toUpperCase(wrldname);
	if (wrldname == "EXIT")
	{
		Player::OnConsoleMessage(peer, "You cant warp to that world!");
	}
	else if (frozenworlds.size() != 0) {
		if (find(frozenworlds.begin(), frozenworlds.end(), wrldname) != frozenworlds.end()) {
			SendConsole("Saved server from crashing! in world " + wrldname + "", "ERROR");
			Player::OnConsoleMessage(peer, "This world is busy... Try again");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
	}
	else
	{
		sendPlayerLeave(peer);
		auto info = worldDB.get(wrldname);
		if (info.name == "error") {
			Player::OnConsoleMessage(peer, "An error occured while trying to enter this world, please try again!");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
		sendWorld(peer, &info);
		auto x = 3040;
		auto y = 736;
		for (auto j = 0; j < info.width * info.height; j++)
		{
			if (info.items[j].foreground == 6)
			{
				x = (j % info.width) * 32;
				y = (j / info.width) * 32;
			}
		}
		/*magplant*/
		auto iscontainss = false;
		SearchInventoryItem(peer, 5640, 1, iscontainss);
		if (iscontainss)
		{
			static_cast<PlayerInfo*>(peer->data)->magplantitemid = 0;
			RemoveInventoryItem(5640, 1, peer, true);
		}
		if (x_ != -1 && y_ != -1)
		{
			x = x_ * 32;
			y = y_ * 32;
		}
		if (!static_cast<PlayerInfo*>(peer->data)->Console)
		{
			auto p = packetEnd(appendString(appendString(createPacket(), "OnSpawn"), "spawn|avatar\nnetID|" + std::to_string(cId) + "\nuserID|" + std::to_string(cId) + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(x) + "|" + std::to_string(y) + "\nname|``" + static_cast<PlayerInfo*>(peer->data)->displayName + "``\ncountry|" + static_cast<PlayerInfo*>(peer->data)->country + "\ninvis|0\nmstate|0\nsmstate|0\ntype|local\n"));
			const auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			delete p.data;
		}
		static_cast<PlayerInfo*>(peer->data)->netID = cId;
		onPeerConnect(peer);
		cId++;
		SendInventory(peer, static_cast<PlayerInfo*>(peer->data)->inventory);
	}
}

inline void handle_world(ENetPeer* peer, string act, bool sync = false, bool door = false, string destId = "", bool animations = true, int x = 0, int y = 0) {
	if (serverIsFrozen || !static_cast<PlayerInfo*>(peer->data)->HasLogged && static_cast<PlayerInfo*>(peer->data)->haveGrowId) return;
	toUpperCase(act);
	if (act.size() > 24) return;
	if (act.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != string::npos) {
		Player::OnConsoleMessage(peer, "Sorry, spaces and special characters are not allowed in world or door names.  Try again.");
		Player::OnFailedToEnterWorld(peer);
		return;
	}
	if (act == "EXIT" && static_cast<PlayerInfo*>(peer->data)->currentWorld == "EXIT") {
		Player::OnConsoleMessage(peer, "Exit from what? Press back if you're done playing.");
		Player::OnFailedToEnterWorld(peer);
		return;
	}
	else if (act == "EXIT") {
		Player::OnConsoleMessage(peer, "Where would you like to go? (`w" + to_string(GetPlayerCountServer()) + " `oonline)");
		sendPlayerLeave(peer);
		static_cast<PlayerInfo*>(peer->data)->currentWorld = "EXIT";
		sendWorldOffers(peer);
		return;
	}
	if (act == "ANAL" || act == "ANUS" || act == "ARSE" || act == "KONTOL" || act == "MEMEK" || act == "ASS" || act == "BALLSACK" || act == "BALLS" || act == "BASTARD" || act == "BITCH" || act == "BIATCH" || act == "BLOODY" || act == "BLOWJOB" || act == "BOLLOCK" || act == "BOLLOK" || act == "BONER" || act == "BOOB" || act == "BUGGER" || act == "BUM" || act == "BUTT" || act == "BUTTPLUG" || act == "CLITORIS" || act == "COCK" || act == "COON" || act == "CRAP" || act == "CUNT" || act == "DAMN" || act == "DICK" || act == "DILDO" || act == "DYKE" || act == "FAG" || act == "FECK" || act == "FELLATE" || act == "FELLATIO" || act == "FELCHING" || act == "FUCK" || act == "FUDGEPACKER" || act == "FLANGE" || act == "GODDAMN" || act == "HOMO" || act == "JERK" || act == "JIZZ" || act == "KNOBEND" || act == "LABIA" || act == "LMAO" || act == "LMFAO" || act == "MUFF" || act == "NIGGER" || act == "NIGGA" || act == "OMG" || act == "PENIS" || act == "PISS" || act == "POOP" || act == "PRICK" || act == "PUBE" || act == "PUSSY" || act == "QUEER" || act == "SCROTUM" || act == "SEX" || act == "SHIT" || act == "SH1T" || act == "SLUT" || act == "SMEGMA" || act == "SPUNK" || act == "TIT" || act == "TOSSER" || act == "TURD" || act == "TWAT" || act == "VAGINA" || act == "WANK" || act == "WHORE" || act == "WTF" || act == "SEBIA" || act == "ADMIN" || act == "SETH" || act == "HAMUMU" || act == "GOD" || act == "SATAN" || act == "RTSOFT" || act == "HEROMAN" || act == "SYSTEM" || act == "MIKEHOMMEL" || act == "SKIDS" || act == "MODERATOR" || act == "GODS" || act == "THEGODS" || act == "ALMANTAS") {
		Player::OnConsoleMessage(peer, "`4To reduce confusion, that is not a valid world name.``  Try another?");
		Player::OnFailedToEnterWorld(peer);
		return;
	}
	if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) act = "START";
	if (frozenworlds.size() != 0) {
		if (find(frozenworlds.begin(), frozenworlds.end(), act) != frozenworlds.end()) {
			SendConsole("Saved server from crashing! in world " + act + "", "ERROR");
			Player::OnConsoleMessage(peer, "This world is busy... Try again");
			Player::OnFailedToEnterWorld(peer);
			return;
		}
	}
	if (static_cast<PlayerInfo*>(peer->data)->currentWorld != "EXIT" && !door) {
		sendPlayerLeave(peer);
	}
	if (act == "" && !door) {
		joinWorld(peer, "START", 0, 0);
		return;
	}
	WorldInfo info;
	if (door && act == "") info = worldDB.get(static_cast<PlayerInfo*>(peer->data)->currentWorld);
	else info = worldDB.get(act);
	if (info.items == nullptr || info.name == "error") {
		Player::OnConsoleMessage(peer, "An error occured while trying to enter this world, please try again!");
		Player::OnFailedToEnterWorld(peer);
		return;
	}
	if (door) {
		if (destId != "") {
			for (auto i = 0; i < info.width * info.height; i++) {
				if (getItemDef(info.items[i].foreground).blockType == BlockTypes::DOOR || getItemDef(info.items[i].foreground).blockType == BlockTypes::PORTAL) {
					if (info.items[i].currId == destId) {
						if (act == static_cast<PlayerInfo*>(peer->data)->currentWorld || act == "") {
							DoCancelTransitionAndTeleport(peer, (i % info.width), (i / info.width), false, animations);
						} else {
							joinWorld(peer, act, (i % info.width) * 32, (i / info.width) * 32);
						}
						return;
					}
				}
			}
		}
		for (auto s = 0; s < info.width * info.height; s++) {
			if (info.items[s].foreground == 6) {
				if (act == static_cast<PlayerInfo*>(peer->data)->currentWorld || act == "") {
					DoCancelTransitionAndTeleport(peer, (s % info.width), (s / info.width), false, animations);
				} else {
					joinWorld(peer, act, 0, 0);
				}
				return;
			}
		}
		return;
	}
	if (getPlayersCountInWorldSave(info.name) > 60) {
		Player::OnConsoleMessage(peer, "Oops, `5" + info.name + "`` already has `460`` people in it. Try again later.");
		Player::OnFailedToEnterWorld(peer);
		return;
	}
	if (act == "GROWGANOTH" && !GrowganothEvent && !isDev(peer)) {
		Player::OnConsoleMessage(peer, "Growganoth is currently closed.");
		Player::OnFailedToEnterWorld(peer);
		return;
	}
	if (info.isNuked && !isMod(peer)) {
		Player::OnConsoleMessage(peer, "That world is inaccessible.");
		Player::OnFailedToEnterWorld(peer);
		return;
	}	
	if (info.entrylevel > static_cast<PlayerInfo*>(peer->data)->level && info.owner != static_cast<PlayerInfo*>(peer->data)->rawName && !isMod(peer)) {
		Player::OnConsoleMessage(peer, "Players lower than level " + to_string(info.entrylevel) + " can't enter " + info.name + ".");
		Player::OnFailedToEnterWorld(peer);
		return;
	}
	joinWorld(peer, act, x, y);
	if (sync) Player::PlayAudio(peer, "audio/choir.wav", 200);
}

inline void DoEnterDoor(ENetPeer* peer, WorldInfo* world, int x, int y, bool animations = true) {
	if (static_cast<PlayerInfo*>(peer->data)->Fishing) {
		static_cast<PlayerInfo*>(peer->data)->TriggerFish = false;
		static_cast<PlayerInfo*>(peer->data)->FishPosX = 0;
		static_cast<PlayerInfo*>(peer->data)->FishPosY = 0;
		static_cast<PlayerInfo*>(peer->data)->Fishing = false;
		send_state(peer);
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wSit perfectly when fishing!", 0, false);
		Player::OnSetPos(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y);
	}
	handle_world(peer, world->items[x + world->width * y].destWorld, false, true, world->items[x + world->width * y].destId, animations);
}

inline void playerRespawn(WorldInfo* world, ENetPeer* peer, const bool isDeadByTile) {
	if (static_cast<PlayerInfo*>(peer->data)->Fishing) {
		static_cast<PlayerInfo*>(peer->data)->TriggerFish = false;
		static_cast<PlayerInfo*>(peer->data)->FishPosX = 0;
		static_cast<PlayerInfo*>(peer->data)->FishPosY = 0;
		static_cast<PlayerInfo*>(peer->data)->Fishing = false;
		send_state(peer);
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wSit perfectly when fishing!", 0, false);
		Player::OnSetPos(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y);
	}
	auto netID = static_cast<PlayerInfo*>(peer->data)->netID;
	if (isDeadByTile == false) {
		Player::OnKilled(peer, static_cast<PlayerInfo*>(peer->data)->netID);
	}
	auto p2x = packetEnd(appendInt(appendString(createPacket(), "OnSetFreezeState"), 0));
	memcpy(p2x.data + 8, &netID, 4);
	auto respawnTimeout = 2000;
	auto deathFlag = 0x19;
	memcpy(p2x.data + 24, &respawnTimeout, 4);
	memcpy(p2x.data + 56, &deathFlag, 4);
	const auto packet2x = enet_packet_create(p2x.data, p2x.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2x);
	delete p2x.data;
	const auto p5 = packetEnd(appendInt(appendString(createPacket(), "OnSetFreezeState"), 2));
	memcpy(p5.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
	const auto packet5 = enet_packet_create(p5.data, p5.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet5);
	GamePacket p2;
	if (world == NULL || world == nullptr) { 
		SendConsole("Failed to run playerrespawn world was NULL", "ERROR");
		return;
	}
	//const auto world = getPlyersWorld(peer);
	auto x = 3040;
	auto y = 736;
	for (auto i = 0; i < world->width * world->height; i++) {
		if (world->items[i].foreground == 6) {
			x = (i % world->width) * 32;
			y = (i / world->width) * 32;
		}
	}
	if (static_cast<PlayerInfo*>(peer->data)->ischeck == true) {
		p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), static_cast<PlayerInfo*>(peer->data)->checkx, static_cast<PlayerInfo*>(peer->data)->checky));
	} else {
		p2 = packetEnd(appendFloat(appendString(createPacket(), "OnSetPos"), x, y));
	}
	memcpy(p2.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
	respawnTimeout = 2000;
	memcpy(p2.data + 24, &respawnTimeout, 4);
	memcpy(p2.data + 56, &deathFlag, 4);
	const auto packet2 = enet_packet_create(p2.data, p2.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2);
	delete p2.data;
	auto p2a = packetEnd(appendString(appendString(createPacket(), "OnPlayPositioned"), "audio/teleport.wav"));
	memcpy(p2a.data + 8, &netID, 4);
	respawnTimeout = 2000;
	memcpy(p2a.data + 24, &respawnTimeout, 4);
	memcpy(p2a.data + 56, &deathFlag, 4);
	const auto packet2a = enet_packet_create(p2a.data, p2a.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2a);
	delete p2a.data;
}

inline void SendSacrifice(WorldInfo* world, ENetPeer* peer, int itemid, int count)
{



	int pradinis = itemid;
	
	int Rarity = getItemDef(itemid).rarity;
	if (getItemDef(itemid).rarity >= 10)
	{
		Rarity = getItemDef(itemid).rarity * count;
	}

	if (itemid == 242) itemid = 1212;
	else if (itemid == 1190) itemid = 1214;
	else if (itemid == 882) itemid = 1232;
	else if (itemid == 592 || itemid == 1018) itemid = 1178;
	else if (itemid == 362) itemid = 1234;
	else if (itemid == 910) itemid = 1250;
	else if (itemid == 274 || itemid == 276) itemid = 1956;
	else if (itemid == 1474) itemid = 1990;
	else if (itemid == 1506) itemid = 1968;
	else if (itemid == 1746) itemid = 1960;
	else if (itemid == 1252) itemid = 1948;
	else if (itemid == 1830) itemid = 1966;
	else if (itemid == 2722) itemid = 3114;
	else if (itemid == 2984) itemid = 3118;
	else if (itemid == 3040) itemid = 3100;
	else if (itemid == 2390) itemid = 3122;
	else if (itemid == 1934) itemid = 3124;
	else if (itemid == 1162) itemid = 3126;
	else if (itemid == 604 || itemid == 2636) itemid = 3108;
	else if (itemid == 3020) itemid = 3098;
	else if (itemid == 914 || itemid == 916 || itemid == 918 || itemid == 920 || itemid == 924) itemid = 1962;
	else if (itemid == 900 || itemid == 1378 || itemid == 1576 || itemid == 7136 || itemid == 7754 || itemid == 7752 || itemid == 7758 || itemid == 7760) itemid = 2000;
	else if (itemid == 1460) itemid = 1970;
	else if (itemid == 3556) itemid = 4186;
	else if (itemid == 3556) itemid = 4188;
	else if (itemid == 2914 || itemid == 3012 || itemid == 3014) itemid = 4246;
	else if (itemid == 3016 || itemid == 3018) itemid = 4248;
	else if (itemid == 414 || itemid == 416 || itemid == 418 || itemid == 420 || itemid == 422 || itemid == 424 || itemid == 426 || itemid == 4634 || itemid == 4636 || itemid == 4638 || itemid == 4640 || itemid == 4642) itemid = 4192;
	else if (itemid == 1114) itemid = 4156;
	else if (itemid == 366) itemid = 4136;
	else if (itemid == 1950) itemid = 4152;
	else if (itemid == 2386) itemid = 4166;
	else if (itemid == 762) itemid = 4190;
	else if (itemid == 2860 || itemid == 2268) itemid = 4172;
	else if (itemid == 2972) itemid = 4182;
	else if (itemid == 3294) itemid = 4144;
	else if (itemid == 3296) itemid = 4146;
	else if (itemid == 3298) itemid = 4148;
	else if (itemid == 3290) itemid = 4140;
	else if (itemid == 3288) itemid = 4138;
	else if (itemid == 3292) itemid = 4142;
	else if (itemid == 1198) itemid = 5256;
	else if (itemid == 4960) itemid = 5208;
	else if (itemid == 1242) itemid = 5216;
	else if (itemid == 1244) itemid = 5218;
	else if (itemid == 1248) itemid = 5220;
	else if (itemid == 1246) itemid = 5214;
	else if (itemid == 5018) itemid = 5210;
	else if (itemid == 1408) itemid = 5254;
	else if (itemid == 4334) itemid = 5250;
	else if (itemid == 4338) itemid = 5252;
	else if (itemid == 3792) itemid = 5244;
	else if (itemid == 1294) itemid = 5236;
	else if (itemid == 6144) itemid = 7104;
	else if (itemid == 4732) itemid = 7124;
	else if (itemid == 4326) itemid = 7122;
	else if (itemid == 6300) itemid = 7102;
	else if (itemid == 2868) itemid = 7100;
	else if (itemid == 6798) itemid = 7126;
	else if (itemid == 6160) itemid = 7104;
	else if (itemid == 6176) itemid = 7124;
	else if (itemid == 5246) itemid = 7122;
	else if (itemid == 5246) itemid = 7102;
	else if (itemid == 5246) itemid = 7100;
	else if (itemid == 7998) itemid = 9048;
	else if (itemid == 6196) itemid = 9056;
	else if (itemid == 2392) itemid = 9114;
	else if (itemid == 8018) itemid = 9034;
	else if (itemid == 8468) itemid = 10232;

	else if (itemid == 4360) itemid = 10194;
	else if (itemid == 9364) itemid = 10206;
	else if (itemid == 9322) itemid = 10184;

	else if (itemid == 3818) itemid = 10192;
	else if (itemid == 3794) itemid = 10190;
	else if (itemid == 7696) itemid = 10186;

	else if (itemid == 10212) itemid = 10212;

	else if (itemid == 10328)
	{
		int itemuMas[154] = { 10232, 10194, 10206, 10184, 10192, 10190, 10186, 10212, 1212, 1190, 1206, 1166, 1964, 1976, 1998, 1946, 2002, 1958, 1952, 2030, 3104, 3112, 3120, 3092, 3094, 3096, 4184, 4178, 4174, 4180, 4170, 4168, 4150, 1180, 1224, 5226, 5228, 5230, 5212, 5246, 5242, 5234, 7134, 7118, 7132, 7120, 7098, 9018, 9038, 9026, 9066, 9058, 9044, 9024, 9032, 9036, 9028, 9030, 9110, 9112, 10386, 10326, 10324, 10322, 10328, 10316, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 1230, 1194, 1192, 1226, 1196, 1236, 1182, 1184, 1186, 1188, 1170, 1212, 1214, 1232, 1178, 1234, 1250, 1956, 1990, 1968, 1960, 1948, 1966, 3114, 3118, 3100, 3122, 3124, 3126, 3108, 3098, 1962, 2000, 1970, 4186, 4188, 4246, 4248, 4192, 4156, 4136, 4152, 4166, 4190, 4172, 4182, 4144, 4146, 4148, 4140, 4138, 4142, 5256, 5208, 5216, 5218, 5220, 5214, 5210, 5254, 5250, 5252, 5244, 5236, 7104, 7124, 7122, 7102, 7100, 7126, 7104, 7124, 7122, 7102, 7100, 9048, 9056, 9114, 9034 };
		auto randIndex = rand() % 154;
		itemid = itemuMas[randIndex];
		playerRespawn(world, peer, false);
		Player::OnConsoleMessage(peer, "`2" + getItemDef(pradinis).name + " `owas devoursed by Growganoth!");
		Player::OnConsoleMessage(peer, "`4Growganoth retrieves a very special artifact from his tomb on your behalf and kills you for the service!");
		Player::OnConsoleMessage(peer, "`oA `2" + getItemDef(itemid).name + " `owas bestoved upon you!");
		if (getItemDef(itemid).name.find("Wings") != string::npos || getItemDef(itemid).name.find("Cape") != string::npos || getItemDef(itemid).name.find("Cloak") != string::npos)
		{
			ENetPeer* currentPeer;
			for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
				Player::OnConsoleMessage(currentPeer, "`4Growganoth `ohonors `w" + static_cast<PlayerInfo*>(peer->data)->displayName + " `owith a `5Rare " + getItemDef(itemid).name + "");
			}
		}
		auto success = true;
		SaveItemMoreTimes(itemid, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from growganoth");
		if (count >= 2)
		{
			auto success = true;
			SaveItemMoreTimes(10328, count - 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from growganoth");
		}
		return;
	}

	else if (getItemDef(itemid).blockType == BlockTypes::WEATHER && itemid != 932) itemid = 1210;

	else if (Rarity < 10)
	{
		int itemuMas[2] = { 1208, 5256 };
		auto randIndex = rand() % 2;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 15)
	{
		int itemuMas[5] = { 1222, 1198, 1992, 5256, 1208 };
		auto randIndex = rand() % 5;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 20)
	{
		int itemuMas[7] = { 1200, 1992, 1982, 5256, 1198, 1208, 1222 };
		auto randIndex = rand() % 7;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 25)
	{
		int itemuMas[9] = { 1220, 1992, 1982, 5256, 1198, 1208, 1222, 1200, 10198 };
		auto randIndex = rand() % 9;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 30)
	{
		int itemuMas[11] = { 1202, 1992, 1982, 5240, 5256, 1198, 1208, 1222, 1200, 1220, 10198 };
		auto randIndex = rand() % 11;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 35)
	{
		int itemuMas[17] = { 1238, 1992, 1982, 4160, 4162, 5240, 5238, 5256, 7116, 1198, 1208, 1222, 1200, 1220, 1202, 10198, 10196 };
		auto randIndex = rand() % 17;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 40)
	{
		int itemuMas[18] = { 1168, 1992, 1982, 4160, 4162, 5240, 5238, 5256, 7116, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 10198, 10196 };
		auto randIndex = rand() % 18;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 45)
	{
		int itemuMas[21] = { 1172, 1992, 1982, 3116, 4160, 4162, 4164, 5240, 5238, 5256, 7116, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 10198, 10196 };
		auto randIndex = rand() % 21;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 50)
	{
		int itemuMas[22] = { 1230, 1992, 1982, 3116, 4160, 4162, 4164, 5240, 5238, 5256, 7116, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 10198, 10196 };
		auto randIndex = rand() % 22;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 55)
	{
		int itemuMas[25] = { 1194, 1192, 1992, 1982, 3116, 4160, 4162, 4164, 5240, 5238, 5256, 7116, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 1230, 10198, 10196, 10202 };
		auto randIndex = rand() % 25;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 60)
	{
		int itemuMas[27] = { 1226, 1992, 1982, 3116, 4160, 4162, 4164, 5240, 5238, 5256, 7116, 7108, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 1230, 1194, 1192, 10198, 10196, 10202 };
		auto randIndex = rand() % 27;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 65)
	{
		int itemuMas[28] = { 1196, 1992, 1982, 3116, 4160, 4162, 4164, 5240, 5238, 5256, 7116, 7108, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 1230, 1194, 1192, 1226, 10198, 10196, 10202 };
		auto randIndex = rand() % 28;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 70)
	{
		int itemuMas[29] = { 1236, 1992, 1982, 3116, 4160, 4162, 4164, 5240, 5238, 5256, 7116, 7108, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 1230, 1194, 1192, 1226, 1196, 10198, 10196, 10202 };
		auto randIndex = rand() % 29;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 80)
	{
		int itemuMas[44] = { 1182, 1184, 1186, 1188, 1992, 1982, 1994, 1972, 1980, 1988, 3116, 3102, 4160, 4162, 4164, 4154, 5224, 5222, 5232, 5240, 5238, 5256, 7116, 7108, 7110, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 1230, 1194, 1192, 1226, 1196, 1236, 10198, 10196, 10202, 10204 };
		auto randIndex = rand() % 44;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity < 90)
	{
		int itemuMas[48] = { 1170, 1992, 1982, 1994, 1972, 1980, 1988, 1984, 3116, 3102, 4160, 4162, 4164, 4154, 4158, 5224, 5222, 5232, 5240, 5238, 5256, 7116, 7108, 7110, 7128, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 1230, 1194, 1192, 1226, 1196, 1236, 1182, 1184, 1186, 1188, 10198, 10196, 10202, 10204 };
		auto randIndex = rand() % 48;
		itemid = itemuMas[randIndex];
		count = 1;
	}
	else if (Rarity >= 90 && Rarity != 999)
	{
		int itemuMas[56] = { 1216, 1218, 1992, 1982, 1994, 1972, 1980, 1988, 1984, 3116, 3102, 3106, 3110, 4160, 4162, 4164, 4154, 4158, 5224, 5222, 5232, 5240, 5248, 5238, 5256, 7116, 7108, 7110, 7128, 7112, 7114, 7130, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 1230, 1194, 1192, 1226, 1196, 1236, 1182, 1184, 1186, 1188, 1170, 10198, 10196, 10202, 10204 };
		auto randIndex = rand() % 56;
		itemid = itemuMas[randIndex];
		count = 1;
	}

	if (pradinis == itemid)
	{
		playerRespawn(world, peer, false);
		Player::OnConsoleMessage(peer, "`4Growganoth rejects your puny offering and eats you instead!");
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4Growganoth rejects your puny offering and eats you instead!", 0, true);
		auto success = true;
		SaveItemMoreTimes(pradinis, count, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from growganoth");
		return;
	}

	playerRespawn(world, peer, false);
	Player::OnConsoleMessage(peer, "`2" + getItemDef(pradinis).name + " `owas devoursed by Growganoth!");
	Player::OnConsoleMessage(peer, "`oA `2" + getItemDef(itemid).name + " `owas bestoved upon you!");
	auto success = true;
	SaveItemMoreTimes(itemid, count, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from growganoth");

}