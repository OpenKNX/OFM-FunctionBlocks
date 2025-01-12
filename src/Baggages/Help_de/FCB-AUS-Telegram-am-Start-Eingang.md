### AUS Telegram am Start Eingang

Gibt an ob und wie ein Blinkvorgang durch eine AUS Telegram am Start Eingang beendet werden kann.

- **Ignorieren**
  AUS-Telegramme am Eingang oder 0 am Eingang zum Starten mit Anzahl werden ignoriert.
- **Blinken sofort beenden und EIN senden**
  Das Blinken wird beendet und der Ausgang wir eingeschalten
- **Blinken sofort beenden und AUS senden**
  Das Blinken wird beendet und der Ausgang wir ausgeschalten
- **Blinken sofort beenden, Zustand vor Blink-Beginn herstellen**
  Das Blinken wird beendet und der Zustand vor dem Blinken wird wieder hergestellt. 
  Wird der Prozent Datentype verwendet kann dies auch ein Wert ungleich der definierten Werte für EIN und AUS sein.
- **Blinken sofort beenden, Zustand umgekehrt wie vor Blink-Beginn herstellen**
  War vor dem Blinken der Aktor eingeschalten, wird der nach dem Blinken ausgeschalten.
  War vor dem Blinken der Aktor ausgeschalten, wird der nach dem Blinken eingeschalten.
- Mit aktuellen Zustand beenden (Kein Telegram senden)**
  Das Blinken wird beendet ohne ein Abschlusstelegram zu senden.
							

