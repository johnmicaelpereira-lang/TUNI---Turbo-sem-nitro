# Registro de Progresso — Projeto Integrador

---

## Identificação do Projeto

- **Nome da equipe:** TUNI - Turbo Sem Nitro
- **Turma:** Meca3V
- **Professor técnico / Orientador:** Jefferson Doolan

Este arquivo armazena o histórico semanal de desenvolvimento do veículo. Os registros das semanas anteriores são mantidos permanentemente para fins de auditoria e acompanhamento do progresso real em relação ao planejado. Alterações no cronograma e suas justificativas estão em [PLANEJAMENTO.md](./PLANEJAMENTO.md).

---

## Semana 1 — 16/09/2026 a 22/09/2026

### Atividades Planejadas
- Definir a arquitetura geral do veículo e o conceito da solução.
- Escolher a arquitetura de tração e direção (diferencial com dois motores DC).
- Estruturar o repositório público no GitHub com as pastas obrigatórias (`docs/software/`, `docs/mecanica/`, `docs/eletronica/` e `docs/testes/`).
- Elaborar os arquivos fundamentais de documentação (`README.md`, `PLANEJAMENTO.md` e `PROGRESSO.md`).
- Enviar a solicitação formal de materiais do kit para a COLAB (`colab.par@ifrn.edu.br`) com cópia para o orientador.

### Atividades Concluídas
- Arquitetura geral do veículo e subsistemas definidos.
- Escolha da tração diferencial com 2 motores DC e controle de velocidade via PWM.
- Repositório público criado no GitHub.
- Arquivos `README.md`, `PLANEJAMENTO.md` e `PROGRESSO.md` criados.
- Solicitação formal de materiais encaminhada à COLAB com o assunto padronizado.

### Atividades Não Concluídas
- Medição da corrente de partida dos motores sob carga (adiada para a validação do driver de potência). **Continua pendente.**

### Problemas e Impedimentos
- O driver de motor do kit precisa ter sua capacidade de corrente verificada sob carga para evitar sobreaquecimento ou danos durante o uso contínuo.

### Decisões Técnicas da Semana
- Adotar o microcontrolador ESP32 como unidade central de processamento e controle.
- Manter o protocolo UDP unicast na porta 5000 para comandos JSON do volante oficial e o MQTT na porta 1883 para telemetria (previstos pelo regulamento). *(Atualização de 17/10: o MQTT passou a ser o protocolo final de comandos; ver Semana 5.)*
- Projetar uma placa PCB própria (responsável: Andrielle) para integrar alimentação, conectores e driver, eliminando protoboards e jumpers soltos.

### Testes Realizados
- **Teste 1 (17/09/2026) — Energização do ESP32:**
  - *Procedimento:* Conexão do ESP32 ao barramento de alimentação regulado em bancada.
  - *Resultado:* Inicialização correta do microcontrolador sem variações de tensão.
  - *Ação:* Liberado para implementação do firmware de recepção JSON.

- **Teste 2 (17/09/2026) — Rotação dos Motores DC:**
  - *Procedimento:* Aplicação de sinal de controle direto nos dois motores DC do kit.
  - *Resultado:* Ambos os motores apresentaram rotação adequada nos dois sentidos.
  - *Ação:* Medir corrente de pico sob carga real.

### Comparativo: Planejado vs. Realizado
- **Previsto:** Estruturação do repositório, documentação inicial e solicitação do kit de materiais.
- **Entregue:** 100% das entregas previstas para a semana (repositório, documentação inicial e solicitação de materiais).

### Próximas Ações (Semana 2)
- Desenvolver e testar o código C++/Arduino no ESP32 para receber comandos JSON.
- Projetar a estrutura física do suporte do smartphone.
- Iniciar os testes de transmissão de vídeo com o celular embarcado.

---

## Semana 2 — 23/09/2026 a 29/09/2026

### Atividades Planejadas
- Desenvolver o firmware do ESP32 para recepção de comandos via protocolo MQTT.
- Integrar os pinos de controle do ESP32 com o driver de motores Ponte H L298N.
- Implementar a lógica de tração diferencial dos motores DC com controle de velocidade por PWM.
- Testar a rotação individual dos motores em bancada.

### Atividades Concluídas
- Estrutura base do código C++/Arduino com as bibliotecas `PubSubClient` e `ArduinoJson`.
- Conexão Wi-Fi e subscrição MQTT no broker `broker.emqx.io` (tópico `tuni/carrinho/comandos`).
- Controle PWM (0 a 255) para acionamento das saídas do driver.
- Compensação de zona morta (`PWM_MINIMO = 75`) para vencer o atrito inicial dos motores.
- Testes de bancada concluídos com validação do sentido de rotação dos motores.

