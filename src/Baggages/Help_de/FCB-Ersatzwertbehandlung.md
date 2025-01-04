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
