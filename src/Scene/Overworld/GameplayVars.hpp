#pragma once

//player
static constexpr float HeatRegen = 100.f;
static constexpr float MoveHeatCost = 8.f;
static constexpr float ShootHeatCost = 2.f;
static constexpr float ShotgunHeatCost = 10.f;
static constexpr float LaserHeatCost = 50.f; //per second

static constexpr int BaseDamage = 20;
static constexpr int ShotgunDamage = 10;
static constexpr float LaserDamage = 7;

//drone
constexpr int DroneXpValue = 75;
constexpr int DroneDamage = 1;

//tutorials

namespace gamevars
{
	extern bool TutorialsEnabled;
	extern int PlayerMoney;
	extern bool WeaponUnlocked[4];
}