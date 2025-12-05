#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include "DHT.h"

// --- SEUS DADOS DE REDE ---
const char *ssid = "NOME_WIFI";
const char *password = "SENHA";

// --- CONFIGURAÇÃO DO SENSOR ---
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

WebServer server(80);

// Variáveis globais
float umidade = 0.0;
float temperatura = 0.0;

// ---------------------------------------------------------
// CÓDIGO HTML + CSS + JS (Interface do Web App)
// ---------------------------------------------------------
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-br">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
  <title>Drybox Monitor</title>
  <style>
    :root {
      --bg-color: #121212;
      --card-bg: #1e1e1e;
      --text-primary: #ffffff;
      --text-secondary: #b0b0b0;
      --accent-purple: #bb86fc;
      --accent-green: #03dac6;
      --accent-red: #cf6679;
    }
    
    body {
      background-color: var(--bg-color);
      color: var(--text-primary);
      font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
      margin: 0;
      padding: 20px;
      display: flex;
      flex-direction: column;
      align-items: center;
      min-height: 100vh;
    }

    h1 {
      font-weight: 300;
      letter-spacing: 2px;
      margin-bottom: 30px;
      color: var(--accent-purple);
      text-transform: uppercase;
      font-size: 1.5rem;
    }

    .container {
      width: 100%;
      max-width: 400px;
      display: grid;
      gap: 20px;
    }

    .card {
      background-color: var(--card-bg);
      border-radius: 20px;
      padding: 25px;
      box-shadow: 0 8px 16px rgba(0,0,0,0.3);
      text-align: center;
      position: relative;
      overflow: hidden;
      transition: transform 0.2s;
    }

    .card:active {
      transform: scale(0.98);
    }

    .card::before {
      content: '';
      position: absolute;
      top: 0;
      left: 0;
      width: 100%;
      height: 4px;
      background: var(--accent-purple);
    }

    .icon {
      width: 40px;
      height: 40px;
      fill: var(--text-secondary);
      margin-bottom: 10px;
    }

    .label {
      font-size: 0.9rem;
      color: var(--text-secondary);
      text-transform: uppercase;
      letter-spacing: 1px;
    }

    .value {
      font-size: 3.5rem;
      font-weight: 700;
      margin: 10px 0;
    }

    .unit {
      font-size: 1.5rem;
      font-weight: 400;
      color: var(--text-secondary);
    }

    /* Status Indicator for Filament */
    .status-box {
      margin-top: 20px;
      padding: 15px;
      border-radius: 12px;
      background: rgba(187, 134, 252, 0.1);
      border: 1px solid var(--accent-purple);
      font-size: 0.9rem;
      text-align: center;
    }

    /* Classes dinâmicas para alertas */
    .good { color: var(--accent-green); }
    .warning { color: #ffb74d; }
    .danger { color: var(--accent-red); }

  </style>
</head>
<body>

  <h1>Drybox ESP32</h1>

  <div class="container">
    <!-- Card Umidade -->
    <div class="card">
      <svg class="icon" viewBox="0 0 24 24"><path d="M12,2C12,2 6,9 6,14.5C6,17.5 8.5,20 12,20C15.5,20 18,17.5 18,14.5C18,9 12,2 12,2M12,22A7.5,7.5 0 0,1 4.5,14.5C4.5,8.2 12,0.5 12,0.5S19.5,8.2 19.5,14.5A7.5,7.5 0 0,1 12,22Z"/></svg>
      <div class="label">Umidade</div>
      <div class="value" id="hum">--</div><span class="unit">%</span>
    </div>

    <!-- Card Temperatura -->
    <div class="card">
      <svg class="icon" viewBox="0 0 24 24"><path d="M15,13V5A3,3 0 0,0 9,5V13A5,5 0 1,0 15,13M12,4A1,1 0 0,1 13,5V12H11V5A1,1 0 0,1 12,4Z"/></svg>
      <div class="label">Temperatura</div>
      <div class="value" id="temp">--</div><span class="unit">°C</span>
    </div>

    <div class="status-box" id="status-msg">
      Carregando dados...
    </div>
  </div>

<script>
  // Função que roda a cada 2 segundos
  setInterval(function() {
    getData();
  }, 2000);

  function getData() {
    fetch("/data") // Pede os dados JSON pro ESP32
      .then(response => response.json())
      .then(data => {
        // Atualiza os números
        document.getElementById("temp").innerText = data.temperatura.toFixed(1);
        document.getElementById("hum").innerText = data.umidade.toFixed(1);
        
        // Lógica para Filamento PLA (Drybox)
        updateStatus(data.umidade);
      })
      .catch(error => console.log(error));
  }

  function updateStatus(h) {
    const statusMsg = document.getElementById("status-msg");
    const humValue = document.getElementById("hum");
    
    // Regras para PLA (Ideal < 40%, Aceitável < 50%)
    if(h < 40) {
      statusMsg.innerHTML = "✅ Ambiente Perfeito para PLA";
      statusMsg.style.borderColor = "#03dac6";
      humValue.className = "value good";
    } else if (h < 55) {
      statusMsg.innerHTML = "⚠️ Atenção: Umidade subindo";
      statusMsg.style.borderColor = "#ffb74d";
      humValue.className = "value warning";
    } else {
      statusMsg.innerHTML = "🔥 CRÍTICO: Seque o filamento!";
      statusMsg.style.borderColor = "#cf6679";
      humValue.className = "value danger";
    }
  }

  getData();
</script>

</body>
</html>
)rawliteral";

// ---------------------------------------------------------
// FUNÇÕES DO ARDUINO
// ---------------------------------------------------------

void handleRoot()
{
  server.send(200, "text/html", index_html);
}

void handleData()
{
  // Lê os dados
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t))
  {
    Serial.println("Falha no sensor!");
    h = 0.0;
    t = 0.0;
  }

  StaticJsonDocument<200> doc;
  doc["temperatura"] = t;
  doc["umidade"] = h;

  String jsonString;
  serializeJson(doc, jsonString);

  server.send(200, "application/json", jsonString);
}

void setup()
{
  Serial.begin(115200);
  dht.begin();

  // Conexão Wi-Fi
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Rotas do Servidor
  server.on("/", handleRoot);
  server.on("/data", handleData);

  server.begin();
}

void loop()
{
  server.handleClient();
}