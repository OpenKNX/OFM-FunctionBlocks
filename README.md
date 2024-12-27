# OFM-FunctionBlocks

Dieses Modul stellt Funktionsbausteine zur Verfügung. 
Es sollte dabei als Ergänzung und nicht als Ersatz zum [Logikmodul](https://github.com/OpenKNX/OFM-LogicModule) gesehen werden.
Ziel ist, komplexere Logiken einfach per Konfiguration abbilden zu können. 
Im Gegensatz zum Logikmodul sind die Funktion-Blöcke nicht generisch, das heißt, jeder Funktionsblock dient genau einem Zweck und ist nur im geringen Maß konfigurierbar.
Bei Bedarf können die FunktionsBlöcke mit Logiken ergänzen werden.

## Features
- AND mit 9 Eingängen
- OR mit 9 Eingängen
- Prioritätsschalter
- Anzahl
- Aggregation
  - Summe
  - Mittelwert
  - Minimum
  - Maximum
  - Spannbreite (Maximum - Minimum)
- Count Down Zeitgeber


## Planned Features
- Multiplexer
- Counter
- Messwertüberwachung
  - Watchdog
  - Grenzen
- Blinker

## Applikationsbeschreibung

Die Applikationsbeschreibung ist [hier](doc/Applikationsbeschreibung-FunctionBlocks.md) zu finden.

## Hardware Unterstützung

|Prozessor | Status               | Anmerkung                  |
|----------|----------------------|----------------------------|
|RP2040    | Beta                 |                            |
|ESP32     | Beta                 |                            |
|SAMD      | Compilable, Untested |                            |

Getestete Hardware:
- [OpenKNX Reg1-ETH](https://github.com/OpenKNX/OpenKNX/wiki/REG1-Eth)
- Adafruit ESP32 Feather V2

## Einbindung in die Anwendung

In das Anwendungs XML muss OFM-FunctionBlocks aufgenommen werden:

```xml
  <op:define prefix="FCB" ModuleType="21"
    share=   "../lib/OFM-FunctionBlocks/src/FunctionBlocks.share.xml"
    template="../lib/OFM-FunctionBlocks/src/FunctionBlocks.templ.xml"
    NumChannels="20"
    KoOffset="410">
    <op:verify File="../lib/OFM-FunctionBlocks/library.json" ModuleVersion="0.1" /> 
  </op:define>
```

**Hinweis:** Pro Kanal werden 10 KO's benötigt. Dies muss bei nachfolgenden Modulen bei KoOffset entsprechend berücksichtigt werden.

In main.cpp muss das FunctionBlocks hinzugefügt werden:

```
[...]
#include "FunctionBlocksModule.h"
[...]

void setup()
{
    [...]
    openknx.addModule(1, openknxNetwork);
    openknx.addModule(3, openknxFunctionBlocks);
    [...]
}
```

## Lizenz

[GNU GPL v3](LICENSE)