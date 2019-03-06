En este archivo se especificará el funcionamiento del proyecto de la practica 2. El proyecto consiste en un juego usando el
teclado del maletín. Es un juego para 2 jugadores. El jugador 1 se representa con el lez izquierdo y el jugador 2 con el led
derecho. Una vez empieza el juego, uno de los 2 jugadores pulsa una de las teclas. Una vez pulsada se cambia el turno y se
repite el proceso con el siguiente jugador. El punto se acaba cuando uno de los jugadores pulsa una tecla que ya ha sido
pulsada previamente o no contesta dentro del tiempo indicado. Dicho jugador perderá y el otro jugador ganará un punto.
Una vez asignado el punto se reinicia para jugar otro punto.

Los pasos que se siguen son los siguientes

  1. El juego empezará una vez transcurridos 10 segundos. Este contador se reflejara en el 8 segmentos (Se utiliza el timer0
  para ello)

  2. Se iluminará el led izquierdo para que el jugador 1 pulse una tecla. Cuando la pulse se cambia el valor de dicha tecla a 1
  y cambia el turno al jugador 2 (se enciende el led derecho)

  3. Durante cada turno hay un tiempo límite (15 segundos) para que un jugador pulse una tecla. En caso de no pulsar el jugador
  contrario gana 1 punto. (Se utiliza el timer1 para el límite de tiempo)

  4. Cuando se pierde un punto se indica en el 8 segmentos el jugador que ha ganado el punto y se vuelve a empezar transcurrido
  1 segundo.

  5. En cualquier momento se puede pulsar un boton para acabar la partida, el cual mostrará en el 8 segmentos cuantos puntos ha
  hecho cada jugador. (Primero muestra el jugador que ha perdido con su correspondiente led y luego el ganador.
  La diferencia de tiempo en mostrar cada puntuación se controla con el timer2)
