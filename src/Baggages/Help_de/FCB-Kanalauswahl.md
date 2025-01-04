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
  Zählt von einer vorgegebenen Zeit in herunter.
  Die Laufzeit kann über konfiguration oder über den Bus gesteuert werden.

- **Blinker**
  Die Funktion Blinker stellt einen Ausgang für ein Blinklicht bereit.
  Die Anzahl der Blinkintervalle ist konfigurierbar und/oder über ein Gruppenobjekt steuerbar.
  Die jeweilige Ein- bzw. Ausschaltzeit kann in 10/Sekunden, Sekunden, Minuten oder Stunden festgelegt werden.