### Atividades Não Concluídas
- Integração física com o módulo transmissor do volante (programada para as semanas seguintes).
- Suporte físico do smartphone e testes de vídeo (reprogramados; ver [PLANEJAMENTO.md](./PLANEJAMENTO.md)).

### Problemas e Impedimentos
- A queda de tensão na ponte H L298N impedia o arranque dos motores com valores baixos de PWM.
- **Solução:** remapeamento no ESP32 para que qualquer movimento aplique no mínimo o PWM de `75`.

### Decisões Técnicas da Semana
- Adotar a lógica de tração diferencial para controlar direção e velocidade com os dois motores.
- Usar `doc.containsKey()` no JSON para permitir o processamento flexível de dados.
- Validar o controle por MQTT antes de implementar o UDP.

### Testes Realizados
- **Teste 1 (25/09/2026) — Validação do Firmware e Callback MQTT:**
  - *Procedimento:* Envio manual de mensagens MQTT de teste para o ESP32.
  - *Resultado:* O microcontrolador recebeu os pacotes e imprimiu os dados no Monitor Serial.
  - *Ação:* Aprovado para o teste físico do acionamento dos motores.
- **Teste 2 (28/09/2026) — Rotação dos Motores em Bancada:**
  - *Procedimento:* Acionamento dos motores sem carga para verificar avanço e ré.
  - *Resultado:* Motores responderam corretamente aos comandos de rotação diferencial.
  - *Ação:* Firmware liberado para a integração com o volante.

### Comparativo: Planejado vs. Realizado
- **Previsto:** Estruturar e testar a lógica de controle do carrinho via MQTT em bancada.
- **Entregue:** Código base, recepção MQTT e acionamento da Ponte H L298N concluídos. Suporte do smartphone não concluído.

### Próximas Ações
- Preparar o firmware e o hardware do volante físico de controle.
- Estruturar o protocolo de comunicação entre o volante e o carrinho.

---

## Semana 3 — 30/09/2026 a 06/10/2026

### Atividades Planejadas
- Estruturar o envio de dados do volante físico para o protocolo MQTT.
- Preparar o ambiente de testes para a integração física entre o volante e o carrinho.
- Adequar os intervalos de transmissão de mensagens para evitar congestionamento na rede Wi-Fi.

### Atividades Concluídas
- Mapeamento das leituras de controle do volante físico e estruturação das variáveis de saída.
- Ajuste na taxa de envio das mensagens MQTT para transmissão contínua sem travamentos.
- Validação preliminar do envio de pacotes do volante para o broker MQTT.

### Atividades Não Concluídas
- Teste prático de rodagem do conjunto no chão (transferido para a Semana 4).
- Esquemático elétrico inicial (previsto no cronograma; ainda pendente).

### Problemas e Impedimentos
- A alta frequência de envio de mensagens no volante gerava latência na rede nos testes iniciais.
- **Solução:** intervalo mínimo entre envios (debounce temporal) para otimizar a transmissão.

### Decisões Técnicas da Semana
- Manter o tópico `tuni/carrinho/comandos` como canal único e padronizado entre o volante e o carrinho.

### Testes Realizados
- **Teste 1 (03/10/2026) — Estabilidade do Transmissor do Volante:**
  - *Procedimento:* Monitoramento dos dados publicados pelo volante no broker MQTT.
  - *Resultado:* Pacotes entregues com regularidade e sem perdas de conexão.
  - *Ação:* Sistema de transmissão liberado para o teste de integração com o veículo.

### Comparativo: Planejado vs. Realizado
- **Previsto:** Preparar o volante para integração e validar o envio via MQTT.
- **Entregue:** Preparação do volante e validação da transmissão concluídas. Esquemático da PCB não iniciado.

### Próximas Ações
- Testes práticos de integração física (volante + carrinho) e validação do pacote JSON final.
- Apresentar o protótipo ao professor orientador.

---

## Semana 4 — 07/10/2026 a 13/10/2026

### Atividades Planejadas
- Testes práticos de integração em tempo real entre o volante físico e o carrinho no chão.
- Definir e padronizar o formato definitivo do pacote JSON.
- Apresentar o protótipo funcional ao professor orientador.
- Atualizar a documentação no GitHub (`PROGRESSO.md`).

### Atividades Concluídas
- **Validação integrada (09/10/2026):** teste prático com o volante físico e o carrinho andando no chão em tempo real.
- **Padronização do JSON (09/10/2026):** estrutura final enviada pelo volante: `{"volante": -1.0 a 1.0, "acelerador": -1.0 a 1.0}`.
- Apresentação do protótipo ao orientador (Jefferson Doolan), que aprovou o funcionamento lógico e pediu a adequação da parte física para ocultar fiação e protoboard expostas.
- Definição da solução da equipe: planejar uma carcaça fechada de carrinho comercial como chassi protetor.

