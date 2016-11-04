//	lifelib.c	07/18/2013
//******************************************************************************
//******************************************************************************
//
//	LL     IIII   FFFFFF  EEEEEE  LL     IIII  BBBBB        CCCCC
//	LL      II    FF      EE      LL      II   BB  BB      CC   CC
//	LL      II    FF      EE      LL      II   BB  BB      CC
//	LL      II    FFFF    EEEE    LL      II   BBBBB       CC
//	LL      II    FF      EE      LL      II   BB  BB      CC
//	LL      II    FF      EE      LL      II   BB  BB  ..  CC   CC
//	LLLLL  IIII   FF      EEEEEE  LLLLL  IIII  BBBBB   ..   CCCCC
//
//
//******************************************************************************
//******************************************************************************
// includes
#include "msp430x22x4.h"
#include "RBX430-1.h"

// still lifes
const uint8 block[] = { "x = 2, y = 2, rule = B3/S23\n2o$2o!" };
const uint8 beehive[] = { "x = 3, y = 4, rule = B3/S23\nbo$obo$obo$bo!" };
const uint8 loaf[] = { "x = 4, y = 4, rule = B3/S23\nb2o$o2bo$obo$bo!" };
const uint8 boat[] = { "x = 3, y = 3, rule = B3/S23\n2o$obo$bo!" };

// oscillators
const uint8 blinker[] = { "x = 3, y = 1, rule = B3/S23\n3o!" };
const uint8 toad[] = { "x = 4, y = 2, rule = B3/S23\nb3o$3o!" };
const uint8 beacon[] = { "x = 4, y = 4, rule = B3/S23\n2b2o$3bo$o$2o!" };

const uint8 by_flop[] = { "x = 6, y = 7, rule = B3/S23\n"
		"3bo$bobo$5bo$5o$5bo$bobo$3bo!" };

const uint8 hexapole[] = {	"x = 9, y = 9, rule = B3/S23\n"
		"2o$obo2$2bobo2$4bobo2$6bobo$7b2o!"  };

const uint8 pulsar[] = { "x = 13, y = 13, rule = B3/S23\n"
		"2b3o3b3o2$o4bobo4bo$o4bobo4bo$o4bobo4bo$2b3o3b3o2$2b3o3b3o$o4bobo4bo$o"
		"4bobo4bo$o4bobo4bo2$2b3o3b3o!" };

// guns
const uint8 gosper_glider_gun[] = {	"x = 36, y = 9, rule = B3/S23\n"
		"24bo$22bobo$12b2o6b2o12b2o$11bo3bo4b2o12b2o$2o8bo5bo3b2o$"
		"2o8bo3bob2o4bobo$10bo5bo7bo$11bo3bo$12b2o!" };

const uint8 gosper_glider_gun2[] = { "x = 36, y = 9, rule = B3/S23\n"
		"12b2o$11bo3bo$10bo5bo7bo$2o8bo3bob2o4bobo$2o8bo5bo3b2o$"
		"11bo3bo4b2o12b2o$12b2o6b2o12b2o$22bobo$24bo$!" };

// spaceships
const uint8 glider[] = { "x = 3, y = 3, rule = B3/S23\n3o$2bo$bo!" };
const uint8 glider1[] = { "x = 3, y = 3, rule = B3/S23\nbo$2bo$3o!" };

const uint8 lwss[] = { "x = 5, y = 4, rule = B3/S23\no2bo$4bo$o3bo$b4o!" };
const uint8 mwss[] = { "x = 6, y = 5, rule = B3/S23\n2bo$o3bo$5bo$o4bo$b5o!" };
const uint8 hwss[] = { "x = 7, y = 5, rule = B3/S23\n2b2o$o4bo$6bo$o5bo$b6o!" };

const uint8 bird[] = { "x = 10, y = 20, rule = B3/S23\n"
		"4bobo$3bo$3bo$3bo2bo$3b3o5$4b2o$2b2ob2o$2b4o$3b2o3$2b3o$bo2bo$4bo$4bo$bobo!"  };

