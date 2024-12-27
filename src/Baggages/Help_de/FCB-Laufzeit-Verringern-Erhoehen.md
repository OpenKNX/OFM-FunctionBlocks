### Laufzeit Verringern / Erhöhen

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

