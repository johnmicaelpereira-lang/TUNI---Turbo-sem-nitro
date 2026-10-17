// Carrinho TUNI - firmware do ESP32 (controle por MQTT, tração diferencial)
// Credenciais do Wi-Fi ficam em secrets.h (ver secrets.h.example)
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "secrets.h"

// --- CONFIGURAÇÕES MQTT ---
const char* mqtt_server = "broker.emqx.io";
const char* topico_sub = "tuni/carrinho/comandos";

// --- DEFINIÇÃO DOS PINOS DA PONTE H L298N ---
// Motor Esquerdo
const int ENA = 23; 
const int IN1 = 21;
const int IN2 = 22;

// Motor Direito
const int ENB = 5;
const int IN3 = 19;
const int IN4 = 18;

// --- AJUSTE DE POTÊNCIA (COMPENSAÇÃO DE ATRITO) ---
const int PWM_MINIMO = 75;  // PWM mínimo para vencer a inércia dos motores
const int PWM_MAXIMO = 255; // PWM máximo

// --- VARIÁVEIS DE ESTADO ---
float volante = 0.0f;     // -1.0 (esquerda) a 1.0 (direita)
float acelerador = 0.0f;  // -1.0 (marcha-atrás) a 1.0 (frente)
bool habilitado = true;

WiFiClient espClient;
PubSubClient client(espClient);

// Converte a entrada decimal (-1.0 a 1.0) para PWM com compensação de zona morta
int converterParaPWM(float entrada) {
  if (fabs(entrada) < 0.02f) return 0; // Margem de folga do centro do volante
  
  int sentido = (entrada > 0.0f) ? 1 : -1;
  float magnitude = constrain(fabs(entrada), 0.0f, 1.0f);
  int pwmCalculado = PWM_MINIMO + (int)(magnitude * (PWM_MAXIMO - PWM_MINIMO));
  
  return pwmCalculado * sentido;
}

// --- CONTROLE DE MOTORES POR TRAÇÃO DIFERENCIAL ---
void atualizarMotores() {
  if (!habilitado) {
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
    return;
  }

  // 1. Mistura de eixos para Tração Diferencial
  float esqNorm = acelerador + volante;
  float dirNorm = acelerador - volante;

  // 2. Limita o intervalo de atuação (-1.0 a 1.0)
  esqNorm = constrain(esqNorm, -1.0f, 1.0f);
  dirNorm = constrain(dirNorm, -1.0f, 1.0f);

  // 3. Converte para o valor de PWM do hardware
  int pwmEsq = converterParaPWM(esqNorm);
  int pwmDir = converterParaPWM(dirNorm);

  // --- MOTOR ESQUERDO ---
  if (pwmEsq > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else if (pwmEsq < 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }
  analogWrite(ENA, abs(pwmEsq));

  // --- MOTOR DIREITO ---
  if (pwmDir > 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else if (pwmDir < 0) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  analogWrite(ENB, abs(pwmDir));
}

// --- CALLBACK MQTT OTIMIZADO (LEITURA DIRETA E INSTANTÂNEA) ---
void callback(char* topic, byte* payload, unsigned int length) {
  JsonDocument doc;
  
  // Deserialização direta a partir do buffer (sem conversão para String para economizar tempo de CPU)
  DeserializationError error = deserializeJson(doc, payload, length);

  if (!error) {
    if (doc.containsKey("volante"))    volante = doc["volante"].as<float>();
    if (doc.containsKey("acelerador")) acelerador = doc["acelerador"].as<float>();
    if (doc.containsKey("habilitado")) habilitado = doc["habilitado"].as<bool>();

    atualizarMotores();
  }
}

// --- RECONEXÃO AUTOMÁTICA AO BROKER MQTT ---
void reconectar() {
  while (!client.connected()) {
    Serial.print("[MQTT] Conectando ao broker...");
    
    String clientId = "ESP32_Carrinho_" + String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println(" CONECTADO!");
      client.subscribe(topico_sub);
      Serial.print("Subscrito no topico: ");
      Serial.println(topico_sub);
    } else {
      Serial.print(" Falhou (rc=");
      Serial.print(client.state());
      Serial.println("). Nova tentativa em 2s...");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("\n===========================================");
  Serial.println("CARRINHO TUNI - OTIMIZADO PARA BAIXA LATENCIA");
  Serial.println("===========================================");

  // Configuração dos pinos digitais da Ponte H
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT); pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT); pinMode(ENB, OUTPUT);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  // Conexão Wi-Fi
  Serial.print("Conectando ao Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi Conectado! IP: " + WiFi.localIP().toString());

  // --- OTIMIZAÇÕES CHAVE PARA RESPOSTA RÁPIDA ---
  WiFi.setSleep(false);        // Desativa economia de energia do rádio Wi-Fi
  espClient.setNoDelay(true);  // Força o envio/recepção imediata do TCP sem buffer

  // Configuração do Servidor MQTT
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconectar();
  }
  client.loop();
}
