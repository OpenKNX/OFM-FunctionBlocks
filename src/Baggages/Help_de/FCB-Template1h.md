### Kleiner 1 Stunde

Die Testformatierung wird verwendet, um den Text für eine Restlaufzeit kleiner 1 Stunde auszugeben.

Hinweis: durch Verwendung des Sekundenplatzhalters wird der KNX Bus start belastet, da jede Sekunde der aktualisierte Text übertragen wird.

Beispiele: 

"M1 Minuten $" gibt bei laufenden Zeitgeber mit einer Restlaufzeit von 6 Minuten 30 Sekunden "7 Minuten *" aus. Da kein Sekunden Platzhalter verwendet wurde, werden die Minuten aufgerundet.

"M1:SX $" gibt bei laufenden Zeitgeber mit einer Restlaufzeit von 6 Minuten 31 Sekunden "6:40 *" aus. Da ein Sekunden Platzhalter verwendet wurde, werden die Minute abgerundet. Der Platzhalter **SX** rundet immer auf die nächsten vollen 10 Sekunden auf.