const uint8 loafer[] = { "x = 9, y = 9, rule = B3/S23\n"
		"b2o2bob2o$o2bo2b2o$bobo$2bo$8bo$6b3o$5bo$6bo$7b2o!"
};

const uint8 canada_goose[] = { "x = 13, y = 12, rule = B3/S23\n"
		"10b3o$b2o9bo$ob3o6bo$4b2o2b2o$8bo$4bo$3bo3b2o$4b2obobo$b2obo2bobo$4b2o"
		"4bo$9b2o$9b2o!" };

// factories
const uint8 beacon_maker[] = { "x = 49, y = 54, rule = B3/S23\n"
		"53b2o$52bobo$51bo$50bo$49bo$"
		"48bo$47bo$46bo$45bo$44bo$43bo$42bo$41bo$40bo$39bo$38bo$37bo$36bo$35bo$"
		"34bo$33bo$32bo$31bo$30bo$29bo$28bo$27bo$26bo$25bo$24bo$23bo$22bo$21bo$"
		"20bo$19bo$18bo$17bo$16bo$15bo$14bo$13bo$12bo$11bo$10bo$9bo$8bo$7bo$6bo"
		"$5bo$4bo$3bo$3o$2bo$2bo!" };
//		"x = 49, y = 61, rule = B3/S23\n"
//		"60b2o$59bobo$58bo$57bo$56bo$55bo$54bo$53bo$52bo$51bo$50bo$49bo$"
//		"48bo$47bo$46bo$45bo$44bo$43bo$42bo$41bo$40bo$39bo$38bo$37bo$36bo$35bo$" };

const uint8 blinker_puffer[] = { "x = 9, y = 18, rule = B3/S23\n"
		"5bo$3bo3bo$8bo$3bo4bo$4b5o4$6b2o$3b3ob2o$4b4o$5b2o2$2b2o$"
		"o4bo$6bo$o5bo$b6o!" };

const uint8 carnivore[] = { "x = 31, y = 21, rule = B3/S23\n"
		"28b2o$28b2o2$26b4o$26bo3bo$29bo$29bo$2bo17bo7bo$o3bo13bo3bo4bobo$5bo4b"
		"5o8bo4bo$o4bo3bo4bo3bo4bo$b5o8bo4b5o4bo$9bo3bo13bobo$11bo16bo$29bo$29b"
		"o$26bo3bo$26b4o2$28b2o$28b2o!" };

const uint8 converter[] = { "x = 29, y = 32, rule = B3/S23\n"
		"6bo14b3o$7b2o11bo2bo$6b2o15bo$23bo$20bobo8$17bobo$18b2o$18bo5$15bo$14b"
		"2o8b2o$2o11b3obo5bo2bo$2o10b2o8b2ob3o$13b2o8b2obo$14bo10bo2$14bo$13b2o"
		"$2o10b2o13b2o$2o11b3obo9b2o$14b2o$15bo!" };

// HighLife patterns
const uint8 replicator[] = { "x = 4, y = 4, rule = B36/S23\nb3o$o3b$o3b$o!" };


