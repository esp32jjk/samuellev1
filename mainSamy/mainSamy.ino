#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <WiFiManager.h>
#include <AsyncTCP.h>

// Configuration du serveur web
AsyncWebServer server(80);

// Configuration WiFiManager
const char* WIFI_AP_NAME = "MediConnect_Config";
const char* WIFI_AP_PASSWORD = "12345678";
const int WM_CONFIG_TIMEOUT = 180; // 3 minutes

// Callback pour le portail captif
void configModeCallback(WiFiManager *myWiFiManager) {
    Serial.println("[WiFiManager] Portail Captif démarré");
    Serial.println("[WiFiManager] SSID: " + String(WIFI_AP_NAME));
    Serial.println("[WiFiManager] Mot de passe: " + String(WIFI_AP_PASSWORD));
    Serial.println("[WiFiManager] URL: http://192.168.4.1");
}

void setupWiFi() {
    WiFiManager wm;
    
    // Configuration du WiFiManager
    wm.setAPCallback(configModeCallback);
    wm.setConfigPortalTimeout(WM_CONFIG_TIMEOUT);
    wm.setDebugOutput(true);
    
    // Tentative de connexion automatique
    bool res = wm.autoConnect(WIFI_AP_NAME, WIFI_AP_PASSWORD);
    
    if (!res) {
        Serial.println("[WiFi] ❌ Échec de connexion");
        Serial.println("[WiFi] Redémarrage...");
        delay(2000);
        ESP.restart();
    }
    
    Serial.println("[WiFi] ✅ Connecté !");
    Serial.println("[WiFi] IP: " + WiFi.localIP().toString());
}

void setup() {
    Serial.begin(115200);
    
    // Initialisation SPIFFS
    if (!SPIFFS.begin(true)) {
        Serial.println("Erreur de montage SPIFFS");
        return;
    }
    
    // Configuration WiFi
    setupWiFi();
    
    // Configuration du serveur web
    server.serveStatic("/", SPIFFS, "/");
    
    // Gestion de la racine
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/login.html", "text/html");
    });
    
    // Démarrage du serveur
    server.begin();
    Serial.println("Serveur démarré");
}

void loop() {
    // Vérification de la connexion WiFi
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Perte de connexion WiFi, redémarrage...");
        delay(2000);
        ESP.restart();
    }
}