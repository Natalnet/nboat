============
Experimentos
============


Montagem do veleiro
-------------------

1) O primeiro passo é montar o leme. Devido ao seu tamanho, talvez seja preciso levantar o casco para encaixar o leme em seu compartimento. Duas pessoas (ou mais) levantam o casco enquanto uma pessoa vai por baixo e encaixa o leme no seu buraco. Em seguida o casco é baixado até descançar novamente na carroça. Alternativamente, o engate da carroça, que neste momento está apoiado em uma cadeira ou uma caixa, pode ser descido até o chão, de forma que a traseira se eleve e talvez dê para encaixar o leme. Após esta etapa, uma pessoa mantém o leme elevado e, pelo compartimento 4, a haste que encaixa no atuador linear é aparafusada ao leme. Em seguida é preciso calibrar o leme. Com o sistema do veleiro e o rádio ligado, certifique-se que há o controle manual pelo rádio movendo os sticks e vendo se o leme e/ou a vela se mexem. Então, deixe o stick do leme (stick direito, movimento horizontal) na posição central e gire o potenciometro cuidadosamente. Perceba que girando o potenciometro em um sentido o atuador retrai e girando em outro sentido o atuador abre. Então, observando a faixa de cores no atuador linear, ajuste o potenciometro até que o atuador pare na cor preta. Em seguida, encaixe o braço do potenciometro na vela, tendo cuidado para manter a posição do potenciometro (normalemente ele gira um pouco e o atuador se move). Por fim, use os trims para um ajuste fino do leme, de modo que ele fique alinhado corretamente;

2) A segunda parte a ser montada é a bolina. Com o veleiro em cima da carroça de transporte, duas pessoas (ou mais) levantam o casco verticalmente enquanto outras duas (ou mais) posicionam a bolina no centro da carroça e alinham sua entrada. O casco é então descido lentamente, observando sua angulação pois se a bolina estiver um pouco desalinhada há o perigo de danificar o casco. Vale salientar que neste momento o casco, por conter as baterias, pesa aproximadamente 100kg. Quando o casco descer ao ponto de ser apoiado novamente na carroça, duas pessoas vão por baixo da carroça e empurram a bolina para cima até que o buraco no meio da bolina fique visível na parte superior do casco. Então, outra pessoa põe uma haste nesse buraco, o que mantém a bolina na posição elevada impede que ela desça. Em seguida alguém encaixa e aparafusa a tampa da bolina;

3) O próximo passo é montar a vela. Para montar a vela é preciso primeiro por o tecido da vela no mastro. Em seguida o mastro é encaixado no casco. Quando o veleiro estiver na água, deve-se colocar a retranca no mastro e amarrar a ponta da vela no final da retranca, mantendo a vela tensionada;

4) Com a estrutura principal do veleiro montada, é preciso agora conectar as baterias e fazer alguns testes básicos do sistema de controle. Antes de conectar verifique se o botão de emergência está pressionado e se o disjuntor central está desligado. Primeiramente conecte as baterias em paralelo, conectando um cabo vermelho do positivo da bat1 para o positivo da bat2 e um cabo preto do negativo da bat1 para o negativo da bat2. Então, conecte o cabo preto do (negativo do sistema) e o cabo preto e vermelho (relé) no contato negativo da bateria. Em seguida, conecte o cabo vermelho (positivo do sistema) no contato positivo da bateria. Você deve ouvir um clique o que indica que o relé foi energizado. Caso não ouça este clique verifique as conexões. Ligue o disjuntor central. Solte o botão de emergência e verifique se o led verde do compartimento das baterias está aceso.

.. warning::
	CUIDADO PARA NÃO INVERTER A CONEXÃO DA BATERIA!!!!!

5) Ligue o rádio e verifique se o controle manual está funcionando. Ligue o notebook de apoio e conecte o receptor do rádio de telemetria na porta usb. Abra o QGroundControl ou o MissionPlanner e tente se conectar. Deixe o sistema ligado um tempo para que o GPS esquente e dê lock (isso leva mais ou menos uns 3 minutos). Após isto o sistema de controle está pronto para ir pra água.

6) Agora, para levar o veleiro até a margem do reservatório, deve-se ter cuidado com o leme pois devido a altura da carroça, o mesmo fica bem próximo ao chão. É melhor levar o veleiro até a margem de ré, dependendo da inclinação do local.


Debugando o sistema
-------------------

Após ligar o veleiro vários problemas podem ocorrer que causam o mau funcionamento do sistema. O mais importante é manter o controle manual funcional a todo tempo para salvar veleiro em situação de emergência.

1) O controle manual não funciona:
	- problema no potenciometro;
	- problema na placa central;
	- problema no driver;
	- problema na pixhawk;
	- problema no rádio;
	- problema no receptor do rádio;