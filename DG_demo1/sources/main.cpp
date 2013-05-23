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


DangerGalaxy currently uses some textures from M.A.R.S. - a ridiculous Shooter,
which are under CC-BY-3.0 license.

"Textures:
 - all textures are created with Blender (http://www.blender.org)
   and Gimp (http://www.gimp.org)
 - they are released under the Creative Commons Attribution 3.0
   by (C) 2010 Simon Schneegans and Felix Lauer
   (http://creativecommons.org/licenses/by/3.0/)"

This refers to ships.png and starfield_1_medium.jpg


Other textures and meshes are Copyright © 2011 OverQuantum,
And is licensed under the Creative Commons Attribution-ShareAlike 3.0 Unported License.
To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/3.0/ or send a
letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


Some of meshes are created with Blender and irrb.


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
110615: ADD: pseudo-relativistic effect after 0.8c, speed=c could not be achived
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
110929: CHG: debug jump around whole galaxy
110930: CHG: galaxy is now have circular form and fading density of stars
110930: CHG: intergalactic stars added
110930: CHG: star presence check upgraded (for multybyte random)
101001: FIX: zoom speed is now FPS-independent
111001: FIX: UndeterminedRandomGenerator::GenerateBytes
111001: CHG: stellar density field (+ debug dump)
111001: ADD: galaxy radius and density in core is randomized from galaxy seed
111001: ADD: star count estimation
111003: FIX: lightspeed limit improved, more physical, from 0.5c
111005: REM: GoInterstellar on AcviateView REAL_SPACE
111005: CHG: Interstellar is now have center in (x+0.5,y+0.5) by galaxy coordinates (i.e. not exit point from star system as before)
111005: ADD: Interstellar center is updated each time player change quadrant
111005: ADD: Center of map to player
111005: ADD: Pan of map - W/A/S/D
111005: CHG: dump of stellar density field to BMP
111008: ADD: sizes of objects on map (lead to escaping of labels)
111008: CHG: labels on map now below marker
111008: FIX: scenenode remains after jump to FTL (GoInterstellar was not called)
111008: ADD: galaxy texture on map, fades on star-system scale
111009: ADD: spiral galaxy (still testing)
111009: FIX: u64 for non-Windows
111009: ADD: 1000fps limit
111009: ADD: huge zooms of RealSpace (up to 1 ly)
111009: ADD: Determined generator test
111009: FIX: galaxy texture balanced creation (from density)
111009: ADD: nice spiral arms
111011: ADD: generation of spiral and elliptical galaxies done (very very smooth, no clusterization)
111011: CHG: start system is now on the edge of galaxy
111011: CHG: planet and moon naming changed to ~ Hessman et al 2010 proposal (http://arxiv.org/abs/1012.0707)
111011: ADD: PlusMinus Engine (currenly dummy, goes by x axis)
111012: ADD: PlusMinus Engine by correct curve
111013: ADD: Singleton GlobalURNG
111013: ADD: Third option of PlusMinus Engine (by gray '*' key)
111013: FIX: Added check PlusMinus Engine for galaxy grid
111013: CHG: PlusMinus Engine manual exit disabled
111013: CHG: planet and moon naming changed back to my own
111013: FIX: Moon orbit better limited by planet orbits
111013: CHG: Switch to star system on exit from PlusMinus moved into UpdateQuasiSpace
111013: FIX: Leaving star system moved from 0.1 to 0.101 ly from center (to make hysteresis)
111013: CHG: Start is now 0.07 ly from star system center
111014: FIX: PlusMinus now use quadrant of star system, if player is not interstellar
111014: CHG: FindRandomLocationWithSpecificGravity
111015: FIX: unused variables, moonMass
111019: CHG: added yield() for lowering CPU load
111019: ADD: slow first jumps on PlusMinus and fast later
111021: exp: FindRandomLocationWithSpecificXGravity

111107: CHG: PlusMinus works by XGravity (-36..-35)
111109: CHG: switch to star3 texture 
111109: ADD: minor logging at start
111109: ADD: very basic wormholes (visible only)
111110: CHG: SpaceObject int properties organized into array
111114: CHG: RealSpaceView.playerThrust replaced by PlayerShip.controlThrust
111114: ADD: Basic wormholes - works, but no nice network yet (for all starsystems in +-5 ly quad)
111114: CHG: PlusMinus fast calc limited by FPS
111115: FIX: SpaceObject.rotation is now in radians
111117: CHG: Wormhole4.irrmesh
111117: CHG: Wormhole radius to 50, effective to *0.7
111117: CHG: camera near and far low-limited for RealSpace
111120: ADD: saving and loading (time and ship position only)
111120: ADD: checking for wormholes to be too close
111120: ADD: handling of one-way wormholes
111123: FIX: removed memory leaks "new() and not delete" (+ one from Irrlicht, but by workaround)
111124: FIX: unlock before lock for needed system
111124: CHG: wormholes generation moved to galaxy's method (still very easy)
111124: ADD: show wormhole links (currently shifted from stars)
111125: FIX: wormhole links are now not shifted from stars
111127: CHG: thrust mesh updated, texture replaced by my own
111127: CHG: planet texture replaced by my own
111127: CHG: moderate wormhole net generation algorithm - by wave algorithm
111127: DBG: debug teleport to random wormhole and wormhole, close to player ship direction
111128: ADD: grid on map (including mesh and texture)
111128: FIX: unnecessary star systems were included in 10x10 l.y. quad for wormhole generation
111129: CHG: simple text is available for all views
111129: ADD: display grid size on map
111129: ADD: zoom in/out with big steps
111129: ADD: debug view wormhole network for +-100 l.y. quad
111201: ADD: stargate in system (it does nothing yet)
111201: ADD: basic mesh for stargate and its event horizon (+textures)
111201: ADD: linked motion type (object follow other object as hard-linked to position and rotation)
111202: ADD: galaxy coords<->stargate address basic converter (no encryption yet)
111203: ADD: visibility property is handled
111203: ADD: SpaceObject float properties array (not all props organized)
111203: ADD: SpaceObject process mechanism
111203: ADD: Stargate opening, waiting and closing processes
111203: ADD: stargate travel by typing address
111204: CHG: SpaceObject float properties organized into array
111204: FIX: collision with moving output stargate
111204: ADD: checks: stargate too far, stargate busy
111204: ADD: scanning space (it prints address of stargate if found)
111205: ADD: fp_mulmod and fp_powmod (for low-len RSA)
111206: ADD: stargate address<->coord encryption
111207: FIX: _wtoi64 replaced by stoi64
111208: ADD: stargate address<->text conversion functions (currently use hex 3:3:3 format)
111208: ADD: typing letters A-F
111208: FIX: change direction of player ship after passing stargate

120111: ADD: mousewheel to control zoom (RealSpace and Map)
120111: CHG: autopilot breaking and orbiting is now in autopilot queue
120112: ADD: mousewheel zoom on map is now centred on mouse
120112: ADD: autopilot rotating
120113: ADD: autopilot fly-to (not very nice in strong grav field)
120114: CHG: switch view is now by current status of playership
120114: ADD: autopilot FTL jump by mouse click, including map
120114: CHG: FTL is now have remaining-time
120114: ADD: autopilot fly-to by mouse click on map
120114: ADD: display ETA for fly-to autopilot
120114: ADD: text info for FTL
120114: ADD: display FTL remaining time
120114: ADD: timespeed control on FTL 
120116: ADD: marker of autopilot target
120117: ADD: deletion of objects
120117: ADD: show autopilot destination
120118: FIX: autopilot fly-to better deceleration
120119: ADD: autopilot go-to-orbit-at-that-point (rather rough)
120120: CHG: prolong stargate open on object falling
120120: ADD: removing projectiles by timer
120120: CHG: better collision calculation with wormholes and stargates
120120: CHG: stargate event horizon now created and destroyed
120120: CHG: SpaceObjects all arrayed properties default init to 0
120121: FIX: stargate duplicate open removed
120122: ADD: wormhole opening on approach and closing on departure of objects
120122: ADD: HyperSpace (works, but completely empty)
120123: ADD: stars grav-wells in HyperSpace
120123: ADD: GFX in FTL (not very nice at high timespeed)
120124: CHG: better GFX in FTL
120125: ADD: scaner in HyperSpace
120125: ADD: twirl of speed in HyperSpace, with high relativistic effec
120125: CHG: recalc star on moving in HyperSpace, zoom limited
120125: CHG: conversion pixel->physics coordinates is subroutined
120125: ADD: autopilot in HyperSpace (timer-ed)
120128: ADD: forcefield on FTL (by decal only)
120128: ADD: forcefield in QuasiSpace (by decal only)
120128: FIX: object left in interstellar space are now moves correctly on change quadrant (+autopilot breaked)
120130: ADD: distorted relation btw RealSpace and HyperSpace
120130: ADD: distorted relation of HyperSpace is mixed with encryption-like sbox
120131: CHG: HyperSpace twirl depends on coordinates only
120201: ADD: HyperSpace "fog" limits star visibility to ~6 l.y.
120201: ADD: locations of planets seen from HyperSpace

120403: FIX: StargateAddress2text for Linux

130520: FIX: abs->fabs for Linux
130520: FIX: collision on stargate eventhorizon restored
130520: ADD: R for breaking speed
130523: FIX: cmath

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
+ zoom map around arbitrary point, starting with ship
+ galaxy map
+ galaxy-wide physics checker
+ camera further from system, than 4M (degree=4000)
+ fix enter/leaving star system with hysteresis
+ move playerThrust to another class (or not reset in Init() )
+ add fixed delay on fastest star search (PlusMinus)
+ advanced mesh - visible from a far (wormhole)
+ too close wormholes - shift them to diff locations
+ no wormhole at destination
+ FIX BUG: memory leak somewhere on star system generation or exiting/entering
+ visualization of wormhole links
+ debug teleport to wormhole
+ some triangulation for building wormhole net
+ FIX BUG: player galaxy coordinates in star system (used for wormholes e.t.c) should be quadrant-sticked
+ map grid
+ print map grid size
+ stargate system : generation of stargate in star system
+ stargate system : basic mesh
+ stargate system : typing destination address
+ stargate system : opening and closing
+ stargate system : jumping
+ organize float properties of spaceobject
+ stargate system : limit distance of signaling  
+ stargate system : getting address
+ stargate system : address<->coord encryption
+ use mouse pointer to center on mouse-wheel zoom on map
+ autopiloting: autopliot fly-to by mouse click
+ autopliot FTL jump to mouse targeting
+ autopilot fly-to by map click
+ show autopilot destination (on RealSpace and on map)
+ autopilot go-to-orbit-at-that-point
+ stargate system : "killing" non-player objects
+ wormhole network : "killing" non-player objects
+ wormhole network : opening on approaching mass and closing - by process
+ FTL nice graphic (flow algorithm)
+ HyperSpace : location of stars
+ HyperSpace : scaner to recognize stars
+ HyperSpace : limit zoom
+ HyperSpace : twirl - drift of speed angle (+increase of drift on near-lightspeed)
+ HyperSpace : recalc stars on moving thru Galaxy
+ HyperSpace : timer-autopilot
+ FIX BUG: projectiles left in interstellar space are flying strange
+ HyperSpace : distorted relation to RealSpace
+ HyperSpace : twirl depends on coordinates only (not combined with distorted relation)


TODO:

* MAIN PLAN
- BUG: something wrong on Linux with angle on autopilot stop and orbiting ( .normalize() ??)
- HyperSpace
  + location of planets (just location "gravity well" or so) (need remade of starsystemgenerator)
  + "fog" (to limit visible stars not by rectangle screen)
  - approx map(?)
  - entering and exiting by hypergate/jumpsphere/etc
  - randomize distortion with RealSpace in interstellar
  - nice graphic for background (2D flow algorithm ?)
  - twirl depends on star density?
  - in-HyperSpace quick-living objects (slowdown or speedup player; pull/push by gravity-like force e.t.c.)
  - what should be in intergalactic HyperSpace - obstacle or very plain?
- FTL
  - better forcefield (a bit opaque, may be reflections)
- weapons
  - hit objects
- stargate system
  - better mesh and textures
  - defence force-field around gate object
- wormhole network
  .? advanced triangulation for building wormhole net
- map
  - show stars on other locations in galaxy
  ? grid in metres for detailed zooms
- save & load
  + global position and speed
  . rotation, thrust
  . object statuses
- setup more in meshes, less in code
- BUG/FEATURE: something wrong with device->yield() - cause 65 fps in case of NOT LAUNCHED R&Q



* Star system generation
- HR and so on
- planet rotation around it's axis
- corona of star and atmosphere of planets by decal/billboard/etc
- Option for planet naming by Hessman 2010 proposal



* FTL
- going/exiting FTL cannot happens in vicinity of big object, regardless of gravity
- destruction of objects around ship on going/exiting FTL
- moving of some background at FTL
- showing map for FTL travel (marker of autopilot will not be shown?)


* RealSpace
- display more info about orbit - shape, min/max distance (with fall estimation), period
- HUD
- messages on main screen
- thrust flame as sub-object to SpaceObject
- auto-zoom camera - to show ship and nearest object
- somthing to display then ship inside stars (?)
- better speed indicator
- exponential fading of light sources (?)


* PlusMinus
- Entering to system after PlusMinus Engine - check for gravity at all



* Map
m remove overlapping of labels on map (how?)

* Physic
? orbiting of gravity-domination body by orbital parameters, not simple euler
?m change check of vector length to bounding-box - max(X,Y,Z)  - ex. for radius of star system and so on



* Logic
-2 Recheck all chains of creationg physical objects, scene nodes and map objects - FTL/back, entering/leaving star sytems and so on
-3SpaceShip - derivative to SpaceObject with virtual UpdatePhysics() and so on
- autopilot to travel to specific point
- handling of errors
- consider vsynch
- shift autopilot objectives on change interstellar quadrant (instead of removing them at all)
m option to turnoff yield
m multithreading protection (for GlobalURNG)


* Hashing
- SHA1 - unfinalized hashing, incomplete bytes

* License
m check SHA1 code for license




QUESTIONS
- how display map-info above map - gui or adjust billboard?
- limit FPS and calc physics to 200/100/?
- how to draw ship passing stars and planets?  [thinking: collision]
- time game koefficient (to pass star system in a matter of minutes/seconds) [current: 1000]
- size game koefficient (planet size in a relation to its orbits) [current: NO]
- size game logarithm (from hypergians stars to small moons/asteroids should be seen)   [current: NO]
- PI, G and other constant - where they should hold?


CONTROL on RealSpace main:
A/D - rotate
W/S - thrust
1/2/3/4/5/6 - different thrust levels (1 - highest, 6 - lowest)
Space - fire weapon (plasma ball)
R - breaking (autopilot) relative to distant stars
O - orbiting (around object which produce max graviry force at player's ship)
ESC - stop autopilot
Up/Down - zoom
MouseWheel - zoom
Tab - switch to map
F - jump to FTL (FTL works only if gravity < -5.75 dgr)
F1/F2/F3/F4/F5/F6 - different time speed (1 - 1.0, 2 - 10, ... 6 - 100k)
+/-/* - activate PlusMinus Engine (* - third option)
L - load saved game
K - save game
Y - type and send stargate address
T - scan space (to get stargate address and so on)
MouseClick Left - autopilot fly-to
MouseClick Right - autopilot FTL-to
MouseClick Middle - autopilot fly-to-orbit
X - (DEBUG) dump galaxy coordinates into log
H - jump to HyperSpace

CONTROL on map:
W/A/S/D - pan
Up/Down - zoom
MouseWheel - zoom, center on mouse
PgUp/PgDn - zoom in/out by big steps
MouseClick Left - autopilot fly-to
MouseClick Right - autopilot FTL-to (started after closing map)
MouseClick Middle - autopilot fly-to-orbit
Esc - back to RealSpace

CONTROL on FTL:
F1/F2/F3/F4/F5/F6 - different time speed (1 - 1.0, 2 - 10, ... 6 - 100k)
Esc - drop out to RealSpace
X - (DEBUG) dump galaxy coordinates into log

CONTROL on QuasiSpace (PlusMinus):
X - (DEBUG) dump PlusMinus debug info into log

CONTROL on HyperSpace
H - jump back to RealSpace
A/D - rotate
W/S - thrust
1/2/3/4/5/6 - different thrust levels (1 - highest, 6 - lowest)
Space - breaking (autopilot) relative to distant stars
ESC - stop autopilot
Up/Down - zoom
MouseWheel - zoom
F1/F2/F3/F4/F5/F6 - different time speed (1 - 1.0, 2 - 10, ... 6 - 100k)
T - scan space (to identify near star)
MouseClick Left - autopilot fly-to



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
#include <cmath>

using namespace irr;


//defines
#define RESOURCE_PATH	"media"

//Geometry
#define TWO_PI 6.2831853
#define RADTODEG64 (irr::core::RADTODEG64)

//Distances is in 1000 km, so k=10^6  
//Time is in 1000 seconds - k=1000
//Mass is in 10^24 kg - k=10^24

//Gravitational constant
//G = 6.67384(80)*10^-11 N * (m/kg)^2 = .. [m*m*m/kg*s^2]
//Ggame = G * 10^-18/(10^-24 * 10^-6) = G * 10^12 = 66.7384
#define G_CONSTANT 66.7384

//Speed of light in vacuum, c
#define LIGHTSPEED 300000.0

//Light-year, exact value
#define LIGHTYEAR 9460730472.5808

//How much distances in HyperSpace smaller than in RealSpace
#define HYPERSPACE_SCALE 50000.0

//Radius of star system in light-years (used for enter star system check, for limit orbits of planets and so on)
#define STAR_SYSTEM_RADIUS 0.1
//and this one only for checking leaving
#define STAR_SYSTEM_RADIUS_LEAVE 0.101

//Density of stars outside galaxy outer radius
//Value 1.5e-7 gives ~2600 stars in whole galaxy quad and ~1000 stars outside r=57000 ly
#define INTERGALACTIC_STARS_DENSITY 1.5e-7

//Maximum time between frames, in seconds
//Limits low FPS and slowdowns game if lower
//0.02 gives 50 fps
#define FRAME_TIME_MAX 0.02

//Maximum x-gravity for PlusMinus
#define XGRAVITY_MAX_PLUSMINUS -35


#define KEY_PSEUDO_MOUSEWHEELUP 0xD0
#define KEY_PSEUDO_MOUSEWHEELDOWN 0xD1
//#define FRAME_TIME_MIN 0.001


//types
typedef core::stringw   text_string;

#ifdef _MSC_VER
typedef unsigned __int64	u64;
#else
#include <stdint.h>
typedef uint64_t u64;
#endif

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

//Multiply two numbers modulus 3rd
// [ Result = number1*number2 mod modulus ] 
//Calculation proceed via standart doubling-and-adding technique
//number2 = SUMM {s[i]*(2^i)} => number1*number2 = SUMM {s[i]*Dst*(2^i)} (mod modulus)
u64 fp_mulmod(u64 number1, u64 number2, u64 modulus)
{
	u64 checkBit=1;//for checking bits
	u64 number2mult=number2;//number2*2^0
	u64 result=0;
	for (u32 i=0;i<64;i++)
	{
		if ((number1&checkBit)!=0)//check i-th bit of number1
		{
			result+=number2mult;//add number2*2^i
			if (result>=modulus) result-=modulus;//reduce if needed
		}
		else if (number1<checkBit)
		{
			break;//break if there is no more bits
		}
		checkBit<<=1;//shift checking bit
		number2mult<<=1;//mul by 2
		if (number2mult>=modulus) number2mult-=modulus;//and reduce if needed
	}
	return result;
}

//Power number modulus
// [ Result = number^power mod modulus ]
//Calculation proceed via standart squaring-and-multiplying technique
//power = SUMM {s[i]*(2^i)} => number^power = PROD {s[i]*number^(2^i)} (mod modulus)
u64 fp_powmod(u64 number, u64 power, u64 modulus)
{
	u64 checkBit=1;//for checking bits
	u64 numberPow=number;

	//initial set
	u64 result=1;
	if ((power&checkBit)!=0)
		result = number;

	for (u32 i=1;i<64;i++)
	{
		numberPow = fp_mulmod(numberPow,numberPow,modulus);//square
		checkBit<<=1;//shift checking bit
		if ((power&checkBit)!=0)//check bit
		{
			result = fp_mulmod(result,numberPow,modulus);//mul by number^(2^i)
		}
		else if (power<checkBit)
		{
			break;//break if there is no more bits
		}
	}
	return result;
}

u64 stoi64(text_string string)
{
	u64 result=0;
	const wchar_t* string_w = string.c_str();
	u32 i,len = string.size();
	for(i=0;i<len;i++)
		if (string_w[i]>=L'0' && string_w[i]<=L'9')
		{
			result*=10;
			result+=string_w[i]-L'0';
		}
	return result;
}

//#########################################################################
//classes

class MyEventReceiver;
class ReferenceCounted;
class GravityInfo;
class WormholeInfo;
class SpaceObject;
class GamePhysics;
//class StarSystemConstructor;
class DG_Game;
class GameView;
class RealSpaceView;
class MapObject;
class MapSpaceView;
class FTLView;
class QuasiSpaceView;
class HyperSpaceView;
class PlayerShip;
class Galaxy;
class GalaxyStarSystem;
class ResourceManager;
class InfoFTL;
class SHA1;
class DeterminedRandomGenerator;
class UndeterminedRandomGenerator;
class GlobalURNG;
class StarComponent;
class AutopilotInstruction;
class FTLStripe;

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

	// We'll create a struct to record info on the mouse state
	struct SMouseState
	{
		vector2ds Position;
		vector2ds LastClick;
		u32 LastClickButtons;
	} MouseState;

	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		// Remember whether each key is down or up
		switch(event.EventType)
		{
		case irr::EET_KEY_INPUT_EVENT:
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
			break;
		case irr::EET_MOUSE_INPUT_EVENT:
			switch(event.MouseInput.Event)
			{
			case EMIE_LMOUSE_PRESSED_DOWN:
			case EMIE_RMOUSE_PRESSED_DOWN:
			case EMIE_MMOUSE_PRESSED_DOWN:
				//MouseState.LeftButtonDown = true;
				MouseState.LastClick.X = event.MouseInput.X;
				MouseState.LastClick.Y = event.MouseInput.Y;
				MouseState.LastClickButtons = event.MouseInput.ButtonStates;
				//wprintf(L"Mouse click: %i,%i\r\n",MouseState.LastClick.X,MouseState.LastClick.Y);
				break;

			case EMIE_MOUSE_WHEEL:
				//MouseState.LeftButtonDown = false;
				//MouseState.LastClickButtons = MouseState.LastClickButtons;
				if (event.MouseInput.Wheel>0)
				{
					KeyIsDown[KEY_PSEUDO_MOUSEWHEELUP]=true;
					KeyIsDown[KEY_PSEUDO_MOUSEWHEELDOWN]=false;
				}
				else
				{
					KeyIsDown[KEY_PSEUDO_MOUSEWHEELUP]=false;
					KeyIsDown[KEY_PSEUDO_MOUSEWHEELDOWN]=true;
				}
				break;

			case EMIE_MOUSE_MOVED:
				MouseState.Position.X = event.MouseInput.X;
				MouseState.Position.Y = event.MouseInput.Y;
				break;

			default:
				// We won't use the wheel
				break;
			}
			break;
		default:
			break;
		}


		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	// This is used to check whether a key is pressed once
	virtual bool IsKeyPressed(EKEY_CODE keyCode) 
	{
		if (KeyIsDown[keyCode])
		{
			KeyIsDown[keyCode] = false;
			return true;
		}
		return false;
	}

	vector2ds GetMousePosition() {return MouseState.Position;}
	vector2ds GetLastMouseClick() {return MouseState.LastClick;}
	u32 GetLastMouseClickButtons() {return MouseState.LastClickButtons;}
	void RemoveLastMouseClick() {MouseState.LastClick = vector2ds(-1);}

	//void CleanKeyStatus(EKEY_CODE keyCode) {KeyIsDown[keyCode]=false;}
	
	MyEventReceiver()
	{
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
		MouseState.Position = vector2ds(-1);
		MouseState.LastClick = vector2ds(-1);
	}

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

//Interface for objects, which need to handled with complex memory management
//Keep counter of locks (references), which is base for (self)-destruction of object
class LockCounted {
	public:
		LockCounted() {lockCount = 0;}
		virtual ~LockCounted() {}
		void lock(s32 locking);
		bool unlock(s32 unlocking);
	private:
		s32 lockCount;
};


//Hold info about gravity at certain point
class GravityInfo {
	public:
		text_string print();//print information

		//max gravity:
		f64 maxGravity; //value
		SpaceObject* maxGravityObject;//emitting object

		//second max gravity
		f64 secondMaxGravity; //value
		SpaceObject* secondMaxGravityObject;//emitting object

		void UpdateGravityInfoOrbit(SpaceObject* orbitingObject);//update orbiting info

		//Kepler orbit elements (around maxGravityObject)
		f64 orbitSemimajorAxis;//Semimajor axis
		f64 orbitEccentricity;//Eccentricity
		f64 orbitArgumentPeriapsis;//Argument of periapsis
};

//Hold information about wormhole between two stars (without references to objects, just coordinates)
class WormholeInfo {
	public:
		vector2ds Star1;
		vector2ds Star2;
};


//SpaceObject - any object in current RealSpace
class SpaceObject {

	public:

		//TODO: think on subclassing space objects

		//Type of object motion
		enum MotionType : s32 {
			MOTION_NONE,        //Object not moving at all
			MOTION_ORBITAL,     //Object is orbiting circular orbit around another
			MOTION_LINKED,      //Object is linked to another object and follow him as fixed-linked
			MOTION_NAVIGATION,  //Object is self-navigating
			MOTION_FTL,         //Object moves at FTL
			MOTION_PLUSMINUS,   //Object moves at PlusMinus
			MOTION_HYPER,       //Object moves in HyperSpace (only for PlayerShip?)
		};

		enum ControlType {
			CONTROL_THRUST_ABSOLUTE,
			CONTROL_THRUST_RELATIVE,
			CONTROL_ROTATION_SPEED_ABSOLUTE,
			CONTROL_ROTATION_SPEED_RELATIVE,
		};

		//Integer and boolean properties
		enum IntProperty : s32 {
			VISIBLE_TO_PLAYER=0, //bool: 0 - false, 1 - true
			MOTION_TYPE,         //See MotionType
			EMIT_GRAVITY,        //bool: 0 - false, 1 - true
			AFFECTED_BY_GRAVITY, //bool: 0 - false, 1 - true
			WORMHOLE,            //bool: 0 - false, 1 - true
			TRAVEL_TO_X,         //s32, x coordinate of wormhole or stargate travel, also used by gravity-well
			TRAVEL_TO_Y,         //s32, y coordinate --- !! ----
			STARGATE,            //s32, 0 - none, 1 - gate, 2 - event horizon
			GRAVITY_WELL,        //bool, 0 - none, 1 - gravity well (only for hyperspace)
			ACTIVE,              //bool: 0 - false, 1 - true  (only for stargate)
			CURRENT_PROCESS,     //s32, see enum ProcessType
			COLLISIONS_CHECK,    //bool: 0 - false, 1 - true

			INT_PROPERTIES_COUNT,//Only for array allocation
		};

		//Floating point properties
		enum FloatProperty : s32 {
			MASS=0,              //mass - for calc gravity
			GEOMETRY_RADIUS,     //raduis for map marker and so on
			GRAVITY_MIN_RADIUS,  //raduis for calc gravity only

			THRUST_POWER,        //current thrust
			MAX_THRUST,          //max thrust
			ROTATION_ANGLE,      //current rotation angle  (in radians)
			ROTATION_SPEED,      //rotation speed
			MAX_ROT_THRUST,      //max rotation thrust

			ORBITAL_RADIUS,      //radius of an orbit around orbitingObject
			ORBITAL_PERIOD,      //period of orbiting
			ORBITAL_EPOCH_PHASE, //phase of orbiting (angle in time=0, in radians)

			LINK_ROTATION_ANGLE, //rotation relative to parent object (in radians)

			PROCESS_START_TIME,  //Time, when current proccess started (or should ended)

			MAX_FTL_GRAVITY,     //Max acceleration for FTL possible
			FTL_REMAINING_TIME,  //Time, left for flying on FTL

			MARKER_SIZE,         //Size of marker on map

			FLOAT_PROPERTIES_COUNT, //Only for array allocation
		};

		//Type of ongoing process
		enum ProcessType : s32 {
			PROCESS_NONE,                //nothing is going on
			PROCESS_STARGATE_OPENING,    //stargate opens, 1 second
			PROCESS_STARGATE_WAITING,    //stargate waiting object to pass, 15 seconds
			PROCESS_STARGATE_CLOSING,    //stargate closing, 1 second
			PROCESS_DELAYED_DELETION,    //delete object at process-start-time
			PROCESS_WORMHOLE_RESIZING,   //wormhole check and opening/closing (up to GRAVITY_MIN_RADIUS, exponential by time), start time is time of next check
		};

		SpaceObject();//Constuctor
		~SpaceObject();//Destructor

		//Getters
		s32 GetIntProperty(IntProperty propertyNumber) {return IntProperties[propertyNumber];}
		f64 GetFloatProperty(FloatProperty propertyNumber) {return FloatProperties[propertyNumber];}
		vector3d GetPosition() {return position;}
		vector3d GetPrevPosition() {return prevPosition;}
		vector3d GetSpeed();
		vector3d GetDirection();
		text_string GetName() {return name;}
		SceneNode* GetNode() {return sceneNode;}
		text_string GetAutopilotInfo();

		//Setters
		void SetPosition(vector3d newPos) {position = newPos; prevPosition = newPos;}
		void SetSpeed(vector3d newSpeed) {speed = newSpeed;}
		void SetNode(SceneNode * node);
		void SetMarkerNode(SceneNode * node, f64 size);
		void SetOrbitalParams(SpaceObject* parent, f64 radius, f64 Period, f64 EpochPhase);
		void SetLinkedParams(SpaceObject* parent, vector3d linkPos, f64 linkRot);
		void SetOrbitalParent(SpaceObject* parent) {orbitingObject = parent;}
		void SetPhysics(GamePhysics* physicsOwner) {physics = physicsOwner;}
		void SetName(text_string newName) {name = newName;}
		void SetIntProperty(IntProperty propertyNumber, s32 newValue);
		void SetFloatProperty(FloatProperty propertyNumber, f64 newValue);
		void AddFloatProperty(FloatProperty propertyNumber, f64 addValue);

		SpaceObject* GetEstimation(f64 atTime);//Estimation of object (position+speed) on past/future
		
		vector3d GetGravityAcceleration(vector3d location);//Get gravity, emitted by this object
		vector3d GetXGravityAcceleration(vector3d location);//Get X-gravity, emitted by this object
		void SetControl(f64 newValue, ControlType type);

		bool AutopilotBreak();//Stopping
		bool AutopilotOrbiting();//Setting to orbit
		bool AutopilotSetSpeed(vector3d requiredSpeed);//Matching speed
		bool AutopilotRotate(vector3d requiredDirection);//Aiming
		//bool AutopilotFlyTo(vector3d requiredLocation, f64 requiredSpeed);//Simply flying (rotate+accelerate+fly-at-half-lightspeed+breaking)
		bool AutopilotFlyTo(AutopilotInstruction* instruction, f64 frameTime);//Simply flying (rotate+accelerate+fly-at-half-lightspeed+breaking)
		bool AutopilotFTLTo(AutopilotInstruction* instruction, f64 frameTime);//FTL to location
		bool AutopilotFlyToOrbit(AutopilotInstruction* instruction, f64 frameTime);//Flying to orbit
		bool AutopilotHyperFlyTo(AutopilotInstruction* instruction, f64 frameTime);//Flying in HyperSpace to location

		void AddAutopilot(AutopilotInstruction* instruction);
		void BreakAutopilot();

		void JumpToFTL(f64 ftlSpeed);
		void BreakFTL(f64 remainingSpeed);

		virtual void FallIntoWormhole(SpaceObject* wormhole);
		virtual void FallIntoStargate(SpaceObject* wormhole);

		SpaceObject* FireProjectile();

		void Delete();//call physics to delete this object

		//updating
		void UpdatePhysics(f64 time);
		void UpdateMotionOnFTL(f64 time);
		void UpdateSceneNode();
		void UpdateSceneNode(SpaceObject* centerSceneObject);
		void UpdateMarkerNode(f64 cameraDistance);
		void UpdateVisibility(SpaceObject* centerSceneObject);

	protected:
		//Arrays of properties
		s32 IntProperties[INT_PROPERTIES_COUNT];
		f64 FloatProperties[FLOAT_PROPERTIES_COUNT];

		core::array<AutopilotInstruction*> autopilotQueue;

		vector3d position;//current position in space, coordinates (zero at star system center of mass)
		vector3d prevPosition;//previous position in space (used for checking collisions)
		vector3d speed;//current motion speed, relative to "background stars"

		vector3d linkPosition;//position relative to parent object

		text_string name;

		SpaceObject* orbitingObject;//parent object for orbiting or linked-motion
		GamePhysics* physics;//reference to GamePhysics

		SceneNode * sceneNode; //Irrlich renderable object
		SceneNode * sceneMarkerNode; //sceneNode of map-marker type - for displaying from a far
		//vector3d acceleration; //
};

//GamePhysics - calculates movement, collision, gravity and so on
class GamePhysics {
	public:
		GamePhysics();
		~GamePhysics();

		f64 globalTime;//Global time, in seconds
		//TODO: move field into private area

		//Getters
		bool IsInterstellar() {return isInterstellar;}//Are we in insterstellar space
		vector2d GetGalaxyCoordinatesOfCenter() {return galaxyCoordinatesOfCenter;}
		vector2ds GetGalaxyQuadrant() {return galaxyQuadrant;}
		DG_Game* GetRoot() {return gameRoot;}
		SpaceObject* GetWormholeTo(vector2ds galaxyQuadrant);
		SpaceObject* GetFirstObject(SpaceObject::IntProperty prop, s32 value);
		void GetObjectsAtDistance(core::array<SpaceObject*>* list, vector3d location, f64 distance);
		f64 GetTimeSpeed() {return timeSpeed;}

		//Setters
		void SetGalaxyCoordinatesOfCenter(vector2d newCoordinates);
		void SetGalaxyQuadrant(vector2ds newQuadrant) {galaxyQuadrant = newQuadrant;}
		void SetGravityCheckRadiusSQ(f64 newRadiusSQ) {maxGravityCheckRadiusSQ = newRadiusSQ;}
		void SetPlayerShip(PlayerShip* newPlayerShip) {playerShip = newPlayerShip;}
		void SetTimeSpeed(f64 newSpeed);
		void SetRoot(DG_Game* newRoot) {gameRoot = newRoot;}

		void Update(f64 time);
		void UpdateNodes(SpaceObject* centerSceneObject, u32 flags);
		void AddObject(SpaceObject* newObject);
		void UpdateMarkers(f64 cameraDistance);
		void UpdateMapMarkers(f64 mapScale);

		void RemoveObject(SpaceObject* removedObject);

		s32 IsGravity();

		vector3d FindRandomLocationWithSpecificGravity(f64 gravityMin, f64 gravityMax);
		vector3d FindRandomLocationWithSpecificXGravity(f64 gravityMin, f64 gravityMax);

		vector3d GetGravityAcceleration(vector3d location);
		vector3d GetXGravityAcceleration(vector3d location);
		GravityInfo* GetGravityInfo(vector3d location);

		void CheckCollisions(SpaceObject* object);
		
		bool IsFTLPossible(vector3d location, f64 gravityLimit);
		bool IsPlusMinusPossible(vector3d location);

		void SendStargateAddress(SpaceObject* sender, u64 address);

		InfoFTL* CheckFTLBreak(vector3d start, vector3d end, f64 gravityLimit);
		bool CheckLeaveStarSystem();

		void GoInterstellar();
		void GoStarSystem();
		void GoHyperSpace();

		void Activate();

		//f64 GetHyperSpaceTwirl();
		f64 GetHyperSpaceTwirl(vector3d atPosition);

		void DebugJumpToWormhole(u32 param);

		void MakeMap(MapSpaceView* mapView);//Provide MapSpaceView with info about all objects

	private:
		bool calcCollisions;//Perform collision calculations or not
		bool isInterstellar;
		f64 maxGravityCheckRadiusSQ; //if object is farther from this radius, then we could skip checking of gravity for FTL, radius squared as it is much easier to check this way
		f64 timeSpeed;//speed of time going, 1.0 for normal, 100 for faster
		//f64 hyperSpaceTwirl;
		//f64 hyperSpaceTwirlChangeTime;

		f64 hyperSpaceTwirl11,hyperSpaceTwirl12,hyperSpaceTwirl21,hyperSpaceTwirl22;
		vector2ds hyperSpaceTwirlAnchor;//coordinates for hyperSpaceTwirl11 value

		DG_Game* gameRoot;
		PlayerShip* playerShip;
		core::array<SpaceObject*> listObjects;//All known objects
		vector2d galaxyCoordinatesOfCenter;
		vector2ds galaxyQuadrant;

		void ClearObjects();//all but player

};

//DG_Game - game root, hold everything else
class DG_Game {

	public:

		enum ViewType {
			VIEW_NONE,
			VIEW_REALSPACE,
			VIEW_SECTOR_MAP,
			VIEW_FTL,
			VIEW_QUASISPACE,
			VIEW_HYPERSPACE,
		};

		int Init(int Count, char **Arguments);
		void Update();
		void Close();

		Galaxy* GetGalaxy() {return wholeGalaxy;}
		ResourceManager* GetResourceManager() {return resourceManager;}
		PlayerShip* GetPlayerShip() {return playerShip;}
		GalaxyStarSystem* GetCurrentSystem() {return currentStarSystem;}

		s32 AcviateView(ViewType newView);
		s32 CloseView(ViewType oldView);
		s32 SwitchView(ViewType newView);

		bool IsViewActive(ViewType checkedView);

		void UseSceneManager(ViewType ofView);

		void GoInterstellar();
		void GoStarSystem(GalaxyStarSystem* toStarSystem);
		void GoHyperSpace();
		void BreakHyperSpace();

		void SaveGame();
		void LoadGame();

		bool IsDone() { return Done; }
		void SetDone(bool Value) { Done = Value; }

	private:
		ResourceManager* resourceManager;
		Galaxy* wholeGalaxy;

		PlayerShip* playerShip;

		GalaxyStarSystem* currentStarSystem;

		IrrlichtDevice* device;
		u32 then;
		GamePhysics * gamePhysics;
		bool Done, MouseWasLocked;
		MyEventReceiver* receiver;
		scene::ISceneManager* smgr;
		video::IVideoDriver* driver;
		s32 lastFPS;


		//Views
		RealSpaceView* RealSpace;
		MapSpaceView* SectorMap;
		FTLView* FTLSpace;
		QuasiSpaceView* QuasiSpace;
		HyperSpaceView* HyperSpace;

		SpaceObject::MotionType prevPlayerMotion;

		core::array<ViewType*> viewStack;
		GameView* activeView;

		void InternalAcviateView(ViewType newView);

};

//ResourceManager - manage game resources
class ResourceManager
{
	public:
		void Setup(IrrlichtDevice* newDevice, scene::ISceneManager* newSceneManager, video::IVideoDriver* newVideoDriver, MyEventReceiver* newEventReceiver, GamePhysics* newPhysics);
		void SetSceneManager(scene::ISceneManager* newSceneManager) {sceneManager = newSceneManager;}

		IrrlichtDevice* GetDevice() {return device;}
		video::IVideoDriver* GetVideoDriver() {return videoDriver;}
		MyEventReceiver* GetEventReceiver() {return eventReceiver;}
		gui::IGUITab* GetHUD(DG_Game::ViewType view);

		//void MakeSimpleSystem();
		void MakeBackground();
		SpaceObject* MakeStar(f64 radius = 10.0, s32 polygons = 32);
		SpaceObject* MakePlanet(f64 radius = 3.0, s32 polygons = 32);
		SpaceObject* MakeBarycenter();
		SpaceObject* MakeWormhole();
		SpaceObject* MakeStargate();
		SpaceObject* MakeStargateEH();
		SpaceObject* MakeShip();
		SpaceObject* MakeMarker();
		SpaceObject* MakeGravityWell(f64 radius);//location of star/planet in HyperSpace
		SpaceObject* MakeProjectile();
		SpaceObject* LoadNodesForShip(SpaceObject* ship);
		void AddMarker(SpaceObject* toObject, u32 type);
		void ActivateHUD(DG_Game::ViewType view);

		SceneNode* NewShipNode();

		//gui::IGUIStaticText* getSimpleText() {return simpleTextToDisplay;}

	private:
		//gui::IGUIStaticText* simpleTextToDisplay;
		GamePhysics* physics;

		IrrlichtDevice* device;
		scene::ISceneManager* sceneManager;
		video::IVideoDriver* videoDriver;
		MyEventReceiver* eventReceiver;

		gui::IGUITab* RealSpace_HUD;
		gui::IGUITab* Map_HUD;
		gui::IGUITab* FTL_HUD;
		gui::IGUITab* QuasiSpace_HUD;
		gui::IGUITab* HyperSpace_HUD;
};


//GameView - interface-like class for different game views
class GameView
{
public:
	virtual void Init() {}; //called once, after construction
	virtual void Prepare() {};//called for recreating objects
	virtual void Activate() {};//called just before switching
	virtual void Update(f64 frameDeltaTime) {}; //update on frame
	virtual void Close() {}; //called once for destruction
	virtual vector2d GetCoordinatesOnScreen(vector2ds pixelCoords, u32 flags) {return vector2d(0);} //for convert mouse clicks into physics/galaxy and so on coordinates, flags: 1 - return galaxy coordinates (default: physics)

	void SetRoot(DG_Game* newRoot) {gameRoot = newRoot;}
	void SetSceneManager(scene::ISceneManager* newSceneManager) {sceneManager = newSceneManager;}
	void SetPhysics(GamePhysics* newPhysics) {gamePhysics = newPhysics;}

	scene::ISceneManager* GetSceneManager() {return sceneManager;}

	void DisplayMessage(text_string message);

protected:
	DG_Game* gameRoot;
	GamePhysics * gamePhysics;
	MyEventReceiver* eventReceiver;
	IrrlichtDevice* device;
	scene::ISceneManager* sceneManager;
	video::IVideoDriver* videoDriver;
	ResourceManager* resourceManager;
	gui::IGUITab* viewHUD;
	SceneNode* forceField;
};

//RealSpaceView - to render RealSpace
class RealSpaceView : public GameView
{
public:
	RealSpaceView();

	void Init();
	void Prepare();
	void Activate();
	void Update(f64 frameDeltaTime);
	void Close();
	vector2d GetCoordinatesOnScreen(vector2ds pixelCoords, u32 flags);

	f64 GetCameraDistance() {return cameraDistance;}
	f64 cameraDistanceDegree;

	void Clean();

	void UpdateCameraDistance();

private:
	f64 cameraDistance;
	u32 typing;
	text_string typingText;
	text_string typingTextPrev;

	PlayerShip* playerShip;
	//f64 playerThrust; //TODO: move to other class (?)

	scene::ICameraSceneNode* camera;
	SceneNode* playerShipThrust;
	gui::IGUIStaticText* simpleTextToDisplay;
};

//MapObject - single object on map (for MapSpaceView)
class MapObject
{
public:
	MapObject();
	void UpdatePosition(f64 mapScale, vector2d centerOfMap);
	void SetNonObjectPosition(vector2d newPositions) {originalObject = 0;nonObjectPosition = newPositions;}
	void SetNode(SceneNode * node) {sceneNode = node;}
	void SetOriginal(SpaceObject* object) {originalObject = object;}
	void SetSizes(f64 newSizeReal, f64 newSizeMinimal) {sizeReal = newSizeReal; sizeMinimal = newSizeMinimal;}
	void SetYScale(f64 newYScale) {yScale = newYScale;}
	void SetScaleLimits(f64 newLowLimit) {lowScaleLimit = newLowLimit;}

private:
	SpaceObject* originalObject;
	vector2d nonObjectPosition; //in case of originalObject=0
	f64 sizeReal;//physical size of object, for detailed zooms
	f64 sizeMinimal;//in case of very far distance
	f64 lowScaleLimit;//fade objects if it too big
	f64 yScale;//scale koeff for Y-size
	SceneNode* sceneNode; //Irrlich renderable object
};

//MapSpaceView - for drawing map of RealSpace
class MapSpaceView : public GameView
{
public:
	void Init();
	void Prepare();
	void Activate();
	void Update(f64 frameDeltaTime);
	void Close();
	vector2d GetCoordinatesOnScreen(vector2ds pixelCoords, u32 flags);

	void AddObject(SpaceObject* spaceObject);
	void AddStarMarker(GalaxyStarSystem* starSystem);
	void AddWormholeLink(vector2d coordinates1, vector2d coordinates2);

	void AddGalaxy(vector2d galaxyPosition);

	void SetCenter(vector2d newCenter) {centerOfMap = newCenter;}

	f64 cameraDistanceDegree;

	void UpdateCameraDistance(u32 flags);

private:
	f64 mapScale;
	f64 gridCellSize;
	vector2d centerOfMap;
	vector2d shiftToQuadrant;//shift from galaxy quarant grid to center of physics (used for drawing detailed grid)
	vector2d shiftToGalaxy;//shift from galaxy center to center of physics (used for drawing galaxy-scale grid)
	core::array<MapObject*> MapObjectList;
	void ClearObjects();
	scene::ICameraSceneNode* camera;
	SceneNode* gridNode;
	gui::IGUIStaticText* simpleTextToDisplay;
};

//FTLView - to render fly on FTL
class FTLView : public GameView
{
public:
	void Init();
	void Prepare();
	void Activate();
	void Update(f64 frameDeltaTime);
	void Close();

private:
	static const u32 flowSectorCount = 32;
	f64 angle;//fly angle
	s32 flowSectors[flowSectorCount];
	PlayerShip* playerShip;
	SceneNode* playerShipNode;
	scene::ICameraSceneNode* camera;
	SceneNode* forceField;
	gui::IGUIStaticText* simpleTextToDisplay;
	core::array<FTLStripe*> stripes;//for GFX only
};

//QuasiSpaceView - to render fly in QuasiSpace of PlusMinus
class QuasiSpaceView : public GameView
{
public:
	void Init();
	void Prepare();
	void Activate();
	void Update(f64 frameDeltaTime);
	void Close();


private:
	PlayerShip* playerShip;
	SceneNode* playerShipNode;
	scene::ICameraSceneNode* camera;
};

//HyperSpaceView - to render fly in HyperSpace
class HyperSpaceView : public GameView
{
public:
	void Init();
	void Prepare();
	void Activate();
	void Update(f64 frameDeltaTime);
	void Close();
	vector2d GetCoordinatesOnScreen(vector2ds pixelCoords, u32 flags);

	void AddStar(GalaxyStarSystem* starSystem);
	void RemoveAllStars();

	f64 GetCameraDistance() {return cameraDistance;}
	f64 cameraDistanceDegree;

	void UpdateCameraDistance();

private:
	f64 cameraDistance;

	PlayerShip* playerShip;
	scene::ICameraSceneNode* camera;
	gui::IGUIStaticText* simpleTextToDisplay;
};

//PlayerShip - hold all information about player and his ship
class PlayerShip : public SpaceObject
{
public:
	PlayerShip();

	vector2d GetGalaxyCoordinates() {return galaxyCoordinates;}
	vector2ds GetGalaxyQuadrant() {return galaxyQuadrant;}
	f64 GetControlThrust() {return controlThrust;}

	void SetGalaxyCoordinates(vector2d newCoords);

	void UpdateGalaxyCoordinates(u32 type);

	void JumpToQuasiSpace(s32 direction);//+1 for Plus, -1 for Minus, 0 for random (+2/-2)
	void BreakQuasiSpace();
	void UpdateQuasiSpace(f64 time, Galaxy* galaxy);
	void FallIntoWormhole(SpaceObject* wormhole);
	void SetControlThrust(f64 newThrust);

	void FallIntoStargate(SpaceObject* wormhole);
	void ScanSpace(f64 radius);

	void DebugPrint_QuasiSpace();

private:
	f64 controlThrust;
	vector2d galaxyCoordinates;
	vector2ds galaxyQuadrant;

	s32 plusMinusDirection;//+1 for Plus, -1 for Minus (+2/-2 on random)
	f64 plusMinusTime;//accumulated time for PlusMinus calculation
	f64 plusMinusStep;//step (i.e. speed) of PlusMinus calculation
	s32 plusMinusCounter;//counter of jumps
	s32 plusMinusDoubling;//counter value on which we should double speed of PlusMinus calculation
};

//Galaxy - hold main information about whole Galaxy
class Galaxy
{
public:
	~Galaxy();

	void Init();//creation
	GalaxyStarSystem* GetStarSystem(vector2ds coordinates);//Get star system in quadrant
	GalaxyStarSystem* GetNearStarSystem(vector2d coordinates);//Get nearest star system by exact coordinates
	void AddNearStarSystems(MapSpaceView* mapView);//Add markers of near star system to MapView
	void AddHyperSpaceObjects(HyperSpaceView* hyperView, u32 flags);//Add markers of near star system to HyperSpaceView
	u32 CheckStarPresence(vector2ds coordinates);//Check only presence of star in quadrant
	u32 CheckStargatePresence(vector2ds coordinates, bool checkStar);//Check presence of stargate in system
	u32 IsInGrid(vector2ds coordinates);//Check coordinates for being inside 131072x131072 grid
	GalaxyStarSystem* GetStartStarSystem(); //Get star system of player start
	void UpdatePlayerLocation(vector2d coordinates);//For updating cache of stars
	void GetWormholesFrom(vector2ds quadrant, core::array<WormholeInfo*>* list);

	u64 Coordinates2StargateAddress(vector2ds quadrant);//convert coordinates to address
	vector2ds StargateAddress2Coordinates(u64 address);//convert address to coordinates  (two error cases possible: - address is greater than PK and decryption does not have padding)
	u64 text2StargateAddress(text_string text);//convert text to address
	text_string StargateAddress2text(u64 address);//convert text to address

	vector3d Galaxy2HyperSpace(vector2d galaxyCoordinates);//convert galaxy coordinates to HyperSpace coordinates
	vector2d HyperSpace2Galaxy(vector3d hyperSpaceCoordinates);//convert HyperSpace coordinates to galaxy coordinates
	f64 GetHyperSpaceTwirl(vector2ds galaxyQuadrant);

	//void DebugDump();//ONLY for debug - dump count of stars in regions 64x64 ly
	void SaveMapTexture();

	vector2ds MoveByPlusMinus(vector2ds quadrant, s32 direction);
	s32 HilbertCurveDirection(s32 x, s32 y, s32 direction);

	GalaxyStarSystem* DebugJump();
	void DebugShowWormholes();

private:

	static const u8 sBox[256];
	static const u8 sBoxInv[256];

	bool wormholesGenerated;
	u32 debugStarCounter;
	u32 galaxyType;//0 - E0, 1 - E1-E7, 2 - S*, 3 - Irr random, 4 - E* two cores

	f64 halfDensityRadius;//10k-17k ly, ~14600 ly for Milky Way
	f64 maxDensity;//stellar density in the core, should vary from 0.1 to 0.6
	f64 outerRadius;//beyond that is intergalaxy space
	f64 minorRadius;//only for elliptical galaxies

	f64 starCountEstimation;// amount of star systems in a galaxy, estimation by stellar density field

	//constants of stargate address/coordinates conversion function (includes RSA encryption/decryption)
	u64 sgPublicKeyMod;//n - public key modulus
	u64 sgPublicKeyExp;//e - public key exponent
	u64 sgPrivateKeyExp;//d - private key exponent (non-CRT)
	u64 sgCoordXorValue;//value to xor coordinates additionally
	u64 sgAddressAddValue;//value to add to address additionally

	u8 galaxySeed[16];//seed of whole galaxy
	DeterminedRandomGenerator* galaxyRNG;//

	f32 stellarDensity[2048][2048];//stellar density field
	
	core::array<GalaxyStarSystem*> knownStars;//cache for near stars
	core::array<WormholeInfo*> knownWormholes;//cache for wormholes
	vector2ds knownStarsAnchor;//"center" of cache
	vector2ds hyperSpaceStarsAnchor;//last updated "center" of cache

	GalaxyStarSystem* SeedStar(vector2ds coordinates);//seed star system from galaxy seed. Prereq: galaxyRNG must be seeded with coordinates in CheckStarPresence() or so
	void UpdateKnownStars(s32 param = 0);//Updates caches (ex. in case of player moves to quadrant other than center of cache)

	void GenerateWormholes(s32 param = 0);
	void ClearWormholes();
	void ClearKnownStars();
};

//Information about 1 star system in the galaxy
//Object reference should be stored with lock-unlock mechanism
class GalaxyStarSystem : public LockCounted
{
public:

	GalaxyStarSystem(vector2ds quadrantCoordinates);
	~GalaxyStarSystem();

	vector2d GetGalaxyCoordinates() {return galaxyCoordinates;}
	vector2ds GetGalaxyQuadrant() {return galaxyQuadrant;}
	text_string GetName() {return name;}
	f64 GetWormholeDistance() {return wormholeDistance;}
	u64 GetStargateAddress() {return stargateAddress;}
	u32 GetStatus() {return statusFlags;}

	void SetSeed(u8* seedData, u32 seedLen);

	//static GalaxyStarSystem* RandomStar(vector2ds quadrantCoordinates);
	void GenerateStar();
	void SetName(text_string newName) {name = newName;}

	void GenerateStarSystem(ResourceManager* resourceManager, Galaxy* galaxy);

	void GenerateComponent(ResourceManager* resourceManager, f64 mass, f64 sizeLimit, SpaceObject** rootObject);

	void GenerateComponent2(StarComponent* component);
private:
	u32 statusFlags;//1 - seed set, 2 - generated
	f64 wormholeDistance;//distance of wormholes from center
	u32 componentIndex;//for naming stars in systems
	u32 planetIndex;//for numbering planets
	u64 stargateAddress;//address of this system
	DeterminedRandomGenerator* starRNG;
	vector2d galaxyCoordinates;
	vector2ds galaxyQuadrant;
	text_string name;

	SpaceObject* FinalizeComponent(ResourceManager* resourceManager, StarComponent* component);
	void GenerateWormholes(ResourceManager* resourceManager, StarComponent* component, Galaxy* galaxy);
	SpaceObject* GenerateStargate(ResourceManager* resourceManager, StarComponent* component, Galaxy* galaxy);

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
	~DeterminedRandomGenerator();

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
	~UndeterminedRandomGenerator();

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

//(kind a) Singleton for UndeterminedRandomGenerator
class GlobalURNG : UndeterminedRandomGenerator
{
public:
	static UndeterminedRandomGenerator &Instance() {
		//& is needed for updating objIntance by further calls, and a not copy
		static UndeterminedRandomGenerator objIntance;
		return objIntance;
	}
	
};

//Holds info on star or composite component of star system
class StarComponent
{
public:
	StarComponent();
	~StarComponent();

	u32 type;//0 - composite, 1 - main-sequence star, 2 - ...
	f64 mass;//mass, in units
	f64 radius;//physical radius of object, in units,  for composite its radius of components + mutual distance
	f64 luminosity;//luminosity of object, in Solar's, N/A for composite
	f64 innerOrbitLimit;//inner limit for orbiting objects
	f64 outerOrbitLimit;//outer limit for orbiting objects
	f64 maxOrbiting;//max distance for orbiting objects
	//text_string spectralClass;
	f64 colorIndexBV;//  en.wikipedia.org/wiki/B-V_color,  N/A for composite
	f64 subComponentsOrbit; //distance between subcomponents
	StarComponent* subComponentA; //most massive, 0 if current is single object
	StarComponent* subComponentB; //least massive, 0 if current is single object
};

//Elements of autopilot "script"
class AutopilotInstruction
{
public:
	enum AutopilotType : s32 {
		AP_SETSPEED,        //Set speed to desired value, params: vector1 is required speed
		AP_ORBITING,        //Set speed to orbit max-gravity object, params: none
		AP_FLY_TO,          //Fly to specific location, params: vector1 is required location, value1 is required speed
		                             //use: value2 is maxspeed, value3 is remaining time, value4 is time since recalc course
		//AP_FTL_TIMER,       //FTL jump for specific time, params: value1 is time 
		AP_FTL_TO,          //FTL fly to specific location, params: vector1 is required location (galaxy coordinates)
		AP_FLY_TO_ORBIT,    //Fly to orbit of object near specific location, params: paramObject is object to orbit, value1 is orbit height
		AP_HYPERSPACE_FLY_TO, //Fly to in HyperSpace, params: vector1 is required location
	};

	AutopilotInstruction() {prepareText = false; object = 0; paramObject = 0;}
	~AutopilotInstruction()	{
		if (object)
			object->Delete();
	}


	AutopilotType instruction;
	bool prepareText;
	u32 phase;//phase, for multi-phase autopiloting
	vector2d vector1;
	vector2d vector2;
	f64 value1;
	f64 value2;
	f64 value3;
	f64 value4;
	f64 value5;
	SpaceObject* object;//for autopilot marker
	SpaceObject* paramObject;
	text_string textInfo;
};

//FTL graphical stripe
class FTLStripe
{
public:
	f64 angle;
	f64 speed;
	//f64 acceleration;
	f64 width;
	//u32 red, green, blue;
	SceneNode* node;
};

//#########################################################################
//Class methods

//#########################################################################
//LockCounted

//Lock object
void LockCounted::lock(s32 locking)
{
	lockCount+=locking;
}

//Unlock object, delete it if lock counter become zero
bool LockCounted::unlock(s32 unlocking)
{
	lockCount-=unlocking;
	if (lockCount<=0)
	{
		delete this;
		return true;
	}
	return false;
}

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

	invAxis = 2.0/relativePosition.getLength() - relativeSpeed.getLengthSQ()/(G_CONSTANT*maxGravityObject->GetFloatProperty(SpaceObject::MASS));

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
	orbitEccentricity = sqrt(1-specificRAMomentum*specificRAMomentum*invAxis/(G_CONSTANT*maxGravityObject->GetFloatProperty(SpaceObject::MASS)));
	//orbitEccentricity = -2;//not calced
}


text_string GravityInfo::print()
{
	text_string gravityInfo;//(L"");
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
	prevPosition = vector3d(0);
	speed = vector3d(0);
	//SetFloatProperty(ROTATION_ANGLE,0);
	sceneNode = 0;
	sceneMarkerNode = 0;
	orbitingObject = 0;

	name = L"";

	for (u32 i=0;i<INT_PROPERTIES_COUNT;i++)
		IntProperties[i]=0;
	for (u32 i=0;i<FLOAT_PROPERTIES_COUNT;i++)
		FloatProperties[i]=0;

	SetIntProperty(VISIBLE_TO_PLAYER,1);
	//SetIntProperty(AFFECTED_BY_GRAVITY,0);
	//SetIntProperty(EMIT_GRAVITY,0);
	//SetIntProperty(WORMHOLE,0);
	//SetIntProperty(TRAVEL_TO_X,0);
	//SetIntProperty(TRAVEL_TO_Y,0);
	SetIntProperty(MOTION_TYPE,MOTION_NONE);
	//SetIntProperty(STARGATE,0);
	SetIntProperty(CURRENT_PROCESS,PROCESS_NONE);

	SetFloatProperty(MARKER_SIZE,0.01);
	//SetFloatProperty(PROCESS_START_TIME,0);

	linkPosition = vector3d(0);
	//SetFloatProperty(LINK_ROTATION_ANGLE,0);

	//ftlSpeed = 10.0;
	//isEmitGravity = false;
	//isAffectedByGravity = false;
	//motionType = MOTION_NONE;
	//isVisibleToPlayer = false;
	//SetFloatProperty(MASS,0);
	SetFloatProperty(GRAVITY_MIN_RADIUS,1);
	//SetFloatProperty(GEOMETRY_RADIUS,0);
	//SetFloatProperty(MAX_THRUST,0);
	//SetFloatProperty(THRUST_POWER,0);
	//SetFloatProperty(MAX_ROT_THRUST,0);
	SetFloatProperty(ORBITAL_RADIUS,1.0);
	SetFloatProperty(ORBITAL_PERIOD,1.0);
	//SetFloatProperty(ORBITAL_EPOCH_PHASE,0);
	//SetFloatProperty(ROTATION_SPEED,0);
	SetFloatProperty(MAX_FTL_GRAVITY,0.003);
	//SetFloatProperty(FTL_REMAINING_TIME,0);

}

SpaceObject::~SpaceObject()
{
//	name.~string();
	if (sceneNode)
		sceneNode->remove();
	if (sceneMarkerNode)
		sceneMarkerNode->remove();
	BreakAutopilot();

	return;
}


vector3d SpaceObject::GetDirection()
{
	return vector3d(cos(GetFloatProperty(ROTATION_ANGLE)),sin(GetFloatProperty(ROTATION_ANGLE)),0);
}



void SpaceObject::UpdateSceneNode()
{
	sceneNode->setPosition(vector3df((f32)position.X,(f32)position.Y,0));
	sceneNode->setRotation(vector3df(0,0,(f32)(GetFloatProperty(ROTATION_ANGLE)*RADTODEG64)));
	if (sceneMarkerNode)
	{
		//TODO: optimize?
		sceneMarkerNode->setPosition(vector3df((f32)position.X,(f32)position.Y,0.01f));
		sceneMarkerNode->setRotation(vector3df(0,0,(f32)(GetFloatProperty(ROTATION_ANGLE)*RADTODEG64)));
	}
}

void SpaceObject::UpdateSceneNode(SpaceObject* centerSceneObject)
{
	f32 positionX = (f32)(position.X - centerSceneObject->position.X);
	f32 positionY = (f32)(position.Y - centerSceneObject->position.Y);
	if (sceneNode)
	{
		sceneNode->setPosition(vector3df(positionX,positionY,0));
		sceneNode->setRotation(vector3df(0,0,(f32)(GetFloatProperty(ROTATION_ANGLE)*RADTODEG64)));
	}
	if (sceneMarkerNode)
	{
		//TODO: optimize?
		sceneMarkerNode->setPosition(vector3df(positionX,positionY,0.01f));
		sceneMarkerNode->setRotation(vector3df(0,0,(f32)(GetFloatProperty(ROTATION_ANGLE)*RADTODEG64)));
	}
}

void SpaceObject::UpdateVisibility(SpaceObject* centerSceneObject)
{
	if (GetIntProperty(GRAVITY_WELL)!=0)
	{
		f64 distSQ = (position-centerSceneObject->position).getLengthSQ();
		u32 alpha = 0;
		/*
		u32 alpha = 255;
		if (distSQ>9e11)
		{
			if (distSQ>1.3e12)
				alpha =0;
			else
				alpha = (u32)(255.0*(1.3e12-distSQ)/4e11);
		}*/
		if (distSQ<1.3e12)
			alpha = (u32)(200.0*(1.0-distSQ/1.3e12));//visibility is limited to 6 l.y. of RealSpace equivalent
		if (sceneNode)
			sceneNode->getMaterial(0).EmissiveColor.set(255,alpha,alpha,alpha);
		if (sceneMarkerNode)
			sceneMarkerNode->getMaterial(0).EmissiveColor.set(255,alpha,alpha,alpha);
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
	SetFloatProperty(ORBITAL_RADIUS,radius);
	SetFloatProperty(ORBITAL_PERIOD,period);
	SetFloatProperty(ORBITAL_EPOCH_PHASE,epochPhase);
	//motionType = MOTION_ORBITAL;
	SetIntProperty(SpaceObject::MOTION_TYPE,SpaceObject::MOTION_ORBITAL);
}

void SpaceObject::SetLinkedParams(SpaceObject* parent, vector3d linkPos, f64 linkRot)
{
	orbitingObject = parent;
	linkPosition = linkPos;
	SetFloatProperty(LINK_ROTATION_ANGLE,linkRot);
	SetIntProperty(SpaceObject::MOTION_TYPE,SpaceObject::MOTION_LINKED);
}

void SpaceObject::SetControl(f64 newValue, ControlType type)
{
	switch(type)
	{
		case CONTROL_THRUST_ABSOLUTE:
			SetFloatProperty(THRUST_POWER,newValue);
			//check to max value!
			break;
		case CONTROL_THRUST_RELATIVE:
			SetFloatProperty(THRUST_POWER,newValue*GetFloatProperty(MAX_THRUST));
			//check to max value!
			break;
		case CONTROL_ROTATION_SPEED_ABSOLUTE:
			SetFloatProperty(ROTATION_SPEED,newValue);
			//check to max value!
			break;
		case CONTROL_ROTATION_SPEED_RELATIVE:
			SetFloatProperty(ROTATION_SPEED,newValue*GetFloatProperty(MAX_ROT_THRUST));
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

//Breaking relative to physics center and distant stars
bool SpaceObject::AutopilotBreak()
{
	return AutopilotSetSpeed(vector3d(0));
}

bool SpaceObject::AutopilotRotate(vector3d requiredDirection)
{
	vector3d direction = GetDirection();
	vector3d speedNormalized = requiredDirection;
	speedNormalized.normalize();
	f64 whereToRotate;
	whereToRotate = direction.Y*speedNormalized.X - direction.X*speedNormalized.Y;

	if (fabs(whereToRotate)<0.005 && direction.dotProduct(requiredDirection)>0)
	{
		SetFloatProperty(ROTATION_ANGLE,atan2(requiredDirection.Y,requiredDirection.X));//Force set rotation to required angle
		return true;
	}

	if (whereToRotate>0)
	{
		SetControl(-1,CONTROL_ROTATION_SPEED_RELATIVE);
	}
	else //if (whereToRotate<0)
	{
		SetControl(1,CONTROL_ROTATION_SPEED_RELATIVE);
	}
	return false;
}

//Set speed to desired value
bool SpaceObject::AutopilotSetSpeed(vector3d requiredSpeed)
{
	vector3d direction = GetDirection();
	vector3d changeSpeed = requiredSpeed-speed;
	if (changeSpeed.getLength()<0.01)
	{
		speed = requiredSpeed;
		return true;
	}

	if (AutopilotRotate(changeSpeed))
	{
		f64 k=1;
		if (changeSpeed.getLength()<k*GetFloatProperty(MAX_THRUST)*0.05)//this assumes minimum frame interval is 20 ms, 
		{
			//TODO: get minimum frame interval from physics or game?
			k = 200.0*changeSpeed.getLength()/GetFloatProperty(MAX_THRUST);//adjust breaking thrust power to partial of speed
		}
		SetControl(k,CONTROL_THRUST_RELATIVE);
	}
	return false;
}

//Simply flying (rotate+accelerate+fly-at-half-lightspeed+breaking)
//bool SpaceObject::AutopilotFlyTo(vector3d requiredLocation, f64 requiredSpeed)
bool SpaceObject::AutopilotFlyTo(AutopilotInstruction* instruction, f64 frameTime)
{
	vector3d requiredLocation = vector3d(instruction->vector1.X,instruction->vector1.Y,0);
	f64 requiredSpeed = instruction->value1;

	f64 speedInDirection;
	f64 maxThrust;
	f64 distanceForDeceleration;
	f64 distanceSQ;
	f64 timeRotate = 2.0;
	f64 maxSpeed;

	//TODO: optimize initial calcs
	vector3d flyVector = requiredLocation-position;
	vector3d flyDirection = flyVector;
	distanceSQ = flyVector.getLengthSQ();
	
	flyDirection.normalize();
	speedInDirection = flyDirection.dotProduct(speed);
	maxThrust = GetFloatProperty(MAX_THRUST)*0.5;

	switch(instruction->phase)
	{
	case 0:
	case 1:
		//Out of fly course, recalc it

		f64 D1;

		D1 = 0.25*timeRotate*timeRotate + 0.5*(speedInDirection*speedInDirection+requiredSpeed*requiredSpeed)/(maxThrust*maxThrust) + sqrt(distanceSQ)/maxThrust;
		if (D1<0)
		{
			//Should not happens ever, as D1 have only positive components
			wprintf(L" Autopilot fly-to, failed to solve speed equation\r\n");
			return true;//autopilot failed;
		}
		maxSpeed = maxThrust*(sqrt(D1)-0.5*timeRotate);
		
		if (maxSpeed>(LIGHTSPEED*.5))
			maxSpeed=LIGHTSPEED*.5;

		if (instruction->prepareText)
		{
			instruction->textInfo = L"Autopilot accelerating... ETA: ";
			instruction->textInfo += print_f64(sqrt(distanceSQ)/maxSpeed,L"%.03f");
		}

		instruction->value2 = maxSpeed;//max speed
		instruction->phase = 2;//course calculated
		AutopilotSetSpeed(flyDirection*maxSpeed);
		break;
	case 2:
		//Accelerate
		maxSpeed = instruction->value2;
		if (AutopilotSetSpeed(flyDirection*maxSpeed))
		{
			f64 time = sqrt(distanceSQ)/maxSpeed;
			//wprintf(L" Autopilot fly-to, speed reached, flying... ETA %.3f\r\n",time);
			instruction->value3 = time;
			instruction->value4 = 0;
			instruction->phase = 3;

			if (instruction->prepareText)
			{
				instruction->textInfo = L"Autopilot fly... ETA: ";
				instruction->textInfo += print_f64(time,L"%.03f");
			}
		}
		break;
	case 3:
		//Fly on course
		instruction->value3-=frameTime;
		instruction->value4+=frameTime;
		if (AutopilotRotate(flyDirection))
		{
			maxSpeed = instruction->value2;
			distanceForDeceleration = 0.5*(speedInDirection*speedInDirection - requiredSpeed*requiredSpeed)/maxThrust + timeRotate*maxSpeed;
			if (distanceSQ<(distanceForDeceleration*distanceForDeceleration))
			{
				//wprintf(L" Autopilot fly-to, deceleration...\r\n");
				if (instruction->prepareText)
				{
					instruction->textInfo = L"Autopilot deceleration...";
				}
				instruction->phase = 4;//deceleration
				instruction->value3 = (speedInDirection-requiredSpeed)/maxThrust + timeRotate;
				instruction->vector2.X = flyDirection.X;
				instruction->vector2.Y = flyDirection.Y;
				/*if (maxSpeed > speedInDirection)
					instruction->value2 = speedInDirection;*/
			}
			else
			if (instruction->prepareText)
			{
				instruction->textInfo = L"Autopilot fly... ETA: ";
				//instruction->textInfo += print_f64(sqrt(distanceSQ)/maxSpeed,L"%.01f");
				instruction->textInfo += print_f64(instruction->value3,L"%.01f");
				
			}
		}
		else if (instruction->value4<1.0)
		{
			//small or short deviation from course - adjust speed only
			maxSpeed = instruction->value2;
			AutopilotSetSpeed(flyDirection*maxSpeed);
		}
		else
		{
			//TODO: limit recalculation to once in 1-2 seconds (?)

			//wprintf(L" Autopilot fly-to, course correction needed\r\n");
			instruction->phase = 1;//course should be recalculated
			//TODO - 1 frame lost
			return false;
		}
		break;
	case 4:
		//Time to decelerate
		//maxSpeed = 0.8*sqrt(2.0*sqrt(distanceSQ)*maxThrust + requiredSpeed*requiredSpeed);
		{
			//TODO: deceleration by timer

			instruction->value3-=frameTime;

			f64 minDist = 1 + requiredSpeed*FRAME_TIME_MAX*10;
			if (distanceSQ<(minDist*minDist) || speedInDirection<0)
			{
				if (AutopilotSetSpeed(vector3d(instruction->vector2.X,instruction->vector2.Y,0)*requiredSpeed))
				{
					//wprintf(L" Autopilot fly-to finished\r\n");
					return true;
				}
				return false;
			}
			else
			{
				/*
				AutopilotRotate(-flyDirection);

				f64 k;
				maxSpeed = instruction->value2;
				distanceForDeceleration = 0.5*(speedInDirection*speedInDirection - requiredSpeed*requiredSpeed)/maxThrust + FRAME_TIME_MAX *10.0*maxSpeed;
				k = sqrt(distanceSQ)/distanceForDeceleration;
				if (k>0.99) k = 0.99;
				AutopilotSetSpeed(flyDirection*(maxSpeed*k + (1.0-k)*requiredSpeed));
				*/

				f64 setSpeed = speedInDirection - 0.5*frameTime*(speedInDirection*speedInDirection-requiredSpeed*requiredSpeed)/sqrt(distanceSQ);
				AutopilotSetSpeed(flyDirection*setSpeed);
			}
		}
		break;
	default:
		break;

	}

	/*

	if (instruction->value3!=0 && AutopilotRotate(flyDirection))
	{

	}
	else
	{
	}*/
	return false;

	/*
	timeDeceleration = speedInDirection/maxThrust + 2.0;//2 is time of rotate to backward
	distanceForDeceleration = 0.5*maxThrust*timeDeceleration*timeDeceleration;
	if (distanceSQ>(distanceForDeceleration*distanceForDeceleration))
	{
		maxSpeed = 0.8*sqrt(2.0*sqrt(distanceSQ)*maxThrust);//-maxThrust*2.0;
		if (maxSpeed>(LIGHTSPEED*.5))
			maxSpeed=LIGHTSPEED*.5;
		flyDirection*=maxSpeed;
		AutopilotSetSpeed(flyDirection);
		return false;
	}
	else
	{
		flyDirection*=0.8*sqrt(2.0*sqrt(distanceSQ)*maxThrust);
		return AutopilotSetSpeed(flyDirection);
	}*/
}

bool SpaceObject::AutopilotFTLTo(AutopilotInstruction* instruction, f64 frameTime)
{
	switch(instruction->phase)
	{
	case 0:
		{
			vector2d loc = instruction->vector1-physics->GetGalaxyCoordinatesOfCenter();
			loc*=LIGHTYEAR;
			vector3d requiredLocation = vector3d(loc.X,loc.Y,0);
			vector3d flyVector = requiredLocation-position;
			if (AutopilotRotate(flyVector))
			{
				if (physics->IsFTLPossible(position,GetFloatProperty(SpaceObject::MAX_FTL_GRAVITY)))
				{
					instruction->value1 = flyVector.getLength()/(LIGHTSPEED*3000.0);//remaining time
					SetFloatProperty(FTL_REMAINING_TIME,instruction->value1);

					JumpToFTL(3000.0);
					//physics->GetRoot()->SwitchView(DG_Game::VIEW_FTL);
					instruction->phase = 1;
					//wprintf(L" Autopilot FTL, jumping, ETA: %.6f, finished\r\n",instruction->value1);
				}
				else
				{
					wprintf(L" Autopilot FTL, FTL is not possible, aborted\r\n");
					return true;
				}
			}
		}
		break;
	case 1:
		if (GetIntProperty(MOTION_TYPE)==MOTION_FTL)
		{
			//Set speed at FTL more accurate
			vector2d loc = instruction->vector1-physics->GetGalaxyCoordinatesOfCenter();
			loc*=LIGHTYEAR;
			vector3d requiredLocation = vector3d(loc.X,loc.Y,0);
			vector3d flyVector = requiredLocation-position;
			f64 distance = flyVector.getLength();
			instruction->value1 = distance/(LIGHTSPEED*3000.0);//remaining time
			speed = flyVector*(LIGHTSPEED*3000.0/distance);
			//instruction->phase = 2;
			SetFloatProperty(FTL_REMAINING_TIME,instruction->value1);
			//instruction->value1-=frameTime;
			//wprintf(L" Autopilot FTL, jumped, timer is set, finished\r\n");
			return true;
		}
		else
		{
			//not jumped (only while jumptoftl is instant) or made it in one frame
			/*if (GetFloatProperty(FTL_REMAINING_TIME)>0)
			{
				//not jumped - only while jumptoftl is instant
				wprintf(L" Autopilot FTL, failed to jump to FTL, aborted\r\n");
			}*/
			return true;
		}
		break;
	/*case 2:
		{
			if (GetIntProperty(MOTION_TYPE)!=MOTION_FTL)
			{
				wprintf(L" Autopilot FTL breaked due to jumpout\r\n");
				return true;
			}
			if (instruction->value1<frameTime)
			{
				UpdateMotionOnFTL(instruction->value1);
				wprintf(L" Autopilot FTL finished\r\n");
				BreakFTL(100.0);
				return true;
			}
			instruction->value1-=frameTime;
			return false;
		}*/
	default:
		break;
	}
	return false;
}

bool SpaceObject::AutopilotFlyToOrbit(AutopilotInstruction* instruction, f64 frameTime)
{
	switch(instruction->phase)
	{
	case 0://Not calculated
		{
			u32 attempts;
			f64 nowTime = physics->globalTime;
			f64 meetingTime;
			f64 maxSpeed;
			f64 distance;
			SpaceObject* estimation;
			vector3d meetingPos;
			vector3d meetingPos2;
			vector3d orbitVector;
			maxSpeed = LIGHTSPEED*0.5;

			meetingPos2 = instruction->paramObject->GetPosition();
			
			//very dumb, direct to object itself and use contant speed c/2
			for(attempts=0;attempts<100;attempts++)
			{
				meetingPos = meetingPos2;
				distance = (position-meetingPos).getLength()-instruction->value1;
				meetingTime = nowTime+distance/maxSpeed + 2;
				estimation = instruction->paramObject->GetEstimation(meetingTime);
				meetingPos2 = estimation->GetPosition();
				delete estimation;

				if ((meetingPos2-meetingPos).getLengthSQ()<1) break;
			}
			if (attempts>=100)
			{
				wprintf(L" Autopilot orbiting, failed to solve orbital equation, aborted\r\n");
				return true;
			}
			else
			{
				wprintf(L" Autopilot orbiting, solved orbital equation in %i\r\n",attempts);

			}
			
			orbitVector = meetingPos2-position;
			orbitVector.setLength(instruction->value1);
			meetingPos2 -= orbitVector;

			instruction->value5 = instruction->value1;

			//Dirty hack :)
			//instruction->instruction = AutopilotInstruction::AP_FLY_TO;
			instruction->vector1 = vector2d(meetingPos2.X,meetingPos2.Y);
			instruction->value1 = 0;//speed, 0 is temprorary
			instruction->value2 = 0;//maxspeed = 0
			instruction->phase = 1;
			instruction->object->SetPosition(meetingPos2);


			return false;
		}
		break;
	case 1:
	case 2:
	case 3:
	//case 4:
		//Use Autopilot-Fly-To
		if (AutopilotFlyTo(instruction,frameTime))
		{
			//instruction->phase = 5;
		}
		break;
	case 4:
		{
			/*
			f64 distance = (instruction->paramObject->position-position).getLength();
			f64 relativeSpeed = instruction->paramObject->speed-speed;*/
			vector3d relativePos = instruction->paramObject->position-position;
			//vector3d relativeSpeed = instruction->paramObject->speed-speed;
			vector3d direction = relativePos;
			f64 speedInDirection;
			f64 distance = relativePos.getLength();
			direction.normalize();
			speedInDirection = direction.dotProduct(instruction->paramObject->speed-speed);

			instruction->value4 = fabs(speedInDirection)*sqrt(1.0/fabs(distance-instruction->value5));
			instruction->phase = 5;
		}
		break;
	case 5:
		{
			vector3d relativePos = instruction->paramObject->position-position;
			vector3d relativeSpeed = instruction->paramObject->speed-speed;
			vector3d direction = relativePos;
			vector3d requiredSpeed;
			vector3d gravityAcceleration;
			f64 speedInDirection;
			f64 setSpeedTo;
			f64 orbitingSpeed;
			f64 distance = relativePos.getLength();
			direction.normalize();

			speedInDirection = direction.dotProduct(relativeSpeed);
			//maxThrust = GetFloatProperty(MAX_THRUST)*0.01;

			instruction->object->SetPosition(instruction->paramObject->position-direction*instruction->value5);

			//setSpeedTo = maxSpeed*(distance-instruction->value5)/instruction->value4;
			setSpeedTo = 0.8*instruction->value4*sqrt(fabs(distance-instruction->value5));
			if (distance<instruction->value5)
				setSpeedTo = -setSpeedTo;

			if (setSpeedTo*speedInDirection>0)
				instruction->value4*=0.95;


			//get gravity acceleration from dominant gravity object
			gravityAcceleration = instruction->paramObject->GetGravityAcceleration(position);

			//required speed value - via centro-escape acceleration
			orbitingSpeed = sqrt((gravityAcceleration.getLength())*distance); 

			//required speed - perpendicular to relative position
			requiredSpeed.X = relativePos.Y;
			requiredSpeed.Y = -relativePos.X;
			requiredSpeed.Z = 0;

			/*
			//check opposite direction, it could be closer to current speed
			if (relativeSpeed.dotProduct(requiredSpeed)<0)
			{//yes, this direction is opposite to current speed vector
				requiredSpeed.X=-requiredSpeed.X;//reverse required speed
				requiredSpeed.Y=-requiredSpeed.Y;
			}*/

			requiredSpeed.normalize();//normalize - to get vector of 1 unit length
			requiredSpeed*=orbitingSpeed;//use required speed value

			requiredSpeed+=instruction->paramObject->speed;// + direction*setSpeedTo;

			if (fabs(distance-instruction->value5)<1)
			{
				return (AutopilotSetSpeed(requiredSpeed));
			}
			else
			{
				AutopilotSetSpeed(requiredSpeed+direction*setSpeedTo);
			}
		}
		break;
	}
	return false;
}

bool SpaceObject::AutopilotHyperFlyTo(AutopilotInstruction* instruction, f64 frameTime)
{
	vector3d requiredLocation = vector3d(instruction->vector1.X,instruction->vector1.Y,0);

	f64 speedInDirection;
	f64 maxThrust;
	f64 distanceSQ;
	f64 timeRotate = 2.0;
	f64 maxSpeed;

	//TODO: optimize initial calcs
	vector3d flyVector = requiredLocation-position;
	vector3d flyDirection = flyVector;
	distanceSQ = flyVector.getLengthSQ();
	
	flyDirection.normalize();
	speedInDirection = flyDirection.dotProduct(speed);
	maxThrust = GetFloatProperty(MAX_THRUST);

	switch(instruction->phase)
	{
	case 0:
	case 1:
		//Accelerate into direction of target

		f64 D1;

		D1 = 0.25*timeRotate*timeRotate + 0.5*(speedInDirection*speedInDirection)/(maxThrust*maxThrust) + sqrt(distanceSQ)/maxThrust;
		if (D1<0)
		{
			//Should not happens ever, as D1 have only positive components
			wprintf(L" Autopilot fly-to, failed to solve speed equation\r\n");
			return true;//autopilot failed;
		}
		maxSpeed = maxThrust*(sqrt(D1)-0.5*timeRotate);
		
		if (maxSpeed>(LIGHTSPEED*.3))
			maxSpeed=LIGHTSPEED*.3;

		if (instruction->prepareText)
		{
			instruction->textInfo = L"Autopilot accelerating... ETA: ";
			instruction->textInfo += print_f64(sqrt(distanceSQ)/maxSpeed,L"%.03f");
		}

		instruction->value2 = maxSpeed;//max speed
		instruction->phase = 2;//course calculated
		AutopilotSetSpeed(flyDirection*maxSpeed);
		break;
	case 2:
		//Accelerate
		maxSpeed = instruction->value2;
		if (fabs(speedInDirection-maxSpeed)<maxSpeed*0.001)
		{
			f64 time = sqrt(distanceSQ)/maxSpeed + 0.5*maxSpeed/maxThrust;
			//wprintf(L" Autopilot fly-to, speed reached, flying... ETA %.3f\r\n",time);
			instruction->value3 = time;
			instruction->value4 = 0;
			instruction->phase = 3;

			if (instruction->prepareText)
			{
				instruction->textInfo = L"Autopilot fly... ETA: ";
				instruction->textInfo += print_f64(time,L"%.03f");
			}

			//remove marker as rest of fly is timer-only
			instruction->object->Delete();
			instruction->object=0;
		}
		else
			AutopilotSetSpeed(flyDirection*maxSpeed);

		break;
	case 3:
		//Fly on course by timer
		maxSpeed = instruction->value2;
		instruction->value3-=frameTime;
		if (instruction->value3<timeRotate)
		{
			//prepare for breaking in advance
			AutopilotRotate(-flyDirection);
		}
		if (instruction->value3<(maxSpeed/maxThrust))
		{
			if (instruction->prepareText)
				instruction->textInfo = L"Autopilot deceleration...";
			instruction->phase = 4;//deceleration
		}

		if (instruction->prepareText)
		{
			instruction->textInfo = L"Autopilot fly... ETA: ";
			instruction->textInfo += print_f64(instruction->value3,L"%.01f");
			
		}
		break;
	case 4:
		//Decelerate to zero
		return AutopilotSetSpeed(vector3d(0));
		break;
	default:
		break;

	}

	/*

	if (instruction->value3!=0 && AutopilotRotate(flyDirection))
	{

	}
	else
	{
	}*/
	return false;

	/*
	timeDeceleration = speedInDirection/maxThrust + 2.0;//2 is time of rotate to backward
	distanceForDeceleration = 0.5*maxThrust*timeDeceleration*timeDeceleration;
	if (distanceSQ>(distanceForDeceleration*distanceForDeceleration))
	{
		maxSpeed = 0.8*sqrt(2.0*sqrt(distanceSQ)*maxThrust);//-maxThrust*2.0;
		if (maxSpeed>(LIGHTSPEED*.5))
			maxSpeed=LIGHTSPEED*.5;
		flyDirection*=maxSpeed;
		AutopilotSetSpeed(flyDirection);
		return false;
	}
	else
	{
		flyDirection*=0.8*sqrt(2.0*sqrt(distanceSQ)*maxThrust);
		return AutopilotSetSpeed(flyDirection);
	}*/
}


void SpaceObject::UpdateMarkerNode(f64 cameraDistance)
{
	if (sceneMarkerNode)
	{
		f64 scale = .2*GetFloatProperty(MARKER_SIZE)*cameraDistance;///log(cameraDistance);
		//f32 scale = cameraDistance/(1.f*log(cameraDistance));
		//sceneMarkerNode->setSize(core::dimension2d<f32>(scale,scale));
		sceneMarkerNode->setScale(vector3df((f32)scale));
		//sceneMarkerNode->setB
		//sceneNode->setScale(vector3d(scale,scale,scale));
	}
}

void SpaceObject::UpdateMotionOnFTL(f64 time)
{
	bool breakFlag=false;
	f64 time2 = GetFloatProperty(FTL_REMAINING_TIME);
	if (time2>time)
		time2 = time;
	else
		breakFlag = true;
	vector3d position2 = position + speed*time2;
	AddFloatProperty(FTL_REMAINING_TIME,-time2);
	InfoFTL* checkFTL = physics->CheckFTLBreak(position,position2,GetFloatProperty(MAX_FTL_GRAVITY));
	if (checkFTL->breaked)
	{
		position = checkFTL->breakPoint;
		//motionType = MOTION_NAVIGATION;
		SetIntProperty(MOTION_TYPE,MOTION_NAVIGATION);
		BreakFTL(10.0);
		wprintf(L"Drop out from FTL due to high gravity\r\n");
		breakFlag = false;
	}
	else
	{
		position = position2;
	}
	if (breakFlag)
	{
		wprintf(L"Exit from FTL by timer\r\n");
		BreakFTL(100.0);
		//BreakFTL(0.0);//DEBUG
	}
	delete checkFTL; //new in CheckFTLBreak()

	//if (!(physics->IsFTLPossible(position)))
	//	motionType = MOTION_NAVIGATION;
}

void SpaceObject::UpdatePhysics(f64 time)
{
	vector3d acceleration = vector3d(0,0,0);
	vector3d prevSpeedVector;
	prevPosition = position;

	if (autopilotQueue.size()>0)
	{
		AutopilotInstruction* ins = autopilotQueue[0];
		switch (ins->instruction)
		{
		case AutopilotInstruction::AP_SETSPEED:
			if (AutopilotSetSpeed(vector3d(ins->vector1.X,ins->vector1.Y,0)))
			{
				delete ins;
				autopilotQueue.erase(0);
			}
			break;
		case AutopilotInstruction::AP_ORBITING:
			if (AutopilotOrbiting())
			{
				delete ins;
				autopilotQueue.erase(0);
			}
			break;
		case AutopilotInstruction::AP_FLY_TO:
			if (AutopilotFlyTo(ins,time))
			{
				delete ins;
				autopilotQueue.erase(0);
			}
			break;
		case AutopilotInstruction::AP_FTL_TO:
			if (AutopilotFTLTo(ins,time))
			{
				delete ins;
				autopilotQueue.erase(0);
			}
			break;
		case AutopilotInstruction::AP_FLY_TO_ORBIT:
			if (AutopilotFlyToOrbit(ins,time))
			{
				delete ins;
				autopilotQueue.erase(0);
			}
			break;
		case AutopilotInstruction::AP_HYPERSPACE_FLY_TO:
			if (AutopilotHyperFlyTo(ins,time))
			{
				delete ins;
				autopilotQueue.erase(0);
			}
			break;
		default:
			{
				//Delete unknown objectives
				delete ins;
				autopilotQueue.erase(0);
			}
			break;
		}
	}


	switch (GetIntProperty(MOTION_TYPE))
	{
	case MOTION_NONE:
		//do nothing;
		break;
	case MOTION_HYPER:
		{
			f64 speedLen = speed.getLength();
			//f64 twirl = physics->GetHyperSpaceTwirl()*time*0.00000002*speedLen;//about 500 ly raduius of minimum curvature if v<<c
			f64 twirl = physics->GetHyperSpaceTwirl(position)*time*0.00000002*speedLen;//about 500 ly raduius of minimum curvature if v<<c

			//f64 pseudoRelativisticKoeff=1.0 - speed.getLengthSQ()/(LIGHTSPEED*LIGHTSPEED);
			f64 pseudoRelativisticKoeff=1.0 - speedLen/LIGHTSPEED;
			f64 x=speed.X,y=speed.Y;
			if (pseudoRelativisticKoeff<1e-10) 
				pseudoRelativisticKoeff = 1e-10;
			twirl/=pseudoRelativisticKoeff*pseudoRelativisticKoeff*pseudoRelativisticKoeff; //max = 1e10
			//twirl speed ~3x at 0.3c, 8x at 0.5c, 125x at 0.8c, 1000x at 0.9c, 8000x at 0.95c, 1e6x at 0.99c
			
			f64 kx = cos(twirl),ky = sin(twirl);
			speed.X = kx*x-ky*y;
			speed.Y = kx*y+ky*x;
			//speed.rotateXYBy
		}
		//fall into navigation
	case MOTION_NAVIGATION:
		{
			//vector3d prevPosition;
			acceleration+=GetFloatProperty(THRUST_POWER)*GetDirection();

			//Simple Euler solving of differential equations
			if (GetIntProperty(AFFECTED_BY_GRAVITY)!=0)
			{
				acceleration += physics->GetGravityAcceleration(position);
			}
			AddFloatProperty(ROTATION_ANGLE,GetFloatProperty(ROTATION_SPEED)*time);
			
			prevSpeedVector = speed;
			speed += acceleration*time;

			//TODO: use LIGHTSPEED instead of fixed constants
			//TODO: optimize by getLengthSQ
			if (speed.getLength()>150000.0)
			{
				//above 0.5c - activate "relativistic" effects, lightspeed limit
				//effect is performed by 1) calculating relativistic momentum from previous speed
				//2) adding F*t to it 3) calculating new speed from new momentum
				//this is not really relativistic effect of external forces, but gives good effect of hard-to-achieve and hard-do-break of sub-lightspeeds
				//(instead of momentum calculated pseudo-momentum - without mass)
				f64 newSpeed;
				f64 pseudoRelativisticKoeff,pRIsq;
				vector3d pseudoRelativisticImpulse;

				//calc pseudoRelativisticImpulse from previous speed
				pseudoRelativisticKoeff = 1.0 - prevSpeedVector.getLengthSQ()/(LIGHTSPEED*LIGHTSPEED);
				if (pseudoRelativisticKoeff<1e-10) 
					pseudoRelativisticKoeff = 1e-10;
				pseudoRelativisticImpulse = prevSpeedVector/sqrt(pseudoRelativisticKoeff); //max = 1e5
				
				//add external forces by F*t
				pseudoRelativisticImpulse+=acceleration*time;

				//calc speed from new pseudoRelativisticImpulse
				pRIsq = pseudoRelativisticImpulse.getLengthSQ(); //pseudo relativistic impulse, square of len
				newSpeed = LIGHTSPEED*sqrt(pRIsq/(pRIsq + LIGHTSPEED*LIGHTSPEED));

				pseudoRelativisticImpulse.normalize();
				speed=pseudoRelativisticImpulse*newSpeed;

				//Adjust acceleration for further calculation of position shift
				if (time>0)
				{
					acceleration=(speed-prevSpeedVector)/time;
				}
				
			}
			//else
			position += speed*time + acceleration*time*time*.5;
			physics->CheckCollisions(this);
		}
		break;
	case MOTION_LINKED:
		{
			if (orbitingObject!=0)
			{
				vector3d linkRot = orbitingObject->GetDirection();
				position=orbitingObject->position;
				position.X+=linkPosition.X*linkRot.X-linkPosition.Y*linkRot.Y;
				position.Y+=linkPosition.Y*linkRot.X+linkPosition.X*linkRot.Y;
				SetFloatProperty(ROTATION_ANGLE,orbitingObject->GetFloatProperty(ROTATION_ANGLE)+GetFloatProperty(LINK_ROTATION_ANGLE));
			}
		}
		break;
	case MOTION_ORBITAL:
		{
			//simple circular orbiting
			f64 Phase = GetFloatProperty(ORBITAL_EPOCH_PHASE);
			if (GetFloatProperty(ORBITAL_PERIOD)!=0)
			{
				//Phase+=360.0*physics->globalTime/orbitalPeriod;
				Phase+=TWO_PI*physics->globalTime/GetFloatProperty(ORBITAL_PERIOD);
			}
			position.X = cos(Phase)*GetFloatProperty(ORBITAL_RADIUS);
			position.Y = sin(Phase)*GetFloatProperty(ORBITAL_RADIUS);
			position.Z = 0;
			if (orbitingObject!=0)
				position+=orbitingObject->position;
		}
		break;
	case MOTION_FTL:
		UpdateMotionOnFTL(time);
		break;
	case MOTION_PLUSMINUS:
		{

		}
		break;
	default:
		break;
	}

	switch(GetIntProperty(CURRENT_PROCESS))
	{
	case PROCESS_NONE:
		break;
	case PROCESS_STARGATE_OPENING:
		{
			//Opening in 1 second
			f64 phase = physics->globalTime - GetFloatProperty(PROCESS_START_TIME);
			f32 scale = (f32)(70.0*phase);
			if (phase>1)
			{
				scale = 70.0;
				SetFloatProperty(PROCESS_START_TIME,physics->globalTime);
				SetIntProperty(CURRENT_PROCESS,PROCESS_STARGATE_WAITING);
			}
			if (sceneNode)
				sceneNode->setScale(vector3df(scale));
		}
		break;
	case PROCESS_STARGATE_WAITING:
		{
			//Opening in 1 second
			f64 phase = physics->globalTime - GetFloatProperty(PROCESS_START_TIME);
			if (phase>15)
			{
				SetFloatProperty(PROCESS_START_TIME,physics->globalTime);
				SetIntProperty(CURRENT_PROCESS,PROCESS_STARGATE_CLOSING);
			}
		}
		break;
	case PROCESS_STARGATE_CLOSING:
		{
			//Closing in 1 second
			f64 phase = physics->globalTime - GetFloatProperty(PROCESS_START_TIME);
			f32 scale = (f32)(70.0*(1.0-phase));
			if (sceneNode)
				sceneNode->setScale(vector3df(scale));
			if (phase>1)
			{
				scale = 0.0;
				SetIntProperty(VISIBLE_TO_PLAYER,0);
				SetIntProperty(CURRENT_PROCESS,PROCESS_NONE);
				if (orbitingObject)
					orbitingObject->SetIntProperty(SpaceObject::ACTIVE,0);
				Delete();
			}
		}
		break;
	case PROCESS_DELAYED_DELETION:
		{
			if (physics->globalTime>GetFloatProperty(PROCESS_START_TIME))
				Delete();
		}
		break;
	case PROCESS_WORMHOLE_RESIZING:
		{
			if (physics->globalTime>GetFloatProperty(PROCESS_START_TIME))
			{
				f64 radius, maxRadius;
				core::array<SpaceObject*> foundObjects;
				physics->GetObjectsAtDistance(&foundObjects,position,100);//in 100 units range
				maxRadius = 0.01;
				for (u32 i = 0;i<foundObjects.size();i++)
				{
					if (foundObjects[i]!=this)
					{
						radius = foundObjects[i]->GetFloatProperty(GEOMETRY_RADIUS);
						if (radius>maxRadius) maxRadius = radius;
					}
				}
				SetFloatProperty(GRAVITY_MIN_RADIUS,maxRadius*10);
				/*
				radius = GetFloatProperty(GEOMETRY_RADIUS);
				if (radius<>maxRadius
				*/
				SetFloatProperty(PROCESS_START_TIME,physics->globalTime+1);

			}

			if (GetFloatProperty(GEOMETRY_RADIUS)!=GetFloatProperty(GRAVITY_MIN_RADIUS))
			{
				f64 radius = GetFloatProperty(GEOMETRY_RADIUS);
				f64 needRadius = GetFloatProperty(GRAVITY_MIN_RADIUS);
				if (radius<needRadius)
				{
					radius*=exp(time);
					if (radius>needRadius)
						radius = needRadius;
				}
				else
				{
					radius*=exp(-time);
					if (radius<needRadius)
						radius = needRadius;
				}
				if (sceneNode)
					sceneNode->setScale(vector3df((f32)(radius*1.429)));
				SetFloatProperty(SpaceObject::GEOMETRY_RADIUS,radius);//Distance to check passing thru circle

			}
		}
		break;
	}

}


vector3d SpaceObject::GetSpeed()
{
	switch (GetIntProperty(MOTION_TYPE))
	{
	case MOTION_ORBITAL:
		{
			//simple circular orbiting
			if (GetFloatProperty(ORBITAL_PERIOD)!=0)
			{
				f64 Phase = GetFloatProperty(ORBITAL_EPOCH_PHASE);
				f64 speedValue = GetFloatProperty(ORBITAL_RADIUS)*TWO_PI/GetFloatProperty(ORBITAL_PERIOD);
				//Phase+=360.0*physics->globalTime/orbitalPeriod;
				Phase+=TWO_PI*physics->globalTime/GetFloatProperty(ORBITAL_PERIOD);
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
	case MOTION_LINKED:
		{
			if (orbitingObject!=0)
				speed=orbitingObject->GetSpeed();
		}

		break;
	default:
		break;
	}
	return speed;
}

//Estimation of object movement in future or past
//Creates new SpaceObject which have: position, speed, ROTATION_ANGLE, ROTATION_SPEED
//other properties should not be readed by caller function
//caller function is responsible for deletion of returned object
SpaceObject* SpaceObject::GetEstimation(f64 atTime)
{
	SpaceObject* estimation = new SpaceObject();//delete in caller function

	switch (GetIntProperty(MOTION_TYPE))
	{
	case MOTION_NONE:
		estimation->speed = speed;
		estimation->position = position;
		estimation->SetFloatProperty(ROTATION_ANGLE,GetFloatProperty(ROTATION_ANGLE));
		estimation->SetFloatProperty(ROTATION_SPEED,GetFloatProperty(ROTATION_SPEED));
		//do nothing;
		break;
	case MOTION_NAVIGATION:
	case MOTION_FTL:
		{
			f64 rotAngle;
			estimation->speed = speed;
			estimation->position = position+speed*(atTime-physics->globalTime);
			rotAngle = GetFloatProperty(ROTATION_ANGLE)+GetFloatProperty(ROTATION_SPEED)*(atTime-physics->globalTime);
			estimation->SetFloatProperty(ROTATION_ANGLE,rotAngle);
			estimation->SetFloatProperty(ROTATION_SPEED,GetFloatProperty(ROTATION_SPEED));
		}
		break;
	case MOTION_LINKED:
		{
			if (orbitingObject!=0)
			{
				SpaceObject* estOrbiting = orbitingObject->GetEstimation(atTime);
				vector3d linkRot = estOrbiting->GetDirection();
				estimation->position=estOrbiting->position;
				estimation->position.X+=linkPosition.X*linkRot.X-linkPosition.Y*linkRot.Y;
				estimation->position.Y+=linkPosition.Y*linkRot.X+linkPosition.X*linkRot.Y;
				estimation->SetFloatProperty(ROTATION_ANGLE,estOrbiting->GetFloatProperty(ROTATION_ANGLE)+GetFloatProperty(LINK_ROTATION_ANGLE));
				delete estOrbiting;
			}
			else
			{
				estimation->speed = speed;
				estimation->position = position;
				estimation->SetFloatProperty(ROTATION_ANGLE,GetFloatProperty(ROTATION_ANGLE));
				estimation->SetFloatProperty(ROTATION_SPEED,GetFloatProperty(ROTATION_SPEED));
			}
		}
		break;
	case MOTION_ORBITAL:
		{
			//simple circular orbiting
			f64 Phase = GetFloatProperty(ORBITAL_EPOCH_PHASE);
			f64 orbitRadius = GetFloatProperty(ORBITAL_RADIUS);
			f64 orbitPeriod = GetFloatProperty(ORBITAL_PERIOD);
			if (GetFloatProperty(ORBITAL_PERIOD)!=0)
			{
				f64 speedValue = orbitRadius*TWO_PI/orbitPeriod;
				//Phase+=360.0*physics->globalTime/orbitalPeriod;
				Phase+=TWO_PI*atTime/orbitPeriod;
				estimation->speed.X = -sin(Phase)*speedValue;
				estimation->speed.Y = cos(Phase)*speedValue;
				estimation->speed.Z = 0;
			}
			else
			{
				estimation->speed = vector3d(0);
			}
			estimation->position.X = cos(Phase)*orbitRadius;
			estimation->position.Y = sin(Phase)*orbitRadius;
			estimation->position.Z = 0;
			if (orbitingObject!=0)
			{
				SpaceObject* estOrbiting = orbitingObject->GetEstimation(atTime);
				estimation->position+=estOrbiting->position;
				estimation->speed+=estOrbiting->speed;
				delete estOrbiting;
			}
		}
		break;
	default:
		break;
	}

	return estimation;
}

void SpaceObject::SetNode(SceneNode * node)
{
	sceneNode = node;
	if (node)
		sceneNode->setVisible(GetIntProperty(VISIBLE_TO_PLAYER)!=0);
}

void SpaceObject::SetMarkerNode(SceneNode * node, f64 size)
{
	sceneMarkerNode = node;
	SetFloatProperty(MARKER_SIZE,size);
	if (node)
		sceneMarkerNode->setVisible(GetIntProperty(VISIBLE_TO_PLAYER)!=0);
}

void SpaceObject::SetIntProperty(IntProperty propertyNumber, s32 newValue)
{
	IntProperties[propertyNumber]=newValue;
	switch(propertyNumber)
	{
	case VISIBLE_TO_PLAYER:
		if (sceneNode)
			sceneNode->setVisible(newValue!=0);
		if (sceneMarkerNode)
			sceneMarkerNode->setVisible(newValue!=0);
		break;
	default:
		break;
	}
}

void SpaceObject::SetFloatProperty(FloatProperty propertyNumber, f64 newValue)
{
	FloatProperties[propertyNumber]=newValue;
}

void SpaceObject::AddFloatProperty(FloatProperty propertyNumber, f64 addValue)
{
	FloatProperties[propertyNumber]+=addValue;
}


vector3d SpaceObject::GetGravityAcceleration(vector3d location)
{
	vector3d vectorDirection = position-location;
	f64 distance = vectorDirection.getLength();
	f64 gravityRadius = GetFloatProperty(GRAVITY_MIN_RADIUS);
	if (distance<gravityRadius)
	{
		//Inside object - linear from radius to gravity on surface
		return G_CONSTANT*vectorDirection*GetFloatProperty(MASS)/(gravityRadius*gravityRadius*gravityRadius);
	}
	//Outside object - by Newton's law
	return G_CONSTANT*vectorDirection*GetFloatProperty(MASS)/(distance*distance*distance);
}

//X-gravity = G*M/R^4
vector3d SpaceObject::GetXGravityAcceleration(vector3d location)
{
	vector3d vectorDirection = position-location;
	f64 distance = vectorDirection.getLength();
	if (distance<GetFloatProperty(GRAVITY_MIN_RADIUS))
	{
		//Inside object - very big
		return G_CONSTANT*vectorDirection*GetFloatProperty(MASS);
	}
	//Outside object - G*M/R*R*R*R
	return G_CONSTANT*vectorDirection*GetFloatProperty(MASS)/(distance*distance*distance*distance*distance);
}


//Breaking relative to distant-stars
bool SpaceObject::AutopilotOrbiting()
{
	
	f64 requiredRelativeSpeed;
	vector3d maxGravityAcceleration;
	vector3d relativePosition;
	vector3d relativeSpeed;
	vector3d requiredSpeed;

	//Get gravity info from game physics
	GravityInfo* gravInfo = physics->GetGravityInfo(position);
	if (gravInfo->maxGravityObject)
	{//only if there is dominant object
		
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
		return AutopilotSetSpeed(requiredSpeed);
	}
	delete gravInfo;//new in GamePhysics::GetGravityInfo
	return true;
}

void SpaceObject::JumpToFTL(f64 ftlSpeed)
{
	//motionType = MOTION_FTL;
	SetIntProperty(MOTION_TYPE,MOTION_FTL);
	//speed.normalize();
	speed = GetDirection();
	speed*=ftlSpeed*LIGHTSPEED;
}

void SpaceObject::BreakFTL(f64 remainingSpeed)
{
	//motionType = MOTION_NAVIGATION;
	SetIntProperty(MOTION_TYPE,MOTION_NAVIGATION);
	speed.normalize();
	speed*=remainingSpeed;
}


void SpaceObject::FallIntoWormhole(SpaceObject* wormhole)
{
	wprintf(L"DG: %ws fall into %ws\r\n",this->GetName().c_str(),wormhole->GetName().c_str());
	Delete();
	return;
}

void SpaceObject::FallIntoStargate(SpaceObject* wormhole)
{
	wprintf(L"DG: %ws fall into %ws\r\n",this->GetName().c_str(),wormhole->GetName().c_str());
	Delete();
	return;
}

void SpaceObject::AddAutopilot(AutopilotInstruction* instruction)
{
	autopilotQueue.push_back(instruction);
}

void SpaceObject::BreakAutopilot()
{
	if (autopilotQueue.size()>0)
		wprintf(L" Removed %i autopilot instructions\r\n",autopilotQueue.size());

	for (u32 i = 0;i<autopilotQueue.size();i++)
	{
		delete autopilotQueue[i];
	}
	autopilotQueue.clear();
}

text_string SpaceObject::GetAutopilotInfo()
{
	if (autopilotQueue.size()>0)
		if (autopilotQueue[0]->prepareText)
			if (autopilotQueue[0]->textInfo!=0)
				return autopilotQueue[0]->textInfo;
	return L"";
}

SpaceObject* SpaceObject::FireProjectile()
{
	SpaceObject* projectile;
	physics->GetRoot()->UseSceneManager(DG_Game::VIEW_REALSPACE);
	projectile = physics->GetRoot()->GetResourceManager()->MakeProjectile();

	projectile->position = position + GetDirection()*1;
	//projectile->SetSpeed(speed + GetDirection()*LIGHTSPEED*0.01);
	//projectile->SetSpeed(speed + GetDirection()*300.0);
	projectile->SetSpeed(speed + GetDirection()*30000.0);
	projectile->SetName(text_string(L"plasma ball"));
	
	/*
	projectile->SetIntProperty(CURRENT_PROCESS,PROCESS_DELAYED_DELETION);
	projectile->SetFloatProperty(PROCESS_START_TIME,physics->globalTime+10);
	DEBUG!
	*/

	return projectile;
	
}

void SpaceObject::Delete()
{
	physics->RemoveObject(this);
}

//#########################################################################
//GamePhysics

GamePhysics::GamePhysics()
{
	calcCollisions = false;
	//hyperSpaceTwirlChangeTime=0;
	//hyperSpaceTwirl=0;
	hyperSpaceTwirlAnchor= vector2ds(1,1);
	hyperSpaceTwirl11 = 0;
	hyperSpaceTwirl21 = 0;
	hyperSpaceTwirl12 = 0;
	hyperSpaceTwirl22 = 0;
}

GamePhysics::~GamePhysics()
{
	playerShip = 0;
	ClearObjects();
}


void GamePhysics::SetTimeSpeed(f64 newSpeed)
{
	timeSpeed = newSpeed;
	wprintf(L"DG: timespeed is %f\r\n",timeSpeed);
}


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

//flags: 1 - update visibility also
void GamePhysics::UpdateNodes(SpaceObject* centerSceneObject, u32 flags)
{
	u32 i;
	if ((flags&1)!=0)
	{
		for (i=0;i<listObjects.size();i++)
		{
			//SpaceObjectList[i]->UpdatePhysics(time);
			listObjects[i]->UpdateSceneNode(centerSceneObject);
			listObjects[i]->UpdateVisibility(centerSceneObject);
		}
	}
	else
	{
		for (i=0;i<listObjects.size();i++)
		{
			//SpaceObjectList[i]->UpdatePhysics(time);
			listObjects[i]->UpdateSceneNode(centerSceneObject);
		}
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

void GamePhysics::RemoveObject(SpaceObject* removedObject)
{
	s32 index = listObjects.linear_search(removedObject);
	if (index<0)
		return;//nothing to delete;

	delete listObjects[index];
	listObjects[index] = 0;
	listObjects.erase(index);

}

void GamePhysics::SetGalaxyCoordinatesOfCenter(vector2d newCoordinates)
{
	vector2d oldGalaxyCoords = galaxyCoordinatesOfCenter;
	galaxyCoordinatesOfCenter = newCoordinates;
	if (isInterstellar)
	{
		oldGalaxyCoords-=galaxyCoordinatesOfCenter;
		oldGalaxyCoords*=LIGHTYEAR;
		vector3d shift = vector3d(oldGalaxyCoords.X,oldGalaxyCoords.Y,0);
		for (u32 i=0;i<listObjects.size();i++)
		{
			listObjects[i]->SetPosition(listObjects[i]->GetPosition()+shift);
			listObjects[i]->BreakAutopilot();
		}
	}
}

vector3d GamePhysics::GetGravityAcceleration(vector3d location)
{
	u32 i;
	vector3d acceleration = vector3d(0,0,0);
	for (i=0;i<listObjects.size();i++)
		//if (listObjects[i]->IsEmittingGravity())
		if (listObjects[i]->GetIntProperty(SpaceObject::EMIT_GRAVITY)!=0)
		{
			//vector3d vectorDirection = SpaceObjectList[i]->GetPosition()-location;
			//f64 distance = vectorDirection.getLength();
			//acceleration += 66.7*vectorDirection*SpaceObjectList[i]->GetMass()/(distance*distance*distance);
			acceleration += listObjects[i]->GetGravityAcceleration(location);
		}
	return acceleration;
}

vector3d GamePhysics::GetXGravityAcceleration(vector3d location)
{
	u32 i;
	vector3d acceleration = vector3d(0,0,0);
	for (i=0;i<listObjects.size();i++)
		//if (listObjects[i]->IsEmittingGravity())
		if (listObjects[i]->GetIntProperty(SpaceObject::EMIT_GRAVITY)!=0)
		{
			acceleration += listObjects[i]->GetXGravityAcceleration(location);
		}
	return acceleration;
}


//Find random location where log of gravity is in range (gravityMin, gravityMax)
//Iterative solving of equation F(x) = a by finding slope of F(x)
vector3d GamePhysics::FindRandomLocationWithSpecificGravity(f64 gravityMin, f64 gravityMax)
{
	u32 i,j;
	vector3d result;
	vector3d gravity;
	f64 grav,gravSQ,grav2SQ;
	f64 pseudoRadius;
	f64 gravityDest;

	pseudoRadius = LIGHTYEAR*STAR_SYSTEM_RADIUS*0.75;

	//make 5 attempts
	for (j=0;j<5;j++)
	{
		//make start location of iterations
		f64 angle = GlobalURNG::Instance().GenerateByte()*TWO_PI/255.0;//random angle
		result = vector3d(pseudoRadius*cos(angle),pseudoRadius*sin(angle),0);

		//TODO: check for gravity at all

		//Random desirable gravity - somewhere in range (gravityMin, gravityMax)
		//Simple average of gravityMin and gravityMax is not good, as algorithm will very often will find solution at once
		gravityDest = gravityMin + GlobalURNG::Instance().GenerateByte() * (gravityMax-gravityMin)/255.0;
		
		//100 iterations (2 works in >50%, never seen >4)
		for (i=0;i<100;i++)
		{
			//Get gravity force
			gravity = GetGravityAcceleration(result);

			//Calc square of modulus
			gravSQ = gravity.getLengthSQ();

			//Calc log of modulus
			grav = 0.5*log(gravSQ);

			wprintf(L" * FRLWSG: %f\r\n",grav);//print intermediate gravity
			
			//Check for result
			if (grav>=gravityMin && grav<=gravityMax)
				return result;

			//Normalization of vector (basic .normalize() does not work due to very small value )
			gravity /= gravity.getLength();

			//Get gravity force in 1 unit aside
			grav2SQ = GetGravityAcceleration(result+gravity).getLengthSQ();

			gravSQ = pow(gravSQ,-0.25);//pre-calc value which is required twice

			//Shift location by distance, calculcated from 3 gravity values: current, 1 unit aside, and desired
			//Direction of shift is defined by gravity vector
			//In case of 1 gravity body, this will give exact solution
			result += gravity*(exp(-0.5*gravityDest)-gravSQ)/(pow(grav2SQ,-0.25)-gravSQ);

		}
	}
	//Very hard star system, solution not found in 5x100 iterations
	wprintf(L"WARNING: FRLWSG does not finished with solution, grav=%f\r\n",grav);
	return result;
}

//Find random location where log of X-gravity is in range (gravityMin, gravityMax)
//Iterative solving of equation F(x) = a by finding slope of F(x)
vector3d GamePhysics::FindRandomLocationWithSpecificXGravity(f64 gravityMin, f64 gravityMax)
{
	u32 i,j;
	vector3d result;
	vector3d gravity;
	f64 grav,gravSQ,grav2SQ;
	f64 pseudoRadius;
	f64 gravityDest;

	pseudoRadius = LIGHTYEAR*STAR_SYSTEM_RADIUS*0.75;

	//make 5 attempts
	for (j=0;j<5;j++)
	{
		//make start location of iterations
		f64 angle = GlobalURNG::Instance().GenerateByte()*TWO_PI/255.0;//random angle
		result = vector3d(pseudoRadius*cos(angle),pseudoRadius*sin(angle),0);

		//TODO: check for gravity at all

		//Random desirable gravity - somewhere in range (gravityMin, gravityMax)
		//Simple average of gravityMin and gravityMax is not good, as algorithm will very often will find solution at once
		gravityDest = gravityMin + GlobalURNG::Instance().GenerateByte() * (gravityMax-gravityMin)/255.0;
		
		//100 iterations (2 works in >50%, never seen >4)
		for (i=0;i<100;i++)
		{
			//Get gravity force
			gravity = GetXGravityAcceleration(result);

			//Calc square of modulus
			gravSQ = gravity.getLengthSQ();

			//Calc log of modulus
			grav = 0.5*log(gravSQ);

			wprintf(L" * FRLWSXG: %f\r\n",grav);//print intermediate gravity
			
			//Check for result
			if (grav>=gravityMin && grav<=gravityMax)
				return result;

			//Normalization of vector (basic .normalize() does not work due to very small value )
			gravity /= gravity.getLength();

			//Get gravity force in 1 unit aside
			grav2SQ = GetXGravityAcceleration(result+gravity).getLengthSQ();

			gravSQ = pow(gravSQ,-0.125);//pre-calc value which is required twice

			//Shift location by distance, calculcated from 3 gravity values: current, 1 unit aside, and desired
			//Direction of shift is defined by gravity vector
			//In case of 1 gravity body, this will give exact solution
			result += gravity*(exp(-0.25*gravityDest)-gravSQ)/(pow(grav2SQ,-0.125)-gravSQ);

		}
	}
	//Very hard star system, solution not found in 5x100 iterations
	wprintf(L"WARNING: FRLWSXG does not finished with solution, grav=%f\r\n",grav);
	return result;
}


GravityInfo* GamePhysics::GetGravityInfo(vector3d location)
{
	u32 i;
	//text_string gravityInfo(L"");
	f64 gravity;

	GravityInfo* gravInfo = new GravityInfo();//delete must be in called
	
	f64 maxGravity=-1;
	SpaceObject* maxGravityObject =0;
	f64 secondMaxGravity=-1;
	SpaceObject* secondMaxGravityObject =0;
	//f64 orbitSemimajorAxis, orbitEccentricity;


	for (i=0;i<listObjects.size();i++)
		//if (listObjects[i]->IsEmittingGravity())
		if (listObjects[i]->GetIntProperty(SpaceObject::EMIT_GRAVITY)!=0)
		{
			//vector3d vectorDirection = SpaceObjectList[i]->GetPosition()-location;
			//f64 distance = vectorDirection.getLength();
			//gravity = (vectorDirection*SpaceObjectList[i]->GetMass()/(distance*distance*distance)).getLength();

			//TODO: speedup by getLengthSQ. sqrt() can by applied at the end
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

bool GamePhysics::IsPlusMinusPossible(vector3d location)
{
	if (isInterstellar)
		return true;
	if (location.getLengthSQ()>maxGravityCheckRadiusSQ)
		return true;

	f64 grav = log(GetXGravityAcceleration(location).getLength());
	if (grav>XGRAVITY_MAX_PLUSMINUS)
		return false;
	return true;
}


InfoFTL* GamePhysics::CheckFTLBreak(vector3d start, vector3d end, f64 gravityLimit)
{
	InfoFTL* info = new InfoFTL();//delete must be in caller scope
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
		//vector3d perpendicularMoving = vector3d(moving.Y,-moving.X,0);
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
			//if (listObjects[i]->IsEmittingGravity())
			if (listObjects[i]->GetIntProperty(SpaceObject::EMIT_GRAVITY)!=0)
			{
				criticalRadiusSQ = criticalRadiusSQToMass*listObjects[i]->GetFloatProperty(SpaceObject::MASS);
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
	ClearObjects();
	
	isInterstellar=true;
	//listObjects.push_back((SpaceObject*)playerShip);
//	AddObject(playerShip);
}

void GamePhysics::GoStarSystem()
{
	ClearObjects();//listObjects.clear();
	isInterstellar = false;
//	AddObject(playerShip);
}

void GamePhysics::Activate()
{
	calcCollisions = false;
	Update(0);//relocate stars, planets and so on
	calcCollisions = true;
}

void GamePhysics::GoHyperSpace()
{
	ClearObjects();//listObjects.clear();
	isInterstellar = false;
}

void GamePhysics::ClearObjects()
{
	if (playerShip)
		playerShip->BreakAutopilot();//All objects removed, any object-related autopilot would crush

	for (u32 i=0;i<listObjects.size();i++)
	{
		if (listObjects[i]!=playerShip)
		{
			delete listObjects[i];
			listObjects[i] = 0;
		}
	}
	listObjects.clear();
	if (playerShip)
		AddObject(playerShip);
}

void GamePhysics::CheckCollisions(SpaceObject* object)
{
	u32 i;
	f64 minDistance;
	vector3d collisionDist;
	if (!calcCollisions)
		return;
	for (i=0;i<listObjects.size();i++)
	{
		if (listObjects[i]->GetIntProperty(SpaceObject::COLLISIONS_CHECK)==0)
			continue;

		if (listObjects[i]==object)
			continue;//Skip same object

		if (listObjects[i]->GetIntProperty(SpaceObject::WORMHOLE)!=0)
		{
			//f64 projectedDistance;
			vector3d curVector = object->GetPosition()-listObjects[i]->GetPosition();
			vector3d prevVector = object->GetPrevPosition()-listObjects[i]->GetPrevPosition();
			vector3d wormholeDirection = listObjects[i]->GetDirection();
			vector3d wormholeNormale = vector3d(wormholeDirection.Y,-wormholeDirection.X,0);
			if (curVector.dotProduct(wormholeNormale)*prevVector.dotProduct(wormholeNormale)<=0)
			{
				//object cross wormhole plane - should check distance of cross to center of wormhole
				
				//calc: shift = pos - prevpos, fall = gate + axis*y, fall = pos + shift*x, y = [pos-gate,shift]/[axis,shift]
				vector3d shift = object->GetPosition()-object->GetPrevPosition();
				f64 fallLocation = (shift.X*curVector.Y-shift.Y*curVector.X)/(shift.X*wormholeDirection.Y-shift.Y*wormholeDirection.X);
				if (fabs(fallLocation)<listObjects[i]->GetFloatProperty(SpaceObject::GEOMETRY_RADIUS))
				{
					object->FallIntoWormhole(listObjects[i]);
					return;//no more collisions expected
				}
			}
			continue;//wormhole, other cases of collision should not be checked
		}

		if (listObjects[i]->GetIntProperty(SpaceObject::STARGATE)!=0)
		{
			if (listObjects[i]->GetIntProperty(SpaceObject::STARGATE)!=2)
				continue; //skip stargate body, proceede with event horizon only

			if (listObjects[i]->GetIntProperty(SpaceObject::CURRENT_PROCESS)!=SpaceObject::PROCESS_STARGATE_WAITING)
				continue; //skip closed/opening/closing wormholes

			vector3d curVector = object->GetPosition()-listObjects[i]->GetPosition();
			vector3d prevVector = object->GetPrevPosition()-listObjects[i]->GetPrevPosition();
			vector3d stargateNormale = listObjects[i]->GetDirection();
			
			if (curVector.dotProduct(stargateNormale)*prevVector.dotProduct(stargateNormale)<=0)
			{
				//object cross stargate plane - should check distance of cross to center of gate
				vector3d stargateDirection = vector3d(stargateNormale.Y,-stargateNormale.X,0);
				vector3d shift = object->GetPosition()-object->GetPrevPosition();
				f64 fallLocation = (shift.X*curVector.Y-shift.Y*curVector.X)/(shift.X*stargateDirection.Y-shift.Y*stargateDirection.X);
				if (fabs(fallLocation)<listObjects[i]->GetFloatProperty(SpaceObject::GEOMETRY_RADIUS))
				{
					if (listObjects[i]->GetIntProperty(SpaceObject::TRAVEL_TO_X)<-65536)
					{//bounce to event horizon of output stargate
						wprintf(L"DG: %ws bounce on event horizon of output stargate\r\n",object->GetName().c_str());
						
						f64 perpendicularSpeed = stargateNormale.dotProduct(object->GetSpeed()-listObjects[i]->GetSpeed());
						//object->SetPosition(object->GetPrevPosition() + listObjects[i]->GetPosition()-listObjects[i]->GetPrevPosition()); //return object to prev position and shift for vector of movement of listObjects[i]
						object->SetPosition(object->GetPosition() + listObjects[i]->GetPosition()-listObjects[i]->GetPrevPosition()-2.0*stargateNormale*stargateNormale.dotProduct(curVector)); 
						object->SetSpeed(object->GetSpeed()-2.0*perpendicularSpeed*stargateNormale);
						continue; //no more collisions expected
					}
					listObjects[i]->SetFloatProperty(SpaceObject::PROCESS_START_TIME,globalTime);//reset stargate closing timer
					object->FallIntoStargate(listObjects[i]);
					return;//no more collisions expected
				}
			}
			continue;//stargate, other cases of collision should not be checked
		}


		//distance = (object->GetPosition()-listObjects[i]->GetPosition()).getLengthSQ();
		minDistance = (object->GetFloatProperty(SpaceObject::GEOMETRY_RADIUS)+listObjects[i]->GetFloatProperty(SpaceObject::GEOMETRY_RADIUS));
		minDistance*=minDistance;
		
		if ((object->GetPosition()-listObjects[i]->GetPosition()).getLengthSQ() < minDistance)
		{
			wprintf(L"DG: collision %ws with %ws\r\n",object->GetName().c_str(),listObjects[i]->GetName().c_str());
		}
	}
	return;
}

//Find wormhole to specific star system (if there is one)
SpaceObject* GamePhysics::GetWormholeTo(vector2ds galaxyQuadrant)
{
	u32 i;
	for (i=0;i<listObjects.size();i++)
		if (listObjects[i]->GetIntProperty(SpaceObject::WORMHOLE)!=0)
			if (listObjects[i]->GetIntProperty(SpaceObject::TRAVEL_TO_X)==galaxyQuadrant.X)
				if (listObjects[i]->GetIntProperty(SpaceObject::TRAVEL_TO_Y)==galaxyQuadrant.Y)
				{
					return listObjects[i];
				}
	return 0;//No such wormhole
}

//Find first object with specific value of property
SpaceObject* GamePhysics::GetFirstObject(SpaceObject::IntProperty prop, s32 value)
{
	u32 i;
	for (i=0;i<listObjects.size();i++)
		if (listObjects[i]->GetIntProperty(prop)==value)
			{
				return listObjects[i];
			}
	return 0;//No such object
}


void GamePhysics::DebugJumpToWormhole(u32 param)
{
	u32 i;
	u32 wormholesCount;
	u32 wormholeTo;
	f64 maxDist, dist;
	vector3d teleportTo;
	vector3d shift;

	if (param==0)
	{
		//v1 - random
		wormholesCount = 0;
		for (i=0;i<listObjects.size();i++)
		{
			if (listObjects[i]->GetIntProperty(SpaceObject::WORMHOLE)!=0)
				//if (listObjects[i]->GetPosition().X>0)
					wormholesCount++;
		}

		if (wormholesCount<1)
			return;//nothing to do

		wormholeTo = GlobalURNG::Instance().GenerateByte();//random angle
		wormholeTo = wormholeTo%wormholesCount;//not very uniform, but still;
		
		wormholesCount=0;
		for (i=0;i<listObjects.size();i++)
		{
			if (listObjects[i]->GetIntProperty(SpaceObject::WORMHOLE)!=0)
				//if (listObjects[i]->GetPosition().X>0)
				{
					if (wormholesCount==wormholeTo)
					{
						teleportTo  = listObjects[i]->GetPosition();
						break;
					}
					wormholesCount++;
				}
		}
	}
	else
	{

		//v2 - closest to direction of ship
		maxDist = -1e60;
		for (i=0;i<listObjects.size();i++)
		{
			if (listObjects[i]->GetIntProperty(SpaceObject::WORMHOLE)!=0)
			{
				shift = listObjects[i]->GetPosition();
				dist = shift.dotProduct(playerShip->GetDirection());//maximum if directions coincides
				if (dist>maxDist)
				{
					teleportTo = shift;
					maxDist = dist;
				}
			}
		}
	}
	

	//if (wormholesCount<1)
	//	return;//nothing to do

	shift = teleportTo;
	shift.normalize();
	teleportTo -= shift*30;

	playerShip->SetPosition(teleportTo);
	if (param==0)
	{
		playerShip->SetSpeed(shift*30.0);
	}
	else
	{
		playerShip->SetSpeed(shift*2000.0);
	}
	//playerShip->SetSpeed(vector3d(100.0,-100.0,0));
}

void GamePhysics::SendStargateAddress(SpaceObject* sender, u64 address)
{
	u32 stargatePresence;
	SpaceObject* destGate;
	vector2ds coordinates;
	coordinates = gameRoot->GetGalaxy()->StargateAddress2Coordinates(address);

	//destGate = GetFirstObject(SpaceObject::STARGATE,2);
	destGate = GetFirstObject(SpaceObject::STARGATE,1);
	if (destGate==0 || (sender->GetPosition()-destGate->GetPosition()).getLengthSQ()>1e8)
	{
		wprintf(L" ** Nothing happens\r\n");
		return;
	}

	if (galaxyQuadrant == coordinates)
	{
		wprintf(L" ** Stargate instantly respond that it is their address\r\n");
		return;
	}

	if (destGate->GetIntProperty(SpaceObject::ACTIVE)!=0)
	{
		wprintf(L" ** Stargate instantly respond that they are busy\r\n");
		return;
	}

	if (coordinates.X<-65536)
	{
		if (coordinates.Y==1)
			wprintf(L" ** After a small pause stargate respond that address is incorrect\r\n");
		else
			wprintf(L" ** Stargate instantly respond that address is incorrect\r\n");
		return;
	}

	wprintf(L" ** ** Stargate activating to (%i,%i)...\r\n",coordinates.X,coordinates.Y);//DEBUG!
	stargatePresence = gameRoot->GetGalaxy()->CheckStargatePresence(coordinates,true);
	if (stargatePresence==0)
	{
		wprintf(L" ** Stargate activated, but not opened. A bit later came response was that address is incorrect\r\n");
		return;
	}
	if (stargatePresence==2)
	{
		wprintf(L" ** Stargate activated, but not opened. After a second came strange response. You cannot decode it\r\n");
		return;
	}

	wprintf(L" ** Stargate activated and opened\r\n");

	/*

	destGate->SetIntProperty(SpaceObject::VISIBLE_TO_PLAYER,1);
	destGate->SetIntProperty(SpaceObject::CURRENT_PROCESS,SpaceObject::PROCESS_STARGATE_OPENING);
	destGate->SetIntProperty(SpaceObject::TRAVEL_TO_X,coordinates.X);
	destGate->SetIntProperty(SpaceObject::TRAVEL_TO_Y,coordinates.Y);
	destGate->SetFloatProperty(SpaceObject::PROCESS_START_TIME,globalTime);
	*/
	destGate->SetIntProperty(SpaceObject::ACTIVE,1);

	gameRoot->UseSceneManager(DG_Game::VIEW_REALSPACE);
	SpaceObject* eventHorizon = gameRoot->GetResourceManager()->MakeStargateEH();
	eventHorizon->SetLinkedParams(destGate,vector3d(13.0,0,0),0);
	eventHorizon->SetIntProperty(SpaceObject::VISIBLE_TO_PLAYER,1);
	eventHorizon->SetIntProperty(SpaceObject::CURRENT_PROCESS,SpaceObject::PROCESS_STARGATE_OPENING);
	eventHorizon->SetIntProperty(SpaceObject::TRAVEL_TO_X,coordinates.X);
	eventHorizon->SetIntProperty(SpaceObject::TRAVEL_TO_Y,coordinates.Y);
	eventHorizon->SetFloatProperty(SpaceObject::PROCESS_START_TIME,globalTime);

	return;
}

void GamePhysics::GetObjectsAtDistance(core::array<SpaceObject*>* list, vector3d location, f64 distance)
{
	f64 distSQ = distance*distance;
	list->clear();
	u32 i;
	for (i=0;i<listObjects.size();i++)
	{
		if ((location-listObjects[i]->GetPosition()).getLengthSQ()<distSQ)
		{
			list->push_back(listObjects[i]);
		}
	}
}

/*
f64 GamePhysics::GetHyperSpaceTwirl()
{
	//TODO: twirl should depends on galaxy coords, not be timer-random

	if (globalTime>hyperSpaceTwirlChangeTime)
	{
		hyperSpaceTwirl = 2.0*GlobalURNG::Instance().GenerateByte()/255.0-1.0;
		hyperSpaceTwirlChangeTime = globalTime+5;
	}
	return hyperSpaceTwirl;
	//return 1.0;//DEBUG
}*/

f64 GamePhysics::GetHyperSpaceTwirl(vector3d atPosition)
{
	//NOTE: optimal only for one objects in HyperSpace
	vector2d galaxyPos;
	vector2ds galaxyQuadrant;
	galaxyPos.X = atPosition.X*HYPERSPACE_SCALE/LIGHTYEAR;
	galaxyPos.Y = atPosition.Y*HYPERSPACE_SCALE/LIGHTYEAR;
	galaxyQuadrant.X = (s32)(galaxyPos.X)&0xFFFFFFF0;
	galaxyQuadrant.Y = (s32)(galaxyPos.Y)&0xFFFFFFF0;
	if (galaxyQuadrant!=hyperSpaceTwirlAnchor)
	{
		Galaxy* currentGalaxy = gameRoot->GetGalaxy();
		vector2ds galaxyQuad2 = galaxyQuadrant;
		hyperSpaceTwirlAnchor = galaxyQuadrant;
		hyperSpaceTwirl11 = currentGalaxy->GetHyperSpaceTwirl(galaxyQuad2);
		galaxyQuad2.X+=16;
		hyperSpaceTwirl21 = currentGalaxy->GetHyperSpaceTwirl(galaxyQuad2);
		galaxyQuad2.X=galaxyQuadrant.X;
		galaxyQuad2.Y+=16;
		hyperSpaceTwirl12 = currentGalaxy->GetHyperSpaceTwirl(galaxyQuad2);
		galaxyQuad2.X+=16;
		hyperSpaceTwirl22 = currentGalaxy->GetHyperSpaceTwirl(galaxyQuad2);
	}
	galaxyPos.X-=galaxyQuadrant.X;
	galaxyPos.Y-=galaxyQuadrant.Y;
	galaxyPos*=0.0625;// divide by 16
	//return GetHyperSpaceTwirl();//TEMP
	return hyperSpaceTwirl11+galaxyPos.X*(hyperSpaceTwirl21-hyperSpaceTwirl11)+
		galaxyPos.Y*(hyperSpaceTwirl12-hyperSpaceTwirl11)+
		galaxyPos.X*galaxyPos.Y*(hyperSpaceTwirl22+hyperSpaceTwirl11-hyperSpaceTwirl12-hyperSpaceTwirl21);
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

	if (newDevice)
	{
		newDevice->getGUIEnvironment()->clear();

		FTL_HUD = newDevice->getGUIEnvironment()->addTab(core::rect<s32>(0, 0, 1000, 700),0,1);
		RealSpace_HUD = newDevice->getGUIEnvironment()->addTab(core::rect<s32>(0, 0, 1000, 700),0,2);
		Map_HUD = newDevice->getGUIEnvironment()->addTab(core::rect<s32>(0, 0, 1000, 700),0,3);
		QuasiSpace_HUD = newDevice->getGUIEnvironment()->addTab(core::rect<s32>(0, 0, 1000, 700),0,4);
		HyperSpace_HUD = newDevice->getGUIEnvironment()->addTab(core::rect<s32>(0, 0, 1000, 700),0,5);

		//RealSpace_HUD->setVisible(false);
	}

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
	SpaceObject* newStar = new SpaceObject();//delete is in GamePhysics::ClearObjects
	SceneNode * sceneNode;

	if (sceneManager)
	{
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
		//newStar->SetMotionType(SpaceObject::MOTION_NONE);

		scene::ILightSceneNode * light = sceneManager->addLightSceneNode(sceneNode, core::vector3df(0,0,-(f32)radius),
			//video::SColorf(100.0f,100.0f,100.0f,1.0f), 1.0f);
			video::SColorf(1.0f,1.0f,1.0f,1.0f), 100.0f);

		//ELT_DIRECTIONAL 

		//light->getLightData().Attenuation.set(.7f,0,0.000003f);
		//light->getLightData().Attenuation.set(.7f,0.001f,0);

		light->getLightData().Attenuation.set(.7f,0,0);//zero fading - temp, for adjusting scale
	}

	newStar->SetIntProperty(SpaceObject::MOTION_TYPE,SpaceObject::MOTION_NONE);
	newStar->SetIntProperty(SpaceObject::COLLISIONS_CHECK,1);
	newStar->SetFloatProperty(SpaceObject::GRAVITY_MIN_RADIUS,radius);
	newStar->SetFloatProperty(SpaceObject::GEOMETRY_RADIUS,radius);
	//planetOne->SetOrbitalParams(0,200,300,0);
	physics->AddObject(newStar);

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
	SpaceObject* newPlanet = new SpaceObject();//delete is in GamePhysics::ClearObjects
	SceneNode * sceneNode;

	if (sceneManager)
	{
		sceneNode = sceneManager->addSphereSceneNode((f32)radius,polygons);
		if (sceneNode)
		{
			//sceneNode->setScale(vector3d(radius,radius,radius));
			//sceneNode->setPosition(core::vector3df(-30,50,0));
			sceneNode->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/planet0.bmp"));
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
	}
	newPlanet->SetIntProperty(SpaceObject::COLLISIONS_CHECK,1);
	newPlanet->SetFloatProperty(SpaceObject::GRAVITY_MIN_RADIUS,radius);
	newPlanet->SetFloatProperty(SpaceObject::GEOMETRY_RADIUS,radius);
	//planetOne->SetMotionType(SpaceObject::MOTION_NONE);
	//newPlanet->SetOrbitalParams(0,200,300,0);


	physics->AddObject(newPlanet);

	AddMarker(newPlanet,0);

	return newPlanet;
}

SpaceObject* ResourceManager::MakeBarycenter()
{
	SpaceObject* barycenter = new SpaceObject();//delete is in GamePhysics::ClearObjects
	barycenter->SetNode(0);
	barycenter->SetIntProperty(SpaceObject::COLLISIONS_CHECK,0);
	
	physics->AddObject(barycenter);

	return barycenter;
}

SpaceObject* ResourceManager::MakeWormhole()
{
	SpaceObject* newWormhole = new SpaceObject();//delete is in GamePhysics::ClearObjects
	SceneNode * sceneNode;

	if (sceneManager)
	{
		sceneNode = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/wormhole4.irrmesh"));

		sceneNode->setScale(vector3df(0.1429f));
		newWormhole->SetNode(sceneNode);
	}

	newWormhole->SetIntProperty(SpaceObject::COLLISIONS_CHECK,1);
	newWormhole->SetFloatProperty(SpaceObject::MASS,0);
	newWormhole->SetFloatProperty(SpaceObject::GEOMETRY_RADIUS,0.1);//Distance to check passing thru circle
	newWormhole->SetIntProperty(SpaceObject::EMIT_GRAVITY,0);
	newWormhole->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
	newWormhole->SetIntProperty(SpaceObject::WORMHOLE,1);
	newWormhole->SetIntProperty(SpaceObject::CURRENT_PROCESS,SpaceObject::PROCESS_WORMHOLE_RESIZING);

	physics->AddObject(newWormhole);
	AddMarker(newWormhole,0);

	return newWormhole;
}


SpaceObject* ResourceManager::MakeStargate()
{
	SpaceObject* newStargate = new SpaceObject();//delete is in GamePhysics::ClearObjects
	SceneNode * sceneNode;
	/*
	SpaceObject* newStargateEH = new SpaceObject();//delete is in GamePhysics::ClearObjects
	SceneNode * sceneNodeEH;*/

	if (sceneManager)
	{
		sceneNode = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/sg1.irrmesh"));

		sceneNode->setScale(vector3df(50.0f));
		newStargate->SetNode(sceneNode);
	}

	newStargate->SetIntProperty(SpaceObject::COLLISIONS_CHECK,1);
	newStargate->SetFloatProperty(SpaceObject::MASS,0);
	newStargate->SetFloatProperty(SpaceObject::GEOMETRY_RADIUS,50.0*0.7);
	newStargate->SetIntProperty(SpaceObject::EMIT_GRAVITY,0);
	newStargate->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
	newStargate->SetIntProperty(SpaceObject::STARGATE,1);

	physics->AddObject(newStargate);
	AddMarker(newStargate,0);

/*
	sceneNodeEH = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/sg1eh.irrmesh"));
	sceneNodeEH->setScale(vector3df(70.0f));
	newStargateEH->SetNode(sceneNodeEH);

	newStargateEH->SetFloatProperty(SpaceObject::MASS,0);
	newStargateEH->SetFloatProperty(SpaceObject::GEOMETRY_RADIUS,70.0);
	newStargateEH->SetIntProperty(SpaceObject::EMIT_GRAVITY,0);
	newStargateEH->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
	newStargateEH->SetIntProperty(SpaceObject::TRAVEL_TO_X,-100000);//not working
	newStargateEH->SetIntProperty(SpaceObject::TRAVEL_TO_Y,0);
	newStargateEH->SetIntProperty(SpaceObject::STARGATE,2);//TODO: ????

	//newStargateEH->SetIntProperty(SpaceObject::MOTION_TYPE,SpaceObject::MOTION_LINKED);
	//newStargateEH->SetLinkedPosition(vector3d(0,13.0,0));
	//newStargateEH->SetOrbitalParent(newStargate);
	newStargateEH->SetLinkedParams(newStargate,vector3d(13.0,0,0),0);
	newStargateEH->SetName(L"stargate event horizon");
	newStargateEH->SetIntProperty(SpaceObject::VISIBLE_TO_PLAYER,0);

	physics->AddObject(newStargateEH);
	//AddMarker(newStargateEH,0);
	*/

	return newStargate;
}

SpaceObject* ResourceManager::MakeStargateEH()
{
	SpaceObject* newStargateEH = new SpaceObject();//delete is in GamePhysics::ClearObjects
	SceneNode * sceneNodeEH;

	if (sceneManager)
	{
		sceneNodeEH = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/sg1eh.irrmesh"));
		sceneNodeEH->setScale(vector3df(70.0f));
		newStargateEH->SetNode(sceneNodeEH);
	}

	newStargateEH->SetFloatProperty(SpaceObject::MASS,0);
	newStargateEH->SetFloatProperty(SpaceObject::GEOMETRY_RADIUS,70.0);
	newStargateEH->SetIntProperty(SpaceObject::EMIT_GRAVITY,0);
	newStargateEH->SetIntProperty(SpaceObject::COLLISIONS_CHECK,1);
	newStargateEH->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
	newStargateEH->SetIntProperty(SpaceObject::TRAVEL_TO_X,-100000);//not working
	newStargateEH->SetIntProperty(SpaceObject::TRAVEL_TO_Y,0);
	newStargateEH->SetIntProperty(SpaceObject::STARGATE,2);//TODO: ????

	//newStargateEH->SetLinkedParams(newStargate,vector3d(13.0,0,0),0);
	newStargateEH->SetName(L"stargate event horizon");
	newStargateEH->SetIntProperty(SpaceObject::VISIBLE_TO_PLAYER,0);

	physics->AddObject(newStargateEH);
	//AddMarker(newStargateEH,0);

	return newStargateEH;
}


SpaceObject* ResourceManager::MakeMarker()
{
	SpaceObject* newMarker = new SpaceObject();//delete is in GamePhysics::ClearObjects
	
	/*
	SceneNode * sceneNode;

	sceneNode = sceneManager->addSphereSceneNode((f32)0.5,3);
	if (sceneNode)
	{
		//sceneNode->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/planet0.bmp"));
	}
	newMarker->SetNode(sceneNode);
	*/

	newMarker->SetNode(0);
	newMarker->SetFloatProperty(SpaceObject::GEOMETRY_RADIUS,0);
	newMarker->SetIntProperty(SpaceObject::COLLISIONS_CHECK,0);

	physics->AddObject(newMarker);
	AddMarker(newMarker,0);

	return newMarker;
}

SpaceObject* ResourceManager::MakeGravityWell(f64 radius)
{
	SpaceObject* newWell = new SpaceObject();//delete is in GamePhysics::ClearObjects
	SceneNode * sceneNode;

	sceneNode = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/plane.irrmesh"));
	if (sceneNode)
	{
		sceneNode->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
		sceneNode->setMaterialFlag(video::EMF_LIGHTING, true);
		sceneNode->getMaterial(0).EmissiveColor.set(255,0,0,0);
		sceneNode->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/star3.bmp"));
		sceneNode->setScale(vector3df((f32)(radius*2.0)));
	}
	newWell->SetNode(sceneNode);

	newWell->SetFloatProperty(SpaceObject::GEOMETRY_RADIUS,radius);
	newWell->SetIntProperty(SpaceObject::COLLISIONS_CHECK,0);
	newWell->SetIntProperty(SpaceObject::GRAVITY_WELL,1);

	physics->AddObject(newWell);
	AddMarker(newWell,2);

	return newWell;
}

SpaceObject* ResourceManager::MakeProjectile()
{
	SpaceObject* newProjectile = new SpaceObject();//delete is in GamePhysics::ClearObjects
	
	SceneNode * sceneNode;

	sceneNode = sceneManager->addSphereSceneNode((f32)0.05,5);
	if (sceneNode)
	{
		//sceneNode->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/planet0.bmp"));
	}
	newProjectile->SetNode(sceneNode);

	//newProjectile->SetNode(0);
	newProjectile->SetFloatProperty(SpaceObject::GEOMETRY_RADIUS,0.05);
	newProjectile->SetIntProperty(SpaceObject::MOTION_TYPE,SpaceObject::MOTION_NAVIGATION);
	newProjectile->SetIntProperty(SpaceObject::EMIT_GRAVITY,0);
	newProjectile->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,1);
	newProjectile->SetIntProperty(SpaceObject::COLLISIONS_CHECK,1);

	physics->AddObject(newProjectile);
	AddMarker(newProjectile,0);

	return newProjectile;

}


SpaceObject* ResourceManager::LoadNodesForShip(SpaceObject* ship)
{
	ship->SetNode(NewShipNode());
	AddMarker(ship,1);

	return ship;
}


SpaceObject* ResourceManager::MakeShip()
{
	SpaceObject* ship = new SpaceObject();//delete is in GamePhysics::ClearObjects
	//ship->SetMotionType(SpaceObject::MOTION_NAVIGATION);
	ship->SetIntProperty(SpaceObject::MOTION_TYPE,SpaceObject::MOTION_NAVIGATION);
	ship->SetIntProperty(SpaceObject::COLLISIONS_CHECK,1);

	//ship->SetGravity(false,true);
	ship->SetIntProperty(SpaceObject::EMIT_GRAVITY,0);
	ship->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,1);

	ship->SetFloatProperty(SpaceObject::GEOMETRY_RADIUS,1.0);
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
	if (sceneManager==0)
		return;

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
		switch(type)
		{
		case 0:
			sceneNode2->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/star3.bmp"));
			sizeMarker  = .07;
			break;
		case 1:
			sceneNode2->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/arrow.bmp"));
			sizeMarker  = .1;
			break;
		case 2:
			sceneNode2->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/star3.bmp"));
			sizeMarker  = .07;
			sceneNode2->setMaterialFlag(video::EMF_LIGHTING, true);
			sceneNode2->getMaterial(0).EmissiveColor.set(255,0,0,0);
			break;
		}
	}
	toObject->SetMarkerNode(sceneNode2,sizeMarker);
}

gui::IGUITab* ResourceManager::GetHUD(DG_Game::ViewType view)
{
	switch(view)
	{
	case DG_Game::VIEW_FTL:
		return FTL_HUD;
	case DG_Game::VIEW_QUASISPACE:
		return QuasiSpace_HUD;
	case DG_Game::VIEW_REALSPACE:
		return RealSpace_HUD;
	case DG_Game::VIEW_SECTOR_MAP:
		return Map_HUD;
	case DG_Game::VIEW_HYPERSPACE:
		return HyperSpace_HUD;
	default:
		return 0;
	}

}

void ResourceManager::ActivateHUD(DG_Game::ViewType view)
{
	RealSpace_HUD->setVisible(view==DG_Game::VIEW_REALSPACE);
	Map_HUD->setVisible(view==DG_Game::VIEW_SECTOR_MAP);
	FTL_HUD->setVisible(view==DG_Game::VIEW_FTL);
	QuasiSpace_HUD->setVisible(view==DG_Game::VIEW_QUASISPACE);
	HyperSpace_HUD->setVisible(view==DG_Game::VIEW_HYPERSPACE);
	return;
}


//#########################################################################
//GameView

void GameView::DisplayMessage(text_string message)
{
	wprintf(L"DG: %ws\r\n",message.c_str());
}


//#########################################################################
//RealSpaceView

RealSpaceView::RealSpaceView()
{
	typing = 0;
	typingText = L"";
	//typingTextPrev = L"";
	typingTextPrev = L"48A:887:CE4";//DEBUG!
}

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

	viewHUD = resourceManager->GetHUD(DG_Game::VIEW_REALSPACE);
	
	
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

	//playerThrust = 1.0;


	//device->getCursorControl()->setVisible(false);

	/*
	Add a colorful irrlicht logo
	*/

	/*
	device->getGUIEnvironment()->addImage(
		driver->getTexture(RESOURCE_PATH"/ships.png"),//irrlichtlogoalpha2.tga"),
		core::position2d<s32>(10,20));*/

	//simpleTextToDisplay = resourceManager->getSimpleText();
	simpleTextToDisplay = device->getGUIEnvironment()->addStaticText(
		L"Diagnostic very-very-very-very-very-very-very-very-long 1\r\nSecond line", core::rect<s32>(5, 5, 400, 200),false,true,viewHUD);
	simpleTextToDisplay->setOverrideColor(video::SColor(255, 0, 255, 0));

	/**/

	// This is the movemen speed in units per second.
	//MOVEMENT_SPEED = 5.0;

	Prepare();

}

void RealSpaceView::Prepare()
{
	resourceManager->SetSceneManager(sceneManager);
	sceneManager->clear();

	resourceManager->LoadNodesForShip((SpaceObject*)playerShip);

	playerShipThrust = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/thrust1.irrmesh"));
	if (playerShipThrust)
	{
		playerShipThrust->setScale(core::vector3df(1.f));
		/*playerShipThrust->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/fire1.bmp"));
		playerShipThrust->setMaterialFlag(video::EMF_LIGHTING, false);
		playerShipThrust->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
		playerShipThrust->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);*/
		playerShipThrust->setParent(playerShip->GetNode());
		playerShipThrust->setPosition(vector3df(-0.45f,0.f,-0.1f));
		playerShipThrust->setScale(vector3df(2.0f,0.5f,1.0f));
		playerShipThrust->setVisible(false);
	}

	camera = sceneManager->addCameraSceneNode();
	camera->setFOV(.7f);//field-of-view
	camera->setTarget(vector3df(0));//update camera look-at point

	cameraDistanceDegree = 1000.0;
	UpdateCameraDistance();

}


void RealSpaceView::Activate()
{
}

//flags: 1 - return galaxy coordinates (default: physics)
vector2d RealSpaceView::GetCoordinatesOnScreen(vector2ds pixelCoords, u32 flags)
{
	core::dimension2d<u32> screenSize = videoDriver->getScreenSize();
	f64 kfov = 2*tan(camera->getFOV()*0.5)*cameraDistance;
	vector2d gameCoordinates;
	gameCoordinates.X = pixelCoords.X;
	gameCoordinates.Y = pixelCoords.Y;
	gameCoordinates.X=playerShip->GetPosition().X+kfov*((gameCoordinates.X-screenSize.Width*.5)/screenSize.Height);
	gameCoordinates.Y=playerShip->GetPosition().Y-kfov*(gameCoordinates.Y/screenSize.Height-0.5);

	if ((flags&1)!=0)
	{
		//galaxy coordinates needed
		gameCoordinates/=LIGHTYEAR;
		gameCoordinates+=gamePhysics->GetGalaxyCoordinatesOfCenter();
	}

	return gameCoordinates;
}

void RealSpaceView::Update(f64 frameDeltaTime)
{
	vector3d playerPosition;// = node->getPosition();
	vector3df nodePosition;// = node->getPosition();
	s32 quasiDir;

	if (typing==0)
	{
		if(eventReceiver->IsKeyDown(irr::KEY_KEY_W))
			//playerShip->speed.Y += MOVEMENT_SPEED * frameDeltaTime;
			playerShip->SetControl(playerShip->GetControlThrust(),SpaceObject::CONTROL_THRUST_RELATIVE);
		else if(eventReceiver->IsKeyDown(irr::KEY_KEY_S))
			//playerShip->speed.Y -= MOVEMENT_SPEED * frameDeltaTime;
			playerShip->SetControl(-playerShip->GetControlThrust(),SpaceObject::CONTROL_THRUST_RELATIVE);
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
			playerShip->SetControlThrust(1.0); //playerThrust = 1.0;
		if(eventReceiver->IsKeyPressed(irr::KEY_KEY_2))
			playerShip->SetControlThrust(0.1); //playerThrust = 0.1;
		if(eventReceiver->IsKeyPressed(irr::KEY_KEY_3))
			playerShip->SetControlThrust(0.01); //playerThrust = 0.01;
		if(eventReceiver->IsKeyPressed(irr::KEY_KEY_4))
			playerShip->SetControlThrust(0.001); //playerThrust = 0.001;
		if(eventReceiver->IsKeyPressed(irr::KEY_KEY_5))
			playerShip->SetControlThrust(0.0001); //playerThrust = 0.0001;
		if(eventReceiver->IsKeyPressed(irr::KEY_KEY_6))
			playerShip->SetControlThrust(0.00001); //playerThrust = 0.00001;

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

		if (eventReceiver->IsKeyPressed(irr::KEY_SPACE))
		{
			playerShip->FireProjectile();
			UpdateCameraDistance();//to show marker
		}


		//if (eventReceiver->IsKeyDown(irr::KEY_SPACE))
		//	playerShip->AutopilotBreak();
		if (eventReceiver->IsKeyDown(irr::KEY_KEY_R))
			playerShip->AutopilotBreak();
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_Z))
		{
			AutopilotInstruction* ins = new AutopilotInstruction();//delete in ~SpaceObject or in autopilot processing
			ins->instruction = AutopilotInstruction::AP_SETSPEED;
			ins->vector1 = vector2d(0);
			playerShip->AddAutopilot(ins);
		}
		//if (eventReceiver->IsKeyDown(irr::KEY_KEY_O))
		//	playerShip->AutopilotOrbiting();
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_O))
		{
			AutopilotInstruction* ins = new AutopilotInstruction();//delete in ~SpaceObject or in autopilot processing
			ins->instruction = AutopilotInstruction::AP_ORBITING;
			playerShip->AddAutopilot(ins);
		}

		if (eventReceiver->IsKeyPressed(irr::KEY_ESCAPE))
			playerShip->BreakAutopilot();

		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_K))
			gameRoot->SaveGame();
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_L))
			gameRoot->LoadGame();


		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_X))
		{
			//Dump galaxy coordinates, in light-years
			//10 digits after point roughly gives game units, as light-year is roughly 10^10 * 1000 km
			vector3d xgrav = gamePhysics->GetXGravityAcceleration(playerShip->GetPosition());
			text_string message=L"Player galaxy coordinates: ";
			message+=print_f64(playerShip->GetGalaxyCoordinates().X,L"%.010f");
			message+=L", ";
			message+=print_f64(playerShip->GetGalaxyCoordinates().Y,L"%.010f");
			DisplayMessage(message);
			message = L"Player coordinates in system: ";
			message+=print_f64(playerShip->GetPosition().X,L"%.010f");
			message+=L", ";
			message+=print_f64(playerShip->GetPosition().Y,L"%.010f");
			DisplayMessage(message);
			message = L"X-gravity: ";
			message+=print_f64(log(xgrav.getLength()),L"%.03f");
			DisplayMessage(message);
		}
			
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_B))
		{
			gameRoot->GetGalaxy()->DebugShowWormholes();
		}

		if (eventReceiver->IsKeyPressed(irr::KEY_TAB))
		{
			//gameRoot->ActivateMap();
			gameRoot->AcviateView(DG_Game::VIEW_SECTOR_MAP);
			return; //skip update physics
		}

		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_F))
		{
			if (gamePhysics->IsFTLPossible(playerShip->GetPosition(),playerShip->GetFloatProperty(SpaceObject::MAX_FTL_GRAVITY)))
			{
				playerShip->SetFloatProperty(SpaceObject::FTL_REMAINING_TIME,100000000.0);//about a 3 years
				playerShip->JumpToFTL(3000.0);
				DisplayMessage(L"Jump to FTL");
				//gameRoot->ActivateFTL();
				//gameRoot->SwitchView(DG_Game::VIEW_FTL);

			}
			else
			{
				DisplayMessage(L"Gravity is too high to jump to FTL");
			}
		}

		if (eventReceiver->IsKeyPressed(irr::KEY_MULTIPLY))
		{
			quasiDir = 0;
			goto JumpToQuasi;
		}

		if (eventReceiver->IsKeyPressed(irr::KEY_MINUS) || eventReceiver->IsKeyPressed(irr::KEY_SUBTRACT))
		{
			quasiDir = -1;
			goto JumpToQuasi;
		}

		if (eventReceiver->IsKeyPressed(irr::KEY_PLUS) || eventReceiver->IsKeyPressed(irr::KEY_ADD))
		{
			quasiDir = 1;
	JumpToQuasi:
			if (gameRoot->GetGalaxy()->IsInGrid(playerShip->GetGalaxyQuadrant())!=1)
			{//outside galaxy grid
				DisplayMessage(L"PlusMinus Engine does not actived");
			}
			else if (gamePhysics->IsPlusMinusPossible(playerShip->GetPosition()))
			{
				playerShip->JumpToQuasiSpace(quasiDir);
				if (quasiDir==1)
				{
					DisplayMessage(L"PlusMinus Engine activated by Plus");
				}
				else if (quasiDir==-1)
				{
					DisplayMessage(L"PlusMinus Engine activated by Minus");
				}
				else
				{
					//N/A
					DisplayMessage(L"PlusMinus Engine activated by Plus and Minus at once");
				}

				//gamePhysics->GoInterstellar();
				gameRoot->GoInterstellar();

				//gameRoot->SwitchView(DG_Game::VIEW_QUASISPACE);
			}
			else
			{
				DisplayMessage(L"Gravity is too high to use PlusMinus Engine");
			}
		}


		/*
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_J))
			gamePhysics->DebugJumpToWormhole(1);
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_H))
			gamePhysics->DebugJumpToWormhole(0);
		*/
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_H))
		{
			DisplayMessage(L"Jump to HyperSpace");
			gameRoot->GoHyperSpace();
			return;
		}

		if(eventReceiver->IsKeyDown(irr::KEY_UP))
		{
			cameraDistanceDegree+=frameDeltaTime*2000.0;
			//cameraDistance *= 1.f*(1.f+frameDeltaTime);
			UpdateCameraDistance();
		}

		if(eventReceiver->IsKeyDown(irr::KEY_DOWN))
		{
			//cameraDistance *= 1.f*(1.f-frameDeltaTime);
			cameraDistanceDegree-=frameDeltaTime*2000.0;
			UpdateCameraDistance();
		}

		if(eventReceiver->IsKeyPressed((irr::EKEY_CODE)KEY_PSEUDO_MOUSEWHEELUP))
		{
			cameraDistanceDegree-=200;
			UpdateCameraDistance();
		}
		if(eventReceiver->IsKeyPressed((irr::EKEY_CODE)KEY_PSEUDO_MOUSEWHEELDOWN))
		{
			cameraDistanceDegree+=200;
			UpdateCameraDistance();
		}

		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_T))
		{
			playerShip->ScanSpace(1e4);
		}

		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_Y))
		{
			typing = 1;//type stargate address
			typingText = L"";
		}
	}
	else
	{
		if (eventReceiver->IsKeyPressed(irr::KEY_ESCAPE))
			typing = 0;
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_0))
			typingText += L"0";
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_1))
			typingText += L"1";
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_2))
			typingText += L"2";
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_3))
			typingText += L"3";
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_4))
			typingText += L"4";
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_5))
			typingText += L"5";
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_6))
			typingText += L"6";
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_7))
			typingText += L"7";
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_8))
			typingText += L"8";
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_9))
			typingText += L"9";
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_A))
			typingText += L"A";
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_B))
			typingText += L"B";
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_C))
			typingText += L"C";
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_D))
			typingText += L"D";
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_E))
			typingText += L"E";
		if (eventReceiver->IsKeyPressed(irr::KEY_KEY_F))
			typingText += L"F";
		if (eventReceiver->IsKeyPressed(irr::KEY_UP))
			typingText = typingTextPrev;
		if (eventReceiver->IsKeyPressed(irr::KEY_BACK))
			typingText = typingText.subString(0,typingText.size()-1);
		if (eventReceiver->IsKeyPressed(irr::KEY_RETURN))
		{
			typingTextPrev = typingText;
			if (typing==1)
			{
				//u64 address = _wtoi64(typingText.c_str());
				//u64 address = stoi64(typingText);
				u64 address = gameRoot->GetGalaxy()->text2StargateAddress(typingText);
				wprintf(L" * Typed stargate address: %I64i\r\n",address);
				//playerShip->FallIntoStargate(address);
				gamePhysics->SendStargateAddress(playerShip,address);
			}
			typing=0;
		}
	}

	vector2ds lastClick = eventReceiver->GetLastMouseClick();
	if (lastClick.X>-1)
	{
		vector2d clickPos = GetCoordinatesOnScreen(lastClick,0);
		eventReceiver->RemoveLastMouseClick();
		/*
		core::dimension2d<u32> screenSize = videoDriver->getScreenSize();
		f64 kfov = 2*tan(camera->getFOV()*0.5)*cameraDistance;
		f64 x,y;
		x = lastClick.X;
		y = lastClick.Y;
		//x /=screenSize.Width;
		//y /=screenSize.Height;
		x=kfov*((x-screenSize.Width*.5)/screenSize.Height)+playerShip->GetPosition().X;//-0.5 .. +0.5
		y=playerShip->GetPosition().Y-kfov*(y/screenSize.Height-0.5);
		*/

		u32 buttons = eventReceiver->GetLastMouseClickButtons();

		if (buttons&1)
		{
			wprintf(L" Autopilot fly to: %f,%f\r\n",clickPos.X,clickPos.Y);

			//playerShip->SetPosition(vector3d(x,y,0));//DEBUG

			AutopilotInstruction* ins = new AutopilotInstruction();//delete in ~SpaceObject or in autopilot processing
			ins->instruction = AutopilotInstruction::AP_FLY_TO;
			ins->prepareText = true;
			ins->textInfo = L"";
			ins->vector1 = clickPos;
			//ins->value1 = 0;//speed, 0 is temprorary
			ins->value1 = playerShip->GetSpeed().getLength();
			if (ins->value1>LIGHTSPEED*0.5)
				ins->value1 = LIGHTSPEED*0.5;
			ins->value2 = 0;//maxspeed = 0
			ins->phase = 0;
			playerShip->AddAutopilot(ins);

			resourceManager->SetSceneManager(sceneManager);
			SpaceObject* marker = resourceManager->MakeMarker();
			marker->SetIntProperty(SpaceObject::EMIT_GRAVITY,0);
			marker->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
			marker->SetPosition(vector3d(clickPos.X,clickPos.Y,0));
			marker->SetName(L"autopilot marker");
			UpdateCameraDistance();//to show marker

			ins->object = marker;

		}
		else if (buttons&2)
		{
			//vector2d destination = vector2d(x,y);
			//destination /=LIGHTYEAR;
			//destination += gamePhysics->GetGalaxyCoordinatesOfCenter();
			clickPos = GetCoordinatesOnScreen(lastClick,1);
			//x+=phy
			wprintf(L" Autopilot FTL to: %f,%f\r\n",clickPos.X,clickPos.Y);

			AutopilotInstruction* ins = new AutopilotInstruction();//delete in ~SpaceObject or in autopilot processing
			ins->instruction = AutopilotInstruction::AP_FTL_TO;
			ins->vector1 = clickPos;//vector2d(x,y);
			ins->phase = 0;
			playerShip->AddAutopilot(ins);

			resourceManager->SetSceneManager(sceneManager);
			SpaceObject* marker = resourceManager->MakeMarker();
			marker->SetIntProperty(SpaceObject::EMIT_GRAVITY,0);
			marker->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
			marker->SetPosition(vector3d(clickPos.X,clickPos.Y,0));
			marker->SetName(L"autopilot FTL marker");
			UpdateCameraDistance();//to show marker

			ins->object = marker;

		}
		else if (buttons&4)
		{

			//playerShip->SetPosition(vector3d(x,y,0));//DEBUG
			vector3d clickedPosition=vector3d(clickPos.X,clickPos.Y,0);

			AutopilotInstruction* ins = new AutopilotInstruction();//delete in ~SpaceObject or in autopilot processing

			GravityInfo* gravInfo = gamePhysics->GetGravityInfo(clickedPosition);
			if (gravInfo->maxGravityObject)
			{//only if there is dominant object
				ins->instruction = AutopilotInstruction::AP_FLY_TO_ORBIT;
				ins->paramObject = gravInfo->maxGravityObject;
				ins->value1 = (clickedPosition - gravInfo->maxGravityObject->GetPosition()).getLength();
				ins->value2 = 0;//maxspeed = 0

				wprintf(L" Autopilot orbiting to: %ws\r\n",ins->paramObject->GetName().c_str());
			}
			else
			{
				wprintf(L" Autopilot orbiting to: %f,%f\r\n",clickPos.X,clickPos.Y);

				ins->instruction = AutopilotInstruction::AP_FLY_TO;
				ins->vector1 = clickPos;//vector2d(x,y);
				ins->value1 = playerShip->GetSpeed().getLength();
				if (ins->value1>LIGHTSPEED*0.5)
					ins->value1 = LIGHTSPEED*0.5;
				ins->value2 = 0;//maxspeed = 0
			}
			delete gravInfo;

			ins->prepareText = true;
			ins->textInfo = L"";
			ins->phase = 0;
			playerShip->AddAutopilot(ins);

			resourceManager->SetSceneManager(sceneManager);
			SpaceObject* marker = resourceManager->MakeMarker();
			marker->SetIntProperty(SpaceObject::EMIT_GRAVITY,0);
			marker->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
			marker->SetPosition(clickedPosition);
			marker->SetName(L"autopilot orbiting marker");
			UpdateCameraDistance();//to show marker

			ins->object = marker;
		}
		else
		{
			wprintf(L" Mouse click on: %f,%f\r\n",clickPos.X,clickPos.Y);
		}
	
	}

	/*
	if (eventReceiver->IsKeyDown(irr::KEY_KEY_Q))
	{
		gameRoot->GetGalaxy()->DebugDump();
	}*/

	//playerShip->thrustPower = thrust*MOVEMENT_SPEED*5.f;
	//playerShip->rotationSpeed = rotate;
	//playerShip->SetThrust(thrust*MOVEMENT_SPEED*5.f);
	//playerShip->SetRotationSpeed(rotate);
	//someShip->SetControl(1.f,SpaceObject::CONTROL_THRUST_ABSOLUTE);
	//someShip->SetControl(20.f,SpaceObject::CONTROL_ROTATION_SPEED_ABSOLUTE);

	
	
	f64 thrust = playerShip->GetFloatProperty(SpaceObject::THRUST_POWER);
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


	if (typing==0)
	{
		text_string debug_text(L"Speed: ");
		f64 playerSpeed;
		GravityInfo* gravInfo;
		gravInfo = gamePhysics->GetGravityInfo(playerShip->GetPosition());
		gravInfo->UpdateGravityInfoOrbit(playerShip);

		playerSpeed = playerShip->GetSpeed().getLength();
		debug_text += playerSpeed;
		debug_text += L" km/s\r\n";
		debug_text += (playerSpeed/LIGHTSPEED);
		debug_text += L" c; ";
		debug_text += L"\r\n";
		debug_text += gravInfo->print();
		debug_text += L"\r\n";
		debug_text += playerShip->GetAutopilotInfo();
		simpleTextToDisplay->setText(debug_text.c_str());
	
		delete gravInfo;//new in GamePhysics::GetGravityInfo
	}
	else
	{
		text_string debug_text(L"Typing: ");
		debug_text += typingText;
		simpleTextToDisplay->setText(debug_text.c_str());
	}

	gamePhysics->Update(frameDeltaTime);
	gamePhysics->UpdateNodes(playerShip,0);


	//TODO: use resourceManager to render?
	videoDriver->beginScene(true, true, video::SColor(255,0,0,0));
	sceneManager->drawAll(); // draw the 3d scene
	device->getGUIEnvironment()->drawAll();
	videoDriver->endScene();
}

void RealSpaceView::Close()
{
}

void RealSpaceView::UpdateCameraDistance()
{
	if (cameraDistanceDegree<-100)
		cameraDistanceDegree=-100;
	if (cameraDistanceDegree>6500)
		cameraDistanceDegree=6500;

	cameraDistance = 30.0*exp(cameraDistanceDegree*0.003);

	if (cameraDistance<50.0f)
	{//modified mainly for wormholes
		camera->setFarValue(100.f);
		camera->setNearValue(1.f);
	}
	else
	{
		camera->setFarValue((f32)(cameraDistance*2.0));
		camera->setNearValue((f32)(cameraDistance*0.5));
	}
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

MapObject::MapObject()
{
	lowScaleLimit = 0;
	nonObjectPosition = vector2d(0);
	sceneNode = 0;
	originalObject = 0;
	sizeMinimal = 0;
	sizeReal = 1.0;
	yScale = 1.0;
}

void MapObject::UpdatePosition(f64 mapScale, vector2d centerOfMap)
{
	if (sceneNode)
	{
		vector2d position;
		f64 size;
		if (originalObject)
		{
			vector3d pos3d = originalObject->GetPosition();
			position.X = pos3d.X;
			position.Y = pos3d.Y;
		}
		else
		{
			position = nonObjectPosition;
		}
		position -= centerOfMap;
		position *= mapScale;
		size = sizeReal*mapScale;
		if (size<sizeMinimal) size = sizeMinimal;

		sceneNode->setPosition(vector3df((f32)(position.X),(f32)(position.Y),0));
		//sceneNode->setScale(vector3df((f32)(size)));
		sceneNode->setScale(vector3df((f32)(size),(f32)(size*yScale),(f32)(size)));

		if (lowScaleLimit!=0)
		{
			u32 alpha = 255;
			if (size>lowScaleLimit)
				alpha = (u32)(255.0*lowScaleLimit/size);
			sceneNode->getMaterial(0).EmissiveColor.set(255,alpha,alpha,alpha);
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
		sceneNode2->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/star3.bmp"));
		//sizeMarker  = .07;
		sceneNode2->setPosition(vector3df((f32)(position.X*.000001),(f32)(position.Y*.000001),0));
	}
	text_string label = spaceObject->GetName();
	core::dimension2d<u32> labelSize = sceneManager->getGUIEnvironment()->getBuiltInFont()->getDimension(label.c_str());
	SceneNode * sceneNode3 = sceneManager->addBillboardTextSceneNode(0,label.c_str(),sceneNode2,core::dimension2d<f32>(labelSize.Width*0.24f,2.0f));
	
	//SceneNode* sceneNode3 = sceneManager->addBillboardTextSceneNode(0,label.c_str(),sceneNode2,core::dimension2d<f32>(10.f,2.0f));
	
	//getDimension(
	//sceneNode3->setPosition(vector3df(labelSize.Width*0.12f,1.0f,0));
	sceneNode3->setPosition(vector3df(0,-1.0f,0));
	//sceneNode3->setPosition(sceneNode3->getScale());

	MapObject* newMapObject = new MapObject();//delete in MapSpaveView::ClearObjects
	newMapObject->SetNode(sceneNode2);
	newMapObject->SetOriginal(spaceObject);
	newMapObject->SetSizes(2.0*spaceObject->GetFloatProperty(SpaceObject::GEOMETRY_RADIUS),1.0);
	MapObjectList.push_back(newMapObject);
}

void MapSpaceView::AddStarMarker(GalaxyStarSystem* starSystem)
{
	vector2d position = (starSystem->GetGalaxyCoordinates() - gamePhysics->GetGalaxyCoordinatesOfCenter())*LIGHTYEAR;

	if (position.getLengthSQ()<0.01)
		return;//skip same star

	SceneNode* sceneNode2 = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/plane.irrmesh"));
	if (sceneNode2)
	{
		sceneNode2->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
		sceneNode2->setMaterialFlag(video::EMF_LIGHTING, false);
		sceneNode2->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/star3.bmp"));
		//sizeMarker  = .07;
		//sceneNode2->setPosition(vector3df((f32)(position.X*.000001*LIGHTYEAR),(f32)(position.Y*.000001*LIGHTYEAR),0));
	}
	text_string label = starSystem->GetName();
	core::dimension2d<u32> labelSize = sceneManager->getGUIEnvironment()->getBuiltInFont()->getDimension(label.c_str());
	SceneNode * sceneNode3 = sceneManager->addBillboardTextSceneNode(0,label.c_str(),sceneNode2,core::dimension2d<f32>(labelSize.Width*0.24f,2.0f));
	
	//SceneNode* sceneNode3 = sceneManager->addBillboardTextSceneNode(0,label.c_str(),sceneNode2,core::dimension2d<f32>(10.f,2.0f));
	
	//getDimension(
	//sceneNode3->setPosition(vector3df(labelSize.Width*0.12f,1.0f,0));
	sceneNode3->setPosition(vector3df(0,-1.0f,0));
	//sceneNode3->setPosition(sceneNode3->getScale());

	MapObject* newMapObject = new MapObject();//delete in MapSpaveView::ClearObjects
	newMapObject->SetNode(sceneNode2);
	newMapObject->SetNonObjectPosition(position);
	newMapObject->SetSizes(1e6,1.0);//~1 lighthour, ~6.6 AU, ~720 solar raduises
	MapObjectList.push_back(newMapObject);
}

void MapSpaceView::AddWormholeLink(vector2d coordinates1, vector2d coordinates2)
{
	f64 rotation;
	f64 distance;
	vector2d linkVector = coordinates2-coordinates1;
	//vector2d linkVector;
	//linkVector.X = link->Star2.X-link->Star1.X;
	//linkVector.Y = link->Star2.Y-link->Star1.Y;

	//vector2d position = (vector2d(link->Star1.X,link->Star1.Y) - gamePhysics->GetGalaxyCoordinatesOfCenter())*LIGHTYEAR;
	vector2d position = (coordinates1 - gamePhysics->GetGalaxyCoordinatesOfCenter())*LIGHTYEAR;
	rotation = atan2(linkVector.Y,linkVector.X)*RADTODEG64;
	//rotation = linkVector.getAngle();
	distance = linkVector.getLength();

	/*linkVector.normalize();
	position+=linkVector*0.05*LIGHTYEAR;
	distance-=0.1;*/


	SceneNode* sceneNode2 = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/wormholelink.irrmesh"));
	sceneNode2->setRotation(vector3df(0,0,(f32)rotation));

	MapObject* newMapObject = new MapObject();//delete in MapSpaveView::ClearObjects
	newMapObject->SetNode(sceneNode2);
	newMapObject->SetNonObjectPosition(position);
	newMapObject->SetSizes(LIGHTYEAR*distance,0.0);
	newMapObject->SetYScale(0.2/distance);//width should be contant (0.2 l.y), so Y-scale is revert to distance
	newMapObject->SetScaleLimits(1000);//disappear for system-wide scale
	MapObjectList.push_back(newMapObject);
}

void MapSpaceView::AddGalaxy(vector2d galaxyPosition)
{
	//TODO: add non-object marker
	SceneNode* sceneNode2 = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/plane.irrmesh"));
	if (sceneNode2)
	{
		sceneNode2->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
		//sceneNode2->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL );
		//sceneNode2->setMaterialType(video::EMT_SOLID );
		//sceneNode2->setMaterialType(video::EMT_ONETEXTURE_BLEND);
		//sceneNode2->setMaterialFlag(video::EMF_LIGHTING, true);
		//sceneNode2->getMaterial(0).DiffuseColor.set(255,0,0,0);
		//sceneNode2->getMaterial(0).setFlag(video::E_MATERIAL_FLAG::

		sceneNode2->setMaterialTexture(0, videoDriver->getTexture("galaxy.bmp"));

		//this->sceneManager->registerNodeForRendering(sceneNode2,scene::ESNRP_TRANSPARENT );

		/*
		for (u32 i=0;i<sceneNode2->getMaterialCount();i++)
		{
			//sceneNode2->setMaterialType(video::EMT_ONETEXTURE_BLEND );
			//sceneNode2->getMaterial(i).MaterialType = video::EMT_ONETEXTURE_BLEND;
			//sceneNode2->getMaterial(0).MaterialTypeParam = irr::video::pack_texureBlendFunc(irr::video::EBF_SRC_ALPHA, irr::video::EBF_DST_ALPHA);
			//sceneNode2->getMaterial(0).MaterialTypeParam = irr::video::pack_texureBlendFunc(irr::video::EBF_ONE, irr::video::EBF_ONE);
			//sceneNode2->getMaterial(i).MaterialTypeParam = irr::video::pack_texureBlendFunc( video::EBF_SRC_ALPHA, video::EBF_ONE_MINUS_SRC_ALPHA, video::EMFN_MODULATE_1X );
			//sceneNode2->getMaterial(i).AmbientColor.set(128,255,0,255);
			//sceneNode2->getMaterial(i).DiffuseColor.set(128,255,0,255);
			//sceneNode2->getMaterial(i).Lighting = true;
			//sceneNode2->getMaterial(i).ZWriteEnable = true;
			//sceneNode2->getMaterial(i).DiffuseColor.setAlpha(32);
		}*/
		sceneNode2->getMaterial(0).EmissiveColor.set(255,64,64,64);


		//video::ITexture * text2 = videoDriver->getTexture("galaxy.bmp");
		//video::ECOLOR_FORMAT cf = text2->getColorFormat();
		//sceneNode2->setMaterialTexture(0, text2);

		//TODO: direct creation of texture from stellar density
	}

	MapObject* newMapObject = new MapObject();//delete in MapSpaveView::ClearObjects
	newMapObject->SetNode(sceneNode2);
	newMapObject->SetNonObjectPosition(-galaxyPosition*LIGHTYEAR);
	newMapObject->SetSizes(LIGHTYEAR*131072,1.0);//
	newMapObject->SetScaleLimits(200000);//disappear for cluster-wide scale
	MapObjectList.push_back(newMapObject);
}


void MapSpaceView::Init()
{
	//sceneManager->clear();
	resourceManager = gameRoot->GetResourceManager();
	videoDriver = resourceManager->GetVideoDriver();
	device = resourceManager->GetDevice();
	eventReceiver = resourceManager->GetEventReceiver();
	centerOfMap = vector2d(0);
	viewHUD = resourceManager->GetHUD(DG_Game::VIEW_SECTOR_MAP);

	//simpleTextToDisplay = resourceManager->getSimpleText();
	simpleTextToDisplay = device->getGUIEnvironment()->addStaticText(
		L"Diagnostic very-very-very-very-very-very-very-very-long 2\r\nSecond line", core::rect<s32>(5, 5, 400, 200),false,true,viewHUD);
	simpleTextToDisplay->setOverrideColor(video::SColor(255, 0, 255, 0));
}

void MapSpaceView::Prepare()
{
}

void MapSpaceView::Activate()
{

	//gamePhysics->MakeMap(sceneManager,videoDriver,this);
	sceneManager->clear();
	ClearObjects();

	gamePhysics->MakeMap(this);

	/*
	if (gamePhysics->IsInterstellar())
	{
		gameRoot->GetGalaxy()->UpdatePlayerLocation(gameRoot->GetPlayerShip()->GetGalaxyCoordinates());
	}
	else
	{
		//Inside star system we should not update to exact location, but to center of star system
		gameRoot->GetGalaxy()->UpdatePlayerLocation(gamePhysics->GetGalaxyCoordinatesOfCenter());
	}*/

	gameRoot->GetGalaxy()->AddNearStarSystems(this);

	AddGalaxy(gamePhysics->GetGalaxyCoordinatesOfCenter());

	gridNode = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/grid1.irrmesh"));
	gridNode->setPosition(vector3df(0,0,0.1f));
	gridNode->setScale(vector3df(200.0f,200.0f,1.0f));


	camera = sceneManager->addCameraSceneNode();
	camera->setFOV(.7f);
	camera->setTarget(vector3df(0,0,0));
	camera->setPosition(vector3df(0,0,-100.f));
	camera->setFarValue(200.f);

	{
		vector3d center = gameRoot->GetPlayerShip()->GetPosition();
		centerOfMap.X = center.X;
		centerOfMap.Y = center.Y;

		//get shifts to quadrant grid and galaxy center
		shiftToGalaxy = gamePhysics->GetGalaxyCoordinatesOfCenter();
		shiftToQuadrant = shiftToGalaxy;
		shiftToQuadrant.X -= floor(shiftToQuadrant.X);//round shift to 1 l.y.
		shiftToQuadrant.Y -= floor(shiftToQuadrant.Y);
		shiftToQuadrant*=LIGHTYEAR;
		shiftToGalaxy*=LIGHTYEAR;

		//shiftToQuadrant
	}

	//cameraDistanceDegree = 5500.0;
	//cameraDistanceDegree = 11000.0;//galaxy view
	cameraDistanceDegree = 8400.0;//near stars view
	UpdateCameraDistance(0);
}

//flags: 1 - return galaxy coordinates (default: physics)
vector2d MapSpaceView::GetCoordinatesOnScreen(vector2ds pixelCoords, u32 flags)
{
	core::dimension2d<u32> screenSize = videoDriver->getScreenSize();
	f64 kfov = tan(camera->getFOV()*0.5)*200/mapScale;//200 = 2 * 100, 100 is cameradistance
	vector2d gameCoordinates = centerOfMap;
	gameCoordinates.X+=kfov*((((f64)pixelCoords.X)-screenSize.Width*.5)/screenSize.Height);//-0.5 .. +0.5
	gameCoordinates.Y-=kfov*(((f64)pixelCoords.Y)/screenSize.Height-0.5);

	if ((flags&1)!=0)
	{
		//galaxy coordinates needed
		gameCoordinates += shiftToGalaxy;
		gameCoordinates/=LIGHTYEAR;
	}

	return gameCoordinates;

}

void MapSpaceView::Update(f64 frameDeltaTime)
{
	if (eventReceiver->IsKeyPressed(irr::KEY_ESCAPE))
		//gameRoot->ActivateRealSpace();
		gameRoot->CloseView(DG_Game::VIEW_SECTOR_MAP);

	
	if(eventReceiver->IsKeyDown(irr::KEY_KEY_W))
	{
		centerOfMap.Y += 100.0*frameDeltaTime/mapScale;
		UpdateCameraDistance(0);
	}
	else if(eventReceiver->IsKeyDown(irr::KEY_KEY_S))
	{
		centerOfMap.Y -= 100.0*frameDeltaTime/mapScale;
		UpdateCameraDistance(0);
	}

	if(eventReceiver->IsKeyDown(irr::KEY_KEY_A))
	{
		centerOfMap.X -= 100.0*frameDeltaTime/mapScale;
		UpdateCameraDistance(0);
	}
	else if(eventReceiver->IsKeyDown(irr::KEY_KEY_D))
	{
		centerOfMap.X += 100.0*frameDeltaTime/mapScale;
		UpdateCameraDistance(0);
	}
	
	if(eventReceiver->IsKeyDown(irr::KEY_UP))
	//if (cameraDistanceDegree<8200) //estimated good to see ~10 LY in all directions
	{
		cameraDistanceDegree+=frameDeltaTime*2000.0;

		//f64 mapScale = 30.0*exp(cameraDistanceDegree*-0.003);
		//gamePhysics->UpdateMapMarkers(mapScale);
		UpdateCameraDistance(0);
	}

	if(eventReceiver->IsKeyDown(irr::KEY_DOWN))
	{
		//cameraDistance *= 1.f*(1.f-frameDeltaTime);
		cameraDistanceDegree-=frameDeltaTime*2000.0;
		//UpdateCameraDistance();
		//f64 mapScale = 30.0*exp(cameraDistanceDegree*-0.003);
		//gamePhysics->UpdateMapMarkers(mapScale);
		UpdateCameraDistance(0);

	}
	if (eventReceiver->IsKeyPressed(irr::KEY_NEXT))
	{
		if (cameraDistanceDegree>10000)
		{
			cameraDistanceDegree = 10000;
		}
		else if (cameraDistanceDegree>8500)
		{
			cameraDistanceDegree = 8500;
		}
		else if (cameraDistanceDegree>7000)
		{
			cameraDistanceDegree = 7000;
		}
		else if (cameraDistanceDegree>5500)
		{
			cameraDistanceDegree = 5500;
		}
		else if (cameraDistanceDegree>4000)
		{
			cameraDistanceDegree = 4000;
		}
		else if (cameraDistanceDegree>2500)
		{
			cameraDistanceDegree = 2500;
		}
		else if (cameraDistanceDegree>850)
		{
			cameraDistanceDegree = 850;
		}
		UpdateCameraDistance(0);
	}
	if (eventReceiver->IsKeyPressed(irr::KEY_PRIOR))
	{
		if (cameraDistanceDegree<850)
		{
			cameraDistanceDegree = 850;
		}
		else if (cameraDistanceDegree<2500)
		{
			cameraDistanceDegree = 2500;
		}
		else if (cameraDistanceDegree<4000)
		{
			cameraDistanceDegree = 4000;
		}
		else if (cameraDistanceDegree<5500)
		{
			cameraDistanceDegree = 5500;
		}
		else if (cameraDistanceDegree<7000)
		{
			cameraDistanceDegree = 7000;
		}
		else if (cameraDistanceDegree<8500)
		{
			cameraDistanceDegree = 8500;
		}
		else if (cameraDistanceDegree<10000)
		{
			cameraDistanceDegree = 10000;
		}
		else if (cameraDistanceDegree<11500)
		{
			cameraDistanceDegree = 11500;
		}
		UpdateCameraDistance(0);
	}

	vector2ds lastClick = eventReceiver->GetLastMouseClick();
	if (lastClick.X>-1)
	{
		eventReceiver->RemoveLastMouseClick();
		vector2d clickPos = GetCoordinatesOnScreen(lastClick,0);
		/*
		core::dimension2d<u32> screenSize = videoDriver->getScreenSize();
		f64 kfov = tan(camera->getFOV()*0.5)*200/mapScale;//200 = 2 * 100, 100 is cameradistance
		vector2d clickPos = centerOfMap;
		clickPos.X+=kfov*((((f64)lastClick.X)-screenSize.Width*.5)/screenSize.Height);//-0.5 .. +0.5
		clickPos.Y-=kfov*(((f64)lastClick.Y)/screenSize.Height-0.5);
		*/

		u32 buttons = eventReceiver->GetLastMouseClickButtons();

		if (buttons&1)
		{
			wprintf(L" Autopilot fly to: %f,%f\r\n",clickPos.X,clickPos.Y);

			//playerShip->SetPosition(vector3d(x,y,0));//DEBUG

			AutopilotInstruction* ins = new AutopilotInstruction();//delete in ~SpaceObject or in autopilot processing
			ins->instruction = AutopilotInstruction::AP_FLY_TO;
			ins->prepareText = true;
			ins->textInfo = L"";
			ins->vector1 = clickPos;
			ins->value1 = 0;//speed, 0 is temprorary
			ins->value2 = 0;//maxspeed = 0
			ins->phase = 0;
			gameRoot->GetPlayerShip()->AddAutopilot(ins);

			
			//resourceManager->SetSceneManager(sceneManager);
			gameRoot->UseSceneManager(DG_Game::VIEW_REALSPACE);
			SpaceObject* marker = resourceManager->MakeMarker();
			marker->SetIntProperty(SpaceObject::EMIT_GRAVITY,0);
			marker->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
			marker->SetPosition(vector3d(clickPos.X,clickPos.Y,0));
			marker->SetName(L"autopilot marker");
			AddObject(marker);
			UpdateCameraDistance(0);//to show marker

			ins->object = marker;
			

		}
		else if (buttons&2)
		{

			//resourceManager->SetSceneManager(sceneManager);
			gameRoot->UseSceneManager(DG_Game::VIEW_REALSPACE);
			SpaceObject* marker = resourceManager->MakeMarker();
			marker->SetIntProperty(SpaceObject::EMIT_GRAVITY,0);
			marker->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
			marker->SetPosition(vector3d(clickPos.X,clickPos.Y,0));
			marker->SetName(L"autopilot FTL marker");
			AddObject(marker);
			UpdateCameraDistance(0);//to show marker

			//clickPos += shiftToGalaxy;
			//clickPos/=LIGHTYEAR;
			clickPos = GetCoordinatesOnScreen(lastClick,1);
			wprintf(L" Autopilot FTL to: %f,%f\r\n",clickPos.X,clickPos.Y);

			AutopilotInstruction* ins = new AutopilotInstruction();//delete in ~SpaceObject or in autopilot processing
			ins->instruction = AutopilotInstruction::AP_FTL_TO;
			ins->vector1 = clickPos;
			ins->phase = 0;
			gameRoot->GetPlayerShip()->AddAutopilot(ins);

			ins->object = marker;

		}
		else if (buttons&4)
		{

			//playerShip->SetPosition(vector3d(x,y,0));//DEBUG
			vector3d clickedPosition=vector3d(clickPos.X,clickPos.Y,0);

			AutopilotInstruction* ins = new AutopilotInstruction();//delete in ~SpaceObject or in autopilot processing

			GravityInfo* gravInfo = gamePhysics->GetGravityInfo(clickedPosition);
			if (gravInfo->maxGravityObject)
			{//only if there is dominant object
				ins->instruction = AutopilotInstruction::AP_FLY_TO_ORBIT;
				ins->paramObject = gravInfo->maxGravityObject;
				ins->value1 = (clickedPosition - gravInfo->maxGravityObject->GetPosition()).getLength();
				ins->value2 = 0;//maxspeed = 0

				wprintf(L" Autopilot orbiting to: %ws\r\n",ins->paramObject->GetName().c_str());
			}
			else
			{
				ins->instruction = AutopilotInstruction::AP_FLY_TO;
				ins->vector1 = clickPos;
				ins->value1 = gameRoot->GetPlayerShip()->GetSpeed().getLength();
				if (ins->value1>LIGHTSPEED*0.5)
					ins->value1 = LIGHTSPEED*0.5;
				ins->value2 = 0;//maxspeed = 0

				wprintf(L" Autopilot orbiting to: %f,%f\r\n",clickPos.X,clickPos.Y);
			}
			delete gravInfo;

			ins->prepareText = true;
			ins->textInfo = L"";
			ins->phase = 0;
			gameRoot->GetPlayerShip()->AddAutopilot(ins);

			gameRoot->UseSceneManager(DG_Game::VIEW_REALSPACE);
			SpaceObject* marker = resourceManager->MakeMarker();
			marker->SetIntProperty(SpaceObject::EMIT_GRAVITY,0);
			marker->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
			marker->SetPosition(clickedPosition);
			marker->SetName(L"autopilot orbiting marker");

			ins->object = marker;

			AddObject(marker);
			UpdateCameraDistance(0);//to show marker
		}
		else
		{
			clickPos = GetCoordinatesOnScreen(lastClick,1);
			wprintf(L" Mouse click on map: (%.10f,%.10f)\r\n",clickPos.X,clickPos.Y);
		}
	}


		if(eventReceiver->IsKeyPressed((irr::EKEY_CODE)KEY_PSEUDO_MOUSEWHEELUP))
		{
			cameraDistanceDegree-=200;
			goto UpdateCameraForMouseWheel;

		}
		if(eventReceiver->IsKeyPressed((irr::EKEY_CODE)KEY_PSEUDO_MOUSEWHEELDOWN))
		{
			cameraDistanceDegree+=200;

UpdateCameraForMouseWheel:
			vector2ds mousePos = eventReceiver->GetMousePosition();
			f64 oldScale = mapScale;
			core::dimension2d<u32> screenSize = videoDriver->getScreenSize();
			f64 kfov = tan(camera->getFOV()*0.5)*200/mapScale;//200 = 2 * 100, 100 is cameradistance
			vector2d zoomCenter;
			zoomCenter.X=kfov*((((f64)mousePos.X)-screenSize.Width*.5)/screenSize.Height);//-0.5 .. +0.5
			zoomCenter.Y=-kfov*(((f64)mousePos.Y)/screenSize.Height-0.5);
			//wprintf(L" Mouse wheel: %f,%f\r\n",zoomCenter.X,zoomCenter.Y);//DEBUG

			UpdateCameraDistance(1);

			centerOfMap+=zoomCenter*(1-oldScale/mapScale);

			UpdateCameraDistance(0);
		}


	text_string debug_text(L"Map scale: ");
	debug_text += cameraDistanceDegree;
	debug_text += L"\r\nGrid size: ";
	//debug_text += gridCellSize;
	if (gridCellSize>=0)
	{
		debug_text += L"1";
		for (s32 i=0;i<(s32)gridCellSize;i++)
		{
			debug_text += L"0";
		}
	}
	else
	{
		debug_text += L"0.";
		for (s32 i=(s32)gridCellSize;i<-1;i++)
		{
			debug_text += L"0";
		}
		debug_text += L"1";
	}
	debug_text += L" l.y.";
	simpleTextToDisplay->setText(debug_text.c_str());


	//TODO: use resourceManager to render?
	//videoDriver->beginScene(true, true, video::SColor(255,20,20,20));
	videoDriver->beginScene(true, true, video::SColor(255,0,0,0));
	sceneManager->drawAll();
	device->getGUIEnvironment()->drawAll();
	videoDriver->endScene();
}

//flags: 1 - only recalc mapScale
void MapSpaceView::UpdateCameraDistance(u32 flags)
{
	u32 i;
	f64 gridScale;
	vector2d gridShift;

	if (cameraDistanceDegree<-180)//1 unit have size about whole screen
		cameraDistanceDegree=-180;

	//convert distance to scale
	mapScale = 30.0*exp(cameraDistanceDegree*-0.003);

	if ((flags&1)!=0)
		return;

	//update scale and position of all objects
	for (i=0;i<MapObjectList.size();i++)
	{
		//MapObjectList[i]->UpdatePhysics(time);
		MapObjectList[i]->UpdatePosition(mapScale,centerOfMap);
	}

	//draw grid

	/*
	//convert map scale into grid scale (unoptimized version)
	gridScale = mapScale*LIGHTYEAR*2.0;

	//round grid scale to (110,1100) range
	while (gridScale>1100.0)
		gridScale*=0.1;
	while (gridScale<110.0)
		gridScale*=10.;
	*/

	//convert map scale into grid scale (optimized version)
	gridScale = cameraDistanceDegree+220.523766502312287933;//add shift
	gridCellSize = floor(gridScale*0.001302883445709755482953);
	gridScale -= gridCellSize*767.52836433134856133933;//round degree to ln(10)/0.003
	gridScale = 1100.0*exp(gridScale*-0.003);//result will be in range (110,1100)
	gridCellSize -= 11;//now 0 means that grid size is 1 l.y.


	if (gridCellSize>=0)
	{
		//grid cell is l.y or larger - shift grid to galaxy center
		gridShift = -(centerOfMap+shiftToGalaxy)*mapScale;
	}
	else
	{
		//grid cell is less than l.y - shift grid to qudrant grid
		gridShift = -(centerOfMap+shiftToQuadrant)*mapScale;
	}

	//round grid shift to 1/20 of gridScale (i.e. to one texture step)
	gridShift.X -= floor(20.0*gridShift.X/gridScale)*gridScale*0.05;
	gridShift.Y -= floor(20.0*gridShift.Y/gridScale)*gridScale*0.05;

	//update grid scene node
	gridNode->setScale(vector3df((f32)gridScale,(f32)gridScale,1.0f));
	gridNode->setPosition(vector3df((f32)gridShift.X,(f32)gridShift.Y,0.1f));
}

void MapSpaceView::ClearObjects()
{
	for (u32 i=0;i<MapObjectList.size();i++)
	{
		delete MapObjectList[i];
		MapObjectList[i] = 0;
	}
	MapObjectList.clear();
}


void MapSpaceView::Close()
{
	ClearObjects();
	sceneManager->drop();
}


//#########################################################################
//FTLView

void FTLView::Init()
{
	resourceManager = gameRoot->GetResourceManager();

	videoDriver = resourceManager->GetVideoDriver();
	device = resourceManager->GetDevice();
	eventReceiver = resourceManager->GetEventReceiver();
	viewHUD = resourceManager->GetHUD(DG_Game::VIEW_FTL);

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

	forceField = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/plane.irrmesh"));
	if (forceField)
	{
		forceField->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
		forceField->setMaterialFlag(video::EMF_LIGHTING, false);
		forceField->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/forcefield_ftl1.bmp"));
		forceField->setScale(vector3df(3.0f));
	}


	simpleTextToDisplay = device->getGUIEnvironment()->addStaticText(
		L"Diagnostic very-very-very-very-very-very-very-very-long 3\r\nSecond line", core::rect<s32>(5, 5, 400, 200),false,true,viewHUD);
	simpleTextToDisplay->setOverrideColor(video::SColor(255, 0, 0, 0));

	for (u32 i = 0;i<50;i++)
	{
		FTLStripe* stripe1 = new FTLStripe();
		stripe1->node = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/plane.irrmesh"));
		if (stripe1->node)
		{
			stripe1->node->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
			stripe1->node->setMaterialFlag(video::EMF_LIGHTING, true);
			stripe1->node->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/stripe1.bmp"));
			stripe1->node->setScale(vector3df(3.f,100.0f,1.0f));
		}
		stripes.push_back(stripe1);
	}
}

void FTLView::Prepare()
{
}

void FTLView::Activate()
{
	playerShip = gameRoot->GetPlayerShip();

	angle = playerShip->GetFloatProperty(SpaceObject::ROTATION_ANGLE);

	playerShipNode->setRotation(vector3df(0,0,(f32)(angle*RADTODEG64)));
	forceField->setRotation(vector3df(0,0,(f32)(angle*RADTODEG64)));
	forceField->setPosition(vector3df((f32)(-0.6*cos(angle)),(f32)(-0.6*sin(angle)),-0.1f));

	for (u32 i=0;i<stripes.size();i++)
	{
		f64 brightness;//0 - green, 1 - white
		//f64 color;//0 - a bit to red, 1 - a bit to blue
		u32 red, green, blue;
		//stripes[i]->angle = (GlobalURNG::Instance().GenerateByte()-127)*0.5*TWO_PI/255;//-pi/2 .. +pi/2
		//stripes[i]->angle = GlobalURNG::Instance().GenerateByte()/255.0;//-pi/2 .. +pi/2
		stripes[i]->angle = 1.0*i/stripes.size();//uniformly
		stripes[i]->speed = (GlobalURNG::Instance().GenerateByte()-127)*0.0005;
		//stripes[i]->acceleration = (GlobalURNG::Instance().GenerateByte()-127)*0.002;//-0.254 .. +0.256
		stripes[i]->width = 0.5+GlobalURNG::Instance().GenerateByte()/255.0;
		stripes[i]->node->setScale(vector3df((f32)(3.0*stripes[i]->width),100.0f,1.0f));
		stripes[i]->node->setRotation(vector3df(0,0,(f32)((angle+TWO_PI*0.25)*RADTODEG64)));
		brightness = 0.7+0.3*GlobalURNG::Instance().GenerateByte()/255.0;
		//color = GlobalURNG::Instance().GenerateByte()/255.0;
		green = (u32)(brightness*255.0);
		red = (u32)(brightness*255.0);
		blue = (u32)(brightness*255.0);
		stripes[i]->node->getMaterial(0).EmissiveColor.set(255,red,green,blue);
	}

	for (u32 i=0;i<flowSectorCount;i++)
		flowSectors[i]=0;

	//sceneManager->addSceneNode(
}

void FTLView::Update(f64 frameDeltaTime)
{
	//if (playerShip->GetMotionType()!=SpaceObject::MOTION_FTL)
	if (playerShip->GetIntProperty(SpaceObject::MOTION_TYPE)!=SpaceObject::MOTION_FTL)
	{
		DisplayMessage(L"Drop out of FTL due to high gravity");
		//gameRoot->ActivateRealSpace();
		//gameRoot->SwitchView(DG_Game::VIEW_REALSPACE);
	}
	if (eventReceiver->IsKeyPressed(irr::KEY_ESCAPE))
	{
		DisplayMessage(L"Manual exit from FTL");
		playerShip->BreakFTL(100.0);
		//gameRoot->ActivateRealSpace();
		//gameRoot->SwitchView(DG_Game::VIEW_REALSPACE);
	}

	if (eventReceiver->IsKeyPressed(irr::KEY_KEY_X))
	{
		text_string galaxyCoords=L"Coordinates: ";
		galaxyCoords+=print_f64(playerShip->GetGalaxyCoordinates().X,L"%.010f");
		galaxyCoords+=L", ";
		galaxyCoords+=print_f64(playerShip->GetGalaxyCoordinates().Y,L"%.010f");
		DisplayMessage(galaxyCoords);
	}
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

	gamePhysics->Update(frameDeltaTime);

	{
		vector2d playerPos = playerShip->GetGalaxyCoordinates();
		text_string debug_text(L"FTL\r\n");
		debug_text += L"Coordinates: ";
		debug_text += print_f64(playerPos.X,L"%.01f,");
		debug_text += print_f64(playerPos.Y,L"%.01f\r\n");
		f64 remainingTime = playerShip->GetFloatProperty(SpaceObject::FTL_REMAINING_TIME);
		if (remainingTime<1000000)
		{
			debug_text += L"Remaining time: ";
			debug_text += print_f64(remainingTime,L"%.01f");
			debug_text += L"\r\n";
		}
		debug_text += playerShip->GetAutopilotInfo();
		simpleTextToDisplay->setText(debug_text.c_str());
	}

	{
		f64 timeAdd = 1.0*frameDeltaTime*gamePhysics->GetTimeSpeed();
		if (gamePhysics->GetTimeSpeed()>30.0)
			timeAdd=frameDeltaTime*30.0;
		f64 kx = cos(angle+TWO_PI*0.25);
		f64 ky = sin(angle+TWO_PI*0.25);
		f64 fading = exp(-timeAdd*0.1);
		f64 acceleration;
		f64 x,y;
		f64 angleStripe;
		s32 sector;
		for (u32 i=0;i<flowSectorCount;i++)
		{
			//if (flowSectors[i]>0)
				flowSectors[i]=0;
			if (GlobalURNG::Instance().GenerateByte()<3)
				flowSectors[i]=2;

		}
		for (u32 i=0;i<stripes.size();i++)
		{
			bool cycled=false;
			//sector = (s32)((0.5+2.0*stripes[i]->angle/TWO_PI)*flowSectorCount);

			if (stripes[i]->angle>=1.0)
			{
				stripes[i]->angle=modf(stripes[i]->angle,&x);
				cycled=true;
			}
			if (stripes[i]->angle<0.0)
			{
				stripes[i]->angle=1.0+modf(stripes[i]->angle,&x);
				cycled=true;
			}
			sector = (s32)floor(stripes[i]->angle*flowSectorCount);
			if (cycled)
			{
				stripes[i]->width = 0.5+GlobalURNG::Instance().GenerateByte()/255.0;
				stripes[i]->node->setScale(vector3df((f32)(3.0*stripes[i]->width),100.0f,1.0f));
			}
			flowSectors[sector]++;
		}

		for (u32 i=0;i<stripes.size();i++)
		{

			sector = (s32)floor(stripes[i]->angle*flowSectorCount);

			angleStripe = (stripes[i]->angle-0.5)*TWO_PI*0.5;
			x = 15.0*sin(angleStripe);
			y = 15.0*cos(angleStripe);

			acceleration = (flowSectors[(sector+flowSectorCount-1)%flowSectorCount]-flowSectors[(sector+1)%flowSectorCount])*0.03;

			stripes[i]->angle+=timeAdd*(stripes[i]->speed+0.5*timeAdd*acceleration);
			stripes[i]->speed+=timeAdd*acceleration;
			stripes[i]->speed*=fading;
			stripes[i]->node->setPosition(vector3df((f32)(x*kx),(f32)(x*ky),(f32)y));

		}
	}

	//TODO: use resourceManager to render?
	//videoDriver->beginScene(true, true, video::SColor(255,20,200,20));
	videoDriver->beginScene(true, true, video::SColor(255,10,100,10));
	sceneManager->drawAll();
	device->getGUIEnvironment()->drawAll();
	videoDriver->endScene();
}

void FTLView::Close()
{
	for (u32 i = 0;i<stripes.size();i++)
	{
		delete stripes[i];
	}
	stripes.clear();

	sceneManager->drop();
}

//#########################################################################
//QuasiSpaceView

void QuasiSpaceView::Init()
{
	resourceManager = gameRoot->GetResourceManager();

	videoDriver = resourceManager->GetVideoDriver();
	device = resourceManager->GetDevice();
	eventReceiver = resourceManager->GetEventReceiver();
	viewHUD = resourceManager->GetHUD(DG_Game::VIEW_QUASISPACE);

	sceneManager->clear();

	resourceManager->SetSceneManager(sceneManager);

	playerShipNode  = resourceManager->NewShipNode();

	/*
	SceneNode* bubble = sceneManager->addSphereSceneNode((f32)0.75,16);
	if (bubble)
	{
		bubble->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/yellow.bmp"));
		//bubble->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
		bubble->setMaterialFlag(video::EMF_LIGHTING, false);
		bubble->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
		//bubble->getMaterial(0).EmissiveColor.set(255,64,64,64);
	}*/

	forceField = sceneManager->addMeshSceneNode(sceneManager->getMesh(RESOURCE_PATH"/plane.irrmesh"));
	if (forceField)
	{
		forceField->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
		forceField->setMaterialFlag(video::EMF_LIGHTING, false);
		forceField->setMaterialTexture(0, videoDriver->getTexture(RESOURCE_PATH"/forcefield_sph1.bmp"));
		forceField->setScale(vector3df(1.5f));
		forceField->setPosition(vector3df(0.0f));
	}


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

void QuasiSpaceView::Prepare()
{
}


void QuasiSpaceView::Activate()
{
	playerShip = gameRoot->GetPlayerShip();

	playerShipNode->setRotation(vector3df(0,0,(f32)(playerShip->GetFloatProperty(SpaceObject::ROTATION_ANGLE)*RADTODEG64)));
	//sceneManager->addSceneNode(
}

void QuasiSpaceView::Update(f64 frameDeltaTime)
{
	//if (playerShip->GetMotionType()!=SpaceObject::MOTION_PLUSMINUS)
	if (playerShip->GetIntProperty(SpaceObject::MOTION_TYPE)!=SpaceObject::MOTION_PLUSMINUS)
	{
		DisplayMessage(L"Drop out of QuasiSpace");
		//playerShip->BreakQuasiSpace();
		//gameRoot->ActivateRealSpace();
		//gameRoot->SwitchView(DG_Game::VIEW_REALSPACE);
	}

	if (eventReceiver->IsKeyPressed(irr::KEY_KEY_X))
	{
		playerShip->DebugPrint_QuasiSpace();
	}

	/*
	if (eventReceiver->IsKeyPressed(irr::KEY_ESCAPE))
	{
		DisplayMessage(L"Manual exit from QuasiSpace");
		playerShip->BreakQuasiSpace();
		gameRoot->SwitchView(DG_Game::VIEW_REALSPACE);
	}*/

	gamePhysics->Update(frameDeltaTime);

	//TODO: use resourceManager to render?
	videoDriver->beginScene(true, true, video::SColor(255,200,20,200));
	sceneManager->drawAll();
	device->getGUIEnvironment()->drawAll();
	videoDriver->endScene();
}

void QuasiSpaceView::Close()
{
	sceneManager->drop();
}


//#########################################################################
//HyperSpaceView

void HyperSpaceView::Init()
{
	resourceManager = gameRoot->GetResourceManager();

	videoDriver = resourceManager->GetVideoDriver();
	device = resourceManager->GetDevice();
	eventReceiver = resourceManager->GetEventReceiver();
	viewHUD = resourceManager->GetHUD(DG_Game::VIEW_HYPERSPACE);

	sceneManager->clear();

	resourceManager->SetSceneManager(sceneManager);

	simpleTextToDisplay = device->getGUIEnvironment()->addStaticText(
		L"Diagnostic very-very-very-very-very-very-very-very-long 1\r\nSecond line", core::rect<s32>(5, 5, 400, 200),false,true,viewHUD);
	simpleTextToDisplay->setOverrideColor(video::SColor(255, 0, 0, 0));

}

void HyperSpaceView::Prepare()
{
	playerShip = gameRoot->GetPlayerShip();

	resourceManager->SetSceneManager(sceneManager);
	sceneManager->clear();
	resourceManager->LoadNodesForShip((SpaceObject*)playerShip);

	camera = sceneManager->addCameraSceneNode();
	if (camera)
	{
		camera->setPosition(vector3df(0,0,-20.f));
		camera->setTarget(vector3df(0));
		camera->setFOV(0.7f);
	}
}

void HyperSpaceView::Activate()
{
}

void HyperSpaceView::AddStar(GalaxyStarSystem* starSystem)
{
	vector3d starHyperPos;
	vector2d starGalaxyPos;
	vector2ds galaxyQuadrant = starSystem->GetGalaxyQuadrant();
	SpaceObject* starMarker = resourceManager->MakeGravityWell(0.01*LIGHTYEAR/HYPERSPACE_SCALE);

	/*
	starGalaxyPos = starSystem->GetGalaxyCoordinates();
	starHyperPos.X = starGalaxyPos.X*LIGHTYEAR/HYPERSPACE_SCALE;
	starHyperPos.Y = starGalaxyPos.Y*LIGHTYEAR/HYPERSPACE_SCALE;
	starHyperPos.Z = 0;*/
	starHyperPos = gameRoot->GetGalaxy()->Galaxy2HyperSpace(starSystem->GetGalaxyCoordinates());

	starMarker->SetIntProperty(SpaceObject::EMIT_GRAVITY,0);
	starMarker->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
	starMarker->SetIntProperty(SpaceObject::TRAVEL_TO_X,galaxyQuadrant.X);
	starMarker->SetIntProperty(SpaceObject::TRAVEL_TO_Y,galaxyQuadrant.Y);
	starMarker->SetPosition(starHyperPos);
	starMarker->SetName(starSystem->GetName());
}

void HyperSpaceView::RemoveAllStars()
{
	core::array<SpaceObject*> foundObjects;
	gameRoot->UseSceneManager(DG_Game::VIEW_HYPERSPACE);

	gamePhysics->GetObjectsAtDistance(&foundObjects,vector3d(0,0,0),1e60);//all
	for (u32 i=0;i<foundObjects.size();i++)
	{
		if (foundObjects[i]->GetIntProperty(SpaceObject::GRAVITY_WELL)!=0)
		{
			foundObjects[i]->Delete();
		}
	}
}

//flags: none
vector2d HyperSpaceView::GetCoordinatesOnScreen(vector2ds pixelCoords, u32 flags)
{
	core::dimension2d<u32> screenSize = videoDriver->getScreenSize();
	f64 kfov = 2*tan(camera->getFOV()*0.5)*cameraDistance;
	vector2d gameCoordinates;
	gameCoordinates.X = pixelCoords.X;
	gameCoordinates.Y = pixelCoords.Y;
	gameCoordinates.X=playerShip->GetPosition().X+kfov*((gameCoordinates.X-screenSize.Width*.5)/screenSize.Height);
	gameCoordinates.Y=playerShip->GetPosition().Y-kfov*(gameCoordinates.Y/screenSize.Height-0.5);

	/*
	if ((flags&1)!=0)
	{
		//galaxy coordinates needed
		gameCoordinates*=HYPERSPACE_SCALE/LIGHTYEAR;
		
	}*/

	return gameCoordinates;
}

void HyperSpaceView::Update(f64 frameDeltaTime)
{
	if (eventReceiver->IsKeyPressed(irr::KEY_KEY_X))
	{
		playerShip->SetSpeed(vector3d(0,LIGHTSPEED*0.85,0));

	}

	if(eventReceiver->IsKeyDown(irr::KEY_KEY_W))
		playerShip->SetControl(playerShip->GetControlThrust(),SpaceObject::CONTROL_THRUST_RELATIVE);
	else if(eventReceiver->IsKeyDown(irr::KEY_KEY_S))
		playerShip->SetControl(-playerShip->GetControlThrust(),SpaceObject::CONTROL_THRUST_RELATIVE);
	else
		playerShip->SetControl(0.0,SpaceObject::CONTROL_THRUST_ABSOLUTE);

	if(eventReceiver->IsKeyDown(irr::KEY_KEY_A))
		playerShip->SetControl(1.0,SpaceObject::CONTROL_ROTATION_SPEED_RELATIVE);
	else if(eventReceiver->IsKeyDown(irr::KEY_KEY_D))
		playerShip->SetControl(-1.0,SpaceObject::CONTROL_ROTATION_SPEED_RELATIVE);
	else
		playerShip->SetControl(0,SpaceObject::CONTROL_ROTATION_SPEED_ABSOLUTE);

	if(eventReceiver->IsKeyPressed(irr::KEY_KEY_1))
		playerShip->SetControlThrust(1.0); //playerThrust = 1.0;
	if(eventReceiver->IsKeyPressed(irr::KEY_KEY_2))
		playerShip->SetControlThrust(0.1); //playerThrust = 0.1;
	if(eventReceiver->IsKeyPressed(irr::KEY_KEY_3))
		playerShip->SetControlThrust(0.01); //playerThrust = 0.01;
	if(eventReceiver->IsKeyPressed(irr::KEY_KEY_4))
		playerShip->SetControlThrust(0.001); //playerThrust = 0.001;
	if(eventReceiver->IsKeyPressed(irr::KEY_KEY_5))
		playerShip->SetControlThrust(0.0001); //playerThrust = 0.0001;
	if(eventReceiver->IsKeyPressed(irr::KEY_KEY_6))
		playerShip->SetControlThrust(0.00001); //playerThrust = 0.00001;

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

	if (eventReceiver->IsKeyPressed(irr::KEY_KEY_Z))
	{
		AutopilotInstruction* ins = new AutopilotInstruction();//delete in ~SpaceObject or in autopilot processing
		ins->instruction = AutopilotInstruction::AP_SETSPEED;
		ins->vector1 = vector2d(0);
		playerShip->AddAutopilot(ins);
	}

	if (eventReceiver->IsKeyPressed(irr::KEY_KEY_H))
	{
		gameRoot->BreakHyperSpace();
		return;
	}

	if (eventReceiver->IsKeyPressed(irr::KEY_KEY_T))
	{
		playerShip->ScanSpace(1e4);
	}

	if (eventReceiver->IsKeyPressed(irr::KEY_ESCAPE))
		playerShip->BreakAutopilot();


	if(eventReceiver->IsKeyDown(irr::KEY_UP))
	{
		cameraDistanceDegree+=frameDeltaTime*2000.0;
		UpdateCameraDistance();
	}

	if(eventReceiver->IsKeyDown(irr::KEY_DOWN))
	{
		cameraDistanceDegree-=frameDeltaTime*2000.0;
		UpdateCameraDistance();
	}


	if(eventReceiver->IsKeyPressed((irr::EKEY_CODE)KEY_PSEUDO_MOUSEWHEELUP))
	{
		cameraDistanceDegree-=200;
		UpdateCameraDistance();
	}
	if(eventReceiver->IsKeyPressed((irr::EKEY_CODE)KEY_PSEUDO_MOUSEWHEELDOWN))
	{
		cameraDistanceDegree+=200;
		UpdateCameraDistance();
	}


	vector2ds lastClick = eventReceiver->GetLastMouseClick();
	if (lastClick.X>-1)
	{
		vector2d clickPos = GetCoordinatesOnScreen(lastClick,0);
		eventReceiver->RemoveLastMouseClick();
		u32 buttons = eventReceiver->GetLastMouseClickButtons();

		
		if (buttons&1)
		{
			//wprintf(L" Autopilot fly to: %f,%f\r\n",clickPos.X,clickPos.Y);//coords are DEBUG

			AutopilotInstruction* ins = new AutopilotInstruction();//delete in ~SpaceObject or in autopilot processing
			ins->instruction = AutopilotInstruction::AP_HYPERSPACE_FLY_TO;
			ins->prepareText = true;
			ins->textInfo = L"";
			ins->vector1 = clickPos;
			ins->phase = 0;
			playerShip->AddAutopilot(ins);

			resourceManager->SetSceneManager(sceneManager);
			SpaceObject* marker = resourceManager->MakeMarker();
			marker->SetIntProperty(SpaceObject::EMIT_GRAVITY,0);
			marker->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
			marker->SetPosition(vector3d(clickPos.X,clickPos.Y,0));
			marker->SetName(L"autopilot marker");
			UpdateCameraDistance();//to show marker

			ins->object = marker;

		}
		/*else if (buttons&2)
		{
			//vector2d destination = vector2d(x,y);
			//destination /=LIGHTYEAR;
			//destination += gamePhysics->GetGalaxyCoordinatesOfCenter();
			clickPos = GetCoordinatesOnScreen(lastClick,1);
			//x+=phy
			wprintf(L" Autopilot FTL to: %f,%f\r\n",clickPos.X,clickPos.Y);

			AutopilotInstruction* ins = new AutopilotInstruction();//delete in ~SpaceObject or in autopilot processing
			ins->instruction = AutopilotInstruction::AP_FTL_TO;
			ins->vector1 = clickPos;//vector2d(x,y);
			ins->phase = 0;
			playerShip->AddAutopilot(ins);

			resourceManager->SetSceneManager(sceneManager);
			SpaceObject* marker = resourceManager->MakeMarker();
			marker->SetIntProperty(SpaceObject::EMIT_GRAVITY,0);
			marker->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
			marker->SetPosition(vector3d(clickPos.X,clickPos.Y,0));
			marker->SetName(L"autopilot FTL marker");
			UpdateCameraDistance();//to show marker

			ins->object = marker;

		}
		else if (buttons&4)
		{

			//playerShip->SetPosition(vector3d(x,y,0));//DEBUG
			vector3d clickedPosition=vector3d(clickPos.X,clickPos.Y,0);

			AutopilotInstruction* ins = new AutopilotInstruction();//delete in ~SpaceObject or in autopilot processing

			GravityInfo* gravInfo = gamePhysics->GetGravityInfo(clickedPosition);
			if (gravInfo->maxGravityObject)
			{//only if there is dominant object
				ins->instruction = AutopilotInstruction::AP_FLY_TO_ORBIT;
				ins->paramObject = gravInfo->maxGravityObject;
				ins->value1 = (clickedPosition - gravInfo->maxGravityObject->GetPosition()).getLength();
				ins->value2 = 0;//maxspeed = 0

				wprintf(L" Autopilot orbiting to: %ws\r\n",ins->paramObject->GetName().c_str());
			}
			else
			{
				wprintf(L" Autopilot orbiting to: %f,%f\r\n",clickPos.X,clickPos.Y);

				ins->instruction = AutopilotInstruction::AP_FLY_TO;
				ins->vector1 = clickPos;//vector2d(x,y);
				ins->value1 = playerShip->GetSpeed().getLength();
				if (ins->value1>LIGHTSPEED*0.5)
					ins->value1 = LIGHTSPEED*0.5;
				ins->value2 = 0;//maxspeed = 0
			}
			delete gravInfo;

			ins->prepareText = true;
			ins->textInfo = L"";
			ins->phase = 0;
			playerShip->AddAutopilot(ins);

			resourceManager->SetSceneManager(sceneManager);
			SpaceObject* marker = resourceManager->MakeMarker();
			marker->SetIntProperty(SpaceObject::EMIT_GRAVITY,0);
			marker->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
			marker->SetPosition(clickedPosition);
			marker->SetName(L"autopilot orbiting marker");
			UpdateCameraDistance();//to show marker

			ins->object = marker;
		}*/
		else
		{
			//wprintf(L" Mouse click on: %f,%f\r\n",clickPos.X,clickPos.Y);//DEBUG
			wprintf(L" Mouse click somewhere in HyperSpace...\r\n");
		}
	}

	{
		text_string debug_text(L"HyperSpace\r\nSpeed: ");
		f64 playerSpeed;

		playerSpeed = playerShip->GetSpeed().getLength();
		debug_text += playerSpeed;
		debug_text += L" km/s\r\n";
		debug_text += (playerSpeed/LIGHTSPEED);
		debug_text += L" c; \r\nTwirl: ";
		debug_text += gamePhysics->GetHyperSpaceTwirl(playerShip->GetPosition());
		debug_text += L"\r\n";
		debug_text += playerShip->GetAutopilotInfo();
		simpleTextToDisplay->setText(debug_text.c_str());
	}

	{
		core::array<SpaceObject*> foundObjects;
		gamePhysics->GetObjectsAtDistance(&foundObjects,playerShip->GetPosition(),1e4);
		for (u32 i=0;i<foundObjects.size();i++)
		{
			if (foundObjects[i]->GetIntProperty(SpaceObject::GRAVITY_WELL)==1)
			{
				vector3d position;
				vector2ds quadrant;
				ResourceManager* pseudoRM;
				GalaxyStarSystem* star;
				Galaxy* galaxy = gameRoot->GetGalaxy();
				GamePhysics* pseudoPhysics;
				core::array<SpaceObject*> systemObjects;

				pseudoRM = new ResourceManager();
				pseudoPhysics = new GamePhysics();
				pseudoRM->Setup(0,0,0,0,pseudoPhysics);
				quadrant.X = foundObjects[i]->GetIntProperty(SpaceObject::TRAVEL_TO_X);
				quadrant.Y = foundObjects[i]->GetIntProperty(SpaceObject::TRAVEL_TO_Y);
				star = galaxy->GetStarSystem(quadrant);
				star->GenerateStarSystem(pseudoRM,galaxy);

				foundObjects[i]->SetIntProperty(SpaceObject::GRAVITY_WELL,2);
				foundObjects[i]->SetIntProperty(SpaceObject::VISIBLE_TO_PLAYER,0);
				position = foundObjects[i]->GetPosition();

				pseudoPhysics->globalTime = gamePhysics->globalTime;
				pseudoPhysics->Update(0);
				pseudoPhysics->GetObjectsAtDistance(&systemObjects,vector3d(0),LIGHTYEAR);
				for (u32 j=0;j<systemObjects.size();j++)
				{
					if (systemObjects[j]->GetIntProperty(SpaceObject::EMIT_GRAVITY)!=0)
					{
						SpaceObject* objectMarker;
						vector3d pos2;
						f64 gravRadius = sqrt(systemObjects[j]->GetFloatProperty(SpaceObject::MASS))*0.05;
						objectMarker = resourceManager->MakeGravityWell(gravRadius);

						objectMarker->SetIntProperty(SpaceObject::EMIT_GRAVITY,0);
						objectMarker->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
						objectMarker->SetIntProperty(SpaceObject::GRAVITY_WELL,2);
						pos2 = position+systemObjects[j]->GetPosition()/HYPERSPACE_SCALE;
						objectMarker->SetPosition(pos2);
					}
				}
				UpdateCameraDistance();//to display markers

				star->unlock(0);//free if not used elsewhere
				delete pseudoRM;
				delete pseudoPhysics;
 			}
		}
	}

	gamePhysics->Update(frameDeltaTime);
	gamePhysics->UpdateNodes(playerShip,1);

	videoDriver->beginScene(true, true, video::SColor(255,250,120,0));
	sceneManager->drawAll();
	device->getGUIEnvironment()->drawAll();
	videoDriver->endScene();
}

void HyperSpaceView::Close()
{
	sceneManager->drop();
}


void HyperSpaceView::UpdateCameraDistance()
{
	if (cameraDistanceDegree<-100)
		cameraDistanceDegree=-100;
	if (cameraDistanceDegree>3850)//whole circle R = 6 ly is visible for player
		cameraDistanceDegree=3850;
	/*if (cameraDistanceDegree>4800)
		cameraDistanceDegree=4800;*/

	cameraDistance = 30.0*exp(cameraDistanceDegree*0.003);

	if (cameraDistance<50.0f)
	{//modified mainly for wormholes
		camera->setFarValue(100.f);
		camera->setNearValue(1.f);
	}
	else
	{
		camera->setFarValue((f32)(cameraDistance*2.0));
		camera->setNearValue((f32)(cameraDistance*0.5));
	}
	gamePhysics->UpdateMarkers(cameraDistance);

	camera->setPosition(vector3df(0,0,-(f32)cameraDistance));//update camera look-from point
}


//#########################################################################
//DG_Game


// Processes parameters and initializes the game
s32 DG_Game::Init(s32 Count, char **Arguments) {
	// ask user for driver

	wholeGalaxy = new Galaxy();//delete in DG_Game::Close
	wholeGalaxy->Init();

	vector2d startGalaxyCoord = vector2d(0);
	currentStarSystem = wholeGalaxy->GetStartStarSystem();
	if (currentStarSystem)
	{
		startGalaxyCoord = currentStarSystem->GetGalaxyCoordinates();
		currentStarSystem->lock(1);//lock as it is stored
	}

	
	gamePhysics = new GamePhysics();//delete in DG_Game::Close
	gamePhysics->globalTime = 0;
	gamePhysics->SetGalaxyCoordinatesOfCenter(startGalaxyCoord);
	gamePhysics->SetGalaxyQuadrant(currentStarSystem->GetGalaxyQuadrant());//just in case
	gamePhysics->SetGravityCheckRadiusSQ(STAR_SYSTEM_RADIUS_LEAVE*STAR_SYSTEM_RADIUS_LEAVE*LIGHTYEAR*LIGHTYEAR);
	gamePhysics->SetTimeSpeed(1.0);
	gamePhysics->SetRoot(this);

	//wholeGalaxy->UpdatePlayerLocation(startGalaxyCoord);

	viewStack.clear();

	/*
	video::E_DRIVER_TYPE driverType=driverChoiceConsole();
	if (driverType==video::EDT_COUNT)
		return 1;
	*/
	//driverType = video::EDT_OPENGL;

	// create device

	receiver = new MyEventReceiver();//delete in DG_Game::Close

	//IrrlichtDevice* device = createDevice(driverType,
	device = createDevice(video::EDT_OPENGL,
			core::dimension2d<u32>(1024, 768), 32, false, false, false, receiver);//drop in DG_Game::Close

	if (device == 0)
		return 1; // could not create selected driver.

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();

	//driver->setTextureCreationFlag(irr::video::ETCF_ALWAYS_32_BIT,true);

	//video::ECOLOR_FORMAT cf2 =  driver->getColorFormat();

	resourceManager = new ResourceManager();//delete in DG_Game::Close
	resourceManager->Setup(device,smgr,driver,receiver,gamePhysics);

	RealSpace = new RealSpaceView();//delete in DG_Game::Close
	RealSpace->SetRoot(this);
	RealSpace->SetSceneManager(smgr);
	RealSpace->SetPhysics(gamePhysics);

	//playerShip = (PlayerShip*)resourceManager->MakeShip();
	playerShip = new PlayerShip();//delete in DG_Game::Close
	gamePhysics->AddObject((SpaceObject*)playerShip);
	//playerShip->SetGravity(false,true);
	playerShip->SetIntProperty(SpaceObject::EMIT_GRAVITY,0);
	playerShip->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,1);

	//playerShip->SetMotionType(SpaceObject::MOTION_NAVIGATION);
	playerShip->SetIntProperty(SpaceObject::MOTION_TYPE,SpaceObject::MOTION_NAVIGATION);
	//playerShip->SetRotation(90);
	playerShip->SetFloatProperty(SpaceObject::ROTATION_ANGLE,TWO_PI*0.25);//90 degrees
	playerShip->SetSpeed(vector3d(0,0,0));
	//playerShip->SetMaxThrust(100000,150);
	//playerShip->SetMaxThrust(100000,5);
	playerShip->SetFloatProperty(SpaceObject::MAX_THRUST,100000);
	playerShip->SetFloatProperty(SpaceObject::MAX_ROT_THRUST,5);
	playerShip->SetName(L"Player");
	playerShip->SetFloatProperty(SpaceObject::MAX_FTL_GRAVITY,0.003138);
	playerShip->SetFloatProperty(SpaceObject::GEOMETRY_RADIUS,0.5);
	//acceleration = 0.003138 <=> gravity = -5.75 "dgr"


	gamePhysics->SetPlayerShip(playerShip);

	//wholeGalaxy->AddNearStarSystems(gamePhysics);

	RealSpace->Init();
	//gamePhysics->GoStarSystem();
	GoStarSystem(currentStarSystem);

	playerShip->SetPosition(vector3d(LIGHTYEAR*0.07,0,0));
	playerShip->UpdateGalaxyCoordinates(0);

	prevPlayerMotion = SpaceObject::MOTION_NAVIGATION;


	gamePhysics->Activate();

	//smgr->saveScene("1.irrexp"); //DEBUG



	/*
	gamePhysics->GoStarSystem();
	RealSpace->Init();
	resourceManager->MakeBackground();
	resourceManager->MakeSimpleSystem();
	*/


	//activeView = RealSpace;


	SectorMap = new MapSpaceView();//delete in DG_Game::Close
	SectorMap->SetRoot(this);
	SectorMap->SetSceneManager(smgr->createNewSceneManager()); //drop in MapSpaceView::Close
	//SectorMap->SetDevice(device);
	//SectorMap->SetVideoDriver(driver);
	//SectorMap->SetEventReceiver(&receiver);
	SectorMap->SetPhysics(gamePhysics);
	SectorMap->Init();


	FTLSpace = new FTLView();//delete in DG_Game::Close
	FTLSpace->SetRoot(this);
	FTLSpace->SetSceneManager(smgr->createNewSceneManager()); //drop in FTLSpace::Close
	FTLSpace->SetPhysics(gamePhysics);
	FTLSpace->Init();

	QuasiSpace = new QuasiSpaceView();//delete in DG_Game::Close
	QuasiSpace->SetRoot(this);
	QuasiSpace->SetSceneManager(smgr->createNewSceneManager()); //drop in QuasiSpace::Close
	QuasiSpace->SetPhysics(gamePhysics);
	QuasiSpace->Init();

	HyperSpace = new HyperSpaceView();//delete in DG_Game::Close
	HyperSpace->SetRoot(this);
	HyperSpace->SetSceneManager(smgr->createNewSceneManager()); //drop in QuasiSpace::Close
	HyperSpace->SetPhysics(gamePhysics);
	HyperSpace->Init();

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
	f64 frameDeltaTime = (f64)(now - then) * 0.001; // Time in seconds
	
	/*
	if (frameDeltaTime<FRAME_TIME_MIN)
	{
		device->sleep(1);
		return;
	}*/


	then = now;

	if (frameDeltaTime>FRAME_TIME_MAX) frameDeltaTime = FRAME_TIME_MAX;//50 fps minimum, or slowdown game


	if (prevPlayerMotion!=playerShip->GetIntProperty(SpaceObject::MOTION_TYPE))
	{
		prevPlayerMotion = (SpaceObject::MotionType)playerShip->GetIntProperty(SpaceObject::MOTION_TYPE);
		switch(prevPlayerMotion)
		{
		case SpaceObject::MOTION_PLUSMINUS:
			SwitchView(VIEW_QUASISPACE);
			break;
		case SpaceObject::MOTION_FTL:
			SwitchView(VIEW_FTL);
			break;
		case SpaceObject::MOTION_HYPER:
			SwitchView(VIEW_HYPERSPACE);
			break;
		default:
			SwitchView(VIEW_REALSPACE);
			break;
		}
	}

	//Update game via current view
	//Game physics is updated via view due to view-dependency behaviour of physics (i.e. physics not updated in case of viewing map)
	activeView->Update(frameDeltaTime);

	switch(playerShip->GetIntProperty(SpaceObject::MOTION_TYPE))
	{
	case SpaceObject::MOTION_PLUSMINUS:
		playerShip->UpdateQuasiSpace(frameDeltaTime,wholeGalaxy);
		break;
	case SpaceObject::MOTION_HYPER:
		playerShip->UpdateGalaxyCoordinates(1);//in hyper
		wholeGalaxy->UpdatePlayerLocation(playerShip->GetGalaxyCoordinates());
		wholeGalaxy->AddHyperSpaceObjects(HyperSpace,1);//will recreate star markers only if player location has changed

		//known stars is updated by 50x50 ly, this may leads to "appearing" stars at 6 l.y. from player
		//(if x = 80*n + 70 and decreased, star located at x=80*n+49..50 could appear at x=80*n+64

		break;
	default:
		playerShip->UpdateGalaxyCoordinates(0);

		//Check that player reach border some star system and so this system should be loaded
		if (gamePhysics->IsInterstellar())
		{

			if (!gamePhysics->GetGalaxyQuadrant().equals(playerShip->GetGalaxyQuadrant()))
			{
			//update center of interstellar on changing quadrants
				//vector2ds shift = playerShip->GetGalaxyQuadrant()-gamePhysics->GetGalaxyQuadrant();
				//vector2d shiftPos = vector2d((f64)(shift.X),(f64)(shift.Y));
				vector2ds quadrant = playerShip->GetGalaxyQuadrant();
				vector2d playerGalaxyCoordinates = playerShip->GetGalaxyCoordinates();
				vector2d quadrantGalaxyCoordinates;
				vector3d playerLocalPosition;

				quadrantGalaxyCoordinates.X = 0.5+(f64)quadrant.X;
				quadrantGalaxyCoordinates.Y = 0.5+(f64)quadrant.Y;

				gamePhysics->SetGalaxyCoordinatesOfCenter(quadrantGalaxyCoordinates);
				gamePhysics->SetGalaxyQuadrant(quadrant);

				playerGalaxyCoordinates-=quadrantGalaxyCoordinates;
				playerLocalPosition.X = playerGalaxyCoordinates.X*LIGHTYEAR;
				playerLocalPosition.Y = playerGalaxyCoordinates.Y*LIGHTYEAR;
				playerLocalPosition.Z = 0;

				playerShip->SetPosition(vector3d(playerLocalPosition));

				//TODO! remove all other objects
			}

			wholeGalaxy->UpdatePlayerLocation(playerShip->GetGalaxyCoordinates()); //Could be optimized - into scope of update center of interstellar

			//TODO: this is dumb check, if FTL speed is larger than 50000c, then on 50 fps min checks may be too seldom to "catch" star system
			GalaxyStarSystem* nearStarSystem = wholeGalaxy->GetNearStarSystem(playerShip->GetGalaxyCoordinates());
			if (nearStarSystem)
			{
				GoStarSystem(nearStarSystem);
			}
		}

		//Check that player fly too far from star system and it (system) could be unloaded
		if (gamePhysics->CheckLeaveStarSystem())
		{
			{
				text_string message = L"Departed star system ";
				message += currentStarSystem->GetName();
				RealSpace->DisplayMessage(message);
			}
			//gamePhysics->GoInterstellar();

			//if (IsViewActive(VIEW_REALSPACE))
			GoInterstellar();
		}
		break;
	}

	s32 fps = driver->getFPS();

	if (lastFPS != fps)
	{
		text_string tmp(L"DangerGalaxy - first demo [");
		tmp += driver->getName();
		tmp += L"] fps: ";
		tmp += fps;

		device->setWindowCaption(tmp.c_str());
		lastFPS = fps;
	}

	//TODO: option to turn off this "yield"
	device->yield();
}

void DG_Game::Close() {
	
	//delete playerShip;//new in DG_Game::Init

	delete wholeGalaxy;//new in DG_Game::Init
	delete gamePhysics;//new in DG_Game::Init
	delete receiver;//new in DG_Game::Init

	//Close views
	QuasiSpace->Close();
	FTLSpace->Close();
	RealSpace->Close();
	SectorMap->Close();
	HyperSpace->Close();

	delete RealSpace;//new in DG_Game::Init
	delete SectorMap;//new in DG_Game::Init
	delete FTLSpace;//new in DG_Game::Init
	delete QuasiSpace;//new in DG_Game::Init
	delete HyperSpace;//new in DG_Game::Init
	delete resourceManager;//new in DG_Game::Init

	for (u32 i=0;i<viewStack.size();i++)
	{
		delete viewStack[i];//new in DG_Game::AcviateView and DG_Game::SwitchView
		viewStack[i] = 0;
	}


	//In the end, delete the Irrlicht device.
	device->drop();//create in DG_Game::Init
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

//playerGalaxyCoordinates is root for locationing
void DG_Game::GoInterstellar()
{
	vector2d playerGalaxyCoordinates;
	vector2ds quadrant;
	vector2d quadrantGalaxyCoordinates;
	vector3d playerLocalPosition;
	f64 cameraDistance = RealSpace->cameraDistanceDegree;

	gamePhysics->GoInterstellar();

	if (currentStarSystem)
	{
		currentStarSystem->unlock(1);//free
		currentStarSystem = 0;
	}

	RealSpace->Clean();
	RealSpace->Prepare();

	RealSpace->cameraDistanceDegree = cameraDistance;
	RealSpace->UpdateCameraDistance();

	resourceManager->SetSceneManager(smgr);
	resourceManager->MakeBackground();
	
	quadrant = playerShip->GetGalaxyQuadrant();
	playerGalaxyCoordinates = playerShip->GetGalaxyCoordinates();

	quadrantGalaxyCoordinates.X = 0.5+(f64)quadrant.X;
	quadrantGalaxyCoordinates.Y = 0.5+(f64)quadrant.Y;

	gamePhysics->SetGalaxyCoordinatesOfCenter(quadrantGalaxyCoordinates);
	gamePhysics->SetGalaxyQuadrant(quadrant);

	playerGalaxyCoordinates-=quadrantGalaxyCoordinates;
	playerLocalPosition.X = playerGalaxyCoordinates.X*LIGHTYEAR;
	playerLocalPosition.Y = playerGalaxyCoordinates.Y*LIGHTYEAR;
	playerLocalPosition.Z = 0;

	playerShip->SetPosition(vector3d(playerLocalPosition));

	gamePhysics->Activate();

	//wholeGalaxy->AddNearStarSystems(gamePhysics);
}

void DG_Game::GoStarSystem(GalaxyStarSystem* toStarSystem)
{
	f64 cameraDistance = RealSpace->cameraDistanceDegree;
	vector2d playerGalaxyCoordinates = playerShip->GetGalaxyCoordinates();

	vector2d playerRelativeCoordinates;
	vector2d nearStarSystemGalaxyCoordinates;

	gamePhysics->GoStarSystem();

	RealSpace->Clean();
	RealSpace->Prepare();

	resourceManager->SetSceneManager(smgr);
	resourceManager->MakeBackground();

	{
		text_string message = L"Entered to system ";
		message += toStarSystem->GetName();
		RealSpace->DisplayMessage(message);
	}

	toStarSystem->lock(1);//lock as it is stored, lock 1st as toStarSystem could be = to currentStarSystem

	if (currentStarSystem)
	{
		currentStarSystem->unlock(1);//free
		currentStarSystem = 0;
	}
	currentStarSystem = toStarSystem;

	nearStarSystemGalaxyCoordinates = toStarSystem->GetGalaxyCoordinates();
	wholeGalaxy->UpdatePlayerLocation(nearStarSystemGalaxyCoordinates);

	//resourceManager->MakeSimpleSystem();
	toStarSystem->GenerateStarSystem(resourceManager, wholeGalaxy);

	RealSpace->cameraDistanceDegree = cameraDistance;
	RealSpace->UpdateCameraDistance();

	
	playerRelativeCoordinates = (playerGalaxyCoordinates-nearStarSystemGalaxyCoordinates)*LIGHTYEAR;
	gamePhysics->SetGalaxyCoordinatesOfCenter(nearStarSystemGalaxyCoordinates);
	gamePhysics->SetGalaxyQuadrant(vector2ds((s32)floor(nearStarSystemGalaxyCoordinates.X),(s32)floor(nearStarSystemGalaxyCoordinates.Y)));//just in case
	playerShip->SetPosition(vector3d(playerRelativeCoordinates.X,playerRelativeCoordinates.Y,0));


	gamePhysics->Activate();

	//wholeGalaxy->AddNearStarSystems(gamePhysics);
}

void DG_Game::GoHyperSpace()
{
	//f64 koef = LIGHTYEAR/HYPERSPACE_SCALE;
	//vector2d playerGalaxyCoordinates = playerShip->GetGalaxyCoordinates();
	//vector3d playerHyperSpacePos = vector3d(playerGalaxyCoordinates.X*koef,playerGalaxyCoordinates.Y*koef,0);
	vector3d playerHyperSpacePos = wholeGalaxy->Galaxy2HyperSpace(playerShip->GetGalaxyCoordinates());

	playerShip->SetIntProperty(SpaceObject::MOTION_TYPE,SpaceObject::MOTION_HYPER);
	gamePhysics->GoHyperSpace();

	HyperSpace->Prepare();

	UseSceneManager(VIEW_HYPERSPACE);
	wholeGalaxy->AddHyperSpaceObjects(HyperSpace,0);

	playerShip->SetPosition(playerHyperSpacePos);
	playerShip->SetSpeed(vector3d(0));

	gamePhysics->Activate();
}

void DG_Game::BreakHyperSpace()
{
	//f64 koef = HYPERSPACE_SCALE/LIGHTYEAR;
	//vector3d playerHyperSpacePos = playerShip->GetPosition();
	//vector2d playerGalaxyCoordinates = vector2d(playerHyperSpacePos.X*koef,playerHyperSpacePos.Y*koef);

	//playerShip->SetGalaxyCoordinates(playerGalaxyCoordinates);
	//playerShip->UpdateGalaxyCoordinates(1);//in hyper
	playerShip->SetGalaxyCoordinates(wholeGalaxy->HyperSpace2Galaxy(playerShip->GetPosition()));
	playerShip->SetSpeed(vector3d(0));
	playerShip->SetIntProperty(SpaceObject::MOTION_TYPE,SpaceObject::MOTION_NAVIGATION);

	wprintf(L"Exit from HyperSpace\r\n");

	GoInterstellar();
}

void DG_Game::InternalAcviateView(ViewType newView)
{
	//Workaround for memory leak somewhere inside Irrlicht
	//I don't know how to do it better
	smgr->createNewSceneManager()->drop();

	switch(newView)
	{
	case VIEW_NONE:
		break;
	case VIEW_REALSPACE:
		/*if (gamePhysics->IsInterstellar())
		{
			GoInterstellar();
		}*/
		RealSpace->Activate();
		RealSpace->UpdateCameraDistance();
		activeView = RealSpace;
		break;
	case VIEW_SECTOR_MAP:
		SectorMap->Activate();
		SectorMap->cameraDistanceDegree = RealSpace->cameraDistanceDegree+732.4;//match zoom of map to RealSpace
		//SectorMap->cameraDistanceDegree = 8430;//DEBUG  - sector view
		SectorMap->UpdateCameraDistance(0);
		activeView = SectorMap;
		break;
	case VIEW_FTL:
		FTLSpace->Activate();
		activeView = FTLSpace;
		break;
	case VIEW_QUASISPACE:
		QuasiSpace->Activate();
		activeView = QuasiSpace;
		break;
	case VIEW_HYPERSPACE:
		HyperSpace->Activate();
		HyperSpace->cameraDistanceDegree = RealSpace->cameraDistanceDegree;
		HyperSpace->UpdateCameraDistance();
		activeView = HyperSpace;
		break;
	}
	resourceManager->ActivateHUD(newView);
}

s32 DG_Game::AcviateView(ViewType newView)
{
	if (IsViewActive(newView)) return 1;//already opened
	viewStack.push_back(new ViewType(newView));//delete in DG_Game::Close
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

	delete viewStack[viewStack.size()-1];
	viewStack[viewStack.size()-1] = new ViewType(newView);//delete in DG_Game::Close and above
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

void DG_Game::UseSceneManager(ViewType ofView)
{
	switch(ofView)
	{
	case VIEW_REALSPACE:
		resourceManager->SetSceneManager(RealSpace->GetSceneManager());
		break;
	case VIEW_FTL:
		resourceManager->SetSceneManager(RealSpace->GetSceneManager());
		break;
	case VIEW_SECTOR_MAP:
		resourceManager->SetSceneManager(RealSpace->GetSceneManager());
		break;
	case VIEW_QUASISPACE:
		resourceManager->SetSceneManager(RealSpace->GetSceneManager());
		break;
	}
	return;
}

void DG_Game::SaveGame()
{
	//TODO: Should be JSON
	FILE * saveGameFile;
	vector2d position;
	vector3d speed;
	f64 time;
	saveGameFile = fopen("save0.dgs","wb");
	fprintf(saveGameFile,"DG save file, version 0.1\r\n");
	position = GetPlayerShip()->GetGalaxyCoordinates();
	speed = GetPlayerShip()->GetSpeed();
	time = gamePhysics->globalTime;
	fprintf(saveGameFile,"gamePhysics.globalTime = %.20f\r\n",time);
	fprintf(saveGameFile,"playerShip.galaxyCoordinates.X = %.20f\r\n",position.X);
	fprintf(saveGameFile,"playerShip.galaxyCoordinates.Y = %.20f\r\n",position.Y);
	fprintf(saveGameFile,"playerShip.speed.X = %.20f\r\n",speed.X);
	fprintf(saveGameFile,"playerShip.speed.Y = %.20f\r\n",speed.Y);
	fclose(saveGameFile);
	wprintf(L"Saved to save0.dgs\r\n");
}

void DG_Game::LoadGame()
{
	FILE * saveGameFile;
	char loadingBuffer[1000];
	vector2d position;
	vector2d currentPosition;
	vector3d localPosition;
	vector3d speed;
	f64 time;

	saveGameFile = fopen("save0.dgs","rb");
	if (saveGameFile==0)
	{
		wprintf(L"Error opening save0.dgs, nothing is loaded\r\n");
	}

	speed = vector3d(0);
	position = vector2d(0);
	time = 0;

	while(!feof(saveGameFile))
	{
		fgets(loadingBuffer,1000,saveGameFile);
		if (strncmp(loadingBuffer,"playerShip.galaxyCoordinates.X = ",33)==0)
		{
			position.X = atof(loadingBuffer+33);
		}
		else if (strncmp(loadingBuffer,"playerShip.galaxyCoordinates.Y = ",33)==0)
		{
			position.Y = atof(loadingBuffer+33);
		}
		else if (strncmp(loadingBuffer,"playerShip.speed.X = ",21)==0)
		{
			speed.X = atof(loadingBuffer+21);
		}
		else if (strncmp(loadingBuffer,"playerShip.speed.Y = ",21)==0)
		{
			speed.Y = atof(loadingBuffer+21);
		}
		else if (strncmp(loadingBuffer,"gamePhysics.globalTime = ",25)==0)
		{
			time = atof(loadingBuffer+25);
		}
	}
	fclose(saveGameFile);

	gamePhysics->globalTime = time;
	localPosition = GetPlayerShip()->GetPosition();
	currentPosition = GetPlayerShip()->GetGalaxyCoordinates();
	localPosition.X += (position.X-currentPosition.X)*LIGHTYEAR;
	localPosition.Y += (position.Y-currentPosition.Y)*LIGHTYEAR;
	GetPlayerShip()->SetPosition(localPosition);
	GetPlayerShip()->SetSpeed(speed);

	wprintf(L"Loaded save0.dgs\r\n");

}


//#########################################################################
//PlayerShip

PlayerShip::PlayerShip()
{
	SpaceObject();
	plusMinusTime = 0;
	plusMinusStep = 0.1;
	plusMinusDirection = 1;
	plusMinusCounter = 0;
	plusMinusDoubling = 16;
	galaxyCoordinates = vector2d(0);
	controlThrust = 1.0;
}

void PlayerShip::UpdateGalaxyCoordinates(u32 type)
{
	switch(type)
	{
	case 0://RealSpace
		galaxyCoordinates = physics->GetGalaxyCoordinatesOfCenter();
		galaxyCoordinates.X += position.X / LIGHTYEAR;
		galaxyCoordinates.Y += position.Y / LIGHTYEAR;
		galaxyQuadrant.X = (s32)floor(galaxyCoordinates.X);
		galaxyQuadrant.Y = (s32)floor(galaxyCoordinates.Y);
		break;
	case 1://HyperSpace
		galaxyCoordinates.X = position.X * HYPERSPACE_SCALE/LIGHTYEAR;
		galaxyCoordinates.Y = position.Y * HYPERSPACE_SCALE/LIGHTYEAR;
		
		//galaxyCoordinates = physics->GetRoot()->GetGalaxy()->

		galaxyQuadrant.X = (s32)floor(galaxyCoordinates.X);
		galaxyQuadrant.Y = (s32)floor(galaxyCoordinates.Y);
		break;
	default:
		break;
	}
}

void PlayerShip::SetGalaxyCoordinates(vector2d newCoords)
{
	galaxyCoordinates=newCoords;
	galaxyQuadrant.X = (s32)floor(galaxyCoordinates.X);
	galaxyQuadrant.Y = (s32)floor(galaxyCoordinates.Y);
}


void PlayerShip::JumpToQuasiSpace(s32 direction)
{
	plusMinusTime = 0;
	plusMinusStep = 0.1;
	//plusMinusStep = 0.00001;//DEBUG
	plusMinusCounter = 0;
	plusMinusDoubling = 16;
	galaxyQuadrant = physics->GetGalaxyQuadrant();//ship may be outside quadrant of starsystem (if starsystem is on the edge of quadrant) counting should goes from quadrant of starsystem

	//if (abs(galaxyQuadrant.Y)<100) galaxyQuadrant = vector2ds(-65536,65535);//DEBUG

	plusMinusDirection = direction;
	if (direction==0)
	{//Third option - two times at random direction
		if (GlobalURNG::Instance().GenerateByte()<128)
			plusMinusDirection = -2;//two times backward
		else
			plusMinusDirection = 2;//two times forward
	}
	//motionType = MOTION_PLUSMINUS;
	SetIntProperty(MOTION_TYPE, MOTION_PLUSMINUS);

	speed=vector3d(0);
}

void PlayerShip::BreakQuasiSpace()
{
	//motionType = MOTION_NAVIGATION;
	SetIntProperty(MOTION_TYPE, MOTION_NAVIGATION);
	//speed.normalize();
	speed=vector3d(0);

	wprintf(L" - PlusMinus breaked after %i steps\r\n",plusMinusCounter);

	physics->SetGalaxyCoordinatesOfCenter(vector2d(galaxyQuadrant.X+0.5,galaxyQuadrant.Y+0.5));
	position = vector3d(0);
}

void PlayerShip::UpdateQuasiSpace(f64 time, Galaxy* galaxy)
{
	/* Tests in default galaxy
		(64510,61915) OBS 5567
		3701608 steps
		(62841,63341) PGU 3297
		231690 steps
		(62506,62505) THH 1343
		1893148 steps
		(62204,63884) VYZ 0378
		8437341 steps (over boundary)
		(-65266,64015) DUX 5459
		192886 steps
		(-65332,63738) SCL 9376
		5424656 steps
		(-61749,63834) LEI 3354

		speed: 100k / second
	*/

	plusMinusTime+=time;
	while (plusMinusTime>plusMinusStep)
	{
		galaxyQuadrant = galaxy->MoveByPlusMinus(galaxyQuadrant,plusMinusDirection);
		if (galaxy->CheckStarPresence(galaxyQuadrant)!=0)
		{
			//star found
			if (plusMinusDirection<-1)
			{//several steps backward
				plusMinusDirection++;
			}
			else if (plusMinusDirection>1)
			{//several steps forward
				plusMinusDirection--;
			}
			else
			{//only/last step finished
				//f64 angle;
				wprintf(L" - PlusMinus finished after %i steps\r\n",plusMinusCounter);

				GalaxyStarSystem* exitTo = galaxy->GetStarSystem(galaxyQuadrant);//get obj with basic info about system where we will exit
				galaxyCoordinates = exitTo->GetGalaxyCoordinates();//get galaxy coords
				//galaxy->UpdatePlayerLocation(galaxyCoordinates);//update galaxy for our new location
				physics->GetRoot()->GoStarSystem(exitTo);//force game to go player to this star systems (includes generation of planets and so on)
				//physics->Update(0);//update planets and e.t.c. to their locations

				//TODO: Find random location for exit from QuasiSpace

				//random angle
				//angle = GlobalURNG::Instance().GenerateByte()*TWO_PI/255.0;
				//position = vector3d(LIGHTYEAR*0.07*cos(angle),LIGHTYEAR*0.07*sin(angle),0);//dumb "far from planets" location, 0.07 ly is beyond planet generation limit
				//position = physics->FindRandomLocationWithSpecificGravity(-15.49,-15.12);
				//position = physics->FindRandomLocationWithSpecificGravity(-7.0,-6.0);
				position = physics->FindRandomLocationWithSpecificXGravity(-36.0,-35.0);
				//-15.49 dgr is the gravity on surface of ice ball with m=1300 kg and radius = 68 cm
				//-15.12 dgr on dist = 0.1 ly is making star of 1829 solar masses
				//So with except to galaxy-center black hole, finding such gravity inside star system should not be a problem

				physics->Activate();

				//motionType = MOTION_NAVIGATION;
				SetIntProperty(MOTION_TYPE, MOTION_NAVIGATION);
				speed=vector3d(0);
				exitTo->unlock(0);//free if not stored somewhere else
				return;
			}
		}
		plusMinusCounter++;

		if (plusMinusCounter>plusMinusDoubling)
		{//Speed up counting - for far jumps
			//if (plusMinusStep>0.00001) //limit speed to 50k jumps/second
			if (time<FRAME_TIME_MAX) //limit speed, if PC is working slow
			{
				//wprintf(L" - PlusMinus speed doubled\r\n");
				plusMinusDoubling*=2;
				plusMinusStep*=0.5;
			}
		}
		
		/*text_string galaxyCoords=L" - PlusMinus goes to ";
		galaxyCoords+=galaxyQuadrant.X;
		galaxyCoords+=L", ";
		galaxyCoords+=galaxyQuadrant.Y;*/
		
		//wprintf(L" - PlusMinus goes to %i,%i\r\n",galaxyQuadrant.X,galaxyQuadrant.Y);

		plusMinusTime-=plusMinusStep;
	}
}

void PlayerShip::DebugPrint_QuasiSpace()
{
	wprintf(L" - PlusMinus is on %i step around (%i,%i), direction is %i\r\n",plusMinusCounter,galaxyQuadrant.X,galaxyQuadrant.Y,plusMinusDirection);
}

void PlayerShip::FallIntoWormhole(SpaceObject* wormhole)
{
//	f64 inputDirection;
//	f64 toRotate;
	vector3d newSpeed;
	vector3d inputVector;
	vector2d inputGalaxyCoordinates;
	vector2ds inputGalaxyQuadrant;
	vector2ds galaxyQuadrant;
	f64 radius, radius2;
	SpaceObject* outputWormhole;

	BreakAutopilot();

	inputVector = position-wormhole->GetPosition();
	inputGalaxyQuadrant = physics->GetGalaxyQuadrant();
	inputGalaxyCoordinates = physics->GetGalaxyCoordinatesOfCenter();
	radius = wormhole->GetFloatProperty(GEOMETRY_RADIUS);
	radius2 = wormhole->GetFloatProperty(GRAVITY_MIN_RADIUS);
	//inputDirection = wormhole->GetRotation();

	wprintf(L"DG: player falls into %ws\r\n",wormhole->GetName().c_str());
	galaxyQuadrant.X = wormhole->GetIntProperty(TRAVEL_TO_X);
	galaxyQuadrant.Y = wormhole->GetIntProperty(TRAVEL_TO_Y);

	GalaxyStarSystem* exitTo = physics->GetRoot()->GetGalaxy()->GetStarSystem(galaxyQuadrant);//get obj with basic info about system where we will exit
	galaxyCoordinates = exitTo->GetGalaxyCoordinates();//get galaxy coords
	//physics->GetRoot()->GetGalaxy()->UpdatePlayerLocation(galaxyCoordinates);//update galaxy for our new location
	physics->GetRoot()->GoStarSystem(exitTo);//force game to go player to this star systems (includes generation of planets and so on)
	//physics->Update(0);//update planets and e.t.c. to their locations

	//position = physics->FindRandomLocationWithSpecificXGravity(-36.0,-35.0);
	outputWormhole = physics->GetWormholeTo(inputGalaxyQuadrant);

	//toRotate = (outputWormhole->GetRotation()-inputDirection)*CoeffDegreesToRadians;

	if (outputWormhole)
	{
		position = outputWormhole->GetPosition()+inputVector;//TODO: bettwe position after jump
		outputWormhole->SetFloatProperty(GEOMETRY_RADIUS,radius*0.9999);//this for update wormhole geometry
		outputWormhole->SetFloatProperty(GRAVITY_MIN_RADIUS,radius2);
		outputWormhole->UpdatePhysics(0);
	}
	else
	{
		//No backward wormhole in destination system
		//Location is approximate position, direction is vector between stars, distance - wormholeDistance
		//+ Great bonus for player
		vector2d direction;
		wprintf(L"Whoa! Great bonus for discoveing one-way wormhole!!\r\n");

		direction = inputGalaxyCoordinates - exitTo->GetGalaxyCoordinates();
		direction.normalize();
		direction*=exitTo->GetWormholeDistance();
		position = inputVector;
		position.X +=direction.X;
		position.Y +=direction.Y;
	}
	prevPosition = position;

	/*rotation += outputWormhole->GetRotation()-inputDirection;
	position = outputWormhole->GetPosition()+GetDirection()*10.0;
	newSpeed.X = speed.X*cos(toRotate)-speed.Y*sin(toRotate);
	newSpeed.Y = speed.Y*cos(toRotate)+speed.X*sin(toRotate);
	newSpeed.Z = 0;
	speed = newSpeed;*/

	physics->Activate();

	exitTo->unlock(0);//free if not stored somewhere else

	return;
}

void PlayerShip::FallIntoStargate(SpaceObject* stargate)
{
//	f64 inputDirection;
//	f64 toRotate;
	vector3d stargateAxis;
	vector3d outputStargateAxis;
	vector3d newSpeed;
	vector3d inputSpeed;
	vector2ds galaxyQuadrant;
	f64 fallLocation;//falling position along stargate event horizon
	f64 rotAngle;
	SpaceObject* outputStargate;

	BreakAutopilot();

	stargateAxis.X = stargate->GetDirection().Y;
	stargateAxis.Y = -stargate->GetDirection().X;

	rotAngle = -stargate->GetFloatProperty(SpaceObject::ROTATION_ANGLE);
	fallLocation = stargateAxis.dotProduct(position-stargate->GetPosition());
	inputSpeed = speed-stargate->GetSpeed();

	wprintf(L"DG: player falls into %ws\r\n",stargate->GetName().c_str());
	galaxyQuadrant.X = stargate->GetIntProperty(TRAVEL_TO_X);
	galaxyQuadrant.Y = stargate->GetIntProperty(TRAVEL_TO_Y);

	GalaxyStarSystem* exitTo = physics->GetRoot()->GetGalaxy()->GetStarSystem(galaxyQuadrant);//get obj with basic info about system where we will exit
	galaxyCoordinates = exitTo->GetGalaxyCoordinates();//get galaxy coords
	physics->GetRoot()->GoStarSystem(exitTo);//force game to go player to this star systems (includes generation of planets and so on)

	//outputStargate = physics->GetFirstObject(STARGATE,2);
	outputStargate = physics->GetFirstObject(STARGATE,1);
		
	//toRotate = (outputWormhole->GetRotation()-inputDirection)*CoeffDegreesToRadians;

	if (outputStargate)
	{
		outputStargateAxis.X = outputStargate->GetDirection().Y;
		outputStargateAxis.Y = -outputStargate->GetDirection().X;
		rotAngle += TWO_PI*0.5 + outputStargate->GetFloatProperty(SpaceObject::ROTATION_ANGLE);//+TWO_PI*0.5;

		newSpeed.X = inputSpeed.X*cos(rotAngle)-inputSpeed.Y*sin(rotAngle);
		newSpeed.Y = inputSpeed.Y*cos(rotAngle)+inputSpeed.X*sin(rotAngle);
		newSpeed.Z = 0;

		speed = newSpeed+outputStargate->GetSpeed();
		AddFloatProperty(SpaceObject::ROTATION_ANGLE,rotAngle);
		
		physics->GetRoot()->UseSceneManager(DG_Game::VIEW_REALSPACE);
		SpaceObject* eventHorizon = physics->GetRoot()->GetResourceManager()->MakeStargateEH();
		eventHorizon->SetLinkedParams(outputStargate,vector3d(13.0,0,0),0);
		eventHorizon->SetIntProperty(SpaceObject::VISIBLE_TO_PLAYER,1);
		eventHorizon->SetIntProperty(SpaceObject::CURRENT_PROCESS,SpaceObject::PROCESS_STARGATE_OPENING);
		eventHorizon->SetIntProperty(SpaceObject::TRAVEL_TO_X,-100000);
		//eventHorizon->SetIntProperty(SpaceObject::TRAVEL_TO_Y,coordinates.Y);
		eventHorizon->SetFloatProperty(SpaceObject::PROCESS_START_TIME,physics->globalTime-1);//TODO: remove this cheat
		eventHorizon->UpdatePhysics(0);

		position = eventHorizon->GetPosition()+speed*0.01-outputStargateAxis*fallLocation;
		outputStargate->SetIntProperty(SpaceObject::ACTIVE,1);


	}
	else
	{
		//should not happens
		//TODO: random location
		position = vector3d(0);
	}
	prevPosition = position;
	
	/*
	outputStargate->SetIntProperty(VISIBLE_TO_PLAYER,1);
	outputStargate->SetIntProperty(CURRENT_PROCESS,PROCESS_STARGATE_OPENING);
	outputStargate->SetIntProperty(TRAVEL_TO_X,-100000);
	outputStargate->SetFloatProperty(PROCESS_START_TIME,physics->globalTime-1);//TODO: remove this cheat
	*/


	physics->Activate();

	exitTo->unlock(0);//free if not stored somewhere else

	return;
}

void PlayerShip::ScanSpace(f64 radius)
{
	bool found;
	core::array<SpaceObject*> foundObjects;
	physics->GetObjectsAtDistance(&foundObjects,position,radius);
	found = false;
	for (u32 i = 0;i<foundObjects.size();i++)
	{
		if (foundObjects[i]!=this)
		{
			found = true;
			if (foundObjects[i]->GetIntProperty(STARGATE)==1)
			{
				wprintf(L" Scanner found %ws, it has address %ws\r\n",foundObjects[i]->GetName().c_str(),physics->GetRoot()->GetGalaxy()->StargateAddress2text(physics->GetRoot()->GetCurrentSystem()->GetStargateAddress()).c_str());
				continue;
			}
			wprintf(L" Scanner found %ws\r\n",foundObjects[i]->GetName().c_str());
		}
	}
	if (!found)
		wprintf(L" Scanner not found anything\r\n");

}

void PlayerShip::SetControlThrust(f64 newThrust)
{
	controlThrust = newThrust;
	if (controlThrust>1.0)
		controlThrust = 1.0;
	else if (controlThrust<0.0)
		controlThrust = 0.0;
}

//#########################################################################
//Galaxy

//Rijndael Forward S-box
const u8 Galaxy::sBox[256] = {
   0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
   0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
   0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
   0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
   0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
   0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
   0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
   0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
   0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
   0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
   0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
   0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
   0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
   0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
   0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
   0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

//Rijndael Inverse S-box
const u8 Galaxy::sBoxInv[256] = 
{
   0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
   0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
   0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
   0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
   0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
   0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
   0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
   0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
   0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
   0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
   0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
   0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
   0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
   0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
   0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
   0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};


void Galaxy::Init()
{
	debugStarCounter = 0;

	//TEMP
	galaxySeed[0]=0x10;
	//galaxySeed[0]=0x18;//E1 galaxy
	//galaxySeed[0]=0x12;
	galaxySeed[1]=0x12;
	galaxySeed[2]=0x17;
	galaxySeed[3]=0xF0;
	galaxySeed[4]=0xE2;
	galaxySeed[5]=0xC4;
	galaxySeed[6]=0x66;
	galaxySeed[7]=0x90;
	memcpy(galaxySeed+8,galaxySeed,8);

	galaxyRNG = new DeterminedRandomGenerator();//delete in ~Galaxy

	galaxyRNG->SetSeed(galaxySeed,16);

	knownStarsAnchor.X = 0;
	knownStarsAnchor.Y = 0;

	s32 x,y;
	s32 number;
	f64 eccentricity;
	f64 rotationAngle;
	f64 stellarDensity1;
	f64 densityKoeff;
	f64 len2,fi,dist,distSQ,pDist,angleDist;
	text_string galaxyClass = L"*";;


	//for spiral galaxies
	f64 spiralityB;
	f64 armKoef;//1.0 for 2 arms, 1.5 for 3 arms, 2.0 for 4 arms
	f64 armWidth;
	f64 armDist1,armDistK;
	f64 pitchAngle;//in radians
	//f64 gapDensity;//stellar density in the interarm gap on r=outerRadius/2

	starCountEstimation=0;
	vector2d coords;
	vector2d coordsArm;

	wprintf(L"DG: Galaxy random generation...\r\n");

	number = galaxyRNG->GenerateByte();
	if (number<197)
	{//77% - spiral
		galaxyType = 2;
	}
	else //if (number<247)
	{//20% - elliptical
		galaxyType = 0;//E0

	}
	/*
	else
	{//3% - irregular
		//Not implemented
		galaxyType = 3;//Irr
		//TODO: irregular galaxies
	}
	*/

	//N/A for irregulars
	for (;;)
	{
		number = galaxyRNG->GenerateByte();
		halfDensityRadius = 10000.0+27.4*number;//10k-17k
		number = galaxyRNG->GenerateByte();
		maxDensity = 0.2 + 0.0015*number; //0.2 - 0.6
		outerRadius = sqrt(log(maxDensity/INTERGALACTIC_STARS_DENSITY))*halfDensityRadius;
		
		if (outerRadius<65530)//if > then generate density and radius once again
			break;
	}

	//Generate elliptical form for E*
	if (galaxyType==0)
	{
		galaxyClass = L"E0";
		number = galaxyRNG->GenerateByte();
		if (number<128)
		{//50%
			galaxyType = 1;//E1-E7

			//Eccentricity
			//TODO: more realistic eccentricity
			number = galaxyRNG->GenerateByte();
			eccentricity = (0.3+number*0.00235);//0.3 - 0.9, 1.0 not needed

			//Rotation angle, any in (0,2*pi)
			number = galaxyRNG->GenerateByte();
			rotationAngle = number*TWO_PI/255.0;

			minorRadius = outerRadius*eccentricity;
			{
				wchar_t tmp[255];
				swprintf(tmp, 255, L"E%i", (s32)floor(10.0-eccentricity*10.0));
				galaxyClass = tmp;
			}
		}
	}

	if (galaxyType==2)
	{
		//spiralityB = 0.27 for Milky Way
		number = galaxyRNG->GenerateByte();
		if (number<63)
		{	
			galaxyClass = L"Sa";
			spiralityB=number*0.00177;//0.05-0.16, class Sa
		}
		else if (number<163)
		{
			galaxyClass = L"Sb";
			spiralityB=0.16+(number-63)*0.0018;//0.16-0.34, class Sb
		}
		else if (number<252)
		{
			galaxyClass = L"Sc";
			spiralityB=0.34+(number-163)*0.00261;//0.34-0.57, class Sñ
		}
		else
		{
			galaxyClass = L"Sd";
			number = galaxyRNG->GenerateByte();
			spiralityB=0.57+number*0.00168;//0.57-1.0, class Sd
		}
		//TODO: more realistic spirality

		//direction of arms, positive -> going from center to edge is CCW, negative -> CW
		number = galaxyRNG->GenerateByte();
		if (number<127)
			spiralityB =-spiralityB;

		//Number of arms
		number = galaxyRNG->GenerateByte();
		if (number<200)
		{//78%
			armKoef = 1.0;//2 arms
		}
		else if (number<251)
		{//20%
			armKoef = 2.0;//4 arms
			galaxyClass += L"-4";
		}
		else
		{//2%
			armKoef = 1.5;//3 arms
			galaxyClass += L"-3";
		}
		//TODO: more realistic number of arms (?)

		//Rotation angle - any in (0,2*pi)
		number = galaxyRNG->GenerateByte();
		rotationAngle = number*TWO_PI/255.0;

		/*
		//Milky Way
		spiralityB = 0.27;
		armKoef = 2.0;*/

		//pitch angle, calc from spirality
		pitchAngle = TWO_PI*0.25-atan(fabs(1.0/spiralityB));

		armDist1 = halfDensityRadius*.5;

		//Width of arms
		number = galaxyRNG->GenerateByte();
		armWidth  = outerRadius*(0.022+number*3.843e-4);
		//min: 0.022*r, ~159M star systems for r=60kly, maxdens=0.3; ~41M for r=37,5kly, maxdens = 0.2
		//max: 0.12*r, ~536M star systems for r=60kly, maxdens=0.3; ~1240M for r=65.5kly maxdens = 0.6
	}

 
	densityKoeff = -1.0/(halfDensityRadius*halfDensityRadius);

	//Generate stellar density field, which will be used later for generation of stars
	for (y=0;y<2048;y++)
	for (x=0;x<2048;x++)
	{
		coords.X = x*64-65504;//-65504 = -65536+32
		coords.Y = y*64-65504;

		if (galaxyType==0)
		{
			//Calc star density, v1 elliptical (E0) galaxy - no spiral arms at all
			stellarDensity1 = maxDensity*exp(densityKoeff*coords.getLengthSQ());
		}
		if (galaxyType==1)
		{
			//Calc star density, v2 elliptical (E1-E7) galaxy
			fi = atan2(coords.Y,coords.X)-rotationAngle;
			//len2 = coords.X*coords.X+coords.Y*coords.Y/(eccentricity*eccentricity);
			//len2 = eccentricity*eccentricity/(eccentricity*eccentricity*cos(fi)*cos(fi)+sin(fi)*sin(fi));
			//len2=coords.getLengthSQ()/len2;
			len2 = coords.getLengthSQ()*(eccentricity*eccentricity*cos(fi)*cos(fi)+sin(fi)*sin(fi))/(eccentricity*eccentricity);

			stellarDensity1 = maxDensity*exp(densityKoeff*len2); 
		}
		if (galaxyType==2)
		{
			distSQ = coords.getLengthSQ();
			dist = sqrt(distSQ);
			//stellarDensity1 = maxDensity*exp(densityKoeff*distSQ);
			//stellarDensity1 = maxDensity*exp(densityKoeff*distSQ)*(1.0-distSQ*densityKoeff);
			if (dist<(outerRadius*.5))
			{//Arms density from 0 to r/2 is maximum
				stellarDensity1 = maxDensity;
			}
			else
			{//Arms density after r/2 decreases and on r reach value of exponent 

				//pDist = dist*2.0-outerRadius;  //to fast grow after 1 (dist = outerRadius) 
				//pDist = dist-0.25*outerRadius*outerRadius/dist; // f(1)<1, bad
				//pDist = (4*dist-outerRadius*outerRadius/dist)/3.0; 
				pDist = (2.0*dist-outerRadius)*(2.0*dist/outerRadius-1.0);//looks good

				stellarDensity1 = maxDensity*exp(densityKoeff*pDist*pDist);
			}

			//Angle distance (in radians) between logarithmic spiral and current quadrant, incl. rotation
			angleDist = log(dist)/spiralityB - atan2(coords.Y,coords.X) - rotationAngle;

			//Koeff of arms/core transfer function
			//1.0 for arms, 0.0 for core
			armDistK = 1.0/(1.0+exp(5.0*(1.0-dist/armDist1)));

			//Linear distance from spiral arm to current quadrant
			//sin() + armKoef defines number of arms, armWidth - width of an arm
			angleDist = sin(angleDist*armKoef)*dist/armWidth;

			stellarDensity1 *= (1.0-armDistK)+armDistK/(1.0+angleDist*angleDist);
		}

		if (stellarDensity1<INTERGALACTIC_STARS_DENSITY)
			stellarDensity1 = INTERGALACTIC_STARS_DENSITY;
		
		stellarDensity[x][y]=(f32)stellarDensity1;
		starCountEstimation+=stellarDensity1*4096.0;//4096 = 64*64 ly
	}

	//TODO: clusterization of stars in arms (and core?)
	//TODO: additional clusters
	//TODO: Additional rings or arc around galaxy

	SaveMapTexture();
	wprintf(L"DG: Galaxy generated, class %ws, ~%.0f star systems\r\n",galaxyClass.c_str(),starCountEstimation);
	wprintf(L"    radius: ~%.0f ly\r\n",outerRadius);

	
	galaxyRNG->SetOffset(100000);

	//RSA-36 key pair
	//p = 262151, q = 131111
	sgPublicKeyMod=34370879761;//0x800AA0111
	sgPublicKeyExp=3;
	sgPrivateKeyExp=22913657667;//0x555C2AB43

	//randomization values
	sgCoordXorValue=galaxyRNG->GenerateByte();
	sgCoordXorValue+=((u64)galaxyRNG->GenerateByte())<<8;
	sgCoordXorValue+=((u64)galaxyRNG->GenerateByte())<<16;
	sgCoordXorValue+=((u64)galaxyRNG->GenerateByte())<<24;
	sgCoordXorValue+=((u64)galaxyRNG->GenerateByte()&3)<<32;//34 bits
	sgAddressAddValue=galaxyRNG->GenerateByte();
	sgAddressAddValue+=((u64)galaxyRNG->GenerateByte())<<8;
	sgAddressAddValue+=((u64)galaxyRNG->GenerateByte())<<16;
	sgAddressAddValue+=((u64)galaxyRNG->GenerateByte())<<24;
	sgAddressAddValue+=((u64)galaxyRNG->GenerateByte()&7)<<32;//35 bits


	
	/*
	//DEBUG
	//Encryption system self test
	for (number=0;number<100000;number++)
	{
		vector2ds coords1,coords2;
		u64 address;
		coords1.X = -65536+GlobalURNG::Instance().GenerateByte();
		coords1.X += GlobalURNG::Instance().GenerateByte()*256;
		coords1.X += (GlobalURNG::Instance().GenerateByte()&1)*65536;
		coords1.Y = -65536+GlobalURNG::Instance().GenerateByte();
		coords1.Y += GlobalURNG::Instance().GenerateByte()*256;
		coords1.Y += (GlobalURNG::Instance().GenerateByte()&1)*65536;
		address = Coordinates2StargateAddress(coords1);
		coords2 = StargateAddress2Coordinates(address);
		if (coords1!=coords2)
			wprintf(L"Error on encryption system self test\r\n");
	}
	*/

	UpdateKnownStars();
}

Galaxy::~Galaxy()
{
	ClearKnownStars();
	ClearWormholes();
	delete galaxyRNG;//new in Galaxy::Init
	galaxyRNG =0;
}

//Object should be unlock()-ed to 0 outside
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
	quadrant.X = ((s32)floor(coordinates.X*0.1))*10;//round to 10th
	quadrant.Y = ((s32)floor(coordinates.Y*0.1))*10;//round to 10th
	if (quadrant!=knownStarsAnchor)
	{
		knownStarsAnchor = quadrant;
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
	vector2d coordinates1,coordinates2;

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

	for (i=0;i<knownWormholes.size();i++)
	{
		//initial, approximate coordinates
		coordinates1.X = knownWormholes[i]->Star1.X;
		coordinates1.Y = knownWormholes[i]->Star1.Y;
		coordinates2.X = knownWormholes[i]->Star2.X;
		coordinates2.Y = knownWormholes[i]->Star2.Y;

		//find precise coordinates (unoptimized search)
		for (u32 j=0;j<knownStars.size();j++)
			if (knownWormholes[i]->Star1 == knownStars[j]->GetGalaxyQuadrant())
			{
				coordinates1 = knownStars[j]->GetGalaxyCoordinates();
				break;
			}
		for (u32 j=0;j<knownStars.size();j++)
			if (knownWormholes[i]->Star2 == knownStars[j]->GetGalaxyQuadrant())
			{
				coordinates2 = knownStars[j]->GetGalaxyCoordinates();
				break;
			}
		mapView->AddWormholeLink(coordinates1,coordinates2);
	}

	return;

}

//flags: 1 - do not add if player location is about the same (use internal "anchors")
void Galaxy::AddHyperSpaceObjects(HyperSpaceView* hyperView, u32 flags)
{
	u32 i;
	vector2d coordinates1,coordinates2;

	if ((flags&1)!=0)
	{
		if (hyperSpaceStarsAnchor==knownStarsAnchor)
			return;
	}

	hyperView->RemoveAllStars();

	for (i=0;i<knownStars.size();i++)
	{
		hyperView->AddStar(knownStars[i]);
	}

	hyperSpaceStarsAnchor = knownStarsAnchor;
	hyperView->UpdateCameraDistance();
	return;

}


u32 Galaxy::IsInGrid(vector2ds coordinates)
{
	if (coordinates.X<-65536 || coordinates.X>65535 || coordinates.Y<-65536 || coordinates.Y>65535)
		return 0;//outside 131072x131072 grid
	return 1;
}

//1 - present, 0 - not
u32 Galaxy::CheckStarPresence(vector2ds coordinates)
{
	f64 starDensity;
	f64 number;
	s32 x,y;

	//vector2d coords = vector2d(coordinates.X,coordinates.Y);
	//if (coordinates.X<-65536 || coordinates.X>65535 || coordinates.Y<-65536 || coordinates.Y>65535)
	if (IsInGrid(coordinates)!=1)
		return 0;//no stars outside 131072x131072 grid

	x = (coordinates.X+65536)>>6;//divide by 64
	y = (coordinates.Y+65536)>>6;//divide by 64

	starDensity = stellarDensity[x][y];
	
	//Now we must generate random number in range [0,1)
	//If number will be less than density, then star is present in quadrant
	//To do so we:
	//1) Generate one random byte, scale density by 256 and compare them
	//2) If random is larger, then no star
	//3) If density is too small (<16) then scale density and number by 256 and add one more random byte to a number
	//4) Loop 3
	//5) If random is still smaller then there is a star system

	galaxyRNG->SetSeedWithCoordinates(galaxySeed,16,coordinates.X,coordinates.Y);
	
	//Get 1st random byte and scale density
	number = galaxyRNG->GetByteByOffset(0);
	starDensity *=256.0;

	while (starDensity<16.0)
	{
		if (number>starDensity)
			return 0;//no star ( random number is greater then density)

		//Get next random byte and scale density
		number = number*256.0+galaxyRNG->GenerateByte();
		starDensity *=256.0;
	}

	if (number<starDensity)
		return 1;//star present (random number is less than density)
	return 0;//no star
}

//Check presence of stargate in system
//checkStar - check star presence or not
//return: 0 - no star system/ no stargate, 1 - stargate present, 2 - stargate present but locked
u32 Galaxy::CheckStargatePresence(vector2ds coordinates, bool checkStar)
{
	s32 number;

	if (checkStar)
	{
		if (CheckStarPresence(coordinates)==0)
			return 0;
	}

	galaxyRNG->SetSeedWithCoordinates(galaxySeed,16,coordinates.X,coordinates.Y);
	number = galaxyRNG->GetByteByOffset(100);

	if (number<3)
	{
		//no stargate
		return 0;
	}
	else
	{
		//stargate is present
		number = galaxyRNG->GenerateByte();

		if (number<3)
		{
			//stargate locked
			return 2;
		}
	}

	return 1;//stargate present and working
}

/*
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
}*/

GalaxyStarSystem* Galaxy::GetStartStarSystem()
{
	u32 i;
	f64 minDistanceSQ=1e20;
	f64 distanceSQ;
	GalaxyStarSystem* minDistanceObject=0;
	s32 x,y;

	y = 1024;//0 by galaxy coordinates

	//start from left most stars
	//find galaxy cell with non minimal density
	for (x=2047;x>=1026;x--)
		if (stellarDensity[x][y]>0.02)
			break;

	knownStarsAnchor.X = x*64-65504;
	knownStarsAnchor.Y = 0;

	//find quad with non zero stars
	for (;;)
	{
		UpdateKnownStars();//update cache of stars around found location

		if (knownStars.size()>0)
			break;

		knownStarsAnchor.X -= 20;
		//TODO: exit condition, in case of very bad luck
	}


	//find star, closest to X=0 axis ( min(abs(Y)) )
	for (i=0;i<knownStars.size();i++)
	{
		//distanceSQ = (knownStars[i]->GetGalaxyCoordinates()).getLengthSQ();//distance from (0,0)
		distanceSQ = fabs(knownStars[i]->GetGalaxyCoordinates().Y);//need min Y coordinate
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

//void Galaxy::DebugDump()
void Galaxy::SaveMapTexture()
{
	//vector2ds coord1,coord0,coord;
	s32 x,y;
	//s32 count;
	u8 byte;
	FILE * f1;
	u8 header[54] = {0x42,0x4D,0x38,0x04,0x40,0x00,0x00,0x00,0x00,0x00,0x36,0x04,0x00,0x00,0x28,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x08,0x00,0x00,0x01,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x40,0x00,0x12,0x0B,0x00,0x00,0x12,0x0B,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

	/*
	f1 = fopen("galaxy.bmp","rb");
	if (f1!=0)
	{
		fclose(f1);
		return;
	}*/

	f1 = fopen("galaxy.bmp","wb");

	fwrite(header,1,54,f1);//BMP header
	for (x=0;x<256;x++)
	{//palette
		byte = x;
		fwrite(&byte,1,1,f1);
		fwrite(&byte,1,1,f1);
		fwrite(&byte,1,1,f1);
		byte = 0;
		fwrite(&byte,1,1,f1);
	}

	//lines are inverted in BMP and so inverted Y axis in galaxy
	for (y=0;y<2048;y++)
	{
		for (x=0;x<2048;x++)
		//for (coord0.X=53376;coord0.X<65536;coord0.X+=64)
		{
			//byte=(u8)(pow(((f64)stellarDensity[x][y])/maxDensity,0.4)*255.0);//power 0.4, balanced for high and med density
			//byte=(u8)(236+log(stellarDensity[x][y])*15.0);//logarithmic, good for viewing least dense regions
			byte=(u8)(63+log(stellarDensity[x][y])*4.0+pow(((f64)stellarDensity[x][y])/maxDensity,0.4)*194.0);//balanced log-pow, looks good for all densities

			//byte=(u8)(255-pow((f64)log(stellarDensity[x][y]),2.0));
			fwrite(&byte,1,1,f1);
		}
	}
	fclose(f1);
}

//Object should be unlock()-ed to 0 outside
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
	galaxyRNG->SetSeedWithCoordinates(galaxySeed,16,knownStarsAnchor.X,knownStarsAnchor.Y);
	galaxyRNG->SetOffset(777+debugStarCounter);

	for (u32 i=0;i<1000;i++)
	{
		randomLocation.X = -65536 + galaxyRNG->GenerateByte();
		randomLocation.X += galaxyRNG->GenerateByte()*256;
		randomLocation.X += (galaxyRNG->GenerateByte()&1)*65536;//last bit

		randomLocation.Y = -65536 + galaxyRNG->GenerateByte();
		randomLocation.Y += galaxyRNG->GenerateByte()*256;
		randomLocation.Y += (galaxyRNG->GenerateByte()&1)*65536;//last bit

		debugStarCounter+=6;//this allows to use this function again with another random seq

		if (CheckStarPresence(randomLocation)==1)
		{
			return SeedStar(randomLocation);
		}
	}
	return 0;

}

//Generate wormhole in a big circle around and no clean them
void Galaxy::DebugShowWormholes()
{
	vector2ds currentAnchor = knownStarsAnchor;
	s32 x,y;

	for(y = -100;y<100;y+=10)
	for(x = -100;x<100;x+=10)
	{
		knownStarsAnchor = currentAnchor;
		knownStarsAnchor.X +=x;
		knownStarsAnchor.Y +=y;
		UpdateKnownStars(1);
		GenerateWormholes(1);
	}

	knownStarsAnchor = currentAnchor;
	UpdateKnownStars(1);
	GenerateWormholes(1);
}

//Object should be unlock()-ed to 0 outside
GalaxyStarSystem* Galaxy::SeedStar(vector2ds coordinates)
{
	u8 starSeed[16];

	//galaxyRNG is seeded with coordinates in CheckStarPresence()
	galaxyRNG->SetOffset(10);
	galaxyRNG->GenerateBytes(starSeed,16);

	//starName = L"Star ";
	//starName +=n;
	//GalaxyStarSystem* newSystem = GalaxyStarSystem::RandomStar(coordinates);
	GalaxyStarSystem* newSystem = new GalaxyStarSystem(coordinates);//delete - by unlock()
	newSystem->SetSeed(starSeed,16);
	newSystem->GenerateStar();
	//newSystem->SetName(text_string(tmp));

	return newSystem;
}


void Galaxy::UpdateKnownStars(s32 param)
{
	s32 x,y;
	s32 x0,y0,x1,y1;
	//s32 n = 0;
	text_string starName;
	vector2ds coordinates;

	ClearKnownStars();

	if (param ==0)
	{
		ClearWormholes();
	}

	//Assumed that knownStarsAnchor is rounded to 10 l.y.
	x0 = knownStarsAnchor.X-20;
	y0 = knownStarsAnchor.Y-20;
	x1 = x0+50;
	y1 = y0+50;

	for (y=y0;y<y1;y++)
	{
		coordinates.Y = y;
		for (x=x0;x<x1;x++)
		{
			coordinates.X = x;
			if (CheckStarPresence(coordinates)==1)
			{
				GalaxyStarSystem* knownSystem;
				knownSystem = SeedStar(coordinates);
				knownSystem->lock(1);//lock as it is stored
				knownStars.push_back(knownSystem);
			}
		}
	}

	wprintf(L"DG: quadrant (%i,%i) stars around: %i\r\n",knownStarsAnchor.X,knownStarsAnchor.Y,knownStars.size());
	
	//knownStars.
}

vector2ds Galaxy::MoveByPlusMinus(vector2ds quadrant, s32 direction)
{
	switch(HilbertCurveDirection(quadrant.X+65536,quadrant.Y+65536,direction))
	{
	case 0:	quadrant.X++; break;
	case 1:	quadrant.Y++; break;
	case 2:	quadrant.X--; break;
	case 3:	quadrant.Y--; break;
	}
	if (quadrant.Y==65536)
	{
		quadrant.X=65535;quadrant.Y=65535;
	}
	if (quadrant.X==65536)
	{
		quadrant.X=-65536;quadrant.Y=65535;
	}
	return quadrant;
}

//x: (0,+inf) y: (0,+inf), direction - +1 or -1
//returns: 0 - left, 1 - down, 2 - right, 3 - up
s32 Galaxy::HilbertCurveDirection(s32 x, s32 y, s32 direction)
{
	s32 k,p;
	if (x==0 && y==0) //main line
	{
		if (direction<0)
			return 1;//CCW
		else
			return 0;//CW
	}

	//TODO: comment and optimize calculations

    //determine quarter size
    k = x;
    if (y > k) k=y;
    p = 2;
    while (k>=p)
        p*=2;
    
    p/=2;
    
    //p is quarter size, point is either top-right, botton-left or bottom-right quarter
    
	if (direction<0)
	{//CCW
		if (y >= p)
		{
			if (x >= p)
			{
				//bottom-right
				if (x==(p*2-1) && y==p)
				{
					//exception - connection to top-right
					return 3;
				}
				else
				{
					//repeat top-left with mirror against main diagonal (x=y)
					return HilbertCurveDirection(y - p, x - p,direction)^1;
				}
			}
			else
			{
                //bottom-left
                if (x==0 && y==(p*2-1))
				{
                    //exception - connection to outer
                    return 1;
				}
                else
				{
                    //repeat top-left with mirror against secondary diagonal (x+y=p)
                    return HilbertCurveDirection(p - 1 - (y - p), p - 1 - x,direction)^3;
				}
			}
		}
		else
		{
			//top-right
			if (x==p && y==(p - 1))
			{
				//exception - connection to top-left
				return 2;
			}
			else
			{
				//repeat top-left quarter as is
				return HilbertCurveDirection(x - p, y,direction);
			}
		}
	}
	else
	{//CW
		if (y >= p)
		{
			if (x >= p)
			{
				//bottom-right
				if (x==(p*2-1) && y==(p*2-1))
				{
					//exception - connection to outer
					return 0;
				}
				else
				{
					//repeat top-left with mirror against main diagonal (x=y)
					return HilbertCurveDirection(y - p, x - p,direction)^1;
				}
			}
			else
			{
				//bottom-left
				//repeat top-left with mirror against secondary diagonal (x+y=p)
				return HilbertCurveDirection(p - 1 - (y - p), p - 1 - x,direction)^3;
			}
		}
		else
		{
			//top-right
			if (x==(p * 2 - 1) && y==(p - 1))
			{
				//exception - connection to bottom-right
				return 1;
			}
			else
			{
				//repeat top-left quarter as is
				return HilbertCurveDirection(x - p, y,direction);
			}
		}
	}

}

void Galaxy::GenerateWormholes(s32 param)
{
	u32 i,j,k;
	f64 distSQ;
	s32 x,y;
	s32 wave[50][50];
	s32 waveStep[50][50];
	s32 n;
	s32* nearStars;
	s32 waveCurrentStep;
	s32 star1,star2;
	vector2ds coord1,coord2;
	bool keepWave;

//	core::array<vector2ds*> nearStars;

	WormholeInfo* newWormhole;
	//knownWormholes.push_back();

	if (param==0)
	{
		if (wormholesGenerated)
			return;//do nothing

		ClearWormholes();
	}

	if (knownStars.size()>1)
	{

		/*
		//Very basic list of wormholes - all with dist<=10 l.y.
		for (j=1;j<knownStars.size();j++)
			for (i=0;i<j;i++)
			{
				distSQ = (knownStars[i]->GetGalaxyCoordinates() - knownStars[j]->GetGalaxyCoordinates()).getLengthSQ();
				if (distSQ < 100.0)
				{
					newWormhole = new WormholeInfo();//delete in Galaxy::ClearWormholes
					newWormhole->Star1 = knownStars[i]->GetGalaxyQuadrant();
					newWormhole->Star2 = knownStars[j]->GetGalaxyQuadrant();
					knownWormholes.push_back(newWormhole);
				}
			}
		*/

		nearStars = new s32[knownStars.size()];

		//v4 wave-alg , very good, but gives a few asymmetry
		//network falls to pieces where stellardensity is about 0.0033 and below

		//Assumed that knownStarsAnchor is rounded to 10 l.y.
		//and knownStars is calced for (knownStarsAnchor-20;knownStarsAnchor+30) quad


		//Clean field
		for (j=0;j<50;j++)
		for (i=0;i<50;i++)
		{
			wave[i][j]=-1;
			waveStep[i][j]=0;
		}

		//Add known stars
		n=0;
		for (i=0;i<knownStars.size();i++)
		{
			x = knownStars[i]->GetGalaxyQuadrant().X-knownStarsAnchor.X+20;
			y = knownStars[i]->GetGalaxyQuadrant().Y-knownStarsAnchor.Y+20;
			if (x<0 || x>=50 || y<0 || y>=50)
				continue;
			wave[x][y]=n;
			waveStep[x][y]=1;
			nearStars[n]=i;
			n++;
		}

		//Wave algorithm
		waveCurrentStep=1;
		keepWave = true;

		while (keepWave)
		{
			keepWave = false;
			for (j=1;j<49;j++)
			for (i=1;i<49;i++)
				if (wave[i][j]==-1)
				{
					if (waveStep[i-1][j]==waveCurrentStep)
					{
						wave[i][j] = wave[i-1][j];
						waveStep[i][j]=waveCurrentStep+1;
						keepWave = true;
					}
					if (waveStep[i+1][j]==waveCurrentStep)
					{
						wave[i][j] = wave[i+1][j];
						waveStep[i][j]=waveCurrentStep+1;
						keepWave = true;
					}
					if (waveStep[i][j-1]==waveCurrentStep)
					{
						wave[i][j] = wave[i][j-1];
						waveStep[i][j]=waveCurrentStep+1;
						keepWave = true;
					}
					if (waveStep[i][j+1]==waveCurrentStep)
					{
						wave[i][j] = wave[i][j+1];
						waveStep[i][j]=waveCurrentStep+1;
						keepWave = true;
					}
				}
			waveCurrentStep++;
			if (waveCurrentStep>50)
				break;//break on too many steps
		}

		//Check waves what reach other
		for (j=0;j<49;j++)
		for (i=0;i<49;i++)
		{
			if (wave[i][j]!=wave[i+1][j] && wave[i][j]>=0 && wave[i+1][j]>=0)
			{
				star1 = nearStars[wave[i][j]];
				star2 = nearStars[wave[i+1][j]];
				goto lConnect;
			}
			if (wave[i][j]!=wave[i][j+1] && wave[i][j]>=0 && wave[i][j+1]>=0)
			{
				star1 = nearStars[wave[i][j]];
				star2 = nearStars[wave[i][j+1]];
lConnect:
				if (star2<star1)
				{//swap indexes, to simplify search
					k=star2;
					star2=star1;
					star1=k;
				}

				coord1 = knownStars[star1]->GetGalaxyQuadrant();
				coord2 = knownStars[star2]->GetGalaxyQuadrant();

				//
				//check that both stars are outside center 10x10 quad
				if ((coord1.X<knownStarsAnchor.X || coord1.X>(knownStarsAnchor.X+9) || 
					 coord1.Y<knownStarsAnchor.Y || coord1.Y>(knownStarsAnchor.Y+9)) &&
					(coord2.X<knownStarsAnchor.X || coord2.X>(knownStarsAnchor.X+9) || 
					 coord2.Y<knownStarsAnchor.Y || coord2.Y>(knownStarsAnchor.Y+9)))
					goto lSkip;


				distSQ = (knownStars[star1]->GetGalaxyCoordinates()-knownStars[star2]->GetGalaxyCoordinates()).getLengthSQ();
				if (distSQ>400)
					goto lSkip;

				for (k=0;k<knownWormholes.size();k++)
				{
					if (knownWormholes[k]->Star1 == coord1 &&
						knownWormholes[k]->Star2 == coord2)
					{
						goto lSkip;
					}
				}

				{
					newWormhole = new WormholeInfo();//delete in Galaxy::ClearWormholes
					newWormhole->Star1 = coord1;
					newWormhole->Star2 = coord2;
					knownWormholes.push_back(newWormhole);
				}
lSkip:;

			}
		}

	}

	wormholesGenerated = true;
	wprintf(L" * GenWorm: %i wormholes generated\r\n",knownWormholes.size());
}

void Galaxy::GetWormholesFrom(vector2ds quadrant, core::array<WormholeInfo*>* list)
{
	GenerateWormholes();

	list->clear();
	for (u32 i=0;i<knownWormholes.size();i++)
	{
		if (knownWormholes[i]->Star1 == quadrant || 
			knownWormholes[i]->Star2 == quadrant)
		{
			list->push_back(knownWormholes[i]);
		}
	}
}

void Galaxy::ClearWormholes()
{
	wormholesGenerated = false;
	for (u32 i=0;i<knownWormholes.size();i++)
	{
		delete knownWormholes[i];
		knownWormholes[i] = 0;
	}
	knownWormholes.clear();
}

void Galaxy::ClearKnownStars()
{
	for (u32 i=0;i<knownStars.size();i++)
		knownStars[i]->unlock(1);//free
	knownStars.clear();
}


//convert coordinates to address
u64 Galaxy::Coordinates2StargateAddress(vector2ds quadrant)
{
	/*//no-encryption version
	u64 x,y,address;
	x = quadrant.X+65536;
	y = quadrant.Y+65536;
	address = 0x400000000 | y | (x<<17);*/

	if (quadrant.X<-65536 || quadrant.X>65535 || quadrant.Y<-65536 || quadrant.Y>65535)
		return 0;//outside 131072x131072 grid

	u64 x,y,address;
	x = quadrant.X+65536;
	y = quadrant.Y+65536;
	address = 0x400000000 | y | (x<<17);//combine coordinates and padding
	address^= sgCoordXorValue;//xor coordinates with randomization
	
	address = fp_powmod(address,sgPrivateKeyExp,sgPublicKeyMod)+sgAddressAddValue;//encrypt on SK, add randomization value

	if (address>sgPublicKeyMod)
		address-=sgPublicKeyMod; //reduce if needed
	
	return address;//encryption on SK
}

//convert address to coordinates  (two error cases possible: - address is greater than PK and decryption does not have padding)
vector2ds Galaxy::StargateAddress2Coordinates(u64 address)
{
/*	//no-encryption version
	vector2ds result;
	u64 x,y;
	result.X = -100000;
	result.Y = 0;
	if (address>0x7FFFFFFFF)
		return result;
	if (address<0x400000000)
	{
		result.Y = 1;
		return result;
	}
	y = address&0x1FFFF;
	x = (address>>17)&0x1FFFF;
	result.X = (s32)x - 65536;
	result.Y = (s32)y - 65536;
	return result;*/

	vector2ds result;
	u64 decrypt,x,y;
	result.X = -100000;
	result.Y = 0;
	if (address>sgPublicKeyMod)
		return result;//address is greater than PK

	if (address<sgAddressAddValue)
		address+=sgPublicKeyMod;
	address-=sgAddressAddValue;//remove randomization value

	//TODO: could be optimized to 2 fp_mulmod (while sgPublicKeyExp = 3)
	decrypt = fp_powmod(address,sgPublicKeyExp,sgPublicKeyMod);//decrypt on PK

	if (decrypt<0x400000000)
	{//decryption result does not have required padding
		result.Y = 1;
		return result;
	}
	decrypt^= sgCoordXorValue;//xor coordinates with randomization

	y = decrypt&0x1FFFF;
	x = (decrypt>>17)&0x1FFFF;
	result.X = ((s32)x) - 65536;
	result.Y = ((s32)y) - 65536;
	return result;
}

//convert text to address
u64 Galaxy::text2StargateAddress(text_string text)
{
	u64 result=0;
	const wchar_t* text_w = text.c_str();
	u32 i,len = text.size();
	for(i=0;i<len;i++)
	{
		if (text_w[i]>=L'0' && text_w[i]<=L'9')
		{
			result*=16;
			result+=text_w[i]-L'0';
		}
		if (text_w[i]>=L'a' && text_w[i]<=L'f')
		{
			result*=16;
			result+=10+text_w[i]-L'a';
		}
		if (text_w[i]>=L'A' && text_w[i]<=L'F')
		{
			result*=16;
			result+=10+text_w[i]-L'A';
		}
	}
	return result;
}

//convert text to address
text_string Galaxy::StargateAddress2text(u64 address)
{
	wchar_t tmp[255];
	u32 len;
	len = swprintf(tmp,255,L"%09I64X",address);
	if (len>8)
	{
		tmp[len+2]=tmp[len];
		tmp[len+1]=tmp[len-1];
		tmp[len]=tmp[len-2];
		tmp[len-1]=tmp[len-3];
		tmp[len-2]=':';
		tmp[len-3]=tmp[len-4];
		tmp[len-4]=tmp[len-5];
		tmp[len-5]=tmp[len-6];
		tmp[len-6]=':';
	}
	return tmp;
}

//convert galaxy coordinates to HyperSpace coordinates
vector3d Galaxy::Galaxy2HyperSpace(vector2d galaxyCoordinates)
{
	//Algo:
	//1) fractional part (sub lightyear) is remained
	//2) inside square 16x16 ly coordinates are mixed by Rijndael s-box with additional seed-random variables
	//3) seed-random variables is calculated by determined random generator (i.e. hash) from coordinates rounded to 16
	f64 xInt, xFrac, yInt, yFrac;
	s32 x, y;
	s32 xHigh,yHigh;
	u8 xLow, yLow, xy;
	xInt = floor(galaxyCoordinates.X);
	xFrac = galaxyCoordinates.X-xInt;
	yInt = floor(galaxyCoordinates.Y);
	yFrac = galaxyCoordinates.Y-yInt;
	x = (s32)xInt;
	y = (s32)yInt;
	xLow = (u8)(x&15);
	yLow = (u8)(y&15);
	xHigh = x&0xFFFFFFF0;
	yHigh = y&0xFFFFFFF0;
	xy = xLow+(yLow<<4);

	//mixing
	galaxyRNG->SetSeedWithCoordinates(galaxySeed,16,xHigh,yHigh);
	xy+=galaxyRNG->GetByteByOffset(0);
	xy = sBox[xy];
	xy+=galaxyRNG->GetByteByOffset(1);

	xLow = xy&15;
	yLow = xy>>4;
	x = xHigh^xLow;
	y = yHigh^yLow;
	xInt = (f64)x;
	yInt = (f64)y;

	return vector3d((xInt + xFrac)*LIGHTYEAR/HYPERSPACE_SCALE,
		(yInt + yFrac)*LIGHTYEAR/HYPERSPACE_SCALE,0);
}

//convert HyperSpace coordinates to galaxy coordinates
vector2d Galaxy::HyperSpace2Galaxy(vector3d hyperSpaceCoordinates)
{
	f64 xFull, yFull, xInt, xFrac, yInt, yFrac;
	s32 x, y;
	s32 xHigh,yHigh;
	u8 xLow, yLow, xy;
	xFull = hyperSpaceCoordinates.X*HYPERSPACE_SCALE/LIGHTYEAR;
	yFull = hyperSpaceCoordinates.Y*HYPERSPACE_SCALE/LIGHTYEAR;
	xInt = floor(xFull);
	xFrac = xFull-xInt;
	yInt = floor(yFull);
	yFrac = yFull-yInt;
	x = (s32)xInt;
	y = (s32)yInt;
	xLow = (u8)(x&15);
	yLow = (u8)(y&15);
	xHigh = x&0xFFFFFFF0;
	yHigh = y&0xFFFFFFF0;
	xy = xLow+(yLow<<4);

	//demixing
	galaxyRNG->SetSeedWithCoordinates(galaxySeed,16,xHigh,yHigh);
	xy-=galaxyRNG->GetByteByOffset(1);
	xy = sBoxInv[xy];
	xy-=galaxyRNG->GetByteByOffset(0);

	xLow = xy&15;
	yLow = xy>>4;
	x = (x&0xFFFFFFF0)^xLow;
	y = (y&0xFFFFFFF0)^yLow;
	xInt = (f64)x;
	yInt = (f64)y;

	return vector2d(xInt + xFrac,yInt + yFrac);
}

f64 Galaxy::GetHyperSpaceTwirl(vector2ds galaxyQuadrant)
{
	galaxyRNG->SetSeedWithCoordinates(galaxySeed,16,(u32)galaxyQuadrant.X,(u32)galaxyQuadrant.Y);
	return (f64)(-1.0+galaxyRNG->GetByteByOffset(5)/127.5);
}


//#########################################################################
//GalaxyStarSystem

GalaxyStarSystem::GalaxyStarSystem(vector2ds quadrantCoordinates)
{
	galaxyQuadrant = quadrantCoordinates;
	starRNG = new DeterminedRandomGenerator();//delete in ~GalaxyStarSystem
	statusFlags = 0;
}

GalaxyStarSystem::~GalaxyStarSystem()
{
	delete starRNG;//new in GalaxyStarSystem::GalaxyStarSystem
	starRNG = 0;
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

	//TODO: this is uniform distribution among whole quadrant, but what if two systems will be very close in adjanced quadrants?
	galaxyCoordinates.X = galaxyQuadrant.X+x/65536.0;
	galaxyCoordinates.Y = galaxyQuadrant.Y+y/65536.0;
	statusFlags|=1;
	//galaxyCoordinates.X = galaxyQuadrant.X+0.5;//DEBUG
	//galaxyCoordinates.Y = galaxyQuadrant.Y+0.5;
}

void GalaxyStarSystem::SetSeed(u8* seedData, u32 seedLen)
{
	starRNG->SetSeed(seedData,seedLen);
}

void GalaxyStarSystem::GenerateStarSystem(ResourceManager* resourceManager, Galaxy* galaxy)
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

	StarComponent* rootComponent;

	SpaceObject* root;
	SpaceObject* stargate;
	u32 number;
	f64 starMass;


	//Solar system
	//Everything not to scale

	starRNG->SetOffset(1000);
	//starRNG->SetOffset(1001); //__DEBUG

	//Star size: from 0.008 to 2100 solar radii, 2.8 - 1531500 units
	//Star mass: 0.014 - 265 solar masses, 27598 - 522391320 units
	number = starRNG->GenerateByte();
	number += 256*starRNG->GenerateByte();
	starMass = exp(number*0.000201+1)*500.0;

	componentIndex = 0;
	planetIndex = 0;

	//GenerateComponent(resourceManager,starMass,LIGHTYEAR*0.05,&root);

	//root->SetMotionType(SpaceObject::MOTION_NONE);


	rootComponent = new StarComponent();//delete below

	rootComponent->type = 0;//yet is composite
	rootComponent->mass = starMass;
	rootComponent->maxOrbiting = 0;
	rootComponent->outerOrbitLimit = STAR_SYSTEM_RADIUS*LIGHTYEAR*0.5;
	rootComponent->innerOrbitLimit = 0;
	rootComponent->radius = 0;
	rootComponent->colorIndexBV = 0;
	rootComponent->subComponentsOrbit = 0;
	rootComponent->luminosity = 1;
	rootComponent->subComponentA = 0;
	rootComponent->subComponentB = 0;

	GenerateComponent2(rootComponent);

	root = FinalizeComponent(resourceManager,rootComponent);

	//root->SetMotionType(SpaceObject::MOTION_NONE);
	root->SetIntProperty(SpaceObject::MOTION_TYPE,SpaceObject::MOTION_NONE);
	root->SetPosition(vector3d(0));

	stargateAddress = galaxy->Coordinates2StargateAddress(galaxyQuadrant);
	stargate = GenerateStargate(resourceManager,rootComponent,galaxy);
	if (stargate)
		stargate->SetOrbitalParent(root);

	GenerateWormholes(resourceManager,rootComponent,galaxy);

	delete rootComponent;//new here in scope
	rootComponent = 0;



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
	statusFlags|=2;
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
		star->SetFloatProperty(SpaceObject::MASS,mass);//in 10^24 kg
		//star->SetGravity(true,false);
		star->SetIntProperty(SpaceObject::EMIT_GRAVITY,1);
		star->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);

		//star->SetName(name);//name of star system
		{
			wchar_t tmp[255];
			swprintf(tmp, 255, L"%ws %wc", name.c_str(), 65+componentIndex);
			star->SetName(tmp);
		}
		componentIndex++;

		//DEBUG INFO
		wprintf(L" Star %ws\r\n",star->GetName().c_str());


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
			planet->SetFloatProperty(SpaceObject::MASS,planetMass);//in 10^24 kg
			//planet->SetGravity(true,false);
			planet->SetIntProperty(SpaceObject::EMIT_GRAVITY,1);
			planet->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);

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
				moon->SetFloatProperty(SpaceObject::MASS,moonMass);
				//moon->SetGravity(true,false);
				moon->SetIntProperty(SpaceObject::EMIT_GRAVITY,1);
				moon->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
				{
					wchar_t tmp[255];
					if (j>26)
					{
						swprintf(tmp, 255, L"Moon %i%c%c", i,97+(j/26),97+(j%26));
					}
					else
					{
						swprintf(tmp, 255, L"Moon %i%c", i,97+j);
					}
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
		//barycenter->SetGravity(false,false);
		barycenter->SetIntProperty(SpaceObject::EMIT_GRAVITY,0);
		barycenter->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
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

		component->subComponentA = new StarComponent();//delete in ~StarComponent of upper StarComponent
		component->subComponentB = new StarComponent();//delete in ~StarComponent of upper StarComponent


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
		//barycenter->SetGravity(false,false);
		barycenter->SetIntProperty(SpaceObject::EMIT_GRAVITY,0);
		barycenter->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
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

		//Max orbiting
		component->maxOrbiting = star_A_orbit+component->subComponentA->maxOrbiting;
		nextOrbit = star_B_orbit+component->subComponentB->maxOrbiting;
		if (component->maxOrbiting < nextOrbit) component->maxOrbiting = nextOrbit;

		wprintf(L" } Composite ends  %f \r\n", component->mass);
		returnObject = barycenter;
	}
	else
	{
		star = resourceManager->MakeStar(component->radius);
		star->SetFloatProperty(SpaceObject::MASS,component->mass);//in 10^24 kg
		//star->SetGravity(true,false);
		star->SetIntProperty(SpaceObject::EMIT_GRAVITY,1);
		star->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
		{
			wchar_t tmp[255];
			swprintf(tmp, 255, L"%ws %wc", name.c_str(), 65+componentIndex);
			star->SetName(tmp);
		}
		componentIndex++;

		component->maxOrbiting = component->radius;

		//wprintf(L" * Single star %f \r\n", component->mass);
		wprintf(L" * Star %ws %f \r\n", star->GetName().c_str(), component->mass);
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


	//moon orbit may not exceed inner limit for planet system
	moonOrbitLimit = planetOrbit - component->innerOrbitLimit;

	//moon orbit may not exceed outer limit for planet system
	if ((planetOrbit + moonOrbitLimit)>component->outerOrbitLimit)
		moonOrbitLimit = component->outerOrbitLimit - planetOrbit;


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
			//swprintf(tmp, 255, L"Planet %c", 97+planetIndex);//starting from b - "Planet b" [Hessman 2010 proposal scheme] 
			planet->SetName(tmp);
		}

		planet->SetFloatProperty(SpaceObject::MASS,planetMass);//in 10^24 kg
		//planet->SetGravity(true,false);
		planet->SetIntProperty(SpaceObject::EMIT_GRAVITY,1);
		planet->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
		i++;

		component->maxOrbiting = planetOrbit+planetRadius;

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
			moon->SetFloatProperty(SpaceObject::MASS,moonMass);
			//moon->SetGravity(true,false);
			moon->SetIntProperty(SpaceObject::EMIT_GRAVITY,1);
			moon->SetIntProperty(SpaceObject::AFFECTED_BY_GRAVITY,0);
			{
				wchar_t tmp[255];
				//swprintf(tmp, 255, L"Moon %c%i", 97+planetIndex,(j+2)); // "Moon c2" [Hessman 2010 proposal scheme] 
				swprintf(tmp, 255, L"Moon %i%c", planetIndex,97+j);

				moon->SetName(tmp);
			}

			component->maxOrbiting = planetOrbit+moonOrbitRadius+moonRadius;

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


void GalaxyStarSystem::GenerateWormholes(ResourceManager* resourceManager, StarComponent* component, Galaxy* galaxy)
{
	//s32 x,y;
	SpaceObject* wormhole;
	GalaxyStarSystem* destSystem;
	vector2d direction;
	vector2ds destination;
	f64 thisDistance;
	s32 wormholeCounter=0;
	s32 number;
	u32 i,j;
	core::array<WormholeInfo*> listWormholeLinks;
	core::array<SpaceObject*> listWormholes;
	bool flagDistanceCheck;

	number = starRNG->GenerateByte();
	wormholeDistance = component->maxOrbiting*(1.2+number*0.0004);//1.2 - 1.3

	if (wormholeDistance<2000000.0) 
		wormholeDistance = 2000000.0;

	
	//wormholeDistance = 662251140; //DEBUG

	galaxy->GetWormholesFrom(galaxyQuadrant,&listWormholeLinks);

	for (i=0;i<listWormholeLinks.size();i++)
	{
		destination = listWormholeLinks[i]->Star2;
		if (destination == galaxyQuadrant)
			destination = listWormholeLinks[i]->Star1;
		
		destSystem = galaxy->GetStarSystem(destination);

	
/*
	//Very-very dumb - all wormholes to stars in +-5 l.y. quad
	for (x=-5;x<=5;x++)
	for (y=-5;y<=5;y++)
	if (x!=0 || y!=0)
	{
		destSystem = galaxy->GetStarSystem(vector2ds(x+galaxyQuadrant.X,y+galaxyQuadrant.Y));*/
		if (destSystem!=0)
		{
			direction = destSystem->galaxyCoordinates-galaxyCoordinates;
			direction.normalize();

			//direction.X = 1;
			//direction.Y = 0;

			//if (wormholeCounter==0) direction = vector2d(1,0); //DEBUG

			number = starRNG->GenerateByte();
			thisDistance = wormholeDistance*(1.0+(number-128)*0.00001);

			wormhole = resourceManager->MakeWormhole();
			//wormhole->SetMotionType(SpaceObject::MOTION_NONE);
			wormhole->SetIntProperty(SpaceObject::MOTION_TYPE,SpaceObject::MOTION_NONE);
			wormhole->SetPosition(vector3d(direction.X*thisDistance,direction.Y*thisDistance,0));
			//wormhole->SetRotation(90+atan2(direction.Y,direction.X)/CoeffDegreesToRadians);

			wormhole->SetFloatProperty(SpaceObject::ROTATION_ANGLE,TWO_PI*0.25+atan2(direction.Y,direction.X));//perpendicular to direction to destination
			/*
			{
				wchar_t tmp[255];
				swprintf(tmp, 255, L"Wormhole to %s",destSystem->name.c_str());
				wormhole->SetName(tmp);
			}*/
			//wormhole->SetName(text_string(L"Unknown wormhole"));
			wormhole->SetName(text_string(L"Wormhole to ")+destSystem->name);

			//wormhole->SetIntProperty(SpaceObject::TRAVEL_TO_X,x+galaxyQuadrant.X);
			//wormhole->SetIntProperty(SpaceObject::TRAVEL_TO_Y,y+galaxyQuadrant.Y);
			wormhole->SetIntProperty(SpaceObject::TRAVEL_TO_X,destination.X);
			wormhole->SetIntProperty(SpaceObject::TRAVEL_TO_Y,destination.Y);

			listWormholes.push_back(wormhole);

			wormholeCounter++;
			destSystem->unlock(0);//free if not stored somewhere else
		}
	}

	flagDistanceCheck = true;

	//Check for wormhole to be too close to each other
	//Probably this would never happens, but still
	while(flagDistanceCheck)
	{
 		flagDistanceCheck = false;
		for (j=1;j<listWormholes.size();j++)
			for (i=0;i<j;i++)
			{
				if ((listWormholes[i]->GetPosition() - listWormholes[j]->GetPosition()).getLengthSQ()<10000)
				{
					vector3d position1 = listWormholes[i]->GetPosition();
					vector3d position2 = listWormholes[j]->GetPosition();
					vector3d distanceVector = position2-position1;
					distanceVector.normalize();
					if (distanceVector.getLengthSQ() < 0.3)
					{
						distanceVector.X = 1;
						distanceVector.Y = 0;
						distanceVector.Z = 0;
					}
					distanceVector*=200;
					listWormholes[i]->SetPosition(position1-distanceVector);
					listWormholes[j]->SetPosition(position2+distanceVector);
					flagDistanceCheck = true;
					goto labelBreakDistanceCheck;//could not do break from two nested loops
				}
			}
labelBreakDistanceCheck:;
	}

	
}


SpaceObject* GalaxyStarSystem::GenerateStargate(ResourceManager* resourceManager, StarComponent* component, Galaxy* galaxy)
{
	s32 stargateStatus = galaxy->CheckStargatePresence(galaxyQuadrant,false);
	if (stargateStatus==0)
		return 0;//no stargate in system, nothing to do
	//TODO: destroyed stargate could be displayed

	f64 stargateDistance, dist2;
	f64 orbitPhase;
	f64 orbitPeriod;
	f64 rotation;
	s32 number;
	SpaceObject* stargate;

	stargateDistance = component->innerOrbitLimit * 2.5;
	dist2 = component->maxOrbiting*1.1;
	if (dist2>stargateDistance) stargateDistance = dist2;
	dist2 = 100000.0;
	if (dist2>stargateDistance) stargateDistance = dist2;

	component->maxOrbiting = stargateDistance;
	
	//stargateDistance = 100000;//DEBUG

	//OrbitPhase = epoch - totally random
	number = starRNG->GenerateByte();
	orbitPhase = number * TWO_PI/256.0;

	//rotation - random
	number = starRNG->GenerateByte();
	rotation = number * TWO_PI/256.0;

	orbitPeriod = TWO_PI * stargateDistance * sqrt(stargateDistance/(component->mass*G_CONSTANT));

	stargate = resourceManager->MakeStargate();

	stargate->SetOrbitalParams(0,stargateDistance,orbitPeriod,orbitPhase);
	//parent will be set up in caller function

	stargate->SetFloatProperty(SpaceObject::ROTATION_ANGLE,rotation);
	stargate->SetName(text_string(L"Stargate"));

	//wprintf(L" * Stargate is present in system, address %I64u\r\n",stargateAddress);//DEBUG
	wprintf(L" * Stargate is present in system\r\n");

	return stargate;
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
	//u32 * data32=(u32*)data;
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
	hasher = new SHA1();//delete in ~DeterminedRandomGenerator
	offset = -1;
	blockOffset = -1;
	memset(hashBuffer,0,bufferLength);
	//SetSeed(0,0);
	SetOffset(0);
}

DeterminedRandomGenerator::~DeterminedRandomGenerator()
{
	delete hasher;//new in DeterminedRandomGenerator::DeterminedRandomGenerator
	hasher = 0;
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
	hasher = new SHA1();//delete in ~UndeterminedRandomGenerator
	offset = 0;
	memset(hashBuffer,0,bufferLength);//clean, as compiler would not like leaving buffer with untouched memory content
	GenerateBlock();
}

UndeterminedRandomGenerator::~UndeterminedRandomGenerator()
{
	delete hasher;//new in UndeterminedRandomGenerator::UndeterminedRandomGenerator
	hasher = 0;
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
	u32 i;
	for (i=0;i<len;i++)
	{	//NOT OPTIMIZED
		destination[i]=GenerateByte();
	}
}

void UndeterminedRandomGenerator::GenerateBlock()
{
	u32 pos;
	u64 systemTime;
	u32 systemRandom;
	u64 memoryAddress;

	// random sources:
	//  0-15  prev random [16]
	// 16-23  counter [8]
	// 24-31  time [8]
	// 32-35  systemRandom [4]
	// 36-43  address of time variable [8]
	// 44-63  (RFU)

	counter++;
	pos = blockLength;
	memcpy(hashBuffer+pos,&counter,8);pos+=8;

	systemTime = (u64)time(0);
	memcpy(hashBuffer+pos,&systemTime,8);pos+=8;

	systemRandom = rand();
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
//StarComponent - hold info for component of (multiple) star

StarComponent::StarComponent()
{
	type = 0;
	mass = 0;
	radius = 0;
	luminosity = 1;
	innerOrbitLimit = 0;
	outerOrbitLimit = 0;
	maxOrbiting = 0;
	colorIndexBV = 0;
	subComponentsOrbit = 0;

	subComponentA = 0;
	subComponentB = 0;
}

StarComponent::~StarComponent()
{
	if (subComponentA)
	{
		delete subComponentA;
		subComponentA = 0;
	}
	if (subComponentB)
	{
		delete subComponentB;
		subComponentB = 0;
	}
}


//#########################################################################
//main()

int main(int ArgumentCount, char **Arguments) {

	printf("DangerGalaxy demo1 started\r\n");

	//u64 number1=0x0400000000,number2=22913657667,number3=34370879761;
	//printf("rsa-test: fp_powmod(%I64u,%I64u,%I64u)=%I64u\r\n",number1,number2,number3,fp_powmod(number1,number2,number3));

	{
		DeterminedRandomGenerator* pRNG = new DeterminedRandomGenerator();//delete is below

		for (;;)
		{
			//UndeterminedRandomGenerator* pRNG = new UndeterminedRandomGenerator();
			u8 testSeed[32]={0x69,0x55,0xF1,0x14, 0xED,0xFE,0x58,0x45, 0xA9,0x21,0x30,0x61, 0x95,0x19,0x21,0x32,
				0x4D,0xD8,0x71,0xB5, 0xB9,0x76,0xEC,0x03, 0x29,0xAD,0xCC,0x3B, 0xC2,0xF1,0xE2,0x07};
			//u8 testSeed[32];//={0x11,0x12,0x23,0x;
			u8 testVector1[16]={0xED,0x4B,0x97,0x67,0x02,0xC1,0x47,0x24,0x9E,0x89,0xF3,0xB7,0x1D,0x28,0x21,0xC9};
			u8 testVector2[16]={0x36,0x45,0xFA,0x99,0x68,0xDC,0xEB,0x49,0x7E,0xC3,0x1E,0xCC,0x0C,0x01,0x68,0x93};
			u8 testOut1[16],testOut2[16];

			//for (u32 i=0;i<32;i++)
			//	testSeed[i]=11;
			pRNG->SetSeedWithCoordinates(testSeed,32,1,1);
			//pRNG->AddSeed(testSeed,32);

			//printf("seed (1,1) from 0 v1:");
			for (u32 i=0;i<16;i++)
				//printf("%02X",pRNG->GenerateByte());
				testOut1[i]=pRNG->GenerateByte();
			//printf("\r\n");

			if (memcmp(testVector1,testOut1,16)!=0)
			{
				printf("WARNING! Determined generator failed on 1st test\r\n");
				break;
			}

			//pRNG->SetOffset(3);
			pRNG->SetSeedWithCoordinates(testSeed,32,1,2);

			//printf("seed (1,2) from 3 v2:");
			for (u32 i=0;i<16;i++)
				//printf("%02X",pRNG->GetByteByOffset(i+1003));
				testOut2[i]=pRNG->GetByteByOffset(i+1003);
				//printf("%02X",pRNG->GenerateByte());
			//printf("\r\n");
			if (memcmp(testVector2,testOut2,16)!=0)
			{
				printf("WARNING! Determined generator failed on 2nd test\r\n");
				break;
			}
			printf("Determined generator works fine\r\n");
			break;
		}
		delete pRNG;//new is above
		pRNG = 0;
	}

	//Init and semi-test
	GlobalURNG::Instance().GenerateByte();


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

	delete game;
	game = 0;

	return 0;
}

