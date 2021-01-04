#pragma once
#include "stdafx.h"
#include <vector>
using namespace std;
vector<WorldInfo> worlds;

/*Dropping the event item*/
inline void SendDropEventItem(const string WorldName, const int netID, const int x, int y, const int item, const int count, const BYTE specialEffect)
{
	if (serverIsFrozen) return;
	if (item >= maxItems) return;
	if (item < 0) return;
	auto world = worldDB.get2(WorldName).ptr;
	DroppedItem itemDropped;
	itemDropped.id = item;
	itemDropped.count = count;
	itemDropped.x = x;
	itemDropped.y = y;
	itemDropped.uid = world->droppedCount++;
	world->droppedItems.push_back(itemDropped);
	for (auto currentPeer = server->peers;
	     currentPeer < &server->peers[server->peerCount];
	     ++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (EventWorld(currentPeer, WorldName))
		{
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

/*Spawning the event items*/
inline void SpawnEventItem(const string WorldName, const int ItemID, const int count, int Time, const int x, const int y, const int Multiple)
{
	if (serverIsFrozen) return;
	for (auto i = 0; i < Multiple; i++) {
		const auto DropX = rand() % x * 32;
		const auto DropY = rand() % y * 32;
		SendDropEventItem(WorldName, -1, DropX, DropY, ItemID, count, 0);
	}
}

/*Basically the all world event things, this is a loop which finds active worlds*/
inline void WorldEvents() {
	while (true) {
		sleep(400); // sleep(400);
		if (serverIsFrozen) continue;
		auto worlds = worldDB.getRandomWorlds();
		for (auto iss = 0; iss < worlds.size(); iss++) {
			if (iss >= worlds.size()) {
				SendConsole("worlds.size() was larger than loop size (c63)", "ERROR");
				continue;
			}
			if (worlds[iss].items == nullptr) {
				cout << "was nullptr value case 6" << endl;
				continue;
			}
			if (worlds[iss].name == "error" || worlds[iss].name == "EXIT") continue;
			if (getPlayersCountInWorldEvent(worlds[iss], worlds[iss].name) <= 0) continue;
			for (auto jas = 0; jas < worlds[iss].width * worlds[iss].height; jas++) {
				auto x = (jas % worlds[iss].width);
				auto y = (jas / worlds[iss].width);
				if (x / 32 >= 0 && y / 32 >= 0 && x / 32 <= worlds[iss].width && y / 32 <= worlds[iss].height) {
					if (worlds[iss].items[x + (y * worlds[iss].width)].foreground == 10) {
						if (rand() % 100 <= 3) {
							if (worlds[iss].items[x + (y * worlds[iss].width)].evolvestage == 10) {
								worlds[iss].items[x + (y * worlds[iss].width)].evolvestage = 0;
								int RedBlocks = 0;
								int GreenBlocks = 0;
								int GoldenBlocks = 0;
								int BlueBlocks = 0;
								if (worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground == 4 || x > 0 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground == 4 || y > 0 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground == 4 || y < 59 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground == 4) {
									if (worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground == 4) RedBlocks++;
									if (x > 0 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground == 4) RedBlocks++;
									if (y > 0 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground == 4) RedBlocks++;
									if (y < 59 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground == 4) RedBlocks++;
								}
								if (worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground == 2 || x > 0 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground == 2 || y > 0 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground == 2 || y < 59 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground == 2) {
									if (worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground == 2) GreenBlocks++;
									if (x > 0 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground == 2) GreenBlocks++;
									if (y > 0 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground == 2) GreenBlocks++;
									if (y < 59 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground == 2) GreenBlocks++;
								}
								if (worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground == 260 || x > 0 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground == 260 || y > 0 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground == 260 || y < 59 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground == 260) {
									if (worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground == 260) GoldenBlocks++;
									if (x > 0 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground == 260) GoldenBlocks++;
									if (y > 0 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground == 260) GoldenBlocks++;
									if (y < 59 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground == 260) GoldenBlocks++;
								}
								if (worlds[iss].items[x + 1 + (y * worlds[iss].width)].water || x > 0 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].water || y > 0 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].water || y < 59 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].water) {
									if (worlds[iss].items[x + 1 + (y * worlds[iss].width)].water) BlueBlocks++;
									if (x > 0 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].water) BlueBlocks++;
									if (y > 0 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].water) BlueBlocks++;
									if (y < 59 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].water) BlueBlocks++;
								}
								int SpawnID = 0;
								if (RedBlocks >= GreenBlocks && RedBlocks >= GoldenBlocks && RedBlocks >= BlueBlocks) {
									SpawnID = 10406;
								}
								if (GreenBlocks >= RedBlocks && GreenBlocks >= GoldenBlocks && GreenBlocks >= BlueBlocks) {
									SpawnID = 10404;
								}
								if (GoldenBlocks >= GreenBlocks && GoldenBlocks >= RedBlocks && GoldenBlocks >= BlueBlocks) {
									SpawnID = 10402;
								}
								if (BlueBlocks >= GreenBlocks && BlueBlocks >= RedBlocks && BlueBlocks >= GoldenBlocks) {
									SpawnID = 10408;
								}
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
								data3.plantingTree = SpawnID;
								for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
									if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
									if (EventWorld(currentPeer6, worlds[iss].name)) {
										SendParticleEffect(currentPeer6, x * 32 + 16, y * 32 + 16, 4762, 97, 0);
										auto raw = packPlayerMoving(&data3);
										raw[2] = 0;
										raw[3] = 0;
										SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
									}
								}
								worlds[iss].items[x + (y * worlds[iss].width)].foreground = SpawnID;
							}
							else {
								worlds[iss].items[x + (y * worlds[iss].width)].evolvestage++;
							}
						}
						//jas += 1;
					}
					if (worlds[iss].items[x + (y * worlds[iss].width)].fire) {
						auto Chance = rand() % 100;
						if (worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground != 3528 && !worlds[iss].items[x + 1 + (y * worlds[iss].width)].water && !worlds[iss].items[x + 1 + (y * worlds[iss].width)].fire && !isSeed(worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground) && worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground != 8 && worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground != 6 && getItemDef(worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground).blockType != BlockTypes::LOCK && getItemDef(worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground).blockType != BlockTypes::DISPLAY && worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground != 6952 && worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground != 6954 && worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground != 5638 && worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground != 6946 && worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground != 6948 && worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground != 2978 && worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground != 1420 && worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground != 6214 && worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground != 1006 && worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground != 656 && worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground != 1420 && getItemDef(worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground).blockType != BlockTypes::DONATION && Chance >= 75) {
							if (worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground == 0 && worlds[iss].items[x + 1 + (y * worlds[iss].width)].background == 0 || worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground == 0 && worlds[iss].items[x + 1 + (y * worlds[iss].width)].background == 6864) continue;
							worlds[iss].items[x + 1 + (y * worlds[iss].width)].fire = true;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									UpdateVisualsForBlock(currentPeer6, true, x + 1, y, getPlyersWorld(currentPeer6));
									Player::OnParticleEffect(currentPeer6, 150, x * 32, y * 32, 0);
								}
							}
						}
						else if (x > 0 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground != 3528 && !worlds[iss].items[x - 1 + (y * worlds[iss].width)].water && !worlds[iss].items[x - 1 + (y * worlds[iss].width)].fire && !isSeed(worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground) && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground != 8 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground != 6 && getItemDef(worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground).blockType != BlockTypes::LOCK && getItemDef(worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground).blockType != BlockTypes::DISPLAY && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground != 6952 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground != 6954 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground != 5638 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground != 6946 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground != 6948 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground != 2978 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground != 1420 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground != 6214 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground != 1006 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground != 656 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground != 1420 && getItemDef(worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground).blockType != BlockTypes::DONATION && Chance >= 43) {
							if (worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground == 0 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].background == 0 || worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground == 0 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].background == 6864) continue;
							worlds[iss].items[x - 1 + (y * worlds[iss].width)].fire = true;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									UpdateVisualsForBlock(currentPeer6, true, x - 1, y, getPlyersWorld(currentPeer6));
									Player::OnParticleEffect(currentPeer6, 150, x * 32, y * 32, 0);
								}
							}
						}
						else if (y > 0 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground != 3528 && !worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].water && !worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].fire && !isSeed(worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground) && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground != 8 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground != 6 && getItemDef(worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground).blockType != BlockTypes::LOCK && getItemDef(worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground).blockType != BlockTypes::DISPLAY && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground != 6952 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground != 6954 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground != 5638 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground != 6946 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground != 6948 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground != 2978 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground != 1420 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground != 6214 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground != 1006 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground != 656 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground != 1420 && getItemDef(worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground).blockType != BlockTypes::DONATION && Chance >= 20) {
							if (worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground == 0 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].background == 0 || worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground == 0 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].background == 6864) continue;
							worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].fire = true;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									UpdateVisualsForBlock(currentPeer6, true, x, y - 1, getPlyersWorld(currentPeer6));
									Player::OnParticleEffect(currentPeer6, 150, x * 32, y * 32, 0);
								}
							}
						}
						else if (y < 59 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground != 3528 && !worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].water && !worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].fire && !isSeed(worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground) && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground != 8 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground != 6 && getItemDef(worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground).blockType != BlockTypes::LOCK && getItemDef(worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground).blockType != BlockTypes::DISPLAY && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground != 6952 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground != 6954 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground != 5638 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground != 6946 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground != 6948 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground != 2978 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground != 1420 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground != 6214 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground != 1006 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground != 656 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground != 1420 && getItemDef(worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground).blockType != BlockTypes::DONATION && Chance >= 0) {
							if (worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground == 0 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].background == 0 || worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground == 0 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].background == 6864) continue;
							worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].fire = true;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									UpdateVisualsForBlock(currentPeer6, true, x, y + 1, getPlyersWorld(currentPeer6));
									Player::OnParticleEffect(currentPeer6, 150, x * 32, y * 32, 0);
								}
							}
						}
						jas += 1;
					}
					if (worlds[iss].items[x + (y * worlds[iss].width)].foreground == 4762) {
						auto Chance = rand() % 100;
						if (worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground == 0 && Chance >= 75) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x + 1;
							data3.y = y;
							data3.punchX = x + 1;
							data3.punchY = y;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 4762;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32 + 45, y * 32 + 16, 4762, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground = 4762;
						}
						else if (x > 0 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground == 0 && Chance >= 43) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x - 1;
							data3.y = y;
							data3.punchX = x - 1;
							data3.punchY = y;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 4762;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32 - 22, y * 32 + 16, 4762, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground = 4762;
						}
						else if (y > 0 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground == 0 && Chance >= 20) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x;
							data3.y = y - 1;
							data3.punchX = x;
							data3.punchY = y - 1;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 4762;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32, y * 32 + 16, 4762, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground = 4762;
						}
						else if (y < 59 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground == 0 && Chance >= 0) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x;
							data3.y = y + 1;
							data3.punchX = x;
							data3.punchY = y + 1;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 4762;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32, y * 32 + 16, 4762, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground = 4762;
						}
						jas += 1;
					}
					if (worlds[iss].items[x + (y * worlds[iss].width)].foreground == 7382) {
						auto Chance = rand() % 100;
						if (worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground == 0 && Chance >= 75) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x + 1;
							data3.y = y;
							data3.punchX = x + 1;
							data3.punchY = y;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 7382;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32 + 45, y * 32 + 16, 7382, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground = 7382;
						}
						else if (x > 0 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground == 0 && Chance >= 43) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x - 1;
							data3.y = y;
							data3.punchX = x - 1;
							data3.punchY = y;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 7382;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32 - 22, y * 32 + 16, 7382, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground = 7382;
						}
						else if (y > 0 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground == 0 && Chance >= 25) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x;
							data3.y = y - 1;
							data3.punchX = x;
							data3.punchY = y - 1;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 7382;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32, y * 32 + 16, 7382, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground = 7382;
						}
						else if (y < 59 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground == 0 && Chance >= 5) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x;
							data3.y = y + 1;
							data3.punchX = x;
							data3.punchY = y + 1;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 7382;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32, y * 32 + 16, 7382, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground = 7382;
						}
						jas += 1;
					}
					if (worlds[iss].items[x + (y * worlds[iss].width)].foreground == 9460) {
						auto Chance = rand() % 100;
						if (worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground == 0 && Chance >= 75) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x + 1;
							data3.y = y;
							data3.punchX = x + 1;
							data3.punchY = y;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 9460;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32 + 45, y * 32 + 16, 9460, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground = 9460;
						}
						else if (x > 0 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground == 0 && Chance >= 43) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x - 1;
							data3.y = y;
							data3.punchX = x - 1;
							data3.punchY = y;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 9460;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32 - 22, y * 32 + 16, 9460, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground = 9460;
						}
						else if (y > 0 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground == 0 && Chance >= 30) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x;
							data3.y = y - 1;
							data3.punchX = x;
							data3.punchY = y - 1;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 9460;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32, y * 32 + 16, 9460, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground = 9460;
						}
						else if (y < 59 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground == 0 && Chance >= 10) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x;
							data3.y = y + 1;
							data3.punchX = x;
							data3.punchY = y + 1;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 9460;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32, y * 32 + 16, 9460, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground = 9460;
						}
						jas += 1;
					}
					if (worlds[iss].items[x + (y * worlds[iss].width)].foreground == 9468) {
						auto Chance = rand() % 100;
						if (worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground == 0 && Chance >= 85) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x + 1;
							data3.y = y;
							data3.punchX = x + 1;
							data3.punchY = y;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 9468;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32 + 45, y * 32 + 16, 9468, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground = 9468;
						}
						else if (x > 0 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground == 0 && Chance >= 53) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x - 1;
							data3.y = y;
							data3.punchX = x - 1;
							data3.punchY = y;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 9468;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32 - 22, y * 32 + 16, 9468, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground = 9468;
						}
						else if (y > 0 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground == 0 && Chance >= 35) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x;
							data3.y = y - 1;
							data3.punchX = x;
							data3.punchY = y - 1;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 9468;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32, y * 32 + 16, 9468, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground = 9468;
						}
						else if (y < 59 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground == 0 && Chance >= 15) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x;
							data3.y = y + 1;
							data3.punchX = x;
							data3.punchY = y + 1;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 9468;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32, y * 32 + 16, 9468, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground = 9468;
						}
						jas += 1;
					}
					if (worlds[iss].items[x + (y * worlds[iss].width)].foreground == 10024) {
						auto Chance = rand() % 100;
						if (worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground == 0 && Chance >= 75) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x + 1;
							data3.y = y;
							data3.punchX = x + 1;
							data3.punchY = y;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 10024;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32 + 45, y * 32 + 16, 10024, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground = 10024;
						}
						else if (x > 0 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground == 0 && Chance >= 53) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x - 1;
							data3.y = y;
							data3.punchX = x - 1;
							data3.punchY = y;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 10024;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32 - 22, y * 32 + 16, 10024, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground = 10024;
						}
						else if (y > 0 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground == 0 && Chance >= 33) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x;
							data3.y = y - 1;
							data3.punchX = x;
							data3.punchY = y - 1;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 10024;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32, y * 32 + 16, 10024, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground = 10024;
						}
						else if (y < 59 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground == 0 && Chance >= 20) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x;
							data3.y = y + 1;
							data3.punchX = x;
							data3.punchY = y + 1;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 10024;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32, y * 32 + 16, 10024, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground = 10024;
						}
						jas += 1;
					}
					if (worlds[iss].items[x + (y * worlds[iss].width)].foreground == 10028) {
						auto Chance = rand() % 100;
						if (worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground == 0 && Chance >= 70) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x + 1;
							data3.y = y;
							data3.punchX = x + 1;
							data3.punchY = y;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 10028;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32 + 45, y * 32 + 16, 10028, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x + 1 + (y * worlds[iss].width)].foreground = 10028;
						}
						else if (x > 0 && worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground == 0 && Chance >= 53) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x - 1;
							data3.y = y;
							data3.punchX = x - 1;
							data3.punchY = y;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 10028;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32 - 22, y * 32 + 16, 10028, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x - 1 + (y * worlds[iss].width)].foreground = 10028;
						}
						else if (y > 0 && worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground == 0 && Chance >= 40) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x;
							data3.y = y - 1;
							data3.punchX = x;
							data3.punchY = y - 1;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 10028;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32, y * 32 + 16, 10028, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x + (y * worlds[iss].width - worlds[iss].width)].foreground = 10028;
						}
						else if (y < 59 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground == 0 && Chance >= 25) {
							PlayerMoving data3;
							data3.packetType = 0x3;
							data3.characterState = 0x0;
							data3.x = x;
							data3.y = y + 1;
							data3.punchX = x;
							data3.punchY = y + 1;
							data3.XSpeed = 0;
							data3.YSpeed = 0;
							data3.netID = -1;
							data3.plantingTree = 10028;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									SendParticleEffect(currentPeer6, x * 32, y * 32 + 16, 10028, 97, 0);
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground = 10028;
						}
						jas += 1;
					}
				}
			}
		}
		for (auto i = 0; i < worlds.size(); i++) {
			if (i >= worlds.size()) {
				SendConsole("worlds.size() was larger than loop size (c797)", "ERROR");
				continue;
			}
			if (worlds[i].items == nullptr) {
				cout << "was nullptr value case 6" << endl;
				continue;
			}
			if (worlds[i].name == "error" || worlds[i].name == "EXIT") continue;		
			if (getPlayersCountInWorldEvent(worlds[i], worlds[i].name) <= 0) continue; /*to avoid events in empty worlds*/
			if (getPlayersCountInWorldEvent(worlds[i], worlds[i].name) >= 5) {
				/*Choose event type*/
				string Notification = "";
				auto ItemID = 0;
				auto Count = 0;
				const auto Time = 0; /*Not used for now*/
				auto Multiple = 0; /*How much times the drop will be repeated*/
				int values;
				srand(time(nullptr));
				if (HarvestEvent) values = rand() % 15 + 1;
				else if (ValentineEvent) values = rand() % 30 + 1;
				else values = rand() % 13 + 1;
				switch (values)
				{
				case 1: /*World Lock Event*/
				{
					Notification = "`2World Locks Rain! `oYou have `wUnlimited `oseconds to find the `w3 `#World Locks `oHidden in this world!";
					ItemID = 242;
					Count = 1;
					Multiple = 3;
					break;
				}
				case 2: /*Surgery Split Event*/
				{
					Notification = "`2Surgical Split! `oYou have `wUnlimited `oseconds to find the `#Surgery Tool Pack `oHidden in this world!";
					ItemID = 9644;
					Count = 1;
					Multiple = 1;
					break;
				}
				case 3: /*The Fireworks Event*/
				{
					Notification = "`2Bright Lights! `oYou have `wUnlimited `oseconds to find the `w5 `#Fireworks `oHidden in this world!";
					ItemID = 834;
					Count = 1;
					Multiple = 5;
					break;
				}
				case 4: /*Beat The Heat!*/
				{
					Notification = "`2Beat The Heat! `oYou have `wUnlimited `oseconds to find the `w5 `#Water Buckets `oHidden in this world!";
					ItemID = 822;
					Count = 1;
					Multiple = 5;
					break;
				}
				case 5: /*Beat The Heat!*/
				{
					Notification = "`2Beat The Heat! `oYou have `wUnlimited `oseconds to find the `w5 `#Water Buckets `oHidden in this world!";
					ItemID = 822;
					Count = 1;
					Multiple = 5;
					break;
				}
				case 6: /*Luck of the Growish Event*/
				{
					Notification = "`2Luck of the Growish! `oYou have `wUnlimited `oseconds to find the `#Lucky Clover `oHidden in this world!";
					ItemID = 528;
					Count = 1;
					Multiple = 1;
					break;
				}
				case 7: /*Beautiful Crystal Event*/
				{
					Notification = "`2Beautiful Crystal! `oYou have `wUnlimited `oseconds to find the `#Crystal Block Seed `oHidden in this world!";
					ItemID = 263;
					Count = 1;
					Multiple = 1;
					break;
				}
				case 8: /*Magical Seeds Event*/
				{
					Notification = "`2Beautiful Crystal! `oYou have `wUnlimited `oseconds to find the `#Crystal Block Seed `oHidden in this world!";
					ItemID = 263;
					Count = 1;
					Multiple = 1;
					break;
				}
				case 9: /*Luck of the Growish Event*/
				{
					Notification = "`2Luck of the Growish! `oYou have `wUnlimited `oseconds to find the `#Lucky Clover `oHidden in this world!";
					ItemID = 528;
					Count = 1;
					Multiple = 1;
					break;
				}
				case 10: /*Shinny Potion*/
				{
					Notification = "`2Shinny Potion! `oYou have `wUnlimited `oseconds to find the `#Punch Potion `oHidden in this world!";
					ItemID = 6918;
					Count = 1;
					Multiple = 1;
					break;
				}
				case 11: /*What's that?*/
				{
					Notification = "`2What's that?! `oYou have `wUnlimited `oseconds to find the `#Doohickey `oHidden in this world!";
					ItemID = 1396;
					Count = 1;
					Multiple = 1;
					break;
				}
				case 12: /*Egg Hunt*/
				{
					Notification = "`2Egg Hunt! `oGo find them eggs! `w20 `#Magic Eggs `owill spawn in the world!";
					ItemID = 611;
					Count = 1;
					Multiple = 20;
					break;
				}
				case 13: /*Jackpot*/
				{
					Notification = "`2Jackpot! `oGems are spawned throughout the world!";
					ItemID = 112;
					Count = 1;
					Multiple = 100;
					break;
				}
				case 14: /*Songpyeon Hunt (harvest fest only)*/
				{
					Notification = "`2Songpyeon Hunt! `oYou have `wUnlimited `oseconds to find the `w3 `#Songpyeons `oHidden in this world!";
					ItemID = 1056;
					Count = 1;
					Multiple = 3;
					break;
				}
				case 15: /*Mooncake Rain (harvest fest only)*/
				{
					vector<int> CakeBase{ 1058, 1094, 1096, 1098, 1828, 3870, 7058 };
					const int Index = rand() % CakeBase.size();
					const auto IID = CakeBase[Index];
					Notification = "`2Mooncake Rain! `oYou have `wUnlimited `oseconds to find the `#" + getItemDef(IID).name + " `oHidden in this world!";
					ItemID = IID;
					Count = 1;
					Multiple = 5;
					break;
				}
				case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29: case 30: /*Share The Love (valentine event only)*/
				{
					Notification = "`2Share The Love!: `oCelebrite Valentine's with free treasure!";
					bool success = true;
					for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
					{
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (EventWorld(currentPeer, worlds[i].name)) /*Display message for all players in world*/
						{
							SaveItemMoreTimes(3402, 1, currentPeer, success, static_cast<PlayerInfo*>(currentPeer->data)->rawName + " from special valentine event");
							SendTradeEffect(currentPeer, 3402, static_cast<PlayerInfo*>(currentPeer->data)->netID, static_cast<PlayerInfo*>(currentPeer->data)->netID, 150);
						}
					}
					break;
				}
				default: break;
				}
				for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (EventWorld(currentPeer, worlds[i].name)) /*Display message for all players in world*/
					{
						Player::OnAddNotification(currentPeer, Notification, "audio/cumbia_horns.wav", "interface/large/special_event.rttex");
					}
				}
				if (ItemID != 0) SpawnEventItem(worlds[i].name, ItemID, Count, Time, worlds[i].width, worlds[i].height, Multiple); /*Spawn the Item*/
				break;
			}
		}
	}
}

