#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN() system("cls")
#else
#define CLEAR_SCREEN() printf("\033[2J\033[H")
#endif

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
    {"Australia (Lord Howe)", "Lord Howe Island", 630, 1, "LHST/LHDT"},
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

static int is_dst_active(int utc_offset_min, int observes_dst) {
    if (!observes_dst) return 0;
    time_t now = time(NULL);
    struct tm *gmt = gmtime(&now);
    int month = gmt->tm_mon + 1;
    int local_offset = utc_offset_min;
    if (local_offset >= 0) {
        return (month >= 3 && month <= 10);
    } else {
        return (month <= 3 || month >= 10);
    }
    return 0;
}

static void compute_local_time(int utc_offset_min, int observes_dst,
                               int *out_hour, int *out_min, int *out_sec,
                               int *out_day, int *out_month, int *out_year,
                               int *out_wday) {
    time_t now = time(NULL);
    int total_offset = utc_offset_min;
    if (is_dst_active(utc_offset_min, observes_dst))
        total_offset += 60;
    time_t local_time = now + total_offset * 60;
    struct tm *lt = gmtime(&local_time);
    *out_hour = lt->tm_hour;
    *out_min = lt->tm_min;
    *out_sec = lt->tm_sec;
    *out_day = lt->tm_mday;
    *out_month = lt->tm_mon + 1;
    *out_year = lt->tm_year + 1900;
    *out_wday = lt->tm_wday;
}

#ifdef _WIN32
static void set_color(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)color);
}

static void hide_cursor(void) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci;
    GetConsoleCursorInfo(hConsole, &ci);
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &ci);
}

static void show_cursor(void) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci;
    GetConsoleCursorInfo(hConsole, &ci);
    ci.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &ci);
}
#else
static void set_color(int color) { (void)color; }
static void hide_cursor(void) {}
static void show_cursor(void) {}
#endif

static const char *day_names[] = {
    "Sunday", "Monday", "Tuesday", "Wednesday",
    "Thursday", "Friday", "Saturday"
};

static const char *month_names[] = {
    "", "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleTitleA("WORLD CLOCK - All Countries & Time Zones");
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
#endif

    hide_cursor();
    atexit(show_cursor);

    while (1) {
        CLEAR_SCREEN();

        time_t now = time(NULL);
        struct tm *utc_tm = gmtime(&now);

        /* header */
        set_color(11);
        printf("\n");
        printf("  =================================================================================================\n");
        printf("  |                             W O R L D   C L O C K                                            |\n");
        printf("  |                    Current UTC: %04d-%02d-%02d  %s  %02d:%02d:%02d                             |\n",
               utc_tm->tm_year + 1900, utc_tm->tm_mon + 1, utc_tm->tm_mday,
               day_names[utc_tm->tm_wday],
               utc_tm->tm_hour, utc_tm->tm_min, utc_tm->tm_sec);
        printf("  =================================================================================================\n");

        set_color(14);
        printf("  %-3s  %-44s  %-12s  %-14s  %-5s  %-12s  %-12s\n",
               "No.", "Country / Territory", "Capital", "Time Zone", "DOW",
               "Local Time", "Local Date");
        set_color(15);
        printf("  %-3s  %-44s  %-12s  %-14s  %-5s  %-12s  %-12s\n",
               "---", "--------------------------------------------", "------------",
               "--------------", "-----", "------------", "------------");

        for (size_t i = 0; i < NUM_COUNTRIES; i++) {
            int hour, minute, second, day, month, year, wday;
            compute_local_time(countries[i].utc_offset_min,
                               countries[i].observes_dst,
                               &hour, &minute, &second,
                               &day, &month, &year, &wday);

            int color = 7;
            if (hour >= 6 && hour < 12)
                color = 10;  /* morning - green */
            else if (hour >= 12 && hour < 18)
                color = 14;  /* afternoon - yellow */
            else if (hour >= 18 && hour < 22)
                color = 12;  /* evening - red */
            else
                color = 9;   /* night - blue */

            set_color(color);
            printf("  %3zu  %-44s  %-12s  %-14s  %-5s  %02d:%02d:%02d     %s %02d, %d\n",
                   i + 1,
                   countries[i].name,
                   countries[i].capital,
                   countries[i].tz_abbr,
                   day_names[wday],
                   hour, minute, second,
                   month_names[month], day, year);
        }

        set_color(11);
        printf("\n  =================================================================================================\n");
        printf("  |   Press Ctrl+C to exit   |   Total: %zu locations   |   %s   |\n",
               NUM_COUNTRIES, __DATE__);
        printf("  =================================================================================================\n");

        set_color(7);
        fflush(stdout);

#ifdef _WIN32
        Sleep(1000);
#else
        sleep(1);
#endif
    }

    return 0;
}
