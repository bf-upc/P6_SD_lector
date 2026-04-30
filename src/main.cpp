#include <SPI.h>
#include <SD.h>

#define SD_SCK  36
#define SD_MISO 37
#define SD_MOSI 35
#define SD_CS   39

String nomFitxer = "";
boolean sdInicialitzada = false;


void llistarFitxers() {
  Serial.println("\n📁 LLISTAT DE FITXERS:");
  Serial.println("-----------------------------------");
  
  File root = SD.open("/");
  if (!root) {
    Serial.println("❌ Error obrint el directori arrel");
    return;
  }
  
  File file = root.openNextFile();
  int comptador = 0;
  
  while (file) {
    comptador++;
    Serial.print("  📄 ");
    Serial.print(file.name());
    
    // Mostrem tamany
    Serial.print(" (");
    Serial.print(file.size());
    Serial.println(" bytes)");
    
    file = root.openNextFile();
  }
  
  if (comptador == 0) {
    Serial.println("  ❌ No hi ha fitxers a la targeta SD");
  } else {
    Serial.println("-----------------------------------");
    Serial.print("  Total: ");
    Serial.print(comptador);
    Serial.println(" fitxers");
  }
  
  Serial.println();
}

void llegirFitxer(String nom) {
  Serial.print("\n📖 Llegint fitxer: ");
  Serial.println(nom);
  Serial.println("-----------------------------------");
  
  // Assegurem que comença amb barra
  if (!nom.startsWith("/")) {
    nom = "/" + nom;
  }
  
  File myFile = SD.open(nom.c_str());
  
  if (myFile) {
    Serial.println("✅ Fitxer obert correctament!");
    Serial.println("\n📝 CONTINGUT:");
    Serial.println("-----------------------------------");
    
    // Llegim i mostrem tot el contingut
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    
    Serial.println("\n-----------------------------------");
    Serial.print("✅ Lectura finalitzada (");
    Serial.print(myFile.position());
    Serial.println(" bytes llegits)");
    
    myFile.close();
  } else {
    Serial.println("❌ ERROR: No s'ha pogut obrir el fitxer");
    Serial.println("   Comprova que el nom es correcte");
    Serial.println("   Exemple: llegir archivo.txt");
  }
  
  Serial.println();
}

void mostrarAjuda() {
  Serial.println("\n=================================");
  Serial.println("COMANDES DISPONIBLES:");
  Serial.println("  - 'llistar'                  -> Mostra tots els fitxers");
  Serial.println("  - 'llegir NOMFITXER.txt'     -> Llegeix un fitxer");
  Serial.println("  - 'ajuda'                    -> Mostra aquest menu");
  Serial.println("=================================\n");
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  
  Serial.println("\n\n=================================");
  Serial.println("   LECTOR SD INTERACTIU");
  Serial.println("=================================");
  
  SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  
  Serial.print("Iniciant targeta SD... ");
  if (!SD.begin(SD_CS, SPI)) {
    Serial.println("ERROR!");
    Serial.println("❌ No s'ha pogut inicialitzar la SD");
    Serial.println("   Comprova que hi ha una targeta SD inserida");
    sdInicialitzada = false;
    return;
  }
  
  Serial.println("✅ OK!");
  sdInicialitzada = true;
  
  // Mostrem informacio
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.print("📊 Tamany SD: ");
  Serial.print(cardSize);
  Serial.println(" MB");
  
  Serial.println("\n=================================");
  Serial.println("INSTRUCCIONS:");
  Serial.println("  - Escriu 'llistar' per veure tots els fitxers");
  Serial.println("  - Escriu 'llegir nomfitxer.txt' per llegir un fitxer");
  Serial.println("  - Escriu 'ajuda' per mostrar aquest menu");
  Serial.println("=================================\n");
  
  // Llistem fitxers automaticament
  llistarFitxers();
}

void loop() {
  if (!sdInicialitzada) {
    delay(1000);
    return;
  }
  
  if (Serial.available() > 0) {
    String comanda = Serial.readStringUntil('\n');
    comanda.trim();
    
    if (comanda == "llistar") {
      llistarFitxers();
    }
    else if (comanda == "ajuda") {
      mostrarAjuda();
    }
    else if (comanda.startsWith("llegir ")) {
      String nomFitxer = comanda.substring(7);
      nomFitxer.trim();
      llegirFitxer(nomFitxer);
    }
    else if (comanda.length() > 0) {
      Serial.print("❌ Comanda desconeguda: ");
      Serial.println(comanda);
      Serial.println("Escriu 'ajuda' per veure les comandes disponibles");
    }
  }
  
  delay(50);
}
