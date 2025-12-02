# DryBox IoT: Sistema de Monitoramento e Preservação de Filamentos

| | |
|:-------------------------:|:-------------------------:|
| <img src="./Imagens/montagem-final.jpeg" width="100%" alt="Visão Frontal"> | <img src="./Imagens/montagem-final-2.jpeg" width="100%" alt="Visão Lateral"> |

## Visão Geral

O projeto **DryBox IoT** consiste em uma solução de hardware e software para o armazenamento monitoramento de filamentos para impressão 3D.

Filamentos termoplásticos, como o PLA, são higroscópicos e tendem a absorver a umidade do ambiente. A água absorvida transforma-se em vapor durante o processo de extrusão, criando tensões internas, falhas estruturais e tornando o material quebradiço. Este projeto mitiga esses problemas mantendo o filamento em um ambiente controlado e monitorado remotamente.

## Funcionalidades

* **Monitoramento em Tempo Real:** Leitura contínua de temperatura e umidade relativa interna via sensor DHT22.
* **Conectividade IoT:** Utilização do microcontrolador ESP32 para processamento de dados e conectividade Wi-Fi/Bluetooth.
* **Interface de Monitoramento:** Dashboard visual que categoriza a qualidade do ambiente de armazenamento.
* **Desumidificação Passiva:** Integração com desumidificadores químicos (Cloreto de Cálcio) para redução ativa da umidade.

## Interface do Sistema

O sistema disponibiliza uma interface gráfica para visualização rápida dos parâmetros ambientais.

| Status Ideal | Status de Atenção | Status Crítico |
| :---: | :---: | :---: |
| <img src="./Imagens/app-3.jpeg" height="400" alt="Ambiente Perfeito"> | <img src="./Imagens/app-2.jpeg" height="400" alt="Atenção"> | <img src="./Imagens/app-1.jpeg" height="400" alt="Crítico"> |

## Lista de Materiais

Abaixo estão listados os componentes necessários para a montagem do projeto.

| Componente | Imagem | Descrição |
| :--- | :---: | :--- |
| **Microcontrolador ESP32** | <img src="./Imagens/esp32.jpeg" width="150"> | Responsável pelo processamento e conectividade Wi-Fi. |
| **Sensor DHT22** | <img src="./Imagens/dht22.jpeg" width="150"> | Sensor digital para leitura precisa de temperatura e umidade. |
| **Recipiente Hermético** | <img src="./Imagens/pote.jpeg" width="150"> | Caixa organizadora com vedação para isolar o filamento. |
| **Desumidificador** | <img src="./Imagens/secador.jpeg" width="150"> | Pote de Cloreto de Cálcio (ex: Durasol) para absorção de umidade. |
| **Tubo PTFE e Conexões** | <img src="./Imagens/tubo-ptfe.jpeg" width="150"> | Guia o filamento para fora da caixa sem perder a vedação. |
| **Barra Roscada** | <img src="./Imagens/barra.jpeg" width="150"> | Eixo central para suporte e rotação do carretel. |

## Peças para Impressão 3D

Os arquivos para a fabricação das peças estruturais estão disponíveis no diretório `./Peças` no formato STP.

<img src="./Imagens/partes3d.jpeg" width="600" alt="Visão Geral das Peças">
<br>
<i>Visão geral de todas as peças impressas.</i>

| Peça | Imagem | Arquivo | Qtd | Descrição |
| :--- | :---: | :--- | :---: | :--- |
| **Case ESP32** | <img src="./Imagens/box-esp32.jpeg" width="150"> | `box-esp32-1x.stp` | 1 | Case externo para proteger a eletrônica e isolá-la do ambiente interno da caixa. |
| **Suporte Lateral** | <img src="./Imagens/apoio.jpeg" width="150"> | `apoio-2x.stp` | 2 | Suportes para a barra roscada e rolamentos. Devem ser colados ou fixados na lateral interna. |
| **Adaptador de Rolo** | <img src="./Imagens/rolo.jpeg" width="150"> | `rolo-filamento-1x.stp` | 1 | Centralizador cônico para manter o carretel alinhado no eixo. |
| **Trava do Rolo** | <img src="./Imagens/tampa.jpeg" width="150"> | `tampa-rolo-1x.stp` | 1 | Tampa rosqueável ou de pressão para travar o carretel no adaptador. |

## Criadores

O projeto não teria sido possível sem essas pessoas:

| Avatar | Nome |
| :---: | :--- |
| <img src="https://github.com/gui200428.png?size=80" width="80px" alt="Guilherme Augusto"/> | [Guilherme Augusto](https://github.com/gui200428) |
| <img src="https://github.com/jfscripts.png?size=80" width="80px" alt="João Francisco"/> | [João Francisco B. Ferreira](https://github.com/jfscripts) |
| <img src="https://github.com/Thales-Enrico.png?size=80" width="80px" alt="Thales Enrico"/> | [Thales Enrico S. da Silva](https://github.com/Thales-Enrico) |
| <img src="https://github.com/ronald-barbist.png?size=80" width="80px" alt="Vitor Ronald"/> | [Vitor Ronald Barbist](https://github.com/ronald-barbist) |
| <img src="https://github.com/LuccasHenrique13.png?size=80" width="80px" alt="Luccas Henrique"/> | [Luccas Henrique R. da Silva](https://github.com/LuccasHenrique13) |
| <img src="https://github.com/Miguelmotta.png?size=80" width="80px" alt="Miguel Arcanjo"/> | [Miguel Arcanjo B. Motta](https://github.com/Miguelmotta) |
| <img src="https://github.com/Mgonzalez980.png?size=80" width="80px" alt="Matheus Gonzalez"/> | [Matheus Gonzalez](https://github.com/Mgonzalez980) |
| <img src="https://github.com/higorrb.png?size=80" width="80px" alt="Higor Robert"/> | [Higor Robert Barbist](https://github.com/higorrb) |