
#include "CreatureComponentC.h"


//constructors
CreatureComponentC::CreatureComponentC() : 
Owner(P0),
Name("Default Construction"),
HexPos(sf::Vector2u(0, 0)),
Health(1000),
Resource(0),
move_land(3),
move_water(3),
move_air(3),
type(MINION),
val_chaos(10),
val_light(10),
val_dark(10),
val_entropy(10)
{
	//Nothing to see here folks
}

CreatureComponentC::CreatureComponentC(POwner NewOwner, std::string NewName, sf::Vector2i NewHexPosition, ushort NewHealth, ushort NewResource,
	ushort NewLandMovement, ushort NewWaterMovement, ushort NewAirMovement,
	CType NewType, ushort NewChaosValue, ushort NewLightValue, ushort NewDarkValue, ushort NewEntropyValue) :
Owner(NewOwner),
Name(NewName),
Health(NewHealth),
Resource(NewResource),
HexPos(NewHexPosition),
move_land(NewLandMovement),
move_water(NewWaterMovement),
move_air(NewAirMovement),
type(NewType),
val_chaos(NewChaosValue),
val_light(NewLightValue),
val_dark(NewDarkValue),
val_entropy(NewEntropyValue)
{
	//Don't want to use this one...
}

CreatureComponentC::~CreatureComponentC()
{

}

//Getters
const POwner CreatureComponentC::GetOwner() const
{
	return Owner;
}
const std::string CreatureComponentC::GetName() const
{
	return Name;
}

const ushort CreatureComponentC::GetHealth() const
{
	return Health;
}

const sf::Vector2i CreatureComponentC::GetHexPosition() const
{
	return HexPos;
}

const ushort CreatureComponentC::GetResource() const
{
	return Resource;
}

const ushort CreatureComponentC::GetLandMovement() const
{
	return move_land;
}
const ushort CreatureComponentC::GetWaterMovement() const
{
	return move_water;
}
const ushort CreatureComponentC::GetAirMovement() const
{
	return move_air;
}

const CType CreatureComponentC::GetType() const
{
	return type;
}

const ushort CreatureComponentC::GetChaosValue() const
{
	return val_chaos;
}
const ushort CreatureComponentC::GetLightValue() const
{
	return val_light;
}
const ushort CreatureComponentC::GetDarkValue() const
{
	return val_dark;
}
const ushort CreatureComponentC::GetEntropValue() const
{
	return val_entropy;
}

//Setters
void CreatureComponentC::SetOwner(POwner NewOwner)
{
	Owner = NewOwner;
}
void CreatureComponentC::SetName(std::string NewName)
{
	Name = NewName;
}

void CreatureComponentC::SetHealth(ushort NewHealth)
{
	Health = NewHealth;
}

void CreatureComponentC::SetHexPosition(sf::Vector2i NewHexPos)
{
	HexPos = NewHexPos;
}

void CreatureComponentC::SetResource(ushort NewResource)
{
	Resource - NewResource;
}

void CreatureComponentC::SetLandMovement(ushort NewLandMovement)
{
	move_land = NewLandMovement;
}
void CreatureComponentC::SetWaterMovement(ushort NewWaterMovement)
{
	move_water = NewWaterMovement;
}
void CreatureComponentC::SetAirMovement(ushort NewAirMovement)
{
	move_air = NewAirMovement;
}

void CreatureComponentC::SetType(CType NewType)
{
	type = NewType;
}

void CreatureComponentC::SetChaosValue(ushort NewChaosValue)
{
	val_chaos = NewChaosValue;
}
void CreatureComponentC::SetLightValue(ushort NewLightValue)
{
	val_light = NewLightValue;
}
void CreatureComponentC::SetDarkValue(ushort NewDarkValue)
{
	val_dark = NewDarkValue;
}
void CreatureComponentC::SetEntropValue(ushort NewEntropyValue)
{
	val_entropy = NewEntropyValue;
}