#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// ------ Einstellungen für das Setup-WLAN (AP) ------
const char* AP_SSID = "ESP32-Setup";
const char* AP_PASS = "12345678";   // min. 8 Zeichen

// Einfacher HTTP-Server
WebServer server(80);

// HTML-Seite (Formular)
const char HTML_INDEX[] PROGMEM = R"HTML(
<!DOCTYPE html><html lang="de"><meta charset="utf-8">
<title>ESP32 WLAN Setup</title>
<style>body{font-family:sans-serif;margin:2rem}input{padding:.5rem;margin:.3rem 0;width:100%}button{padding:.6rem 1rem}</style>
<h2>WLAN verbinden</h2>
<form method="POST" action="/connect">
  <label>SSID</label><br>
  <input name="ssid" placeholder="WLAN-Name" required><br>
  <label>Passwort</label><br>
  <input name="pass" type="password" placeholder="WLAN-Passwort"><br><br>
  <button type="submit">Verbinden</button>
</form>
<p>Diese Seite erreichst du unter <b>http://192.168.4.1</b></p>
)HTML";

// Handler: Startseite
void handleRoot() {
  server.send(200, "text/html", HTML_INDEX);
}

// Handler: Verbindung herstellen
void handleConnect() {
  String ssid = server.arg("ssid");
  String pass = server.arg("pass");

  // Kurze Antwortseite anzeigen (Ladebildschirm)
  server.send(200, "text/html",
              "<html><meta charset='utf-8'><body>"
              "<h3>Verbinde mit WLAN...</h3>"
              "<p>SSID: " + ssid + "</p>"
              "<p>Bitte 5–10 Sekunden warten.</p>"
              "</body></html>");

  // STA-Modus und Verbindung versuchen
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid.c_str(), pass.c_str());

  unsigned long start = millis();
  const unsigned long timeout = 15000; // 15s warten

  while (WiFi.status() != WL_CONNECTED && millis() - start < timeout) {
    delay(250);
  }

  // Ergebnis ausgeben
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Verbunden mit: " + ssid);
    Serial.print("IP im Heimnetz: "); Serial.println(WiFi.localIP());

    // Optional: AP schließen, damit nur noch Heimnetz genutzt wird
    WiFi.softAPdisconnect(true);

  } else {
    Serial.println("Verbindung fehlgeschlagen.");
  }
}

void setup() {
  Serial.begin(9600);
  delay(200);

  // Eigenes WLAN starten (Access Point)
  WiFi.mode(WIFI_AP);
  bool ok = WiFi.softAP(AP_SSID, AP_PASS);
  IPAddress apIP = WiFi.softAPIP();
  Serial.println(ok ? "AP gestartet." : "AP-Start FEHLER!");
  Serial.print("AP SSID: "); Serial.println(AP_SSID);
  Serial.print("AP IP:   "); Serial.println(apIP); // -> 192.168.4.1

  // Routen registrieren
  server.on("/", handleRoot);
  server.on("/connect", HTTP_POST, handleConnect);
  server.onNotFound([](){ server.send(200, "text/html", HTML_INDEX); });

  // Server starten
  server.begin();
  Serial.println("HTTP-Server bereit.");
}

void loop() {
  // Anfragen bearbeiten
  server.handleClient();
}
