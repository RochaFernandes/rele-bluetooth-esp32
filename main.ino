#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

String meuMAC = "23:06:22:80:06:14";


int rele = 5;
const unsigned long tempoDesligamento = 30000; // 10 segundos
unsigned long ultimaDeteccao= 0;

void setup() {
  // Inicia a comunicação serial com velocidade de 115200 bps (bits por segundo)
  Serial.begin(115200);
  // Inicializa o módulo Bluetooth do ESP32 no modo cliente (somente escaneia, não se conecta)
  BLEDevice::init("");
  //Configura a GPIO com saída
  pinMode(rele, OUTPUT);
  //Inicializa com o relé ligado
  digitalWrite(rele, LOW);
}

void loop() {
  // Cria um objeto scanner para detectar dispositivos BLE próximos
  BLEScan* scanner = BLEDevice::getScan();

  // Ativa o modo de escaneamento ativo (coleta mais informações dos dispositivos)
  scanner->setActiveScan(true);

  // Executa o escaneamento por 5 segundos e armazena os resultados em um ponteiro
  BLEScanResults* resultado = scanner->start(5, false);

  bool encontrado = false;
  String macAtual = "";

  // Percorre todos os dispositivos encontrados
  for (int i = 0; i < resultado->getCount(); i++) {
    BLEAdvertisedDevice d = resultado->getDevice(i);
    macAtual = d.getAddress().toString().c_str();
    // Verifica se o dispositivo é o desejado e se o sinal está forte o suficiente
    if(macAtual.equalsIgnoreCase(meuMAC) && (d.getRSSI() >= -85)){
      encontrado = true;
      ultimaDeteccao = millis();
      break;
    }
  }
  // Se encontrou o dispositivo alvo com sinal suficiente e liga o relé 
  if(encontrado){
    if(digitalRead(rele) == HIGH){
      Serial.println("Dispositivo encontrado! Acionando RELÉ.");
      digitalWrite(rele, LOW);
    }else{
      Serial.println("Dispositivo presente. O relé permanece ligado");
    }
  }else {
    //Verifica se passou o tempo desde a última detecção
    if(millis() - ultimaDeteccao > tempoDesligamento){
      if(digitalRead(rele) == LOW){
        Serial.println("Dispositivo ausente há 30 segundos. Desligando Relé!");
        digitalWrite(rele, HIGH);
      }else{
        Serial.println("Dispositivo ausente. Relé já desligado");
      }
    }else{
      Serial.println("Dispositivo não detectado, mas dentro do tempo limite. Mantendo relé ligado!");
    }

  } 

}
