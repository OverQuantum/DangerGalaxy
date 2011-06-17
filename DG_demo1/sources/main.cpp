/** 
Demo made from Irrlicht sample
*/

/*
110510: SGU ended
110512: SAIS played
110512: Project Idea, (13.05.2011 ~01:30:00 MSK)
110513: Planing started (13.05.2011 22:23:23 MSK)
110531: github repo created
110602: Demo started

110608: ADD: StarSystemConstructor, ->MakeStar, ->MakePlanet
110609: CHG: a bit better star lights
110610: ADD: surface of stars - without lighting each other, better lighting of planets
110612: ADD: autopilot: breaking by space
110613: ADD: markers - highlight all objects in system on distant views; two types
110613: ADD: gravity
110613: ADD: cameraDistanceDegree
110613: ADD: solar system to scale (sun, planets and moon), graviry too weak
110614: ADD: scales defined (for now), gravity to scale
110614: ADD: "speed indicator" (particle-cloud) is locked to ship location
110615: CHG: all physics to double
110615: ADD: 4 levels of thrust
110615: ADD: debug text, diplaying speed in km/s and c
110615: ADD: pseudo-relativistiv effect after 0.8c, speed=c could not be achived
110616: CHG: UTF16 removed
110616: ADD: gravity field info
110616: CHG: gravity radius, inside planets and stars gravity is now linear fading (~r) instead of singularity (~1/r^2)
110617: ADD: build.log
110617: CHG: breaking now used adjustable thrust power
110617: ADD: autopilot to orbiting gravity-dominant object (currently "cheating", as it can use max thrust)


DONE:
+ surface of stars - without lighting each other
+ autopiloting stops
+ gravity
+ all physics to double
+ thrust should be different - interplanet travels and adjusting orbit requires different thrust
+ estimation of gravity domination
+ adjust autopilot to reduce thrust if speed is low
+ autopilot to orbiting gravity-dominant object

TODO
-3map of star system
-?orbiting of gravity-domination body by orbital parameters, not simple euler
- camera further from system, tham 4M? (degree=4000)
- autopilot to travel to specific point
- corona of star and atmosphere of planets by decal/billboard/etc
- handling of errors
? playerShip as separate class, derivate from SpaceObject? (incorporate thrust power e.t.c)
minor:
- better speed indicator
- exponential fading of light sources (?)


QUESTIONS
- how to draw ship passing stars and planets?  [thinking: collision]
- time game koefficient (to pass star system in a matter of minutes/seconds) [current: 1000]
- size game koefficient (planet size in a relation to its orbits) [current: NO]
- size game logarithm (from hypergians stars to small moons/asteroids should be seen)   [current: NO]


CONTROL:
A/D - rotate
W/S - thrust
Space - breaking (autopilot) relative to distant stars
1/2/3/4 - different thrust levels (1 - highest, 4 - lowest)
O - orbiting (around object which product max graviry force at player's ship)
Up/Down - zoom

*/


#ifdef _MSC_VER
// We'll also define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <irrlicht.h>
//#include "driverChoice.h"
#include <SMaterial.h>

using namespace irr;

#define RESOURCE_PATH	"media"
#define CoeffDegreesToRadians  0.01745329

//typedef core::vector3df vector3d;


typedef core::stringw   text_string;

//Irrlicht works in float, so f32
//DangerGalaxy works in double, so f64
typedef core::vector3d<f32>  vector3df;
typedef core::vector3d<f64>  vector3d;

//#define vector3d core::vector3df

text_string print_f64(f64 value, wchar_t* format)
{
	wchar_t tmp[255];
	//swprintf_s(tmp, 255, format, value);
	swprintf(tmp, 255, format, value);
	return tmp;
}



/*
To receive events like mouse and keyboard input, or GUI events like "the OK
button has been clicked", we need an object which is derived from the
irr::IEventReceiver object. There is only one method to override:
irr::IEventReceiver::OnEvent(). This method will be called by the engine once
when an event happens. What we really want to know is whether a key is being
held down, and so we will remember the current state of each key.
*/

class GamePhysics;
class SpaceObject;