inline void WorldDisasters() {
	while (true) {
		sleep(900);
		bool Sandstorm = false;
		bool Firestorm = false;
		bool Cometrain = false;
		auto worlds = worldDB.getRandomWorlds();
		for (auto iss = 0; iss < worlds.size(); iss++) {
			if (iss >= worlds.size()) {
				SendConsole("worlds.size() was larger than loop size (c980)", "ERROR");
				continue;
			}
			if (worlds[iss].items == nullptr) {
				cout << "was nullptr value case 6" << endl;
				continue;
			}
			if (worlds[iss].name == "error" || worlds[iss].name == "EXIT") continue;
			if (getPlayersCountInWorldEvent(worlds[iss], worlds[iss].name) <= 0) continue;
			bool NoEvent = false;
			for (auto jsss = 0; jsss < worlds[iss].width * worlds[iss].height; jsss++) {
				if (worlds[iss].items[jsss].foreground == 10422 && worlds[iss].items[jsss].activated) {
					NoEvent = true;
				}
			}
			if (NoEvent) {
				SendConsole("Skipped event in " + worlds[iss].name + "", "EVENT");
				continue;
			}
			int sukure = 0;
			if (rand() % 100 < 50) {
				Sandstorm = true;
			} else {
				Firestorm = true;
			}
			for (auto jas = 0; jas < worlds[iss].width * worlds[iss].height; jas++) {
				auto x = (jas % worlds[iss].width);
				auto y = (jas / worlds[iss].width);
				if (x / 32 >= 0 && y / 32 >= 0 && x / 32 <= worlds[iss].width && y / 32 <= worlds[iss].height) {
					if (Sandstorm) {
						if (worlds[iss].items[x + (y * worlds[iss].width)].foreground == 0 && sukure <= 300 && rand() % 100 <= 40) {
							sukure++;
							worlds[iss].items[x + (y * worlds[iss].width)].foreground = 442;
							PlayerMoving data4;
							data4.packetType = 0x3;
							data4.characterState = 0x0;
							data4.x = x;
							data4.y = y + 1;
							data4.punchX = x;
							data4.punchY = y + 1;
							data4.XSpeed = 0;
							data4.YSpeed = 0;
							data4.netID = -1;
							data4.plantingTree = 442;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									auto raw = packPlayerMoving(&data4);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
						}
					} else {
						if (worlds[iss].items[x + (y * worlds[iss].width)].foreground != 0 && !isSeed(worlds[iss].items[x + (y * worlds[iss].width)].foreground) && worlds[iss].items[x + (y * worlds[iss].width)].foreground != 6 && worlds[iss].items[x + (y * worlds[iss].width)].foreground != 8 && rand() % 100 <= 16) {
							worlds[iss].items[x + (y * worlds[iss].width)].fire = true;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									UpdateVisualsForBlock(currentPeer6, true, x, y, getPlyersWorld(currentPeer6));
									Player::OnParticleEffect(currentPeer6, 150, x * 32, y * 32, 0);
								}
							}
						}
					}
				}
			}
			for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
				if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
				if (EventWorld(currentPeer6, worlds[iss].name)) {
					if (Sandstorm) Player::OnConsoleMessage(currentPeer6, "Sandstorm comes into your world!");
					if (Firestorm) Player::OnConsoleMessage(currentPeer6, "Firestorm comes into your world!");
				} else {
					if (Sandstorm) {
						Player::OnConsoleMessage(currentPeer6, "Sandstorm fills " + worlds[iss].name + " with sands!");
						Player::PlayAudio(currentPeer6, "audio/explode.wav", 0);
					}
					if (Firestorm) {
						Player::OnConsoleMessage(currentPeer6, "Huge firestorm smashes " + worlds[iss].name + " into tiny bits!");
						Player::PlayAudio(currentPeer6, "audio/fireball.wav", 0);
					}
					if (Cometrain) {
						Player::OnConsoleMessage(currentPeer6, "Comet rain comes into " + worlds[iss].name + "");
						Player::PlayAudio(currentPeer6, "audio/droar.wav", 0);
					}
				}
			}
			break;
		}
	}
}

