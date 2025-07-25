# Acionamento de Lâmpada com ESP32 e Detecção Bluetooth

Este projeto utiliza um microcontrolador **ESP32**, um **módulo relé** e um dispositivo Bluetooth (meu relógio) para acionar automaticamente uma **lâmpada real** com base na presença detectada via Bluetooth Low Energy (BLE).

---

## 📦 Componentes utilizados

- Módulo de desenvolvimento ESP32  
- Módulo Relé 1 canal  
- Lâmpada 110V com soquete e cabos  
- Relógio com Bluetooth (dispositivo a ser detectado)  
- Protoboard e jumpers  
- Cabo USB (para alimentação)

---

## ⚙️ Funcionamento

A ESP32 realiza um escaneamento BLE a cada 5 segundos em busca do endereço MAC do relógio.

Sempre que o dispositivo é detectado com sinal adequado (RSSI ≥ -85), a placa **aciona o relé** e acende a lâmpada.  
Se o dispositivo não for detectado por **mais de 30 segundos**, o relé é desligado automaticamente e a lâmpada apaga.

Essa lógica evita desligamentos acidentais causados por falhas momentâneas no sinal Bluetooth.

---

## 🖼️ Imagem do projeto

![Acionamento por Presença Bluetooth](./imagem.jpg)

---

## 🧠 Aprendizados envolvidos

- Escaneamento BLE com `BLEDevice`, `BLEScan` e `BLEAdvertisedDevice`  
- Comparação de endereços MAC e uso de RSSI como critério de proximidade  
- Controle de relé com ESP32 (acionamento físico)  
- Lógica condicional com `if` + controle de tempo com `millis()`  
- Integração de hardware real (ESP + relé + carga 110V)

---

## 📘 Bibliotecas utilizadas

- `BLEDevice.h`  
- `BLEUtils.h`  
- `BLEScan.h`  
- `BLEAdvertisedDevice.h`

Todas disponíveis na IDE Arduino via suporte à ESP32.

---

## 📽️ Demonstração em vídeo

Confira o funcionamento completo do projeto no vídeo postado no Instagram:

🔗 [@embarcados.na.automacao](https://www.instagram.com/embarcados.na.automacao)

---

## 👨‍💻 Autor

Projeto criado por **Enrike Rocha Fernandes**, estudante de Engenharia de Controle e Automação.  
Foco em projetos com ESP32, sistemas embarcados e automação aplicada de forma prática, acessível e funcional.
