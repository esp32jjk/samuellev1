# MediConnect - Système de Gestion Médicale sur ESP32

## Prérequis

### 1. Installation de l'IDE Arduino
1. Télécharger et installer l'IDE Arduino depuis [arduino.cc](https://www.arduino.cc/en/software)
2. Version recommandée : 1.8.x ou supérieure

### 2. Configuration de l'ESP32 dans l'IDE Arduino
1. Ouvrir l'IDE Arduino
2. Aller dans "Fichier > Préférences"
3. Dans "URLs additionnelles de gestionnaires de cartes", ajouter :
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Cliquer sur "OK"
5. Aller dans "Outils > Type de carte > Gestionnaire de cartes"
6. Rechercher "ESP32"
7. Installer "ESP32 by Espressif Systems"

### 3. Installation des bibliothèques requises
Dans l'IDE Arduino, aller dans "Croquis > Inclure une bibliothèque > Gérer les bibliothèques" et installer :
- ESPAsyncWebServer
- AsyncTCP
- WiFiManager
- SPIFFS (pour ESP32)

### 4. Installation de l'outil ESP32 Sketch Data Upload
1. Aller dans "Outils > Gérer les bibliothèques"
2. Rechercher "ESP32 Sketch Data Upload"
3. Installer la bibliothèque

## Configuration du Projet

### 1. Préparation des fichiers
1. Créer un dossier `data` dans votre projet
2. Copier tous les fichiers web dans ce dossier :
   ```
   votre_projet/
   ├── data/
   │   ├── login.html
   │   ├── login.css
   │   ├── auth.js
   │   ├── doctor.html
   │   ├── doctor.css
   │   ├── nurse.html
   │   └── nurse.css
   └── mainSamy.ino
   ```

### 2. Téléversement des fichiers
1. Connecter l'ESP32 à votre ordinateur
2. Dans l'IDE Arduino :
   - Sélectionner la bonne carte (Tools > Board > ESP32 Arduino > ESP32 Dev Module)
   - Sélectionner le bon port (Tools > Port > COM[X])
3. Téléverser les fichiers web :
   - Aller dans "Outils > ESP32 Sketch Data Upload"
   - Attendre la fin du téléversement

### 3. Configuration WiFi
1. Téléverser le code principal (mainSamy.ino)
2. Redémarrer l'ESP32
3. Un point d'accès WiFi nommé "MediConnect_Config" sera créé
4. Se connecter à ce réseau avec le mot de passe : "12345678"
5. Un portail captif s'ouvrira automatiquement
6. Sélectionner votre réseau WiFi et entrer le mot de passe
7. L'ESP32 se connectera automatiquement et redémarrera

### 4. Accès à l'interface
1. Noter l'adresse IP affichée dans le moniteur série
2. Ouvrir un navigateur et accéder à cette adresse IP
3. L'interface de connexion devrait s'afficher

## Dépannage

### Si le portail captif ne s'ouvre pas
1. Vérifier que vous êtes bien connecté au réseau "MediConnect_Config"
2. Essayer d'accéder à http://192.168.4.1 manuellement
3. Redémarrer l'ESP32 si nécessaire

### Si les fichiers web ne s'affichent pas
1. Vérifier que le téléversement des données a réussi
2. Vérifier les messages d'erreur dans le moniteur série
3. Réessayer le téléversement des données

### Si la connexion WiFi échoue
1. Vérifier que le réseau WiFi est à portée
2. Vérifier les identifiants WiFi
3. Redémarrer l'ESP32 pour relancer le portail de configuration

## Notes importantes
- La première configuration peut prendre jusqu'à 3 minutes
- Les identifiants WiFi sont sauvegardés en mémoire
- En cas de perte de connexion, l'ESP32 tentera de se reconnecter automatiquement
- Pour réinitialiser la configuration WiFi, maintenir le bouton de reset pendant 10 secondes
- L'ESP32 offre plus de mémoire et de puissance que l'ESP8266, ce qui permet une meilleure performance
