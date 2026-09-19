# Projeto Integrador — Carrinho Robotizado

---

## 👥 Equipe e Identificação

- **Nome da equipe:** TUNI - Turbo Sem Nitro
- **Turma:** Meca3V
- **Professor técnico / Orientador:** Jefferson Doolan

### Integrantes e Áreas de Atuação

- **Letícia Gabrielle** (Piloto e calibração): Testes de dirigibilidade, calibração, operação de pistas, câmera e suporte.
- **Emili Emanuele** (Mecânica): Projeto estrutural do chassi, tração, direção, fixações mecânicas e montagem.
- **Luiz Carlos** (Projeto e documentação): Arquitetura geral, desenhos técnicos, organização da documentação do GitHub e testes de comunicação.
- **Andrielle Rayllany** (Eletrônica e integração elétrica): Sistema de alimentação, drivers de motor, esquemático e roteamento da placa PCB dedicada.
- **John Micael** (Software e controle): Firmware do ESP32, protocolo de recepção de comandos JSON (Serial/UDP), automação e controle dos motores.

> *Nota: As áreas indicam as responsabilidades principais, mas as atividades e entregas são integradas entre os membros.*

---

## 🔗 Links Principais

- **Cronograma e Planejamento Semanal:** [PLANEJAMENTO.md](./PLANEJAMENTO.md)[cite: 1]
- **Registro de Progresso Semanal:** [PROGRESSO.md](./PROGRESSO.md)[cite: 1]

---

## 1. 🎯 Objetivo do Projeto

Desenvolver um veículo robotizado terrestre de pequena escala para participação na **Competição de Carrinhos do Projeto Integrador**[cite: 1]. O veículo deverá percorrer a pista oficial respeitando os requisitos técnicos do regulamento e respondendo aos comandos da interface de controle disponibilizada pela organização[cite: 1].

---

## 2. 💡 Visão Geral da Solução

- **Arquitetura de tração:** Tração diferencial composta por dois motores DC acoplados às rodas traseiras.
- **Direção:** Controle de direção diferencial via variação individual da velocidade PWM de cada motor DC.
- **Microcontrolador principal:** ESP32.
- **Driver de motores:** Ponte H dedicada (em fase de testes de bancada e medição de corrente).
- **Câmera embarcada:** Smartphone embarcado executando aplicativo de streaming de vídeo IP em tempo real.
- **Sistema de alimentação:** Bateria dedicada para acionamento dos motores com barramento e regulação isolados para a lógica do ESP32.
- **Comunicação e automação:** Interpretação de pacotes JSON para controle de movimento e telemetria via protocolo MQTT.

---

## 3. 📐 Arquitetura Geral do Sistema

```text
Volante da Organização
        |
        | UDP (Porta 5000 / Pacotes JSON UTF-8)
        v
      ESP32 (Recepção & Firmware de Controle)
        |
        +--> Driver de Motores (Ponte H / Controle PWM Diferencial)
        +--> Sensores & Módulos de Telemetria
        |
        +--> MQTT (TCP Porta 1883) --> Servidor de Telemetria

Smartphone Embarcado (Câmera) --> Transmissão de Vídeo via IP / App
```

---

## 4. 🧱 Detalhamento dos Subsistemas

### Mecânica
- **Estrutura:** Chassi leve com fixação para motores DC, bateria e placa eletrônica.
- **Tração e Direção:** Sistema diferencial operado por dois motores DC de caixa de redução.
- **Suporte da Câmera:** Estrutura física impressa/confeccionada para acoplamento do smartphone mantendo a estabilidade da imagem.

### Elétrica e Eletrônica
- **Alimentação:** Barramentos de tensão independentes para evitar surtos da parte de potência no ESP32.
- **Drivers e Motores:** Ponte H controlada por saídas PWM do microcontrolador.
- **Placa PCB Dedicada:** Projeto e confecção de placa de circuito impresso própria (desenvolvida por Andrielle) para integração dos componentes e eliminação de conexões por jumpers soltos.

### Software e Controle
- **Firmware:** Desenvolvido na IDE Arduino/C++ para o ESP32.
- **Parsing JSON:** Módulo interno para deserialização dos pacotes de comando recebidos via porta Serial/UDP.
- **Módulos de Comunicação:** Conexão Wi-Fi para recepção de comandos UDP e publicação de dados de telemetria MQTT.

---

## 5. 🛒 Lista de Materiais e Componentes

- **ESP32:** 1 unidade | Origem: Kit da Organização[cite: 1] | Situação: Disponível
- **Motores DC com Redução:** 2 unidades | Origem: Kit da Organização[cite: 1] | Situação: Disponível
- **Driver de Motor (Ponte H):** 1 unidade | Origem: Kit da Organização / Equipe[cite: 1] | Situação: Em Testes
- **Chassi e Rodas:** 1 conjunto | Origem: Equipe[cite: 1] | Situação: Disponível
- **Smartphone (Câmera):** 1 unidade | Origem: Equipe[cite: 1] | Situação: Disponível
- **Componentes Eletrônicos da PCB:** Resistores, conectores e reguladores | Origem: Solicitado ao COLAB / Adquirido[cite: 1] | Situação: Em solicitação

---

## 6. 📡 Protocolos de Comunicação

### Comandos da Organização
- **Protocolo:** UDP unicast
- **Porta:** 5000
- **Formato:** JSON em UTF-8
- **Frequência nominal:** 60 Hz
- **Estrutura do pacote esperado:**
```json
{
  "sequencia": 123,
  "volante": 0,
  "aceleracao": 0,
  "habilitado": true
}
```

### Telemetria
- **Protocolo:** MQTT 3.1.1 sobre TCP
- **Porta:** 1883
- **Tópico previsto:** `carrinhos/TUNI/telemetria`

---

## 7. 🧪 Registros de Testes de Bancada

- **Teste 1 (17/09/2026) — Alimentação e Lógica:**
  - *Procedimento:* Teste de energização do ESP32 via regulador de tensão.
  - *Resultado:* Microcontrolador iniciou normalmente sem quedas de tensão.
  - *Ação:* Avançar para o teste de comunicação serial.

- **Teste 2 (17/09/2026) — Motores DC:**
  - *Procedimento:* Acionamento direto dos dois motores DC do kit.
  - *Resultado:* Ambos os motores operacionais com rotação em ambos os sentidos.
  - *Ação:* Medir a corrente de partida sob carga para validação da Ponte H.

---

## 8. 📁 Estrutura do Repositório

```text
/
├── README.md               # Apresentação geral do projeto[cite: 1]
├── PLANEJAMENTO.md         # Cronograma completo[cite: 1]
├── PROGRESSO.md            # Registro semanal de atividades[cite: 1]
└── docs/                   # Documentação técnica obrigatória[cite: 1]
    ├── software/           # Códigos, rotinas JSON e MQTT[cite: 1]
    ├── mecanica/           # Desenhos do chassi e suporte da câmera[cite: 1]
    ├── eletronica/         # Esquemáticos elétricos e arquivos Gerber da PCB[cite: 1]
    └── testes/             # Logs e relatórios de ensaios[cite: 1]
```