// lcd images
const uint16 life_image[] = { 126, 76,
	0x0dff,0x8000,0x87df,0x000e,0x08ff,0x8380,0x87df,0x05ff,0x7000,0xfe8e,0x01fe,
	0x7410,0x000e,0x06ff,0x0dff,0xfe80,0x01fe,0x769f,0x08ff,0xffce,0x01fe,0x039f,
	0x04ff,0xfb80,0x03fe,0x77df,0x06ff,0x0dff,0xffce,0x02fe,0x000e,0x07ff,0xffd0,
	0x01fe,0x069f,0x04ff,0xfc00,0x04fe,0x039f,0x05ff,0x0dff,0xffd0,0x02fe,0x039f,
	0x07ff,0x02fe,0x77df,0x04ff,0xffc0,0x04fe,0x77df,0x05ff,0x0dff,0x03fe,0x77df,
	0x07ff,0x03fe,0x04ff,0xfc00,0x04fe,0xd7df,0x05ff,0x0dff,0x04fe,0x000e,0x06ff,
	0x03fe,0x000e,0x03ff,0xfb80,0x05fe,0x000e,0x04ff,0x0dff,0x04fe,0x001a,0x06ff,
	0x03fe,0x0010,0x03ff,0xfb80,0x05fe,0x001f,0x04ff,0x0dff,0x04fe,0x041f,0x06ff,
	0xffd0,0x02fe,0x039f,0x03ff,0xf800,0x05fe,0x039f,0x04ff,0x0dff,0xffd0,0x03fe,
	0x77df,0x06ff,0xffce,0x02fe,0x039f,0x03ff,0x8000,0x05fe,0x069f,0x04ff,0x0dff,
	0xffd0,0x03fe,0xd7df,0x06ff,0xffce,0x02fe,0x039f,0x03ff,0x7000,0x05fe,0x77df,
	0x04ff,0x0dff,0xffce,0x04fe,0x000e,0x05ff,0xffc0,0x02fe,0x069f,0x04ff,0x05fe,
	0x77df,0x04ff,0x0dff,0xffce,0x01fe,0xffce,0x02fe,0x001f,0x05ff,0xfb80,0x02fe,
	0x07df,0x04ff,0xffd0,0x05fe,0x04ff,0x0dff,0xffce,0x01fe,0xffc0,0x02fe,0x039f,
	0x05ff,0xfb80,0x02fe,0x07df,0x04ff,0xffce,0x05fe,0x000e,0x03ff,0x0dff,0xffc0,
	0x01fe,0xffc0,0x02fe,0x07df,0x05ff,0x7000,0x02fe,0x041f,0x04ff,0xffc0,0x05fe,
	0x0010,0x03ff,0x0dff,0xfc00,0x01fe,0xfc00,0x02fe,0x77df,0x06ff,0xffda,0x01fe,
	0x039f,0x04ff,0xfc00,0x05fe,0x001f,0x03ff,0x0dff,0xfb80,0x01fe,0xfb80,0x03fe,
	0x06ff,0xfc00,0x01fe,0x001f,0x04ff,0xfb80,0x05fe,0x039f,0x03ff,0x0dff,0xfb80,
	0x01fe,0xfb80,0x03fe,0x000e,0x05ff,0x7000,0x87da,0x000e,0x04ff,0xd000,0x05fe,
	0x041f,0x03ff,0x02ff,0xfc0e,0x87df,0x7390,0x08ff,0xf800,0x01fe,0xfb80,0x03fe,
	0x001a,0x0cff,0x7000,0x05fe,0x07df,0x03ff,0x01ff,0xd380,0x03fe,0x0390,0x07ff,
	0x7000,0x01fe,0xf800,0x03fe,0x039f,0x05ff,0x8380,0x769f,0x06ff,0x05fe,0x77df,
	0x03ff,0x01ff,0xffce,0x04fe,0x000e,0x07ff,0x01fe,0xf800,0x03fe,0x041f,0x05ff,
	0xffd0,0x01fe,0x039f,0x05ff,0xffd0,0x04fe,0x87df,0x03ff,0x7000,0x05fe,0x769f,
	0x07ff,0x87d0,0xf800,0x03fe,0x07df,0x04ff,0x7000,0x02fe,0x041f,0x05ff,0xffce,
	0x05fe,0x03ff,0x8000,0x06fe,0x0010,0x06ff,0x7400,0x8000,0x03fe,0x77df,0x04ff,
	0xf800,0x02fe,0x77df,0x05ff,0xfc00,0x05fe,0x000e,0x02ff,0xfb80,0x06fe,0x069f,
	0x07ff,0x8000,0x03fe,0x87df,0x04ff,0xfb80,0x03fe,0x05ff,0xfb80,0x05fe,0x000e,
	0x02ff,0xfb80,0x07fe,0x000e,0x06ff,0x7000,0x04fe,0x04ff,0xfc00,0x03fe,0x0010,
	0x04ff,0xf800,0x05fe,0x001f,0x02ff,0xfb80,0x03fe,0x800e,0x03fe,0x039f,0x06ff,
	0x7000,0x04fe,0x000e,0x03ff,0xffc0,0x03fe,0x001f,0x04ff,0x8000,0x05fe,0x001f,
	0x02ff,0xffc0,0x03fe,0x01ff,0xffd0,0x02fe,0x77df,0x07ff,0x04fe,0x0010,0x03ff,
	0xffc0,0x03fe,0x039f,0x04ff,0x7000,0x05fe,0x039f,0x02ff,0xffc0,0x03fe,0x01ff,
	0xffce,0x03fe,0x000e,0x05ff,0x7000,0x04fe,0x001f,0x03ff,0xffc0,0x03fe,0x07df,
	0x05ff,0xffda,0x04fe,0x041f,0x02ff,0xffc0,0x03fe,0x01ff,0xfc00,0x03fe,0x001a,
	0x06ff,0x04fe,0x039f,0x03ff,0xffc0,0x03fe,0x77df,0x05ff,0xffce,0x04fe,0x07df,
	0x02ff,0xffc0,0x03fe,0x01ff,0xf800,0x03fe,0x041f,0x06ff,0x04fe,0x041f,0x03ff,
	0xffc0,0x03fe,0x87df,0x05ff,0xffce,0x04fe,0x77df,0x02ff,0xfc00,0x03fe,0x000e,
	0x7000,0x03fe,0x77df,0x06ff,0xffd0,0x03fe,0x07df,0x03ff,0xffc0,0x04fe,0x000e,
	0x04ff,0xfc00,0x04fe,0x87df,0x02ff,0xfb80,0x03fe,0x02ff,0x04fe,0x06ff,0xffd0,
	0x03fe,0x77df,0x03ff,0xfc00,0x04fe,0x000e,0x04ff,0xfb80,0x05fe,0x02ff,0xfb80,
	0x03fe,0x000e,0x01ff,0xffce,0x03fe,0x0010,0x05ff,0xffce,0x03fe,0x87df,0x03ff,
	0xfc00,0x04fe,0x001a,0x04ff,0xf800,0x05fe,0x000e,0x01ff,0xf800,0x03fe,0x000e,
	0x01ff,0xffc0,0x03fe,0x039f,0x05ff,0xffce,0x03fe,0xd7df,0x03ff,0xfb80,0x04fe,
	0x001f,0x04ff,0x7000,0x05fe,0x000e,0x01ff,0x7000,0x03fe,0x001a,0x01ff,0xfc00,
	0x03fe,0x041f,0x05ff,0xffce,0x04fe,0x03ff,0xfb80,0x04fe,0x039f,0x04ff,0x7000,
	0x05fe,0x0010,0x01ff,0x01ff,0x03fe,0x001f,0x01ff,0xfb80,0x03fe,0x77df,0x05ff,
	0xffce,0x04fe,0x000e,0x02ff,0xfb80,0x04fe,0x041f,0x05ff,0xffda,0x04fe,0x001f,
	0x01ff,0x01ff,0xffd0,0x02fe,0x039f,0x01ff,0xd000,0x03fe,0x87df,0x05ff,0xffc0,
	0x04fe,0x0010,0x02ff,0xfb80,0x04fe,0x07df,0x05ff,0xffce,0x04fe,0x039f,0x01ff,
	0x01ff,0xffce,0x02fe,0x041f,0x01ff,0x7000,0x04fe,0x05ff,0xffc0,0x04fe,0x001a,
	0x02ff,0xf800,0x04fe,0x77df,0x05ff,0xffce,0x04fe,0x039f,0x01ff,0x01ff,0xfb80,
	0x02fe,0x77df,0x02ff,0x04fe,0x000e,0x04ff,0xffc0,0x04fe,0x001f,0x02ff,0x8000,
	0x04fe,0x77df,0x05ff,0xfc00,0x04fe,0x039f,0x01ff,0x01ff,0x8000,0x02fe,0x77df,
	0x02ff,0x04fe,0x001f,0x04ff,0xfc00,0x04fe,0x039f,0x02ff,0x7000,0x04fe,0x87df,
	0x05ff,0xfb80,0x04fe,0x07df,0x01ff,0x02ff,0xffda,0x02fe,0x02ff,0xffd0,0x03fe,
	0x039f,0x04ff,0xfb80,0x04fe,0x039f,0x02ff,0x7000,0x05fe,0x05ff,0xf800,0x04fe,
	0x77df,0x01ff,0x02ff,0xffce,0x02fe,0x000e,0x01ff,0xffce,0x03fe,0x039f,0x01ff,
	0x8380,0x07fe,0x041f,0x02ff,0x7000,0x05fe,0x05ff,0x8000,0x04fe,0x77df,0x01ff,
	0x02ff,0xfb80,0x02fe,0x039f,0x01ff,0xffce,0x03fe,0x07df,0x01ff,0xffd0,0x07fe,
	0x07df,0x03ff,0x05fe,0x000e,0x04ff,0x7000,0x04fe,0x77df,0x01ff,0x02ff,0x7000,
	0x02fe,0x041f,0x01ff,0xffc0,0x03fe,0x07df,0x01ff,0x08fe,0x07df,0x03ff,0xffd0,
	0x04fe,0x000e,0x04ff,0x7000,0x04fe,0xd7df,0x01ff,0x03ff,0xffce,0x01fe,0x77df,
	0x01ff,0xffc0,0x03fe,0x77df,0x01ff,0xffd0,0x07fe,0x77df,0x03ff,0xffce,0x04fe,
	0x000e,0x05ff,0xffda,0x04fe,0x01ff,0x03ff,0xfb80,0x02fe,0x000e,0xffc0,0x03fe,
	0x77df,0x01ff,0xffce,0x07fe,0x77df,0x03ff,0xffce,0x04fe,0x0010,0x05ff,0xffce,
	0x04fe,0x000e,0x01ff,0xfc0e,0x0390,0x01ff,0xffda,0x01fe,0x039f,0xffc0,0x03fe,
	0x87df,0x01ff,0xffc0,0x07fe,0x87df,0x03ff,0xffc0,0x04fe,0x0010,0x05ff,0xffce,
	0x04fe,0x000e,0x8000,0x01fe,0x77df,0x01ff,0xfb80,0x01fe,0x77df,0xffce,0x03fe,
	0xd7df,0x01ff,0xfb80,0x08fe,0x03ff,0xfb80,0x04fe,0x001f,0x05ff,0xffc0,0x04fe,
	0x0010,0x8000,0x02fe,0x0010,0x01ff,0xffd0,0x06fe,0x01ff,0xd000,0x08fe,0x03ff,
	0xfb80,0x04fe,0x001f,0x05ff,0xfc00,0x04fe,0x001f,0x7000,0x02fe,0x77df,0x01ff,
	0x7380,0x87da,0xffd0,0x04fe,0x02ff,0x08fe,0x000e,0x02ff,0xf800,0x04fe,0x001f,
	0xfc00,0x7390,0x000e,0x02ff,0xfb80,0x04fe,0x001f,0x01ff,0xffce,0x02fe,0x0390,
	0x02ff,0xffd0,0x04fe,0x02ff,0xfc00,0x07fe,0x000e,0x02ff,0x8000,0x04fe,0x001f,
	0xffc0,0x01fe,0x77df,0x038e,0x01ff,0xf800,0x04fe,0x039f,0x01ff,0xd000,0x02fe,
	0x87df,0x000e,0x8000,0x04fe,0x87df,0x02ff,0x7000,0xfc0e,0x06fe,0x000e,0x02ff,
	0x7000,0x04fe,0x001f,0xfb80,0x03fe,0x7390,0xd00e,0x04fe,0x039f,0x02ff,0xffd0,
	0x08fe,0x77df,0x04ff,0x7380,0x05fe,0x0010,0x03ff,0x04fe,0x001a,0xfb80,0x09fe,
	0x039f,0x02ff,0xfc00,0x08fe,0x77df,0x05ff,0x05fe,0x000e,0x03ff,0xffd0,0x03fe,
	0x0010,0x8000,0x09fe,0x041f,0x02ff,0x7000,0x08fe,0x07df,0x04ff,0x7000,0x05fe,
	0x001f,0x03ff,0xffce,0x03fe,0x000e,0x01ff,0xffda,0x08fe,0x07df,0x03ff,0xfc0e,
	0x07fe,0x039f,0x05ff,0x05fe,0x001f,0x03ff,0xffce,0x03fe,0x000e,0x01ff,0xffce,
	0x08fe,0x07df,0x03ff,0x7000,0xffda,0x06fe,0x0010,0x05ff,0xffda,0x04fe,0x039f,
	0x03ff,0xfc00,0x02fe,0x87df,0x02ff,0xfb80,0x08fe,0x07df,0x04ff,0xfb80,0x05fe,
	0xd7df,0x06ff,0xffd0,0x04fe,0x001f,0x03ff,0xfb80,0x02fe,0x77df,0x02ff,0x7000,
	0x08fe,0x041f,0x05ff,0xffce,0x04fe,0x041f,0x06ff,0xffce,0x04fe,0x039f,0x03ff,
	0x8000,0x02fe,0x039f,0x03ff,0xffce,0x07fe,0x039f,0x05ff,0x7000,0xffd0,0x03fe,
	0x000e,0x06ff,0xffce,0x04fe,0x039f,0x04ff,0xffda,0x01fe,0x000e,0x03ff,0x8380,
	0x07fe,0x000e,0x06ff,0x7000,0xfc0e,0x87df,0x038e,0x07ff,0xffce,0x04fe,0x039f,
	0x04ff,0x8380,0x741f,0x05ff,0x7380,0xd410,0x03fe,0x741f,0x0390,0x01ff,0x11ff,
	0xffc0,0x04fe,0x039f,0x13ff,0x11ff,0xffc0,0x04fe,0x041f,0x13ff,0x11ff,0xfc00,
	0x04fe,0x041f,0x13ff,0x11ff,0xfb80,0x04fe,0x041f,0x13ff,0x11ff,0xfb80,0x04fe,
	0x041f,0x13ff,0x11ff,0xfb80,0x04fe,0x07df,0x13ff,0x11ff,0xf800,0x04fe,0x07df,
	0x13ff,0x11ff,0xf800,0x04fe,0x07df,0x13ff,0x11ff,0x8000,0x04fe,0x07df,0x13ff,
	0x11ff,0x7000,0x04fe,0x07df,0x13ff,0x11ff,0x7000,0x04fe,0x07df,0x13ff,0x12ff,
	0x04fe,0x07df,0x13ff,0x12ff,0xffce,0x03fe,0x069f,0x13ff,0x12ff,0xffc0,0x03fe,
	0x039f,0x13ff,0x12ff,0xd380,0x03fe,0x0010,0x13ff,0x13ff,0xfc0e,0x01fe,0x7390,
	0x14ff
};

