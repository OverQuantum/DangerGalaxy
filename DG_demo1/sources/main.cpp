/*
DangerGalaxy, Demo #1, development play
2.5D galaxy-wide space exploration game with crowdsource (micro)modding

Copyright © 2011 OverQuantum

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Author contacts:
http://overquantum.livejournal.com
https://github.com/OverQuantum

Project homepage:
https://github.com/OverQuantum/DangerGalaxy


DangerGalaxy uses Irrlicht Engine v1.7.2, released under zlib/libpng license.
Please refer to http://irrlicht.sourceforge.net for details


//#########################################################################


Change log

prehistory:
110510: SGU ended
110512: SAIS played
110512: Project Idea, (13.05.2011 ~01:30:00 MSK)
110513: Planing started (13.05.2011 22:23:23 MSK)
110531: github repo created
110602: Demo started

coding demo1:
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
110618: ADD: obrital params (semi-major axis and e)
110619: ADD: map of starsystem
110620: ADD: zoom on map, labels on map (yet looks terrible)
110621: CHG: discretization effect elimitated
110621: REM: thrust and speed indicators removed
110622: CHG: removed SetDevice e.t.c. from *View classes
110622: CHG: removed setPosition for camera each frame
110623: CHG: declarations and methods rearranged - now: class list; class declarations; methods, sorted by classes; main
110623: ADD: license info added
110623: ADD: simple FTL jump
110623: ADD: DisplayMessage method via console
110624: ADD: thrust restored as flame burst
110624: CHG: GameView::Init split into ::Init and ::Activate
110625: FIX: wchar_t and %s issues for Linux
110626: ADD: PlayerShip, Galaxy, GalaxyStarSystem
110626: ADD: maxGravityCheckRadiusSQ + simplified check of gravity using that
110626: CHG: StarSystemConstructor->ResourceManager
110627: CHG: Leaving star system
110627: ADD: Dump galaxy coordinates of ship into log
110627: CHG: getting videoDriver and so on is moved from DG_Game to ResourceManager
110628: ADD: Entering star systems after departing another
110628: CHG: Changing views reorganized into viewStack
110629: ADD: Advanced check of FTL break due to gravity
110629: ADD: maxFTLGravity moved from constant to SpaceObject

110829: FIX: text width on map adjusted to use font dimension
110829: ADD: Nearest stars markers on map (via SpaceObjects)
110830: CHG: near stars markers on map is now non SpaceObjects
110901: ADD: SHA1
110901: ADD: DeterminedRandomGenerator
110902: ADD: SetSeedWithCoordinates
110903: ADD: UndeterminedRandomGenerator
110903: ADD: galaxySeed
110903: ADD: more stars + name generator
110904: ADD: generation of star systems (very dumb)
110904: ADD: debug jump - press J to cycle thru all star systems
110906: ADD: generation of planets (dumb)
110908: CHG: generation of planets improved a little
110908: ADD: generation of moons (dumb)
110911: ADD: binary stars (dumb)
110911: ADD: dump basic info about star system
110912: ADD: multiple stars (dumb, many checks are skipped)
110915: ADD: multiple stars a bit more physical (no planets yet)
110915: ADD: time speed control, 1-100k (F1-F6)
110916: ADD: planets around multiple stars

110928: ADD: planet mass limit (depends on host star mass)
110929: CHG: start system is now nearest to (0,0)
110929: ADD: cache of near star systems
110929: ADD: real size galaxy, 100kx100k ly, quad form yet

110901: TMP: DeterminedRandomGenerator test printf


DONE:
+ surface of stars - without lighting each other
+ autopiloting stops
+ gravity
+ all physics to double
+ thrust should be different - interplanet travels and adjusting orbit requires different thrust
+ estimation of gravity domination
+ adjust autopilot to reduce thrust if speed is low
+ autopilot to orbiting gravity-dominant object
+ map of star system
+ elimitate discretization effect
+ removed SetDevice e.t.c. from *View classes - use GetDevice from DG_Game object, provided by SetRoot
+ removed setPosition for camera each frame
+ simple FTL jump
+ new thrust - flame, by resizable mesh
+ split GameView::Init into ::Init(...) and ::Activate(...)
+ resource handler
+ entering star system must be checked during FTL fly, not on exit
+ FTL limit from constant to PlayerShip
+ playerShip as separate class, derivate from SpaceObject? (incorporate thrust power e.t.c)
+ RNGs and seeds
+ generation of double and multiple stars

TODO
-1 more physics in star systems - HR and so on

-2 Recheck all chains of creationg physical objects, scene nodes and map objects - FTL/back, entering/leaving star sytems and so on

- Remove index "A" for root stars in single-star systems


- messages on main screen
- zoom map around arbitrary point, starting with ship
- display more info about orbit - shape, min/max distance (with fall estimation), period
- galaxy map

-3SpaceShip - derivative to SpaceObject with virtual UpdatePhysics() and so on

- moving of some background at FTL
- thrust flame as sub-object to SpaceObject
- galaxy-wide physics checker
- HUD
- auto-zoom camera - to show ship and nearest object
- camera further from system, than 4M? (degree=4000) - requires remastering scene
- planet rotation around it's axis
- somthing to display then ship inside stars (?)
- autopilot to travel to specific point
- corona of star and atmosphere of planets by decal/billboard/etc
- handling of errors
minor:
- check SHA1 code for license
- remove overlapping of labels on map (how?)
- better speed indicator
- exponential fading of light sources (?)
- SHA1 - unfinalized hashing, incomplete bytes

CONSIDER:
- orbiting of gravity-domination body by orbital parameters, not simple euler
- change check of vector length to bounding-box - max(X,Y,Z)  - ex. for radius of star system and so on

QUESTIONS
- how display map-info above map - gui or adjust billboard?
- limit FPS and calc physics to 200/100/?
- how to draw ship passing stars and planets?  [thinking: collision]
- time game koefficient (to pass star system in a matter of minutes/seconds) [current: 1000]
- size game koefficient (planet size in a relation to its orbits) [current: NO]
- size game logarithm (from hypergians stars to small moons/asteroids should be seen)   [current: NO]
- PI, G and other constant - where they should hold?


CONTROL:
A/D - rotate
W/S - thrust
Space - breaking (autopilot) relative to distant stars
1/2/3/4/5/6 - different thrust levels (1 - highest, 6 - lowest)
O - orbiting (around object which produce max graviry force at player's ship)
Up/Down - zoom
Tab - switch to map
F - jump to FTL (FTL works only if gravity < -5.75 dgr)
J - jump to some system (for debug only)
X - dump galaxy coordinates into log
F1/F2/F3/F4/F5/F6 - different time speed (1 - 1.0, 2 - 10, ... 6 - 100k)

CONTROL on map:
Up/Down - zoom
Esc - back to RealSpace

CONTROL on FTL:
Esc - drop out to RealSpace
X - dump galaxy coordinates into log

*/

//#########################################################################
//pragmas

#ifdef _MSC_VER
// We'll also define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif


//includes
#include <time.h>
#include <assert.h>
#include <irrlicht.h>
#include <SMaterial.h>

using namespace irr;


//defines
#define RESOURCE_PATH	"media"
#define CoeffDegreesToRadians  0.01745329
#define TWO_PI 6.2831853

//Distances is in 1000 km, so k=10^6  
//Time is in 1000 seconds - k=1000
//Mass is in 10^24 kg - k=10^24

//Gravitational constant
//G = 6.67384(80)*10^-11 N * (m/kg)^2 = .. [m*m*m/kg*s^2]
//Ggame = G * 10^-18/(10^-24 * 10^-6) = G * 10^12 = 66.7384
#define G_CONSTANT 66.7384

//speed of light in vacuum, c
#define LIGHTSPEED 300000.0

//Light-year, exact value
#define LIGHTYEAR 9460730472.5808

//Radius of star system in light-years (used to enter/leave star system check)
#define STAR_SYSTEM_RADIUS 0.1

//Maximum time between frames, in seconds
//Limits low FPS and slowdowns game if lower
//0.02 gives 50 fps
#define FRAME_TIME_MAX 0.02


//types
typedef core::stringw   text_string;
typedef unsigned __int64	u64;

//Irrlicht works in float, so f32
//DangerGalaxy works in double, so f64
typedef core::vector3d<f32>  vector3df;
typedef core::vector3d<f64>  vector3d;
typedef core::vector2d<s32>  vector2ds;
typedef core::vector2d<f64>  vector2d;
typedef scene::ISceneNode    SceneNode;
//typedef unsigned long u32;

//#########################################################################
//global functions

text_string print_f64(f64 value, const wchar_t* format)
{
	wchar_t tmp[255];
	swprintf(tmp, 255, format, value);
	return tmp;
}

//#########################################################################
//classes

class MyEventReceiver;
class GravityInfo;
class SpaceObject;
class GamePhysics;
//class StarSystemConstructor;
class DG_Game;
class GameView;
class RealSpaceView;
class MapObject;
class MapSpaceView;
class FTLView;
class PlayerShip;
class Galaxy;
class GalaxyStarSystem;
class ResourceManager;
class InfoFTL;
class SHA1;
class DeterminedRandomGenerator;
class UndeterminedRandomGenerator;
class StarComponent;

/*
To receive events like mouse and keyboard input, or GUI events like "the OK
button has been clicked", we need an object which is derived from the
irr::IEventReceiver object. There is only one method to override:
irr::IEventReceiver::OnEvent(). This method will be called by the engine once
when an event happens. What we really want to know is whether a key is being
held down, and so we will remember the current state of each key.
*/
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

	virtual bool IsKeyPressed(EKEY_CODE keyCode) 
	{
		if (KeyIsDown[keyCode])
		{
			KeyIsDown[keyCode] = false;
			return true;
		}
		return false;
	}

	//void CleanKeyStatus(EKEY_CODE keyCode) {KeyIsDown[keyCode]=false;}
	
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

		void UpdateGravityInfoOrbit(SpaceObject* orbitingObject);

		//Kepler orbit elements (around maxGravityObject)
		f64 orbitSemimajorAxis;//Semimajor axis
		f64 orbitEccentricity;//Eccentricity
		f64 orbitArgumentPeriapsis;//Argument of periapsis
};

//SpaceObject - is any object in current visible space
class SpaceObject {

	public:

		//TODO: think on subclassing space objects by motion type
		enum MotionType {
			MOTION_NONE,
			MOTION_ORBITAL,
			MOTION_NAVIGATION,
			MOTION_FTL,
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
		f64 GetRotation() {return rotation;}
		text_string GetName() {return name;}
		MotionType GetMotionType() {return motionType;}
		//f32 GetMaxThrust() {return maxThrust;}
		//f32 GetMaxRotationThrust() {return maxRotationThrust;}
		f64 GetMaxFTLGravity() {return maxFTLGravity;}

		SceneNode* GetNode() {return sceneNode;}

		//setters
		void SetPosition(vector3d newPos) {position = newPos;}
		void SetSpeed(vector3d newSpeed) {speed = newSpeed;}
		void SetRotation(f64 newRotation) {rotation = newRotation;}
		void SetNode(SceneNode * node) {sceneNode = node;}
		void SetMarkerNode(SceneNode * node, f64 size) {sceneMarkerNode = node; sizeMarker = size;}
		void SetMotionType(MotionType newType) {motionType = newType;}
		void SetOrbitalParams(SpaceObject* parent, f64 radius, f64 Period, f64 EpochPhase);
		void SetPhysics(GamePhysics* physicsOwner) {physics = physicsOwner;}
		void SetMaxThrust(f64 newMaxThrust, f64 newMaxRotationThrust) {maxThrust = newMaxThrust; maxRotationThrust = newMaxRotationThrust; }
		void SetMass(f64 newMass) {mass = newMass;}
		void SetMassRadius(f64 newMassRadius) {gravityMinRadius = newMassRadius;}
		void SetGravity(bool emit, bool affected) {isEmitGravity = emit,isAffectedByGravity = affected;}
		void SetName(text_string newName) {name = newName;}
		void SetMaxFTLGravity(f64 newGravity) {maxFTLGravity = newGravity;}
		
		//void SetThrust(f64 newThrust) {thrustPower = newThrust;}
		//void SetRotationSpeed(f64 newRotSpeed) {rotationSpeed = newRotSpeed;}

		vector3d GetGravityAcceleration(vector3d location);
		void SetControl(f64 newValue, ControlType type);

		void AutopilotBreak();
		void AutopilotOrbiting();
		void AutopilotSetSpeed(vector3d requiredSpeed);

		void JumpToFTL(f64 ftlSpeed);
		void BreakFTL(f64 remainingSpeed);

		//updating
		void UpdatePhysics(f64 time);
		void UpdateSceneNode();
		void UpdateSceneNode(SpaceObject* centerSceneObject);
		void UpdateMarkerNode(f64 cameraDistance);
	protected:
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
		f64 ftlSpeed;//in multiple of lightspeed

		f64 maxFTLGravity;//Max acceleration for FTL possible

		vector3d position;//current position in space, coordinates (zero at star system center of mass)
		vector3d speed;//current motion speed, relative to "background stars"
		f64 rotation;//rotation angle, degrees (zero is direction to down)

		SceneNode * sceneNode; //Irrlich renderable object
		//scene::IBillboardSceneNode * sceneMarkerNode; //Irrlich renderable object - for displaying from a far
		SceneNode * sceneMarkerNode; //Irrlich renderable object - for displaying from a far
		//vector3d acceleration; //
};

//GamePhysics - calculates movement, collision, gravity and so on
class GamePhysics {
	public:
		f64 globalTime;//TODO: move field into private area

		bool IsInterstellar() {return isInterstellar;}
		vector2d GetGalaxyCoordinatesOfCenter() {return galaxyCoordinatesOfCenter;}

		void SetGalaxyCoordinatesOfCenter(vector2d newCoordinates) {galaxyCoordinatesOfCenter = newCoordinates;}
		void SetGravityCheckRadiusSQ(f64 newRadiusSQ) {maxGravityCheckRadiusSQ = newRadiusSQ;}
		void SetPlayerShip(PlayerShip* newPlayerShip) {playerShip = newPlayerShip;}
		void SetTimeSpeed(f64 newSpeed) {timeSpeed = newSpeed;}

		void Update(f64 time);
		void UpdateNodes(SpaceObject* centerSceneObject);
		void AddObject(SpaceObject* newObject);
		void UpdateMarkers(f64 cameraDistance);
		void UpdateMapMarkers(f64 mapScale);
		
		vector3d GetGravityAcceleration(vector3d location);
		GravityInfo* GetGravityInfo(vector3d location);
		
		//bool IsFTLPossible(vector3d location);
		bool IsFTLPossible(vector3d location, f64 gravityLimit);

		//InfoFTL* CheckFTLBreak(vector3d start, vector3d end);
		InfoFTL* CheckFTLBreak(vector3d start, vector3d end, f64 gravityLimit);
		//bool IsOutOfStarSystem(vector3d location);
		bool CheckLeaveStarSystem();

		void GoInterstellar();
		void GoStarSystem();

		void MakeMap(MapSpaceView* mapView);
	private:
		bool isInterstellar;//Nothing except ship
		f64 maxGravityCheckRadiusSQ; //if object is farther from this radius, then we could skip checking of gravity for FTL, radius squared as it is much easier to check this way
		f64 timeSpeed;//speed of time going, 1.0 for normal, 100 for faster

		PlayerShip* playerShip;
		core::array<SpaceObject*> listObjects;
		vector2d galaxyCoordinatesOfCenter;
};

//ResourceManager - manage game resource
class ResourceManager
{
	public:
		void Setup(IrrlichtDevice* newDevice, scene::ISceneManager* newSceneManager, video::IVideoDriver* newVideoDriver, MyEventReceiver* newEventReceiver, GamePhysics* newPhysics);
		void SetSceneManager(scene::ISceneManager* newSceneManager) {sceneManager = newSceneManager;}

