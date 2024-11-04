<!-- SPDX-License-Identifier: AGPL-3.0-only -->
<!-- Copyright (C) 2024 Michael Geramb -->

# Applikationsbeschreibung Funktionsblöcke

Die Anwendung stellt je Kanal einen Funktionsblock bereit.
Folgende Funktionsblöcke stehen zur Auswahl:
  * [UND](#und)
  * [ODER](#oder)
  * [Prioritätsschalter](#prioritätsschalter)
    * [Beispielanwendungen](#beispielsanwendung)
  * [Anzahl](#anzahl)



### ETS Konfiguration

* **[Allgemein](#allgemein)**
  * [Kanalauswahl](#kanalauswahl)
* (n=1 bis 99) *Abhängig vomTyp*:
  * [Kanal-Typ-unabhängige Einstellungen](#kanaleinstellungen)
  * {[**UND**](#undoder-kanaleinstellungen), [**ODER**](#undoder-kanaleinstellungen)}
  * [**Prioritätsschalter**](#prioritätsschalter-2)
  * [**Anzahl**](#anzahl)



# Blocktypen


<!-- DOC -->
## UND

Ein UND-Funktionsblock verfügt über bis zu 9 Eingänge. 
Der Ausgang gibt EIN aus, wenn alle Eingänge EIN sind.
Zusätzlich können sowohl die Eingänge als auch der Ausgang über die Konfiguration invertiert werden.

<!-- DOC -->
## ODER

Ein ODER-Funktionsblock verfügt über bis zu 9 Eingänge. Der Ausgang gibt EIN aus, wenn mindestens ein Eingang EIN ist.
Zusätzlich können sowohl die Eingänge als auch der Ausgang über die Konfiguration invertiert werden.

<!-- DOC -->
## Prioritätsschalter
Ein Prioritätsschalter hat bis zu 9 Eingänge vom Typ EIN/AUS.
Der Eingang mit der höchsten Priorität der EIN ist, bestimmt den Ausgangswert.
Für jede Priorität wird in der Konfiguration der Wert des Ausgangs festgelegt.
Dieser kann als Prozentwert oder Zahl zwischen 0-255 festgelegt werden.

### Beispielsanwendung

<!-- DOC Skip="1" -->
Der [Busch-Jaeger 6108/07 Tasterankopplung](https://www.busch-jaeger.at/online-katalog/detail/2CKA006133A0222) hat eine mehrfärbige LED verbaut. 
<!-- DOCCONTENT
Der Busch-Jaeger 6108/07 Tasterankopplung hat eine mehrfärbige LED verbaut. 
DOCCONTENT -->
Die Farbe der LED kann aber über ein Kommunikationsobjekt nicht verändert werden.
Jedoch bietet der Taste die Möglichkeit verschiedene Prozentwerte mit verschieden Farben darzustellen.
So können z.B. für einen Jalousientaster Kommunikationswerte für Nachbetrieb, Beschattung aktiv, Windsperre auf Prozentwerte umgesetzt werden, die der Taster in verschiedene Farbwerte umsetzt.


<!-- DOC -->
## Anzahl

Ein Anzahl-Funktionsblock verfügt über bis zu 9 Eingänge. 
Der Ausgang gibt aus, wie viele der (verwendeten) Eingänge den Wert EIN angenommen haben.
Die Eingänge können vor Zählung invertiert werden.

# ETS Konfiguration

<!-- DOC -->
## Allgemein
Die Anwendung stellt je Kanal einen Funktionsblock bereit.
Auf dieser Seite kann gewählt werden, welcher Kanal für welche Funktionsblocktype verwendet wird.

<!-- DOC -->
### Verfügbare Kanäle
Maximale Anzahl der benötigten Funktionsblöcke. 
Die Einstellung dient lediglich dazu, die Seite der Basiseinstellungen kompakt auf das wirklich benötigte zu verkleinern.

<!-- DOC -->
### Kanalauswahl

Für jeden Kanal kann für einen Funktionsblock konfiguriert werden:

#### UND

Ein UND-Funktionsblock verfügt über bis zu 9 Eingänge. 
Der Ausgang gibt EIN aus, wenn alle Eingänge EIN sind.

#### ODER

Ein ODER-Funktionsblock verfügt über bis zu 9 Eingänge. Der Ausgang gibt EIN aus, wenn mindestens ein Eingang EIN ist.

#### Prioritätsschalter

Ein Prioritätsschalter hat bis zu 9 Eingänge vom Typ EIN/AUS.
Der Eingang mit der höchsten Priorität der EIN ist, bestimmt den Ausgangswert.

## Kanaleinstellungen

Jeder Kanal bietet folgende Einstellungen:

<!-- DOC -->
### Bezeichnung

Die Bezeichnung wird innerhalb der ETS für die Benennung des Kanals und für die Benennung der Funktionsblock Ein- und Ausgänge verwendet.
Die Bezeichnung hat keinen Einfluss auf das Verhalten des Funktionsblocks und kann jederzeit auch nachträglich angepasst werden.

<!-- DOC -->
### Kanal deaktivieren (zu Testzwecken)

Mit dieser Einstellung kann ein Kanal deaktiviert werden, ohne das die Konfigurationswerte und Gruppenadressen an den Kommunikationsobjekten verloren gehen.
Ein deaktivierter Kanal sendet keine Telegramme auf dem KNX-Bus. 


<!-- DOC -->
#### Kommentar

Hier kann eine ausführlichere - auch mehrzeilige - Dokumention des Blocks erfolgen.
Es wird empfohlen zentrale Annahmen die der Konfiguration des Blocks zugrunde liegen hier festzuhalten.
Die Dokumentation hat keinen Einfluss auf das Geräteverhalten.

Eine mehrzeilige Eingabe ist aufgrund von Beschränkungen der ETS nicht direkt möglich, 
kann jedoch durch Eingabe mit `\n` und Drücken des Buttons erzeugt werden.
Anschließend kann der Text mehrzeilig bearbeitet werden.

<!-- DOCEND -->
*Beispiel:*
>
> Der Text
> ```
> Ein Text\nmit mehreren\nZeilen!
> ```
> wird umgewandelt in
> ```
> Ein Text
> mit mehreren
> Zeilen!
> ```

## UND/ODER/Anzahl Kanaleinstellungen

<!-- DOC HelpContext="LogicEingang" -->
### Eingang 1-9

Legt fest, ob der Eingang verwendet wird, und falls ja, ob der Eingangswert **normal** oder **invertiert** verwendet wird.

<!-- DOC -->
### Initialisierung

Legt den Initialwert für den Eingang fest.
Zur Auswahl stehen:

- **AUS**  
  Der Eingang wird mit AUS vorbelegt
- **EIN**  
  Der Eingang wird mit EIN vorbelegt
- **Vom Bus lesen, dann AUS**  
  Es wird versucht den Eingangswert vom Bus über eine Lesetelegram zu lesen. 
  Wird nach 3 Sekunden keine Antwort empfangen, wird der Eingang mit AUS vorbelegt.
- **Vom Bus lesen, dann EIN**  
  Es wird versucht den Eingangswert vom Bus über eine Lesetelegram zu lesen. 
  Wird nach 3 Sekunden keine Antwort empfangen, wird der Eingang mit EIND vorbelegt.

**Wichtig**: Die Vorbelegung erfolgt vor einer möglichen eingestellten Invertierung des Eingangswertes.
Das bedeutet das bei einer Vorbelegung von "AUS" und einer eingestellten Invertierung der Wert als EIN von der Logik interpretiert wird.

<!-- DOC -->
### Invertiert

<!-- DOC Skip="2" -->
> *Nur* bei Block-Typen UND/ODER verfügbar

Legt fest, ob der Ausgangswert normal oder invertiert auf den Bus gesendet wird.

<!-- DOC -->
### Sendeverhalten

Zur Auswahl stehen:

- **Bei jedem Eingangstelegram**  
  Wenn einer der Eingänge ein Telegramm empfängt, wird der Ausgangswert auf den Bus gesendet. 
  Diese Einstellung kann zu hintereinderfolgenden gleichen Ausgangswerten am Bus führen.

- **Nur bei Änderung des Ausgangswertes**  
  Der Ausgang wird nur dann auf den Bus gesendet, wenn sich durch die berechnete Logikfunktion der Wert ändert.


Unabhängig von der Einstellung wird der Ausgangswert auch nach der Initialisierungsphase inklusive eventueller Wartezeit für Leseanforderungs-Antworten einmalig auf den Bus gesendet.

## Prioritätsschalter

<!-- DOC HelpContext="PrioOutputType" -->
### Type

Legt fest, welchen Werttype für den Ausgang verwendet wird

- **Prozent (0-100%)** 
  Ausgang ist Prozent (5.001)
- **1 Byte (Ohne Vorzeichen)** 
  Ausgang ist byte (5.* 8 bit vorzeichenlos)

<!-- DOCEND -->

### Sendeverhalten

Zur Auswahl stehen:

- **Bei jedem Eingangstelegram**  
  Wenn einer der Eingänge ein Telegramm empfängt, wird der Ausgangswert auf den Bus gesendet. 
  Diese Einstellung kann zu hintereinderfolgenden gleichen Ausgangswerten am Bus führen.

- **Nur bei Änderung des Ausgangswertes**  
  Der Ausgang wird nur dann auf den Bus gesendet, wenn sich durch die berechnete Logikfunktion der Wert ändert.


Unabhängig von der Einstellung wird der Ausgangswert auch nach der Initialisierungsphase inklusive eventueller Wartezeit für Leseanforderungs-Antworten einmalig auf den Bus gesendet.

<!-- DOC -->
### Ausgangswert wenn alle Eingänge AUS

Legt den Wert für den Ausgang fest, wenn alle Eingänge AUS sind.

<!-- DOC HelpContext="PrioEingang" -->
### Eingang 1-9

Legt fest, ob der Eingang verwendet wird und ob der Eingangswert normal oder invertiert verwendet wird.
Die Eingangsnummer 1-9 entspricht gleichzeitig der Priorität, wobei 1 die höchste und 9 die niedrigste darstellt.

<!-- DOCEND-->

### Initialisierung

Legt den Initialwert für den Eingang fest.
Zur Auswahl stehen:

- **AUS**  
  Der Eingang wird mit AUS vorbelegt
- **EIN**  
  Der Eingang wird mit EIN vorbelegt
- **Vom Bus lesen, dann AUS**  
  Es wird versucht den Eingangswert vom Bus über eine Lesetelegram zu lesen. 
  Wird nach 3 Sekunden keine Antwort empfangen, wird der Eingang mit AUS vorbelegt.
- **Vom Bus lesen, dann EIN**  
  Es wird versucht den Eingangswert vom Bus über eine Lesetelegram zu lesen. 
  Wird nach 3 Sekunden keine Antwort empfangen, wird der Eingang mit EIND vorbelegt.

**Wichtig**: Die Vorbelegung erfolgt vor einer möglichen eingestellten Invertierung des Eingangswertes.
Das bedeutet das bei einer Vorbelegung von "AUS" und einer eingestellten Invertierung der Wert als EIN von der Logik interpretiert wird.

<!-- DOC -->		
### Ausgangswert

Legt den Wert fest, der auf den Bus gesendet wird, wenn dieser Eingang der Eingang mit der höchsten Nummer ist der auf EIN gesetzt ist.
  