### Atividades Não Concluídas
- Compra do carrinho de brinquedo e montagem da eletrônica em seu interior.

### Problemas e Impedimentos
- Na avaliação do orientador, fios e componentes expostos na protoboard foram apontados como ponto de vulnerabilidade e acabamento inadequado.
- **Solução prevista:** embutir ESP32, L298N e baterias dentro de uma carcaça, eliminando fiações visíveis.

### Decisões Técnicas da Semana
- Padronizar o pacote JSON com valores decimais (`float`) entre `-1.0` e `1.0` para facilitar a escala da tração diferencial.
- Usar uma carcaça fechada como invólucro estético e de proteção do circuito.

### Testes Realizados
- **Teste 1 (09/10/2026) — Integração Volante + Carrinho e Formato JSON:**
  - *Procedimento:* Pilotagem do carrinho no chão com o volante físico, enviando `{"volante": x, "acelerador": y}` via MQTT.
  - *Resultado:* O carrinho respondeu às curvas e acelerações; firmware e comunicação funcionaram.
  - *Ação:* Formato JSON e integração lógica aprovados.

### Comparativo: Planejado vs. Realizado
- **Previsto:** Testar o conjunto volante e carrinho, definir o pacote JSON final e apresentar o progresso ao orientador.
- **Entregue:** Testes de integração e formato JSON validados, com plano de ação para o acabamento pedido pelo professor.

### Próximas Ações
- Definir o novo carrinho/carcaça e adaptar a eletrônica em seu interior.
- Executar os testes finais de rodagem com a estrutura fechada.

---

## Semana 5 — 14/10/2026 a 20/10/2026

### Atividades Planejadas
- Definir o carrinho/carcaça para o acabamento fechado e iniciar a adaptação.
- Preparar a revisão da Etapa 1 com os avaliadores (terça, 20/10/2026).

### Atividades Concluídas
- Ajustes e organização do carrinho atual (chassi 2WD já existente), deixando-o em condições de demonstração.
- **Otimização do firmware (15/10/2026):** o controle apresentava travamentos; foram aplicados `WiFi.setSleep(false)`, `setNoDelay(true)` e leitura do JSON direto do buffer, sem conversão para `String`.
- **Teste de pilotagem (16/10/2026)** com o volante após as otimizações.
- **Decisão (15/10/2026):** não trocar o carrinho nesta etapa e pesquisar um modelo melhor.
- **Documentação técnica básica (17/10/2026):** pinagem, desenho básico de ligações e fotos do carrinho em `docs/`. Desenho técnico do chassi (vistas superior e inferior) também incluído.

### Atividades Não Concluídas
- Adaptação da eletrônica em carcaça fechada (adiada por decisão de 15/10).
- PCB, integração do smartphone e medição de corrente (ver pendências). O esquemático básico de ligações foi feito em 17/10.

### Problemas e Impedimentos
- O controle ainda apresentava travamentos e pouca fluidez antes da otimização do firmware.
- Fiação e componentes continuam expostos (ver fotos em `docs/mecanica/`).
- **Ação corretiva:** ajuste do firmware (feito); acabamento fechado reprogramado.

### Decisões Técnicas da Semana
- Manter o chassi atual até a revisão da Etapa 1, priorizando o sistema de controle funcionando.
- Pesquisar um carrinho melhor para o acabamento definitivo.
- Confirmado que o **MQTT será o protocolo final** de comunicação do projeto.
- Remover a senha do Wi-Fi do código publicado (credencial em arquivo `secrets.h` fora do Git).

### Testes Realizados
- **Teste (16/10/2026) — Pilotagem com o volante após otimização:**
  - *Procedimento:* Pilotagem livre do carrinho com o volante físico (teste informal, sem instrumentos de medição).
  - *Resultado:* Resposta mais fluida, com menos travamentos que antes do ajuste.
  - *Ação:* Medir a latência de forma objetiva nas próximas semanas.

### Comparativo: Planejado vs. Realizado
- **Previsto (cronograma 14/10 a 20/10):** demonstração prática do subsistema e comparação planejado x realizado no `PROGRESSO.md`.
- **Entregue:** subsistema de controle sem fio + motores funcionando e otimizado, documentação atualizada. O acabamento fechado e a PCB seguem pendentes.

### Próximas Ações
- Revisão da Etapa 1 com os avaliadores (terça, 20/10/2026).
- Esquemático detalhado/PCB e acabamento da fiação.
- Parada de segurança no firmware.
- Medir corrente e temperatura da L298N.
- Validar as cotas estimadas do desenho técnico e medir o carrinho atual (limite 300 x 200 mm; o projeto prevê 213 x 110 mm).
- Integrar o smartphone Android e o app oficial de vídeo quando divulgado.