		IrrlichtDevice* GetDevice() {return device;}
		video::IVideoDriver* GetVideoDriver() {return videoDriver;}
		MyEventReceiver* GetEventReceiver() {return eventReceiver;}

		//void MakeSimpleSystem();
		void MakeBackground();
		SpaceObject* MakeStar(f64 radius = 10.0, s32 polygons = 32);
		SpaceObject* MakePlanet(f64 radius = 3.0, s32 polygons = 32);
		SpaceObject* MakeBarycenter();
		SpaceObject* MakeShip();
		SpaceObject* LoadNodesForShip(SpaceObject* ship);
		void AddMarker(SpaceObject* toObject, u32 type);

		SceneNode* NewShipNode();

	private:
		GamePhysics* physics;

		IrrlichtDevice* device;
		scene::ISceneManager* sceneManager;
		video::IVideoDriver* videoDriver;
		MyEventReceiver* eventReceiver;
};

//DG_Game - game root, hold everything else
class DG_Game {

	public:

		enum ViewType {
			VIEW_NONE,
			VIEW_REALSPACE,
			VIEW_SECTOR_MAP,
			VIEW_FTL,
		};

		int Init(int Count, char **Arguments);
		void Update();
		void Close();

		/*
		//Deprecated
		void ActivateMap();
		void ActivateRealSpace();
		void ActivateFTL();
		*/

		s32 AcviateView(ViewType newView);
		s32 CloseView(ViewType oldView);
		s32 SwitchView(ViewType newView);

		bool IsViewActive(ViewType checkedView);

		void GoInterstellar();
		void GoStarSystem(GalaxyStarSystem* toStarSystem);
		
		Galaxy* GetGalaxy() {return wholeGalaxy;}

		ResourceManager* GetResourceManager() {return resourceManager;}

		PlayerShip* GetPlayerShip() {return playerShip;}
	//void SetVideoDriver(video::IVideoDriver* newVideoDriver) {videoDriver = newVideoDriver;}
	//void SetEventReceiver(MyEventReceiver* newReceiver) {eventReceiver = newReceiver;}

		
		//void ChangeState(StateClass *State);
		//StateClass *GetState() { return State; }

		bool IsDone() { return Done; }
		void SetDone(bool Value) { Done = Value; }
		//float GetTimeStep() { return TimeStep; }
		//void ResetTimer();

		//MAP
		s32 cameraMapDistanceDegree;

	private:
		//f64 MOVEMENT_SPEED;
		// Flags
		ResourceManager* resourceManager;
		Galaxy* wholeGalaxy;

		PlayerShip* playerShip;

		GalaxyStarSystem* currentStarSystem;

		IrrlichtDevice* device;
		u32 then;
		GamePhysics * gamePhysics;
		bool Done, MouseWasLocked;
		SceneNode * node;
		MyEventReceiver* receiver;
		scene::ISceneManager* smgr;
		video::IVideoDriver* driver;
		s32 lastFPS;

		s32 gameMode;//0 - flying, 1 - map

		core::array<ViewType*> viewStack;

		RealSpaceView* RealSpace;
		MapSpaceView* SectorMap;
		FTLView* FTLSpace;

		GameView* activeView;

		void InternalAcviateView(ViewType newView);

};

//GameView - interface-like class for different game views
class GameView
{
public:
	virtual void Init() {};
	virtual void Activate() {};
	virtual void Update(f64 frameDeltaTime) {};
	virtual void Close() {};

	void SetRoot(DG_Game* newRoot) {gameRoot = newRoot;}
	void SetSceneManager(scene::ISceneManager* newSceneManager) {sceneManager = newSceneManager;}
	//void SetDevice(IrrlichtDevice* newDevice) {device = newDevice;}
	//void SetVideoDriver(video::IVideoDriver* newVideoDriver) {videoDriver = newVideoDriver;}
	//void SetEventReceiver(MyEventReceiver* newReceiver) {eventReceiver = newReceiver;}
	void SetPhysics(GamePhysics* newPhysics) {gamePhysics = newPhysics;}

	void DisplayMessage(text_string message);

protected:
	DG_Game* gameRoot;
	GamePhysics * gamePhysics;
	MyEventReceiver* eventReceiver;
	IrrlichtDevice* device;
	scene::ISceneManager* sceneManager;
	video::IVideoDriver* videoDriver;
	ResourceManager* resourceManager;
};

//RealSpaceView - to render RealSpace
class RealSpaceView : public GameView
{
public:
	void Init();
	void Activate();
	void Update(f64 frameDeltaTime);
	void Close();

	f64 GetCameraDistance() {return cameraDistance;}
	s32 cameraDistanceDegree;

	void Clean();

	void UpdateCameraDistance();

private:
	f64 cameraDistance;

	PlayerShip* playerShip;
	f64 playerThrust; //TODO: move to other class (?)

	scene::ICameraSceneNode* camera;
	SceneNode* playerShipThrust;
	//scene::IParticleSystemSceneNode * playerThrustParticles;
	//scene::IParticleEmitter*  playerThrustEmitter;
	//scene::IParticleSystemSceneNode* motionIndicator;
	gui::IGUIStaticText* simpleTextToDisplay;
};

//MapObject - single object on map (for MapSpaceView)
class MapObject
{
public:
	void UpdatePosition(f64 mapScale);
	void SetNonObjectPosition(vector2d newPositions) {originalObject = 0;nonObjectPosition = newPositions;}
	void SetNode(SceneNode * node) {sceneNode = node;}
	void SetOriginal(SpaceObject* object) {originalObject = object;}

private:
	SpaceObject* originalObject;
	vector2d nonObjectPosition; //in case of originalObject=0
	SceneNode* sceneNode; //Irrlich renderable object
};

//MapSpaceView - for drawing map of RealSpace
class MapSpaceView : public GameView
{
public:
	void Init();
	void Activate();
	void Update(f64 frameDeltaTime);
	void Close();
	void AddObject(SpaceObject* spaceObject);
	void AddStarMarker(GalaxyStarSystem* starSystem);

	s32 cameraDistanceDegree;

	void UpdateCameraDistance();

private:
	core::array<MapObject*> MapObjectList;
};

//FTLView - to render fly on FTL
class FTLView : public GameView
{
public:
	void Init();
	void Activate();
	void Update(f64 frameDeltaTime);
	void Close();

private:
	PlayerShip* playerShip;
	SceneNode* playerShipNode;
	scene::ICameraSceneNode* camera;
};

//PlayerShip - hold all information about player and his ship
class PlayerShip : public SpaceObject
{
public:
	PlayerShip();

	vector2d GetGalaxyCoordinates() {return galaxyCoordinates;}

	void SetGalaxyCoordinates(vector2d newPosition) {galaxyCoordinates = newPosition;}

	void UpdateGalaxyCoordinates();

private:
	vector2d galaxyCoordinates;
};

//Galaxy - hold main information about whole Galaxy
class Galaxy
{
public:
	void Init();//creation
	GalaxyStarSystem* GetStarSystem(vector2ds coordinates);//Get star system in quadrant
	GalaxyStarSystem* GetNearStarSystem(vector2d coordinates);//Get nearest star system by exact coordinates
	//void AddNearStarSystems(GamePhysics * gamePhysics);
	void AddNearStarSystems(MapSpaceView* mapView);//Add markers of near star system to MapView
	u32 CheckStarPresence(vector2ds coordinates);//Check only presence of star in quadrant
	GalaxyStarSystem* GetStartStarSystem(); //Get star system of player start
	void UpdatePlayerLocation(vector2d coordinates);//For updating cache of stars

	GalaxyStarSystem* DebugJump();

private:
	u32 debugStarCounter;
	u8 galaxySeed[16];//seed of whole galaxy
	DeterminedRandomGenerator* galaxyRNG;//
	
	core::array<GalaxyStarSystem*> knownStars;//cache for near stars
	vector2ds knownStarsCenter;//center of cache

	GalaxyStarSystem* SeedStar(vector2ds coordinates);//seed star system from galaxy seed. Prereq: galaxyRNG must be seeded with coordinates in CheckStarPresence() or so
	void UpdateKnownStars();//Updates caches (ex. in case of player moves to quadrant other than center of cache)
};

//Information about 1 star system in the galaxy
class GalaxyStarSystem
{
public:

	GalaxyStarSystem(vector2ds quadrantCoordinates);

	vector2d GetGalaxyCoordinates() {return galaxyCoordinates;}
	vector2ds GetGalaxyQuadrant() {return galaxyQuadrant;}
	text_string GetName() {return name;}

	void SetSeed(u8* seedData, u32 seedLen);

	//static GalaxyStarSystem* RandomStar(vector2ds quadrantCoordinates);
	void GenerateStar();
	void SetName(text_string newName) {name = newName;}

	void GenerateStarSystem(ResourceManager* resourceManager);

	void GenerateComponent(ResourceManager* resourceManager, f64 mass, f64 sizeLimit, SpaceObject** rootObject);

	void GenerateComponent2(StarComponent* component);
	SpaceObject* FinalizeComponent(ResourceManager* resourceManager, StarComponent* component);
private:
	u32 componentIndex;//for naming stars in systems
	u32 planetIndex;//for numbering planets
	DeterminedRandomGenerator* starRNG;
	vector2d galaxyCoordinates;
	vector2ds galaxyQuadrant;
	text_string name;
};

//Keep information about FTL fly over line segment
class InfoFTL
{
public:
	vector3d breakPoint;//valid if FTL fly must be breaked
	bool breaked;
};

//SHA-1 hasher
class SHA1
{
public:
	SHA1();//default constructor, also reset object
	
	void Reset();
	u32 ProcessArrayFinal(u8* data, u32 dataLen);
	u32 WriteHash(u8* outputData);
private:
	enum HasherStatus {
		HASHER_RESET,
		HASHER_SOMEDATA,
		HASHER_FINISHED,
	};

	HasherStatus status;
	u32 state[5];//internal state
	u32 processedBytes;//how much data processed
	void TransformBlock(u32* data);
};

//Generates determined stream of bytes
class DeterminedRandomGenerator
{
//scheme:
// SHA1 ( seed [32] | offset [4] ) -> 16 bytes

//coordinated seed:  byte-seed [24] | x [4] | y [4]
public:
	static const u32 seedLength = 32;
	DeterminedRandomGenerator();

	void SetSeed(u8* newSeed, u32 seedLen);//up to 32 bytes, zero-padded at the end
	void SetSeedWithCoordinates(u8* newSeed, u32 seedLen, u32 x, u32 y);//up to 24 bytes, zero-padded at the end
	void GetSeed(u8* buffer);//return 32 bytes

	void SetOffset(u32 newOffset);
	u32 GetOffset() {return offset;}

	u8 GenerateByte();//return 1 random byte and shifts offset to next
	u8 GetByteByOffset(u32 byteOffset);//return random byte by offset
	void GenerateBytes(u8* destination, u32 len);//write <len> bytes and shifts offset
private:
	static const u32 bufferLength = 64;
	u8 hashBuffer[bufferLength];//seed of generator + space for forming data to hash

	SHA1* hasher;

	u32 offset;//offset of generator
	u8 block[20];//generated block
	u32 blockOffset;//offset of block

	void GenerateBlock();
};

//Generates undetermined stream of bytes
class UndeterminedRandomGenerator
{
//scheme:
// SHA1 ( previous-random [16] | random sources ) -> next 16 bytes

public:
	UndeterminedRandomGenerator();

	void AddSeed(u8* newSeed, u32 seedLen);

	u8 GenerateByte();//return 1 random byte
	void GenerateBytes(u8* destination, u32 len);//write <len> bytes 

private:
	static const u32 bufferLength = 64;//full buffer
	static const u32 blockLength = 16;//output part
	u64 counter;

	u8 hashBuffer[bufferLength];
	u32 offset;//offset of generator inside block
	SHA1* hasher;

	void GenerateBlock();
	void RehashBlock();
};

//Holds info on star or composite component of star system
class StarComponent
{
public:
	u32 type;//0 - composite, 1 - main-sequence star, 2 - ...
	f64 mass;//mass, in units
	f64 radius;//physical radius of object, in units,  for composite its radius of components + mutual distance
	f64 luminosity;//luminosity of object, in Solar's, N/A for composite
	f64 innerOrbitLimit;//inner limit for orbiting objects
	f64 outerOrbitLimit;//outer limit for orbiting objects
	//text_string spectralClass;
	f64 colorIndexBV;//  en.wikipedia.org/wiki/B-V_color,  N/A for composite
	f64 subComponentsOrbit; //distance between subcomponents
	StarComponent* subComponentA; //most massive, 0 if current is single object
	StarComponent* subComponentB; //least massive, 0 if current is single object
};

/*
class ResourceManager
{
public:
	void SetSceneManager(scene::ISceneManager* newSceneManager) {sceneManager = newSceneManager;}
	void SetVideoDriver(video::IVideoDriver* newVideoDriver) {videoDriver = newVideoDriver;}

	SceneNode* MakeShip();

private:
	scene::ISceneManager* sceneManager;
	video::IVideoDriver* videoDriver;
};*/


//#########################################################################
//Class methods

//#########################################################################
//GravityInfo

void GravityInfo::UpdateGravityInfoOrbit(SpaceObject* orbitingObject)
{
	f64 invAxis;//q = 1/a, where a - Semimajor axis
	f64 specificRAMomentum;//Specific relative angular momentum 

	if (!maxGravityObject)
		return;

	//Semimajor axis, a, is calc by vis-viva equation: 1/a = 2/r - v*v/G(M+m) = q
	vector3d relativePosition, relativeSpeed;

	relativePosition = orbitingObject->GetPosition() - maxGravityObject->GetPosition();
	relativeSpeed = orbitingObject->GetSpeed() - maxGravityObject->GetSpeed();

	invAxis = 2.0/relativePosition.getLength() - relativeSpeed.getLengthSQ()/(G_CONSTANT*maxGravityObject->GetMass());

	//Eccentricity, e, is calc using specific relative angular momentum: e = sqrt(1+h*h*q*q/2), where h=|H|, q = 1/a
	specificRAMomentum = relativeSpeed.X * relativePosition.Y - relativeSpeed.Y * relativePosition.X;

	if (invAxis != 0.0)
	{
		orbitSemimajorAxis = 1.0/invAxis;
	}
	else
	{
		orbitSemimajorAxis = 0.0;
	}
	//orbitEccentricity = sqrt(1+specificRAMomentum*specificRAMomentum*invAxis*invAxis*.5);//not work

	//TODO: optimize G_CONSTANT*maxGravityObject->GetMass() combined with previous use
	orbitEccentricity = sqrt(1-specificRAMomentum*specificRAMomentum*invAxis/(G_CONSTANT*maxGravityObject->GetMass()));
	//orbitEccentricity = -2;//not calced
}


text_string GravityInfo::print()
{
	text_string gravityInfo(L"");
	if (maxGravityObject)
	{
		f64 percent = 0.0;
		gravityInfo = L"Max gravity from: ";
		gravityInfo += maxGravityObject->GetName();
		gravityInfo += L" (";
		gravityInfo += print_f64(log(maxGravity),L"%.02f");
		gravityInfo += L" dgr ";//dgr: logarithm of gravity acceleration, 0 dgr = 1 m/s*s
		if (secondMaxGravityObject)
		{
			percent = 100.0*maxGravity/(maxGravity+secondMaxGravity);
			gravityInfo += print_f64(percent,L"%.02f");
		}
		gravityInfo += L"%)\r\n";
		gravityInfo += L"Orbit: ";
		gravityInfo += print_f64(orbitSemimajorAxis,L"%.02f");
		gravityInfo += L", e: ";
		gravityInfo += print_f64(orbitEccentricity,L"%f");
		if (secondMaxGravityObject)
		{
			gravityInfo += L"\r\nNext gravity from: ";
			gravityInfo += secondMaxGravityObject->GetName();
			gravityInfo += L" (";
			gravityInfo += print_f64(log(secondMaxGravity),L"%.02f");
			gravityInfo += L" dgr ";
			//gravityInfo += (100.0-percent);
			gravityInfo += print_f64(100.0-percent,L"%.02f");
			gravityInfo += L"%)";

			//gravityInfo += L"% / ";
			//gravityInfo += print_f64(log(secondMaxGravity)-log(maxGravity),L"%.02f");
			//gravityInfo += L" dgr)";
		}
	}
	else
	{
		gravityInfo = L"no gravity detected";
	}
	return gravityInfo;
}

//#########################################################################
//SpaceObject

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

