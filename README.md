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
- **Andrielle Rayllany** (Eletrônica e integração elétrica): Sistema de alimentação, driver de motor, esquemático elétrico e planejamento da placa PCB dedicada.
- **John Micael** (Software e controle): Firmware do ESP32, recepção de comandos JSON via MQTT, automação e controle dos motores.

> *Nota: As áreas indicam as responsabilidades principais, mas as atividades e entregas são integradas entre os membros.*

---

## 🔗 Links Principais

- **Cronograma e Planejamento Semanal:** [PLANEJAMENTO.md](./PLANEJAMENTO.md)
- **Registro de Progresso Semanal:** [PROGRESSO.md](./PROGRESSO.md)
- **Eletrônica (pinagem e ligações):** [docs/eletronica/pinagem_e_ligacoes.md](./docs/eletronica/pinagem_e_ligacoes.md)
- **Mecânica:** [docs/mecanica/mecanica.md](./docs/mecanica/mecanica.md) e [desenho técnico do chassi](./docs/mecanica/desenho_tecnico_chassi.pdf)
- **Firmware:** [docs/software/carrinho_tuni.ino](./docs/software/carrinho_tuni.ino)
- **Testes:** [docs/testes/testes.md](./docs/testes/testes.md)

---

## 1. 🎯 Objetivo do Projeto

Desenvolver um veículo robotizado terrestre de pequena escala para participação na **Competição de Carrinhos do Projeto Integrador**. O veículo deverá percorrer a pista oficial respeitando os requisitos técnicos do regulamento (máximo de 300 mm x 200 mm, ao menos uma câmera embarcada) e respondendo aos comandos da interface de controle disponibilizada pela organização.

---

## 2. 💡 Visão Geral da Solução (situação em 17/10/2026)

| Item | Situação atual | Observações |
|---|---|---|
| Chassi | Chassi 2WD que a equipe já possuía, com 2 motores DC com caixa de redução e roda boba dianteira | Protótipo funcional usado nos testes. Em 09/10 o orientador pediu ocultar fios e protoboard; a solução prevista é uma carcaça fechada. Em 15/10 a equipe decidiu **manter o chassi atual por enquanto** e pesquisar uma opção melhor |
| Projeto do chassi | Desenho técnico (vistas superior e inferior) com 213 mm x 110 mm, dentro do limite de 300 x 200 mm | [desenho_tecnico_chassi.pdf](./docs/mecanica/desenho_tecnico_chassi.pdf); cotas com ≈ ainda a validar nos componentes |
| Tração e direção | Diferencial: 2 motores DC nas rodas traseiras; a direção vem da diferença de PWM entre os lados | Sem servo de direção |
| Microcontrolador | ESP32 | Firmware em Arduino/C++ |
| Driver de motores | Ponte H L298N | Capacidade de corrente ainda a medir sob carga |
| Alimentação | Bateria do kit (2 células Li-ion 3,7 V): positivo passando pela chave liga/desliga até a entrada de 12 V da L298N; o 5 V da L298N alimenta o VIN do ESP32 | Especificação oficial da bateria ainda será divulgada |
| Controle | Volante físico publica JSON; ESP32 recebe via MQTT | MQTT é o protocolo adotado em todo o projeto |
| Câmera | Smartphone Android embarcado com app de vídeo (exigência do regulamento) | **Ainda não integrado** |
| Montagem eletrônica | Jumpers ligando o ESP32 à L298N, com fixação provisória (fita VHB, fita isolante e abraçadeiras) | Fotos em `docs/mecanica/`; PCB própria em planejamento |

---

## 3. 📐 Arquitetura Geral do Sistema

**Arquitetura do sistema:**

```text
Volante físico
      |
      | MQTT (broker.emqx.io, tópico tuni/carrinho/comandos, JSON)
      v
ESP32 (Wi-Fi, firmware de controle, mistura diferencial)
      |
      +--> Ponte H L298N (PWM + sentido) --> Motor esquerdo / Motor direito
```

**Vídeo:** smartphone Android embarcado com o app oficial de transmissão (ainda a integrar).
**Telemetria (prevista):** o ESP32 publica dados no mesmo broker MQTT.

---

## 4. 🧱 Detalhamento dos Subsistemas

