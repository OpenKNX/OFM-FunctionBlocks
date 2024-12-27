### Text

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

