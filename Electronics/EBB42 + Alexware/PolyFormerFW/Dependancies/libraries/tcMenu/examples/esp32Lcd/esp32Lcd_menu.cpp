/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

#include <tcMenu.h>
#include "esp32Lcd_menu.h"

// Global variable declarations
const PROGMEM  ConnectorLocalInfo applicationInfo = { "Esp32Lcd", "7833942f-2ef4-486f-9713-045552b747e8" };
TcMenuRemoteServer remoteServer(applicationInfo);

LiquidCrystal lcd(0, 1, 2, 4, 5, 6, 7);
LiquidCrystalRenderer renderer(lcd, 20, 4);
NoInitialisationNeeded serialInitializer;
SerialTagValueTransport serialTransport(&Serial);
TagValueRemoteServerConnection serialConnection(serialTransport, serialInitializer);

// Global Menu Item declarations
const PROGMEM char pgmStrConnectivityIoTMonitorText[] = { "IoT Monitor" };
RemoteMenuItem menuConnectivityIoTMonitor(pgmStrConnectivityIoTMonitorText, 15, NULL);
RENDERING_CALLBACK_NAME_INVOKE(fnConnectivityRtCall, backSubItemRenderFn, "Connectivity", -1, NO_CALLBACK)
const PROGMEM SubMenuInfo minfoConnectivity = { "Connectivity", 14, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackConnectivity(fnConnectivityRtCall, &menuConnectivityIoTMonitor);
SubMenuItem menuConnectivity(&minfoConnectivity, &menuBackConnectivity, NULL);
extern const char* ramChoices;
RENDERING_CALLBACK_NAME_INVOKE(fnGridNewChoiceItemRtCall, enumItemRenderFn, "New Choice Item", -1, NO_CALLBACK)
ScrollChoiceMenuItem menuGridNewChoiceItem(12, fnGridNewChoiceItemRtCall, 0, ramChoices, 10, 4, NULL);
const PROGMEM AnyMenuInfo minfoGridDown = { "Down", 11, 0xffff, 0, onGridDown };
ActionMenuItem menuGridDown(&minfoGridDown, &menuGridNewChoiceItem);
const PROGMEM AnyMenuInfo minfoGridUp = { "Up", 10, 0xffff, 0, onGridUp };
ActionMenuItem menuGridUp(&minfoGridUp, &menuGridDown);
const PROGMEM BooleanMenuInfo minfoGridLED2 = { "LED2", 8, 0xffff, 1, onGridLed2, NAMING_ON_OFF };
BooleanMenuItem menuGridLED2(&minfoGridLED2, false, &menuGridUp);
const PROGMEM BooleanMenuInfo minfoGridLED1 = { "LED1", 7, 0xffff, 1, onGridLed1, NAMING_ON_OFF };
BooleanMenuItem menuGridLED1(&minfoGridLED1, false, &menuGridLED2);
const PROGMEM FloatMenuInfo minfoGridFloatValue = { "Float value", 9, 0xffff, 3, NO_CALLBACK };
FloatMenuItem menuGridFloatValue(&minfoGridFloatValue, &menuGridLED1);
RENDERING_CALLBACK_NAME_INVOKE(fnGridRtCall, backSubItemRenderFn, "Grid", -1, NO_CALLBACK)
const PROGMEM SubMenuInfo minfoGrid = { "Grid", 6, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackGrid(fnGridRtCall, &menuGridFloatValue);
SubMenuItem menuGrid(&minfoGrid, &menuBackGrid, &menuConnectivity);
RENDERING_CALLBACK_NAME_INVOKE(fnRGBRtCall, rgbAlphaItemRenderFn, "RGB", -1, NO_CALLBACK)
Rgb32MenuItem menuRGB(5, fnRGBRtCall, false, &menuGrid);
ListRuntimeMenuItem menuMyList(4, 0, fnMyListRtCall, &menuRGB);
const PROGMEM BooleanMenuInfo minfoPeeled = { "Power", 3, 0xffff, 1, NO_CALLBACK, NAMING_ON_OFF };
BooleanMenuItem menuPeeled(&minfoPeeled, false, &menuMyList);
const char enumStrFoods_0[] PROGMEM = "Apples";
const char enumStrFoods_1[] PROGMEM = "Bananas";
const char enumStrFoods_2[] PROGMEM = "Oranges";
const char enumStrFoods_3[] PROGMEM = "Grapes";
const char* const enumStrFoods[] PROGMEM  = { enumStrFoods_0, enumStrFoods_1, enumStrFoods_2, enumStrFoods_3 };
const PROGMEM EnumMenuInfo minfoFoods = { "Foods", 2, 0xffff, 3, NO_CALLBACK, enumStrFoods };
EnumMenuItem menuFoods(&minfoFoods, 0, &menuPeeled);
const PROGMEM AnalogMenuInfo minfoPercentage = { "Percentage", 1, 0xffff, 100, NO_CALLBACK, 0, 1, "%" };
AnalogMenuItem menuPercentage(&minfoPercentage, 0, &menuFoods);

void setupMenu() {
    // First we set up eeprom and authentication (if needed).

    // Now add any readonly, non-remote and visible flags.
    menuConnectivityIoTMonitor.setLocalOnly(true);

    // Code generated by plugins.
    Wire.begin();
    lcd.setIoAbstraction(ioFrom8574(0x27, 0xff, &Wire));
    lcd.begin(20, 4);
    renderer.setUpdatesPerSecond(2);
    lcd.configureBacklightPin(3);
    lcd.backlight();
    switches.initialiseInterrupt(internalDigitalIo(), true);
    menuMgr.initForEncoder(&renderer, &menuPercentage, 26, 36, 21);
    remoteServer.addConnection(&serialConnection);

    // We have an IoT monitor, register the server
    menuConnectivityIoTMonitor.setRemoteServer(remoteServer);
}

