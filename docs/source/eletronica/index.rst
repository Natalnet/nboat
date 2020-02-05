
.. _nboat:

..
	sensors
	calibration
	connections
	challenges
	bugs
	softwares

==========
Eletrônica
==========


A parte eletrônica do veleiro Nboat é composta por:

- Placa central para o driver dos atuadores;
- Driver dos atuadores dual-vnh5019-motor-shield (acoplado ao arduino uno);
- Um arduino Mega;
- Um arduino Uno;
- Potenciômetro da vela;
- Potenciômetro do leme;
- Sensores do vento;
- Pixhawk 2.4.6
    - GPS
    - IMU
    - Telemetria 433 MHz
- Raspberry Pi;
- Modem wifi;
- Ubiquiti UNIFI AC MESH;
- Buzina;
- Transmissor e receptor Rádio R7;

Uma breve explicação sobre cada componente é dada a seguir.

Placa central
-------------

A placa central conecta e alimenta todos os componentes dos drivers: os potenciômetros, os arduinos e o dual-vnh5019-motor-shield, além de interfacear com a pixhawk. Ela fica localizada dentro da caixa preta no compartimento 3 e a ideia é que os sinais de dados que vêm dos outros compartimentos são conectados a essa placa usando cabos de rede rj45.

Shield atuadores
----------------

O dual-vnh5019-motor-shield manda sinais de PWM para os atuadores. Possui limite de corrente de 12A com picos de 30A por canal, sendo dois canais de saída, um para o guincho da vela e outro para o atuador linear do leme.

Arduinos
--------

O arduino mega recebe sinal de PWM (faixa de 1000 a 2000), traduz esse sinal para valores de ângulos de atuador ([-90, 90] graus) e envia por I2C para o arduino uno.

O arduino uno está conectado ao shield dual-vnh5019-motor-shield e nele está o controle PID de posição dos atuadores. Este controle lê o valor do potenciômetro da porta analógica [0, 1023] (10 bits), traduz para valor de ângulo de atuador e compara com o ângulo enviado pelo arduino mega, gerando um erro. Neste erro são aplicados os ganhos P e I e então este valor é passado como velocidade para o atuador ([-400, 400]) usando a função *md.setM1Speed(velocidade)* como exemplo de velocidade para o canal M1.

Potenciômetros
--------------

Os potenciômetros da vela e do leme servem para dar ao controlador de posição dos atuadores um retorno sobre a posição atual do atuador. O pot do leme é montado na parte superior do leme, que fica dentro do compartimento 4 e gira junto com o leme, mapeando sua posição. O pot da vela está no compartimento 2. A impressora 3d foi usada para fazer uma peça que encaixa no eixo do guincho e, a medida que ele gira, também gira o potenciômetro que está acoplado na base.

Sensores de vento
-----------------

Os sensores de vento ficam na proa do nboat. No momento temos um que mede a velocidade (speed) e o outro mede a direção. Essas informações do vento são usadas pela Pixhawk para calcular a posição da vela para que o veleiro ganhe velocidade. 

Pixhawk
-------

A pixhawk é o processador central de baixo nível. Nela ficam os controles de movimento do nboat e o planejamento da missão, além da coleta dos dados dos sensores. O kit Pixhawk vem com um IMU e um GPS, e a pixhawk faz toda a parte de filtragem dos dados, estimação do estado e navegação (no sentido Fossen). A pixhawk roda Ardupilot Ardurover com configuração específica para veleiro. O firmware e os parâmetros podem ser encontrados neste branch.

Raspberry Pi
------------

A Raspberry Pi fica com o processamento de alto nível, que é o processamento de imagem ou outra operação mais exija mais processamento e memória. Ela também serve de interface wifi com o mundo externo, já que se conecta a Pixhawk e consegue ler seus valores usando o MAVROS.

WiFi
----

O Ubiquiti UNIFI AC MESH serve para extender o sinal wifi gerado pelo nboat e permitir comunicação de alta velocidade com a estação base.

O modem wifi cria e gerencia a rede interna, que conecta o Ubiquiti UNIFI AC MESH e a raspberry.