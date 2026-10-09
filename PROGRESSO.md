# Registro de Progresso — Projeto Integrador

---

## Identificação do Projeto

- **Nome da equipe:** TUNI - Turbo Sem Nitro
- **Turma:** Meca3V
- **Professor técnico / Orientador:** Jefferson Doolan

Este arquivo armazena o histórico semanal de desenvolvimento do veículo[cite: 1]. Os registros das semanas anteriores são mantidos permanentemente para fins de auditoria e acompanhamento do progresso real em relação ao planejado[cite: 1].

---

## Semana 1 — 16/09/2026 a 22/09/2026

### Atividades Planejadas
- Definir a arquitetura geral do veículo e o conceito da solução.
- Escolher a arquitetura de tração e direção (Diferencial com dois motores DC).
- Estruturar o repositório público no GitHub com as pastas obrigatórias (`docs/software/`, `docs/mecanica/`, `docs/eletronica/` e `docs/testes/`)[cite: 1].
- Elaborar os arquivos fundamentais de documentação (`README.md`, `PLANEJAMENTO.md` e `PROGRESSO.md`)[cite: 1].
- Enviar a solicitação formal de materiais do kit para a COLAB (`colab.par@ifrn.edu.br`) com cópia para o orientador[cite: 1].

### Atividades Concluídas
- Arquitetura geral do veículo e subsistemas definidos.
- Escolha da tração diferencial com 2 motores DC e controle de velocidade via PWM.
- Repositório público criado e organizado no GitHub com a estrutura de pastas exigida[cite: 1].
- Arquivos `README.md`, `PLANEJAMENTO.md` e `PROGRESSO.md` preenchidos e atualizados[cite: 1].
- Solicitação formal de materiais organizada e encaminhada à COLAB respeitando o padrão de assunto exigido[cite: 1].

### Atividades Não Concluídas
- Medição da corrente de partida dos motores sob carga (adiada para a validação do driver de potência na próxima semana).

### Problemas e Impedimentos
- O driver de motor disponível no kit precisa ter sua capacidade de corrente verificada sob carga para evitar sobreaquecimento ou danos durante o uso contínuo.

### Decisões Técnicas da Semana
- Adotar o microcontrolador ESP32 como unidade central de processamento e controle.
- Manter o protocolo UDP unicast na porta 5000 para recepção de comandos JSON e o protocolo MQTT na porta 1883 para envio de telemetria.
- Projetar uma placa PCB própria (sob responsabilidade de Andrielle) para integrar alimentação, conectores e driver, eliminando o uso de protoboards e jumpers soltos[cite: 1].

### Testes Realizados
- **Teste 1 (17/09/2026) — Energização do ESP32:**
  - *Procedimento:* Conexão do ESP32 ao barramento de alimentação regulado em bancada.
  - *Resultado:* Inicialização correta do microcontrolador sem variações de tensão.
  - *Ação:* Liberado para implementação do firmware de recepção JSON.

- **Teste 2 (17/09/2026) — Rotação dos Motores DC:**
  - *Procedimento:* Aplicação de sinal de controle direto nos dois motores DC do kit.
  - *Resultado:* Ambos os motores apresentaram rotação adequada nos dois sentidos.
  - *Ação:* Medir corrente de pico sob carga real na próxima semana.

### Comparativo: Planejado vs. Realizado
- **Previsto:** Estruturação completa do repositório, documentação inicial e solicitação do kit de materiais[cite: 1].
- **Entregue:** 100% das entregas de documentação e planejamento concluídas dentro do prazo estipulado para a Etapa 01[cite: 1].

### Próximas Ações (Semana 2)
- Desenvolver e testar o código em C++/Arduino no ESP32 para deserialização de comandos JSON via Serial e UDP.
- Projetar e montar a estrutura física do suporte para o smartphone no chassi do carrinho.
- Iniciar os testes de transmissão de vídeo via IP com o celular embarcado.

