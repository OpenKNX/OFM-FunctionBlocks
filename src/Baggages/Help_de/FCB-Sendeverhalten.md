### Sendeverhalten

Zur Auswahl stehen:

- **Bei jedem Eingangstelegramm**  
  Wenn einer der Eingänge ein Telegramm empfängt, wird der Ausgangswert auf den Bus gesendet. 
  Diese Einstellung kann zu hintereinderfolgenden gleichen Ausgangswerten am Bus führen.

- **Nur bei Änderung des Ausgangswertes**  
  Der Ausgang wird nur dann auf den Bus gesendet, wenn sich durch die berechnete Logikfunktion der Wert ändert.


Unabhängig von der Einstellung wird der Ausgangswert auch nach der Initialisierungsphase inklusive eventueller Wartezeit für Leseanforderungs-Antworten einmalig auf den Bus gesendet.

