
    .. _nboatmini:

============
Estrutura
============

.. talk about the fisical aspect of the robots and the challenges involved


Construção
----------

O veleiro Nboat II (será chamado de Nboat neste documento) foi construido em meados de 2015. O projeto estrutural do veleiro foi feito pelo Engenheiro naval Fred e sua construção foi comandada pelo Zeca, que tem uma oficina para construção e manutenção de embarcações nos arredores da Redinha.

.. image:: ./images/1.jpg
    :width: 49 %

.. image:: ./images/2.jpg
    :width: 49 %

O casco do veleiro possui 4 compartimentos, cada um vedado com tampas presas com parafusos para evitar a entrada de água. Os compartimentos são conectados lateralmente por tubos de pvc que servem para passar os fios de energia e dados.

A quilha do veleiro é lastrasda, ou seja, possúi um peso em sua extremidade para ajudar na estabilidade do veleiro. Ela pesa 37 Kg.

.. image:: ./images/4.jpg
    :width: 49 %

.. image:: ./images/5.jpg
    :width: 49 %

Também foi construído o leme e a vela. O leme é uma espécie de quilha rotatória que 


Atuadores
---------

Para mover


.. image:: ./images/3.jpg
    :width: 60 %
    :align: center


Organização
-----------

Os compartimentos são númerados de 1 a 4, sendo o compartimento 1 aquele que fica mais a frente da embarcação e 4 o que fica mais próximo ao leme. Cada compartimento acolhe um tipo de equipamento, sendo, atualmente, o compartimento 1 contém o botão de emergência e as entradas dos sensores de vento e da buzina. O compartimento 2 fica com o sistema de atuação da vela e as baterias, além de relés para o sistema de seguraça da vela. O compartimento 3 fica com os processadores centrais e a caixa de disjuntores de distrubuição de energia. O compartimento 4 fica com o atuador do leme.


Montagem do veleiro
-------------------



Dimensões e pesos
-----------------



First Try
+++++++++


Nboat II
--------

Electronics
-----------

We decided to use the arduino as the main processing hardware in this prototyping phase and to integrate our system at this first moment. So we realized that the minimal necessary information to allow autonomous sailing were (at that time): position (GPS), current heading (compass or 9DOF IMU) and wind direction (wind vane) (latter we figured that control the sail angle could be done mechanically).

With these necessary information, we started to develop our first and rudimentary autonomous sailing strategy. The idea was to constantly adjust the sailboat's heading (this is done by the rudder) and to get forward velocity (by adjusting the sail angle). Our first hypothesis was that if a sailboat does theses steps it will eventually reach a desired position. So, in this case the sailboat has two independent controllers: one for the sail, responsible for choosing the "right" sail angle so the sailboat gets some forward velocity; and one for the rudder, responsible for choosing the "right" rudder position so the sailboat follows a desired heading (the one that leads to the target point).

these two controllers were boiled down to the following equations:


.. code-block:: python 
  
    sailAngle = windDirection/2

    rudderAngle = headingError

where,

.. code-block:: python

    headingError = desiredHeading - currentHeading 

After implementing this control strategy we started setting up the hardware. We first tested every one of the sensors physically, so the connections were correct and the sensors were ON, and by software, so the value read by the sensor is available for use in the code. After these individual tests we put them all together in the arduino mega, showed by the pin schematics bellow:

.. image:: ./images/hardware_sailboat1.png
    :scale: 75 %
    :align: center


Testing
-------

After all, we took the boat to a nearby lagoon, called *Lagoa de Alcaçuz*, to perform some experimental tests. We hoped to see if the whole system was working by picking a desired point in the lagoon and observing if the sailboat would be able to reach it on its own. The results of this experiment are shown in the video below.

.. raw:: html

    <div style="position: relative; padding-bottom: 56.25%; height: 0; overflow: hidden; max-width: 100%; height: auto;">
            <iframe src="https://www.youtube.com/embed/vy302e11Tpc?start=390&end=508" frameborder="0" allowfullscreen style="position: absolute; top: 0; left: 0; width: 95%; height: 95%;"></iframe>
                </div>


As you can see the sailboat reached the desired target, even under not ideal conditions, with high wind velocity and some timid waves.

Right after this test the concealment that we put on the sailboat was finally broken by the water and the sailboat stopped working properly.


Lessons learned
---------------

Some of it might seem obvious but...

* The sailing control strategy that we developed worked but it wasn't particularly robust enough to allow sailing to points directly against the wind (a zig-zagging maneuver called tacking/beating)

* If you're developing any navigation techniques for a robot TEST IT FIRST IN SIMULATION. It will save you a lot of time

* If you're going to perform ANY outdoor experiment (especially in the water) CAREFULLY PREPARE you fucking robot and PLAN the fucking mission back to back. In this way you'll take the most out of the experiment