const uint8 jon_arbuckle1[] = { "x = 126, y = 75, rule = B3/S23\n"
		"51bo$"
		"37b2ob2o8bobo$"
		"36bo2b2o2bo3b2o2bo$"
		"33b2o2bo4b2o3bob2o$"
		"32bo2b2o7b2obo5bo$"
		"25bo2b2obob2o9bobob8o$"
		"23b3o3bobo2bo11bobo7bo$"
		"22bo3b3o2b3o12b2o3b4obo2bo$"
		"22bo2bo2bobo19bo3bob4o$"
		"20b2o4bobob2o18b2o$"
		"20bo6bo30b2o$"
		"17b2obo37bobo$"
		"16bobob2o30b2o6bo$"
		"13bo3bo2bo14bo15bobo5bo$"
		"13b4o3bo13bobo8bobo3bobob2obo$"
		"17b3o15bobo3b2obob4obob2obob2o$"
		"15bobo18b2o2bobobo5bo$"
		"14bobo23b2o3b5o$"
		"14b2o20b2o14b2ob2obo$"
		"12b2o21bobo7b5o2bob2ob2o$"
		"13bo21bo7b3o2bobobo6b2o$"
		"12bo23bo5bo8b2o6bobo$"
		"12b2o19b4o4bobo9b2o5b2o$"
		"13bo15b2o2bo6bobo10bobo6b2o$"
		"12bo16bo4bo5b2o13bo6bo$"
		"13b3o14b4o20bo8bo$"
		"16bo23b2o12b4o6bo$"
		"13b3obob2o9b2o8b2o15bo5b2o$"
		"13bo2b2obobo8b2o24bo6bo$"
		"14bo4bobo18b2o14b2o6bo$"
		"13b2ob4obob2o5b2o9bo21b2o$"
		"12bo3bo4bo2bo4bobo8bo15b2o5bo$"
		"12b3o2b3ob2o6bo10b2o14bo7bo$"
		"15b2o2bobo5bob2o10bo15bo5b2o$"
		"12b2o3bobobobo2bobo11bo15b2o$"
		"12bob4obobob4obo11b2o14bo6b2o$"
		"13bo4bobobo5b2o11bo11b2obo2b2obobo$"
		"14b3obobo3b4o12bo5b2ob2obobobobobobo$"
		"16bobob4o3bo13b3obob2obobobobobobob2o$"
		"16bobo5bo18bobo5b2obobobo2bo$"
		"15b2obob4o20b2o8b2obobobo$"
		"16bobobo25b2o3b3o3bobob2o$"
		"16bobo2bo24bobobo2bo3b2o$"
		"15b2ob4o3b2obo2bo17b2o13b2o$"
		"17bo6bobob4o23b4o5bo$"
		"17bob3o2bobo5b2o21bo2bo6bo$"
		"16b2obo2bobo2bob2obobo21b2o8bo$"
		"17bobobobo2b2obobo2bo30b2o$"
		"17bobobo6bo5b2o20b2o6bo$"
		"16b2obob2o3b2o28bo8b2o$"
		"17bobobo4bo7b2o21bo9bo$"
		"17bobobo2bobo7bo23bo6b2o$"
		"16b2ob2o3b2o9bo21b2o6bo$"
		"15bo2bo13b4o21bo8bo$"
		"15b2obo5b2o6bo21b2obo6bobo$"
		"16bob2o3bobo7bo14b2ob2o2bob2o5b2o$"
		"15bo3bo3bo8b2o13bobobob2o$"
		"15bob2o5bo6bo15bo2bo13b2o$"
		"14b2obo5b2o6bo13b2ob2o14bo$"
		"15bobo11b2ob2o12bobo13bobo$"
		"15bob2o11bobobob2o8bobo4bo8b2o$"
		"14b2o14bobobobo2b2o4b2ob2o2bobo5b2o$"
		"15bo15bo3bo2b2o2bo9b2o5bobo$"
		"15bobo23b2o16b2o$16b2o25b2o12b2o$"
		"18b2o23bobo5b2obobobo$"
		"18bo2bo2bo19bobob2o2bob2o$"
		"19b6o20b2obob2o$"
		"25b2o21bo$"
		"21b2obo2bob2o14b4o$"
		"20bobob4obobo13bo3b2o$"
		"20b2o7bobo2bo8b2o2b2o2bo$"
		"18b2o6b2obob4o7bo2b2obob2o$"
		"19bo7bob2o9bo2b2o3bobo$"
		"17bo9bo4b3o3b5o2b4o2bo$"
		/*
		"17b2o6b2ob4o2bo2bo5bo6b2o$"
		"18bo5bobobo3bo4b6ob2o2b2o$"
		"17bo6b2o3b3ob4o5bobo2bo2b2o$"
		"17b2o12bobo3b5o2bo3bobobo$"
		"19bo4b2o8b3o2bo2b2o3b2obo2bo$"
		"17b2obo2bobo10bo4bo7bob2o$"
		"18bobo2bo16b2o7bobo$"
		"17bo3b3o24b2obo$"
		"18b3o3b2o14b2o6bo2b3o$"
		"21bo2bobo12bo2bo6b2o3bo$"
		"18b4o3bobo11bobo9b3o2bo5b2ob2o$"
		"18bo7bo3bo6b2obob3o4b2o3b2obo3bobobobob2o$"
		"19b3o7bobo6bobobo2bobo2bobo2bobo3bobobobobobo$"
		"21bo8bo2bo2bobob2o2b2ob2obob2o2b2ob2obobobo3bobo$"
		"17b4o10b7o9bo2bobo5bobobobo6bobo$"
		"16bo30bob2obo5bobobo2bo6b2o$"
		"16b5o10b5o12bo3b2o2b2obobo2b2o8b2o$"
		"20bo9bo4bo13b3o3bobobo14bobo$"
		"16b2o12b5o16bob3obo2bo14b2o$"
		"16bo11b2o8bo13bo5b3o8bo$"
		"17bo11bob2o4bobo13b5o3b2o5bobo4b2o$"
		"bo16bo10bobo4bobo16bo2b2obobo5bo6bo2bo20bo$"
		"obobob2ob2ob2ob4o9b2obo3bobo7bo12bobo2bo12bobobob2ob2obob2ob2ob2obobo$"
		"b2ob2ob2ob2obobo11bo2bo4bo7b5o15b2o10b2obob2ob2obob2ob2ob2obob2o$"
		"16b5o6b3o4b2o6bo5bo15bo5b2o2bo2bo$"
		"19bo14bo7b7o14bo5bobo2bobo$"
		"15bobo3bo5b3o2bobo28b2o4bobob2ob2o$"
		"14bob5obo3bo2bo2b2o6b9o11b2obo6b2o2bobo$"
		"14bo5bobo3b3o11bo6bobo11bobo8bobobo$"
		"15b4obobob2o6b2o7b5o3bo11bob2o3b3obob2o$"
		"17bob2ob2obob2o2bo2bo3b3o5b3ob2o7b2o4bobo2b2o$"
		"26b2obo2bobo2bo2bob4o2bobo2b2ob2o2bob2obob2o$"
		"29bob2obobobobobo2bo5b2ob2ob2o2b2obo$"
		"29bobo2bobobob2o$"
		"30bo2b2ob2o"
*/
		"!"
} ;

