/* see license file for copyright and license details. */

/* appearance */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */
static const char *fonts[]          = { "monospace:size=10", "JoyPixels:pixelsize=10:antialias=true:autohint=true"  };
static char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1: Web", "2: Develop", "3: Files", "4: Tasks", "5: Network", "6: Crypt", "7: MyCMS", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "clion",     NULL,       NULL,       1 << 1,            1,           -1 },
	{ "Firefox",     NULL,       NULL,       1 << 0,            0,           -1 },
	{0,     NULL,        "Network Manager",       1 << 4,            0,           -1 },
	{"Veracrypt",	NULL,        NULL,       1 << 5,            1,           -1 },
	{0,     NULL,        "VI File Manager",       1 << 2,            0,           -1 },
	{0,     NULL,       "Task Manager",       1 << 3,            0,           -1 },
	{0,     NULL,       "MyCMS",       1 << 6,            0,           -1 },
	{ "Gimp",     NULL,       NULL,       1 << 8,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
 	{ "[@]",      spiral },
 	{ "[\\]",     dwindle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_q,     ACTION##stack, {.i = 0 } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[] = {"st", NULL};
static const char scratchpadname[] = "Floating Panel";
//static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "160x48", NULL };
static const char *scratchpadcmd[] = { "urxvt", "-title", (const char *)scratchpadname, "-g", "160x48", NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY|ShiftMask,		XK_Escape,	spawn,	SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Close Xorg?\")\" = Yes ] && killall Xorg") },
	{ MODKEY,			XK_grave,	spawn,	SHCMD("/usr/local/share/dwm/./dmenuunicode") },
	TAGKEYS(			XK_1,		0)
	TAGKEYS(			XK_2,		1)
	TAGKEYS(			XK_3,		2)
	TAGKEYS(			XK_4,		3)
	TAGKEYS(			XK_5,		4)
	TAGKEYS(			XK_6,		5)
	TAGKEYS(			XK_7,		6)
	TAGKEYS(			XK_8,		7)
	TAGKEYS(			XK_9,		8)
	{ MODKEY,			XK_0,		view,		{.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,		tag,		{.ui = ~0 } },
	{ MODKEY,			XK_minus,	spawn,		SHCMD("pactl set-sink-volume 0 -10%") },
	{ MODKEY|ShiftMask,		XK_minus,	spawn,		SHCMD("pactl set-sink-volume 0 -25%") },
	{ MODKEY,			XK_equal,	spawn,		SHCMD("pactl set-sink-volume 0 +10%") },
	{ MODKEY|ShiftMask,		XK_equal,	spawn,		SHCMD("pactl set-sink-volume 0 +25%") },
	{ MODKEY|ShiftMask,		XK_BackSpace,	spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Reboot computer?\")\" = Yes ] && reboot") },
	{ MODKEY,			XK_Tab,		view,		{0} },
	{ MODKEY,			XK_q,		killclient,	{0} },
	{ MODKEY,			XK_w,		spawn,		SHCMD("$BROWSER") },
	{ MODKEY,			XK_e,		spawn,		SHCMD("$TERMINAL -e $MAILCLIENT") },
	{ MODKEY,			XK_t,		setlayout,	{.v = &layouts[0]} },
	{ MODKEY,			XK_y,		setlayout,	{.v = &layouts[4]} },
	{ MODKEY,			XK_u,		setlayout,	{.v = &layouts[2]} },
	{ MODKEY,			XK_i,		setlayout,	{.v = &layouts[3]} },
	{ MODKEY,			XK_o,		incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,		incnmaster,     {.i = -1 } },
	{ MODKEY,			XK_p,			spawn,		SHCMD("kill -STOP `pidof vlc`") },
	{ MODKEY|ShiftMask,		XK_p,			spawn,		SHCMD("kill -CONT `pidof vlc`") },
//	{ MODKEY,			XK_bracketleft,		spawn,		SHCMD("mpc seek -10") },
//	{ MODKEY|ShiftMask,		XK_bracketleft,		spawn,		SHCMD("mpc seek -120") },
//	{ MODKEY,			XK_bracketright,	spawn,		SHCMD("mpc seek +10") },
//	{ MODKEY|ShiftMask,		XK_bracketright,	spawn,		SHCMD("mpc seek +120") },
	{ MODKEY,			XK_backslash,		view,		{0} },
	{ MODKEY|ShiftMask,		XK_k,		spawn,  	SHCMD("killall -INT ffmpeg") },
	{ MODKEY,			XK_a,		spawn,		SHCMD("pavucontrol") },
	{ MODKEY,			XK_s,		togglesticky,	{0} },
	{ MODKEY|ShiftMask,		XK_s,		spawn,  	SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Suspend computer?\")\" = Yes ] && sudo suspend") },
	{ MODKEY,			XK_d,		spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,		XK_d,		togglegaps,	{0} },
	{ MODKEY,			XK_f,		togglefullscr,	{0} },
	{ MODKEY,			XK_g,		shiftview,	{ .i = -1 } },
	{ MODKEY,			XK_h,		setmfact,	{.f = -0.05} },
	{ MODKEY|ShiftMask,		XK_h,		spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Hibernate computer?\")\" = Yes ] && sudo hibernate") },
	{ MODKEY,			XK_l,		setmfact,      	{.f = +0.05} },
	{ MODKEY,			XK_semicolon,	shiftview,	{ .i = +1 } },
	{ MODKEY,			XK_apostrophe,	zoom,		{0} },
	{ MODKEY,			XK_Return,	spawn,		{.v = termcmd } },
	{ MODKEY|ShiftMask,		XK_Return,	togglescratch,	{.v = scratchpadcmd } },

	{ MODKEY,			XK_z,		incrgaps,	{.i = +1 } },
	{ MODKEY|ShiftMask,		XK_z,		incrgaps,	{.i = -1 } },
	{ MODKEY,			XK_x,		spawn,		SHCMD("slock & xset dpms force off; ") },
	{ MODKEY|ShiftMask,		XK_x,		spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Shutdown computer?\")\" = Yes ] && shutdown now") },
	{ MODKEY,			XK_c,		spawn,		SHCMD("mpv --no-cache --no-osc --no-input-default-bindings --input-conf=/dev/null --title=\"webcam live\"  $(ls /dev/video[0,2,4,6,8] | tail -n 1)") }, 
	{ MODKEY|ShiftMask,		XK_c,		spawn,		SHCMD("pkill -f \"webcam live\"") }, 
	{ MODKEY,			XK_v,		spawn,		SHCMD("$TERMINAL -e $EDITOR") },
	{ MODKEY|ShiftMask,		XK_v,		spawn,		SHCMD("feh --bg-scale --randomize -r $WALLPAPER_PATH") },
