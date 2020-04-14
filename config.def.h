// DWM(https://dwm.suckless.org) config file written by __Pyrix__
// See LICENSE file for copyright details

#include "fibonacci.c"
#include <X11/XF86keysym.h>
#define MODKEY Mod4Mask
#define SHCMD(cmd) { .v = (const char*[]){"/bin/bash", "-c", cmd, NULL } }
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_Left,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_Right,	ACTION##stack,	{.i = INC(-1) } }, \

// Appearance

/* Gaps */
static const unsigned int gappih	= 10; // inner horizontal window gap
static const unsigned int gappiv	= 10; // inner vertical window gap
static const unsigned int gappoh	= 12; // outer horizontal window gap
static const unsigned int gappov	= 12; // outer vertical window gap
static const int smartgaps		=  0; // off = 0; on = 1
/* Borders */
static const unsigned int borderpx	=  3; // border width in px
static const unsigned int snap		= 32; // snap
/* Bar */
static const int showbar		=  1; // off = 0; on = 1
static const int topbar			=  1; // bottom = 0; top = 1
static const int vertpad		=  5; // vertical padding in px
static const int sidepad		=  5; // horizontal padding in px
/* Fonts */
static const char *fonts[]		= { 
	"Hack:size=10", 
	"FontAwesome5Free:style=Solid:size=10",
	"FontAwesome5Free:style=Regular:size=10",
	"FontAwesome5Brands:style=Regular:size=10",
};
static char dmenufont[]			= {  // dmenu fonts
	"Hack:size=10",
};
/* Colors */
static char normbgcolor[]	  	= "#222222"; // global bg color
static char normbordercolor[]		= "#444444"; // global border color
static char normfgcolor[]		= "#bbbbbb"; // global fg color
static char selbgcolor[]		= "#af04e5"; // selected bg color
static char selbordercolor[]		= "#af0fe5"; // selected border color
static char selfgcolor[]		= "#eeeeee"; // selected fg color
static char *colors[][3]		= {
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor, selbgcolor, selbordercolor },
};
/* Tags */
static const char *tags[] = {"","","","","","6","7","8","9"};
static const Rule rules[]		= { 	// tag rulset
	{ "Gimp",	NULL,	NULL,		1 << 8,	0,	-1 },

};
/* Layout */
static const float mfact		= 0.55; // factor of master area
static const int nmaster		=  1;   // # of clients in master
static const int resizehints		=  1;   // 0 = off; 1=respect hints
static const Layout layouts[]		= {
	{ "T",	tile },				// tiled windows
	{ "*",	NULL },				// floating windows
	{ "CM",	centeredmaster },		// master window in center
	{ "@",	spiral },			// fibonacci windows
	{ " \\",	dwindle },			// dwindled windows
};


// Core

/* Commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

/* Volume */
static const char *volup[]	  = {"amixer","sset","Master","5%+",NULL};
static const char *voldown[]	  = {"amixer","sset","Master","5%-",NULL};
static const char *bigvolup[]	  = {"amixer","sset","Master","15%+",NULL};
static const char *bigvoldown[]	  = {"amixer","sset","Master","15%-",NULL};
static const char *voltoggle[]	  = {"amixer","sset","Master","toggle",NULL};
static const char *audiocontrol[] = {"st","-e","alsamixer",NULL};
/*Keyboard*/
static Key keys[]			= {
	STACKKEYS(MODKEY,			focus)
	STACKKEYS(MODKEY|ShiftMask,		push)
	TAGKEYS(		XK_1,		0)
	TAGKEYS(		XK_2,		1)
	TAGKEYS(		XK_3,		2)
	TAGKEYS(		XK_4,		3)
	TAGKEYS(		XK_5,		4)
	TAGKEYS(		XK_6,		5)
	TAGKEYS(		XK_7,		6)
	TAGKEYS(		XK_8,		7)
	TAGKEYS(		XK_9,		8)
	{MODKEY,		XK_0,		 view,	{.ui = ~0} },
	{MODKEY|ShiftMask,	XK_0,		  tag,	{.ui = ~0} },
	{MODKEY|ShiftMask,	XK_minus,	spawn,	{.v = bigvoldown} },
	{MODKEY|ShiftMask,	XK_equal,	spawn,	{.v = bigvolup} },
	{MODKEY,		XK_Tab,		 view,	{0} },
	{MODKEY,		XK_q,	   killclient,  {0} },
	{MODKEY|ShiftMask,	XK_r,	    	 quit,  {1} },
	{MODKEY,		XK_t,	    setlayout,	{.v = &layouts[0]} },
	{MODKEY,		XK_u,	    setlayout,	{.v = &layouts[2]} },
	{MODKEY,		XK_f,	    setlayout,	{.v = &layouts[3]} },
	{MODKEY,		XK_y,	    setlayout,  {.v = &layouts[4]} },
	{MODKEY,		XK_d,		spawn,	{.v = dmenucmd} },
	{MODKEY,		XK_F11,	togglefullscr,	{0} },
	{MODKEY|ControlMask,	XK_Left,     setmfact,	{.f = -0.05} },
	{MODKEY|ControlMask,	XK_Right,    setmfact,	{.f = +0.05} },	
	{MODKEY,		XK_Return,	spawn,	{.v = termcmd} },
	{MODKEY,		XK_space,	 zoom,	{0} },
	{0,XF86XK_AudioRaiseVolume,		spawn,	{.v = voldown} },
	{0,XF86XK_AudioLowerVolume,		spawn, 	{.v = volup} },
	{0,XF86XK_AudioMute,			spawn,	{.v = voltoggle} },
};
/*Mouse*/
static Button buttons[]			= {
	{ClkLtSymbol,0,		Button1,    setlayout,  {0} },
	{ClkLtSymbol,0,		Button3,    setlayout,  {.v = &layouts[2]} },
	{ClkClientWin,MODKEY,	Button1,    movemouse,	{0} },
	{ClkTagBar,0,		Button1,	 view,	{0} },
	{ClkTagBar,0,		Button3,   toggleview,  {0} },
};
/*Defs*/
void
setlayoutex(const Arg *arg) {
	setlayout(&((Arg) {.v = &layouts[arg->i]}));
}
void
viewex(const Arg *arg) {
	view(&((Arg)	  {.ui = 1 << arg->ui}));
}
void
viewall(const Arg *arg) {
	view(&((Arg)	  {.ui = ~0}));
}
void
toggleviewex(const Arg *arg) {
	toggleview(&((Arg)	  {.ui = 1 << arg->ui}));
}	
void
tagex(const Arg *arg) {
	tag(&((Arg)	  {.ui = 1 << arg->ui}));
}	
void
toggletagex(const Arg *arg){
	toggletag(&((Arg) {.ui = 1 << arg->ui}));
}	
void
tagall(const Arg *arg) {
	tag(&((Arg)	  {.ui = ~0}));
}	
/*Signal Defs*/
static Signal signals[]			= {
	{"focusstack",		focusstack},
	{"setmfact",		setmfact},
	{"togglebar",		togglebar},
	{"incnmaster",		incnmaster},
	{"togglefloating",	togglefloating},
	{"focusmon",		focusmon},
	{"tagmon",		tagmon},
	{"zoom",		zoom},
	{"view",		view},
	{"viewall",		viewall},
	{"viewex",		viewex},
	{"toggleview",		toggleview},
	{"toggleviewex",	toggleviewex},
	{"tag",			tag},
	{"tagall",		tagall},
	{"tagex",		tagex},
	{"toggletag",		toggletag},
	{"toggletagex",		toggletagex},
	{"killclient",		killclient},
	{"quit",		quit},
	{"setlayout",		setlayout},
	{"setlayoutex",		setlayoutex},
	{"xrdb",		xrdb},
};