---

## Semana 2 — 23/09/2026 a 29/09/2026

### Atividades Planejadas
- Desenvolver o firmware do ESP32 para recepção de comandos via protocolo MQTT.
- Integrar os pinos de controle do ESP32 com o driver de motores Ponte H L298N.
- Implementar a lógica de tração diferencial dos motores DC com controle de velocidade por PWM.
- Testar a rotação individual dos motores em bancada.

### Atividades Concluídas
- Desenvolvimento da estrutura base do código em C++/Arduino com as bibliotecas `PubSubClient` e `ArduinoJson`.
- Conexão Wi-Fi e subscrição MQTT no broker `broker.emqx.io` (tópico `tuni/carrinho/comandos`).
- Implementação do controle PWM (`0` a `255`) para acionamento das saídas do driver.
- Adicionada a compensação de zona morta (`PWM_MINIMO = 75`) para vencer o atrito inicial dos motores da L298N.
- Testes de bancada concluídos com validação do sentido de rotação dos motores.

### Atividades Não Concluídas
- Integração física com o módulo transmissor do volante (programada para as semanas seguintes).

### Problemas e Impedimentos
- A queda de tensão na ponte H L298N impedia o arranque dos motores com valores baixos de PWM.
- **Solução:** Implementada uma função de remapeamento no ESP32 para garantir que qualquer valor de movimento aplique no mínimo o PWM de `75`.

### Decisões Técnicas da Semana
- Adotar a lógica de tração diferencial para controlar direção e velocidade usando apenas os dois motores principais.
- Utilizar a verificação de chaves no JSON com `doc.containsKey()` para permitir o processamento flexível de dados.

### Testes Realizados
- **Teste 1 (25/09/2026) — Validação do Firmware e Callback MQTT:**
  - *Procedimento:* Envio manual de mensagens MQTT de teste para o ESP32.
  - *Resultado:* O microcontrolador recebeu os pacotes e imprimiu os dados no Monitor Serial.
  - *Ação:* Aprovado para o teste físico do acionamento dos motores.
- **Teste 2 (28/09/2026) — Rotação dos Motores em Bancada:**
  - *Procedimento:* Acionamento dos motores sem carga para verificar os sentidos de avanço e ré.
  - *Resultado:* Motores responderam corretamente aos comandos de rotação diferencial.
  - *Ação:* Firmware do carrinho liberado para a fase de integração com o volante.

### Comparativo: Planejado vs. Realizado
- **Previsto:** Estruturar e testar a lógica de controle do carrinho via MQTT em bancada.
- **Entregue:** 100% do código base, recepção MQTT e acionamento da Ponte H L298N concluídos.

### Próximas Ações
- Preparar o firmware e o hardware do volante físico de controle.
- Estruturar o protocolo de comunicação final entre o volante e o carrinho.

---

## Semana 3 — 30/09/2026 a 06/10/2026

### Atividades Planejadas
- Estruturar o envio de dados do volante físico de controle para o protocolo MQTT.
- Preparar o ambiente de testes para a integração física entre o volante e o carrinho.
- Adequar os intervalos de transmissão de mensagens para evitar congestionamento na rede Wi-Fi.

### Atividades Concluídas
- Mapeamento das leituras de controle do volante físico e estruturação das variáveis de saída.
- Ajuste na taxa de envio das mensagens MQTT para transmissão contínua sem travamentos.
- Validação preliminar do envio de pacotes do volante para o broker MQTT.

### Atividades Não Concluídas
- Teste prático de rodagem do conjunto no chão (transferido para a Semana 4).

### Problemas e Impedimentos
- Alta frequência de envio de mensagens no volante gerava latência na rede durante os testes iniciais.
- **Solução:** Configurado um intervalo mínimo entre envios (debounce temporal) para otimizar a transmissão.

### Decisões Técnicas da Semana
- Manter o tópico `tuni/carrinho/comandos` como canal único e padronizado de comunicação entre o volante e o carrinho.

