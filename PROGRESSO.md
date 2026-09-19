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

## Modelo para Registros das Próximas Semanas

*(Copie o bloco abaixo para registrar o andamento de cada nova semana)*

```text
## Semana X — DD/MM/AAAA a DD/MM/AAAA

### Atividades Planejadas
- ...

### Atividades Concluídas
- ...

### Atividades Não Concluídas
- ...

### Problemas e Impedimentos
- ...

### Decisões Técnicas da Semana
- ...

### Testes Realizados
- **Teste X (DD/MM/AAAA) — Nome do Teste:**
  - *Procedimento:* ...
  - *Resultado:* ...
  - *Ação:* ...

### Comparativo: Planejado vs. Realizado
- **Previsto:** ...
- **Entregue:** ...

### Próximas Ações
- ...
