# OFM-FunctionBlocks

Dieses Modul stellt Funktionsbausteine zur Verfügung. 
Es sollte dabei als Ergänzung und nicht als Ersatz zum [Logikmodul](https://github.com/OpenKNX/OFM-LogicModule) gesehen werden.
Ziel ist, komplexere Logiken einfach per Konfiguration abbilden zu können. 
Im Gegensatz zum Logikmodul sind die Funktion-Blöcke nicht generisch, das heißt, jeder Funktionsblock dient genau einem Zweck und ist nur im geringen Maß konfigurierbar.
Bei Bedarf können die FunktionsBlöcke mit Logiken ergänzen werden.

## Release Notes

- 0.9.1 Fix: Crash beim Programmieren
- 0.9 Neuer Functionsblock "Text Format"
- 0.9 Startverhalten bei Wertüberwachung konfigurierbar
- 0.8 Fix: Bennennung Eingang 9 bei FB-"Anzahl" nicht möglich
- 0.7 Count-Down: Konfigurationsparameter für maximale Laufzeit bei Erhöhen durch KO
- 0.7 Count-Down: Text Parameter für Stopp
- 0.6.2 Breaking Change: Fix: Ko Verringern/Erhöhen für Count-Down: 0...Verringern, 1...Erhöhen
- 0.6.1 Breaking Change: Fix: Ko Pause/Fortsetzten ist nun richtiggestellt: 1...Fortsetzten, 0...Pause
- 0.6 Eingänge können benannt werden
- 0.6 Text Input is now ISO-8859-1
- 0.5 Szene-DPT als Prioritätsschalter Ausgang

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
- Wertüberwachung
  - Zeitüberschreitung (Watchdog)
  - Minimaler Wert
  - Maximaler Wert
- Multiplexer
- Blinker

## Planned Features
- Counter

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