### Mecânica
- **Estrutura:** chassi 2WD existente com fixação dos motores, bateria e eletrônica.
- **Tração e direção:** dois motores DC com redução nas rodas traseiras; roda boba dianteira; direção por velocidade diferencial.
- **Projeto (desenho técnico):** chassi de 213 x 110 mm; motores com caixa de 64,2 x 22,5 x 18,8 mm; rodas Ø 56 x 26,6 mm; roda boba com base de 38 x 32 mm; suporte do celular para um aparelho de 163,7 x 76,1 x 7,6 mm.
- **Pendências:** validar as cotas estimadas nos componentes, medir o carrinho atual, acabamento com fiação oculta e suporte do smartphone.
- Detalhes em [docs/mecanica/mecanica.md](./docs/mecanica/mecanica.md).

### Elétrica e Eletrônica
- **Pinagem validada (ESP32 → L298N):**

| Função | ESP32 | L298N |
|---|---|---|
| Motor esquerdo — PWM | GPIO 23 | ENA |
| Motor esquerdo — sentido | GPIO 21 / 22 | IN1 / IN2 |
| Motor direito — PWM | GPIO 5 | ENB |
| Motor direito — sentido | GPIO 19 / 18 | IN3 / IN4 |

- **Montagem atual:** jumpers diretos entre ESP32 e L298N (fotos em `docs/mecanica/`). **Planejado:** PCB própria (ver [PLANEJAMENTO.md](./PLANEJAMENTO.md)).
- Detalhes em [docs/eletronica/pinagem_e_ligacoes.md](./docs/eletronica/pinagem_e_ligacoes.md).

### Software e Controle
- **Firmware:** Arduino/C++ para ESP32, com as bibliotecas `WiFi`, `PubSubClient` e `ArduinoJson` ([código](./docs/software/carrinho_tuni.ino)).
- **Módulos:**
  - conexão Wi-Fi e reconexão automática ao broker MQTT;
  - *callback* que lê o JSON direto do buffer (sem `String`);
  - conversão de entrada (-1,0 a 1,0) para PWM, com zona morta de 2% no centro e PWM mínimo de 75 para vencer o atrito;
  - controle dos motores por mistura diferencial: `esquerdo = acelerador + volante` e `direito = acelerador - volante`, limitados a ±1.
- **Otimizações de latência:** `WiFi.setSleep(false)` (rádio sempre ativo) e `setNoDelay(true)` (sem espera do algoritmo de Nagle no TCP).
- **Pendente:** parada de segurança quando não chegam comandos e broker MQTT local na rede da competição.

---

## 5. 🛒 Lista de Materiais e Componentes

- **ESP32:** 1 unidade | Origem: Kit da Organização | Situação: Em uso
- **Motores DC com Redução:** 2 unidades | Origem: Kit da Organização / Equipe | Situação: Em uso
- **Driver de Motor (Ponte H L298N):** 1 unidade | Origem: Kit da Organização / Equipe | Situação: Em uso
- **Chassi 2WD e rodas:** 1 conjunto | Origem: Equipe | Situação: Em uso
- **Bateria (2 células Li-ion 3,7 V):** conforme o kit | Origem: Organização | Situação: Em uso (especificação oficial a divulgar)
- **Smartphone Android (câmera):** 1 unidade | Origem: Equipe | Situação: Disponível, ainda não integrado
- **Componentes da PCB (resistores, conectores e reguladores):** Origem: Solicitado à COLAB / Adquirido | Situação: Em solicitação

---

## 6. 📡 Protocolos de Comunicação

### Comandos (MQTT — protocolo adotado em todo o projeto)
- **Broker:** `broker.emqx.io`, porta 1883
- **Tópico:** `tuni/carrinho/comandos`
- **Pacote:**
```json
{ "volante": 0.0, "acelerador": 0.0 }
```
`volante`: -1,0 (esquerda) a 1,0 (direita). `acelerador`: -1,0 (ré) a 1,0 (frente). O campo opcional `habilitado` (true/false) liga/desliga os motores.

O MQTT atende à interface do volante da competição (confirmado pela equipe).

### Telemetria (prevista)
- MQTT 3.1.1 sobre TCP, porta 1883, tópico previsto `carrinhos/TUNI/telemetria`.

---

## 7. 🧪 Registros de Testes

