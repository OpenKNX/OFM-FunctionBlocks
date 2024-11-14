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
  * [Statistische Aggregation](#statistische-aggregation)



### ETS Konfiguration

* **[Allgemein](#allgemein)**
  * [Kanalauswahl](#kanalauswahl)
* (n=1 bis 99) *Abhängig vomTyp*:
  * [Kanal-Typ-unabhängige Einstellungen](#kanaleinstellungen)
  * {[**UND**, **ODER**, **Anzahl**](#undoderanzahl-kanaleinstellungen)}
  * [**Prioritätsschalter**](#prioritätsschalter-2)
  * [**Aggregation**](#aggregation)



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

<!-- DOC -->
## Statistische Aggregation

Ein Aggregations-Funktionsblock verfügt über bis zu 9 numerische Eingänge, gängiger DPTs. 
Der Ausgangswert wird basierend auf der gewählten Funktion (Summe, Mittelwert, Minimum, Maximum, Spannbreite) berechnet und kann in verschiedenen numerischen DPTs ausgegeben werden.
Es kann beeinflusst werden, wie mit Werten umgegangen wird die vom Ausgatyp nicht dargestellt werden können.

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

- **UND**
  Ein UND-Funktionsblock verfügt über bis zu 9 Eingänge. 
  Der Ausgang gibt EIN aus, wenn alle Eingänge EIN sind.

- **ODER**
  Ein ODER-Funktionsblock verfügt über bis zu 9 Eingänge. 
  Der Ausgang gibt EIN aus, wenn mindestens ein Eingang EIN ist.

- **Prioritätsschalter**
  Ein Prioritätsschalter hat bis zu 9 Eingänge vom Typ EIN/AUS.
  Der Eingang mit der höchsten Priorität der EIN ist, bestimmt den Ausgangswert.

- **Anzahl**
  Ein Anzahl-Funktionsblock hat bis zu 9 Eingänge vom Typ EIN/AUS.
  Der Ausgang gibt die Anzahl der Eingänge mit dem Wert EIN aus.

- **Statistische Aggregation**
  Ein Aggregations-Funktionsblock hat bis zu 9 Eingänge mit numerischem Typ.
  Es kann zwischen fünf Funktionen (Summe, Mittelwert, Minimum, Maximum, Spannbreite) zur Berechnung des Ausgangswertes gewählt werden.

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


<!-- DOC -->
### Sendeverhalten

Zur Auswahl stehen:

- **Bei jedem Eingangstelegram**  
  Wenn einer der Eingänge ein Telegramm empfängt, wird der Ausgangswert auf den Bus gesendet. 
  Diese Einstellung kann zu hintereinderfolgenden gleichen Ausgangswerten am Bus führen.

- **Nur bei Änderung des Ausgangswertes**  
  Der Ausgang wird nur dann auf den Bus gesendet, wenn sich durch die berechnete Logikfunktion der Wert ändert.


Unabhängig von der Einstellung wird der Ausgangswert auch nach der Initialisierungsphase inklusive eventueller Wartezeit für Leseanforderungs-Antworten einmalig auf den Bus gesendet.

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

### Invertiert (nur UND/ODER)

<!-- DOC HelpContext="Invertiert" -->
Legt fest, ob der Ausgangswert normal oder invertiert auf den Bus gesendet wird.

## Prioritätsschalter

<!-- DOC HelpContext="PrioOutputType" -->
### Type

Legt fest, welchen Werttype für den Ausgang verwendet wird

- **Prozent (0-100%)** 
  Ausgang ist Prozent (5.001)
- **1 Byte (Ohne Vorzeichen)** 
  Ausgang ist byte (5.* 8 bit vorzeichenlos)

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
<!-- DOCEND-->


## Aggregation

<!-- DOC HelpContext="AggrFunction" -->
### Funktion

Legt fest, wie der Ausgangswert aus den Werten der aktiven Eingänge berechnet wird:

- **Summe** 
  Addiert die Eingangswerte. 
  Das Ergebnis kann außerhalb des Eingangs-Wertebereichs liegen!
- **Mittelwert** 
  Summe dividiert durch die Anzahl der aktiven Eingänge. 
  Das Ergebnis ist i.d.R. nicht ganzzahlig, wird jedoch innerhalb des Eingangs-Wertebereichs liegen.
- **Minimum** 
  Verwendet den kleinsten Eingangswert.
- **Maximum** 
  Verwendet den größten Eingangswert.
- **Spannbreite (Maximum - Minimum)**
  Liefert ein einfaches Maß dafür, wie weit sich die Eingangs-Werte voneinander unterscheiden.
  Das Ergebnis kann außerhalb des Eingangs-Wertebereichs liegen, wenn vorzeichenbehaftet ist!

<!-- DOC -->
### Gewichtung der Eingänge

<!-- DOC Skip="2" -->
> Nur für *Summe* und *Mittelwert*

**Individuelle Gewichte** erlaubt eine Berechnung bei der die Eingänge unterschiedlich stark in der Ergebnis einfließen. 
Dazu kann je aktivem Eingang ein individuelles Gewicht (Standardwert 1) angegeben werden.
Mindestens ein Gewicht muss von 0 abweichen, sonst wird kein Ergebnis ausgegeben!


<!-- DOC HelpContext="DptEingang" -->
### Wertetyp / DPT (Eingänge)

Definiert den DPT der Eingänge. Zur Auswahl stehen gängige numerische DPTs mit 1Byte, 2Bytes und 4Bytes.

<!-- DOC HelpContext="AggrEingang" -->
### Eingang 1-9

Legt fest, ob der Eingang verwendet wird.

<!-- DOC HelpContext="AggrEingangGewicht" -->
### Gewicht Eingang 1-9

Definiert wie stark dieser Eingang in das Ergebnis einfließt.

Bei 0 hat dieser Eingang keinen Einfluss auf das Resultat der Berechnung, 
wird aber verhindern dass ein Ergebnis entsteht so lange der Eingang noch keinen Wert hat, 
oder kann abhängig vom Sendeverhalten ein Senden auf de Bus auslösen.

Ein negativer Wert ändert das Vorzeichen des Eingangswertes. Bei der Gewichtssumme fließt der Betrag ein.

<!-- DOC HelpContext="DptAusgang" -->
### Wertetyp / DPT (Ausgang)

Definiert den DPT des Ausgangs. Zur Auswahl stehen gängige numerische DPTs mit 1Byte, 2Bytes und 4Bytes.

In der Standardeinstellung **Identisch mit Eingängen** wird der DPT der Eingänge übernommen.

<!-- DOC -->
### Rundungsmodus

> *Nur* einstellbar, wenn ein Ganzzahl-Wertetyp für den Ausgang gewählt wurde und das berechnete Ergebnis nicht zwingend ganzzahlig ist.

- **Nachkommastellen verwerfen**  
  Kein besondere Behandlung.
- **Runden (ab 0,5 aufrufen)**  
  Anwendung der üblichen Rundungsregeln.

<!-- DOC HelpContext="OutOfRange"-->
### Bei Überschreiten des Wertebereichs

> *Nur* relevant, wenn der berechnete Ausgangswert durch den gewählten Ausgangs-DPT nicht mehr in jedem Fall abbildbar ist.

- **KO nicht aktualisieren / nicht senden**  
  Ignoriert den Wert.
- **Auf Bereichsrand setzen**  
  Ein zu kleiner Wert wird durch den Minimalwert des DPT ersetzt, ein zu großer Wert durch den Maximalwert.

  