//------------------------------------------------------------------------------
// un-initialized MSP430F2274 interrupt vectors
//
//    .int00       : {}               > INT00
//    .int01       : {}               > INT01
//    PORT1        : { * ( .int02 ) } > INT02 type = VECT_INIT
//    PORT2        : { * ( .int03 ) } > INT03 type = VECT_INIT
//    .int04       : {}               > INT04
//    ADC10        : { * ( .int05 ) } > INT05 type = VECT_INIT
//    USCIAB0TX    : { * ( .int06 ) } > INT06 type = VECT_INIT
//    USCIAB0RX    : { * ( .int07 ) } > INT07 type = VECT_INIT
//    TIMERA1      : { * ( .int08 ) } > INT08 type = VECT_INIT
//    TIMERA0      : { * ( .int09 ) } > INT09 type = VECT_INIT
//    WDT          : { * ( .int10 ) } > INT10 type = VECT_INIT
//    .int11       : {}               > INT11
//    TIMERB1      : { * ( .int12 ) } > INT12 type = VECT_INIT
//    TIMERB0      : { * ( .int13 ) } > INT13 type = VECT_INIT
//    NMI          : { * ( .int14 ) } > INT14 type = VECT_INIT
//    .reset       : {}               > RESET

#pragma vector=PORT2_VECTOR,TIMER0_A1_VECTOR,TIMER0_A0_VECTOR,NMI_VECTOR,	\
		USCIAB0RX_VECTOR,USCIAB0TX_VECTOR,TIMERB0_VECTOR,TIMERB1_VECTOR
__interrupt void ISR_trap(void)
{
	ERROR2(SYS_ERR_ISR);				// unrecognized event
	// cause an access violation which (PUC reset)
	WDTCTL = 0;							// Write to WDT with a wrong password
}