| # | Data | Teste | Procedimento | Resultado | Ação |
|---|---|---|---|---|---|
| 1 | 17/09 | Energização do ESP32 | Alimentação regulada em bancada | Iniciou sem variações de tensão | Implementar firmware |
| 2 | 17/09 | Motores DC | Sinal direto nos 2 motores do kit | Giram nos dois sentidos | Medir corrente sob carga |
| 3 | 25/09 | Callback MQTT | Mensagens MQTT manuais ao ESP32 | Pacotes recebidos e impressos no Monitor Serial | Testar motores |
| 4 | 28/09 | Motores em bancada | Acionamento sem carga | Avanço, ré e giro diferencial corretos | Integrar com o volante |
| 5 | 03/10 | Transmissão do volante | Monitoramento dos pacotes no broker | Entrega regular, sem quedas | Testar com o carrinho |
| 6 | 09/10 | Volante + carrinho no chão | Pilotagem real com o JSON final | Carrinho respondeu aos comandos de curva e aceleração | Orientador pediu ocultar a fiação |
| 7 | 16/10 | Pilotagem após otimização | Pilotagem livre com o volante, após ajustes de firmware (informal, sem medição) | Resposta mais fluida, com menos travamentos | Medir latência com método objetivo |

Pendente: corrente dos motores sob carga e temperatura da L298N. Detalhes em [docs/testes/testes.md](./docs/testes/testes.md).

---

## 8. 📋 Planejado x Realizado

O comparativo semana a semana está no [PROGRESSO.md](./PROGRESSO.md), e as alterações do cronograma, com justificativas, no [PLANEJAMENTO.md](./PLANEJAMENTO.md).

**Resumo:** repositório, documentação, firmware MQTT, mistura diferencial e integração volante + carrinho foram concluídos. Ficaram para as próximas semanas PCB, câmera/celular, parada de segurança e acabamento da fiação.

---

## 9. 🔁 Decisões Técnicas e Mudanças de Rumo

| Data | Decisão | Motivo |
|---|---|---|
| Semana 1 | ESP32 como unidade central; tração diferencial com 2 motores | Simplicidade e domínio da equipe |
| Semana 2 | Adotar MQTT para os comandos | Permitiu testar o firmware desde cedo e funcionou ponta a ponta (volante → broker → ESP32) |
| Semana 2 | PWM mínimo de 75 | A queda de tensão na L298N impedia o arranque em PWM baixo |
| 09/10 | JSON final com `volante` e `acelerador` em float (-1,0 a 1,0) | Facilita a escala da tração diferencial |
| 09/10 | Planejar carcaça fechada | Orientador apontou fios e protoboard expostos |
| 15/10 | Manter o chassi atual nesta etapa e pesquisar um melhor | Priorizar a revisão da Etapa 1 com o sistema funcionando |
| 15/10 | Otimizar latência (`setSleep(false)`, `setNoDelay(true)`, leitura direta do JSON) | Controle apresentava travamentos |
| 17/10 | MQTT confirmado como protocolo final de comunicação do projeto | Já validado ponta a ponta; evita retrabalho |

---

## 10. ⚠️ Pendências e Riscos

1. Esquemático detalhado e PCB (o esquemático básico de ligações já existe).
2. Integração do smartphone Android e do app oficial de vídeo (regulamento).
3. Alimentação do ESP32 pelo regulador de 5 V da L298N: nenhum reinício foi observado nos testes; medir a tensão em operação para confirmar a margem com a bateria descarregada.
4. Parada de segurança do carrinho quando faltar comando.
5. Broker MQTT local na rede da competição (o público tem latência variável).
6. Medir corrente e temperatura da L298N sob carga.
7. Medir o carrinho atual e validar as cotas estimadas do desenho técnico (limite 300 x 200 mm; o projeto prevê 213 x 110 mm).
8. Acabamento: ocultar fiação e protoboard.

---

## 11. 📁 Estrutura do Repositório

```text
/
├── README.md
├── PLANEJAMENTO.md
├── PROGRESSO.md
├── .gitignore
└── docs/
    ├── software/     # carrinho_tuni.ino e secrets.h.example
    ├── mecanica/     # mecanica.md
    ├── eletronica/   # pinagem_e_ligacoes.md
    └── testes/       # testes.md
```

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
