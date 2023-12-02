%% Arkanoid %%
%%%%%%%%%%%%%%

+ Game class
+ Ball class
+ Paddle class
+ Block class

======================
done from List bellow:
+ boarder collision (with frame)
+ Points 
+ Player lifes
+ GameOver
+ Lvl win (will set new blocks)
+ font for txt print


* To implement Next:
- Randomize lvl format
- HiScore
- file read/write
- Wizualize bracket left/right ??
- lvl-up's with working time
- speed and size parametrize
- gravity
- velocity & drag
- Animations?

* To update:
- intersection - ball changing dirrection (angle)
- start new block set whit al balls around paddle
- textures 
- Balls move together with paddle

* Other:
- game window base on resolution [started]
- Settings & Game menu
- timer for additional aspect of highScore?


-intersectionDir - to finish
	for some reason intersectionDir is executed even if theres no balls near paddle
	(intersectionDir is called from 'ball hitting Paddle' section of intersection function)
- when 0 balls game does not finish, not sure why :?