//	{ MODKEY,       		XK_r,		spawn,		SHCMD("ffmpeg -f video4linux2 -input_format yuyv422 -video_size 1280x720 -i /dev/video0 -f alsa -i default \"/mnt/webcam_videos/$(date).mp4\"") },
	{ MODKEY,       		XK_r,		spawn,		SHCMD("/usr/local/share/dwm/./dmenurecord") },
//	{ MODKEY|ShiftMask,		XK_r,		spawn,  	SHCMD("ffmpeg -y -framerate 30 -f x11grab -video_size 1920x1080 -i :0.0 -f pulse -i default \"/mnt/screen_videos/$(date).mp4\"") },
	{ MODKEY|ShiftMask,		XK_r,		spawn,  	SHCMD("/usr/local/share/dwm/dmenurecord kill") },
	{ MODKEY,			XK_b,		togglebar,	{0} },
	{ MODKEY|ShiftMask,		XK_b,		spawn,		SHCMD("groff -mom $THESIS_PATH -Tpdf | zathura -") },
	{ MODKEY,			XK_n,		spawn,		SHCMD("nmtui") },
	{ MODKEY|ShiftMask,		XK_n,		spawn,		SHCMD("$TERMINAL -e \"echo 'LAST' && (last -a | grep -i 'still logged in' ) && echo 'WHO' && who && echo 'W' && w && echo 'NETSTAT' &&  netstat -tnpa | grep '*ssh'\"") },
	{ MODKEY,			XK_m,		spawn,		SHCMD("$TERMINAL -e $FILEMGR") },
//	{ MODKEY,			XK_comma,	spawn,		SHCMD("") },
//	{ MODKEY,			XK_period,	spawn,		SHCMD("") },
//	{ MODKEY,			XK_forwardslash,spawn,		SHCMD("") },
	{ MODKEY,			XK_Page_Up,	shiftview,	{ .i = -1 } },
	{ MODKEY,			XK_Page_Down,	shiftview,	{ .i = 1 } },
//	{ MODKEY,			XK_Insert,	spawn,		SHCMD("notify-send \"📋 Clipboard contents:\" \"$(xclip -o -selection clipboard)\"") },
//	{ MODKEY,			XK_F1,		spawn,		SHCMD("") },
// 	{ MODKEY,			XK_F2,		spawn,		SHCMD("") }, 
//	{ MODKEY,			XK_F3,		spawn,		SHCMD("displayselect") },
//	{ MODKEY,			XK_F5,		xrdb,		{.v = NULL } },
//	{ MODKEY,			XK_F6,		spawn,		SHCMD("torwrap") },
//	{ MODKEY,			XK_F7,		spawn,		SHCMD("td-toggle") },
//	{ MODKEY,			XK_F8,		spawn,		SHCMD("mailsync") },
//	{ MODKEY,			XK_F9,		spawn,		SHCMD("dmenumount") },
//	{ MODKEY,			XK_F10,		spawn,		SHCMD("dmenuumount") },
//	{ MODKEY,			XK_F11,		spawn,		SHCMD("") },
	{ MODKEY|ControlMask|ShiftMask,	XK_F12,		quit,		{0} },
	{ MODKEY,                       XK_space,     	setlayout,      {0} }, 
	{ MODKEY|ShiftMask,		XK_space,	togglefloating,	{0} },

	{ 0,				XK_Print,	spawn,		SHCMD("maim $SCREENSHOT_DESKTOP_PATH/$(date '+%Y.%m.%d-%H%M-%S').png") },
	{ ShiftMask,			XK_Print,	spawn,		SHCMD("maim -i $(xdotool getactivewindow) $SCREENSHOT_ACTIVEWINDOW_PATH/$(date '+%Y.%m.%d-%H%M-%S').png") },
