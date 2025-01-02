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

- **Count-Down Zeitgeber**
  Zählt von eine vorgebenen Zeit in herunter.
  Die Laufzeit kann über konfiguration oder über den Bus gesteuert werden.

- **Wertüberwachung**
  Überwacht einen Eingang und löst einen Alarm bei falschen oder ausbleibenden Werten aus.
  Es können auch Ersatzwerte auf den Bus geschickt werden.

