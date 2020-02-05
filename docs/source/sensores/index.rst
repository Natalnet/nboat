
.. _water-sensors:

********
Sensores
********

Aqui é tratado a parte específica de montagem e conexões dos sensores.


Pixhawk
-------

A pixhawk, que está localizada no compartimento 3, deve receber sinais dos sensores e enviar comandos para os atuadores da vela e do leme. Os sensores padrão que vem no kit pixhawk são um GPS com IMU e o módulo de potencia, que calcula a tensão e corrente a fim de estimar o consumo total da bateria e a carga restante.

No esquema de conexão atual a pixhawk apenas envia os comandos PWM para a placa central, e o sistema implementado nela funciona como uma interface, que recebe um sinal de PWM, traduz para ângulo de vela e leme e comanda os atuadores para levar por a vela e o leme na posição desejada. Como há essa separação entre pixhawk e atuadores, a pixhawk não tem acesso a informações importantes como consumo e posição dos atuadores.

Desta forma, existe uma cominicação serial entre a pixhawk e o driver dos atuadores onde a pixhawk:

- Envia sinais de PWM;
- Recebe estado dos atuadores (consumo, posição, velocidade de rotação);

A conexão para envio de sinais de PWM é mostrada abaixo.

.. image:: ./images/px1.jpg
    :width: 60 %
    :align: center

A conexão para comunicação serial é mostrada abaixo

.. image:: ./images/px3.jpg
    :width: 49 %

.. image:: ./images/px4.jpg
    :width: 49 %



A pixhawk também recebe os sinais do sensores do vento.


Sensores de vento
-----------------

O sensor de direção do vento é composto por um potenciometro de posição absoluta que rotaciona de acordo com a direção do vento. O sensor de velocidade do vento é um conjunto de copos que gira e fecha um circuito funcionando como um botão. O número de clicks indica a velocidade do vento.

A imagem abaixo mostra como os sensores do vento são conectados à pixhawk.

.. image:: ./images/px2.jpg
    :width: 60 %
    :align: center


Algumas configurações na pixhawk são necessárias para os sinais lidos dos sensores de vento. Mais detalhes da configuração neste `post <https://discuss.ardupilot.org/t/sailboat-support/32060/506>`_.

.. image:: ./images/anemometer_bb.png
    :width: 60 %
    :align: center