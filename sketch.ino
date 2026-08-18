#include <WiFi.h>
#include <PubSubClient.h>

// --- Configurações de Rede e ThingsBoard ---
const char* ssid = "Wokwi-GUEST"; 
const char* password = "";
const char* mqtt_server = "thingsboard.cloud";   // Endereço correto para conexão TCP
const char* tb_token = "qXxE9hwLVknYyjkksyQR";   // Token do dispositivo Medido_ESP32

WiFiClient espClient;
PubSubClient client(espClient);

// --- Pinos de Entrada ---
const int PIN_TENSAO = 34;
const int PIN_CORRENTE = 35;

// --- Variáveis Globais ---
float tarifa_kwh = 0.85; 
unsigned long ultimoEnvio = 0;

void setup_wifi() {
  delay(10);
  Serial.print("Conectando ao Wi-Fi ");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi Conectado!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao ThingsBoard via MQTT...");
    String clientId = "ESP32EnergyMeter-";
    clientId += String(random(0xffff), HEX);
    
    // No ThingsBoard, o Token é passado no campo de Usuário (Username)
    if (client.connect(clientId.c_str(), tb_token, NULL)) {
      Serial.println(" Conectado!");
    } else {
      Serial.print(" Falhou, rc=");
      Serial.print(client.state());
      Serial.println(". Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (millis() - ultimoEnvio > 3000) {
    ultimoEnvio = millis();

    int rawTensao = analogRead(PIN_TENSAO);
    int rawCorrente = analogRead(PIN_CORRENTE);

    float tensao = map(rawTensao, 0, 4095, 0, 220);            
    float corrente = map(rawCorrente, 0, 4095, 0, 300) / 10.0; 

    float potencia = tensao * corrente;                 
    float custoHora = (potencia / 1000.0) * tarifa_kwh; 

    Serial.printf("Tensão: %.1f V | Corrente: %.2f A | Potência: %.1f W | Custo/h: R$ %.2f\n", 
                  tensao, corrente, potencia, custoHora);

    // Criação do Payload em formato JSON aceito pelo ThingsBoard
    String payload = "{";
    payload += "\"tensao\":" + String(tensao, 1) + ",";
    payload += "\"corrente\":" + String(corrente, 2) + ",";
    payload += "\"potencia\":" + String(potencia, 1) + ",";
    payload += "\"custo_hora\":" + String(custoHora, 2);
    payload += "}";

    // Publica no tópico padrão de telemetria do ThingsBoard
    client.publish("v1/devices/me/telemetry", payload.c_str());
  }
}
