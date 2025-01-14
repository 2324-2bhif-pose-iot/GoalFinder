# Schritt-für-Schritt-Anleitung: Firmware mit PlatformIO hochladen

## **Schritt 1:** Python installieren
Laden Sie sich die neueste Python-Version herunter. Falls Sie dies noch nicht getan haben, drücken sie hier -> [Microsoft Store](https://apps.microsoft.com/detail/9pjpw5ldxlz5?hl=de-de&gl=US)

---

## **Schritt 2:** PlatformIO Installer-Skript herunterladen
Laden Sie das PlatformIO Installer-Skript herunter, indem Sie diesen Link verwenden:  
[PlatformIO Installer-Skript](https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py).

---

## **Schritt 3:** PlatformIO Installer ausführen
1. Navigieren Sie im Terminal (CMD oder PowerShell) zu dem Verzeichnis, in dem sich das heruntergeladene Skript befindet.
2. Führen Sie den folgenden Befehl aus, um den Installer zu starten:
   ```bash
   python get-platformio.py

---

## **Schritt 4:** PlatformIO verwenden, um die Firmware hochzuladen
Je nachdem, ob Sie die Eingabeaufforderung (CMD) oder PowerShell verwenden, folgen Sie den entsprechenden Anweisungen:

### **Option A: PowerShell**
1. Öffnen Sie PowerShell.
2. Führen Sie den folgenden Befehl aus:
   ```bashq
   ~/.platformio/penv/scripts/platformio.exe run --target upload


### **Option B: Eingabeaufforderung**
1. Öffnen Sie CMD (Eingabeaufforderung).
2. Führen Sie den folgenden Befehl aus:
   ```bash
    %userprofile%\.platformio\penv\scripts\platformio.exe run --target upload

