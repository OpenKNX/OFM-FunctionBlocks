<!-- SPDX-License-Identifier: AGPL-3.0-only -->
<!-- Copyright (C) 2024 Michael Geramb -->

# Applikationsbeschreibung Funktionsblöcke

Die Anwendung stellt je Kanal einen Funktionsblock bereit.
Folgende Funktionsblöcke stehen zur Auswahl:
  * [UND](#und)
  * [ODER](#oder)
  * [Anzahl](#anzahl)
  * [Auswahl (Multiplexer)](#auswahl-multiplexer)
  * [Prioritätsschalter](#prioritätsschalter)
  * [Statistische Aggregation](#statistische-aggregation)
  * [Wertüberwachung](#wertüberwachtung)
  * [Count-Down Zeitgeber](#count-down-zeitgeber)
  * [Blinker](#blinker)


# Blocktypen

<!-- DOC -->
## UND

Ein UND-Funktionsblock verfügt über bis zu 9 Eingänge. 
Der Ausgang gibt EIN aus, wenn alle Eingänge EIN sind.
Zusätzlich können sowohl die Eingänge als auch der Ausgang über die Konfiguration invertiert werden.

<!-- DOCEND -->
[ETS Konfiguration](#undoderanzahl-kanaleinstellungen)

<!-- DOC -->
## ODER

Ein ODER-Funktionsblock verfügt über bis zu 9 Eingänge. Der Ausgang gibt EIN aus, wenn mindestens ein Eingang EIN ist.
Zusätzlich können sowohl die Eingänge als auch der Ausgang über die Konfiguration invertiert werden.

<!-- DOCEND -->
[ETS Konfiguration](#undoderanzahl-kanaleinstellungen)

<!-- DOC -->
## Anzahl

Ein Anzahl-Funktionsblock verfügt über bis zu 9 Eingänge. 
Der Ausgang gibt aus, wie viele der (verwendeten) Eingänge den Wert EIN angenommen haben.
Die Eingänge können vor Zählung invertiert werden.

<!-- DOCEND -->
[ETS Konfiguration](#undoderanzahl-kanaleinstellungen)


<!-- DOC -->
## Auswahl (Multiplexer)

Über die Funktion Auswahl kann ein Eingang auf einen Ausgang durchverbunden werden. 
Es stehen 2-8 Eingänge zur Verfügung. 
Die Auswahl welcher Eingang auf den Ausgang geschalten wird, erfolgt über ein Gruppenobjekt.

<!-- DOCEND -->
[ETS Konfigruation](#auswahl-multiplexer-1)

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

<!-- DOCEND -->
[ETS Konfiguration](#prioritätsschalter-1)

<!-- DOC -->
## Statistische Aggregation

Ein Aggregations-Funktionsblock verfügt über bis zu 9 numerische Eingänge, gängiger DPTs. 
Der Ausgangswert wird basierend auf der gewählten Funktion (Summe, Mittelwert, Minimum, Maximum, Spannbreite) berechnet und kann in verschiedenen numerischen DPTs ausgegeben werden.
Es kann beeinflusst werden, wie mit Werten umgegangen wird die vom Ausgatyp nicht dargestellt werden können.

<!-- DOCEND -->
[ETS Konfiguration](#aggregation)

<!-- DOC -->
## Wertüberwachung

Die Wertüberwachung dient zum überwachen von Messwerten oder Signalen. 
Bei zu lange fehlenden Übertragungen, kann ein Ersatzwert auf den Bus gesendet werden.
Ebenfalls können Minimum und Maximumwerte festgelegt werden und bei Bedarf durch einen Ersatzwert ersetzt werden.

<!-- DOCEND -->
[ETS Konfiguration](#wertüberwachung-1)


<!-- DOC -->
## Count-Down Zeitgeber

Der Funktionsblock zählt von eine vorgebenen Zeit herunter.
Die Laufzeit kann über konfiguration oder über den Bus gesteuert werden.
Der Count Down kann pausiert werden.
Es gibt Ausgänge für
 - Verbleibende Zeit
 - Textdartstellung der verbleibenden Zeit mit Einheit
 - Aktiv laufende Zeit
 - Pause aktiv

<!-- DOCEND -->
[ETS Konfiguration](#count-down-zeitgeber-1)
 

<!-- DOC -->
## Blinker

Die Funktion Blinker stellt einen Ausgang für ein Blinklicht bereit.
Die Anzahl der Blinkintervalle ist konfigurierbar und/oder über ein Gruppenobjekt steuerbar.
Die jeweilige Ein- bzw. Ausschaltzeit kann in 10/Sekunden, Sekunden, Minuten oder Stunden festgelegt werden.

<!-- DOCEND -->
[ETS Konfiguration](#blinker-1)

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

- **Anzahl**
  Ein Anzahl-Funktionsblock hat bis zu 9 Eingänge vom Typ EIN/AUS.
  Der Ausgang gibt die Anzahl der Eingänge mit dem Wert EIN aus.

- **Auswahl (Mulitplexer)**
  Über die Funktion Auswahl kann ein Eingang auf einen Ausgang durchverbunden werden. 
  Es stehen 2-8 Eingänge zur Verfügung. 
  Die Auswahl welcher Eingang auf den Ausgang geschalten wird, erfolgt über ein Gruppenobjekt.

- **Prioritätsschalter**
  Ein Prioritätsschalter hat bis zu 9 Eingänge vom Typ EIN/AUS.
  Der Eingang mit der höchsten Priorität der EIN ist, bestimmt den Ausgangswert.


- **Statistische Aggregation**
  Ein Aggregations-Funktionsblock hat bis zu 9 Eingänge mit numerischem Typ.
  Es kann zwischen fünf Funktionen (Summe, Mittelwert, Minimum, Maximum, Spannbreite) zur Berechnung des Ausgangswertes gewählt werden.

- **Wertüberwachung**
  Überwacht einen Eingang und löst einen Alarm bei falschen oder ausbleibenden Werten aus.
  Es können auch Ersatzwerte auf den Bus geschickt werden.

- **Count-Down Zeitgeber**
  Zählt von eine vorgebenen Zeit in herunter.
  Die Laufzeit kann über konfiguration oder über den Bus gesteuert werden.

- **Blinker**
  Die Funktion Blinker stellt einen Ausgang für ein Blinklicht bereit.
  Die Anzahl der Blinkintervalle ist konfigurierbar und/oder über ein Gruppenobjekt steuerbar.
  Die jeweilige Ein- bzw. Ausschaltzeit kann in 10/Sekunden, Sekunden, Minuten oder Stunden festgelegt werden.

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


<!-- DOC HelpContext="Count-Down"-->
## Count-Down Zeitgeber

Der Funktionsblock zählt von eine vorgebenen Zeit herunter.
Die Laufzeit kann über konfiguration oder über den Bus gesteuert werden.
Der Count Down kann pausiert werden.

<!-- DOC -->
### Ablaufzeit

Legt die Zeit für den Count Down Ablauf fest die bei einem Start Befehl verwendet wird.
Hinweis: Die Zeit wird bei Verwendung des Gruppenobjekts 'Start mit Zeit' nicht verwendet.

<!-- DOC -->
### Ablaufzeit Einheit

Legt die Einheit für die Ablaufzeit fest.

Optionen:

- Sekunde(n)
- Minute(n)
- Stunde(n)

<!-- DOCEND-->
### Eingänge

#### Start / Stop

Über diesen Eingang kann der Count-Down gestartet bzw. gestoppt werden.
Der Start erfolgt über ein EIN (1) Telegram.
Der Stopp erfolgt über ein AUS (0) Telegram.

#### Pause / Fortsetzten

Über diesen Eingang kann der Count-Down pausiert bzw. fortgesetzt werden.
Der Pause erfolgt über ein EIN (1) Telegram.
Der Fortsetzten erfolgt über ein AUS (0) Telegram.

<!-- DOC -->
#### Start mit Zeit

Es wird ein Gruppenobjekt eingeblendet das über einen Zahlenwert den Start des Count Down mit Zeitvorgabe ermöglicht.

Mögliche Einstellungen:

- Deaktiviert

- Einheit Sekunden

- Einheit Minuten

- Einheit Stunden
							
Beispiel:

Wenn 'Minuten' eingestellt wird und ein Telegram mit dem Zahlenwert 5 empfangen wird, startet der Count Down mit einer Zeitvorgabe von 5 Minuten

<!-- DOC -->
#### Laufzeit Verringern / Erhöhen

Mithilfe des Guppenobjekts Zeitoffset wird die Lauf-Zeit um dem eingestellten Betrag erhöht bzw. erniedrigt.
Über ein EIN (1) Telegram wird die Laufzeit verringert.
Über ein Aus (2) Telegram wird die Laufzeit erhöht.

Mögliche Einstellungen:

- Deaktiviert

- 1 Sekunde

- 5 Sekunden

- 10 Sekunden

- 15 Sekunden

- 30 Sekunden

- 1 Minute 

- 5 Minuten 

- 10 Minuten 

- 15 Minuten 

- 30 Minuten 

- 1 Stunde

Hinweis: Ist der Count-Down nicht gestartet, wird bei Empfang eines Auf-Befehl (0) der Count-Down mit der entsprechenden Zeit gestartet. 
Die unter 'Ablauf Zeit' konfigurierte Zeit wird dabei nicht verwendet.

Beispiel:

Ist '5 Sekunden' ausgewählt und es wird ein Auf-Befehl (0) empfangen, wird die aktuelle Ablaufzeit um 5 Sekunden verlängert. Bei Emfpang eine Ab-Befehl (1) wird die aktuelle Ablaufzeit um 5 Sekunden verkürzt. 

<!-- DOCEND-->
### Ausgänge

<!-- DOC HelpContext="GroupObjectText"-->
#### Text

Das Gruppenobjekt stellt die Zeit als Text zur bereit.
Über die Konfiguration kann festgelegt werden, ob die verbleibende Zeit (Abwärts laufend) oder die vergangene Zeit (Aufwärts laufend) dargestellt wird.

Mögliche Einstellungen:

- Deaktiviert

- Verbleibend (Zählt abwärts)

- Vergangen (Zählt aufwärts)

Über Textbausteine kann konfiguriert werden, wie der Text dargestellt wird.
In den Textbausteine können Platzhalter verwendet werden um Informationen zur verbleibenden Zeit oder den Laufend/Pausierten Zustand zu visualisieren.

Platzhalter:

- **H2**...Stunden (2 oder mehrstellig)
  Wird kein Platzhalter für Minuten verwendet, werden die Stunden aufgerundet, sonst abgerundet.

- **H1**...Stunden (1 oder mehrstellig)
  Wird kein Platzhalter für Minuten verwendet, werden die Stunden aufgerundet, sonst abgerundet.

- **M2**...Minuten (2 oder mehrstellig)
  Wird kein Platzhalter für Sekunden verwendet, werden die Minuten aufgerundet, sonst abgerundet.

- **M1**...Minuten (1 oder mehrstellig)
  Wird kein Platzhalter für Sekunden verwendet, werden die Minuten aufgerundet, sonst abgerundet.

- **S2**...Sekunden (2 oder mehrstellig)

- **S1**...Sekunden (1 oder mehrstellig)

- **SX**...10 Sekunden (2 oder mehrstellig)
  Die Sekunden werden auf die nächsten vollen 10 Sekunden aufgerundet.

- **$**....Läuft / Pause Textbautstein" 

Es wrid empfohlen den Platzhalter **S1** und **S2** nur in Sonderfällen zu verwenden, da in dem Fall der Text alle Sekunden über den KNX-Bus geschickt wird und zu einer hohen Buslast führt. Besser ist stattdessen den Platzhalter *SX* zu verwenden da der nur alle 10 Sekunden eine aktualisiert durchführt.

<!-- DOC HelpContext="TemplatePause" -->
#### Pause

Das Konfigurierte Zeichen wird im Gruppenobjekt 'Text' als kennzeichen für einen pausierten Count-Down verwendet.
Das Pauszeichen wird im Platzhalter **$** eingesetzt.

<!-- DOC HelpContext="TemplateLaeuft" -->
#### Läuft

Das Konfigurierte Zeichen wird im Gruppenobjekt 'Text' als kennzeichen für einen pausierten Count-Down verwendet.
Das Pauszeichen wird im Platzhalter **$** eingesetzt.

<!-- DOC HelpContext="Template" -->
#### Standard

Standard Text Formatierung.

Hinweis: durch Verwendung des Sekundenplatzhalters wird der KNX Bus start belastet, da jede Sekunde der aktualisierte Text übertragen wird.

Beispiele: 

"H2:M2 $" gibt bei laufenden Zeitgeber mit einer Restlaufzeit von 3 Stunden und 15 Minuten "03:15 *" aus.
"M2 Minuten $" gibt bei laufenden Zeitgeber mit einer Restlaufzeit von 3 Stunden und 15 Minuten "195 Minuten *" aus.

<!-- DOC HelpContext="Template1h" -->
#### Kleiner 1 Stunde

Die Testformartierung wird verwendet um den Text für eine Restlaufzeit kleiner 1 Stunde auszugeben.

Hinweis: durch Verwendung des Sekundenplatzhalters wird der KNX Bus start belastet, da jede Sekunde der aktualisierte Text übertragen wird.

Beispiele: 

"M1 Minuten $" gibt bei laufenden Zeitgeber mit einer Restlaufzeit von 6 Minuten 30 Sekunden "7 Minuten *" aus. Da kein Sekunden Platzhalter verwendet wurde, werden die Minuten aufgerundet.

"M1:SX $" gibt bei laufenden Zeitgeber mit einer Restlaufzeit von 6 Minuten 31 Sekunden "6:40 *" aus. Da ein Sekunden Platzhalter verwendet wurde, werden die Minute abgerundet. Der Platzhalter **SX** rundet immer auf die nächsten vollen 10 Sekunden auf.

<!-- DOC HelpContext="Template1m" -->
#### Kleiner 1 Minute

Die Testformartierung wird verwendet um den Text für eine Restlaufzeit kleiner 1 Minute auszugeben.

Beispiel: "SX Sekunden $" gibt bei laufenden Zeitgeber mit einer Restlaufzeit von 6 Sekunden (bei **SX** wird aufgerundet) "10 Sekunden *" aus.

<!-- DOC HelpContext="TemplateEnde" -->
#### Ende

Text der nach Ablauf der Zeit angezeigt wird. 
Eventuell verwendete Platzhalter für Stunden, Minuten und Sekunden werden mit 0 bzw. 00 ausgegeben.


<!-- DOC HelpContext="GroupObjectCounter" -->
#### Zähler Verbleibend / Vergangen

Das Gruppenobjekt stellt einen Zähler bereit. 
Achtung: Der maximalwert des Zählers ist mit 255 begrenzt. 
Die Einheit muss so gewählt werden, dass sie mit der maximalen Laufzeit abbildbar ist.

Mögliche Einstellungen:

- Deaktiviert

- Verbleibend Sekunden (Zählt abwärts)

- Verbleibend Minuten (Zählt abwärts) 

- Verbleibend Stunden (Zählt abwärts)

- Vergangen Sekunden (Zählt aufwärts)

- Vergangen Minuten (Zählt aufwärts)

- Vergangen Stunden (Zählt aufwärts)

<!-- DOC HelpContext="GroupObjectTrigger" -->
### Auslöser / Ende

Das Gruppenobjekt Trigger kann verwendet werden um ein Signal am Ende der Laufzeit des Count-Down Zeitgebers zu erzeugen.

Mögliche Einstellungen:

- Deaktiviert       

- Nur EIN     

- Ein für 1 Sekunde

- Ein für 2 Sekunden

- Ein für 5 Sekunden 

- Ein für 10 Sekunden

- Ein für 20 Sekunden

- Ein für 30 Sekunden

- Ein für 1 Minute 

**Nur EIN** sendet am Ende der Laufzeit ein Trigger (1) Telegram. Die anderen Einstellungen senden am Ende ein EIN (1) Telegram und nach Ablauf der Zeit ein AUS (2) Telegram.

Hinweis: Wird der Zeitgeber erneut gestartet bevor die eingestellte Zeit erreicht wurde, wird sofort ein AUS (0) Telegram gesendet.

<!-- DOC HelpContext="Monitoring" -->
## Wertüberwachtung

Die Wertüberwachung dient zum Überwachen von Messwerten oder Signalen. 
Bei zu lange fehlenden Übertragungen, kann ein Ersatzwert auf den Bus gesendet werden.
Ebenfalls können Minimum und Maximumwerte festgelegt werden und bei Bedarf durch einen Ersatzwert ersetzt werden.

Anwendungsbeispiel:
Ein Temperatursensor hat einen Defekt und liefert keine oder nur 0 Werte. 
In diesem Fall kann ein Ersatzwert auf den Bus gesendet werden, damit die Heizungsteuerung in einen Notbetrieb weiter arbeitet.

<!-- DOC -->
### Werttype

Die Type des zu überwachenden Wertes.

Zur Auswahl stehen:

- 1.*           1-Bit (0/1)              
- 5.*           8-Bit vorzeichenlos     
- 5.001       Prozent (0..100%)          
- 6.*           8-Bit vorzeichenbehaftet
- 7.*           2-Byte vorzeichenlos     
- 8.*           2-Byte vorzeichenbehaftet
- 9.*           2-Byte Gleitkommawert    
- 12.*         4-Byte vorzeichenlos      
- 13.*         4-Byte vorzeichenbehaftet 
- 14.*         4-Byte Gleitkommawert     

<!-- DOC HelpContext="Zeitüberwachung aktiv" -->
### Zeitueberwachung (Watchdog)

Die Überwachung erkennt das Ausbleiben von Werten am Eingang.


<!-- DOC HelpContext="Watchdog-Zeit"-->
#### Wartezeit auf Telegramme

Gibt an wie lange am Eingang kein Wert empfangen wird, bis die Zeitüberwachung Alarm gibt.

<!-- DOC HelpContext="Watchdog-Zeitbasis"-->
#### Einheit für die Wartezeit

Folgende Einheiten können für die Wartezeit gewählt werden:

- Minute(n)
- Stunde(n)

<!-- DOC -->
### Verhalten bei Zeitüberschreitung

Definiert die Reaktion(en), die erfolgen soll(en), 
wenn innerhalb des eingestellten Zeitraums kein Eingangstelegramm empfangen wurde: 

- **Nur Alarm auslösen**
  Sendet 1 ("Alarm") über das KO *Zeitüberschreitung*. Es erfolgt keine Korrektur des Eingangswertes.
- **Leseanforderung, dann Alarm**
  Sendet zunächst eine Leseanforderung für den Eingangswert.
  Falls nach 10 Sekunden keine Antwort eingegangen ist, wird 1 ("Alarm") über das KO *Zeitüberschreitung* gesendet.
- **Leseanforderung, dann Ersatzwert und Alarm**
  Sendet zunächst eine Leseanforderung für den Eingangswert.
  Falls nach 10 Sekunden keine Antwort eingegangen ist, wird 1 ("Alarm") über das KO *Zeitüberschreitung* 
  und der Ersatzwert gesendet.
- **Ersatzwert und Alarm**
  Sendet sofort 1 ("Alarm") über das KO *Zeitüberschreitung* und den Ersatzwert.

*Hinweis zum Alarm:*
Zusammen mit dem KO *Zeitüberschreitung* erfolgt auch eine Aktualisierung des KO *Summenalarm*.
Falls sich eine Wertänderung ergibt, wird der neue Wert gesendet.

<!-- DOC -->
### Ersatzwert

Wert der bei fehlendem Wert auf den Bus gesendet werden soll. 
Der Wert wird auf den Ausgang gesendet und nicht auf den Eingang. 

Soll der Ersatzwert auf die Gruppenadresse des Eingangs verwendet werden, muss "Ersatzwerte auf Eingang senden" gewählt werden, ansonsten werden die Ersatzwerte als neuer Eingangswert erkannt und der Alarm rückgesetzt.

<!-- DOC HelpContext="Verhalten bei Wertunterschreitung"  -->
### Minimalwert Überwachung

Option was bei Unterschreiten des minimalen Wertes passieren soll.

#### Verhalten bei Wertunterschreitung

Folgende Optionen stehen zur Auswahl:

- **Überwachung deaktiviert** 
- **Nichts senden**
- **letzten gültiger Wert senden**
- **Grenzwert senden** 

<!-- DOC -->
### Minimaler zulässiger Wert

Minimaler Grenzwert für die Überwachung.

<!-- DOC HelpContext="Verhalten bei Wertüberschreitung" -->
### Maximalwert Überwachung

Option was bei Überschreiten des maximalen Wertes passieren soll.

#### Verhalten bei Wertüberschreitung

Folgende Optionen stehen zur Auswahl:

- **Überwachung deaktiviert** 
- **Nichts senden**
- **letzten gültiger Wert senden**
- **Grenzwert senden** 

<!-- DOC -->
###  Maximaler zulässiger Wert

Minimaler Grenzwert für die Überwachung.

<!-- DOC HelpContext="Ersatzwertbehandlung" -->
### Sendeverhalten

Gibt an, ob die Ersatzwerte auf den Eingang ausgegeben werden sollen, oder ob ein getrenntes Ausgangsobjekt zur Verfügung steht.

Optionen:

- **Ersatzwerte auf Eingang senden**
  Die Ersatzwerte werden auf die am Eingang angeschlossen Gruppenadresse zurückgeschrieben.
  Hinweis: Das führt dazu, das bei Minimal- oder Maximalwertüberschreitung am Bus unmittelbar nach Empfang des Wertes ein korriegierter Wert gesendet wird. 
- **Getrenntes Ausgangsobjekt, nur gültige Werte**
  Am Ausgang werden nur gültige Eingangswerte weitergeleitet.
  Hinweis: Eingestellte Ersatzwerte werden ignoriert.
- **Getrenntes Ausgangsobjekt, gültige und Ersatzwerte**
  Am Ausgang werden alle gültigen Eingangswerte gesendet und im Fehlerfall so eingestellt, Ersatzwerte auf den Bus gesendet.
- **Getrenntes Ausgangsobjekt, nur Ersatzwerte**
  Es werden nur eingestellte Ersatzwerte auf den Ausgang gesendet.

<!-- DOC HelpContext="Selection" -->
## Auswahl (Multiplexer)

<!-- DOC -->
### Datentype

<!-- DOC -->
### Anzahl und Typ der Auswahlen mit gemeinsamen Auswahl Eingang

<!-- DOC -->
### Bei Umschaltung
 
<!-- DOC -->
### Auswahl Status Objekt
  
<!-- DOC -->
## Blinker

<!-- DOC -->
### Anzahl der Blinkvorgänge

<!-- DOC -->
### Ein-Zeit

<!-- DOC HelpContext="Blinker-EIN-Zeit" -->
### Zeit
 
<!-- DOC HelpContext="Blinker-EIN-Zeitbasis" -->
### Einheit 
 

<!-- DOC -->
### Aus-Zeit

<!-- DOC HelpContext="Blinker-AUS-Zeit" -->
### Zeit
 
<!-- DOC HelpContext="Blinker-AUS-Zeitbasis" -->
### Einheit 

<!-- DOC -->
### Start

<!-- DOC -->
### Ende

<!-- DOC -->
### AUS Telegram am Start Eingang
 

<!-- DOC -->
### Ausgang

<!-- DOC -->
### Wert für EIN

<!-- DOC -->
### Wert für AUS


