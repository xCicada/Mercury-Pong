//
// Created by Adonis on 16/04/2014.
//

#include "MainLoop.h"

using namespace std;

int mainLoop(){
    do
    {
        switch(screen)
        {
            // Menu
            case 0:
            {
                // Visible cursor
                window.setMouseCursorVisible(true);

                // Menu zone
                zone1.setSize(Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT/3*2));
                zone1.setPosition(SCREEN_WIDTH/2-zone1.getSize().x/2, SCREEN_HEIGHT/3);

                // Menu buttons
                if(language)
                {
                    onePlayer.setTexture(onePlayerFrLoad, true);
                    twoPlayers.setTexture(twoPlayersFrLoad, true);
                    about.setTexture(aboutFrLoad, true);
                    quit.setTexture(quitFrLoad, true);
                }

                onePlayer.setPosition(SCREEN_WIDTH/2-onePlayer.getLocalBounds().width/2, zone1.getPosition().y+65);
                twoPlayers.setPosition(SCREEN_WIDTH/2-twoPlayers.getLocalBounds().width/2, zone1.getPosition().y+140);
                options.setPosition(SCREEN_WIDTH/2-options.getLocalBounds().width/2, zone1.getPosition().y+215);
                about.setPosition(SCREEN_WIDTH/2-about.getLocalBounds().width/2, zone1.getPosition().y+290);
                quit.setPosition(SCREEN_WIDTH/2-quit.getLocalBounds().width/2, zone1.getPosition().y+365);

                // Display loop
                while(screen == 0)
                {
                    getFPS(time2, clock, fps, count);

                    while(window.pollEvent(event))
                    {
                        // Close the game
                        if(event.type == Event::Closed)
                            screen = -1;

                        if((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))
                            screen = -1;

                        // Click detection
                        if((event.type == Event::MouseButtonReleased))
                        {
                            // 1 player
                            if(isHover(onePlayer, window))
                                screen = 1;

                                // 2 players
                            else if(isHover(twoPlayers, window))
                                screen = 2;

                                // About
                            else if(isHover(options, window))
                                screen = 3;

                                // About
                            else if(isHover(about, window))
                                screen = 4;

                                // Quit
                            else if(isHover(quit, window))
                                screen = -1;
                        }

                    }

                    // Button transformation when the cursor is hover
                    hoverTrans(onePlayer, window), hoverTrans(twoPlayers, window), hoverTrans(options, window), hoverTrans(about, window), hoverTrans(quit, window);

                    // Sound of the menu
                    if(isHover(onePlayer, window) || isHover(twoPlayers, window) || isHover(options, window) || isHover(about, window) || isHover(quit, window))
                    {
                        if(!hoverButton)
                            hover.play();

                        hoverButton = true;
                    }
                    else
                        hoverButton = false;

                    // Rotation of the background
                    menuBg.rotate(0.25);

                    // Display
                    window.clear();
                    window.draw(menuBg);
                    window.draw(menuTitle);
                    window.draw(zone1);
                    window.draw(onePlayer);
                    window.draw(twoPlayers);
                    window.draw(options);
                    window.draw(about);
                    window.draw(quit);
                    if(showFPS)
                        window.draw(fps);
                    window.display();
                }
            }
                break;

                // 1 and 2 Players
            case 1:
            case 2:
            {
                // Invisible cursor
                window.setMouseCursorVisible(0);

                // Change the music
                music.openFromFile(getFile("audio/music/game/"));
                music.play();

                // Change the background
                bgLoad.loadFromFile(getFile("img/bg/"));

                // Values of the first ball
                ball.push_back(CircleShape(37.5, 50)), amount.push_back(50), move.push_back(Vector2f(0, 0));
                ball[0].setTexture(&ballLoad);
                ball[0].setOrigin(ball[0].getRadius(), ball[0].getRadius());
                ball[0].setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

                startDirection(move[0]);

                // Rackets
                racketL.setPosition(racketL.getSize().x, SCREEN_HEIGHT/2);
                racketR.setPosition(SCREEN_WIDTH-racketR.getSize().x*2, SCREEN_HEIGHT/2);

                // Pause Zone
                zone1.setSize(Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT*3/4));
                zone1.setPosition(SCREEN_WIDTH/2-zone1.getSize().x/2, SCREEN_HEIGHT/2-zone1.getSize().y/2);

                // End sound
                done = 0;

                if(screen == 1)
                {
                    // Start sound
                    start.play();

                    // Time text
                    text1.setString(nbStr(floor(time1.asSeconds())));
                    text1.setCharacterSize(125);
                    text1.setPosition(SCREEN_WIDTH/2-text1.getLocalBounds().width/2, 0);
                    text1.setColor(Color(255, 255, 255, 85));

                    text2.setString("Pause");
                    text2.setFont(titleFont);
                    text2.setCharacterSize(60);
                    text2.setPosition(SCREEN_WIDTH/2-text2.getLocalBounds().width/2, zone1.getPosition().y);

                    if(!language)
                        text3.setString("P = Pause ; R = Restart\nF11 = Fullscreen\nM = Menu ; Esc = Quit\n\nUse the mouse to control both\nrackets.\nYou have to keep the mercury as\nlong as possible.");
                    else
                        text3.setString("P = Pause ; R = Rejouer\nF11 = Plein écran\nM = Menu ; Echap = Quitter\n\nUtilisez la souris pour contrôller\nles 2 raquettes.\nVous devez garder le mercure\naussi longtemps que possible.");

                    text3.setFont(textFont);
                    text3.setCharacterSize(35);
                    text3.setPosition(zone1.getPosition().x+zone1.getOutlineThickness(), text2.getPosition().y+text2.getLocalBounds().height*2);

                    // Reset the timer
                    time1 = Time::Zero;
                }
                else
                {
                    // Fight sound
                    fight.play();

                    // Scores
                    scoreL = 0, scoreR = 0;

                    text1.setString(nbStr(scoreL));
                    text1.setCharacterSize(125);
                    text1.setColor(Color(255, 255, 255, 85));
                    text1.setPosition(SCREEN_WIDTH/4-text1.getLocalBounds().width/2, 0);

                    text4.setString(nbStr(scoreR));
                    text4.setFont(titleFont);
                    text4.setCharacterSize(125);
                    text4.setColor(Color(255, 255, 255, 85));
                    text4.setPosition(SCREEN_WIDTH/4*3-text4.getLocalBounds().width/2, 0);

                    // Pause
                    text2.setString("Pause");
                    text2.setFont(titleFont);
                    text2.setCharacterSize(60);
                    text2.setPosition(SCREEN_WIDTH/2-text2.getLocalBounds().width/2, zone1.getPosition().y);

                    if(!language)
                        text3.setString("P = Pause ; R = Restart\nF11 = Fullscreen\nM = Menu ; Esc = Quit\n\nThe first player une E and D, the\nsecond one use Up and Down to\ncontrol the racket.\nDestroy your enemy!");
                    else
                        text3.setString("P = Pause ; R = Rejouer\nF11 = Plein écran\nM = Menu ; Echap = Quitter\n\nLe premier joueur utiliser E et D,\nle second utilise Haut et Bas pour\ncontrôller la raquette.\nDéglingue ton ennemi !");

                    text3.setFont(textFont);
                    text3.setCharacterSize(35);
                    text3.setPosition(zone1.getPosition().x+zone1.getOutlineThickness(), text2.getPosition().y+text2.getLocalBounds().height*2);
                }

                // Display loop
                while(screen == 1 || screen == 2)
                {
                    getFPS(time2, clock, fps, count);

                    while(window.pollEvent(event))
                    {
                        // Close the game
                        if(event.type == Event::Closed)
                            screen = -1;

                        // When a key is pressed
                        if(event.type == Event::KeyPressed)
                        {
                            // Close the game
                            if(event.key.code == Keyboard::Escape)
                                screen = -1;

                            // Fullscreen
                            if(event.key.code == Keyboard::F11)
                            {
                                if(!fullscreen)
                                {
                                    view.setSize(window.getSize().x, window.getSize().y);
                                    window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Mercury Pong", Style::Fullscreen);
                                    fullscreen = 1;
                                }
                                else
                                {
                                    view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
                                    window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Mercury Pong", Style::Close);
                                    fullscreen = 0;
                                }

                                window.setIcon(32, 32, icon.getPixelsPtr());
                                window.setMouseCursorVisible(0);
                                window.setView(view);
                            }

                            // Activate/deactivate the pause
                            if(event.key.code == Keyboard::P)
                            {
                                if(pause)
                                    pause = 0;
                                else
                                    pause = 1;
                            }

                            // Restart
                            if(event.key.code == Keyboard::R)
                            {
                                ball.clear(), move.clear(), amount.clear();
                                ball.push_back(CircleShape(37.5, 50)), amount.push_back(50), move.push_back(Vector2f(0, 0));
                                ball[0].setTexture(&ballLoad);
                                ball[0].setOrigin(ball[0].getRadius(), ball[0].getRadius());
                                ball[0].setPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

                                startDirection(move[0]);

                                bgLoad.loadFromFile(getFile("img/bg/"));

                                racketL.setPosition(racketL.getSize().x, SCREEN_HEIGHT/2);
                                racketR.setPosition(SCREEN_WIDTH-racketR.getSize().x*2, SCREEN_HEIGHT/2);

                                done = 0;

                                if(screen == 1)
                                {
                                    time1 = Time::Zero;
                                    start.play();
                                }
                                else
                                {
                                    scoreL = 0, scoreR = 0;
                                    text1.setString(nbStr(scoreL)), text4.setString(nbStr(scoreR));
                                    text1.setColor(Color(255, 255, 255, 85)), text4.setColor(Color(255, 255, 255, 85));
                                    text1.setPosition(SCREEN_WIDTH/4-text1.getLocalBounds().width/2, 0), text4.setPosition(SCREEN_WIDTH/4*3-text4.getLocalBounds().width/2, 0);
                                    fight.play();
                                }

                            }

                            // Return to menu
                            if(event.key.code == Keyboard::M)
                            {
                                if(fullscreen)
                                {
                                    view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
                                    window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Mercury Pong", Style::Close);
                                    window.setIcon(32, 32, icon.getPixelsPtr());
                                    window.setMouseCursorVisible(0);
                                    window.setView(view);
                                    fullscreen = 0;
                                }

                                text1.setColor(Color(255, 255, 255)), text4.setColor(Color(255, 255, 255));
                                ball.clear(), move.clear(), amount.clear();
                                screen = 0, pause = 1;
                                music.openFromFile(getFile("audio/music/menu/"));
                                music.play();
                            }
                        }

                        // Rackets control
                        if(screen == 1 && !pause && event.type == Event::MouseMoved)
                        {
                            racketL.setPosition(racketL.getPosition().x, mouse.getPosition(window).y);
                            racketR.setPosition(racketR.getPosition().x, mouse.getPosition(window).y);
                        }
                    }

                    if(!pause)
                    {
                        if(screen == 2)
                        {
                            // Keyboard input
                            if (Keyboard::isKeyPressed(Keyboard::E))
                                racketL.move(0, -18);

                            if (Keyboard::isKeyPressed(Keyboard::D))
                                racketL.move(0, 18);

                            if (Keyboard::isKeyPressed(Keyboard::Up))
                                racketR.move(0, -18);

                            if (Keyboard::isKeyPressed(Keyboard::Down))
                                racketR.move(0, 18);
                        }

                        // Racket collides with a wall
                        wallCollision(racketL);
                        wallCollision(racketR);

                        // Ball collision
                        for(unsigned short int i(0) ; i<ball.size() ; i++)
                        {
                            // Ball move
                            ball[i].move(move[i]);

                            // Ball collides with a wall
                            if(ball[i].getPosition().y <= ball[i].getRadius())
                            {
                                ball[i].setPosition(ball[i].getPosition().x, ball[i].getRadius());
                                move[i].y *= -1;

                            }
                            else if(ball[i].getPosition().y >= SCREEN_HEIGHT-ball[i].getRadius())
                            {
                                ball[i].setPosition(ball[i].getPosition().x, SCREEN_HEIGHT-ball[i].getRadius());
                                move[i].y *= -1;
                            }

                            // Ball collides with a racket
                            if(collisionBR(ball[i], racketL) || collisionBR(ball[i], racketR))
                            {
                                if(amount[i] > 3.125)
                                {
                                    ball[i].setRadius(ball[i].getRadius()/sqrt(2));
                                    ball[i].setOrigin(ball[i].getRadius(), ball[i].getRadius());
                                    amount[i] /= 2;
                                    move[i].x *= -1.15;

                                    if(collisionBR(ball[i], racketL))
                                        trajectory(move[i].y, ball[i], racketL);
                                    else if(collisionBR(ball[i], racketR))
                                        trajectory(move[i].y, ball[i], racketL);

                                    speedLimit(move[i], ball.size());

                                    ball.push_back(CircleShape(ball[i].getRadius(), ball[i].getPointCount()));
                                    move.push_back(Vector2f(move[i].x/1.15, -move[i].y/1.15));
                                    amount.push_back(amount[i]);
                                    ball[ball.size()-1].setTexture(&ballLoad);
                                    ball[ball.size()-1].setOrigin(ball[i].getRadius(), ball[i].getRadius());

                                    if(move[i].y < 0)
                                    {
                                        ball[ball.size()-1].setPosition(ball[i].getPosition().x, ball[i].getPosition().y+ball[i].getRadius()*2);
                                        while(collisionBB(ball[i], ball[ball.size()-1]))
                                        {
                                            ball[ball.size()-1].setPosition(ball[ball.size()-1].getPosition().x, ball[ball.size()-1].getPosition().y+1);
                                        }
                                    }
                                    else
                                    {
                                        ball[ball.size()-1].setPosition(ball[i].getPosition().x, ball[i].getPosition().y-ball[i].getRadius()*2);
                                        while(collisionBB(ball[i], ball[ball.size()-1]))
                                        {
                                            ball[ball.size()-1].setPosition(ball[ball.size()-1].getPosition().x, ball[ball.size()-1].getPosition().y-1);
                                        }
                                    }

                                    if(collisionBR(ball[i], racketL))
                                    {
                                        ball[i].setPosition(racketL.getPosition().x+racketL.getSize().x+ball[i].getRadius(), ball[i].getPosition().y);
                                        ball[ball.size()-1].setPosition(racketL.getPosition().x+racketL.getSize().x+ball[ball.size()-1].getRadius(), ball[ball.size()-1].getPosition().y);
                                    }
                                    else if(collisionBR(ball[i], racketR))
                                    {
                                        ball[i].setPosition(racketR.getPosition().x-ball[i].getRadius(), ball[i].getPosition().y);
                                        ball[ball.size()-1].setPosition(racketR.getPosition().x-ball[ball.size()-1].getRadius(), ball[ball.size()-1].getPosition().y);
                                    }
                                }
                                else
                                {
                                    move[i].x *= -1.15;

                                    if(collisionBR(ball[i], racketL))
                                        trajectory(move[i].y, ball[i], racketL);
                                    else if(collisionBR(ball[i], racketR))
                                        trajectory(move[i].y, ball[i], racketL);

                                    speedLimit(move[i], ball.size());

                                    if(collisionBR(ball[i], racketL))
                                        ball[i].setPosition(racketL.getPosition().x+racketL.getSize().x+ball[i].getRadius(), ball[i].getPosition().y);
                                    else if(collisionBR(ball[i], racketR))
                                        ball[i].setPosition(racketR.getPosition().x-ball[i].getRadius(), ball[i].getPosition().y);
                                }
                            }

                                // Ball is in the gutter
                            else if(ball[i].getPosition().x < -ball[i].getRadius() || ball[i].getPosition().x > SCREEN_WIDTH+ball[i].getRadius())
                            {
                                if(screen == 2)
                                {
                                    if(ball[i].getPosition().x < -ball[i].getRadius())
                                    {
                                        scoreL += amount[i];
                                        text1.setString(nbStr(scoreL));
                                        text1.setPosition(SCREEN_WIDTH/4-text1.getLocalBounds().width/2, 0);
                                    }
                                    else
                                    {
                                        scoreR += amount[i];
                                        text4.setString(nbStr(scoreR));
                                        text4.setPosition(SCREEN_WIDTH/4*3-text4.getLocalBounds().width/2, 0);
                                    }
                                }

                                if(amount[i] >= 12.5)
                                {
                                    if(rand()%43)
                                        bigBallDestroy.play();
                                    else
                                    {
                                        toastySound.play();
                                        lol = 1;
                                    }
                                }
                                else
                                    smallBallDestroy.play();

                                ball.erase(ball.begin()+i);
                                move.erase(move.begin()+i);
                                amount.erase(amount.begin()+i);
                            }

                            // Ball collides with another ball
                            if(ball.size() > 1)
                            {
                                for(unsigned short int j(0) ; j<ball.size() ; j++)
                                {
                                    if(j != i)
                                    {
                                        if(collisionBB(ball[i], ball[j]))
                                        {
                                            ball[j].setRadius(sqrt(pow(ball[j].getRadius(), 2)+pow(ball[i].getRadius(), 2)));
                                            ball[j].setOrigin(ball[j].getRadius(), ball[j].getRadius());
                                            move[j].x += move[i].x;
                                            move[j].y += move[i].y;
                                            amount[j] += amount[i];

                                            speedLimit(move[j], ball.size());

                                            ball.erase(ball.begin()+i);
                                            move.erase(move.begin()+i);
                                            amount.erase(amount.begin()+i);
                                        }
                                    }
                                }
                            }
                        }

                        if(screen == 1 && ball.size() > 0)
                        {
                            time1 += time2;
                            text1.setString(nbStr(floor(time1.asSeconds())));
                            text1.setPosition(SCREEN_WIDTH/2-text1.getLocalBounds().width/2, 0);
                        }

                        if(lol)
                        {
                            if(toasty.getPosition().x > SCREEN_WIDTH-toasty.getLocalBounds().width)
                                toasty.move(-7, 0);
                            else
                                lol = 0;
                        }
                        else
                        {
                            if(toasty.getPosition().x < SCREEN_WIDTH)
                                toasty.move(7, 0);
                        }

                        if(screen == 2)
                        {
                            // Text colour
                            if(scoreL > scoreR)
                            {
                                text1.setColor(Color(255, 0, 0, 85));
                                text4.setColor(Color(0, 255, 0, 85));
                            }
                            else if(scoreR > scoreL)
                            {
                                text1.setColor(Color(0, 255, 0, 85));
                                text4.setColor(Color(255, 0, 0, 85));
                            }
                            else
                            {
                                text1.setColor(Color(255, 255, 255, 85));
                                text4.setColor(Color(255, 255, 255, 85));
                            }
                        }

                        if(!ball.size() && !done)
                        {
                            if(screen == 1)
                                gameOver.play();
                            else
                            {
                                if(scoreL != 50 && scoreR != 50)
                                {
                                    if(scoreL < scoreR)
                                        win1.play();
                                    else if(scoreR < scoreL)
                                        win2.play();
                                    else
                                        draw.play();
                                }
                                else
                                    perfect.play();
                            }

                            done = 1;
                        }
                    }

                    // Display
                    window.clear();
                    window.draw(bg);
                    window.draw(shadow);
                    window.draw(text1);
                    if(screen == 2)
                        window.draw(text4);
                    for(unsigned short int i(0) ; i<ball.size() ; i++)
                    {
                        window.draw(ball[i]);
                    }
                    window.draw(racketL);
                    window.draw(racketR);
                    if(pause)
                    {
                        window.draw(zone1);
                        window.draw(text2);
                        window.draw(text3);
                    }
                    if(toasty.getPosition().x < SCREEN_WIDTH)
                        window.draw(toasty);
                    if(showFPS)
                        window.draw(fps);
                    window.display();
                }

            }
                break;

                // Options
            case 3:
            {
                // Options Zone
                zone1.setSize(Vector2f(SCREEN_WIDTH/2, SCREEN_HEIGHT-2*zone1.getOutlineThickness()));
                zone1.setPosition(SCREEN_WIDTH/2-zone1.getSize().x/2, 2*zone1.getOutlineThickness());

                text1.setString("Options");
                text1.setCharacterSize(60);
                text1.setPosition(SCREEN_WIDTH/2-text1.getLocalBounds().width/2, zone1.getPosition().y);

                // Left text
                if(!language)
                    text2.setString("Music volume:\n\nSounds volume:\n\nLanguage:\n\nShow FPS:");
                else
                    text2.setString("Volume de la musique :\n\nVolume des sons :\n\nLangage :\n\nAfficher les FPS :");

                text2.setFont(textFont);
                text2.setCharacterSize(35);
                text2.setPosition(zone1.getPosition().x+zone1.getOutlineThickness(), zone1.getPosition().y+2*text1.getLocalBounds().height);

                // Volume gauge
                gauge1.setPosition(text2.getPosition().x+text2.getLocalBounds().width+zone1.getOutlineThickness(), text2.getPosition().y+gauge1.getLocalBounds().height/2);
                cursor1.setPosition(Vector2f(gauge1.getPosition().x+2*musicVolume, gauge1.getPosition().y));

                gauge2.setPosition(gauge1.getPosition().x, gauge1.getPosition().y+2*text2.getCharacterSize()+gauge2.getLocalBounds().height);
                cursor2.setPosition(Vector2f(gauge2.getPosition().x+2*soundVolume, gauge2.getPosition().y));

                // Language button
                if(!language)
                    lang.setTexture(en, true);
                else
                    lang.setTexture(fr, true);

                lang.setPosition(gauge1.getPosition().x, gauge1.getPosition().y+5*text2.getCharacterSize());

                // FPS button
                buttonFPS.setPosition(gauge1.getPosition().x, gauge1.getPosition().y+7*text2.getCharacterSize()+buttonFPS.getLocalBounds().height);

                // Menu button
                menu1.setPosition(zone1.getPosition().x+zone1.getOutlineThickness(), SCREEN_HEIGHT-menu1.getLocalBounds().height-zone1.getOutlineThickness());
                while(screen == 3)
                {
                    getFPS(time2, clock, fps, count);

                    while(window.pollEvent(event))
                    {
                        // Close the game
                        if(event.type == Event::Closed)
                            screen = -1;

                        if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                            screen = -1;

                        // Musc Volume
                        if(event.type == Event::MouseButtonPressed)
                        {
                            if(isHover(gauge1, window))
                            {
                                cursor1.setPosition(Vector2f(mouse.getPosition(window).x, cursor1.getPosition().y));
                                musicVolume = (cursor1.getPosition().x - gauge1.getPosition().x)/2;
                                music.setVolume(musicVolume);
                            }
                            else if(isHover(gauge2, window))
                            {
                                cursor2.setPosition(Vector2f(mouse.getPosition(window).x, cursor2.getPosition().y));
                                soundVolume = (cursor2.getPosition().x - gauge2.getPosition().x)/2;
                                hover.setVolume(soundVolume), start.setVolume(soundVolume), smallBallDestroy.setVolume(soundVolume), bigBallDestroy.setVolume(soundVolume), fight.setVolume(soundVolume), win1.setVolume(soundVolume), win2.setVolume(soundVolume), draw.setVolume(soundVolume), perfect.setVolume(soundVolume), gameOver.setVolume(soundVolume);
                            }
                            else if(isHover(buttonFPS, window))
                            {
                                if(showFPS)
                                {
                                    showFPS = 0;
                                    buttonFPS.setTexture(off);
                                }
                                else
                                {
                                    showFPS = 1;
                                    buttonFPS.setTexture(on);
                                }
                            }
                            else if(isHover(lang, window))
                            {
                                if(language)
                                {
                                    language = 0;
                                    lang.setTexture(en, true);

                                    text2.setString("Music volume:\n\nSounds volume:\n\nLanguage:\n\nShow FPS:");
                                }
                                else
                                {
                                    language = 1;
                                    lang.setTexture(fr, true);

                                    text2.setString("Volume de la musique :\n\nVolume des sons :\n\nLangage :\n\nAfficher les FPS :");
                                }

                                gauge1.setPosition(text2.getPosition().x+text2.getLocalBounds().width+zone1.getOutlineThickness(), text2.getPosition().y+gauge1.getLocalBounds().height/2);
                                cursor1.setPosition(Vector2f(gauge1.getPosition().x+2*musicVolume, gauge1.getPosition().y));
                                gauge2.setPosition(gauge1.getPosition().x, gauge1.getPosition().y+2*text2.getCharacterSize()+gauge2.getLocalBounds().height);
                                cursor2.setPosition(Vector2f(gauge2.getPosition().x+2*soundVolume, gauge2.getPosition().y));
                                lang.setPosition(gauge1.getPosition().x, gauge1.getPosition().y+5*text2.getCharacterSize());
                                buttonFPS.setPosition(gauge1.getPosition().x, gauge1.getPosition().y+7*text2.getCharacterSize()+buttonFPS.getLocalBounds().height);
                            }

                        }

                        // Return to the menu
                        if(event.type == Event::MouseButtonReleased && isHover(menu1, window))
                        {
                            screen = 0;
                        }
                    }

                    // Button transformation when the cursor is hover
                    hoverTrans(menu1, window), hoverTrans(gauge1, window), hoverTrans(gauge2, window), hoverTrans(buttonFPS, window), hoverTrans(lang, window);

                    // Sound of the menu button
                    if(isHover(menu1, window) || isHover(gauge1, window) || isHover(gauge2, window) || isHover(buttonFPS, window) || isHover(lang, window))
                    {
                        if(!hoverButton)
                            hover.play();

                        hoverButton = true;
                    }
                    else
                        hoverButton = false;

                    // Rotation of the background
                    menuBg.rotate(0.25);

                    // Display
                    window.clear();
                    window.draw(menuBg);
                    window.draw(zone1);
                    window.draw(text1);
                    window.draw(text2);
                    window.draw(gauge1);
                    window.draw(gauge2);
                    window.draw(cursor1);
                    window.draw(cursor2);
                    window.draw(lang);
                    window.draw(buttonFPS);
                    window.draw(menu1);
                    if(showFPS)
                        window.draw(fps);
                    window.display();
                }
            }

                // About
            case 4:
            {
                page = 0;

                // Story
                zone1.setPosition(2*zone1.getOutlineThickness(), 2*zone1.getOutlineThickness());

                if(!language)
                    text3.setString("« As you know, since 2142, Mercury has become one of the rarest and\nmost popular chemical species of our planet.\nWe, the scientists, need it for our research and our work in alchemy.\nTo have some, the cheapest way is to participate at the \"Mercury Pong\"\ntournament, organized annually by our community.\n\nAnd this year you will represent our laboratory, kid!\nI remember Professor Von Krieg in his heyday, when you play Pong.\nOur future research are based on your shoulders!\n\nThe rules of the tournament are simple, a drop of mercury is put on the\nfield and each adversaries control a racket.\nA drop is split into two at each contact with a racket and if you do not\ncaught them, they will fall into your gutter.\nWhen there is no more drop on the ground, the winner is the player\nwith the less quantity of mercury in his gutter.\nAnd he won all the valuable stuff. Your turn now! »");
                else
                    text3.setString("Comme tu le sais, depuis 2142, le mercure est devenu l'une des espèces\nchimiques les plus rares et les plus prisées de notre planète.\nNous, les scientifiques, en avons besoin pour nos recherches et nos\ntravaux en alchimie. Pour nous en munir, le moyen le plus simple est de\nparticiper au grand tournoi de « Mercury Pong » organisé chaque année\npar notre communauté. Et cette année c'est toi qui va représenter\nnotre laboratoire gamin ! Tu me rappelle le professeur Von Krieg à sa\ngrande époque quand je te vois jouer à Pong. Toutes nos futures\nrecherches reposent sur tes épaules !\n\nLes règles de ce tournoi sont simples, une goutte de mercure est mise\nen jeu sur un terrain et les deux adversaires contrôlent chacun\nune raquette. La goutte se divisera en deux à chaque contact avec\nune raquette et si tu ne les rattrapes pas, elles tomberont dans ta\ngouttière. Le gagnant est le joueur qui a le moins de mercure de\nson côté quand il n'y a plus de goutte en jeu.\nEt il remporte l'ensemble de la précieuse substance ! A toi de jouer !");

                text3.setFont(textFont);
                text3.setCharacterSize(22);

                prof.setPosition(SCREEN_WIDTH-zone1.getOutlineThickness()/2, zone1.getOutlineThickness());

                zone1.setSize(Vector2f(SCREEN_WIDTH-4*zone1.getOutlineThickness()-prof.getLocalBounds().width, SCREEN_HEIGHT-2*zone1.getOutlineThickness()));

                if(!language)
                    text1.setString("Story");
                else
                    text1.setString("Histoire");

                text1.setFont(titleFont);
                text1.setCharacterSize(60);
                text1.setPosition((zone1.getPosition().x+zone1.getSize().x/2)-text1.getLocalBounds().width/2, zone1.getPosition().y);

                text3.setPosition(3*zone1.getOutlineThickness(), 2*zone1.getOutlineThickness()+2*text1.getLocalBounds().height);

                menu1.setPosition(3*zone1.getOutlineThickness(), SCREEN_HEIGHT-menu1.getLocalBounds().height-zone1.getOutlineThickness());

                if(!language)
                    next.setTexture(nextLoad, true);
                else
                    next.setTexture(nextFrLoad, true);

                next.setPosition(zone1.getSize().x+zone1.getOutlineThickness()-next.getLocalBounds().width, SCREEN_HEIGHT-next.getLocalBounds().height-zone1.getOutlineThickness());

                // Stuff
                kid.setPosition(SCREEN_WIDTH+zone2.getOutlineThickness()/2, zone1.getOutlineThickness());

                zone2.setPosition(SCREEN_WIDTH+kid.getLocalBounds().width+2*zone2.getOutlineThickness(), 2*zone2.getOutlineThickness());
                zone2.setSize(Vector2f(SCREEN_WIDTH-kid.getLocalBounds().width-4*zone2.getOutlineThickness(), SCREEN_HEIGHT-2*zone2.getOutlineThickness()));

                if(!language)
                    text2.setString("Stuff");
                else
                    text2.setString("Autre");
                text2.setFont(titleFont);
                text2.setCharacterSize(60);
                text2.setPosition((zone2.getPosition().x+zone2.getSize().x/2)-text2.getLocalBounds().width/2, zone2.getPosition().y);

                if(!language)
                    text4.setString("You can modify the game (images, musics, sounds and fonts), simply by\nreplacing the files.\nIf you put multiple files in a folder, the program will choose one of them\nrandomly ; therefore the name of the file does not matter.\nHowever some formats (like mp3) cannot be used, because this game is\nmade with SFML.\nMoreover you cannot change the name of the folders, using a new one,\nor let one of them empty without changing the source code.\nBy the way, it is better to keep the original size for the images.");
                else
                    text4.setString("Vous pouvez modifier le jeu (images, musique, sons et polices),\nsimplement en remplaçant les fichiers.\nSi vous plusieurs fichier dans un dossier, le programme choisira un\nd'entre eux aléatoirement ; par conséquent le nom des fichiers n'a pas\nd'importance.\nCependant certains formats (comme mp3) ne peuvent pas être utilisé,\nparce que ce jeu a été créé à l'aide de la SFML.\nDe plus, vous ne pouvez pas non plus changer le nom des dossiers,\nen utiliser un nouveau, ou en laisser un vide sans changer le code.\nIl est aussi recommandé de garder la taille originale pour les images.");

                text4.setFont(textFont);
                text4.setCharacterSize(22);
                text4.setPosition(zone2.getPosition().x+zone2.getOutlineThickness(), 2*zone2.getOutlineThickness()+2*text2.getLocalBounds().height);

                menu2.setPosition(2*SCREEN_WIDTH-menu2.getLocalBounds().width-3*zone2.getOutlineThickness(), SCREEN_HEIGHT-menu2.getLocalBounds().height-zone2.getOutlineThickness());

                if(!language)
                    previous.setTexture(previousLoad, true);
                else
                    previous.setTexture(previousFrLoad, true);

                previous.setPosition(zone2.getPosition().x+zone2.getOutlineThickness(), SCREEN_HEIGHT-previous.getLocalBounds().height-zone2.getOutlineThickness());

                while(screen == 4)
                {
                    getFPS(time2, clock, fps, count);

                    while(window.pollEvent(event))
                    {
                        // Close the game
                        if(event.type == Event::Closed)
                            screen = -1;

                        if(event.type == Event::KeyPressed)
                        {

                            if(event.key.code == Keyboard::Escape)
                                screen = -1;

                            if(event.key.code == Keyboard::Right)
                                page = 1;

                            else if(event.key.code == Keyboard::Left)
                            {
                                if(prof.getPosition().x == SCREEN_WIDTH-zone1.getOutlineThickness()/2)
                                    screen = 0;

                                page = 0;
                            }
                        }

                        // Click detection
                        if((event.type == Event::MouseButtonReleased))
                        {
                            // Return to the menu
                            if(isHover(menu1, window) || isHover(menu2, window))
                                screen = 0;

                            // Next page
                            if(isHover(next, window))
                                page = 1;

                            // Previous page
                            if(isHover(previous, window))
                                page = 0;
                        }
                    }

                    // Button transformation when the cursor is hover
                    hoverTrans(menu1, window);
                    hoverTrans(next, window);
                    hoverTrans(menu2, window);
                    hoverTrans(previous, window);

                    // Sound of the buttons
                    if(isHover(menu1, window) || isHover(next, window) || isHover(menu2, window) || isHover(previous, window))
                    {
                        if(!hoverButton)
                            hover.play();

                        hoverButton = true;
                    }
                    else
                        hoverButton = false;

                    // Transition when the page change
                    if(page && prof.getPosition().x > -zone1.getOutlineThickness()/2)
                    {
                        prof.move(-transSpeed, 0);
                        zone1.move(-transSpeed, 0);
                        text1.move(-transSpeed, 0);
                        text3.move(-transSpeed, 0);
                        menu1.move(-transSpeed, 0);
                        next.move(-transSpeed, 0);

                        kid.move(-transSpeed, 0);
                        zone2.move(-transSpeed, 0);
                        text2.move(-transSpeed, 0);
                        text4.move(-transSpeed, 0);
                        menu2.move(-transSpeed, 0);
                        previous.move(-transSpeed, 0);
                    }
                    else if(!page && prof.getPosition().x < SCREEN_WIDTH-zone1.getOutlineThickness()/2)
                    {
                        prof.move(transSpeed, 0);
                        zone1.move(transSpeed, 0);
                        text1.move(transSpeed, 0);
                        text3.move(transSpeed, 0);
                        menu1.move(transSpeed, 0);
                        next.move(transSpeed, 0);

                        kid.move(transSpeed, 0);
                        zone2.move(transSpeed, 0);
                        text2.move(transSpeed, 0);
                        text4.move(transSpeed, 0);
                        menu2.move(transSpeed, 0);
                        previous.move(transSpeed, 0);
                    }

                    // Rotation of the background
                    menuBg.rotate(0.25);

                    // Display
                    window.clear();
                    window.draw(menuBg);
                    if(prof.getPosition().x > -zone1.getOutlineThickness()/2)
                    {
                        window.draw(zone1);
                        window.draw(text1);
                        window.draw(text3);
                        window.draw(menu1);
                        window.draw(next);
                        window.draw(prof);
                    }
                    if(prof.getPosition().x < SCREEN_WIDTH-zone1.getOutlineThickness()/2)
                    {
                        window.draw(zone2);
                        window.draw(text2);
                        window.draw(text4);
                        window.draw(kid);
                        window.draw(menu2);
                        window.draw(previous);
                    }
                    if(showFPS)
                        window.draw(fps);
                    window.display();
                }
            }
                break;
        }
    }while(screen >= 0);

    return EXIT_SUCCESS;
}
