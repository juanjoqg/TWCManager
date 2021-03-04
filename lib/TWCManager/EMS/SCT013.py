# SCT013 

import serial

class SCT013:

    import requests
    import time

    cacheTime = 10
    config = None
    configConfig = None
    configSCT013 = None
    consumedW = 0
    debugLevel = 0
    fetchFailed = False
    generatedW = 0
    importW = 0
    exportW = 0
    lastFetch = 0
    master = None
    status = False
    timeout = 10
    voltage = 0
    arduino=0

    def __init__(self, master):
        self.master = master
        self.config = master.config
        try:
            self.configConfig = master.config["config"]
        except KeyError:
            self.configConfig = {}
        try:
            self.configSCT013 = master.config["sources"]["SCT013"]
        except KeyError:
            self.configSCT013 = {}
        self.debugLevel = self.configConfig.get("debugLevel", 0)
        self.status = self.configSCT013.get("enabled", False)
        self.arduinoUSB = self.configSCT013.get("arduinoPort", None)

        # Unload if this module is disabled or misconfigured
        if (not self.status):
            self.master.releaseModule("lib.TWCManager.EMS", "SCT013")
            return None

        self.arduino = serial.Serial(self.arduinoUSB,baudrate=9600, timeout = 3.0)

    def debugLog(self, minlevel, message):
        self.master.debugLog(minlevel, "SCT013", message)

    def getConsumption(self):

        if not self.status:
            self.debugLog(10, "SCT013 EMS Module Disabled. Skipping getConsumption")
            return 0

        # Perform updates if necessary
        self.update()

        # Return consumption value
        return float(self.consumedW)

    def getGeneration(self):

        if not self.status:
            self.debugLog(10, "SCT013 EMS Module Disabled. Skipping getGeneration")
            return 0

        # Perform updates if necessary
        self.update()

        # Return generation value
        if not self.generatedW:
            self.generatedW = 0
        return float(self.generatedW)


    def update(self):

        if (int(self.time.time()) - self.lastFetch) > self.cacheTime:
            # Cache has expired. Fetch values from SCT013.

            try:
                txt=''
                while self.arduino.inWaiting() > 0:
                      txt = str(self.arduino.readline())
                try:            
                   if txt.index("Potencia = "):
                      txt2 = txt[txt.find("Potencia = ")+10:txt.find("Irms = ")]
                      txt2 = txt2.replace(' ','')
                      if not txt2:
                           self.consumedW=0
                      else:
                           self.consumedW=float(txt2)
                except:
                   self.consumedW=self.consumedW

                try:
                   if txt.index("Potencia2 = "):
                      txt3 = txt[txt.find("Potencia2 = ")+11:txt.find("Irms2 = ")]
                      txt3 = txt3.replace(' ','')
                      if not txt3:
                           self.generatedW=0
                      else:
                           self.generatedW=float(txt3)
                except:
                   self.generatedW=self.generatedW

            except (KeyError, TypeError) as e:
                self.debugLog(
                4, "Exception during parsing Meter Data (Consumption)"
                )
                self.debugLog(10, e)

            # Update last fetch time
            if self.fetchFailed is not True:
                self.lastFetch = int(self.time.time())

            return True
        else:
            # Cache time has not elapsed since last fetch, serve from cache.
            return False