//	{ MODKEY,			XK_Print,	spawn,		SHCMD("") },
//	{ MODKEY|ShiftMask,		XK_Print,	spawn,		SHCMD("") },
//	{ MODKEY,			XK_Delete,	spawn,		SHCMD("") },
//	{ MODKEY,			XK_Scroll_Lock,	spawn,		SHCMD("killall screenkey || screenkey &") },//screencast your keystrokes
	{ 0, XF86XK_AudioMute,		spawn,		SHCMD("pactl set-sink-volume 0 0") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pactl set-sink-volume 0 +10%") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pactl set-sink-volume 0 -10%") },
//	{ 0, XF86XK_AudioPrev,		spawn,		SHCMD("mpc prev") },
//	{ 0, XF86XK_AudioNext,		spawn,		SHCMD("mpc next") },
//	{ 0, XF86XK_AudioPause,		spawn,		SHCMD("mpc pause") },
//	{ 0, XF86XK_AudioPlay,		spawn,		SHCMD("mpc play") },
//	{ 0, XF86XK_AudioStop,		spawn,		SHCMD("mpc stop") },
//	{ 0, XF86XK_AudioRewind,	spawn,		SHCMD("mpc seek -10") },
//	{ 0, XF86XK_AudioForward,	spawn,		SHCMD("mpc seek +10") },
//	{ 0, XF86XK_AudioMedia,		spawn,		SHCMD("$TERMINAL -e ncmpcpp") },
	{ 0, XF86XK_PowerOff,		spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Shutdown computer?\")\" = Yes ] && shutdown now") },
	{ 0, XF86XK_Calculator,		spawn,		SHCMD("$TERMINAL -e $CALCULATOR -l") },
	{ 0, XF86XK_Sleep,		spawn,		SHCMD("[ \"$(printf \"No\\nYes\" | dmenu -i -nb darkred -sb red -sf white -nf gray -p \"Hibernate computer?\")\" = Yes ] && sudo hibernate") },
	{ 0, XF86XK_WWW,		spawn,		SHCMD("$BROWSER") },
	{ 0, XF86XK_DOS,		spawn,		SHCMD("$TERMINAL") },
	{ 0, XF86XK_ScreenSaver,	spawn,		SHCMD("slock & xset dpms force off;") },
	{ 0, XF86XK_TaskPane,		spawn,		SHCMD("$TERMINAL -e htop") },
	{ 0, XF86XK_Mail,		spawn,		SHCMD("$TERMINAL -e $MAILCLIENT") },
	{ 0, XF86XK_MyComputer,		spawn,		SHCMD("$TERMINAL -e $FILEMGR /") },
	/* { 0, XF86XK_Battery,		spawn,		SHCMD("") }, */
	{ 0, XF86XK_Launch1,		spawn,		SHCMD("xset dpms force off") },
//	{ 0, XF86XK_TouchpadToggle,	spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
//	{ 0, XF86XK_TouchpadOff,	spawn,		SHCMD("synclient TouchpadOff=1") },
//	{ 0, XF86XK_TouchpadOn,		spawn,		SHCMD("synclient TouchpadOff=0") },
//	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 15") },
//	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 15") },
	//Original bindings	
	/* { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } }, */
	/* { MODKEY,                       XK_period, focusmon,       {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } }, */
	/* { MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } }, */
	/* { MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} }, */
	/* { MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } }, */
	/* { MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } }, */
	/* { MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } }, */
	/* { MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } }, */
	/* { MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } }, */
	/* { MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } }, */

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          SHCMD("$TERMINAL -e ./statusbarinfo") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     	focusstack },
	{ "setmfact",       	setmfact },
	{ "togglebar",      	togglebar },
	{ "incnmaster",     	incnmaster },
	{ "togglefloating", 	togglefloating },
	{ "focusmon",       	focusmon },
	{ "tagmon",         	tagmon },
	{ "zoom",           	zoom },
	{ "view",           	view },
	{ "viewall",        	viewall },
	{ "viewex",         	viewex },
	{ "toggleview",     	view },
	{ "toggleviewex",   	toggleviewex },
	{ "tag",            	tag },
	{ "tagall",         	tagall },
	{ "tagex",          	tagex },
	{ "toggletag",      	tag },
	{ "toggletagex",    	toggletagex },
	{ "killclient",     	killclient },
	{ "quit",           	quit },
	{ "setlayout",    	  setlayout },
	{ "setlayoutex",    	setlayoutex },
	{ "xrdb",		xrdb },
};