class MyEventReceiver : public IEventReceiver
{
public:
	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}
	
	MyEventReceiver()
	{
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

class GravityInfo {
	public:
		text_string print();

		//text_string printableInfo;
		f64 maxGravity;
		SpaceObject* maxGravityObject;
		f64 secondMaxGravity;
		SpaceObject* secondMaxGravityObject;
};


//SpaceObject - is any object in current visible space
class SpaceObject {

	public:

		//TODO: think on subclassing space objects by motion type
		enum MotionType {
			MOTION_NONE,
			MOTION_ORBITAL,
			MOTION_NAVIGATION,
		};

		enum ControlType {
			CONTROL_THRUST_ABSOLUTE,
			CONTROL_THRUST_RELATIVE,
			CONTROL_ROTATION_SPEED_ABSOLUTE,
			CONTROL_ROTATION_SPEED_RELATIVE,
		};

		SpaceObject();

		//getters
		bool IsEmittingGravity() {return isEmitGravity;}
		f64 GetThrust() {return thrustPower;}
		f64 GetMass() {return mass;}
		vector3d GetPosition() {return position;}
		vector3d GetSpeed();
		vector3d GetDirection();
		text_string GetName() {return name;}
		//f32 GetMaxThrust() {return maxThrust;}
		//f32 GetMaxRotationThrust() {return maxRotationThrust;}

		scene::ISceneNode* GetNode() {return sceneNode;}

		//setters
		void SetPosition(vector3d newPos) {position = newPos;}
		void SetSpeed(vector3d newSpeed) {speed = newSpeed;}
		void SetRotation(f64 newRotation) {rotation = newRotation;}
		void SetNode(scene::ISceneNode * node) {sceneNode = node;}
		void SetMarkerNode(scene::ISceneNode * node, f64 size) {sceneMarkerNode = node; sizeMarker = size;}
		void SetMotionType(MotionType newType) {motionType = newType;}
		void SetOrbitalParams(SpaceObject* parent, f64 radius, f64 Period, f64 EpochPhase);
		void SetPhysics(GamePhysics* physicsOwner) {physics = physicsOwner;}
		void SetMaxThrust(f64 newMaxThrust, f64 newMaxRotationThrust) {maxThrust = newMaxThrust; maxRotationThrust = newMaxRotationThrust; }
		void SetMass(f64 newMass) {mass = newMass;}
		void SetMassRadius(f64 newMassRadius) {gravityMinRadius = newMassRadius;}
		void SetGravity(bool emit, bool affected) {isEmitGravity = emit,isAffectedByGravity = affected;}
		void SetName(text_string newName) {name = newName;}
		
		//void SetThrust(f64 newThrust) {thrustPower = newThrust;}
		//void SetRotationSpeed(f64 newRotSpeed) {rotationSpeed = newRotSpeed;}

		vector3d GetGravityAcceleration(vector3d location);
		void SetControl(f64 newValue, ControlType type);

		void AutopilotBreak();
		void AutopilotOrbiting();
		void AutopilotSetSpeed(vector3d requiredSpeed);

		//updating
		void UpdatePhysics(f64 time);
		void UpdateSceneNode();
		void UpdateMarkerNode(f64 cameraDistance);
	private:
		bool isEmitGravity;//for calulcation of gravity field. Gravity is emitted by massive objects - stars, planets, moons, black holes, asteroids. May be by specific weapons or traps
		bool isAffectedByGravity;//for using gravity field. Affected in game engine are ships.
		bool isVisibleToPlayer;//object is visible for player. Invisible are small objects, cloacked, unexplored and so on
		MotionType motionType;//how object motion is calculated

		text_string name;

		f64 mass;//for calc gravity
		f64 gravityMinRadius;//only for calc gravity
		f64 maxThrust;
		f64 maxRotationThrust;

		GamePhysics* physics;
		SpaceObject* orbitingObject;
		f64 orbitalRadius;//radius, orbits are currently circular
		f64 orbitalPeriod;//period
		f64 orbitalEpochPhase;//phase at time zero

		f64 rotationSpeed;
		f64 thrustPower;
		f64 sizeMarker;

		vector3d position;//current position in space, coordinates (zero at star system center of mass)
		vector3d speed;//current motion speed, relative to "background stars"
		f64 rotation;//rotation angle, degrees (zero is direction to down)

		scene::ISceneNode * sceneNode; //Irrlich renderable object
		//scene::IBillboardSceneNode * sceneMarkerNode; //Irrlich renderable object - for displaying from a far
		scene::ISceneNode * sceneMarkerNode; //Irrlich renderable object - for displaying from a far
		//vector3d acceleration; //
};

SpaceObject::SpaceObject()
{
	//initialize simpliest object
	position = vector3d(0);
	speed = vector3d(0);
	rotation = 0;
	sceneNode = 0;
	sceneMarkerNode = 0;
	sizeMarker = 0.01;
	name = L"";

	isEmitGravity = false;
	isAffectedByGravity = false;
	motionType = MOTION_NONE;
	isVisibleToPlayer = false;
	mass = 0;
	gravityMinRadius = 1.0;
	orbitingObject = 0;
	orbitalRadius = 1.0;
	orbitalPeriod = 1.0;
	orbitalEpochPhase = 0;


}

vector3d SpaceObject::GetDirection()
{
	return vector3d(cos(rotation*CoeffDegreesToRadians),sin(rotation*CoeffDegreesToRadians),0);
}



void SpaceObject::UpdateSceneNode()
{
	sceneNode->setPosition(vector3df((f32)position.X,(f32)position.Y,0));
	sceneNode->setRotation(vector3df(0,0,(f32)rotation));
	if (sceneMarkerNode)
	{
		//TODO: optimize?
		sceneMarkerNode->setPosition(vector3df((f32)position.X,(f32)position.Y,0.01f));
		sceneMarkerNode->setRotation(vector3df(0,0,(f32)rotation));
	}
}

/*
void SpaceObject::Thrust(f32 power,f32 time)
{
	vector3d direction = vector3d(sin(rotation*CoeffDegreesToRadians),-cos(rotation*CoeffDegreesToRadians),0);
	Accelerate(direction*power,time);
	//position += speed*time;
}

void SpaceObject::Rotate(f32 degrees)
{
	rotation += degrees;
}*/


void SpaceObject::SetOrbitalParams(SpaceObject* parent, f64 radius, f64 period, f64 epochPhase)
{
	orbitingObject = parent;
	orbitalRadius = radius;
	orbitalPeriod = period;
	orbitalEpochPhase = epochPhase;
	motionType = MOTION_ORBITAL;
}

void SpaceObject::SetControl(f64 newValue, ControlType type)
{
	switch(type)
	{
		case CONTROL_THRUST_ABSOLUTE:
			thrustPower = newValue;
			//check to max value!
			break;
		case CONTROL_THRUST_RELATIVE:
			thrustPower = newValue*maxThrust;
			//check to max value!
			break;
		case CONTROL_ROTATION_SPEED_ABSOLUTE:
			rotationSpeed = newValue;
			//check to max value!
			break;
		case CONTROL_ROTATION_SPEED_RELATIVE:
			rotationSpeed = newValue*maxRotationThrust;
			//check to max value!
			break;
		default:
			break;
	}
}

/*

//Breaking relative to distant-stars
void SpaceObject::AutopilotBreak()
{
	vector3d direction = GetDirection();
	//vector3d speed = GetSpeed();
	vector3d speedNormalized = speed;
	speedNormalized.normalize();
	f64 whereToRotate;
	//f32 speedValeu
	if (speed.getLength()<0.01)
	{
		speed = vector3d(0,0,0);//Force nullify speed
		return;
	}
	//whereToRotate = direction.crossProduct(speedNormalized).Z;
	whereToRotate = direction.X*speedNormalized.Y - direction.Y*speedNormalized.X;
	//whereToRotate = direction.Y*speedNormalized.X-direction.X*speedNormalized.Y;

	if (abs(whereToRotate)<0.005 && direction.dotProduct(speed)<0)
	{
		//TODO: change CoeffDegreesToRadians to another
		rotation = 180+atan2(speed.Y,speed.X)/CoeffDegreesToRadians;//Force set rotation to required angle

		f64 k=1;
		if (speed.getLength()<maxThrust*0.05)//this assumes minimum frame interval is 20 ms, 
		{
			//TODO: get minimum frame interval from physics or game?
			k = 200.0*speed.getLength()/maxThrust;//adjust breaking thrust power to partial of speed
		}
		SetControl(k,CONTROL_THRUST_RELATIVE);
		return;
	}

	if (whereToRotate>0)
	{
		SetControl(-1,CONTROL_ROTATION_SPEED_RELATIVE);
	}
	else if (whereToRotate<0)
	{
		SetControl(1,CONTROL_ROTATION_SPEED_RELATIVE);
	}
}*/

void SpaceObject::AutopilotBreak()
{
	AutopilotSetSpeed(vector3d(0));
}

//Breaking relative to distant-stars
void SpaceObject::AutopilotSetSpeed(vector3d requiredSpeed)
{
	vector3d direction = GetDirection();
	vector3d changeSpeed = requiredSpeed-speed;
	//vector3d speed = GetSpeed();
	vector3d speedNormalized = changeSpeed;
	speedNormalized.normalize();
	f64 whereToRotate;
	//f32 speedValeu
	if (changeSpeed.getLength()<0.01)
	{
		speed = requiredSpeed;
		return;
	}
	whereToRotate = direction.Y*speedNormalized.X - direction.X*speedNormalized.Y;

	if (abs(whereToRotate)<0.005 && direction.dotProduct(changeSpeed)>0)
	{
		//TODO: change CoeffDegreesToRadians to another
		rotation = atan2(changeSpeed.Y,changeSpeed.X)/CoeffDegreesToRadians;//Force set rotation to required angle

		f64 k=1;
		if (changeSpeed.getLength()<k*maxThrust*0.05)//this assumes minimum frame interval is 20 ms, 
		{
			//TODO: get minimum frame interval from physics or game?
			k = 200.0*changeSpeed.getLength()/maxThrust;//adjust breaking thrust power to partial of speed
		}
		SetControl(k,CONTROL_THRUST_RELATIVE);
		return;
	}

	if (whereToRotate>0)
	{
		SetControl(-1,CONTROL_ROTATION_SPEED_RELATIVE);
	}
	else if (whereToRotate<0)
	{
		SetControl(1,CONTROL_ROTATION_SPEED_RELATIVE);
	}
}


void SpaceObject::UpdateMarkerNode(f64 cameraDistance)
{
	if (sceneMarkerNode)
	{
		f64 scale = .2*sizeMarker*cameraDistance;///log(cameraDistance);
		//f32 scale = cameraDistance/(1.f*log(cameraDistance));
		//sceneMarkerNode->setSize(core::dimension2d<f32>(scale,scale));
		sceneMarkerNode->setScale(vector3df((f32)scale));
		//sceneMarkerNode->setB
		//sceneNode->setScale(vector3d(scale,scale,scale));
	}
}


class GamePhysics {
	public:
		f64 globalTime;
		void Update(f64 time);
		void AddObject(SpaceObject* newObject);
		void UpdateMarkers(f64 cameraDistance);
		vector3d GetGravityAcceleration(vector3d location);
		GravityInfo* GetGravityInfo(vector3d location);
	private:
		core::array<SpaceObject*> SpaceObjectList;
};

void GamePhysics::Update(f64 time)
{
	u32 i;
	globalTime += time;
	for (i=0;i<SpaceObjectList.size();i++)
	{
		SpaceObjectList[i]->UpdatePhysics(time);
		SpaceObjectList[i]->UpdateSceneNode();
	}
}

void GamePhysics::UpdateMarkers(f64 cameraDistance)
{
	u32 i;
	for (i=0;i<SpaceObjectList.size();i++)
	{
		SpaceObjectList[i]->UpdateMarkerNode(cameraDistance);
	}
}

void GamePhysics::AddObject(SpaceObject* newObject)
{
	SpaceObjectList.push_back(newObject);
	newObject->SetPhysics(this);
}

void SpaceObject::UpdatePhysics(f64 time)
{
	vector3d acceleration = vector3d(0,0,0);
	switch (motionType)
	{
	case MOTION_NONE:
		//do nothing;
		break;
	case MOTION_NAVIGATION:
		if (thrustPower!=0)
		{
			//vector3d direction = vector3d(sin(rotation*CoeffDegreesToRadians),-cos(rotation*CoeffDegreesToRadians),0);
			acceleration+=thrustPower*GetDirection();
		}

		//Simple Euler solving of differential equations
		if (isAffectedByGravity)
		{
			acceleration += physics->GetGravityAcceleration(position);
		}
		rotation += rotationSpeed*time;
		speed += acceleration*time;
		if (speed.getLength()>240000.0)
		{
			//above 0.8c - activate "relativistic" effects
			//currently effect is very rough, but give good result - no more than 0.9997 speed
			f64 relativisticDrag;
			f64 prevSpeed = (speed - acceleration*time).getLength();
			relativisticDrag = (speed.getLength()-240000.0)/60000.0;//0 at 0.8c, 1 at 1c;
			relativisticDrag *= (speed.getLength() - prevSpeed)/prevSpeed;
			if (time>0)
			{
				acceleration-=speed*relativisticDrag/time;
			}
			speed-=speed*relativisticDrag;
		}
		//else
		{
			position += speed*time + acceleration*time*time*.5;
		}
		break;
	case MOTION_ORBITAL:
		{
			//simple circular orbiting
			f64 Phase = orbitalEpochPhase;
			if (orbitalPeriod!=0)
			{
				Phase+=360.0*physics->globalTime/orbitalPeriod;
			}
			position.X = cos(Phase*CoeffDegreesToRadians)*orbitalRadius;
			position.Y = sin(Phase*CoeffDegreesToRadians)*orbitalRadius;
			position.Z = 0;
			if (orbitingObject!=0)
				position+=orbitingObject->position;
		}
		break;
	default:
		break;
	}
}

vector3d SpaceObject::GetSpeed()
{
	switch (motionType)
	{
	case MOTION_ORBITAL:
		{
			//simple circular orbiting
			if (orbitalPeriod!=0)
			{
				f64 Phase = orbitalEpochPhase;
				f64 speedValue = orbitalRadius*6.2831853/orbitalPeriod;
				Phase+=360.0*physics->globalTime/orbitalPeriod;
				speed.X = -sin(Phase*CoeffDegreesToRadians)*speedValue;
				speed.Y = cos(Phase*CoeffDegreesToRadians)*speedValue;
				speed.Z = 0;
				if (orbitingObject!=0)
					speed+=orbitingObject->GetSpeed();
			}
			else
			{
				speed = vector3d(0);
			}
		}

		break;
	default:
		break;
	}
	return speed;
}


vector3d SpaceObject::GetGravityAcceleration(vector3d location)
{
	vector3d vectorDirection = position-location;
	f64 distance = vectorDirection.getLength();
	if (distance<gravityMinRadius)
	{
		//return vector3d(0);//simply nothing
		return 66.7*vectorDirection*mass/(gravityMinRadius*gravityMinRadius*gravityMinRadius);
	}
	//G = 6.67384(80)*10^-11 N * (m/kg)^2 = .. [m*m*m/kg*s^2]
	//distances is in 1000 km, so k=10^6  
	//time is in 1000 seconds - k=1000
	//mass is in 10^24 kg - k=10^24
	//Ggame = G * 10^-18/(10^-24 * 10^-6) = G * 10^12 = 
	return 66.7*vectorDirection*mass/(distance*distance*distance);
}


vector3d GamePhysics::GetGravityAcceleration(vector3d location)
{
	u32 i;
	vector3d acceleration = vector3d(0,0,0);
	for (i=0;i<SpaceObjectList.size();i++)
		if (SpaceObjectList[i]->IsEmittingGravity())
		{
			//vector3d vectorDirection = SpaceObjectList[i]->GetPosition()-location;
			//f64 distance = vectorDirection.getLength();
			//acceleration += 66.7*vectorDirection*SpaceObjectList[i]->GetMass()/(distance*distance*distance);
			acceleration += SpaceObjectList[i]->GetGravityAcceleration(location);
		}
	return acceleration;
}

GravityInfo* GamePhysics::GetGravityInfo(vector3d location)
{
	u32 i;
	//text_string gravityInfo(L"");
	GravityInfo* gravInfo = new GravityInfo();
	f64 gravity;
	
	f64 maxGravity=-1;
	SpaceObject* maxGravityObject =0;
	f64 secondMaxGravity=-1;
	SpaceObject* secondMaxGravityObject =0;


	for (i=0;i<SpaceObjectList.size();i++)
		if (SpaceObjectList[i]->IsEmittingGravity())
		{
			//vector3d vectorDirection = SpaceObjectList[i]->GetPosition()-location;
			//f64 distance = vectorDirection.getLength();
			//gravity = (vectorDirection*SpaceObjectList[i]->GetMass()/(distance*distance*distance)).getLength();
			gravity = SpaceObjectList[i]->GetGravityAcceleration(location).getLength();
			if (gravity>maxGravity)
			{
				secondMaxGravity = maxGravity;
				secondMaxGravityObject = maxGravityObject;
				maxGravity=gravity;
				maxGravityObject = SpaceObjectList[i];
			}
			else if (gravity>secondMaxGravity)
			{
				secondMaxGravity = gravity;
				secondMaxGravityObject = SpaceObjectList[i];
			}
		}

	//gravInfo->printableInfo = gravityInfo;
	gravInfo->maxGravity = maxGravity;
	gravInfo->maxGravityObject = maxGravityObject;
	gravInfo->secondMaxGravity = secondMaxGravity;
	gravInfo->secondMaxGravityObject = secondMaxGravityObject;
	return gravInfo;
}

text_string GravityInfo::print()
{
	text_string gravityInfo(L"");
	if (maxGravityObject)
	{
		gravityInfo = L"Max gravity from: ";
		gravityInfo += maxGravityObject->GetName();
		if (secondMaxGravityObject)
		{
			f64 percent = 100.0*maxGravity/(maxGravity+secondMaxGravity);
			gravityInfo += L" (";
			gravityInfo += print_f64(percent,L"%.02f");
			gravityInfo += L"%)\r\nNext gravity from: ";
			gravityInfo += secondMaxGravityObject->GetName();
			gravityInfo += L" (";
			//gravityInfo += (100.0-percent);
			gravityInfo += print_f64(100.0-percent,L"%.02f");
			gravityInfo += L"% / ";
			gravityInfo += print_f64(log(secondMaxGravity)-log(maxGravity),L"%.02f");
			gravityInfo += L" dgr)";
		}
	}
	else
	{
		gravityInfo = L"no gravity detected";
	}
	return gravityInfo;
}

class StarSystemConstructor
{
	public:
		void SetupConstructor(GamePhysics* newPhysics, scene::ISceneManager* smgr, video::IVideoDriver* driver);
		void MakeSimpleSystem();
		SpaceObject* MakeStar(f64 radius = 10.0, s32 polygons = 32);
		SpaceObject* MakePlanet(f64 radius = 3.0, s32 polygons = 32);
		SpaceObject* MakeShip();
		void AddMarker(SpaceObject* toObject, u32 type);

	private:
		GamePhysics* physics;
		scene::ISceneManager* sceneManager;
		video::IVideoDriver* videoDriver;
};

void StarSystemConstructor::SetupConstructor(GamePhysics* newPhysics, scene::ISceneManager* smgr, video::IVideoDriver* driver)
{
	physics = newPhysics;
	sceneManager = smgr;
	videoDriver = driver;
}

void StarSystemConstructor::MakeSimpleSystem()
{
	f64 planetSizes[11]={190.0,0.382,0.949,1.00,0.532,11.209,9.449,4.007,3.883,0.19};
	f64 planetOrbits[11]={0.0,0.39,0.72,1.00,1.52,5.20,9.54,19.22,30.06,45.0};
	f64 planetPeriods[11]={0.0,0.24,0.62,1.00,1.88,11.86, 29.46,84.01,164.8,248.09};
	f64 planetMass[11]={330000.0,0.06,0.82,1.00,0.11,317.8,95.2,14.6,17.2,0.0022};
	text_string planetNames[11]={L"Sun",L"Mercury",L"Venus",L"Earth",L"Mars",L"Jupiter",L"Saturn",L"Uranus",L"Neptune",L"Pluto"};
	//f32 planetMass[11]={0.0f,0.06f,0.82f,1.00f,0.11f,317.8f,95.2f,14.6f,17.2f,0.0022f};

	// set ambient light
    sceneManager->setAmbientLight(video::SColor(0,60,60,60));
	//sceneManager->setAmbientLight(video::SColor(0,0,0,0));

	sceneManager->addSkyBoxSceneNode(0,
		0,
		0,
		0,
		0,
		videoDriver->getTexture(RESOURCE_PATH"/starfield_1_medium.jpg"));/**/
	//smgr->addBillboardSceneNode(0,core::dimension2d<f32>(100,100));

	/*
	MakeStar();

	SpaceObject* sun = MakeStar(2);
	sun->SetOrbitalParams(0,70,100,180);
	//sun = MakeStar(2);
	//sun->SetOrbitalParams(0,70,100,90);
	//sun = MakeStar(2);
	//sun->SetOrbitalParams(0,70,100,270);

	SpaceObject* planetOne = MakePlanet(10);
	planetOne->SetOrbitalParams(0,200,300,10);

	SpaceObject* planetTwo = MakePlanet(2,20);
	planetTwo->SetOrbitalParams(0,20,50,40);

	planetTwo = MakePlanet(2,20);
	planetTwo->SetOrbitalParams(planetOne,20,20,15);

	planetTwo = MakePlanet(3);
	planetTwo->SetOrbitalParams(0,35,40,75);

	planetTwo = MakePlanet(3);
	planetTwo->SetOrbitalParams(0,55,80,220);*/


	//Solar system
	//Everything not to scale
	SpaceObject* planet;

	//planet = MakeStar(planetSizes[0]*.01f);//sun is 10 times larger, compared to orbits
	//planet->SetMass(planetMass[0]);
	//planet->SetGravity(true,false);

	for (int i=0;i<10;i++)
	{
		//planetSizes - in 6370 km
		//planetOrbits - in 150M km
		//planetPeriods - in years
		//planetMass - in 5.9736*10^24
		if (i==0)
			planet = MakeStar(planetSizes[i]*6.37);
		else
		{
			planet = MakePlanet(planetSizes[i]*6.37);//1000km in 1 unit
			planet->SetOrbitalParams(0,planetOrbits[i]*150000.0,planetPeriods[i]*365.25*86.4,i*20.0);//1000 seconds in 1
		}
		//if (i==0)
		{
			planet->SetName(planetNames[i]);
			planet->SetMass(planetMass[i]*5.9736);//in 10^24 kg
			planet->SetGravity(true,false);
		}
		//planet->SetOrbitalParams(0,planetOrbits[i]*23.50f,0,0);

		if (i==3)
		{
			SpaceObject* moon;
			moon = MakePlanet(1.74);
			moon->SetOrbitalParams(planet,384.0,2358.72,120.0);
			moon->SetMass(.0123*5.9736);
			moon->SetGravity(true,false);
			moon->SetName("Moon");
		}
	}

	SpaceObject* someShip = MakeShip();
	someShip->SetPosition(vector3d(10,0,0));
	someShip->SetRotation(90);
	//someShip->thrustPower = 1.f;
	//someShip->SetThrust(1.f);
	someShip->SetControl(1.0,SpaceObject::CONTROL_THRUST_ABSOLUTE);
	someShip->SetControl(20.0,SpaceObject::CONTROL_ROTATION_SPEED_ABSOLUTE);

	someShip->SetName(L"test ship");
	//someShip->SetGravity(false,true);
	//someShip->SetRotationSpeed(20.f);
	//someShip->rotationSpeed = 20.f;
}

SpaceObject* StarSystemConstructor::MakeStar(f64 radius, s32 polygons)
{
	SpaceObject* newStar = new SpaceObject();
	scene::ISceneNode * sceneNode;

	sceneNode = sceneManager->addSphereSceneNode((f32)radius,polygons);
	if (sceneNode)
	{
		sceneNode->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/yellow.bmp"));
		sceneNode->setMaterialFlag(video::EMF_LIGHTING, false);
		//sceneNode->getMaterial(0).AmbientColor.set(255,0,0,0);
		//sceneNode->getMaterial(0).DiffuseColor.set(255,0,0,0);
		//sceneNode->getMaterial(0).SpecularColor.set(255,0,0,0);
		//sceneNode->getMaterial(0).EmissiveColor.set(255,255,255,0);
	}
	newStar->SetNode(sceneNode);
	newStar->SetMotionType(SpaceObject::MOTION_NONE);
	newStar->SetMassRadius(radius);
	//planetOne->SetOrbitalParams(0,200,300,0);
	physics->AddObject(newStar);

	scene::ILightSceneNode * light = sceneManager->addLightSceneNode(sceneNode, core::vector3df(0,0,-(f32)radius),
		//video::SColorf(100.0f,100.0f,100.0f,1.0f), 1.0f);
		video::SColorf(1.0f,1.0f,1.0f,1.0f), 100.0f);

	//ELT_DIRECTIONAL 

	//light->getLightData().Attenuation.set(.7f,0,0.000003f);
	//light->getLightData().Attenuation.set(.7f,0.001f,0);

	light->getLightData().Attenuation.set(.7f,0,0);//zero fading - temp, for adjusting scale

	//light->getLightData().Attenuation.set(0,0,1/(radius*radius));
	//light->getLightData().Attenuation.set(.7f,0,0);

	/*
	light = sceneManager->addLightSceneNode(sceneNode, core::vector3df(0,0,1),
	//video::SColorf(100.0f,100.0f,100.0f,1.0f), 1.0f);
	video::SColorf(1.0f,1.0f,1.0f,1.0f), 1.0f);
	light->getLightData().Attenuation.set(1.5f,0,0);
	/**/

	/*
	light = sceneManager->addLightSceneNode(0, core::vector3df(10,0,0),
		//video::SColorf(100.0f,100.0f,100.0f,1.0f), 1.0f);
		video::SColorf(1.0f,1.0f,1.0f,1.0f), 1.0f);
	light->getLightData().Attenuation.set(1.5f,0,0);

	light = sceneManager->addLightSceneNode(0, core::vector3df(-10,0,0),
		//video::SColorf(100.0f,100.0f,100.0f,1.0f), 1.0f);
		video::SColorf(1.0f,1.0f,1.0f,1.0f), 1.0f);
	light->getLightData().Attenuation.set(1.5f,0,0);

	light = sceneManager->addLightSceneNode(0, core::vector3df(0,10,0),
		//video::SColorf(100.0f,100.0f,100.0f,1.0f), 1.0f);
		video::SColorf(1.0f,1.0f,1.0f,1.0f), 1.0f);
	light->getLightData().Attenuation.set(1.5f,0,0);

	light = sceneManager->addLightSceneNode(0, core::vector3df(0,-10,0),
		//video::SColorf(100.0f,100.0f,100.0f,1.0f), 1.0f);
		video::SColorf(1.0f,1.0f,1.0f,1.0f), 1.0f);
	light->getLightData().Attenuation.set(1.5f,0,0);
	//scene::ILightSceneNode * light = sceneManager->addA*/

	AddMarker(newStar,0);

	return newStar;
}

SpaceObject* StarSystemConstructor::MakePlanet(f64 radius, s32 polygons)
{
	SpaceObject* newPlanet = new SpaceObject();
	scene::ISceneNode * sceneNode;

	sceneNode = sceneManager->addSphereSceneNode((f32)radius,polygons);
	if (sceneNode)
	{
		//sceneNode->setScale(vector3d(radius,radius,radius));
		//sceneNode->setPosition(core::vector3df(-30,50,0));
		sceneNode->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/wall.bmp"));
		//node2->setM
		//node2->setMaterialType(irr:video::E_MATERIAL_TYPE 
		//node2->getMaterial(0).DiffuseColor.set(0,255,0,0);
		//node2->getMaterial(0).AmbientColor.set(255,255,255,0);
		//node2->getMaterial(0).SpecularColor.set(0,255,0,0);
		//node2->getMaterial(0).DiffuseColor.set(255,255,0,0);
		//node2->setMaterialFlag(video::EMF_COLOR_MATERIAL,true);
		//node2->setMaterialFlag(video::EMF_GOURAUD_SHADING,false);
		//node2->setMaterialFlag(video::EMF_,true);
		//node2->setMaterialType(video::EMT_PARALLAX_MAP_SOLID);


		//STOPS HERE

		//node2->setMaterialFlag(video::EMF_LIGHTING, false);
		//node2->setMaterialType(new video::E_COLOR_MATERIAL();
		//node2->setMaterialFlag(video::EMF_WIREFRAME, true);
		//node2->setMaterialFlag(video::EMF_NORMALIZE_NORMALS,true);
	}
	newPlanet->SetNode(sceneNode);
	newPlanet->SetMassRadius(radius);
	//planetOne->SetMotionType(SpaceObject::MOTION_NONE);
	//newPlanet->SetOrbitalParams(0,200,300,0);


	physics->AddObject(newPlanet);

	AddMarker(newPlanet,0);

	return newPlanet;

}

SpaceObject* StarSystemConstructor::MakeShip()
{
	scene::ISceneNode* node = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/ship1.irrmesh"));
	if (node)
	{
		//node->setPosition(core::vector3df(0,0,30));
		node->setScale(core::vector3df(3,3,3));
		//node->setMaterialTexture(0, driver->getTexture(RESOURCE_PATH"/crate0.jpg"));
		node->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/ships.png"));
		//node->setMaterialTexture(1, driver->getTexture(RESOURCE_PATH"/ships.png"));
		node->setMaterialFlag(video::EMF_LIGHTING, false);
		//node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
		node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
		//node->setMaterialType(video::EMT_ONETEXTURE_BLEND);
		//node->getMaterial(0).MaterialTypeParam = pack_texureBlendFunc(video::EBF_ONE, video::EBF_ZERO);
	}
	//node = smgr->addSphereSceneNode(3);
	//node->setMaterialTexture(0, driver->getTexture(RESOURCE_PATH"/wall.bmp"));
	//node->setMaterialFlag(video::EMF_WIREFRAME, true);

	SpaceObject* ship = new SpaceObject();
	ship->SetNode(node);
	ship->SetMotionType(SpaceObject::MOTION_NAVIGATION);
	ship->SetGravity(false,true);
	physics->AddObject(ship);

	AddMarker(ship,1);

	return ship;
}

void StarSystemConstructor::AddMarker(SpaceObject* toObject, u32 type)
{
	//scene::IBillboardSceneNode * sceneNode2 = sceneManager->addBillboardSceneNode(toObject->GetNode());
	//scene::ISceneNode * sceneNode2 = sceneManager->addBillboardSceneNode(toObject->GetNode());
	scene::ISceneNode* sceneNode2 = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/plane.irrmesh"));
	f64 sizeMarker;

	if (sceneNode2)
	{
		//sceneNode2->setParent(toObject->GetNode());
		//sceneNode2->setScale(vector3d(5,5,5));
		//sceneNode2->se
		
		sceneNode2->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
		//could be usefull for further smooth disapperance of markers
		//sceneNode2->setMaterialType(video::EMT_ONETEXTURE_BLEND );
		//sceneNode2->getMaterial(0).MaterialTypeParam = irr::video::pack_texureBlendFunc(irr::video::EBF_ONE, irr::video::EBF_ONE);

		sceneNode2->setMaterialFlag(video::EMF_LIGHTING, false);
		//sceneNode2->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
		if (type==1)
		{
			sceneNode2->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/arrow.bmp"));
			sizeMarker  = .1;
		}
		else
		{
			sceneNode2->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/star2.bmp"));
			sizeMarker  = .07;
		}
	}
	toObject->SetMarkerNode(sceneNode2,sizeMarker);
}

//Breaking relative to distant-stars
void SpaceObject::AutopilotOrbiting()
{
	
	f64 requiredRelativeSpeed;
	vector3d maxGravityAcceleration;
	vector3d relativePosition;
	vector3d relativeSpeed;
	vector3d requiredSpeed;
	GravityInfo* gravInfo = physics->GetGravityInfo(position);
	if (!gravInfo->maxGravityObject) //no dominant object - no orbiting
		return;
	//speed = gravInfo->maxGravityObject->GetSpeed();
	relativePosition = position - gravInfo->maxGravityObject->GetPosition();
	relativeSpeed = speed - gravInfo->maxGravityObject->GetSpeed();
	maxGravityAcceleration = gravInfo->maxGravityObject->GetGravityAcceleration(position);
	requiredRelativeSpeed = sqrt((maxGravityAcceleration.getLength())*(relativePosition.getLength())); //via centro-escape acceleration

	//TODO: add check for opposite direction, it could be closer to current speed

	requiredSpeed.X = relativePosition.Y;//perpendicular to relative position
	requiredSpeed.Y = -relativePosition.X;
	requiredSpeed.Z = 0;
	requiredSpeed.normalize();//1 unit length
	requiredSpeed*= requiredRelativeSpeed;//length 
	requiredSpeed+=gravInfo->maxGravityObject->GetSpeed();//absolute value

	//debug: simple set speed to required value
	//speed = requiredSpeed;
	AutopilotSetSpeed(requiredSpeed);
}


class DG_Game {

	public:

		int Init(int Count, char **Arguments);
		void Update();
		void Close();
		f64 GetCameraDistance() {return cameraDistance;}
		s32 cameraDistanceDegree;

		void UpdateCameraDistance();

		
		//void ChangeState(StateClass *State);
		//StateClass *GetState() { return State; }

		bool IsDone() { return Done; }
		void SetDone(bool Value) { Done = Value; }
		//float GetTimeStep() { return TimeStep; }
		//void ResetTimer();

	private:
		f64 cameraDistance;
		//f64 MOVEMENT_SPEED;
		// Flags
		IrrlichtDevice* device;
		u32 then;
		GamePhysics * gamePhysics;
		bool Done, MouseWasLocked;
		scene::ISceneNode * node;
		scene::ICameraSceneNode * camera;
		MyEventReceiver receiver;
		scene::ISceneManager* smgr;
		video::IVideoDriver* driver;
		int lastFPS;

		SpaceObject * playerShip;
		f64 playerThrust;
		scene::IParticleSystemSceneNode * playerThrustParticles;
		scene::IParticleEmitter*  playerThrustEmitter;
		//scene::IParticleSystemSceneNode * playerThrust;
		//scene::IParticleEmitter*  motionIndicatorEmitter;
		scene::IParticleSystemSceneNode* motionIndicator;
		gui::IGUIStaticText* simpleTextToDisplay;
};


/*
void SpaceObject::Accelerate(vector3d acceleration, f32 time)
{
	speed += acceleration*time;
}

void SpaceObject::LinearMotion(f32 time)
{
	position += speed*time;
}*/





// Processes parameters and initializes the game
int DG_Game::Init(int Count, char **Arguments) {
	// ask user for driver
	
	gamePhysics = new GamePhysics;
	gamePhysics->globalTime = 0;


	/*
	video::E_DRIVER_TYPE driverType=driverChoiceConsole();
	if (driverType==video::EDT_COUNT)
		return 1;
	*/
	//driverType = video::EDT_OPENGL;

	// create device

	//IrrlichtDevice* device = createDevice(driverType,
	device = createDevice(video::EDT_OPENGL,
			core::dimension2d<u32>(1024, 768), 16, false, false, false, &receiver);

	if (device == 0)
		return 1; // could not create selected driver.

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();

	/*
	Create the node which will be moved with the WSAD keys. We create a
	sphere node, which is a built-in geometry primitive. We place the node
	at (0,0,30) and assign a texture to it to let it look a little bit more
	interesting. Because we have no dynamic lights in this scene we disable
	lighting for each model (otherwise the models would be black).
	*/
	/*
	node = smgr->addSphereSceneNode();
	if (node)
	{
		node->setPosition(core::vector3df(0,0,30));
		node->setMaterialTexture(0, driver->getTexture(RESOURCE_PATH"/wall.bmp"));
		node->setMaterialFlag(video::EMF_LIGHTING, false);
	}*/


	//node = smgr->addAnimatedMeshSceneNode(smgr->getMesh(RESOURCE_PATH"/cube.irrmesh"));
	//node = smgr->addAnimatedMeshSceneNode(smgr->getMesh(RESOURCE_PATH"/ship1.irrmesh"));
	
	StarSystemConstructor* ssc = new StarSystemConstructor();
	ssc->SetupConstructor(gamePhysics,smgr,driver);
	ssc->MakeSimpleSystem();
	

	playerShip = ssc->MakeShip();
	playerShip->SetPosition(vector3d(0,1300,0));
	playerShip->SetRotation(90);
	playerShip->SetSpeed(vector3d(-320.28,0,0));
	playerShip->SetMaxThrust(100000,150);
	playerThrust = 1.0;
	playerShip->SetName(L"Player");


	
	// create a particle system

	motionIndicator =
		smgr->addParticleSystemSceneNode(false);

	scene::IParticleEmitter* motionIndicatorEmitter = motionIndicator->createBoxEmitter(
		core::aabbox3d<f32>(-100,-100,-20,100,100,20), // emitter size
		core::vector3df(0.0f,0.0f,0.0f),   // initial direction
		200,500,                             // emit rate
		video::SColor(0,255,255,255),       // darkest color
		video::SColor(0,255,255,255),       // brightest color
		0,2000,0,                         // min and max age, angle
		core::dimension2df(1.f,1.f),         // min size
		core::dimension2df(1.f,1.f));        // max size

	motionIndicator->setEmitter(motionIndicatorEmitter); // this grabs the emitter
	//em->drop(); // so we can drop it here without deleting it

	scene::IParticleAffector* paf = motionIndicator->createFadeOutParticleAffector(video::SColor(0,0,0,0),100);

	motionIndicator->addAffector(paf); // same goes for the affector
	paf->drop();

	motionIndicator->setPosition(core::vector3df(0,0,0));
	motionIndicator->setScale(core::vector3df(1,1,1));
	motionIndicator->setMaterialFlag(video::EMF_LIGHTING, false);
	motionIndicator->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	motionIndicator->setMaterialTexture(0, driver->getTexture(RESOURCE_PATH"/fire.bmp"));
	motionIndicator->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
	/**/


	// create a particle system 2
	playerThrustParticles =
		smgr->addParticleSystemSceneNode(false,playerShip->GetNode());

	playerThrustEmitter = playerThrustParticles->createBoxEmitter(
		core::aabbox3d<f32>(-1,-1,-1,1,1,1), // emitter size
		core::vector3df(0.0f,0.0f,0.0f),   // initial direction
		50,50,                             // emit rate
		video::SColor(0,255,255,255),       // darkest color
		video::SColor(0,255,255,255),       // brightest color
		800,2000,5,                         // min and max age, angle
		core::dimension2df(1.f,1.f),         // min size
		core::dimension2df(1.f,1.f));        // max size

	playerThrustParticles->setEmitter(playerThrustEmitter); // this grabs the emitter
	//em2->drop(); // so we can drop it here without deleting it

	scene::IParticleAffector* paf2 = playerThrustParticles->createFadeOutParticleAffector();

	playerThrustParticles->addAffector(paf2); // same goes for the affector
	paf2->drop();

	playerThrustParticles->setPosition(core::vector3df(-.5f,0,0));
	playerThrustParticles->setScale(core::vector3df(.01f,.01f,.01f));
	playerThrustParticles->setMaterialFlag(video::EMF_LIGHTING, false);
	playerThrustParticles->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	playerThrustParticles->setMaterialTexture(0, driver->getTexture(RESOURCE_PATH"/fire.bmp"));
	playerThrustParticles->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
	//playerThrust->setVisible(false);
	//ps2->setRotation(vector3d(0,0,90));
	/**/




	/*
	scene::ISceneNode * node3 = smgr->addMeshSceneNode(smgr->getMesh(RESOURCE_PATH"/ship1.irrmesh"));
	if (node3)
	{
		node3->setScale(core::vector3df(3,3,3));
		node3->setMaterialTexture(0, driver->getTexture(RESOURCE_PATH"/ships.png"));
		node3->setMaterialFlag(video::EMF_LIGHTING, false);
		node3->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	}*/




	camera = smgr->addCameraSceneNode();
	camera->setFOV(.7f);
	//device->getCursorControl()->setVisible(false);

	/*
	Add a colorful irrlicht logo
	*/

	/*
	device->getGUIEnvironment()->addImage(
		driver->getTexture(RESOURCE_PATH"/ships.png"),//irrlichtlogoalpha2.tga"),
		core::position2d<s32>(10,20));*/

	simpleTextToDisplay = device->getGUIEnvironment()->addStaticText(
		L"Diagnostic very-very-very-very-very-very-very-very-long\r\nSecond line", core::rect<s32>(5, 5, 400, 200));
	simpleTextToDisplay->setOverrideColor(video::SColor(255, 255, 255, 0));
	/**/

	/*
	We have done everything, so lets draw it. We also write the current
	frames per second and the name of the driver to the caption of the
	window.
	*/
	lastFPS = -1;

	// In order to do framerate independent movement, we have to know
	// how long it was since the last frame
	then = device->getTimer()->getTime();

	// This is the movemen speed in units per second.
	//MOVEMENT_SPEED = 5.0;

	smgr->saveScene("1.irrexp");
	cameraDistanceDegree = 1000;
	UpdateCameraDistance();


	Done = false;

	return 1;
}

// Updates the current state and runs the game engine
void DG_Game::Update() {

	// Run irrlicht engine
	if(!device->run())
	{
		Done = true;
		return;
	}

	// Work out a frame delta time.
	const u32 now = device->getTimer()->getTime();
	f64 frameDeltaTime = (f32)(now - then) / 1000.0; // Time in seconds
	then = now;

	if (frameDeltaTime>0.02) frameDeltaTime = 0.02;

	/* Check if keys W, S, A or D are being held down, and move the
	sphere node around respectively. */
	vector3d playerPosition;// = node->getPosition();
	vector3df nodePosition;// = node->getPosition();
	//vector3d thrust;
	//f32 thrust=0;
	//f32 rotate=0;

	if(receiver.IsKeyDown(irr::KEY_KEY_W))
		//playerShip->speed.Y += MOVEMENT_SPEED * frameDeltaTime;
		playerShip->SetControl(playerThrust,SpaceObject::CONTROL_THRUST_RELATIVE);
	else if(receiver.IsKeyDown(irr::KEY_KEY_S))
		//playerShip->speed.Y -= MOVEMENT_SPEED * frameDeltaTime;
		playerShip->SetControl(-playerThrust,SpaceObject::CONTROL_THRUST_RELATIVE);
	else
		playerShip->SetControl(0.0,SpaceObject::CONTROL_THRUST_ABSOLUTE);

	if(receiver.IsKeyDown(irr::KEY_KEY_A))
		//rotate = MOVEMENT_SPEED*30.f;
		playerShip->SetControl(1.0,SpaceObject::CONTROL_ROTATION_SPEED_RELATIVE);
		//playerShip->speed.X -= MOVEMENT_SPEED * frameDeltaTime;
	else if(receiver.IsKeyDown(irr::KEY_KEY_D))
		playerShip->SetControl(-1.0,SpaceObject::CONTROL_ROTATION_SPEED_RELATIVE);
		//rotate = -MOVEMENT_SPEED*30.f;
		//playerShip->speed.X += MOVEMENT_SPEED * frameDeltaTime;
	else
		playerShip->SetControl(0,SpaceObject::CONTROL_ROTATION_SPEED_ABSOLUTE);

	if(receiver.IsKeyDown(irr::KEY_KEY_1))
		playerThrust = 1.0;
	if(receiver.IsKeyDown(irr::KEY_KEY_2))
		playerThrust = 0.1;
	if(receiver.IsKeyDown(irr::KEY_KEY_3))
		playerThrust = 0.01;
	if(receiver.IsKeyDown(irr::KEY_KEY_4))
		playerThrust = 0.001;

	if (receiver.IsKeyDown(irr::KEY_SPACE))
		playerShip->AutopilotBreak();
	if (receiver.IsKeyDown(irr::KEY_KEY_O))
		playerShip->AutopilotOrbiting();
		

	//playerShip->thrustPower = thrust*MOVEMENT_SPEED*5.f;
	//playerShip->rotationSpeed = rotate;
	//playerShip->SetThrust(thrust*MOVEMENT_SPEED*5.f);
	//playerShip->SetRotationSpeed(rotate);
	//someShip->SetControl(1.f,SpaceObject::CONTROL_THRUST_ABSOLUTE);
	//someShip->SetControl(20.f,SpaceObject::CONTROL_ROTATION_SPEED_ABSOLUTE);

	
	f64 thrust = playerShip->GetThrust();
	if (thrust!=0)
	{
		vector3d emitterDirection=.001*playerShip->GetSpeed()-thrust*.000001*playerShip->GetDirection();
		//playerThrust->setVisible(true);
		//playerThrust->
		playerThrustParticles->setEmitter(playerThrustEmitter);
		//playerThrustEmitter->setDirection(-.02f*vector3d(sin(playerShip->rotation*CoeffDegreesToRadians),-cos(playerShip->rotation*CoeffDegreesToRadians),0));
		//playerThrustEmitter->setDirection(.001f*playerShip->speed);
		playerThrustEmitter->setDirection(vector3df((f32)emitterDirection.X,(f32)emitterDirection.Y,0));
	}
	else
	{
		//playerThrust->setVisible(false);
		playerThrustParticles->setEmitter(0);
	}/**/

	if(receiver.IsKeyDown(irr::KEY_UP))
		if (cameraDistanceDegree<4000)
		{
			cameraDistanceDegree++;
			//cameraDistance *= 1.f*(1.f+frameDeltaTime);
			UpdateCameraDistance();
		}

	if(receiver.IsKeyDown(irr::KEY_DOWN))
		if (cameraDistanceDegree>0)
		{
			//cameraDistance *= 1.f*(1.f-frameDeltaTime);
			cameraDistanceDegree--;
			UpdateCameraDistance();
		}

	text_string debug_text(L"Speed: ");
	f64 playerSpeed;
	playerSpeed = playerShip->GetSpeed().getLength();
	debug_text += playerSpeed;
	debug_text += " km/s\r\n";
	debug_text += (playerSpeed/300000.0);
	debug_text += " c; ";
	debug_text += "\r\n";
	debug_text += gamePhysics->GetGravityInfo(playerShip->GetPosition())->print();
	simpleTextToDisplay->setText(debug_text.c_str());

	//playerShip->position += playerShip->speed;
	//playerShip->Accelerate(thrust,frameDeltaTime);
	//playerShip->Thrust(thrust,frameDeltaTime);
	//playerShip->Rotate(rotate*frameDeltaTime);
	//playerShip->LinearMotion(frameDeltaTime);
	
	//playerShip->UpdatePhysics(frameDeltaTime);
	//playerShip->UpdateSceneNode();
	gamePhysics->Update(frameDeltaTime);

	//node->setPosition(playerShip->position);
	//node->setPosition(playerShip->position);
	//node->setRotation(vector3d(0,0,playerShip->rotation));

	playerPosition = playerShip->GetPosition();
	//nodePosition.Z = 30;
	//node->setPosition(nodePosition);

	nodePosition = vector3df((f32)playerPosition.X,(f32)playerPosition.Y,0);

	motionIndicator->setPosition(nodePosition);

	camera->setTarget(nodePosition);
	nodePosition.Z = -(f32)GetCameraDistance();
	//nodePosition.X = -nodePosition.X;
	//nodePosition.Y = -nodePosition.Y;
	camera->setPosition(nodePosition);


	driver->beginScene(true, true, video::SColor(255,20,20,20));
	//driver->draw2DImage(driver->getTexture(RESOURCE_PATH"/starfield_1_medium.jpg"),core::vector2d<s32>(0,0));

	smgr->drawAll(); // draw the 3d scene
	device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)

	driver->endScene();

	int fps = driver->getFPS();

	if (lastFPS != fps)
	{
		text_string tmp(L"DangerGalaxy - first demo [");
		tmp += driver->getName();
		tmp += L"] fps: ";
		tmp += fps;
		tmp += L", ";
		tmp += playerShip->GetPosition().X;
		tmp += L", ";
		tmp += playerShip->GetPosition().Y;
		tmp += L", ";
		tmp += cameraDistance;

		device->setWindowCaption(tmp.c_str());
		lastFPS = fps;
	}
}

void DG_Game::Close() {
		/*
	In the end, delete the Irrlicht device.
	*/
	device->drop();

}

void DG_Game::UpdateCameraDistance()
{
	//f32 camreDistance;
	cameraDistance = 30.0*exp(cameraDistanceDegree*0.003);
	camera->setFarValue((f32)(cameraDistance*2.0));
	gamePhysics->UpdateMarkers(cameraDistance);

}


/*
The event receiver for keeping the pressed keys is ready, the actual responses
will be made inside the render loop, right before drawing the scene. So lets
just create an irr::IrrlichtDevice and the scene node we want to move. We also
create some other additional scene nodes, to show that there are also some
different possibilities to move and animate scene nodes.
*/
int main(int ArgumentCount, char **Arguments) {
	DG_Game * game = new DG_Game();

	// Initialize the game
	if(!game->Init(ArgumentCount, Arguments))
		return 0;

	// Main game loop
	while(!game->IsDone()) {

		game->Update();
	}

	// Shut down the system
	game->Close();

	return 0;
}

/*
That's it. Compile and play around with the program.
**/
