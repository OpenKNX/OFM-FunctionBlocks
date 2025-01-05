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

