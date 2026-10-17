# Mecânica

## Chassi atual
- Chassi 2WD de acrílico transparente que a equipe já possuía, com 2 motores DC amarelos com caixa de redução e rodas de borracha.
- Tração: 2 motores nas rodas laterais. Direção: diferencial (diferença de velocidade entre os lados), sem servo.
- Fixação provisória: ESP32 e L298N presos com fita 3M VHB; bateria envolta em fita isolante e presa com abraçadeiras de nylon; chave gangorra na parte traseira.

## Fotos (17/10/2026)
![Vista superior](./foto_carrinho_vista_superior.jpg)
![Vista lateral](./foto_carrinho_lateral.jpg)

## Projeto do chassi (desenho técnico)
Desenho completo: [desenho_tecnico_chassi.pdf](./desenho_tecnico_chassi.pdf) (folha 1: vista superior; folha 2: vista inferior). Cotas marcadas com ≈ são estimadas e devem ser validadas nos componentes físicos antes do corte/impressão.

| Item | Dimensões (mm) |
|---|---|
| Comprimento total | ≈ 213 |
| Largura do chassi | ≈ 110 |
| Rodas principais (2x) | Ø 56 x 26,6 |
| Motor DC + caixa de redução (2x) | 64,2 x 22,5 x 18,8 (eixo Ø 5,4; furos 2x Ø 3) |
| Roda boba (apoio frontal) | base 38 x 32; roda Ø 25–30; altura 30–34; furos Ø 4 |
| ESP32 | 53 x 24 |
| Ponte H L298N | 43 x 43 |
| Suporte do celular | 163,7 x 76,1 x 7,6 (aparelho) |
| Baterias (2 células 3,7 V) | dimensões não informadas |

Limite do regulamento: 300 x 200 mm. O projeto (213 x 110 mm) está dentro do limite.

## Carrinho atual (dimensões)
- Comprimento: [PREENCHER] mm
- Largura: [PREENCHER] mm

## Peças projetadas / modificadas
- Fixações improvisadas (fita VHB e abraçadeiras) para ESP32, L298N e bateria.
- Suporte do smartphone: pendente (ver PLANEJAMENTO.md).

## Decisões relevantes
- 09/10: orientador pediu ocultar fiação e componentes expostos; solução prevista: carcaça fechada.
- 15/10: manter o chassi atual nesta etapa e pesquisar um modelo melhor.
