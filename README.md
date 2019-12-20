# Nboat Project Repository 

This repository contains the ongoing development of the Nboat robots, software and hardware, with the purpose of document our work and facilitate the process of adding new personal. Most of the code here is in C++ (Arduino), and implement navigation, control and sensors and actuators drivers. It is important to keep all code up-to-date and operational.


<p align="center">
  <img src="https://nboat-documentation.readthedocs.io/en/nboat2/_images/nboat.png" width="400" alt="Nboat2"/>
</p>


# Organização

**Arduino ------>** Códigos e bibliotecas usadas para testes no arduino mega e uno. Os códigos carregados nos arduinos são: *master_sailboat_RC_pixhawk* no arduino mega e *slave_vela_e_leme* no arduino uno.

**Códigos_nboat_manual ------>** Códigos dos arduinos usados antes de mudar o sistema para a pixhawk.

**config_pixhawk ------>** Arquivos de configuração da pixhawk. Contém o firmware, os parâmetros e uma missão com pontos na logoa do bonfim.

**docs ------>** Arquivos do site de documentação do projeto.

**matlab_simulators ------>** Simulador de veleiro no matlab.


# Instalação

O código fonte do firmware está em https://github.com/Natalnet/ardupilot.git, no branch nboat. Para compilar siga este (tutorial)[https://ardupilot.org/dev/docs/building-setup-linux.html#building-setup-linux] de *Setup On Ubuntu* até o comando *. ~/.profile*. Se tudo der certo, use os comandos **./waf configure --board Pixhawk1** e **./waf rover**. O firmware estará na pasta **ardupilot/build/Pixhawk1/bin** com o nome **ardupilot.apj**.
