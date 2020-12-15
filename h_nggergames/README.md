# Game Show Buttons
For a self-made game show, an Arduino was connected to two switches and two corresponding light bulbs. The two opposing teams got each one of the buttons. 
When a question is asked, the team which pressed its button faster will get a chance to answer. As soon as a team presses its button, its corresponding light bulb
will light up.

# Arduino
The sketch controls the game show flow and ensures the following:
the faster teams light bulb will light first, at the same time the other teams bulb won't turn on.
to reset, both teams need to switch their switches to off (disconnected) and the gameshow host resets the game via a seperate reset-button 