	ftlSpeed = 10.0;
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
	maxFTLGravity = 0.003;
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

void SpaceObject::UpdateSceneNode(SpaceObject* centerSceneObject)
{
	f32 positionX = (f32)(position.X - centerSceneObject->position.X);
	f32 positionY = (f32)(position.Y - centerSceneObject->position.Y);
	if (sceneNode)
	{
		sceneNode->setPosition(vector3df(positionX,positionY,0));
		sceneNode->setRotation(vector3df(0,0,(f32)rotation));
	}
	if (sceneMarkerNode)
	{
		//TODO: optimize?
		sceneMarkerNode->setPosition(vector3df(positionX,positionY,0.01f));
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

		//TODO: use LIGHTSPEED instead of fixed constants
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
				//Phase+=360.0*physics->globalTime/orbitalPeriod;
				Phase+=TWO_PI*physics->globalTime/orbitalPeriod;
			}
			position.X = cos(Phase)*orbitalRadius;
			position.Y = sin(Phase)*orbitalRadius;
			position.Z = 0;
			if (orbitingObject!=0)
				position+=orbitingObject->position;
		}
		break;
	case MOTION_FTL:
		{
			vector3d position2 = position + speed*time;
			InfoFTL* checkFTL = physics->CheckFTLBreak(position,position2,maxFTLGravity);
			if (checkFTL->breaked)
			{
				position = checkFTL->breakPoint;
				motionType = MOTION_NAVIGATION;
			}
			else
			{
				position = position2;
			}

			//if (!(physics->IsFTLPossible(position)))
			//	motionType = MOTION_NAVIGATION;
		}
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
				f64 speedValue = orbitalRadius*TWO_PI/orbitalPeriod;
				//Phase+=360.0*physics->globalTime/orbitalPeriod;
				Phase+=TWO_PI*physics->globalTime/orbitalPeriod;
				speed.X = -sin(Phase)*speedValue;
				speed.Y = cos(Phase)*speedValue;
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
		return G_CONSTANT*vectorDirection*mass/(gravityMinRadius*gravityMinRadius*gravityMinRadius);
	}
	return G_CONSTANT*vectorDirection*mass/(distance*distance*distance);
}

//Breaking relative to distant-stars
void SpaceObject::AutopilotOrbiting()
{
	
	f64 requiredRelativeSpeed;
	vector3d maxGravityAcceleration;
	vector3d relativePosition;
	vector3d relativeSpeed;
	vector3d requiredSpeed;

	//Get gravity info from game physics
	GravityInfo* gravInfo = physics->GetGravityInfo(position);
	if (!gravInfo->maxGravityObject) //no dominant object - no orbiting
		return;
	
	relativePosition = position - gravInfo->maxGravityObject->GetPosition();
	relativeSpeed = speed - gravInfo->maxGravityObject->GetSpeed();

	//get gravity acceleration from dominant gravity object
	maxGravityAcceleration = gravInfo->maxGravityObject->GetGravityAcceleration(position);

	//required speed value - via centro-escape acceleration
	requiredRelativeSpeed = sqrt((maxGravityAcceleration.getLength())*(relativePosition.getLength())); 

	//required speed - perpendicular to relative position
	requiredSpeed.X = relativePosition.Y;
	requiredSpeed.Y = -relativePosition.X;
	requiredSpeed.Z = 0;

	//check opposite direction, it could be closer to current speed
	if (relativeSpeed.dotProduct(requiredSpeed)<0)
	{//yes, this direction is opposite to current speed vector
		requiredSpeed.X=-requiredSpeed.X;//reverse required speed
		requiredSpeed.Y=-requiredSpeed.Y;
	}

	requiredSpeed.normalize();//normalize - to get vector of 1 unit length
	requiredSpeed*=requiredRelativeSpeed;//use required speed value
	requiredSpeed+=gravInfo->maxGravityObject->GetSpeed();//absolute value

	//debug: simple set speed to required value
	//speed = requiredSpeed;
	AutopilotSetSpeed(requiredSpeed);
}

void SpaceObject::JumpToFTL(f64 ftlSpeed)
{
	motionType = MOTION_FTL;
	//speed.normalize();
	speed = GetDirection();
	speed*=ftlSpeed*LIGHTSPEED;
}

void SpaceObject::BreakFTL(f64 remainingSpeed)
{
	motionType = MOTION_NAVIGATION;
	speed.normalize();
	speed*=remainingSpeed;
}

//#########################################################################
//GamePhysics

void GamePhysics::Update(f64 time)
{
	u32 i;
	globalTime += time*timeSpeed;
	for (i=0;i<listObjects.size();i++)
	{
		listObjects[i]->UpdatePhysics(time*timeSpeed);
		//SpaceObjectList[i]->UpdateSceneNode();
	}
}

void GamePhysics::UpdateNodes(SpaceObject* centerSceneObject)
{
	u32 i;
	for (i=0;i<listObjects.size();i++)
	{
		//SpaceObjectList[i]->UpdatePhysics(time);
		listObjects[i]->UpdateSceneNode(centerSceneObject);
	}
}


void GamePhysics::UpdateMarkers(f64 cameraDistance)
{
	u32 i;
	for (i=0;i<listObjects.size();i++)
	{
		listObjects[i]->UpdateMarkerNode(cameraDistance);
	}
}

void GamePhysics::UpdateMapMarkers(f64 mapScale)
{
}

void GamePhysics::AddObject(SpaceObject* newObject)
{
	listObjects.push_back(newObject);
	newObject->SetPhysics(this);
}

