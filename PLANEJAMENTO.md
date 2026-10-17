# 📅 Planejamento Geral do Projeto — Equipe TUNI

Este documento contém o cronograma de desenvolvimento do carrinho robotizado, desde o planejamento inicial até a competição final, com a situação atualizada em **17/10/2026**. Alterações em relação ao plano original estão registradas e justificadas na seção seguinte.

---

## 📊 Cronograma de Atividades

| Semana / Período | Marco / Etapa | Objetivo da Semana | Entregável Verificável | Responsável(is) | Situação / Observações |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **16/09 a 22/09/2026** | Início do Planejamento | Estruturar repositório público com pastas `docs/software/`, `docs/mecanica/`, `docs/eletronica/` e `docs/testes/` e solicitar materiais à COLAB. | Repositório no GitHub e e-mail enviado para `colab.par@ifrn.edu.br`. | Todos | Concluído |
| **23/09 a 29/09/2026** | Controle e Câmera | Programar o firmware do ESP32 para receber comandos JSON e confeccionar o suporte do smartphone. | Código de controle funcional no ESP32 e suporte físico da câmera montado. | John, Letícia | Parcial: firmware (via MQTT) concluído; suporte do smartphone reprogramado (alteração 1) |
| **30/09 a 06/10/2026** | Mapeamento Elétrico | Desenhar o esquemático elétrico inicial e realizar testes de telemetria/comunicação MQTT. | Esquemáticos em `docs/eletronica/` e logs de teste em `docs/software/`. | Andrielle, Luiz Carlos, Emili | Parcial: comunicação volante → MQTT validada; esquemático reprogramado (alteração 2) |
| **07/10 a 13/10/2026** | Integração de Bancada | Consolidar a integração dos motores com o controle e revisar a documentação do GitHub. | Subsistema de motores respondendo ao JSON e testes registrados. | Todos | Concluído, com integração direta no carrinho (alteração 3) |
| **14/10 a 20/10/2026** | Avaliação da Etapa 01 | Demonstração prática do subsistema de controle na revisão da Etapa 1 (terça, 20/10/2026) e comparação "planejado vs. realizado" no `PROGRESSO.md`. | Demonstração técnica realizada e comparação registrada. | Todos | Em andamento: firmware otimizado e documentação atualizada (alteração 4) |
| **21/10 a 27/10/2026** | Esquemático e Projeto da PCB | Detalhar o esquemático elétrico (a versão básica já foi feita) e rotear a PCB; definir o carrinho/carcaça para o acabamento fechado. | Esquemático e Gerber em `docs/eletronica/`; chassi/carcaça definido e registrado em `docs/mecanica/`. | Andrielle, Luiz Carlos, Emili | Planejado |
| **28/10 a 03/11/2026** | Hardware e Firmware | Confeccionar a PCB, organizar a fiação principal e implementar no firmware a parada de segurança por falta de comando. | PCB funcional, circuito montado e firmware com failsafe testado. | Andrielle, Emili, Letícia, John | Planejado (inclui alteração 5) |
| **04/11 a 10/11/2026** | Avaliação de Progresso 2 | Integrar o controle com a PCB e apresentar o progresso na Avaliação de Progresso 2 (10/11/2026). | Circuito impresso e sistema de controle funcionando na bancada. | Todos | Planejado |
| **11/11 a 17/11/2026** | Montagem Completa | Instalar PCB, motores, suporte do smartphone e bateria no chassi; integrar o app oficial de vídeo. | Carrinho totalmente montado, com câmera funcionando. | Emili, Andrielle, Letícia | Planejado |
| **18/11 a 24/11/2026** | Testes de Pista | Executar testes dinâmicos na pista e ajustar o streaming de vídeo. | Relatórios e logs de testes em pista em `docs/testes/`. | Letícia, John | Planejado |
| **25/11 a 01/12/2026** | Ajustes e Calibração | Eliminar perdas de pacotes Wi-Fi/MQTT, calibrar a tração diferencial e otimizar a bateria. | Firmware final otimizado com rotinas de segurança ativas. | John, Andrielle | Planejado |
| **02/12 a 08/12/2026** | Checklist de Validação | Verificar requisitos técnicos, dimensões (máx. 300 x 200 mm) e acabamento. | Checklist de validação preenchido e aprovado. | Todos | Planejado |
| **09/12 a 15/12/2026** | Treino Oficial | Treino oficial e homologação técnica do veículo (15/12/2026). | Veículo homologado para a competição. | Todos | Planejado |
| **16/12 a 18/12/2026** | Competição Final | Disputar a Competição Final (18/12/2026) e concluir a documentação do repositório. | Participação concluída e repositório finalizado. | Todos | Planejado |

---

## 🔁 Alterações no Planejamento e Justificativas

| # | Item | Planejado | O que aconteceu | Justificativa | Nova data |
|---|---|---|---|---|---|
| 1 | Firmware e suporte do smartphone (23–29/09) | Receber JSON via Serial/UDP e montar o suporte do smartphone | Firmware implementado com MQTT; suporte não montado | O MQTT permitiu validar o controle desde cedo e foi adotado como protocolo final do projeto (decisão de 17/10). Prioridade foi o controle | Suporte: 11–17/11. UDP: descartado (MQTT é o protocolo final) |
| 2 | Esquemático elétrico (30/09–06/10) | Esquemático inicial da PCB | Não concluído; preparação do volante e validação do MQTT | Prioridade foi integrar o volante ao carrinho | 21–27/10 |
| 3 | Integração (07–13/10) | Integração em bancada | Integração feita com o carrinho andando no chão (09/10) | Teste mais representativo do uso real; orientador pediu ocultar fios e protoboard | – |
| 4 | Troca de chassi (14–20/10) | Comprar carrinho e embutir a eletrônica | Decisão de 15/10 de manter o chassi atual e pesquisar um melhor | Priorizar a revisão da Etapa 1 com o sistema funcionando; houve ajuste de firmware para reduzir travamentos | 21–27/10 (definição do chassi) |
| 5 | Novas tarefas | – | Incluídas: parada de segurança, medição de corrente da L298N, conferência de dimensões, integração do app oficial | Exigências do regulamento e riscos identificados na revisão da documentação | 28/10–03/11 e 02–08/12 |

---
**Planilha de Origem:** [📊 Visualizar Cronograma no Google Sheets](https://docs.google.com/spreadsheets/d/1d_tU83n73x08jS0sawkWj94B5m-8b2BaryHRzuHTrT0/edit?usp=sharing)

> Atualize também a planilha do Google Sheets com as mesmas alterações, para ela bater com este arquivo.
