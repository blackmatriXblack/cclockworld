#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ID_LISTBOX    1001
#define ID_TIMER      1002
#define ID_STATUSBAR  1003

typedef struct {
    const char *name;
    const char *capital;
    int utc_offset_min;
    int observes_dst;
    const char *tz_abbr;
} Country;

static Country countries[] = {
    {"Baker Island (US)", "_", -720, 0, "AoE"},
    {"Howland Island (US)", "_", -720, 0, "AoE"},
    {"American Samoa (US)", "Pago Pago", -660, 0, "SST"},
    {"Niue (NZ)", "Alofi", -660, 0, "NUT"},
    {"Cook Islands (NZ)", "Avarua", -600, 0, "CKT"},
    {"French Polynesia (FR)", "Papeete", -600, 0, "TAHT"},
    {"United States (Hawaii)", "Honolulu", -600, 0, "HAST"},
    {"Johnston Atoll (US)", "_", -600, 0, "HAST"},
    {"French Polynesia - Marquesas (FR)", "Taiohae", -570, 0, "MART"},
    {"United States (Alaska)", "Juneau", -540, 1, "AKST/AKDT"},
    {"Gambier Islands (FR)", "Rikitea", -540, 0, "GAMT"},
    {"Canada (Pacific)", "Vancouver", -480, 1, "PST/PDT"},
    {"Mexico (Northwest)", "Tijuana", -480, 1, "PST/PDT"},
    {"United States (Pacific)", "Los Angeles", -480, 1, "PST/PDT"},
    {"Pitcairn Islands (UK)", "Adamstown", -480, 0, "PST"},
    {"Canada (Mountain)", "Calgary", -420, 1, "MST/MDT"},
    {"Mexico (Pacific)", "Chihuahua", -420, 1, "MST/MDT"},
    {"United States (Mountain)", "Denver", -420, 1, "MST/MDT"},
    {"Belize", "Belmopan", -360, 0, "CST"},
    {"Canada (Central)", "Winnipeg", -360, 1, "CST/CDT"},
    {"Costa Rica", "San Jose", -360, 0, "CST"},
    {"Ecuador (Galapagos)", "Pto Baquerizo M.", -360, 0, "GALT"},
    {"El Salvador", "San Salvador", -360, 0, "CST"},
    {"Guatemala", "Guatemala City", -360, 0, "CST"},
    {"Honduras", "Tegucigalpa", -360, 0, "CST"},
    {"Mexico (Central)", "Mexico City", -360, 1, "CST/CDT"},
    {"Nicaragua", "Managua", -360, 0, "CST"},
    {"United States (Central)", "Chicago", -360, 1, "CST/CDT"},
    {"Bahamas", "Nassau", -300, 1, "EST/EDT"},
    {"Brazil (Acre)", "Rio Branco", -300, 0, "ACT"},
    {"Canada (Eastern)", "Toronto", -300, 1, "EST/EDT"},
    {"Cayman Islands (UK)", "George Town", -300, 0, "EST"},
    {"Colombia", "Bogota", -300, 0, "COT"},
    {"Cuba", "Havana", -300, 1, "CST/CDT"},
    {"Ecuador", "Quito", -300, 0, "ECT"},
    {"Haiti", "Port-au-Prince", -300, 1, "EST/EDT"},
    {"Jamaica", "Kingston", -300, 0, "EST"},
    {"Mexico (Southeast)", "Cancun", -300, 0, "EST"},
    {"Panama", "Panama City", -300, 0, "EST"},
    {"Peru", "Lima", -300, 0, "PET"},
    {"United States (Eastern)", "New York", -300, 1, "EST/EDT"},
    {"Anguilla (UK)", "The Valley", -240, 0, "AST"},
    {"Antigua and Barbuda", "St. John's", -240, 0, "AST"},
    {"Aruba (NL)", "Oranjestad", -240, 0, "AST"},
    {"Barbados", "Bridgetown", -240, 0, "AST"},
    {"Bermuda (UK)", "Hamilton", -240, 1, "AST/ADT"},
    {"Bolivia", "La Paz", -240, 0, "BOT"},
    {"Brazil (Amazon)", "Manaus", -240, 0, "AMT"},
    {"British Virgin Is. (UK)", "Road Town", -240, 0, "AST"},
    {"Canada (Atlantic)", "Halifax", -240, 1, "AST/ADT"},
    {"Chile (Continental)", "Santiago", -240, 1, "CLT/CLST"},
    {"Curacao (NL)", "Willemstad", -240, 0, "AST"},
    {"Dominica", "Roseau", -240, 0, "AST"},
    {"Dominican Republic", "Santo Domingo", -240, 0, "AST"},
    {"Grenada", "St. George's", -240, 0, "AST"},
    {"Guadeloupe (FR)", "Basse-Terre", -240, 0, "AST"},
    {"Guyana", "Georgetown", -240, 0, "GYT"},
    {"Martinique (FR)", "Fort-de-France", -240, 0, "AST"},
    {"Montserrat (UK)", "Plymouth", -240, 0, "AST"},
    {"Paraguay", "Asuncion", -240, 1, "PYT/PYST"},
    {"Puerto Rico (US)", "San Juan", -240, 0, "AST"},
    {"St. Kitts and Nevis", "Basseterre", -240, 0, "AST"},
    {"Saint Lucia", "Castries", -240, 0, "AST"},
    {"St. Vincent & Grenadines", "Kingstown", -240, 0, "AST"},
    {"Sint Maarten (NL)", "Philipsburg", -240, 0, "AST"},
    {"Trinidad and Tobago", "Port of Spain", -240, 0, "AST"},
    {"Turks and Caicos (UK)", "Cockburn Town", -240, 1, "EST/EDT"},
    {"US Virgin Islands", "Charlotte Amalie", -240, 0, "AST"},
    {"Venezuela", "Caracas", -240, 0, "VET"},
    {"Canada (Newfoundland)", "St. John's", -210, 1, "NST/NDT"},
    {"Argentina", "Buenos Aires", -180, 0, "ART"},
    {"Brazil (Brasilia)", "Brasilia", -180, 0, "BRT"},
    {"Chile (Magallanes)", "Punta Arenas", -180, 1, "CLT/CLST"},
    {"Falkland Islands (UK)", "Stanley", -180, 0, "FKST"},
    {"French Guiana (FR)", "Cayenne", -180, 0, "GFT"},
    {"Greenland (DK)", "Nuuk", -180, 1, "WGT/WGST"},
    {"St. Pierre & Miquelon (FR)", "St-Pierre", -180, 1, "PMST/PMDT"},
    {"Suriname", "Paramaribo", -180, 0, "SRT"},
    {"Uruguay", "Montevideo", -180, 0, "UYT"},
    {"Brazil (Fernando de Noronha)", "F. de Noronha", -120, 0, "FNT"},
    {"South Georgia (UK)", "King Edward Pt", -120, 0, "GST"},
    {"Azores (PT)", "Ponta Delgada", -60, 1, "AZOT/AZOST"},
    {"Cabo Verde", "Praia", -60, 0, "CVT"},
    {"Burkina Faso", "Ouagadougou", 0, 0, "GMT"},
    {"Cote d'Ivoire", "Yamoussoukro", 0, 0, "GMT"},
    {"Faroe Islands (DK)", "Torshavn", 0, 1, "WET/WEST"},
    {"Gambia", "Banjul", 0, 0, "GMT"},
    {"Ghana", "Accra", 0, 0, "GMT"},
    {"Greenwich Mean Time", "Greenwich", 0, 0, "GMT"},
    {"Guinea", "Conakry", 0, 0, "GMT"},
    {"Guinea-Bissau", "Bissau", 0, 0, "GMT"},
    {"Iceland", "Reykjavik", 0, 0, "GMT"},
    {"Ireland", "Dublin", 0, 1, "GMT/IST"},
    {"Liberia", "Monrovia", 0, 0, "GMT"},
    {"Mali", "Bamako", 0, 0, "GMT"},
    {"Mauritania", "Nouakchott", 0, 0, "GMT"},
    {"Portugal", "Lisbon", 0, 1, "WET/WEST"},
    {"Saint Helena (UK)", "Jamestown", 0, 0, "GMT"},
    {"Sao Tome and Principe", "Sao Tome", 0, 0, "GMT"},
    {"Senegal", "Dakar", 0, 0, "GMT"},
    {"Sierra Leone", "Freetown", 0, 0, "GMT"},
    {"Togo", "Lome", 0, 0, "GMT"},
    {"United Kingdom", "London", 0, 1, "GMT/BST"},
    {"Albania", "Tirana", 60, 1, "CET/CEST"},
    {"Algeria", "Algiers", 60, 0, "CET"},
    {"Andorra", "Andorra la Vella", 60, 1, "CET/CEST"},
    {"Angola", "Luanda", 60, 0, "WAT"},
    {"Austria", "Vienna", 60, 1, "CET/CEST"},
    {"Belgium", "Brussels", 60, 1, "CET/CEST"},
    {"Benin", "Porto-Novo", 60, 0, "WAT"},
    {"Bosnia and Herzegovina", "Sarajevo", 60, 1, "CET/CEST"},
    {"Cameroon", "Yaounde", 60, 0, "WAT"},
    {"Central African Rep.", "Bangui", 60, 0, "WAT"},
    {"Chad", "N'Djamena", 60, 0, "WAT"},
    {"Congo (Republic)", "Brazzaville", 60, 0, "WAT"},
    {"Croatia", "Zagreb", 60, 1, "CET/CEST"},
    {"Czech Republic", "Prague", 60, 1, "CET/CEST"},
    {"Denmark", "Copenhagen", 60, 1, "CET/CEST"},
    {"Equatorial Guinea", "Malabo", 60, 0, "WAT"},
    {"France", "Paris", 60, 1, "CET/CEST"},
    {"Gabon", "Libreville", 60, 0, "WAT"},
    {"Germany", "Berlin", 60, 1, "CET/CEST"},
    {"Gibraltar (UK)", "Gibraltar", 60, 1, "CET/CEST"},
    {"Hungary", "Budapest", 60, 1, "CET/CEST"},
    {"Italy", "Rome", 60, 1, "CET/CEST"},
    {"Kosovo", "Pristina", 60, 1, "CET/CEST"},
    {"Liechtenstein", "Vaduz", 60, 1, "CET/CEST"},
    {"Luxembourg", "Luxembourg", 60, 1, "CET/CEST"},
    {"Malta", "Valletta", 60, 1, "CET/CEST"},
    {"Monaco", "Monaco", 60, 1, "CET/CEST"},
    {"Montenegro", "Podgorica", 60, 1, "CET/CEST"},
    {"Morocco", "Rabat", 60, 1, "WET/WEST"},
    {"Namibia", "Windhoek", 60, 0, "CAT"},
    {"Netherlands", "Amsterdam", 60, 1, "CET/CEST"},
    {"Niger", "Niamey", 60, 0, "WAT"},
    {"Nigeria", "Abuja", 60, 0, "WAT"},
    {"North Macedonia", "Skopje", 60, 1, "CET/CEST"},
    {"Norway", "Oslo", 60, 1, "CET/CEST"},
    {"Poland", "Warsaw", 60, 1, "CET/CEST"},
    {"San Marino", "San Marino", 60, 1, "CET/CEST"},
    {"Serbia", "Belgrade", 60, 1, "CET/CEST"},
    {"Slovakia", "Bratislava", 60, 1, "CET/CEST"},
    {"Slovenia", "Ljubljana", 60, 1, "CET/CEST"},
    {"Spain", "Madrid", 60, 1, "CET/CEST"},
    {"Sweden", "Stockholm", 60, 1, "CET/CEST"},
    {"Switzerland", "Bern", 60, 1, "CET/CEST"},
    {"Tunisia", "Tunis", 60, 0, "CET"},
    {"Vatican City", "Vatican City", 60, 1, "CET/CEST"},
    {"Western Sahara", "El Aaiun", 60, 1, "WET/WEST"},
    {"Botswana", "Gaborone", 120, 0, "CAT"},
    {"Bulgaria", "Sofia", 120, 1, "EET/EEST"},
    {"Burundi", "Bujumbura", 120, 0, "CAT"},
    {"Cyprus", "Nicosia", 120, 1, "EET/EEST"},
    {"Congo (DRC) - West", "Kinshasa", 120, 0, "WAT"},
    {"Egypt", "Cairo", 120, 1, "EET/EEST"},
    {"Estonia", "Tallinn", 120, 1, "EET/EEST"},
    {"Eswatini", "Mbabane", 120, 0, "SAST"},
    {"Finland", "Helsinki", 120, 1, "EET/EEST"},
    {"Greece", "Athens", 120, 1, "EET/EEST"},
    {"Israel", "Jerusalem", 120, 1, "IST/IDT"},
    {"Jordan", "Amman", 120, 1, "EET/EEST"},
    {"Latvia", "Riga", 120, 1, "EET/EEST"},
    {"Lebanon", "Beirut", 120, 1, "EET/EEST"},
    {"Lesotho", "Maseru", 120, 0, "SAST"},
    {"Libya", "Tripoli", 120, 0, "EET"},
    {"Lithuania", "Vilnius", 120, 1, "EET/EEST"},
    {"Malawi", "Lilongwe", 120, 0, "CAT"},
    {"Moldova", "Chisinau", 120, 1, "EET/EEST"},
    {"Mozambique", "Maputo", 120, 0, "CAT"},
    {"Palestine", "Ramallah", 120, 1, "EET/EEST"},
    {"Romania", "Bucharest", 120, 1, "EET/EEST"},
    {"Russia (Kaliningrad)", "Kaliningrad", 120, 0, "EET"},
    {"Rwanda", "Kigali", 120, 0, "CAT"},
    {"South Africa", "Pretoria", 120, 0, "SAST"},
    {"South Sudan", "Juba", 120, 0, "CAT"},
    {"Sudan", "Khartoum", 120, 0, "CAT"},
    {"Syria", "Damascus", 120, 1, "EET/EEST"},
    {"Ukraine", "Kyiv", 120, 1, "EET/EEST"},
    {"Zambia", "Lusaka", 120, 0, "CAT"},
    {"Zimbabwe", "Harare", 120, 0, "CAT"},
    {"Bahrain", "Manama", 180, 0, "AST"},
    {"Belarus", "Minsk", 180, 0, "MSK"},
    {"Comoros", "Moroni", 180, 0, "EAT"},
    {"Djibouti", "Djibouti City", 180, 0, "EAT"},
    {"Eritrea", "Asmara", 180, 0, "EAT"},
    {"Ethiopia", "Addis Ababa", 180, 0, "EAT"},
    {"Iraq", "Baghdad", 180, 0, "AST"},
    {"Kenya", "Nairobi", 180, 0, "EAT"},
    {"Kuwait", "Kuwait City", 180, 0, "AST"},
    {"Madagascar", "Antananarivo", 180, 0, "EAT"},
    {"Mayotte (FR)", "Mamoudzou", 180, 0, "EAT"},
    {"Qatar", "Doha", 180, 0, "AST"},
    {"Russia (Moscow)", "Moscow", 180, 0, "MSK"},
    {"Saudi Arabia", "Riyadh", 180, 0, "AST"},
    {"Somalia", "Mogadishu", 180, 0, "EAT"},
    {"Tanzania", "Dodoma", 180, 0, "EAT"},
    {"Turkiye", "Ankara", 180, 0, "TRT"},
    {"Uganda", "Kampala", 180, 0, "EAT"},
    {"Yemen", "Sana'a", 180, 0, "AST"},
    {"Iran", "Tehran", 210, 1, "IRST/IRDT"},
    {"Armenia", "Yerevan", 240, 0, "AMT"},
    {"Azerbaijan", "Baku", 240, 0, "AZT"},
    {"Georgia", "Tbilisi", 240, 0, "GET"},
    {"Mauritius", "Port Louis", 240, 0, "MUT"},
    {"Oman", "Muscat", 240, 0, "GST"},
    {"Reunion (FR)", "Saint-Denis", 240, 0, "RET"},
    {"Russia (Samara)", "Samara", 240, 0, "SAMT"},
    {"Seychelles", "Victoria", 240, 0, "SCT"},
    {"United Arab Emirates", "Abu Dhabi", 240, 0, "GST"},
    {"Afghanistan", "Kabul", 270, 0, "AFT"},
    {"Kazakhstan (West)", "Aktobe", 300, 0, "AQTT"},
    {"Maldives", "Male", 300, 0, "MVT"},
    {"Pakistan", "Islamabad", 300, 0, "PKT"},
    {"Russia (Yekaterinburg)", "Yekaterinburg", 300, 0, "YEKT"},
    {"Tajikistan", "Dushanbe", 300, 0, "TJT"},
    {"Turkmenistan", "Ashgabat", 300, 0, "TMT"},
    {"Uzbekistan", "Tashkent", 300, 0, "UZT"},
    {"India", "New Delhi", 330, 0, "IST"},
    {"Sri Lanka", "Colombo", 330, 0, "SLST"},
    {"Nepal", "Kathmandu", 345, 0, "NPT"},
    {"Bangladesh", "Dhaka", 360, 0, "BST"},
    {"Bhutan", "Thimphu", 360, 0, "BTT"},
    {"British Indian Ocean (UK)", "Diego Garcia", 360, 0, "IOT"},
    {"Kazakhstan (East)", "Almaty", 360, 0, "ALMT"},
    {"Kyrgyzstan", "Bishkek", 360, 0, "KGT"},
    {"Russia (Omsk)", "Omsk", 360, 0, "OMST"},
    {"Cocos Islands (AU)", "West Island", 390, 0, "CCT"},
    {"Myanmar", "Naypyidaw", 390, 0, "MMT"},
    {"Cambodia", "Phnom Penh", 420, 0, "ICT"},
    {"Christmas Island (AU)", "Flying Fish Cove", 420, 0, "CXT"},
    {"Indonesia (West)", "Jakarta", 420, 0, "WIB"},
    {"Laos", "Vientiane", 420, 0, "ICT"},
    {"Mongolia (West)", "Hovd", 420, 0, "HOVT"},
    {"Russia (Krasnoyarsk)", "Krasnoyarsk", 420, 0, "KRAT"},
    {"Thailand", "Bangkok", 420, 0, "ICT"},
    {"Vietnam", "Hanoi", 420, 0, "ICT"},
    {"Australia (Western)", "Perth", 480, 0, "AWST"},
    {"Brunei", "Bandar Seri Begawan", 480, 0, "BNT"},
    {"China", "Beijing", 480, 0, "CST"},
    {"Hong Kong (CN)", "Hong Kong", 480, 0, "HKT"},
    {"Indonesia (Central)", "Makassar", 480, 0, "WITA"},
    {"Macau (CN)", "Macau", 480, 0, "CST"},
    {"Malaysia", "Kuala Lumpur", 480, 0, "MYT"},
    {"Mongolia (East)", "Ulaanbaatar", 480, 0, "ULAT"},
    {"Philippines", "Manila", 480, 0, "PHT"},
    {"Russia (Irkutsk)", "Irkutsk", 480, 0, "IRKT"},
    {"Singapore", "Singapore", 480, 0, "SGT"},
    {"Taiwan", "Taipei", 480, 0, "CST"},
    {"Australia (Eucla)", "Eucla", 525, 0, "ACWST"},
    {"East Timor", "Dili", 540, 0, "TLT"},
    {"Indonesia (East)", "Jayapura", 540, 0, "WIT"},
    {"Japan", "Tokyo", 540, 0, "JST"},
    {"North Korea", "Pyongyang", 540, 0, "KST"},
    {"Palau", "Ngerulmud", 540, 0, "PWT"},
    {"South Korea", "Seoul", 540, 0, "KST"},
    {"Russia (Yakutsk)", "Yakutsk", 540, 0, "YAKT"},
    {"Australia (Central)", "Adelaide", 570, 1, "ACST/ACDT"},
    {"Australia (Eastern)", "Sydney", 600, 1, "AEST/AEDT"},
    {"Australia (Queensland)", "Brisbane", 600, 0, "AEST"},
    {"Guam (US)", "Hagatna", 600, 0, "ChST"},
    {"Micronesia (Chuuk)", "Weno", 600, 0, "CHUT"},
    {"Northern Mariana Is. (US)", "Saipan", 600, 0, "ChST"},
    {"Papua New Guinea", "Port Moresby", 600, 0, "PGT"},
    {"Russia (Vladivostok)", "Vladivostok", 600, 0, "VLAT"},
    {"Australia (Lord Howe)", "Lord Howe Is.", 630, 1, "LHST/LHDT"},
    {"Micronesia (Kosrae)", "Tofol", 660, 0, "KOST"},
    {"New Caledonia (FR)", "Noumea", 660, 0, "NCT"},
    {"Norfolk Island (AU)", "Kingston", 660, 1, "NFT/NFDT"},
    {"Russia (Magadan)", "Magadan", 660, 0, "MAGT"},
    {"Solomon Islands", "Honiara", 660, 0, "SBT"},
    {"Vanuatu", "Port Vila", 660, 0, "VUT"},
    {"Fiji", "Suva", 720, 1, "FJT/FJST"},
    {"Kiribati (Gilbert)", "Tarawa", 720, 0, "GILT"},
    {"Marshall Islands", "Majuro", 720, 0, "MHT"},
    {"Nauru", "Yaren", 720, 0, "NRT"},
    {"New Zealand", "Wellington", 720, 1, "NZST/NZDT"},
    {"Russia (Kamchatka)", "Petropavlovsk", 720, 0, "PETT"},
    {"Tuvalu", "Funafuti", 720, 0, "TVT"},
    {"Wake Island (US)", "_", 720, 0, "WAKT"},
    {"Wallis and Futuna (FR)", "Mata-Utu", 720, 0, "WFT"},
    {"Chatham Islands (NZ)", "Waitangi", 765, 1, "CHAST/CHADT"},
    {"Kiribati (Phoenix)", "Kanton", 780, 0, "PHOT"},
    {"Samoa", "Apia", 780, 0, "WST"},
    {"Tonga", "Nuku'alofa", 780, 0, "TOT"},
    {"Tokelau (NZ)", "Fakaofo", 780, 0, "TKT"},
    {"Kiribati (Line Islands)", "Kiritimati", 840, 0, "LINT"},
};

