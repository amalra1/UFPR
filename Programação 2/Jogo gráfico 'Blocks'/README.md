# Jewels-in-C
Graphic game 'Jewels' implemented using C language, with &lt;allegro.h> library.
Developed by: Pedro Amaral Chapelin
Release Date: XX/XX/XXXX

## To-Do

- [ ] Game menu;
- [ ] Jewels designs;
- [ ] First level;
  
  
## Game rules

- Match 3 or more identical jewels in a single move to make a match and watch it disappear.
- Match 4 or more gems in a row to unlock special jewels, clear the board, and increase your score faster.
- To earn the most points, fill up the color meters to complete each level and add score multipliers to your next board.
- Drag, click, or tap a jewel to move it vertically or horizontally in the direction to complete a match.
- Game ends when you run out of moves.

## Notes

- Game ends when the player literally cannot do any more movements.
- Save the highest scores in disk and show in a scoreboard;
- On the first level there are 4 types of jewels: **yellow squares**, **purple thin crystals**, **green diamons**, **red squares** and **blue circles**. After the third level, **orange hexagons** start showing up.
- A level ends when you complete a score limit, defined per level. Each time you advance a level, the jewels mix themselves in a random way, and a multiplier is increased (*1st level the multiplier is 1x, 2nd is 2x, and so on..*)
- Random challenges will eventually show up on the screen, telling the player that if he connects a certain quantity of a certain type of figure, he will earn extra points to complete the bar.
- Connecting 4 jewels will turn the 4 into 1 with a background shinning, connecting it to another 2 will generate extra points.
- Connecting more than 4 jewels will create a **crystal jewel**, moving it anywhere will activate it, destroying all jewels from the selected jewel colour.

### Score table

-> Connecting 3 jewels: **10 points**  
-> Connecting 4 jewels: **30 points**  
-> Connecting 5 jewels: **100 points**
> if after connecting, other jewels connect by themselves, they value **10 more points** than the previous connection
