static char normfgcolor[] = "#bbbbbb";//"{color15}";
static char normbgcolor[] = "#222222";//"{color0}";
static char normbordercolor[] = "#444444"; //"{color8}";

static char selfgcolor[] = "#eeeeee";//"{color15}";
static char selbgcolor[] = "#005577";//"{color2}";
static char selbordercolor[] = "#005577";//"{color15}";

static char urgfgcolor[] = "#ff0000";//"{color15}";
static char urgbgcolor[] = "#ff0000";//"{color1}";
static char urgbordercolor[] = "#ff0000";//"{color1}";

static char *colors[][4]      = {{
    /*               fg           bg         border                         */
    [SchemeNorm] = {{ normfgcolor,     normbgcolor,   normbordercolor }}, // unfocused wins
    [SchemeSel]  = {{ selfgcolor,      selbgcolor,    selbordercolor }},  // the focused win
    [SchemeUrg] =  {{ urgfgcolor,      urgbgcolor,    urgbordercolor }},
}};
