//
// Created by Adonis on 16/04/2014.
//

#ifndef MERCURY_PONG_MAINLOOP_H
#define MERCURY_PONG_MAINLOOP_H

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 720

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <sstream>
#include <cstring>
#include <iostream>
#include <stdlib.h>

#include "Ball_Racket.cpp"
#include "Utilities.cpp"

srand(time(NULL));

/*
0 = Menu
1 = 1 player
2 = 2 player
3 = Options
4 = About
*/

short int screen(0);
unsigned short int transSpeed(30), count(0);
bool hoverButton(0), done(0), pause(1), lol(0), page(0), fullscreen(0), showFPS(1), language(1); // 0 -> en ; 1 -> fr
float scoreL(0), scoreR(0), musicVolume(50), soundVolume(100);

Mouse mouse;
Event event;
View view(FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

// Window
RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Mercury Pong", Style::Close);
window.setFramerateLimit(60);
window.setView(view);

// Window icon
Image icon;
icon.loadFromFile(getFile("img/icon/"));
window.setIcon(32, 32, icon.getPixelsPtr());

// Sounds
SoundBuffer hoverLoad, startLoad, smallBallDestroyLoad, bigBallDestroyLoad, toastySoundLoad, fightLoad, win1Load, win2Load, drawLoad, perfectLoad, gameOverLoad;

hoverLoad.loadFromFile(getFile("audio/sound/hover/"));
startLoad.loadFromFile(getFile("audio/sound/start/"));
smallBallDestroyLoad.loadFromFile(getFile("audio/sound/ballDestroy/small/"));
bigBallDestroyLoad.loadFromFile(getFile("audio/sound/ballDestroy/big/"));
toastySoundLoad.loadFromFile(getFile("audio/sound/toasty/"));
fightLoad.loadFromFile(getFile("audio/sound/fight/"));
win1Load.loadFromFile(getFile("audio/sound/win/player1/"));
win2Load.loadFromFile(getFile("audio/sound/win/player2/"));
drawLoad.loadFromFile(getFile("audio/sound/draw/"));
perfectLoad.loadFromFile(getFile("audio/sound/perfect/"));
gameOverLoad.loadFromFile(getFile("audio/sound/gameOver/"));

Sound hover(hoverLoad), start(startLoad), smallBallDestroy(smallBallDestroyLoad), bigBallDestroy(bigBallDestroyLoad), toastySound(toastySoundLoad), fight(fightLoad), win1(win1Load), win2(win2Load), draw(drawLoad), perfect(perfectLoad), gameOver(gameOverLoad);

hover.setVolume(soundVolume), start.setVolume(soundVolume), smallBallDestroy.setVolume(soundVolume), bigBallDestroy.setVolume(soundVolume), fight.setVolume(soundVolume), win1.setVolume(soundVolume), win2.setVolume(soundVolume), draw.setVolume(soundVolume), perfect.setVolume(soundVolume), gameOver.setVolume(soundVolume);

// Fonts
Font titleFont;
titleFont.loadFromFile(getFile("font/title/"));

Font textFont;
textFont.loadFromFile(getFile("font/text/"));

// Music
Music music;
music.openFromFile(getFile("audio/music/menu/"));
music.setVolume(musicVolume);
music.setLoop(1);
music.play();

// Textures/Sprites
Texture menuBgLoad, menuTitleLoad, onePlayerLoad, onePlayerFrLoad, twoPlayersLoad, twoPlayersFrLoad, optionsLoad, aboutLoad, aboutFrLoad, quitLoad, quitFrLoad, menuLoad, bgLoad, ballLoad, racketLoad, shadowLoad, toastyLoad, gaugeLoad, cursorLoad, profLoad, kidLoad, nextLoad, nextFrLoad, previousLoad, previousFrLoad, on, off, en, fr;

menuBgLoad.loadFromFile(getFile("img/menuBg/")), menuTitleLoad.loadFromFile(getFile("img/title/")), onePlayerLoad.loadFromFile(getFile("img/button/1player/en/")), onePlayerFrLoad.loadFromFile(getFile("img/button/1player/fr/")), twoPlayersLoad.loadFromFile(getFile("img/button/2players/en/")), twoPlayersFrLoad.loadFromFile(getFile("img/button/2players/fr/")), optionsLoad.loadFromFile(getFile("img/button/options/")), aboutLoad.loadFromFile(getFile("img/button/about/en/")), aboutFrLoad.loadFromFile(getFile("img/button/about/fr/")), quitLoad.loadFromFile(getFile("img/button/quit/en/")), quitFrLoad.loadFromFile(getFile("img/button/quit/fr/")), menuLoad.loadFromFile(getFile("img/button/menu/")), bgLoad.loadFromFile(getFile("img/bg/")), ballLoad.loadFromFile(getFile("img/ball/")), racketLoad.loadFromFile(getFile("img/racket/")), shadowLoad.loadFromFile(getFile("img/shadow/")), toastyLoad.loadFromFile(getFile("img/toasty/")), gaugeLoad.loadFromFile(getFile("img/gauge/")), cursorLoad.loadFromFile(getFile("img/cursor/")), profLoad.loadFromFile(getFile("img/prof/")), kidLoad.loadFromFile(getFile("img/kid/")), nextLoad.loadFromFile(getFile("img/button/next/en/")), nextFrLoad.loadFromFile(getFile("img/button/next/fr/")), previousLoad.loadFromFile(getFile("img/button/previous/en/")), previousFrLoad.loadFromFile(getFile("img/button/previous/fr/")), on.loadFromFile(getFile("img/button/on/")), off.loadFromFile(getFile("img/button/off/")), en.loadFromFile(getFile("img/button/lang/en/")), fr.loadFromFile(getFile("img/button/lang/fr/"));

Sprite menuBg(menuBgLoad), menuTitle(menuTitleLoad), onePlayer, twoPlayers, options(optionsLoad), about, quit, menu1(menuLoad), menu2(menuLoad), bg(bgLoad), shadow(shadowLoad), toasty(toastyLoad), gauge1(gaugeLoad), gauge2(gaugeLoad), cursor1(cursorLoad), cursor2(cursorLoad), prof(profLoad), kid(kidLoad), next, previous, buttonFPS(on), lang(en);

menuBg.setOrigin(menuBg.getLocalBounds().width/2, menuBg.getLocalBounds().height/2);
menuBg.setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
menuTitle.setPosition(SCREEN_WIDTH/2-menuTitle.getLocalBounds().width/2, SCREEN_HEIGHT/6-menuTitle.getLocalBounds().height/2);
cursor1.setOrigin(cursor1.getLocalBounds().width/2, 0);
toasty.setPosition(SCREEN_WIDTH, SCREEN_HEIGHT-toasty.getLocalBounds().height);
prof.setOrigin(prof.getLocalBounds().width, 0);

// Rectangle shapes
RectangleShape zone1, zone2, zone3(Vector2f(210, 25)), racketL(Vector2f(30, 150)), racketR(Vector2f(30, 150));

zone1.setFillColor(Color(90, 90, 90));
zone1.setOutlineColor(Color(0, 0, 0, 128));
zone1.setOutlineThickness(15);

zone2.setFillColor(Color(90, 90, 90));
zone2.setOutlineColor(Color(0, 0, 0, 128));
zone2.setOutlineThickness(15);

zone3.setFillColor(Color(0, 0, 0, 128));
zone3.setOutlineThickness(1);
zone3.setOutlineColor(Color::Black);

racketL.setTexture(&racketLoad);
racketL.setOrigin(0, racketL.getSize().y/2);

racketR.setTexture(&racketLoad);
racketR.setOrigin(0, racketR.getSize().y/2);

// Dynamic arrays
vector<CircleShape> ball(0);
vector<Vector2f> move(0);
vector<float> amount(0);

// Text
Text text1, text2, text3, text4, fps("FPS: ?");

text1.setFont(titleFont);

fps.setCharacterSize(17);
fps.setPosition(Vector2f(SCREEN_WIDTH-1.5*fps.getLocalBounds().width, fps.getLocalBounds().height));

// Timer
Clock clock;
Time time1, time2;




mainLoop();


#endif //MERCURY_PONG_MAINLOOP_H
