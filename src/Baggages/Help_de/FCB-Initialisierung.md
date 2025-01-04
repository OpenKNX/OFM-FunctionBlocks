### Initialisierung

Legt den Initialwert für den Eingang fest.
Zur Auswahl stehen:

- **AUS**  
  Der Eingang wird mit AUS vorbelegt
- **EIN**  
  Der Eingang wird mit EIN vorbelegt
- **Vom Bus lesen, dann AUS**  
  Es wird versucht den Eingangswert vom Bus über ein Lesetelegramm zu lesen. 
  Wird nach 3 Sekunden keine Antwort empfangen, wird der Eingang mit AUS vorbelegt.
- **Vom Bus lesen, dann EIN**  
  Es wird versucht den Eingangswert vom Bus über ein Lesetelegramm zu lesen. 
  Wird nach 3 Sekunden keine Antwort empfangen, wird der Eingang mit EIN vorbelegt.

**Wichtig**: Die Vorbelegung erfolgt vor einer möglichen eingestellten Invertierung des Eingangswertes.
Das bedeutet das bei einer Vorbelegung von "AUS" und einer eingestellten Invertierung der Wert als EIN von der Logik interpretiert wird.

