
.. _nboatmini:

=========================
Nboat (Version 1.0)
=========================

In the begginings of Nboat project our idea was to first develop a sailboat model in small scale and then test and validate the hardware, mainly compose of the microcontrollers and sensors, and software, composed of the navigation system and the movement control strategies.

So, our idea was instead of build a sailboat from zero, buy a comertioal sailboat model and adapt it to suport our needs. After that, we start developing a movement contol strategy for a sailboat, so that, given a certain target position, the sailboat was able to get there on its own (autonomously). After that, we had to decide what kind of information this movement control needed to do his job, and then pick the appropriated sensors.

All this process is explain in details bellow.

Contruction
--------



Electronics
--------

We decided to use the arduino as the main processing hardware in this prototyping phase and to integrate our system at this first moment. So we realized that the minimal necessary information to allow autonomous sailing were at the time position (GPS), current heading (compass or 9DOF IMU) and wind direction (wind vane) (latter we figured that control the sail angle could be done mecanically).

With these necessary informatio, we started to develop our first and rudimentary autonomous sailing strategy. The idea was to adjust the sailboat heading (this is done by the rudder) and to get forward velocity (by adjusting the sail angle) constantly. Our first hipotesys was that if a sailboat does theses steps it will eventually reach a desired position. So, in this case the sailboat has to independt controllers: one for the sail, responsible for chosing the "right" sail angle so the sailboat gets some forward velocity; and one for the rudder, resposible for chosing the "right" rudder position so the sailboat follows a desired heading (the one that leads to the target point).

these two controllers were boiled down to the following equations:

.. math:: e^{i\pi} + 1 = 0
   :label: euler

COLOCAR EQUAÇÕES DE CONTROLE


After implementing this control strategy he started setting up the hardware. We first tested every one of the sensors fisically, so the conections are correct the sensor is ON, and by software, so the value read by the sensor is available for use in the code. After these individual tests we put them all togueter in the arduino uno used, showed the pin schematics bellow:

IMAGEM DO FRITZING

.. image:: ./source/gnc/images/nboat2.png
    :scale: 50 %
    :align: center
    :alt: Nboat platform.


Testing
--------


