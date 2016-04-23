
#include <string>
#include "SFML/Graphics.hpp"

typedef unsigned short ushort;

enum POwner {P0 = -1, P1, P2, P3, P4, P5, P6, P7, P8, PCount};
enum CType {VASSAL, HERO, MINION, MORTAL, TypeTotal};

class CreatureComponentC
{

private:
	
	POwner Owner;
	std::string Name;
	
	sf::Vector2i HexPos;

	ushort Health;
	ushort Resource;

	ushort move_land;
	ushort move_water;
	ushort move_air;

	CType type;

	ushort val_chaos;
	ushort val_light;
	ushort val_dark;
	ushort val_entropy;

public:

	//constructor
	CreatureComponentC();
	CreatureComponentC(POwner NewOwner, std::string NewName, sf::Vector2i NewHexPosition, ushort NewHealth, ushort NewResource,
		ushort NewLandMovement, ushort NewWaterMovement, ushort NewAirMovement,
		CType NewType, ushort NewChaosValue, ushort NewLightValue, ushort NewDarkValue, ushort NewEntropyValue);

	~CreatureComponentC();

	//Getters
	const POwner GetOwner() const;
	const std::string GetName() const;

	const sf::Vector2i GetHexPosition() const;

	const ushort GetHealth() const;
	const ushort GetResource() const;

	const ushort GetLandMovement() const;
	const ushort GetWaterMovement() const;
	const ushort GetAirMovement() const;
	
	const CType GetType() const;

	const ushort GetChaosValue() const;
	const ushort GetLightValue() const;
	const ushort GetDarkValue() const;
	const ushort GetEntropValue() const;

	//Setters
	void SetOwner(POwner);
	void SetName(std::string);

	void SetHexPosition(sf::Vector2i);

	void SetHealth(ushort);
	void SetResource(ushort);

	void SetLandMovement(ushort);
	void SetWaterMovement(ushort);
	void SetAirMovement(ushort);

	void SetType(CType);

	void SetChaosValue(ushort);
	void SetLightValue(ushort);
	void SetDarkValue(ushort);
	void SetEntropValue(ushort);
};