### Testes Realizados
- **Teste 1 (03/10/2026) — Estabilidade do Transmissor do Volante:**
  - *Procedimento:* Monitoramento dos dados publicados pelo volante no broker MQTT.
  - *Resultado:* Pacotes entregues com regularidade e sem perdas de conexão.
  - *Ação:* Sistema de transmissão liberado para o teste de integração final com o veículo.

### Comparativo: Planejado vs. Realizado
- **Previsto:** Preparar o volante para integração e validar o envio de dados via MQTT.
- **Entregue:** 100% da etapa de preparação do volante e validação da transmissão concluídas.

### Próximas Ações
- Executar os testes práticos de integração física (Volante + Carrinho) e validar a estrutura do pacote JSON final.
- Apresentar o protótipo ao professor orientador.

---

## Semana 4 — 07/10/2026 a 13/10/2026

### Atividades Planejadas
- Realizar os testes práticos de integração em tempo real entre o volante físico e o carrinho no chão.
- Definir e padronizar o formato definitivo da estrutura do pacote JSON.
- Apresentar o protótipo funcional ao professor orientador para avaliação técnica.
- Atualizar a documentação do projeto no repositório GitHub (`PROGRESSO.md`).

### Atividades Concluídas
- **Validação Integrada (09/10/2026):** Conexão e teste prático realizados com sucesso entre o volante físico e o carrinho andando no chão em tempo real.
- **Padronização do JSON (09/10/2026):** Definida a estrutura final e unificada do payload enviada pelo volante: `{"volante": -1.0 a 1.0, "acelerador": -1.0 a 1.0}`.
- Apresentação do protótipo ao professor orientador (Jefferson Doolan), que aprovou o funcionamento lógico, mas solicitou a adequação da parte física para ocultar a fiação e protoboard expostas.
- Definição da solução da equipe: planejamento para a compra de um carrinho de brinquedo comercial para reutilizar a sua carcaça como chassi protetor fechado.

### Atividades Não Concluídas
- Compra física do carrinho de brinquedo e montagem da eletrônica em seu interior (planejadas para os próximos dias).

### Problemas e Impedimentos
- Na avaliação do orientador, os fios e componentes expostos na protoboard foram apontados como um ponto de vulnerabilidade e acabamento inadequado.
- **Solução:** A equipe decidiu adquirir um carrinho de brinquedo para embutir o ESP32, a ponte H L298N e as baterias dentro da carcaça, eliminando fiações visíveis.

### Decisões Técnicas da Semana
- Padronizar o pacote JSON definitivo com valores decimais (`float`) entre `-1.0` e `1.0` para facilidade de escala da tração diferencial.
- Utilizar a carcaça de um carrinho de brinquedo como invólucro estético e de proteção para o circuito elétrico.

### Testes Realizados
- **Teste 1 (09/10/2026) — Integração Volante + Carrinho e Formato JSON:**
  - *Procedimento:* Pilotagem do carrinho no chão utilizando o volante físico, enviando o pacote final `{"volante": x, "acelerador": y}` via MQTT.
  - *Resultado:* O carrinho respondeu com excelente precisão às curvas e acelerações, confirmando o pleno funcionamento do firmware e da comunicação.
  - *Ação:* Formato JSON e integração lógica declarados totalmente aprovados.

### Comparativo: Planejado vs. Realizado
- **Previsto:** Testar o conjunto volante e carrinho, definir o pacote JSON final e apresentar o progresso ao orientador.
- **Entregue:** 100% dos testes de integração e formato JSON validados, com o plano de ação traçado para a solução do chassi solicitada pelo professor.

### Próximas Ações
- Comprar o carrinho de brinquedo selecionado.
- Adaptar a carcaça física e realizar a instalação interna do ESP32, driver L298N e fiação.
- Executar os testes finais de rodagem com a nova estrutura fechada.