inline void WorldPhysics() {
	while (true) {
		usleep(150000);
		auto worlds = worldDB.getRandomWorlds();
		for (auto iss = 0; iss < worlds.size(); iss++) {
			if (iss >= worlds.size()) {
				SendConsole("worlds.size() was larger than loop size (c1073)", "ERROR");
				continue;
			}
			if (worlds[iss].items == nullptr) {
				cout << "was nullptr value" << endl;
				continue;
			}
			if (worlds[iss].name == "error" || worlds[iss].name == "EXIT") continue;
			if (getPlayersCountInWorldEvent(worlds[iss], worlds[iss].name) <= 0) continue;
			bool Physics = false;
			for (auto jsss = 0; jsss < worlds[iss].width * worlds[iss].height; jsss++) {
				if (worlds[iss].items[jsss].foreground == 10432 && worlds[iss].items[jsss].activated) {
					Physics = true;
				}
			}
			for (auto jas = 0; jas < worlds[iss].width * worlds[iss].height; jas++) {
				auto x = (jas % worlds[iss].width);
				auto y = (jas / worlds[iss].width);
				if (x / 32 >= 0 && y / 32 >= 0 && x / 32 <= worlds[iss].width && y / 32 <= worlds[iss].height) {
					if (worlds[iss].items[x + (y * worlds[iss].width)].foreground == 3072) {
						if (worlds[iss].items[x + (y * worlds[iss].width)].firehousestate == 120) {
							worlds[iss].items[x + (y * worlds[iss].width)].firehousestate = 0;
							for (auto magics = 0; magics < worlds[iss].width * worlds[iss].height; magics++) {
								int whyimgayx = (magics % worlds[iss].width);
								int whyimgayy = (magics / worlds[iss].width);
								if (whyimgayx / 32 >= 0 && whyimgayy / 32 >= 0 && whyimgayx / 32 <= worlds[iss].width && whyimgayy / 32 <= worlds[iss].height) {
									if (whyimgayy == 59 || whyimgayy == 99 || worlds[iss].width == 60 && worlds[iss].height == 30 && whyimgayy == 29) continue; /*nezinia*/
									cout << "x " + to_string(whyimgayx) << endl;
									cout << "y " + to_string(whyimgayy) << endl;
									if (worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width + worlds[iss].width)].fire) {
										worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width + worlds[iss].width)].fire = false;
										for (ENetPeer* net_peersss = server->peers; net_peersss < &server->peers[server->peerCount]; ++net_peersss) {
											if (net_peersss->state != ENET_PEER_STATE_CONNECTED) continue;
											if (EventWorld(net_peersss, worlds[iss].name)) {
												UpdateBlockState(net_peersss, whyimgayx, whyimgayy + 1, false, getPlyersWorld(net_peersss));
												break;
											}
										}
										for (ENetPeer* net_peers = server->peers; net_peers < &server->peers[server->peerCount]; ++net_peers) {
											if (net_peers->state != ENET_PEER_STATE_CONNECTED) continue;
											if (EventWorld(net_peers, worlds[iss].name)) {
												Player::OnParticleEffect(net_peers, 149, whyimgayx * 32, whyimgayy * 32 + 14, 0);
											}
										}
										break;
									}
								}
							}
						} else {
							worlds[iss].items[x + (y * worlds[iss].width)].firehousestate++;
						}
					}
					if (worlds[iss].items[x + (y * worlds[iss].width)].foreground == 6954) {
						if (worlds[iss].items[x + (y * worlds[iss].width)].placestate == 12) {
						worlds[iss].items[x + (y * worlds[iss].width)].placestate = 0;
						int PlaceID = 0;
						int IdentificatorID = worlds[iss].items[x + (y * worlds[iss].width)].vid;
						if (worlds[iss].items[x + (y * worlds[iss].width)].mid != 0 && worlds[iss].items[x + (y * worlds[iss].width)].mc > 0) {
							bool Imanoma = false;
							PlaceID = worlds[iss].items[x + (y * worlds[iss].width)].mid;
							for (auto magics = 0; magics < worlds[iss].width * worlds[iss].height; magics++) {
								int whyimgayx = (magics % worlds[iss].width);
								int whyimgayy = (magics / worlds[iss].width);
								if (whyimgayx / 32 >= 0 && whyimgayy / 32 >= 0 && whyimgayx / 32 <= worlds[iss].width && whyimgayy / 32 <= worlds[iss].height) {
									if (whyimgayy == 59 || whyimgayy == 99 || worlds[iss].width == 60 && worlds[iss].height == 30 && whyimgayy == 29) continue; /*nezinia*/
									if (worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width + worlds[iss].width)].foreground == IdentificatorID && worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width)].foreground == 0) {
										Imanoma = true;
										break;
									} else if (worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width)].destroy && worlds[iss].notification == "") {
										cout << "notification is set" << endl;
										worlds[iss].notification = "Warning! Some of machines failed to perform their actions because of incorrect configuration, in this situation you need to make your machines work more logically!";
										//break;
									}
								}
							}
							if (!Imanoma) continue;						
							worlds[iss].items[x + (y * worlds[iss].width)].mc -= 1;
							for (ENetPeer* currentPeer6923 = server->peers; currentPeer6923 < &server->peers[server->peerCount]; ++currentPeer6923) { 
								if (currentPeer6923->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6923, worlds[iss].name)) {
									if (worlds[iss].items[x + (y * worlds[iss].width)].mc <= 0) {
										SendItemSucker(currentPeer6923, 6954, x, y, worlds[iss].items[x + (y * worlds[iss].width)].mid, -1, true, true, worlds[iss].items[x + (y * worlds[iss].width)].background);
									} else {
										SendItemSucker(currentPeer6923, 6954, x, y, worlds[iss].items[x + (y * worlds[iss].width)].mid, 1, true, true, worlds[iss].items[x + (y * worlds[iss].width)].background);
									}
								}
							}
						} else if (worlds[iss].items[x + (y * worlds[iss].width)].rm) {
							bool Imanoma = false;
							for (auto magics = 0; magics < worlds[iss].width * worlds[iss].height; magics++) {
								int whyimgayx = (magics % worlds[iss].width);
								int whyimgayy = (magics / worlds[iss].width);
								if (whyimgayx / 32 >= 0 && whyimgayy / 32 >= 0 && whyimgayx / 32 <= worlds[iss].width && whyimgayy / 32 <= worlds[iss].height) {
									if (whyimgayy == 59 || whyimgayy == 99 || worlds[iss].width == 60 && worlds[iss].height == 30 && whyimgayy == 29) continue; /*nezinia*/
									if (worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width + worlds[iss].width)].foreground == IdentificatorID && worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width)].foreground == 0) {
										Imanoma = true;
										break;
									} else if (worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width)].destroy && worlds[iss].notification == "") {
										cout << "notification is set" << endl;
										worlds[iss].notification = "Warning! Some of machines failed to perform their actions because of incorrect configuration, in this situation you need to make your machines work more logically!";
										//break;
									}
								}
							}
							if (!Imanoma) continue;
							for (auto magics = 0; magics < worlds[iss].width * worlds[iss].height; magics++) {
								int whyimgayx = (magics % worlds[iss].width);
								int whyimgayy = (magics / worlds[iss].width);
								if (whyimgayx / 32 >= 0 && whyimgayy / 32 >= 0 && whyimgayx / 32 <= worlds[iss].width && whyimgayy / 32 <= worlds[iss].height) {
									if (whyimgayy == 59 || whyimgayy == 99 || worlds[iss].width == 60 && worlds[iss].height == 30 && whyimgayy == 29) continue; /*nezinia*/
									if (worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width)].foreground == 5638 && worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width)].mid == worlds[iss].items[x + (y * worlds[iss].width)].mid && worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width)].mc > 0) {
										PlaceID = worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width)].mid;
										worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width)].mc -= 1;
										for (ENetPeer* currentPeer692 = server->peers; currentPeer692 < &server->peers[server->peerCount]; ++currentPeer692) { 
											if (currentPeer692->state != ENET_PEER_STATE_CONNECTED) continue;
											if (EventWorld(currentPeer692, worlds[iss].name)) {
												if (worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width)].mc <= 0) {
													SendItemSucker(currentPeer692, 5638, whyimgayx, whyimgayy, worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width)].mid, 0, true, true, worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width)].background);
												}
												else if (worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width)].mc >= 5000) {
													SendItemSucker(currentPeer692, 5638, whyimgayx, whyimgayy, worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width)].mid, -1, true, true, worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width)].background);
												}
												else {
													SendItemSucker(currentPeer692, 5638, whyimgayx, whyimgayy, worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width)].mid, 1, true, true, worlds[iss].items[whyimgayx + (whyimgayy * worlds[iss].width)].background);
												}
											}
										}
										break; /*and move on*/
									}
								}
							}
						}
						if (PlaceID != 0) {
								for (auto magic = 0; magic < worlds[iss].width * worlds[iss].height; magic++) {
									x = (magic % worlds[iss].width);
									y = (magic / worlds[iss].width);
									if (x / 32 >= 0 && y / 32 >= 0 && x / 32 <= worlds[iss].width && y / 32 <= worlds[iss].height) {
										if (worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground == IdentificatorID && worlds[iss].items[x + (y * worlds[iss].width)].foreground == 0) {
											for (ENetPeer* currentPeer69 = server->peers; currentPeer69 < &server->peers[server->peerCount]; ++currentPeer69) { 
												if (currentPeer69->state != ENET_PEER_STATE_CONNECTED) continue;
												if (EventWorld(currentPeer69, worlds[iss].name)) {
													Player::OnParticleEffect(currentPeer69, 229, x * 32, y * 32, 0);
												}
											}
											worlds[iss].items[x + (y * worlds[iss].width)].foreground = PlaceID;
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
											data3.plantingTree = PlaceID;
											bool UpdateTreeVisuals3 = false;
											if (isSeed(PlaceID)) {
												UpdateTreeVisuals3 = true;
												int growTimeSeed = getItemDef(worlds[iss].items[x + (y * worlds[iss].width)].foreground - 1).rarity * getItemDef(worlds[iss].items[x + (y * worlds[iss].width)].foreground - 1).rarity * getItemDef(worlds[iss].items[x + (y * worlds[iss].width)].foreground - 1).rarity;
												growTimeSeed += 30 * getItemDef(worlds[iss].items[x + (y * worlds[iss].width)].foreground - 1).rarity;
												if (worlds[iss].items[x + (y * worlds[iss].width)].foreground - 1 == 954) growTimeSeed = 1800;
												if (worlds[iss].items[x + (y * worlds[iss].width)].foreground - 1 == 340) growTimeSeed = 3600;
												if (worlds[iss].items[x + (y * worlds[iss].width)].foreground - 1 == 5666) growTimeSeed = 2700;
												if (worlds[iss].items[x + (y * worlds[iss].width)].foreground - 1 == 4584) growTimeSeed = 2400;
												if (worlds[iss].items[x + (y * worlds[iss].width)].foreground - 1 == 4762) growTimeSeed = 14544;
												if (worlds[iss].items[x + (y * worlds[iss].width)].foreground - 1 == 7382) growTimeSeed = 22544;
												if (worlds[iss].items[x + (y * worlds[iss].width)].foreground - 1 == 9460) growTimeSeed = 29544;
												if (worlds[iss].items[x + (y * worlds[iss].width)].foreground - 1 == 9468) growTimeSeed = 36544;
												if (worlds[iss].items[x + (y * worlds[iss].width)].foreground - 1 == 10024) growTimeSeed = 56544;
												if (worlds[iss].items[x + (y * worlds[iss].width)].foreground - 1 == 10028) growTimeSeed = 86400;
												if (worlds[iss].items[x + (y * worlds[iss].width)].foreground - 1 == 10392) growTimeSeed = 7382;
												worlds[iss].items[x + (y * worlds[iss].width)].growtime = (GetCurrentTimeInternalSeconds() + growTimeSeed);
												if (getItemDef(worlds[iss].items[x + (y * worlds[iss].width)].foreground).rarity == 999) {
													worlds[iss].items[x + (y * worlds[iss].width)].fruitcount = (rand() % 1) + 1;
												} else {
													worlds[iss].items[x + (y * worlds[iss].width)].fruitcount = (rand() % 6) + 1;
												}
												if (getItemDef(worlds[iss].items[x + (y * worlds[iss].width)].foreground - 1).blockType == BlockTypes::CLOTHING) worlds[iss].items[x + (y * worlds[iss].width)].fruitcount = (rand() % 2) + 1;
											}
											for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
												if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
												if (EventWorld(currentPeer6, worlds[iss].name)) {
													auto raw = packPlayerMoving(&data3);
													raw[2] = 0;
													raw[3] = 0;
													SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
													if (UpdateTreeVisuals3) {
														UpdateTreeVisuals(currentPeer6, worlds[iss].items[x + (y * worlds[iss].width)].foreground, x, y, worlds[iss].items[x + (y * worlds[iss].width)].background, worlds[iss].items[x + (y * worlds[iss].width)].fruitcount, 0, true, 0);
													}
												}
											}
											break;
										}
									}
								}
							}
						} else {
							worlds[iss].items[x + (y * worlds[iss].width)].placestate++;
						}
					}
					if (worlds[iss].items[x + (y * worlds[iss].width)].foreground == 6952 && worlds[iss].items[x + (y * worlds[iss].width)].mid != 0) {
						if (worlds[iss].items[x + (y * worlds[iss].width)].breakstate == 5) {
							worlds[iss].items[x + (y * worlds[iss].width)].breakstate = 0;
							int destroyid = worlds[iss].items[x + (y * worlds[iss].width)].mid;
							bool targetSeed = worlds[iss].items[x + (y * worlds[iss].width)].rm;
							for (auto magic = 0; magic < worlds[iss].width * worlds[iss].height; magic++) {
								x = (magic % worlds[iss].width);
								y = (magic / worlds[iss].width);
								if (x / 32 >= 0 && y / 32 >= 0 && x / 32 <= worlds[iss].width && y / 32 <= worlds[iss].height) {
									if (!worlds[iss].items[x + (y * worlds[iss].width)].destroy && worlds[iss].items[x + (y * worlds[iss].width)].foreground == destroyid || worlds[iss].items[x + (y * worlds[iss].width)].background == destroyid) {
										if (isSeed(worlds[iss].items[x + (y * worlds[iss].width)].foreground) && calcBanDuration(worlds[iss].items[x + (y * worlds[iss].width)].growtime) != 0) continue;
										for (ENetPeer* currentPeer69 = server->peers; currentPeer69 < &server->peers[server->peerCount]; ++currentPeer69) { 
											if (currentPeer69->state != ENET_PEER_STATE_CONNECTED) continue;
											if (EventWorld(currentPeer69, worlds[iss].name)) {
												Player::OnParticleEffect(currentPeer69, 229, x * 32, y * 32, 0);
											}
										}
										auto count = 0;
										for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
											if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
											if (static_cast<PlayerInfo*>(currentPeer->data)->currentWorld == worlds[iss].name) {
												count++;
											}
										}
										if (count <= 0) {
											if (!worlds[iss].items[x + (y * worlds[iss].width)].destroy && isSeed(worlds[iss].items[x + (y * worlds[iss].width)].foreground) || !worlds[iss].items[x + (y * worlds[iss].width)].destroy && worlds[iss].items[x + (y * worlds[iss].width)].breakbotstate > getItemDef(worlds[iss].items[x + (y * worlds[iss].width)].foreground).breakHits) {
												worlds[iss].items[x + (y * worlds[iss].width)].breakbotstate = 0;
												worlds[iss].items[x + (y * worlds[iss].width)].destroy = true;
											} else {
												worlds[iss].items[x + (y * worlds[iss].width)].breakbotstate++;
											}											
										} else {
											for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
                                				if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
												if (EventWorld(currentPeer6, worlds[iss].name)) {
													sendTileUpdate(x, y, 18, -1, currentPeer6, getPlyersWorld(currentPeer6));
													break;
												}
											}
										}
										break;
									}
								}
							}
						} else {
							worlds[iss].items[x + (y * worlds[iss].width)].breakstate++;
						}
					}
					if (isSeed(worlds[iss].items[x + (y * worlds[iss].width)].foreground) && calcBanDuration(worlds[iss].items[x + (y * worlds[iss].width)].growtime) == 0) {
						for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
                            if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
                            if (EventWorld(currentPeer6, worlds[iss].name)) {
								UpdateTreeVisuals(currentPeer6, worlds[iss].items[x + (y * worlds[iss].width)].foreground, x, y, worlds[iss].items[x + (y * worlds[iss].width)].background, worlds[iss].items[x + (y * worlds[iss].width)].fruitcount, 999999999, false, 0);
							}
						}
					}
					if (worlds[iss].items[x + (y * worlds[iss].width)].activated) {
						for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
                            if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
                            if (EventWorld(currentPeer6, worlds[iss].name)) {
								UpdateBlockState(currentPeer6, x, y, true, getPlyersWorld(currentPeer6));
							}
						}
					}
					if (worlds[iss].items[x + (y * worlds[iss].width)].foreground == 202 || worlds[iss].items[x + (y * worlds[iss].width)].foreground == 204 || worlds[iss].items[x + (y * worlds[iss].width)].foreground == 206 || worlds[iss].items[x + (y * worlds[iss].width)].foreground == 4994) {
						for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
                            if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
                            if (EventWorld(currentPeer6, worlds[iss].name)) {
								if (worlds[iss].items[x + (y * worlds[iss].width)].monitorname == static_cast<PlayerInfo*>(currentPeer6->data)->rawName) ApplyLockPacket(getPlyersWorld(currentPeer6), currentPeer6, x, y, worlds[iss].items[x + (y * worlds[iss].width)].foreground, static_cast<PlayerInfo*>(currentPeer6->data)->netID);
								else if (worlds[iss].items[x + (y * worlds[iss].width)].opened) ApplyLockPacket(getPlyersWorld(currentPeer6), currentPeer6, x, y, worlds[iss].items[x + (y * worlds[iss].width)].foreground, -3);
								else ApplyLockPacket(getPlyersWorld(currentPeer6), currentPeer6, x, y, worlds[iss].items[x + (y * worlds[iss].width)].foreground, -1);
							}
						}
					}
					if (worlds[iss].items[x + (y * worlds[iss].width)].foreground == 442 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground == 0 && !worlds[iss].items[x + (y * worlds[iss].width)].atnaujino || Physics && getItemDef(worlds[iss].items[x + (y * worlds[iss].width)].foreground).blockType == BlockTypes::FOREGROUND && worlds[iss].items[x + (y * worlds[iss].width)].foreground != 0 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground == 0 && !worlds[iss].items[x + (y * worlds[iss].width)].atnaujino || Physics && getItemDef(worlds[iss].items[x + (y * worlds[iss].width)].foreground).blockType == BlockTypes::PAIN_BLOCK && worlds[iss].items[x + (y * worlds[iss].width)].foreground != 0 && worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground == 0 && !worlds[iss].items[x + (y * worlds[iss].width)].atnaujino) {
						if (worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground == 0) {
							worlds[iss].items[x + (y * worlds[iss].width)].atnaujino = false;
							worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].atnaujino = true;
							int beforeid = worlds[iss].items[x + (y * worlds[iss].width)].foreground;
							worlds[iss].items[x + (y * worlds[iss].width)].foreground = 0;
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
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									auto raw = packPlayerMoving(&data3);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
							worlds[iss].items[x + (y * worlds[iss].width + worlds[iss].width)].foreground = beforeid;
							PlayerMoving data4;
							data4.packetType = 0x3;
							data4.characterState = 0x0;
							data4.x = x;
							data4.y = y + 1;
							data4.punchX = x;
							data4.punchY = y + 1;
							data4.XSpeed = 0;
							data4.YSpeed = 0;
							data4.netID = -1;
							data4.plantingTree = beforeid;
							for (ENetPeer* currentPeer6 = server->peers; currentPeer6 < &server->peers[server->peerCount]; ++currentPeer6) {
								if (currentPeer6->state != ENET_PEER_STATE_CONNECTED) continue;
								if (EventWorld(currentPeer6, worlds[iss].name)) {
									auto raw = packPlayerMoving(&data4);
									raw[2] = 0;
									raw[3] = 0;
									SendPacketRaw(4, raw, 56, nullptr, currentPeer6, ENET_PACKET_FLAG_RELIABLE);
								}
							}
						}
					}
				}
				if (jas == (worlds[iss].width * worlds[iss].height) - 1) {
					for (auto magic = 0; magic < worlds[iss].width * worlds[iss].height; magic++) {
						x = (magic % worlds[iss].width);
						y = (magic / worlds[iss].width);
						if (x / 32 >= 0 && y / 32 >= 0 && x / 32 <= worlds[iss].width && y / 32 <= worlds[iss].height) {
							worlds[iss].items[x + (y * worlds[iss].width)].atnaujino = false;
						}
					}
					break;
				}
			}
		}
	}
}
