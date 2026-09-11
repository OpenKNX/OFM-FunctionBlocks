# Release Notes

## 0.11.0
### Breaking Changes
- none

### Feature
- Neuer Funktionsblock: Bayes-Sensor
- Funktionserweiterung Text-Block: Zeitfunktionen (Uhrzeit, Sonnenauf-/-untergang, Datumsbestandteile) 
- OpenKNX-Standardisierung: Anpassung auf neues UI-Pattern für Kanal-Auswahl

### Bug
- Fix #29: Dauer war durch uint8_t Berechnung auf 255s beschränkt bei "Start mit Zeit" in {"Einheit Minuten", "Einheit Stunden"}
- Verschiedene kleine Korrekturen in UI und Hilfetexten

## 0.10.0
### Breaking Changes
- none

### Feature
- Initial machine-readable release notes created.

### Bug
- none

## 0.9.1
### Breaking Changes
- none

### Feature
- none

### Bug
- Fix: Crash beim Programmieren.

## 0.9
### Breaking Changes
- none

### Feature
- Neuer Funktionsblock "Text Format".
- Startverhalten bei Wertüberwachung konfigurierbar.

### Bug
- none

## 0.8
### Breaking Changes
- none

### Feature
- none

### Bug
- Fix: Benennung Eingang 9 bei FB-"Anzahl" nicht möglich.

## 0.7
### Breaking Changes
- none

### Feature
- Count-Down: Konfigurationsparameter für maximale Laufzeit bei Erhöhen durch KO.
- Count-Down: Text-Parameter für Stopp.

### Bug
- none

## 0.6.2
### Breaking Changes
- Verhalten von KO Verringern/Erhöhen für Count-Down wurde geändert.

### Feature
- none

### Bug
- Fix: KO Verringern/Erhöhen für Count-Down (0 = Verringern, 1 = Erhöhen).

## 0.6.1
### Breaking Changes
- Verhalten von KO Pause/Fortsetzen wurde geändert.

### Feature
- none

### Bug
- Fix: KO Pause/Fortsetzen richtiggestellt (1 = Fortsetzen, 0 = Pause).

## 0.6
### Breaking Changes
- none

### Feature
- Eingänge können benannt werden.
- Text-Input verwendet ISO-8859-1.

### Bug
- none

## 0.5
### Breaking Changes
- none

### Feature
- Szene-DPT als Prioritätsschalter-Ausgang.

### Bug
- none