#define NUM_COUNTRIES (sizeof(countries) / sizeof(countries[0]))

static const char *day_names[] = {
    "Sunday", "Monday", "Tuesday", "Wednesday",
    "Thursday", "Friday", "Saturday"
};

static const char *month_names[] = {
    "", "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

typedef struct {
    HWND hwndMain;
    HWND hwndListBox;
    HWND hwndClockPanel;
    HWND hwndDetailPanel;
    HWND hwndStatusBar;
    HWND hwndTooltip;
    int selectedIndex;
    int clockMode; /* 0=selected country, 1=UTC, 2=local */
    int showSeconds;
    int darkMode;
    HFONT hFontClock;
    HFONT hFontDetail;
    HFONT hFontSmall;
    HFONT hFontTitle;
    HBRUSH hBrushBg;
    HBRUSH hBrushClockBg;
    HBRUSH hBrushPanelBg;
    HPEN hPenHour;
    HPEN hPenMinute;
    HPEN hPenSecond;
    HPEN hPenTick;
    HPEN hPenTickSub;
    HPEN hPenBorder;
    COLORREF clrClockBg;
    COLORREF clrPanelBg;
    COLORREF clrText;
} AppState;

static AppState g_app;

static int is_dst_active(int utc_offset_min, int observes_dst) {
    if (!observes_dst) return 0;
    time_t now = time(NULL);
    struct tm *gmt = gmtime(&now);
    int month = gmt->tm_mon + 1;
    (void)utc_offset_min;
    return (month >= 3 && month <= 10);
}

static void compute_local_time_for_index(int index,
    int *out_hour, int *out_min, int *out_sec,
    int *out_day, int *out_month, int *out_year,
    int *out_wday) {
    time_t now = time(NULL);
    int offset = countries[index].utc_offset_min;
    if (is_dst_active(countries[index].utc_offset_min, countries[index].observes_dst))
        offset += 60;
    time_t local_time = now + offset * 60;
    struct tm *lt = gmtime(&local_time);
    *out_hour = lt->tm_hour;
    *out_min = lt->tm_min;
    *out_sec = lt->tm_sec;
    *out_day = lt->tm_mday;
    *out_month = lt->tm_mon + 1;
    *out_year = lt->tm_year + 1900;
    *out_wday = lt->tm_wday;
}

static void draw_clock_face(HDC hdc, RECT rect, int hour, int minute, int second) {
    int w = rect.right - rect.left;
    int h = rect.bottom - rect.top;
    int cx = rect.left + w / 2;
    int cy = rect.top + h / 2;
    int r = (w < h ? w : h) / 2 - 20;
    if (r < 40) r = 40;

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP memBmp = CreateCompatibleBitmap(hdc, w, h);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, memBmp);

    RECT bgRect = {0, 0, w, h};
    FillRect(memDC, &bgRect, g_app.hBrushPanelBg);

    /* outer rim */
    HPEN rimPen = CreatePen(PS_SOLID, 4, RGB(60, 60, 70));
    HBRUSH rimBr = CreateSolidBrush(RGB(240, 240, 245));
    SelectObject(memDC, rimPen);
    SelectObject(memDC, rimBr);
    Ellipse(memDC, cx - r - 6, cy - r - 6, cx + r + 6, cy + r + 6);

    /* clock face */
    HBRUSH faceBr = CreateSolidBrush(g_app.clrClockBg);
    HPEN facePen = CreatePen(PS_SOLID, 2, RGB(80, 80, 90));
    SelectObject(memDC, facePen);
    SelectObject(memDC, faceBr);
    Ellipse(memDC, cx - r, cy - r, cx + r, cy + r);

    DeleteObject(rimPen);
    DeleteObject(rimBr);

    /* day/night arc */
    int night_start = 0, night_end = 0;
    if (hour >= 18 || hour < 6) {
        night_start = 0; night_end = 6 * 30;
    } else {
        night_start = 18 * 30; night_end = 360;
    }
    if (night_start != night_end) {
        COLORREF nightClr = RGB(30, 30, 60);
        HBRUSH nightBr = CreateSolidBrush(nightClr);
        SelectObject(memDC, nightBr);
        HPEN nightPen = CreatePen(PS_SOLID, 1, nightClr);
        SelectObject(memDC, nightPen);
        double a1 = (night_start - 90) * 3.14159 / 180.0;
        double a2 = (night_end - 90) * 3.14159 / 180.0;
        Pie(memDC, cx - r, cy - r, cx + r, cy + r,
            (int)(cx + r * cos(a1)), (int)(cy + r * sin(a1)),
            (int)(cx + r * cos(a2)), (int)(cy + r * sin(a2)));
        DeleteObject(nightBr);
        DeleteObject(nightPen);
    }

    /* border */
    SelectObject(memDC, CreatePen(PS_SOLID, 2, RGB(100, 100, 110)));
    SelectObject(memDC, GetStockObject(NULL_BRUSH));
    Ellipse(memDC, cx - r, cy - r, cx + r, cy + r);

    /* tick marks */
    for (int i = 0; i < 60; i++) {
        double angle = (i * 6 - 90) * 3.14159 / 180.0;
        double cos_a = cos(angle);
        double sin_a = sin(angle);
        if (i % 5 == 0) {
            int x1 = (int)(cx + (r - 16) * cos_a);
            int y1 = (int)(cy + (r - 16) * sin_a);
            int x2 = (int)(cx + (r - 2) * cos_a);
            int y2 = (int)(cy + (r - 2) * sin_a);
            SelectObject(memDC, g_app.hPenTick);
            MoveToEx(memDC, x1, y1, NULL);
            LineTo(memDC, x2, y2);
        } else if (i % 1 == 0) {
            int x1 = (int)(cx + (r - 10) * cos_a);
            int y1 = (int)(cy + (r - 10) * sin_a);
            int x2 = (int)(cx + (r - 4) * cos_a);
            int y2 = (int)(cy + (r - 4) * sin_a);
            SelectObject(memDC, g_app.hPenTickSub);
            MoveToEx(memDC, x1, y1, NULL);
            LineTo(memDC, x2, y2);
        }

        /* hour numbers */
        if (i % 5 == 0) {
            int hnum = i / 5;
            if (hnum == 0) hnum = 12;
            char buf[4];
            sprintf(buf, "%d", hnum);
            int tx = (int)(cx + (r - 34) * cos_a) - 8;
            int ty = (int)(cy + (r - 34) * sin_a) - 8;
            SetBkMode(memDC, TRANSPARENT);
            SetTextColor(memDC, RGB(40, 40, 50));
            SelectObject(memDC, g_app.hFontClock);
            TextOutA(memDC, tx, ty, buf, (int)strlen(buf));
        }
    }

    /* hands */
    int h12 = hour % 12;
    double h_angle = ((h12 * 30) + minute * 0.5 - 90) * 3.14159 / 180.0;
    double m_angle = ((minute * 6) + second * 0.1 - 90) * 3.14159 / 180.0;
    double s_angle = (second * 6 - 90) * 3.14159 / 180.0;

    /* hour hand */
    {
        int len = r * 50 / 100;
        int hx = (int)(cx + len * cos(h_angle));
        int hy = (int)(cy + len * sin(h_angle));
        HPEN hPen = CreatePen(PS_SOLID, 7, RGB(30, 30, 50));
        SelectObject(memDC, hPen);
        MoveToEx(memDC, cx, cy, NULL);
        LineTo(memDC, hx, hy);
        MoveToEx(memDC, cx, cy, NULL);
        LineTo(memDC, (int)(cx - 15 * cos(h_angle)), (int)(cy - 15 * sin(h_angle)));
        DeleteObject(hPen);
    }

    /* minute hand */
    {
        int len = r * 72 / 100;
        int mx = (int)(cx + len * cos(m_angle));
        int my = (int)(cy + len * sin(m_angle));
        HPEN mPen = CreatePen(PS_SOLID, 4, RGB(40, 40, 60));
        SelectObject(memDC, mPen);
        MoveToEx(memDC, cx, cy, NULL);
        LineTo(memDC, mx, my);
        MoveToEx(memDC, cx, cy, NULL);
        LineTo(memDC, (int)(cx - 18 * cos(m_angle)), (int)(cy - 18 * sin(m_angle)));
        DeleteObject(mPen);
    }

    /* second hand */
    if (g_app.showSeconds) {
        int len = r * 85 / 100;
        int sx = (int)(cx + len * cos(s_angle));
        int sy = (int)(cy + len * sin(s_angle));
        HPEN sPen = CreatePen(PS_SOLID, 2, RGB(220, 50, 50));
        SelectObject(memDC, sPen);
        MoveToEx(memDC, cx, cy, NULL);
        LineTo(memDC, sx, sy);
        MoveToEx(memDC, cx, cy, NULL);
        LineTo(memDC, (int)(cx - 25 * cos(s_angle)), (int)(cy - 25 * sin(s_angle)));
        DeleteObject(sPen);
    }

    /* center dot */
    {
        HBRUSH dotBr = CreateSolidBrush(RGB(220, 50, 50));
        HPEN dotPen = CreatePen(PS_SOLID, 1, RGB(180, 30, 30));
        SelectObject(memDC, dotPen);
        SelectObject(memDC, dotBr);
        Ellipse(memDC, cx - 8, cy - 8, cx + 8, cy + 8);
        DeleteObject(dotBr);
        DeleteObject(dotPen);

        HBRUSH capBr = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(memDC, GetStockObject(NULL_PEN));
        SelectObject(memDC, capBr);
        Ellipse(memDC, cx - 3, cy - 3, cx + 3, cy + 3);
        DeleteObject(capBr);
    }

    /* date window */
    {
        int dw_w = 64, dw_h = 22;
        int dw_x = cx - dw_w / 2;
        int dw_y = cy + r / 3;
        HPEN dwPen = CreatePen(PS_SOLID, 1, RGB(120, 120, 130));
        HBRUSH dwBr = CreateSolidBrush(g_app.clrClockBg);
        SelectObject(memDC, dwPen);
        SelectObject(memDC, dwBr);
        RoundRect(memDC, dw_x, dw_y, dw_x + dw_w, dw_y + dw_h, 6, 6);
        DeleteObject(dwPen);
        DeleteObject(dwBr);
    }

    DeleteObject(faceBr);
    DeleteObject(facePen);

    /* blit */
    BitBlt(hdc, rect.left, rect.top, w, h, memDC, 0, 0, SRCCOPY);
    SelectObject(memDC, oldBmp);
    DeleteObject(memBmp);
    DeleteDC(memDC);
}

