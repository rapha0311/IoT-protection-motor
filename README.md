# ⚡ Monitor de Energia Elétrica e Telemetria IoT (ESP32 + ThingsBoard)

Sistema de monitoramento e medição de consumo elétrico em tempo real desenvolvido com ESP32, comunicação via protocolo MQTT e visualização na nuvem com o ThingsBoard Cloud.

---

## 📌 Funcionalidades
* **Leitura de Sensores:** Leitura de sinais analógicos simulando sensores de tensão (V) e corrente (A).
* **Edge Computing:** Processamento local no ESP32 para cálculo de potência ativa (W) e estimativa de custo por hora (R$).
* **Telemetria MQTT:** Envio contínuo de payloads em JSON para o broker do ThingsBoard Cloud.
* **Dashboard Interativo:** Painel em tempo real com medidores digitais (*gauges*) e gráfico de histórico temporal.

---

## 🛠️ Tecnologias Utilizadas
* **Firmware:** C++ / Arduino Framework / ESP32
* **Simulação:** Wokwi Simulator
* **Protocolo de Comunicação:** MQTT (Biblioteca `PubSubClient`)
* **Plataforma Cloud:** ThingsBoard Cloud

---

## 🔗 Links do Projeto
* 🚀 **Simulação Interativa:** [Executar no Wokwi](https://wokwi.com/projects/472703937958391809)
* 📊 **Dashboard em Tempo Real:** [Acessar ThingsBoard Cloud](https://thingsboard.cloud/dashboards/all/1c133120-9b1e-11f1-83d2-798c305070d0)

---

## 💻 Como Executar
1. Acesse o projeto no [Wokwi](https://wokwi.com/projects/472703937958391809).
2. Clique no botão **Play** para iniciar a simulação.
3. Altere os valores nos dois potenciômetros para simular variações de Tensão e Corrente.
4. Observe os dados sendo atualizados no Monitor Serial e no Dashboard do ThingsBoard Cloud.

![Dashboard](Medidor Energético.png)
