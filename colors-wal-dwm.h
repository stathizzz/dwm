static char normfgcolor[] = "#bbbbbb";//"{color15}";
static char normbgcolor[] = "#222222";//"{color0}";
static char normbordercolor[] = "#444444"; //"{color8}";

static char selfgcolor[] = "#eeeeee";//"{color15}";
static char selbgcolor[] = "#005577";//"{color2}";
static char selbordercolor[] = "#005577";//"{color15}";

static char urg_fg[] = "#ff0000";//"{color15}";
static char urg_bg[] = "#ff0000";//"{color1}";
static char urg_border[] = "#ff0000";//"{color1}";

static char *colors[][3]      = {{
    /*               fg           bg         border                         */
    [SchemeNorm] = {{ normfgcolor,     normbgcolor,   normbordercolor }}, // unfocused wins
    [SchemeSel]  = {{ selfgcolor,      selbgcolor,    selbordercolor }},  // the focused win
//    [SchemeUrg] =  {{ urg_fg,      urg_bg,    urg_border }},
}};