static void draw_clock_panel(HDC hdc, RECT rect, int selIndex) {
    int w = rect.right - rect.left;
    int h = rect.bottom - rect.top;

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP memBmp = CreateCompatibleBitmap(hdc, w, h);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, memBmp);

    FillRect(memDC, &rect, g_app.hBrushPanelBg);

    /* title */
    SetBkMode(memDC, TRANSPARENT);
    SetTextColor(memDC, RGB(30, 30, 50));
    SelectObject(memDC, g_app.hFontTitle);
    char title[128];
    if (selIndex >= 0) {
        sprintf(title, "Time in %s", countries[selIndex].name);
    } else {
        sprintf(title, "ANALOG WORLD CLOCK");
    }
    RECT tr = {rect.left + 10, rect.top + 5, rect.right - 10, rect.top + 35};
    DrawTextA(memDC, title, -1, &tr, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    /* clock */
    int clockSize = (w < h - 130 ? w : h - 130) - 20;
    if (clockSize < 100) clockSize = 100;
    int cx = rect.left + w / 2;
    int cy = rect.top + 45 + clockSize / 2;
    RECT clockRect;
    clockRect.left = cx - clockSize / 2;
    clockRect.top = cy - clockSize / 2;
    clockRect.right = cx + clockSize / 2;
    clockRect.bottom = cy + clockSize / 2;

    int hour, minute, second, day, month, year, wday;
    if (selIndex >= 0) {
        compute_local_time_for_index(selIndex, &hour, &minute, &second, &day, &month, &year, &wday);
    } else {
        time_t now = time(NULL);
        struct tm *lt = localtime(&now);
        hour = lt->tm_hour;
        minute = lt->tm_min;
        second = lt->tm_sec;
        day = lt->tm_mday;
        month = lt->tm_mon + 1;
        year = lt->tm_year + 1900;
        wday = lt->tm_wday;
    }

    draw_clock_face(memDC, clockRect, hour, minute, second);

    /* digital time */
    SetTextColor(memDC, RGB(20, 20, 40));
    SelectObject(memDC, g_app.hFontTitle);
    char timeStr[64];
    sprintf(timeStr, "%02d : %02d : %02d", hour, minute, second);
    RECT dtRect = {rect.left, rect.top + clockSize + 50, rect.right, rect.top + clockSize + 85};
    DrawTextA(memDC, timeStr, -1, &dtRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    /* date and day */
    if (selIndex >= 0) {
        SelectObject(memDC, g_app.hFontSmall);
        SetTextColor(memDC, RGB(80, 80, 100));
        char dateBuf[80];
        sprintf(dateBuf, "%s, %s %d, %d", day_names[wday], month_names[month], day, year);
        RECT ddRect = {rect.left, rect.top + clockSize + 80, rect.right, rect.top + clockSize + 108};
        DrawTextA(memDC, dateBuf, -1, &ddRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    /* timezone info for selected */
    if (selIndex >= 0) {
        Country *c = &countries[selIndex];
        int offset = c->utc_offset_min;
        if (is_dst_active(c->utc_offset_min, c->observes_dst))
            offset += 60;
        char tzBuf[128];
        sprintf(tzBuf, "%s  |  UTC%+d:%02d  |  %s",
                c->tz_abbr, offset / 60,
                offset >= 0 ? (offset % 60) : (-offset % 60),
                c->observes_dst ? "DST Active" : "No DST");
        SetTextColor(memDC, RGB(100, 100, 120));
        RECT tzRect = {rect.left, rect.top + clockSize + 105, rect.right, rect.top + clockSize + 130};
        DrawTextA(memDC, tzBuf, -1, &tzRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    BitBlt(hdc, rect.left, rect.top, w, h, memDC, 0, 0, SRCCOPY);
    SelectObject(memDC, oldBmp);
    DeleteObject(memBmp);
    DeleteDC(memDC);
}

static void draw_detail_panel(HDC hdc, RECT rect, int selIndex) {
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP memBmp = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, memBmp);

    FillRect(memDC, &rect, g_app.hBrushPanelBg);

    RECT inner = {rect.left + 8, rect.top + 8, rect.right - 8, rect.bottom - 8};
    HPEN dpPen = CreatePen(PS_SOLID, 1, RGB(180, 180, 190));
    HBRUSH dpBr = CreateSolidBrush(RGB(252, 252, 255));
    SelectObject(memDC, dpPen);
    SelectObject(memDC, dpBr);
    RoundRect(memDC, inner.left, inner.top, inner.right, inner.bottom, 8, 8);
    DeleteObject(dpPen);
    DeleteObject(dpBr);

    SetBkMode(memDC, TRANSPARENT);

    if (selIndex < 0) {
        SetTextColor(memDC, RGB(150, 150, 165));
        SelectObject(memDC, g_app.hFontSmall);
        char *msg = "Select a country from the list to view details";
        RECT msgRect = {inner.left + 10, inner.top + 10, inner.right - 10, inner.bottom - 10};
        DrawTextA(memDC, msg, -1, &msgRect, DT_CENTER | DT_VCENTER | DT_WORDBREAK);
    } else {
        Country *c = &countries[selIndex];
        int hour, minute, second, day, month, year, wday;
        compute_local_time_for_index(selIndex, &hour, &minute, &second, &day, &month, &year, &wday);
        int offset = c->utc_offset_min;
        int dst = is_dst_active(c->utc_offset_min, c->observes_dst);
        if (dst) offset += 60;
        int off_h = offset / 60;
        int off_m = offset >= 0 ? (offset % 60) : (-offset % 60);

        int y = inner.top + 15;
        int lx = inner.left + 15;

        SetTextColor(memDC, RGB(30, 30, 50));
        SelectObject(memDC, g_app.hFontTitle);
        TextOutA(memDC, lx, y, c->name, (int)strlen(c->name));
        y += 30;

        struct {
            const char *label;
            char value[128];
        } lines[10];
        int nl = 0;

        sprintf(lines[nl++].value, "Country Detail");
        lines[nl-1].label = NULL;

        sprintf(lines[nl].value, "%s", c->capital);
        lines[nl++].label = "Capital";

        sprintf(lines[nl].value, "%s, %s %d, %d",
                day_names[wday], month_names[month], day, year);
        lines[nl++].label = "Local Date";

        sprintf(lines[nl].value, "%02d:%02d:%02d", hour, minute, second);
        lines[nl++].label = "Local Time";

        if (off_m == 0)
            sprintf(lines[nl].value, "UTC%+d", off_h);
        else
            sprintf(lines[nl].value, "UTC%+d:%02d", off_h, off_m);
        lines[nl++].label = "UTC Offset";

        sprintf(lines[nl].value, "%s", c->tz_abbr);
        lines[nl++].label = "Time Zone";

        sprintf(lines[nl].value, "%s", dst ? "YES (currently active)" :
                (c->observes_dst ? "YES (not active now)" : "NO"));
        lines[nl++].label = "Observes DST";

        sprintf(lines[nl].value, "#%d of %d", selIndex + 1, (int)NUM_COUNTRIES);
        lines[nl++].label = "List Index";

        for (int i = 0; i < nl; i++) {
            if (lines[i].label) {
                SetTextColor(memDC, RGB(100, 100, 120));
                SelectObject(memDC, g_app.hFontSmall);
                TextOutA(memDC, lx, y, lines[i].label, (int)strlen(lines[i].label));
                y += 18;
            }
            SetTextColor(memDC, RGB(30, 30, 50));
            SelectObject(memDC, g_app.hFontDetail);
            TextOutA(memDC, lx + 10, y, lines[i].value, (int)strlen(lines[i].value));
            y += 24;
        }
    }

    BitBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, memDC, 0, 0, SRCCOPY);
    SelectObject(memDC, oldBmp);
    DeleteObject(memBmp);
    DeleteDC(memDC);
}

static void update_status_bar(void) {
    time_t now = time(NULL);
    struct tm *gt = gmtime(&now);
    char buf[256];
    if (g_app.selectedIndex >= 0) {
        int hour, minute, second, day, month, year, wday;
        compute_local_time_for_index(g_app.selectedIndex, &hour, &minute, &second, &day, &month, &year, &wday);
        Country *c = &countries[g_app.selectedIndex];
        int off = c->utc_offset_min;
        if (is_dst_active(c->utc_offset_min, c->observes_dst)) off += 60;
        sprintf(buf, "  SELECTED: %s | %s, %s %d %d | %02d:%02d:%02d | UTC%+d:%02d | %s",
                c->name, day_names[wday], month_names[month], day, year,
                hour, minute, second, off / 60,
                off >= 0 ? (off % 60) : (-off % 60), c->tz_abbr);
    } else {
        sprintf(buf, "  UTC: %04d-%02d-%02d %s %02d:%02d:%02d   |   %d locations worldwide",
                gt->tm_year + 1900, gt->tm_mon + 1, gt->tm_mday,
                day_names[gt->tm_wday], gt->tm_hour, gt->tm_min, gt->tm_sec,
                (int)NUM_COUNTRIES);
    }
    SetWindowTextA(g_app.hwndStatusBar, buf);
}

static void on_resize(HWND hwnd, int w, int h) {
    int panelW = 360;
    int clockW = w - panelW;
    if (clockW < 200) clockW = 200;
    if (panelW > w - 200) panelW = w - 200;
    if (panelW < 150) panelW = 150;

    int statusH = 24;
    MoveWindow(g_app.hwndStatusBar, 0, h - statusH, w, statusH, TRUE);

    int clientH = h - statusH;
    MoveWindow(g_app.hwndClockPanel, 0, 0, clockW, clientH, TRUE);

    int detailH = clientH / 2;
    MoveWindow(g_app.hwndListBox, clockW, 0, panelW, clientH - detailH, TRUE);
    MoveWindow(g_app.hwndDetailPanel, clockW, clientH - detailH, panelW, detailH, TRUE);

    InvalidateRect(hwnd, NULL, TRUE);
}

static void init_fonts(void) {
    g_app.hFontClock = CreateFontA(18, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, FF_DONTCARE, "Segoe UI");
    g_app.hFontDetail = CreateFontA(16, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, FF_DONTCARE, "Segoe UI");
    g_app.hFontSmall = CreateFontA(13, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, FF_DONTCARE, "Segoe UI");
    g_app.hFontTitle = CreateFontA(22, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, FF_DONTCARE, "Segoe UI");
}

static void init_resources(void) {
    g_app.clrClockBg = RGB(245, 245, 250);
    g_app.clrPanelBg = RGB(235, 238, 245);
    g_app.clrText = RGB(30, 30, 50);
    g_app.hBrushBg = CreateSolidBrush(RGB(240, 240, 245));
    g_app.hBrushClockBg = CreateSolidBrush(g_app.clrClockBg);
    g_app.hBrushPanelBg = CreateSolidBrush(g_app.clrPanelBg);
    g_app.hPenHour = CreatePen(PS_SOLID, 6, RGB(30, 30, 50));
    g_app.hPenMinute = CreatePen(PS_SOLID, 4, RGB(40, 40, 60));
    g_app.hPenSecond = CreatePen(PS_SOLID, 2, RGB(220, 50, 50));
    g_app.hPenTick = CreatePen(PS_SOLID, 2, RGB(70, 70, 85));
    g_app.hPenTickSub = CreatePen(PS_SOLID, 1, RGB(160, 160, 175));
    g_app.hPenBorder = CreatePen(PS_SOLID, 1, RGB(180, 180, 190));
    g_app.showSeconds = 1;
    g_app.selectedIndex = -1;
    init_fonts();
}

static void cleanup_resources(void) {
    DeleteObject(g_app.hFontClock);
    DeleteObject(g_app.hFontDetail);
    DeleteObject(g_app.hFontSmall);
    DeleteObject(g_app.hFontTitle);
    DeleteObject(g_app.hBrushBg);
    DeleteObject(g_app.hBrushClockBg);
    DeleteObject(g_app.hBrushPanelBg);
    DeleteObject(g_app.hPenHour);
    DeleteObject(g_app.hPenMinute);
    DeleteObject(g_app.hPenSecond);
    DeleteObject(g_app.hPenTick);
    DeleteObject(g_app.hPenTickSub);
    DeleteObject(g_app.hPenBorder);
}

static LRESULT CALLBACK clock_panel_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rc;
        GetClientRect(hwnd, &rc);
        draw_clock_panel(hdc, rc, g_app.selectedIndex);
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_ERASEBKGND:
        return 1;
    }
    return DefWindowProcA(hwnd, msg, wp, lp);
}

static LRESULT CALLBACK detail_panel_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rc;
        GetClientRect(hwnd, &rc);
        draw_detail_panel(hdc, rc, g_app.selectedIndex);
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_ERASEBKGND:
        return 1;
    }
    return DefWindowProcA(hwnd, msg, wp, lp);
}

static LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE: {
        g_app.hwndMain = hwnd;

        WNDCLASSA wcPanel = {0};
        wcPanel.lpfnWndProc = clock_panel_proc;
        wcPanel.hInstance = GetModuleHandleA(NULL);
        wcPanel.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcPanel.lpszClassName = "ClockPanelClass";
        RegisterClassA(&wcPanel);

        WNDCLASSA wcDetail = {0};
        wcDetail.lpfnWndProc = detail_panel_proc;
        wcDetail.hInstance = GetModuleHandleA(NULL);
        wcDetail.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcDetail.lpszClassName = "DetailPanelClass";
        RegisterClassA(&wcDetail);

        init_resources();

        g_app.hwndClockPanel = CreateWindowA("ClockPanelClass", NULL,
            WS_CHILD | WS_VISIBLE, 0, 0, 100, 100, hwnd, NULL,
            GetModuleHandleA(NULL), NULL);

        g_app.hwndListBox = CreateWindowA("LISTBOX", NULL,
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY | LBS_HASSTRINGS,
            0, 0, 100, 100, hwnd, (HMENU)ID_LISTBOX,
            GetModuleHandleA(NULL), NULL);
        SendMessageA(g_app.hwndListBox, WM_SETFONT, (WPARAM)g_app.hFontSmall, TRUE);

        for (int i = 0; i < (int)NUM_COUNTRIES; i++) {
            SendMessageA(g_app.hwndListBox, LB_ADDSTRING, 0, (LPARAM)countries[i].name);
        }

        g_app.hwndDetailPanel = CreateWindowA("DetailPanelClass", NULL,
            WS_CHILD | WS_VISIBLE, 0, 0, 100, 100, hwnd, NULL,
            GetModuleHandleA(NULL), NULL);

        g_app.hwndStatusBar = CreateWindowA(STATUSCLASSNAMEA, NULL,
            WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
            0, 0, 100, 24, hwnd, (HMENU)ID_STATUSBAR,
            GetModuleHandleA(NULL), NULL);

        int parts[] = {500, -1};
        SendMessageA(g_app.hwndStatusBar, SB_SETPARTS, 2, (LPARAM)parts);
        SendMessageA(g_app.hwndStatusBar, WM_SETFONT, (WPARAM)g_app.hFontSmall, TRUE);

        SetTimer(hwnd, ID_TIMER, 1000, NULL);
        update_status_bar();
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    }

    case WM_SIZE: {
        int w = LOWORD(lp);
        int h = HIWORD(lp);
        on_resize(hwnd, w, h);
        return 0;
    }

    case WM_TIMER:
        if (wp == ID_TIMER) {
            update_status_bar();
            InvalidateRect(g_app.hwndClockPanel, NULL, FALSE);
            InvalidateRect(g_app.hwndDetailPanel, NULL, FALSE);
        }
        return 0;

    case WM_COMMAND:
        if (LOWORD(wp) == ID_LISTBOX && HIWORD(wp) == LBN_SELCHANGE) {
            int idx = (int)SendMessageA(g_app.hwndListBox, LB_GETCURSEL, 0, 0);
            if (idx != LB_ERR) {
                g_app.selectedIndex = idx;
            }
            update_status_bar();
            InvalidateRect(g_app.hwndClockPanel, NULL, FALSE);
            InvalidateRect(g_app.hwndDetailPanel, NULL, FALSE);
        }
        return 0;

    case WM_CTLCOLORSTATIC: {
        HDC hdc = (HDC)wp;
        HWND ctrl = (HWND)lp;
        if (ctrl == g_app.hwndListBox) {
            SetBkMode(hdc, TRANSPARENT);
            return (LRESULT)g_app.hBrushPanelBg;
        }
        return DefWindowProcA(hwnd, msg, wp, lp);
    }

    case WM_KEYDOWN:
        if (wp == VK_F5) {
            InvalidateRect(hwnd, NULL, TRUE);
        }
        return 0;

    case WM_DESTROY:
        KillTimer(hwnd, ID_TIMER);
        cleanup_resources();
        PostQuitMessage(0);
        return 0;

    case WM_ERASEBKGND: {
        HDC hdc = (HDC)wp;
        RECT rc;
        GetClientRect(hwnd, &rc);
        FillRect(hdc, &rc, g_app.hBrushPanelBg);
        return 1;
    }
    }

    return DefWindowProcA(hwnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    (void)hPrevInstance;
    (void)lpCmdLine;

    InitCommonControls();

    WNDCLASSA wc = {0};
    wc.lpfnWndProc = wnd_proc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursorA(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "WorldClockGUIClass";
    RegisterClassA(&wc);

    int w = 950, h = 650;
    int x = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
    int y = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;

    HWND hwnd = CreateWindowExA(0, "WorldClockGUIClass",
        "World Clock - Global Time Zones",
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        x, y, w, h, NULL, NULL, hInstance, NULL);

    if (!hwnd) return 1;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessageA(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return (int)msg.wParam;
}
