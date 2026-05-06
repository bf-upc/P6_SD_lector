# 📁 LECTOR SD INTERACTIU (ESP32)

Aquest projecte implementa un sistema per llegir fitxers i llistar el contingut d'una targeta SD utilitzant un ESP32 i comunicació pel Monitor Sèrie. A diferència d'altres versions, aquest codi està enfocat exclusivament a la lectura i exploració, incloent detalls com la mida dels fitxers i l'espai total de la targeta.

Permet:
- Llegir fitxers
- Llistar contingut amb mida (bytes)
- Obtenir la capacitat de la SD (MB)

Tot es controla mitjançant comandes enviades pel monitor sèrie. 

---

## ⚙️ Connexions SPI

Configura els pins SPI de la següent manera:

| Senyal | Pin ESP32 |
|--------|----------|
| SCK    | 36       |
| MISO   | 37       |
| MOSI   | 35       |
| CS     | 39       |

---

## 🚀 Inicialització

Quan s'inicia el dispositiu:
1. Es configura la comunicació sèrie (115200 bauds)
2. S'inicialitza el bus SPI
3. Es comprova i s'inicia la targeta SD
4. Es mostra la mida total de la SD
5. Es fa un llistat automàtic dels fitxers inicials

Si tot funciona correctament:

✅ OK!
📊 Tamany SD: XXX MB

---

## 💻 Comandes disponibles

Aquest programa funciona amb un sistema de comandes més natural (separades per espais). Les comandes s'envien des del Monitor Sèrie:

### 📖 Llegir un fitxer

llegir NOMFITXER.txt

Exemple:
llegir dades.txt

---

### 📁 Llistar fitxers

llistar

Mostra tots els fitxers presents a la targeta SD i la seva mida en bytes.

---

### ❓ Ajuda

ajuda

Mostra un menú ràpid amb les comandes que pots utilitzar.

---

## 🧠 Funcionament del codi

El programa es basa en:

- setup()
  - Inicialitza Serial i SPI
  - Detecta i calcula la mida de la targeta SD
  - Llista els fitxers automàticament a l'inici

- loop()
  - Comprova constantment si la SD està inicialitzada (`sdInicialitzada`)
  - Llegeix comandes des del Serial i les analitza usant espais en lloc de comes
  - Interpreta i executa les accions corresponents

---

## 🔧 Funcions principals

- llistarFitxers()
- llegirFitxer(nom)
- mostrarAjuda()

---

## ⚠️ Notes importants

- Els noms de fitxer es guarden amb "/" automàticament si no s'indica
- Si hi ha un error al llegir un fitxer, el programa et suggerirà revisar-ne el nom
- Cal que la targeta SD estigui correctament formatejada (FAT32 recomanat)

---

## 🛠️ Requisits

- ESP32
- Mòdul targeta SD
- Llibreries:
  - SPI.h
  - SD.h

---

## 📌 Possibles millores

- Afegir suport per visualitzar fitxers en formats específics (CSV, JSON)
- Paginació per a fitxers de text molt llargs
- Sistema per navegar entre subcarpetes

---

## 👨‍💻 Autor

Projecte educatiu per a pràctiques amb ESP32 i exploració de sistemes de fitxers.