vector3d GamePhysics::GetGravityAcceleration(vector3d location)
{
	u32 i;
	vector3d acceleration = vector3d(0,0,0);
	for (i=0;i<listObjects.size();i++)
		if (listObjects[i]->IsEmittingGravity())
		{
			//vector3d vectorDirection = SpaceObjectList[i]->GetPosition()-location;
			//f64 distance = vectorDirection.getLength();
			//acceleration += 66.7*vectorDirection*SpaceObjectList[i]->GetMass()/(distance*distance*distance);
			acceleration += listObjects[i]->GetGravityAcceleration(location);
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
	//f64 orbitSemimajorAxis, orbitEccentricity;

	for (i=0;i<listObjects.size();i++)
		if (listObjects[i]->IsEmittingGravity())
		{
			//vector3d vectorDirection = SpaceObjectList[i]->GetPosition()-location;
			//f64 distance = vectorDirection.getLength();
			//gravity = (vectorDirection*SpaceObjectList[i]->GetMass()/(distance*distance*distance)).getLength();
			gravity = listObjects[i]->GetGravityAcceleration(location).getLength();
			if (gravity>maxGravity)
			{
				secondMaxGravity = maxGravity;
				secondMaxGravityObject = maxGravityObject;
				maxGravity=gravity;
				maxGravityObject = listObjects[i];
			}
			else if (gravity>secondMaxGravity)
			{
				secondMaxGravity = gravity;
				secondMaxGravityObject = listObjects[i];
			}
		}

	//gravInfo->printableInfo = gravityInfo;
	gravInfo->maxGravity = maxGravity;
	gravInfo->maxGravityObject = maxGravityObject;
	gravInfo->secondMaxGravity = secondMaxGravity;
	gravInfo->secondMaxGravityObject = secondMaxGravityObject;
	gravInfo->orbitSemimajorAxis = -2;
	gravInfo->orbitEccentricity = -2;
	gravInfo->orbitArgumentPeriapsis = -2;//not calced
	return gravInfo;
}

void GamePhysics::MakeMap(MapSpaceView* mapView)
{
	u32 i;
	//sceneManager->clear();
	for (i=0;i<listObjects.size();i++)
	{
		mapView->AddObject(listObjects[i]);
	}
}

bool GamePhysics::IsFTLPossible(vector3d location, f64 gravityLimit)
{
	if (isInterstellar)
		return true;
	if (location.getLengthSQ()>maxGravityCheckRadiusSQ)
		return true;

	f64 grav = GetGravityAcceleration(location).getLengthSQ();
	//if (grav>GRAVITY_MAX_FTL_SQ) 
	if (grav>(gravityLimit*gravityLimit))
		return false;
	return true;
}

InfoFTL* GamePhysics::CheckFTLBreak(vector3d start, vector3d end, f64 gravityLimit)
{
	InfoFTL* info = new InfoFTL();
	info->breaked = false;

	do
	{
		if (isInterstellar)
			break;

		//TODO: more advanced check, calc minimum distance to all grav-emit objects and check FTL limit against that
		if (!IsFTLPossible(start,gravityLimit))
		{
			info->breaked = true;
			info->breakPoint = start;
			break;
		}

		if (gravityLimit==0) //bad limit, but we should not check further
			break;

		vector3d moving = end-start;
		vector3d perpendicularMoving = vector3d(moving.Y,-moving.X,0);
		vector3d toObject;
		f64 criticalRadiusSQToMass = G_CONSTANT/gravityLimit;
		f64 criticalRadiusSQ;
		f64 a,ia,mb2,c,D1,x1,x2;
		//f64 minDistance;

		//solving vector equation x*moving + R-crit = toObject
		//R-crit = toObject - x*moving
		//R-crit^2 = (toObject - x*moving)^2
		//R-crit^2 = toObject^2 - 2*x*(moving*toObject) + x^2*moving^2
		//a*x^2+b*x+c = 0
		//a = moving^2, b = -2*(moving*toObject), c = toObject^2-R-crit^2
		//D1 = (b/2)^2-a*c, x = (-(b/2) +- sqrt(D1))/a, if D>=0
		//we need only 0<x<1

		//a is equal for all object, we can calc it now
		a = moving.getLengthSQ();
		if (a==0) break;//a is zero, so start = end, nothing need to be check further
		ia = 1.0/a;

		for (u32 i=0;i<listObjects.size();i++)
			if (listObjects[i]->IsEmittingGravity())
			{
				criticalRadiusSQ = criticalRadiusSQToMass*listObjects[i]->GetMass();
				toObject = listObjects[i]->GetPosition()-start;
				mb2 = toObject.dotProduct(moving); //mb2 = -b/2
				c = toObject.getLengthSQ()-criticalRadiusSQ;
				D1 = mb2*mb2-a*c;
				if (D1<0) continue; //Discriminant < 0, no roots, we can skip object
				D1 = sqrt(D1);
				x1 = (mb2-D1)*ia;
				x2 = (mb2+D1)*ia;

				if (x1>1)//minimum root is larger than 1, object is far ahead
					continue;
				if (x2<0)//maximum root is less than zero, object is behind
					continue;

				//otherwise - we have roots inside segment (0,1), so FTL must be breaked
				info->breaked = true;
				if (x1<0)
				{// x1<0, so in (0,1) is x2, we should break now
					info->breakPoint = start;
				}
				else
				{// x1>0, so x1 is in (0,1), we should break at reaching its position
					info->breakPoint = start + x1*moving;
				}
				break;


				/*
				if (x1>=0 && x1<=1)
				{
					info->breaked = true;
					info->breakPoint = start + x1*moving;
					break;
				}
				if (x2>=0 && x2<=1)
				{
					info->breaked = true;
					info->breakPoint = start + x2*moving;
					break;
				}

				//
				/*
				toObject = listObjects[i]->GetPosition()-start;
				minDistance = toObject.dotProduct(perpendicularMoving);
				minDistance *= minDistance;
				minDistance /= perpendicularMoving.getLengthSQ();
				*/

			}

		/*
		if (info->breaked)
			break;

		if (!IsFTLPossible(end))
		{
			info->breaked = true;
			info->breakPoint = end;
			break;
		}*/
	} while(false);
	return info;
}


/*
bool GamePhysics::IsOutOfStarSystem(vector3d location)
{
	if (location.getLengthSQ()>maxGravityCheckRadiusSQ)
		return true;
	return false;
}*/

bool GamePhysics::CheckLeaveStarSystem()
{
	if (isInterstellar) return false;//already left
	if (playerShip->GetPosition().getLengthSQ()>maxGravityCheckRadiusSQ)
		return true;//GoInterstellar();
	return false;

}

void GamePhysics::GoInterstellar()
{
	if (isInterstellar) return;//already there
	listObjects.clear();
	isInterstellar=true;
	//listObjects.push_back((SpaceObject*)playerShip);
	AddObject(playerShip);
}

void GamePhysics::GoStarSystem()
{
	listObjects.clear();
	isInterstellar = false;
	AddObject(playerShip);
}

//#########################################################################
//ResourceManager

void ResourceManager::Setup(IrrlichtDevice* newDevice, scene::ISceneManager* newSceneManager, video::IVideoDriver* newVideoDriver, MyEventReceiver* newEventReceiver, GamePhysics* newPhysics)
{
	eventReceiver = newEventReceiver;
	device = newDevice;
	physics = newPhysics;
	sceneManager = newSceneManager;
	videoDriver = newVideoDriver;
}

void ResourceManager::MakeBackground()
{
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
}

/*
void ResourceManager::MakeSimpleSystem()
{
	f64 planetSizes[11]={190.0,0.382,0.949,1.00,0.532,11.209,9.449,4.007,3.883,0.19};
	f64 planetOrbits[11]={0.0,0.39,0.72,1.00,1.52,5.20,9.54,19.22,30.06,45.0};
	f64 planetPeriods[11]={0.0,0.24,0.62,1.00,1.88,11.86, 29.46,84.01,164.8,248.09};
	f64 planetMass[11]={330000.0,0.06,0.82,1.00,0.11,317.8,95.2,14.6,17.2,0.0022};
	text_string planetNames[11]={L"Sun",L"Mercury",L"Venus",L"Earth",L"Mars",L"Jupiter",L"Saturn",L"Uranus",L"Neptune",L"Pluto"};
	//f32 planetMass[11]={0.0f,0.06f,0.82f,1.00f,0.11f,317.8f,95.2f,14.6f,17.2f,0.0022f};

	//Solar system
	//Everything not to scale
	SpaceObject* planet;

	//planet = MakeStar(planetSizes[0]*.01f);//sun is 10 times larger, compared to orbits
	//planet->SetMass(planetMass[0]);
	//planet->SetGravity(true,false);

	for (s32 i=0;i<10;i++)
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
			planet->SetOrbitalParams(0,planetOrbits[i]*150000.0,planetPeriods[i]*365.25*86.4,i*i*20.0);//1000 seconds in 1
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
			moon->SetName(L"Moon");
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
}*/

SpaceObject* ResourceManager::MakeStar(f64 radius, s32 polygons)
{
	SpaceObject* newStar = new SpaceObject();
	SceneNode * sceneNode;

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

SpaceObject* ResourceManager::MakePlanet(f64 radius, s32 polygons)
{
	SpaceObject* newPlanet = new SpaceObject();
	SceneNode * sceneNode;

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

SpaceObject* ResourceManager::MakeBarycenter()
{
	SpaceObject* barycenter = new SpaceObject();
	barycenter->SetNode(0);
	
	physics->AddObject(barycenter);

	return barycenter;
}

SpaceObject* ResourceManager::LoadNodesForShip(SpaceObject* ship)
{
	ship->SetNode(NewShipNode());
	AddMarker(ship,1);

	return ship;
}


SpaceObject* ResourceManager::MakeShip()
{
	SpaceObject* ship = new SpaceObject();
	ship->SetMotionType(SpaceObject::MOTION_NAVIGATION);

	ship->SetGravity(false,true);
	physics->AddObject(ship);

	LoadNodesForShip(ship);

	return ship;
}

SceneNode* ResourceManager::NewShipNode()
{
	SceneNode* node = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/ship1.irrmesh"));
	if (node)
	{
		node->setScale(core::vector3df(1.f));
		node->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/ships.png"));
		node->setMaterialFlag(video::EMF_LIGHTING, false);
		node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	}

	return node;
}

void ResourceManager::AddMarker(SpaceObject* toObject, u32 type)
{
	//scene::IBillboardSceneNode * sceneNode2 = sceneManager->addBillboardSceneNode(toObject->GetNode());
	//SceneNode * sceneNode2 = sceneManager->addBillboardSceneNode(toObject->GetNode());
	SceneNode* sceneNode2 = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/plane.irrmesh"));
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

//#########################################################################
//GameView

void GameView::DisplayMessage(text_string message)
{
	wprintf(L"DG: %ws\r\n",message.c_str());
}


//#########################################################################
//RealSpaceView

void RealSpaceView::Init()
{
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
	playerShip = gameRoot->GetPlayerShip();
	resourceManager = gameRoot->GetResourceManager();

	videoDriver = resourceManager->GetVideoDriver();
	device = resourceManager->GetDevice();
	eventReceiver = resourceManager->GetEventReceiver();

	resourceManager->SetSceneManager(sceneManager);
	
	sceneManager->clear();
	device->getGUIEnvironment()->clear();
	
	// create a particle system

	/*
	motionIndicator =
		sceneManager->addParticleSystemSceneNode(false);

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
	motionIndicator->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/fire.bmp"));
	motionIndicator->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
	*/
	resourceManager->LoadNodesForShip((SpaceObject*)playerShip);

	playerShipThrust = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/thrust1.irrmesh"));
	if (playerShipThrust)
	{
		playerShipThrust->setScale(core::vector3df(1.f));
		playerShipThrust->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/fire.bmp"));
		playerShipThrust->setMaterialFlag(video::EMF_LIGHTING, false);
		playerShipThrust->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
		playerShipThrust->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
		playerShipThrust->setParent(playerShip->GetNode());
		playerShipThrust->setPosition(vector3df(-0.45f,0.f,-0.1f));
		playerShipThrust->setScale(vector3df(2.0f,0.5f,1.0f));
		playerShipThrust->setVisible(false);
	}





	/*
	// create a particle system 2
	playerThrustParticles =
		sceneManager->addParticleSystemSceneNode(false,playerShip->GetNode());

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
	playerThrustParticles->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/fire.bmp"));
	playerThrustParticles->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
	//playerThrust->setVisible(false);
	//ps2->setRotation(vector3d(0,0,90));
	*/

	/*
	SceneNode * node3 = smgr->addMeshSceneNode(smgr->getMesh(RESOURCE_PATH"/ship1.irrmesh"));
	if (node3)
	{
		node3->setScale(core::vector3df(3,3,3));
		node3->setMaterialTexture(0, driver->getTexture(RESOURCE_PATH"/ships.png"));
		node3->setMaterialFlag(video::EMF_LIGHTING, false);
		node3->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	}*/

	playerThrust = 1.0;

	camera = sceneManager->addCameraSceneNode();
	camera->setFOV(.7f);//field-of-view
	camera->setTarget(vector3df(0));//update camera look-at point

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
	simpleTextToDisplay->setOverrideColor(video::SColor(255, 0, 255, 0));
	/**/

	// This is the movemen speed in units per second.
	//MOVEMENT_SPEED = 5.0;

	//smgr->saveScene("1.irrexp");
	cameraDistanceDegree = 1000;
	UpdateCameraDistance();
}

void RealSpaceView::Activate()
{
}

void RealSpaceView::Update(f64 frameDeltaTime)
{
	vector3d playerPosition;// = node->getPosition();
	vector3df nodePosition;// = node->getPosition();

	if(eventReceiver->IsKeyDown(irr::KEY_KEY_W))
		//playerShip->speed.Y += MOVEMENT_SPEED * frameDeltaTime;
		playerShip->SetControl(playerThrust,SpaceObject::CONTROL_THRUST_RELATIVE);
	else if(eventReceiver->IsKeyDown(irr::KEY_KEY_S))
		//playerShip->speed.Y -= MOVEMENT_SPEED * frameDeltaTime;
		playerShip->SetControl(-playerThrust,SpaceObject::CONTROL_THRUST_RELATIVE);
	else
		playerShip->SetControl(0.0,SpaceObject::CONTROL_THRUST_ABSOLUTE);

	if(eventReceiver->IsKeyDown(irr::KEY_KEY_A))
		//rotate = MOVEMENT_SPEED*30.f;
		playerShip->SetControl(1.0,SpaceObject::CONTROL_ROTATION_SPEED_RELATIVE);
		//playerShip->speed.X -= MOVEMENT_SPEED * frameDeltaTime;
	else if(eventReceiver->IsKeyDown(irr::KEY_KEY_D))
		playerShip->SetControl(-1.0,SpaceObject::CONTROL_ROTATION_SPEED_RELATIVE);
		//rotate = -MOVEMENT_SPEED*30.f;
		//playerShip->speed.X += MOVEMENT_SPEED * frameDeltaTime;
	else
		playerShip->SetControl(0,SpaceObject::CONTROL_ROTATION_SPEED_ABSOLUTE);

	if(eventReceiver->IsKeyPressed(irr::KEY_KEY_1))
		playerThrust = 1.0;
	if(eventReceiver->IsKeyPressed(irr::KEY_KEY_2))
		playerThrust = 0.1;
	if(eventReceiver->IsKeyPressed(irr::KEY_KEY_3))
		playerThrust = 0.01;
	if(eventReceiver->IsKeyPressed(irr::KEY_KEY_4))
		playerThrust = 0.001;
	if(eventReceiver->IsKeyPressed(irr::KEY_KEY_5))
		playerThrust = 0.0001;
	if(eventReceiver->IsKeyPressed(irr::KEY_KEY_6))
		playerThrust = 0.00001;

	if(eventReceiver->IsKeyPressed(irr::KEY_F1))
		gamePhysics->SetTimeSpeed(1.0);
	if(eventReceiver->IsKeyPressed(irr::KEY_F2))
		gamePhysics->SetTimeSpeed(10.0);
	if(eventReceiver->IsKeyPressed(irr::KEY_F3))
		gamePhysics->SetTimeSpeed(100.0);
	if(eventReceiver->IsKeyPressed(irr::KEY_F4))
		gamePhysics->SetTimeSpeed(1000.0);
	if(eventReceiver->IsKeyPressed(irr::KEY_F5))
		gamePhysics->SetTimeSpeed(10000.0);
	if(eventReceiver->IsKeyPressed(irr::KEY_F6))
		gamePhysics->SetTimeSpeed(100000.0);

	if (eventReceiver->IsKeyDown(irr::KEY_SPACE))
		playerShip->AutopilotBreak();
	if (eventReceiver->IsKeyDown(irr::KEY_KEY_O))
		playerShip->AutopilotOrbiting();

	if (eventReceiver->IsKeyPressed(irr::KEY_KEY_X))
	{
		//Dump galaxy coordinates, in light-years
		//10 digits after point roughly gives game units, as light-year is roughly 10^10 * 1000 km
		text_string galaxyCoords=L"Coordinates: ";
		galaxyCoords+=print_f64(playerShip->GetGalaxyCoordinates().X,L"%.010f");
		galaxyCoords+=L", ";
		galaxyCoords+=print_f64(playerShip->GetGalaxyCoordinates().Y,L"%.010f");
		DisplayMessage(galaxyCoords);
	}
		

	if (eventReceiver->IsKeyPressed(irr::KEY_TAB))
		//gameRoot->ActivateMap();
		gameRoot->AcviateView(DG_Game::VIEW_SECTOR_MAP);

	if (eventReceiver->IsKeyPressed(irr::KEY_KEY_F))
	{
		if (gamePhysics->IsFTLPossible(playerShip->GetPosition(),playerShip->GetMaxFTLGravity()))
		{
			playerShip->JumpToFTL(3000.0);
			//gameRoot->ActivateFTL();
			gameRoot->SwitchView(DG_Game::VIEW_FTL);

		}
		else
		{
			DisplayMessage(L"Gravity is too high to jump to FTL");
		}
	}
	if (eventReceiver->IsKeyPressed(irr::KEY_KEY_J))
	{
		GalaxyStarSystem* jumpTo;
		jumpTo = gameRoot->GetGalaxy()->DebugJump();
		if (jumpTo)
		{
			vector3d tempPos = playerShip->GetPosition();
			gameRoot->GoStarSystem(jumpTo);
			playerShip->SetPosition(tempPos);
			
			playerShip->UpdateGalaxyCoordinates();
			gameRoot->GetGalaxy()->UpdatePlayerLocation(playerShip->GetGalaxyCoordinates());
		}
	}


	//playerShip->thrustPower = thrust*MOVEMENT_SPEED*5.f;
	//playerShip->rotationSpeed = rotate;
	//playerShip->SetThrust(thrust*MOVEMENT_SPEED*5.f);
	//playerShip->SetRotationSpeed(rotate);
	//someShip->SetControl(1.f,SpaceObject::CONTROL_THRUST_ABSOLUTE);
	//someShip->SetControl(20.f,SpaceObject::CONTROL_ROTATION_SPEED_ABSOLUTE);

	
	
	f64 thrust = playerShip->GetThrust();
	if (thrust!=0)
	{
		f32 thrustScale;
		if (thrust>0)
		{
			thrustScale = (f32)(.2+log(thrust+1.0));
			playerShipThrust->setScale(vector3df((f32)thrustScale,0.5f,1.f));
		}
		else
		{
			thrustScale = (f32)(-.2-log(1.0-thrust));
			playerShipThrust->setScale(vector3df((f32)thrustScale,-0.5f,1.f));
		}
		playerShipThrust->setVisible(true);

		//vector3d emitterDirection=-thrust*.000001*playerShip->GetDirection();

		//playerThrustParticles->setEmitter(playerThrustEmitter);
		//playerThrustEmitter->setDirection(vector3df((f32)emitterDirection.X,(f32)emitterDirection.Y,0));
	}
	else
	{
		playerShipThrust->setVisible(false);
		//playerThrustParticles->setEmitter(0);
	}

	if(eventReceiver->IsKeyDown(irr::KEY_UP))
		if (cameraDistanceDegree<4000)
		{
			cameraDistanceDegree++;
			//cameraDistance *= 1.f*(1.f+frameDeltaTime);
			UpdateCameraDistance();
		}

	if(eventReceiver->IsKeyDown(irr::KEY_DOWN))
		if (cameraDistanceDegree>-100)
		{
			//cameraDistance *= 1.f*(1.f-frameDeltaTime);
			cameraDistanceDegree--;
			UpdateCameraDistance();
		}

	text_string debug_text(L"Speed: ");
	f64 playerSpeed;
	GravityInfo* gravInfo;
	gravInfo = gamePhysics->GetGravityInfo(playerShip->GetPosition());
	gravInfo->UpdateGravityInfoOrbit(playerShip);

	playerSpeed = playerShip->GetSpeed().getLength();
	debug_text += playerSpeed;
	debug_text += " km/s\r\n";
	debug_text += (playerSpeed/LIGHTSPEED);
	debug_text += " c; ";
	debug_text += "\r\n";
	debug_text += gravInfo->print();
	simpleTextToDisplay->setText(debug_text.c_str());

	gamePhysics->Update(frameDeltaTime);
	gamePhysics->UpdateNodes(playerShip);

	//TODO: use resourceManager to render?
	videoDriver->beginScene(true, true, video::SColor(255,20,20,20));
	sceneManager->drawAll(); // draw the 3d scene
	device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)
	videoDriver->endScene();
}

void RealSpaceView::Close()
{
}

void RealSpaceView::UpdateCameraDistance()
{
	//f32 camreDistance;
	cameraDistance = 30.0*exp(cameraDistanceDegree*0.003);
	camera->setFarValue((f32)(cameraDistance*2.0));
	gamePhysics->UpdateMarkers(cameraDistance);

	camera->setPosition(vector3df(0,0,-(f32)cameraDistance));//update camera look-from point

}

void RealSpaceView::Clean()
{
	sceneManager->clear();
	//sceneManager-> (playerShip->GetNode());
}

//#########################################################################
//MapObject

void MapObject::UpdatePosition(f64 mapScale)
{
	if (sceneNode)
	{
		if (originalObject)
		{
			vector3d position = originalObject->GetPosition();
			sceneNode->setPosition(vector3df((f32)(position.X*mapScale),(f32)(position.Y*mapScale),0));
		}
		else
		{
			vector2d position = nonObjectPosition*mapScale;
			sceneNode->setPosition(vector3df((f32)(position.X),(f32)(position.Y),0));
		}

	}
}

//#########################################################################
//MapSpaceView

void MapSpaceView::AddObject(SpaceObject* spaceObject)
{
	vector3d position = spaceObject->GetPosition();

	SceneNode* sceneNode2 = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/plane.irrmesh"));
	if (sceneNode2)
	{
		sceneNode2->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
		sceneNode2->setMaterialFlag(video::EMF_LIGHTING, false);
		sceneNode2->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/star2.bmp"));
		//sizeMarker  = .07;
		sceneNode2->setPosition(vector3df((f32)(position.X*.000001),(f32)(position.Y*.000001),0));
	}
	text_string label = spaceObject->GetName();
	core::dimension2d<u32> labelSize = sceneManager->getGUIEnvironment()->getBuiltInFont()->getDimension(label.c_str());
	SceneNode * sceneNode3 = sceneManager->addBillboardTextSceneNode(0,label.c_str(),sceneNode2,core::dimension2d<f32>(labelSize.Width*0.24f,2.0f));
	
	//SceneNode* sceneNode3 = sceneManager->addBillboardTextSceneNode(0,label.c_str(),sceneNode2,core::dimension2d<f32>(10.f,2.0f));
	
	//getDimension(
	sceneNode3->setPosition(vector3df(labelSize.Width*0.12f,1.0f,0));
	//sceneNode3->setPosition(sceneNode3->getScale());

	MapObject* newMapObject = new MapObject();
	newMapObject->SetNode(sceneNode2);
	newMapObject->SetOriginal(spaceObject);
	MapObjectList.push_back(newMapObject);
}

void MapSpaceView::AddStarMarker(GalaxyStarSystem* starSystem)
{
	vector2d position = (starSystem->GetGalaxyCoordinates() - gamePhysics->GetGalaxyCoordinatesOfCenter())*LIGHTYEAR;

	if (position.getLengthSQ()<0.01)
		return;//skip same star

	//TODO: add non-object marker
	SceneNode* sceneNode2 = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/plane.irrmesh"));
	if (sceneNode2)
	{
		sceneNode2->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
		sceneNode2->setMaterialFlag(video::EMF_LIGHTING, false);
		sceneNode2->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/star2.bmp"));
		//sizeMarker  = .07;
		//sceneNode2->setPosition(vector3df((f32)(position.X*.000001*LIGHTYEAR),(f32)(position.Y*.000001*LIGHTYEAR),0));
	}
	text_string label = starSystem->GetName();
	core::dimension2d<u32> labelSize = sceneManager->getGUIEnvironment()->getBuiltInFont()->getDimension(label.c_str());
	SceneNode * sceneNode3 = sceneManager->addBillboardTextSceneNode(0,label.c_str(),sceneNode2,core::dimension2d<f32>(labelSize.Width*0.24f,2.0f));
	
	//SceneNode* sceneNode3 = sceneManager->addBillboardTextSceneNode(0,label.c_str(),sceneNode2,core::dimension2d<f32>(10.f,2.0f));
	
	//getDimension(
	sceneNode3->setPosition(vector3df(labelSize.Width*0.12f,1.0f,0));
	//sceneNode3->setPosition(sceneNode3->getScale());

	MapObject* newMapObject = new MapObject();
	newMapObject->SetNode(sceneNode2);
	newMapObject->SetNonObjectPosition(position);
	MapObjectList.push_back(newMapObject);
}


void MapSpaceView::Init()
{
	resourceManager = gameRoot->GetResourceManager();
	videoDriver = resourceManager->GetVideoDriver();
	device = resourceManager->GetDevice();
	eventReceiver = resourceManager->GetEventReceiver();
}

void MapSpaceView::Activate()
{
	MapObjectList.clear();
	//gamePhysics->MakeMap(sceneManager,videoDriver,this);
	sceneManager->clear();

	gamePhysics->MakeMap(this);

	gameRoot->GetGalaxy()->UpdatePlayerLocation(gameRoot->GetPlayerShip()->GetGalaxyCoordinates());

	gameRoot->GetGalaxy()->AddNearStarSystems(this);

	scene::ICameraSceneNode* camera = sceneManager->addCameraSceneNode();
	camera->setFOV(.7f);
	camera->setTarget(vector3df(0,0,0));
	camera->setPosition(vector3df(0,0,-100.f));
	camera->setFarValue(200.f);

	cameraDistanceDegree = 5500;
	UpdateCameraDistance();
}

void MapSpaceView::Update(f64 frameDeltaTime)
{
	if (eventReceiver->IsKeyPressed(irr::KEY_ESCAPE))
		//gameRoot->ActivateRealSpace();
		gameRoot->CloseView(DG_Game::VIEW_SECTOR_MAP);

	
	
	if(eventReceiver->IsKeyDown(irr::KEY_UP))
		//if (cameraDistanceDegree<8200) //estimated good to see ~10 LY in all directions
		{
			cameraDistanceDegree++;

			//f64 mapScale = 30.0*exp(cameraDistanceDegree*-0.003);
			//gamePhysics->UpdateMapMarkers(mapScale);
			UpdateCameraDistance();
		}

	if(eventReceiver->IsKeyDown(irr::KEY_DOWN))
		//if (cameraDistanceDegree>0)
		{
			//cameraDistance *= 1.f*(1.f-frameDeltaTime);
			cameraDistanceDegree--;
			//UpdateCameraDistance();
			//f64 mapScale = 30.0*exp(cameraDistanceDegree*-0.003);
			//gamePhysics->UpdateMapMarkers(mapScale);
			UpdateCameraDistance();

		}

	//TODO: use resourceManager to render?
	videoDriver->beginScene(true, true, video::SColor(255,20,20,20));
	sceneManager->drawAll();
	device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)
	videoDriver->endScene();
}

void MapSpaceView::UpdateCameraDistance()
{
	u32 i;
	f64 mapScale;
	mapScale = 30.0*exp(cameraDistanceDegree*-0.003);
	for (i=0;i<MapObjectList.size();i++)
	{
		//MapObjectList[i]->UpdatePhysics(time);
		MapObjectList[i]->UpdatePosition(mapScale);
	}
}



void MapSpaceView::Close()
{
	sceneManager->drop();
}


//#########################################################################
//FTLView

void FTLView::Init()
{
	resourceManager = gameRoot->GetResourceManager();

	videoDriver = resourceManager->GetVideoDriver();
	//device = resourceManager->GetDevice();
	eventReceiver = resourceManager->GetEventReceiver();

	sceneManager->clear();

	resourceManager->SetSceneManager(sceneManager);

	playerShipNode  = resourceManager->NewShipNode();

	/*
	playerShipNode = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/ship1.irrmesh"));
	if (playerShipNode)
	{
		playerShipNode->setScale(core::vector3df(1.f));
		playerShipNode->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/ships.png"));
		playerShipNode->setMaterialFlag(video::EMF_LIGHTING, false);
		playerShipNode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	}*/

	camera = sceneManager->addCameraSceneNode();
	if (camera)
	{
		camera->setPosition(vector3df(0,0,-20.f));
		camera->setTarget(vector3df(0));
		camera->setFOV(0.7f);
	}

}

void FTLView::Activate()
{
	playerShip = gameRoot->GetPlayerShip();

	playerShipNode->setRotation(vector3df(0,0,(f32)playerShip->GetRotation()));
	//sceneManager->addSceneNode(
}

void FTLView::Update(f64 frameDeltaTime)
{
	if (playerShip->GetMotionType()!=SpaceObject::MOTION_FTL)
	{
		DisplayMessage(L"Drop out of FTL due to high gravity");
		playerShip->BreakFTL(10.0);
		//gameRoot->ActivateRealSpace();
		gameRoot->SwitchView(DG_Game::VIEW_REALSPACE);
	}
	if (eventReceiver->IsKeyPressed(irr::KEY_ESCAPE))
	{
		DisplayMessage(L"Manuial exit from FTL");
		playerShip->BreakFTL(100.0);
		//gameRoot->ActivateRealSpace();
		gameRoot->SwitchView(DG_Game::VIEW_REALSPACE);
	}

	if (eventReceiver->IsKeyPressed(irr::KEY_KEY_X))
	{
		text_string galaxyCoords=L"Coordinates: ";
		galaxyCoords+=print_f64(playerShip->GetGalaxyCoordinates().X,L"%.010f");
		galaxyCoords+=L", ";
		galaxyCoords+=print_f64(playerShip->GetGalaxyCoordinates().Y,L"%.010f");
		DisplayMessage(galaxyCoords);
	}

	gamePhysics->Update(frameDeltaTime);

	//TODO: use resourceManager to render?
	videoDriver->beginScene(true, true, video::SColor(255,20,200,20));
	sceneManager->drawAll();
	videoDriver->endScene();
}

void FTLView::Close()
{
	sceneManager->drop();
}

//#########################################################################
//DG_Game


// Processes parameters and initializes the game
s32 DG_Game::Init(s32 Count, char **Arguments) {
	// ask user for driver

	wholeGalaxy = new Galaxy();
	wholeGalaxy->Init();

	vector2d startGalaxyCoord = vector2d(0);
	currentStarSystem = wholeGalaxy->GetStartStarSystem();
	if (currentStarSystem)
	{
		startGalaxyCoord = currentStarSystem->GetGalaxyCoordinates();
	}
	
	gamePhysics = new GamePhysics;
	gamePhysics->globalTime = 0;
	gamePhysics->SetGalaxyCoordinatesOfCenter(startGalaxyCoord);
	gamePhysics->SetGravityCheckRadiusSQ(STAR_SYSTEM_RADIUS*STAR_SYSTEM_RADIUS*LIGHTYEAR*LIGHTYEAR);
	gamePhysics->SetTimeSpeed(1.0);

	viewStack.clear();

	/*
	video::E_DRIVER_TYPE driverType=driverChoiceConsole();
	if (driverType==video::EDT_COUNT)
		return 1;
	*/
	//driverType = video::EDT_OPENGL;

	// create device

	receiver = new MyEventReceiver();

	//IrrlichtDevice* device = createDevice(driverType,
	device = createDevice(video::EDT_OPENGL,
			core::dimension2d<u32>(1024, 768), 16, false, false, false, receiver);

	if (device == 0)
		return 1; // could not create selected driver.

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	gameMode  = 0;


	RealSpace = new RealSpaceView();
	RealSpace->SetRoot(this);
	RealSpace->SetSceneManager(smgr);
	RealSpace->SetPhysics(gamePhysics);

	resourceManager = new ResourceManager();
	resourceManager->Setup(device,smgr,driver,receiver,gamePhysics);

	//playerShip = (PlayerShip*)resourceManager->MakeShip();
	playerShip = new PlayerShip();
	gamePhysics->AddObject((SpaceObject*)playerShip);
	playerShip->SetGravity(false,true);
	playerShip->SetMotionType(SpaceObject::MOTION_NAVIGATION);
	playerShip->SetRotation(90);
	playerShip->SetSpeed(vector3d(-320.28,0,0));
	playerShip->SetMaxThrust(100000,150);
	playerShip->SetName(L"Player");
	playerShip->SetMaxFTLGravity(0.003138);
	//acceleration = 0.003138 <=> gravity = -5.75 "dgr"


	gamePhysics->SetPlayerShip(playerShip);

	//wholeGalaxy->AddNearStarSystems(gamePhysics);

	RealSpace->Init();
	gamePhysics->GoStarSystem();
	GoStarSystem(currentStarSystem);

	playerShip->SetPosition(vector3d(0,1300,0));

	/*
	gamePhysics->GoStarSystem();
	RealSpace->Init();
	resourceManager->MakeBackground();
	resourceManager->MakeSimpleSystem();
	*/


	//activeView = RealSpace;


	SectorMap = new MapSpaceView();
	SectorMap->SetRoot(this);
	SectorMap->SetSceneManager(smgr->createNewSceneManager()); //drop in MapSpaceView::Close
	//SectorMap->SetDevice(device);
	//SectorMap->SetVideoDriver(driver);
	//SectorMap->SetEventReceiver(&receiver);
	SectorMap->SetPhysics(gamePhysics);
	SectorMap->Init();


	FTLSpace = new FTLView();
	FTLSpace->SetRoot(this);
	FTLSpace->SetSceneManager(smgr->createNewSceneManager()); //drop in FTLSpace::Close
	FTLSpace->SetPhysics(gamePhysics);
	FTLSpace->Init();


	lastFPS = -1;

	// In order to do framerate independent movement, we have to know
	// how long it was since the last frame
	then = device->getTimer()->getTime();

	//ActivateRealSpace();
	AcviateView(VIEW_REALSPACE);


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
	f64 frameDeltaTime = (f64)(now - then) / 1000.0; // Time in seconds
	then = now;

	if (frameDeltaTime>FRAME_TIME_MAX) frameDeltaTime = FRAME_TIME_MAX;//50 fps minimum, or slowdown game

	//Update game via current view
	//Game physics is updated via view due to view-dependency behaviour of physics (i.e. physics not updated in case of viewing map)
	activeView->Update(frameDeltaTime);

	playerShip->UpdateGalaxyCoordinates();

	//Check that player fly too far from star system and it (system) could be unloaded
	if (gamePhysics->CheckLeaveStarSystem())
	{
		{
			text_string message = L"Departed star system ";
			message += currentStarSystem->GetName();
			RealSpace->DisplayMessage(message);
		}
		gamePhysics->GoInterstellar();

		if (IsViewActive(VIEW_REALSPACE))
			GoInterstellar();
	}

	//Check that player reach border some star system and so this system should be loaded
	if (gamePhysics->IsInterstellar())
	{
		wholeGalaxy->UpdatePlayerLocation(playerShip->GetGalaxyCoordinates());

		//TODO: this is dumb check, if FTL speed is larger than 50000c, then on 50 fps min checks may be too seldom to "catch" star system
		GalaxyStarSystem* nearStarSystem = wholeGalaxy->GetNearStarSystem(playerShip->GetGalaxyCoordinates());
		if (nearStarSystem)
		{
			GoStarSystem(nearStarSystem);
		}
	}


	s32 fps = driver->getFPS();

	if (lastFPS != fps)
	{
		text_string tmp(L"DangerGalaxy - first demo [");
		tmp += driver->getName();
		tmp += L"] fps: ";
		tmp += fps;
/*		tmp += L", ";
		tmp += playerShip->GetPosition().X;
		tmp += L", ";
		tmp += playerShip->GetPosition().Y;
		tmp += L", ";
		tmp += cameraDistance;*/

		device->setWindowCaption(tmp.c_str());
		lastFPS = fps;
	}
}

void DG_Game::Close() {
		/*
	In the end, delete the Irrlicht device.
	*/
	
	//Close views
	RealSpace->Close();
	SectorMap->Close();
	FTLSpace->Close();

	device->drop();
}

/*
void DG_Game::ActivateRealSpace()
{
	if (gamePhysics->IsInterstellar())
	{
		GoInterstellar();
	}
	RealSpace->Activate();
	activeView = RealSpace;
}

void DG_Game::ActivateMap()
{
	SectorMap->Activate();
	activeView = SectorMap;
}

void DG_Game::ActivateFTL()
{
	FTLSpace->Activate();
	activeView = FTLSpace;
}*/


void DG_Game::GoInterstellar()
{
	vector2d playerGalaxyCoordinates;
	s32 cameraDistance = RealSpace->cameraDistanceDegree;

	currentStarSystem = 0;

	RealSpace->Clean();
	RealSpace->Init();

	RealSpace->cameraDistanceDegree = cameraDistance;
	RealSpace->UpdateCameraDistance();

	resourceManager->SetSceneManager(smgr);
	resourceManager->MakeBackground();
	
	playerGalaxyCoordinates = playerShip->GetGalaxyCoordinates();

	gamePhysics->SetGalaxyCoordinatesOfCenter(playerGalaxyCoordinates);
	gamePhysics->GoInterstellar();

	playerShip->SetPosition(vector3d(0));
	//wholeGalaxy->AddNearStarSystems(gamePhysics);
}

void DG_Game::GoStarSystem(GalaxyStarSystem* toStarSystem)
{
	s32 cameraDistance = RealSpace->cameraDistanceDegree;
	vector2d playerGalaxyCoordinates = playerShip->GetGalaxyCoordinates();

	vector2d playerRelativeCoordinates;
	vector2d nearStarSystemGalaxyCoordinates;

	gamePhysics->GoStarSystem();

	RealSpace->Clean();
	RealSpace->Init();

	resourceManager->SetSceneManager(smgr);
	resourceManager->MakeBackground();

	{
		text_string message = L"Entered to system ";
		message += toStarSystem->GetName();
		RealSpace->DisplayMessage(message);
	}

	//resourceManager->MakeSimpleSystem();
	toStarSystem->GenerateStarSystem(resourceManager);

	currentStarSystem = toStarSystem;

	RealSpace->cameraDistanceDegree = cameraDistance;
	RealSpace->UpdateCameraDistance();

	nearStarSystemGalaxyCoordinates = toStarSystem->GetGalaxyCoordinates();
	
	playerRelativeCoordinates = (playerGalaxyCoordinates-nearStarSystemGalaxyCoordinates)*LIGHTYEAR;
	gamePhysics->SetGalaxyCoordinatesOfCenter(nearStarSystemGalaxyCoordinates);
	playerShip->SetPosition(vector3d(playerRelativeCoordinates.X,playerRelativeCoordinates.Y,0));

	//wholeGalaxy->AddNearStarSystems(gamePhysics);
}

void DG_Game::InternalAcviateView(ViewType newView)
{
	switch(newView)
	{
	case VIEW_NONE:
		break;
	case VIEW_REALSPACE:
		if (gamePhysics->IsInterstellar())
		{
			GoInterstellar();
		}
		RealSpace->Activate();
		activeView = RealSpace;
		break;
	case VIEW_SECTOR_MAP:
		SectorMap->Activate();
		activeView = SectorMap;
		break;
	case VIEW_FTL:
		FTLSpace->Activate();
		activeView = FTLSpace;
		break;
	}
}

s32 DG_Game::AcviateView(ViewType newView)
{
	if (IsViewActive(newView)) return 1;//already opened
	viewStack.push_back(new ViewType(newView));
	InternalAcviateView(newView);
	return 0;
}

s32 DG_Game::CloseView(ViewType oldView)
{
	ViewType currentView = *viewStack.getLast();
	for (u32 i=0;i<viewStack.size();i++)
	{
		if (*viewStack[i]==oldView)
		{
			viewStack.erase(i);
			if (currentView != *viewStack.getLast())
			{
				InternalAcviateView(*viewStack.getLast());
			}
			return 0;
		}
	}
	return 1;
}

s32 DG_Game::SwitchView(ViewType newView)
{
	ViewType currentView = *viewStack.getLast();
	if (newView==currentView)
		return 0;//aready activated

	viewStack[viewStack.size()-1] = new ViewType(newView);
	InternalAcviateView(newView);

	return 0;
}

bool DG_Game::IsViewActive(ViewType checkedView)
{
	for (u32 i=0;i<viewStack.size();i++)
	{
		if (*viewStack[i]==checkedView)
		{
			return true;
		}
	}
	return false;
}


//#########################################################################
//PlayerShip

PlayerShip::PlayerShip()
{
	SpaceObject();
	galaxyCoordinates = vector2d(0);
}

void PlayerShip::UpdateGalaxyCoordinates()
{
	galaxyCoordinates = physics->GetGalaxyCoordinatesOfCenter();
	galaxyCoordinates.X += position.X / LIGHTYEAR;
	galaxyCoordinates.Y += position.Y / LIGHTYEAR;
}

//#########################################################################
//Galaxy

void Galaxy::Init()
{
	debugStarCounter = 0;

	//TEMP
	galaxySeed[0]=0x10;
	galaxySeed[1]=0x12;
	galaxySeed[2]=0x17;
	galaxySeed[3]=0xF0;
	galaxySeed[4]=0xE2;
	galaxySeed[5]=0xC4;
	galaxySeed[6]=0x66;
	galaxySeed[7]=0x90;
	memcpy(galaxySeed+8,galaxySeed,8);

	galaxyRNG = new DeterminedRandomGenerator();

	galaxyRNG->SetSeed(galaxySeed,16);

	knownStarsCenter.X = 0;
	knownStarsCenter.Y = 0;

	UpdateKnownStars();

}

GalaxyStarSystem* Galaxy::GetStarSystem(vector2ds coordinates)
{
	//u32 i;

	if (CheckStarPresence(coordinates)==1)
	{
		return SeedStar(coordinates);
	}
	
	return 0;

	/*
	for (i=0;i<knownStars.size();i++)
	{
		if (coordinates==knownStars[i]->GetGalaxyQuadrant())
			return knownStars[i];
	}*/
	return 0;
}

void Galaxy::UpdatePlayerLocation(vector2d coordinates)
{
	vector2ds quadrant;
	quadrant.X = (s32)floor(coordinates.X);
	quadrant.Y = (s32)floor(coordinates.Y);
	if (quadrant!=knownStarsCenter)
	{
		knownStarsCenter = quadrant;
		UpdateKnownStars();
	}
}

GalaxyStarSystem* Galaxy::GetNearStarSystem(vector2d coordinates)
{
	u32 i;
	f64 minDistanceSQ=STAR_SYSTEM_RADIUS*STAR_SYSTEM_RADIUS; //So nothing is returned in case of too-far system
	f64 distanceSQ;
	GalaxyStarSystem* minDistanceObject=0;

	//Don't forget to call UpdatePlayerLocation beforehand

	for (i=0;i<knownStars.size();i++)
	{
		//TODO: optimize by using (???)
		distanceSQ = (coordinates-knownStars[i]->GetGalaxyCoordinates()).getLengthSQ();
		if (distanceSQ<minDistanceSQ)
		{
			minDistanceSQ = distanceSQ;
			minDistanceObject = knownStars[i];
		}
	}
	return minDistanceObject;
}

void Galaxy::AddNearStarSystems(MapSpaceView* mapView)
{
	u32 i;
	//vector2d coordinates = gamePhysics->GetGalaxyCoordinatesOfCenter();
	for (i=0;i<knownStars.size();i++)
	{
		mapView->AddStarMarker(knownStars[i]);

		/*
		SpaceObject * nearStar = new SpaceObject();
		vector2d starPosition = (knownStars[i]->GetGalaxyCoordinates()-coordinates)*LIGHTYEAR;
		nearStar->SetName(knownStars[i]->GetName());
		nearStar->SetMotionType(SpaceObject::MOTION_NONE);
		nearStar->SetPosition(vector3d(starPosition.X,starPosition.Y,0));
		nearStar->SetNode(0);
		//coordinates-knownStars[i]->GetGalaxyCoordinates())
		gamePhysics->AddObject(nearStar);
		//if (coordinates==knownStars[i]->GetGalaxyQuadrant())
			//return knownStars[i];*/
	}
	return;

}

u32 Galaxy::CheckStarPresence(vector2ds coordinates)
{
	if (coordinates.X<-65536 || coordinates.X>65535 || coordinates.Y<-65536 || coordinates.Y>65535)
		return 0;//no stars outside 131072x131072 quad
	galaxyRNG->SetSeedWithCoordinates(galaxySeed,16,coordinates.X,coordinates.Y);
	if (galaxyRNG->GetByteByOffset(0)<0x30)
		return 1;//star present
	return 0;//no star
}

GalaxyStarSystem* Galaxy::GetStartStarSystem()
{
	u32 i;
	f64 minDistanceSQ=1e20;
	f64 distanceSQ;
	GalaxyStarSystem* minDistanceObject=0;

	knownStarsCenter.X = 0;
	knownStarsCenter.Y = 0;
	UpdateKnownStars();//update cache of stars around (0,0)

	for (i=0;i<knownStars.size();i++)
	{
		distanceSQ = (knownStars[i]->GetGalaxyCoordinates()).getLengthSQ();//distance from (0,0)
		if (distanceSQ<minDistanceSQ)
		{
			minDistanceSQ = distanceSQ;
			minDistanceObject = knownStars[i];
		}
	}

	if (!minDistanceObject)
		minDistanceObject = knownStars[0];
	return minDistanceObject;
}

GalaxyStarSystem* Galaxy::DebugJump()
{
	/*
	//Cycle thru all knownStars, good only if this list is fixed
	debugStarCounter++;
	if (debugStarCounter>=knownStars.size())
		debugStarCounter=0;
	return knownStars[debugStarCounter];
	*/

	/*
	//Fixed-random from current coordinates to one of nearest stars
	u32 numnber;
	if (knownStars.size()==0)
		return 0;
	galaxyRNG->SetSeedWithCoordinates(galaxySeed,16,knownStarsCenter.X,knownStarsCenter.Y);
	numnber = galaxyRNG->GetByteByOffset(debugStarCounter);
	debugStarCounter++;//cycle to remove deadloop (debugjump to same system)
	return knownStars[numnber%knownStars.size()];*/

	vector2ds randomLocation;
	galaxyRNG->SetSeedWithCoordinates(galaxySeed,16,knownStarsCenter.X,knownStarsCenter.Y);
	galaxyRNG->SetOffset(777);

	for (u32 i=0;i<100;i++)
	{
		randomLocation.X = -65536 + galaxyRNG->GenerateByte();
		randomLocation.X += galaxyRNG->GenerateByte()*256;
		randomLocation.X += (galaxyRNG->GenerateByte()&1)*65536;

		randomLocation.Y = -65536 + galaxyRNG->GenerateByte();
		randomLocation.Y += galaxyRNG->GenerateByte()*256;
		randomLocation.Y += (galaxyRNG->GenerateByte()&1)*65536;

		if (CheckStarPresence(randomLocation)==1)
		{
			return SeedStar(randomLocation);
		}
	}
	return 0;

}

GalaxyStarSystem* Galaxy::SeedStar(vector2ds coordinates)
{
	u8 starSeed[16];

	//galaxyRNG is seeded with coordinates in CheckStarPresence()
	galaxyRNG->SetOffset(10);
	galaxyRNG->GenerateBytes(starSeed,16);

	//starName = L"Star ";
	//starName +=n;
	//GalaxyStarSystem* newSystem = GalaxyStarSystem::RandomStar(coordinates);
	GalaxyStarSystem* newSystem = new GalaxyStarSystem(coordinates);
	newSystem->SetSeed(starSeed,16);
	newSystem->GenerateStar();
	//newSystem->SetName(text_string(tmp));

	return newSystem;
}


void Galaxy::UpdateKnownStars()
{
	s32 x,y;
	//s32 n = 0;
	text_string starName;
	vector2ds coordinates;

	knownStars.clear();

	for (y=-10;y<10;y++)
	{
		coordinates.Y = knownStarsCenter.Y+y;
		for (x=-10;x<10;x++)
		{
			coordinates.X = knownStarsCenter.X+x;
			if (CheckStarPresence(coordinates)==1)
			{
				knownStars.push_back(SeedStar(coordinates));
			}
		}
	}
	
	//knownStars.
}

//#########################################################################
//GalaxyStarSystem

GalaxyStarSystem::GalaxyStarSystem(vector2ds quadrantCoordinates)
{
	galaxyQuadrant = quadrantCoordinates;
	starRNG = new DeterminedRandomGenerator();
}

void GalaxyStarSystem::GenerateStar()
{
	//name = "Star";

	//Very basic star name generator
	wchar_t tmp[255];

	u8 char1,char2,char3;
	u32 number;
	u32 x,y;

	char1= 65+(starRNG->GetByteByOffset(0))%26;
	char2 = 65+(starRNG->GetByteByOffset(1))%26;
	char3 = 65+(starRNG->GetByteByOffset(2))%26;

	number = starRNG->GetByteByOffset(3)+starRNG->GetByteByOffset(4)*256;
	number = number%10000;
	swprintf(tmp, 255, L"%c%c%c %04i", char1,char2,char3,number);

	name = tmp;

	x = starRNG->GetByteByOffset(20)+starRNG->GetByteByOffset(21)*256;
	y = starRNG->GetByteByOffset(22)+starRNG->GetByteByOffset(23)*256;

	galaxyCoordinates.X = galaxyQuadrant.X+x/65536.0;
	galaxyCoordinates.Y = galaxyQuadrant.Y+y/65536.0;
}

void GalaxyStarSystem::SetSeed(u8* seedData, u32 seedLen)
{
	starRNG->SetSeed(seedData,seedLen);
}

void GalaxyStarSystem::GenerateStarSystem(ResourceManager* resourceManager)
{
	//It is estimated that approximately 1/3 of the star systems in the Milky Way are binary or multiple, with the remaining 2/3 consisting of single stars.[64]
	//It is estimated that 50–60% of binary stars are capable of supporting habitable terrestrial planets within stable orbital ranges.[68]
	//Dust disk is formed: around binary is d<3 au, around each component if d>50 au

	/*
	Should be:
	1. Generation of stars - by mass-division algo
		a. Each step fills physical info about star/pair: mass, radius, luminousity, spectral class, inner and outer orbit possible
		b. If stars can't fit into outer orbit limit, corresponding pair should be replaced by one star
	2. Generation of planets and moons around stars and pairs
		a. Orbit should lie between inner and outer orbit limits of star/pair
		b. Sum of planet masses should be only small part of star/pair mass


	*/

	StarComponent *rootComponent;

	SpaceObject *root;
	u32 number;
	f64 starMass;


	//Solar system
	//Everything not to scale

	//starRNG->SetOffset(1000);
	starRNG->SetOffset(1001); //__DEBUG

	//Star size: from 0.008 to 2100 solar radii, 2.8 - 1531500 units
	//Star mass: 0.014 - 265 solar masses, 27598 - 522391320 units
	number = starRNG->GenerateByte();
	number += 256*starRNG->GenerateByte();
	starMass = exp(number*0.000201+1)*500.0;

	componentIndex = 0;
	planetIndex = 0;

	//GenerateComponent(resourceManager,starMass,LIGHTYEAR*0.05,&root);

	//root->SetMotionType(SpaceObject::MOTION_NONE);


	rootComponent = new StarComponent();

	rootComponent->type = 0;//yet is composite
	rootComponent->mass = starMass;
	rootComponent->outerOrbitLimit = LIGHTYEAR*0.05;
	rootComponent->innerOrbitLimit = 0;
	rootComponent->radius = 0;
	rootComponent->colorIndexBV = 0;
	rootComponent->subComponentsOrbit = 0;
	rootComponent->luminosity = 1;
	rootComponent->subComponentA = 0;
	rootComponent->subComponentB = 0;

	GenerateComponent2(rootComponent);

	root = FinalizeComponent(resourceManager,rootComponent);

	root->SetMotionType(SpaceObject::MOTION_NONE);



	//planet = MakeStar(planetSizes[0]*.01f);//sun is 10 times larger, compared to orbits
	//planet->SetMass(planetMass[0]);
	//planet->SetGravity(true,false);
/*
	for (s32 i=1;i<10;i++)
	{
		//planetSizes - in 6370 km
		//planetOrbits - in 150M km
		//planetPeriods - in years
		//planetMass - in 5.9736*10^24
		if (i==0)
			planet = resourceManager->MakeStar(planetSizes[i]*6.37);
		else
		{
			planet = resourceManager->MakePlanet(planetSizes[i]*6.37);//1000km in 1 unit
			planet->SetOrbitalParams(0,planetOrbits[i]*150000.0,planetPeriods[i]*365.25*86.4,i*i*20.0);//1000 seconds in 1
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
			moon = resourceManager->MakePlanet(1.74);
			moon->SetOrbitalParams(planet,384.0,2358.72,120.0);
			moon->SetMass(.0123*5.9736);
			moon->SetGravity(true,false);
			moon->SetName(L"Moon");
		}
	}*/
}

//this generates single star with orbiting planets or call itself twice to generate binary component
//sizelimit is upper limit of size for a system
void GalaxyStarSystem::GenerateComponent(ResourceManager* resourceManager, f64 mass, f64 sizeLimit, SpaceObject** rootObject)
{
	SpaceObject* star, *planet, *moon, *barycenter;

	//generating single star
	f64 starSize;
	f64 star_A_mass, star_A_orbit;
	f64 star_B_mass, star_B_orbit;
	f64 starOrbit, starOrbitPeriod, starOrbitPhase;
	f64 nextOrbit;
	f64 planetOrbit;
	f64 planetMass, planetRadius, planetOrbitPeriod,planetOrbitPhase;
	f64 moonOrbitLimit;
	f64 moonMass, moonRadius, moonOrbitRadius, moonOrbitPeriod, moonOrbitPhase;
	u32 number;
	u32 moonLimit;
	u32 i,j;

	//69% stars - single
	number = starRNG->GenerateByte();

	if (sizeLimit<140) //140 units is orbit in AM Canum Venaticorum binary system
		number = 0;//too small limit to make binary subsystem

	if (number<175)
	{
		//Single star

		//Very-very dumb star generator
		starSize = mass*0.002;

		//TODO: Get Main Sequence from Hertzsprung–Russell diagrams
		//calc luminousity distribution
		//calc mass distribution
		//make mass->luminousity interpolation formula
		//make mass->radius interpolation formula
		//generate mass, calc radius via it

		//SUN:
		//size = 190*6.37;
		//mass = 330000.0*5.9736;
		star = resourceManager->MakeStar(starSize);
		star->SetMass(mass);//in 10^24 kg
		star->SetGravity(true,false);
		//star->SetName(name);//name of star system
		{
			wchar_t tmp[255];
			swprintf(tmp, 255, L"%ws %wc", name.c_str(), 65+componentIndex);
			star->SetName(tmp);
		}
		componentIndex++;

		//DEBUG INFO
		wprintf(L" Star %ws\r\n",star->GetName());


		number = starRNG->GenerateByte();
		
		//1st planet orbit
		//nextOrbit = starSize * (30.0+number*0.3);//30 - 107

		planetOrbit = 60000 + starSize * 1.3;
		planetOrbit = planetOrbit * (0.8+number*0.0015);//k = 0.8 - 1.2

		moonOrbitLimit = planetOrbit - starSize;


		//planet generation cycle
		for (i = 1;;i++) //exit from the middle
		{
			number = starRNG->GenerateByte();

			//check breaking
			if (i==1)
			{
				if (number>=0xF0)
					break;//no planets with probab 6.25%
			}
			else if (i<5)
			{
				if (number>=0xE0)
					break;
			}
			else 
			{
				if (number>=0x80)
					break;//all next planets with probability 50% from previous one
			}

			if (planetOrbit>sizeLimit)
				break;


			//periods is stricly defined by orbit and star mass
			//p = 2*pi * a*(a/G*M)^1/2
			planetOrbitPeriod = TWO_PI * planetOrbit * sqrt(planetOrbit/(mass*G_CONSTANT));


			//OrbitPhase = epoch - totally random (unless we set up orbit resonance and so on)
			number = starRNG->GenerateByte();
			planetOrbitPhase = number * TWO_PI/256.0;

			//0.2 R of Earth - 1.8 R of Jupiter: 1.2 - 126 Mm
			number = starRNG->GenerateByte();
			planetRadius = 1.2 + number*0.49;

			moonLimit = number;//the larger the value - more moons

			//0.02 - ~1000 of Earth, 0.12 - 5973 massunits
			planetMass = 0.12 + number*23.43;//proportional to radius

			//http://en.wikipedia.org/wiki/Extrasolar_planet#Mass_distribution

			planet = resourceManager->MakePlanet(planetRadius);
			planet->SetOrbitalParams(star,planetOrbit,planetOrbitPeriod,planetOrbitPhase);//1000 seconds in 1

			{
				wchar_t tmp[255];
				swprintf(tmp, 255, L"Planet %i", i);
				planet->SetName(tmp);
			}
			planet->SetMass(planetMass);//in 10^24 kg
			planet->SetGravity(true,false);

			moonOrbitRadius = 5000 + 3*planetRadius;

			for (j=0;;j++)
			{
				if (moonOrbitRadius>moonOrbitLimit)
					break;

				number = starRNG->GenerateByte();

				if (number>moonLimit)
					break;//no (more) moon

				number = starRNG->GenerateByte();
				moonMass = (number+1)*0.000275;//0- 0.07 massunits

				moonRadius = (number+1)*0.008;//- 2 Mm
				
				moonOrbitPeriod = TWO_PI * moonOrbitRadius * sqrt(moonOrbitRadius/(planetMass*G_CONSTANT));

				//OrbitPhase = epoch - totally random (unless we set up orbit resonance and so on)
				number = starRNG->GenerateByte();
				moonOrbitPhase = number * TWO_PI/256.0;

				moon = resourceManager->MakePlanet(moonRadius);
				moon->SetOrbitalParams(planet,moonOrbitRadius,moonOrbitPeriod,moonOrbitPhase);
				moon->SetMass(.0123*5.9736);
				moon->SetGravity(true,false);
				{
					wchar_t tmp[255];
					swprintf(tmp, 255, L"Moon %i%c", i,97+j);
					moon->SetName(tmp);
				}

				number = starRNG->GenerateByte();
				moonOrbitRadius = moonOrbitRadius + 1000 + number*4;
				number = starRNG->GenerateByte();
				moonOrbitRadius = moonOrbitRadius * (1.1+number*0.001);

				
			}

			//DEBUG INFO
			wprintf(L"  Planet %i with %i moons\r\n",i,j);

			//to next orbit
			number = starRNG->GenerateByte();
			nextOrbit = planetOrbit * (1.3+number*0.0027);//1.3 - 1.99

			moonOrbitLimit = 0.5*(nextOrbit - planetOrbit);//moon orbit not more then planet inter-orbit span
			planetOrbit = nextOrbit;
		}
		*rootObject = star;
	}
	else
	{//Binary star
		number = starRNG->GenerateByte();
		star_B_mass = mass* (0.02 + number * 0.00188);//2% - 49.94% for B component; A is most massive
		star_A_mass = mass - star_B_mass;
		//star_A_size = star_A_mass *0.002;
		//star_B_size = star_B_mass *0.002;

		number = starRNG->GenerateByte();
		starOrbit = exp(0.02*number)*6000; //exp(0.02*255) =~ 164

		if (starOrbit> sizeLimit)
		{
			number = starRNG->GenerateByte();
			starOrbit = sizeLimit*(0.1+number*0.003);
		}

		//starOrbit += (star_A_size+star_B_size)*2.0;

		starOrbitPeriod = TWO_PI * starOrbit * sqrt(starOrbit/(mass*G_CONSTANT));

		star_A_orbit = starOrbit*star_B_mass/mass;
		star_B_orbit = starOrbit*star_A_mass/mass;

		//totally random
		number = starRNG->GenerateByte();
		starOrbitPhase = number * TWO_PI/256.0;

		barycenter = resourceManager->MakeBarycenter();
		barycenter->SetGravity(false,false);
		barycenter->SetName(L"barycenter");

		/*
		star = resourceManager->MakeStar(star_A_size);
		star->SetMass(star_A_mass);//in 10^24 kg
		star->SetGravity(true,false);
		star->SetName(name+L" A");//name of star system
		*/
		GenerateComponent(resourceManager,star_A_mass,star_A_orbit,&star);
		star->SetOrbitalParams(barycenter,star_A_orbit,starOrbitPeriod,starOrbitPhase);

		//DEBUG INFO
		//wprintf(L" Star %ws\r\n",star->GetName().c_str());

		/*
		star = resourceManager->MakeStar(star_B_size);
		star->SetMass(star_B_mass);//in 10^24 kg
		star->SetGravity(true,false);
		star->SetName(name+L" B");//name of star system*/
		GenerateComponent(resourceManager,star_B_mass,star_B_orbit,&star);
		star->SetOrbitalParams(barycenter,star_B_orbit,starOrbitPeriod,starOrbitPhase+TWO_PI*.5);

		//DEBUG INFO
		//wprintf(L" Star %ws\r\n",star->GetName().c_str());

		*rootObject = barycenter;

	}

}

void GalaxyStarSystem::GenerateComponent2(StarComponent *component)
{
	u32 number;
	f64 fraction, starOrbit, distanceA_H;


	for(;;)
	{
		if (component->outerOrbitLimit<140) //140 units is orbit in AM Canum Venaticorum binary system
			break;number = 0;//too small limit to make binary subsystem, so single star only

		number = starRNG->GenerateByte();

		if (number<175)
			break;//Single star, 69%

		//Binary composite
		component->type = 0;//yet composite

		number = starRNG->GenerateByte();
		fraction = (0.02 + number * 0.00188);//2% - 49.94% for B component

		component->subComponentA = new StarComponent();
		component->subComponentB = new StarComponent();

		component->subComponentA->type = 0;
		component->subComponentB->type = 0;

		component->subComponentA->mass = component->mass*(1.0-fraction);
		component->subComponentB->mass = component->mass*fraction;

		number = starRNG->GenerateByte();
		starOrbit = exp(0.02*number)*6000; //exp(0.02*255) =~ 164

		if (starOrbit>component->outerOrbitLimit)
		{
			number = starRNG->GenerateByte();
			starOrbit = 140.0+(component->outerOrbitLimit-140.0)*(number*0.0039);
		}

		//approximate location of L1 point - location of H (gravity compensation)
		distanceA_H = starOrbit/(1+sqrt(fraction/(1.0-fraction)));
		component->subComponentA->outerOrbitLimit = 0.9*distanceA_H;//90% in Roche lobe
		component->subComponentB->outerOrbitLimit = 0.9*(starOrbit-distanceA_H);//90% in Roche lobe
		component->subComponentsOrbit = starOrbit;

		component->subComponentA->innerOrbitLimit = 0;
		component->subComponentB->innerOrbitLimit = 0;
		component->subComponentA->radius = 0;
		component->subComponentB->radius = 0;

		component->subComponentA->colorIndexBV = 0;
		component->subComponentA->luminosity = 1;
		component->subComponentA->subComponentA = 0;
		component->subComponentA->subComponentB = 0;
		component->subComponentA->subComponentsOrbit = 0;
		component->subComponentB->colorIndexBV = 0;
		component->subComponentB->luminosity = 1;
		component->subComponentB->subComponentA = 0;
		component->subComponentB->subComponentB = 0;
		component->subComponentB->subComponentsOrbit = 0;

		//wprintf(L" | Composite in\r\n");

		GenerateComponent2(component->subComponentA);
		GenerateComponent2(component->subComponentB);

		//wprintf(L" | Composite out\r\n");

		if (component->subComponentA->radius > component->subComponentA->outerOrbitLimit)
			break;//component A exceed Roche lobe, prohibited
		if (component->subComponentB->radius > component->subComponentB->outerOrbitLimit)
			break;//component B exceed Roche lobe, prohibited

		component->radius = component->subComponentA->radius + component->subComponentB->radius + starOrbit;
		component->innerOrbitLimit = component->radius;

		//if (component->radius >component->outerOrbitLimit)
		//	break;//components touch each self - prohibited
		//wprintf(L" } Composite ends  %f \r\n", component->mass);

		return;//All OK - composite generated
	}

	//Single star, 69%
	component->type = 1;//main sequence YET

	//very very dumb
	component->radius = component->mass*0.002;
	component->luminosity = 1;
	component->colorIndexBV = 0;

	component->innerOrbitLimit = component->radius;
	component->subComponentA = 0;
	component->subComponentB = 0;

	//wprintf(L" * Single star %f \r\n", component->mass);
}

SpaceObject* GalaxyStarSystem::FinalizeComponent(ResourceManager* resourceManager, StarComponent *component)
{
	SpaceObject *star, *starB, *planet, *moon, *barycenter;
	SpaceObject *returnObject;

	//f64 fraction, starOrbit, distanceA_H;
	f64 star_A_orbit,star_B_orbit, starOrbitPhase,starOrbitPeriod;

	f64 planetOrbit,nextOrbit;
	f64 planetMass, planetRadius, planetOrbitPeriod,planetOrbitPhase;
	f64 planetMaxMass;
	f64 moonOrbitLimit;
	f64 moonMass, moonRadius, moonOrbitRadius, moonOrbitPeriod, moonOrbitPhase;
	u32 number;
	u32 moonLimit;
	u32 i,j;

	if (component->type==0)
	{//Composite

		wprintf(L" Composite {\r\n");

		barycenter = resourceManager->MakeBarycenter();
		barycenter->SetGravity(false,false);
		barycenter->SetName(L"barycenter");

		star = FinalizeComponent(resourceManager,component->subComponentA);
		starB = FinalizeComponent(resourceManager,component->subComponentB);

		star_A_orbit = component->subComponentsOrbit*component->subComponentB->mass/component->mass;
		star_B_orbit = component->subComponentsOrbit*component->subComponentA->mass/component->mass;

		//totally random
		number = starRNG->GenerateByte();
		starOrbitPhase = number * TWO_PI/256.0;

		starOrbitPeriod = TWO_PI * component->subComponentsOrbit * sqrt(component->subComponentsOrbit/(component->mass*G_CONSTANT));

		star->SetOrbitalParams(barycenter,star_A_orbit,starOrbitPeriod,starOrbitPhase);

		starB->SetOrbitalParams(barycenter,star_B_orbit,starOrbitPeriod,starOrbitPhase+TWO_PI*.5);

		wprintf(L" } Composite ends  %f \r\n", component->mass);
		returnObject = barycenter;
	}
	else
	{
		star = resourceManager->MakeStar(component->radius);
		star->SetMass(component->mass);//in 10^24 kg
		star->SetGravity(true,false);
		{
			wchar_t tmp[255];
			swprintf(tmp, 255, L"%ws %wc", name.c_str(), 65+componentIndex);
			star->SetName(tmp);
		}
		componentIndex++;

		wprintf(L" * Single star %f \r\n", component->mass);
		returnObject = star;
	}

	//Now generating planets and moons
	number = starRNG->GenerateByte();
	
	//1st planet orbit
	//nextOrbit = starSize * (30.0+number*0.3);//30 - 107

	planetOrbit = component->innerOrbitLimit * 2;
	//Kepler-16b have k = 3.14  (around binary Kepler-16AB)
	//WASP-12b have k = 3.14 (around WASP-12)
	//Mercury/Sun have k = 83.3

	planetOrbit = planetOrbit * (1.0+number*0.4);//k = 1.0 - 103.0

	//planet generation cycle
	for (i = 1;;) //exit from the middle
	{
		number = starRNG->GenerateByte();

		//check breaking
		if (i==1)
		{
			if (number>=0xF0)
				break;//no planets with probab 6.25%
		}
		else if (i<5)
		{
			if (number>=0xE0)
				break;
		}
		else 
		{
			if (number>=0x80)
				break;//all next planets with probability 50% from previous one
		}

		if (planetOrbit>component->outerOrbitLimit)
			break;//planet orbit may to exceed outer orbit limit for component

		//OrbitPhase = epoch - totally random (unless we set up orbit resonance and so on)
		number = starRNG->GenerateByte();
		planetOrbitPhase = number * TWO_PI/256.0;

		//STOPS here
		//PLANET MASS should be small part of host component's mass
		//2% = 1/50, while known low limit is 74 for HD 114762 b

		planetMaxMass = component->mass*0.02;

		if (planetMaxMass < 0.2)
			break;//To small star to host any planets

		//Most massive planet HD 217786 is ~13 Mjupiter, which is ~24674 massunit
		if (planetMaxMass>25000)
			planetMaxMass = 25000;
	
		number = starRNG->GenerateByte();
		
		//0.02 - ~1000 of Earth, 0.12 - 5973 massunits
		planetMass = 0.12 + number*planetMaxMass/255.0;

		//0.2 R of Earth - 1.8 R of Jupiter: 1.2 - 126 Mm
		//planetRadius = 1.2 + number*0.49;//proportional to mass

		planetRadius = 5.5*pow(planetMass,0.33) - 1.5; //very aproximate

		moonLimit = number;//the larger the value - more moons


		//May be checked only for 1st planet
		if ((planetOrbit-planetRadius)<component->innerOrbitLimit)
			goto lNextPlanet;

		if ((planetOrbit+planetRadius)>component->outerOrbitLimit)
			break;//planet orbit + size may to exceed outer orbit limit for component


		//periods is stricly defined by orbit and star mass
		//p = 2*pi * a*(a/G*M)^1/2
		planetOrbitPeriod = TWO_PI * planetOrbit * sqrt(planetOrbit/(component->mass*G_CONSTANT));


		//http://en.wikipedia.org/wiki/Extrasolar_planet#Mass_distribution

		planet = resourceManager->MakePlanet(planetRadius);
		planet->SetOrbitalParams(returnObject,planetOrbit,planetOrbitPeriod,planetOrbitPhase);//1000 seconds in 1

		{
			wchar_t tmp[255];
			planetIndex++;
			swprintf(tmp, 255, L"Planet %i", planetIndex);
			planet->SetName(tmp);
		}

		planet->SetMass(planetMass);//in 10^24 kg
		planet->SetGravity(true,false);
		i++;

		//moon orbit may not exceed inner limit for planet system
		moonOrbitLimit = planetOrbit - component->innerOrbitLimit;

		//moon orbit may not exceed outer limit for planet system
		if ((planetOrbit + moonOrbitLimit)>component->outerOrbitLimit)
			moonOrbitLimit = component->outerOrbitLimit - planetOrbit;

		moonOrbitRadius = 5000 + 3*planetRadius;

		for (j=0;;j++)
		{
			if (moonOrbitRadius>moonOrbitLimit)
				break;

			number = starRNG->GenerateByte();

			if (number>moonLimit)
				break;//no (more) moon

			number = starRNG->GenerateByte();
			moonMass = (number+1)*0.000275;//0- 0.07 massunits

			moonRadius = (number+1)*0.008;//- 2 Mm

			if ((moonOrbitRadius+moonRadius) >moonOrbitLimit)
				break;//moon orbit + size exceed moon orbit limit
			
			moonOrbitPeriod = TWO_PI * moonOrbitRadius * sqrt(moonOrbitRadius/(planetMass*G_CONSTANT));

			//OrbitPhase = epoch - totally random (unless we set up orbit resonance and so on)
			number = starRNG->GenerateByte();
			moonOrbitPhase = number * TWO_PI/256.0;

			moon = resourceManager->MakePlanet(moonRadius);
			moon->SetOrbitalParams(planet,moonOrbitRadius,moonOrbitPeriod,moonOrbitPhase);
			moon->SetMass(.0123*5.9736);
			moon->SetGravity(true,false);
			{
				wchar_t tmp[255];
				swprintf(tmp, 255, L"Moon %i%c", planetIndex,97+j);
				moon->SetName(tmp);
			}

			number = starRNG->GenerateByte();
			moonOrbitRadius = moonOrbitRadius + 1000 + number*4;
			number = starRNG->GenerateByte();
			moonOrbitRadius = moonOrbitRadius * (1.1+number*0.001);

			
		}

		//DEBUG INFO
		wprintf(L"  %s with %i moons\r\n",planet->GetName().c_str(),j);

lNextPlanet:
		//to next orbit
		number = starRNG->GenerateByte();
		nextOrbit = planetOrbit * (1.3+number*0.0027);//1.3 - 1.99

		moonOrbitLimit = 0.5*(nextOrbit - planetOrbit);//moon orbit not more then planet inter-orbit span
		planetOrbit = nextOrbit;
	}

	return returnObject;
}


//#########################################################################
//SHA-1 - SHA-1 crypto hash

template <class T> inline T rotlFixed(T x, unsigned int y)
{
    assert(y < sizeof(T)*8);
    //if(y < sizeof(T)*8);
    return (x<<y) | (x>>(sizeof(T)*8-y));
}


// start of Steve Reid's code

#define blk0(i) (W[i] = data[i])
#define blk1(i) (W[i&15] = rotlFixed(W[(i+13)&15]^W[(i+8)&15]^W[(i+2)&15]^W[i&15],1))

#define f1(x,y,z) (z^(x&(y^z)))
#define f2(x,y,z) (x^y^z)
#define f3(x,y,z) ((x&y)|(z&(x|y)))
#define f4(x,y,z) (x^y^z)

/* (R0+R1), R2, R3, R4 are the different operations used in SHA1 */
#define R0(v,w,x,y,z,i) z+=f1(w,x,y)+blk0(i)+0x5A827999+rotlFixed(v,5);w=rotlFixed(w,30);
#define R1(v,w,x,y,z,i) z+=f1(w,x,y)+blk1(i)+0x5A827999+rotlFixed(v,5);w=rotlFixed(w,30);
#define R2(v,w,x,y,z,i) z+=f2(w,x,y)+blk1(i)+0x6ED9EBA1+rotlFixed(v,5);w=rotlFixed(w,30);
#define R3(v,w,x,y,z,i) z+=f3(w,x,y)+blk1(i)+0x8F1BBCDC+rotlFixed(v,5);w=rotlFixed(w,30);
#define R4(v,w,x,y,z,i) z+=f4(w,x,y)+blk1(i)+0xCA62C1D6+rotlFixed(v,5);w=rotlFixed(w,30);

//64 bytes
void SHA1::TransformBlock(u32* data)
{
    register u32 W[16];//={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    /* Copy context->state[] to working vars */
    register u32 a = state[0];
    register u32 b = state[1];
    register u32 c = state[2];
    register u32 d = state[3];
    register u32 e = state[4];
    /* 4 rounds of 20 operations each. Loop unrolled. */
    R0(a,b,c,d,e, 0); R0(e,a,b,c,d, 1); R0(d,e,a,b,c, 2); R0(c,d,e,a,b, 3);
    R0(b,c,d,e,a, 4); R0(a,b,c,d,e, 5); R0(e,a,b,c,d, 6); R0(d,e,a,b,c, 7);
    R0(c,d,e,a,b, 8); R0(b,c,d,e,a, 9); R0(a,b,c,d,e,10); R0(e,a,b,c,d,11);
    R0(d,e,a,b,c,12); R0(c,d,e,a,b,13); R0(b,c,d,e,a,14); R0(a,b,c,d,e,15);
    R1(e,a,b,c,d,16); R1(d,e,a,b,c,17); R1(c,d,e,a,b,18); R1(b,c,d,e,a,19);
    R2(a,b,c,d,e,20); R2(e,a,b,c,d,21); R2(d,e,a,b,c,22); R2(c,d,e,a,b,23);
    R2(b,c,d,e,a,24); R2(a,b,c,d,e,25); R2(e,a,b,c,d,26); R2(d,e,a,b,c,27);
    R2(c,d,e,a,b,28); R2(b,c,d,e,a,29); R2(a,b,c,d,e,30); R2(e,a,b,c,d,31);
    R2(d,e,a,b,c,32); R2(c,d,e,a,b,33); R2(b,c,d,e,a,34); R2(a,b,c,d,e,35);
    R2(e,a,b,c,d,36); R2(d,e,a,b,c,37); R2(c,d,e,a,b,38); R2(b,c,d,e,a,39);
    R3(a,b,c,d,e,40); R3(e,a,b,c,d,41); R3(d,e,a,b,c,42); R3(c,d,e,a,b,43);
    R3(b,c,d,e,a,44); R3(a,b,c,d,e,45); R3(e,a,b,c,d,46); R3(d,e,a,b,c,47);
    R3(c,d,e,a,b,48); R3(b,c,d,e,a,49); R3(a,b,c,d,e,50); R3(e,a,b,c,d,51);
    R3(d,e,a,b,c,52); R3(c,d,e,a,b,53); R3(b,c,d,e,a,54); R3(a,b,c,d,e,55);
    R3(e,a,b,c,d,56); R3(d,e,a,b,c,57); R3(c,d,e,a,b,58); R3(b,c,d,e,a,59);
    R4(a,b,c,d,e,60); R4(e,a,b,c,d,61); R4(d,e,a,b,c,62); R4(c,d,e,a,b,63);
    R4(b,c,d,e,a,64); R4(a,b,c,d,e,65); R4(e,a,b,c,d,66); R4(d,e,a,b,c,67);
    R4(c,d,e,a,b,68); R4(b,c,d,e,a,69); R4(a,b,c,d,e,70); R4(e,a,b,c,d,71);
    R4(d,e,a,b,c,72); R4(c,d,e,a,b,73); R4(b,c,d,e,a,74); R4(a,b,c,d,e,75);
    R4(e,a,b,c,d,76); R4(d,e,a,b,c,77); R4(c,d,e,a,b,78); R4(b,c,d,e,a,79);
    /* Add the working vars back into context.state[] */
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    /* Wipe variables */
    a = b = c = d = e = 0;
    //  memset(W, 0, sizeof(W));
}

// end of Steve Reid's code


//Default constructor
SHA1::SHA1()
{
	Reset();
}

//Reset hasher to start
void SHA1::Reset()
{
    state[0] = 0x67452301L;
    state[1] = 0xEFCDAB89L;
    state[2] = 0x98BADCFEL;
    state[3] = 0x10325476L;
    state[4] = 0xC3D2E1F0L;
	status = HASHER_RESET;
	processedBytes = 0;
}

u32 SHA1::ProcessArrayFinal(u8* data, u32 dataLen)
{
	u32 buffer[32];
	u32 i,j,dlen2,dlen3;
	u32 * data32=(u32*)data;
	u8 * buffer_c=(u8*)buffer;
	u8 * data2=(u8*)(buffer+16);
	//u32 fulllen;

	if (status==HASHER_FINISHED)
		return 1;//error, hasher is finished

	dlen3 = dataLen & 63;

	dlen2 = 0xFFFFFFC0 & dataLen;

	for (i=0;i<dlen2;i+=64)//do it as long as full 512-bit bloks exists
	{
		for (j=0;j<64;j+=4)
		{
			//Revert endians
			buffer_c[j]=data[i+j+3];
			buffer_c[j+1]=data[i+j+2];
			buffer_c[j+2]=data[i+j+1];
			buffer_c[j+3]=data[i+j];
		}
		TransformBlock(buffer);
	}

	processedBytes += dataLen;

	//last data and padding
	memset(data2,0,64);
	memcpy(data2,data+dlen2,dlen3);
	data2[dlen3]=0x80;//bit 1

	for (j=0;j<64;j+=4)
	{
		buffer_c[j]=data2[j+3];
		buffer_c[j+1]=data2[j+2];
		buffer_c[j+2]=data2[j+1];
		buffer_c[j+3]=data2[j];
	}

	if (dlen3>=56)
	{//one more block needed
		//pad block - zeros
		TransformBlock(buffer);
		memset(buffer,0,64);
	}

	//pad block - put len of original message in bits
	buffer[14]=processedBytes>>29;
	buffer[15]=processedBytes<<3;
	TransformBlock(buffer);
	status = HASHER_FINISHED;
	return 0;
}

u32 SHA1::WriteHash(u8* outputData)
{
	u8* hash_c=(u8*)state;
	u32 j;

	for (j=0;j<20;j+=4)
	{
		outputData[j+3]=hash_c[j];
		outputData[j+2]=hash_c[j+1];
		outputData[j+1]=hash_c[j+2];
		outputData[j+0]=hash_c[j+3];
	}

	if (status!=HASHER_FINISHED)
		return 2;//internal status is returned, as hasher is not finished
	return 0;//all OK
}

//#########################################################################
//DeterminedRandomGenerator

DeterminedRandomGenerator::DeterminedRandomGenerator()
{
	hasher = new SHA1();
	offset = -1;
	blockOffset = -1;
	memset(hashBuffer,0,bufferLength);
	//SetSeed(0,0);
	SetOffset(0);
}

//up to 32 bytes, zero-padded at the end
void DeterminedRandomGenerator::SetSeed(u8* newSeed, u32 seedLen)
{
	if (seedLen>seedLength)
		seedLen = seedLength;
	memset(hashBuffer,0,seedLength);
	if (seedLen>0)
		memcpy(hashBuffer,newSeed,seedLen);
	blockOffset = -1;//invalidate block
	GenerateBlock();
}

void DeterminedRandomGenerator::SetSeedWithCoordinates(u8* newSeed, u32 seedLen, u32 x, u32 y)
{
	if ((seedLen+8)>seedLength)
		seedLen = seedLength-8;
	memset(hashBuffer,0,bufferLength);
	if (seedLen>0)
		memcpy(hashBuffer,newSeed,seedLen);
	memcpy(hashBuffer+seedLength-8,&x,4);
	memcpy(hashBuffer+seedLength-4,&y,4);
	blockOffset = -1;//invalidate block
	GenerateBlock();

}

//return 32 bytes
void DeterminedRandomGenerator::GetSeed(u8* buffer)
{
	memcpy(buffer,hashBuffer,seedLength);
}

void DeterminedRandomGenerator::SetOffset(u32 newOffset)
{
	offset = newOffset;
	GenerateBlock();
}

//return 1 random byte and shifts offset to next
u8 DeterminedRandomGenerator::GenerateByte()
{
	u8 rValue;
	GenerateBlock();
	rValue = block[offset-blockOffset];
	offset++;
	return rValue;
}

//return 1 byte by offset and shifts offset to next
u8 DeterminedRandomGenerator::GetByteByOffset(u32 byteOffset)
{
	SetOffset(byteOffset);
	return GenerateByte();
}


//write <len> bytes and shifts offset
void DeterminedRandomGenerator::GenerateBytes(u8* destination, u32 len)
{
	u32 i;
	for (i=0;i<len;i++)
	{	//NOT OPTIMIZED
		GenerateBlock();
		destination[i]=block[offset-blockOffset];
		offset++;
	}
}


//check new offset, if it is outside current block - generate new block
void DeterminedRandomGenerator::GenerateBlock()
{
	u32 newOffset = offset & 0xFFFFFFF0;
	if (newOffset != blockOffset)
	{
		blockOffset = newOffset;
		memcpy(hashBuffer+seedLength,&blockOffset,4);
		hasher->Reset();
		hasher->ProcessArrayFinal(hashBuffer,36);
		hasher->WriteHash(block);
	}
}

//#########################################################################
//UndeterminedRandomGenerator

UndeterminedRandomGenerator::UndeterminedRandomGenerator()
{
	hasher = new SHA1();
	offset = 0;
	memset(hashBuffer,0,bufferLength);//clean, as compiler would not like leaving buffer with untouched memory content
	GenerateBlock();
}

void UndeterminedRandomGenerator::AddSeed(u8* newSeed, u32 seedLen)
{
	u32 bufferStep = bufferLength - blockLength;
	u32 copyLen;
	for(u32 i=0;i<seedLen;i+=bufferStep)
	{
		copyLen = seedLen-i;
		if (copyLen>bufferStep) 
			copyLen=bufferStep;
		memcpy(hashBuffer+blockLength,newSeed+i,copyLen);
		RehashBlock();
	}
}

//return 1 random byte
u8 UndeterminedRandomGenerator::GenerateByte()
{
	offset++;
	if (offset>=blockLength)
		GenerateBlock();
	return hashBuffer[offset];
}

//write <len> bytes 
void UndeterminedRandomGenerator::GenerateBytes(u8* destination, u32 len)
{
}

void UndeterminedRandomGenerator::GenerateBlock()
{
	u32 pos;
	u64 systemTime;
	u32 systemRandom = rand();
	u64 memoryAddress;

	// random sources:
	//  0-15  prev random [16]
	// 16-23  counter [8]
	// 24-31  time [8]
	// 32-35  systemRandom [4]
	// 36-43  address of time variable [8]

	counter++;
	pos = blockLength;
	memcpy(hashBuffer+pos,&counter,8);pos+=8;

	systemTime = (u64)time(0);
	memcpy(hashBuffer+pos,&systemTime,8);pos+=8;

	memcpy(hashBuffer+pos,&systemRandom,4);pos+=4;

	memoryAddress = (u64)&systemTime;
	memcpy(hashBuffer+pos,&memoryAddress,8);pos+=8;

	RehashBlock();

}

void UndeterminedRandomGenerator::RehashBlock()
{
	//hash all
	hasher->Reset();
	hasher->ProcessArrayFinal(hashBuffer,bufferLength);
	hasher->WriteHash(hashBuffer);
	offset = 0;
}

//#########################################################################
//main()

int main(int ArgumentCount, char **Arguments) {

	DeterminedRandomGenerator* pRNG = new DeterminedRandomGenerator();
	//UndeterminedRandomGenerator* pRNG = new UndeterminedRandomGenerator();
	u8 test[32];

	for (u32 i=0;i<32;i++)
		test[i]=11;
	pRNG->SetSeedWithCoordinates(test,32,1,1);

	printf("seed (1,1) from 0 v1:");
	for (u32 i=0;i<100;i++)
		printf("%02X",pRNG->GenerateByte());
	printf("\r\n");

	//pRNG->SetOffset(3);
	pRNG->SetSeedWithCoordinates(test,32,1,2);

	printf("seed (1,2) from 3 v2:");
	for (u32 i=0;i<100;i++)
		printf("%02X",pRNG->GetByteByOffset(i+3));
		//printf("%02X",pRNG->GenerateByte());
	printf("\r\n");


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

