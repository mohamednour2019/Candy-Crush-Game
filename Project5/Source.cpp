#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <ctime>
#include<iostream>
#include"Menu.h"
#include<fstream>
#include<cmath>
#include<algorithm>
using namespace std;
using namespace sf;
int tile = 95;
bool ifmoving = false, swaping = false;


struct piece
{
    int x, y, col, row, kind, match = 0, alpha = 255, score = 0;

} grid[20][20];




void swap(piece p1, piece p2)
{
    swap(p1.col, p2.col);
    swap(p1.row, p2.row);
    grid[p1.row][p1.col] = p1;
    grid[p2.row][p2.col] = p2;
}



void matchfind(piece p) {
    if (grid[p.row][p.col].kind == grid[p.row + 1][p.col].kind) {
        if (grid[p.row][p.col].kind == grid[p.row - 1][p.col].kind)
        {
            for (int n = -1; n <= 1; n++) { grid[p.row - n][p.col].match++; }
        }
    }
    if (grid[p.row][p.col].kind == grid[p.row][p.col + 1].kind) {
        if (grid[p.row][p.col].kind == grid[p.row][p.col - 1].kind) {
            for (int n = -1; n <= 1; n++) { grid[p.row][p.col - n].match++; }
        }
    }
}

void moving(piece p) {
    int motionx, motiony;
    for (int n = 0; n < 9; n++) 
    {

        motionx = grid[p.row][p.col].x - grid[p.row][p.col].col * tile;
        motiony = grid[p.row][p.col].y - grid[p.row][p.col].row * tile;
        if (motionx) {
            grid[p.row][p.col].x -= motionx / abs(motionx);

        }
        if (motiony) { grid[p.row][p.col].y -= motiony / abs(motiony); }
        if (motionx || motiony) { ifmoving = 1; }

    }
}


void deletinganimation(piece p) {
    if (grid[p.row][p.col].match) if (grid[p.row][p.col].alpha > 10) {
        grid[p.row][p.col].alpha -= 10; ifmoving = true;
    }
}

void deleting(piece p) {
    if (grid[p.row][p.col].match) {
        for (int n = p.row; n >= 1; n--) {
            if (!grid[n][p.col].match) {
                swap(grid[p.row][p.col], grid[n][p.col]); break;
            }

        }
    }
}

void updating(piece p, int&s) {

    grid[p.row][p.col].kind = rand()%5;
    grid[p.row][p.col].y = -tile * s;
    grid[p.row][p.col].match = 0;
    grid[p.row][p.col].alpha = 255;
    s++;

}
int main()
{
    RenderWindow window(sf::VideoMode(1500, 900), "Candy Crush");
    Texture m;
    m.loadFromFile("menuback.png"); \
        Sprite menubackground(m);

    Restart:
    Menu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case::Event::KeyReleased:
                switch (event.key.code)
                {
                case ::Keyboard::Up:
                    menu.MoveUp();
                    break;

                case ::Keyboard::Down:
                    menu.MoveDown();
                    break;

                case ::Keyboard::Return:
                    switch (menu.GetPressedItem())
                    {
                    case 0:
                    {window.clear(Color::Black);
                    srand(time(0));
                    Vector2i offset(520, 28);
                    window.setFramerateLimit(85.5);


                    /*pices pictures*/
                    Texture t2;
                    t2.loadFromFile("cake.png");
                    t2.setSmooth(true);
                    Sprite pieces(t2);
                    pieces.setScale(2.15, 2.15);


                    /*background picture 1*/
                    Texture t1;
                    t1.loadFromFile("background.png");
                    Sprite background(t1);

                    /*finishing game background*/
                    Texture b2;
                    b2.loadFromFile("finishing back.png");
                    Sprite finishingbackground(b2);

                    /*finish board win*/
                    Texture b;
                    b.loadFromFile("final board.png");
                    b.setSmooth(true);
                    Sprite board(b);
                    board.setPosition(430, 0);
                    board.setScale(1, 1);

                    /*finish board lose*/
                    Texture blose;
                    blose.loadFromFile("final board lose.png");
                    blose.setSmooth(true);
                    Sprite board2(blose);
                    board2.setPosition(430, 0);
                    board2.setScale(1, 1);


                    /*winner :*/
                    int wineropacity = 0;
                    Texture t3;
                    t3.setSmooth(true);
                    t3.loadFromFile("LevelComplete.png");
                    Sprite winer(t3);
                    winer.setColor(Color(255, 255, 255, 230));
                    winer.setScale(1.3, .9);
                    winer.setPosition(120, 530);
                    SoundBuffer winerbuffer;
                    winerbuffer.loadFromFile("SFX - Arch Win Screen.ogg");
                    Sound winsound(winerbuffer);

                    /*loser :*/
                    int loseropacity = 0;
                    Texture t4;
                    t4.setSmooth(true);
                    t4.loadFromFile("GameOver.png");
                    Sprite loser(t4);
                    loser.setColor(Color(255, 255, 255, 230));
                    loser.setScale(1.3, .9);
                    loser.setPosition(120, 530);
                    SoundBuffer loserbuffer;
                    loserbuffer.loadFromFile("SFX - Level Failed1.ogg");
                    Sound losesound(loserbuffer);


                    /*font*/
                    Font font;
                    font.loadFromFile("CANDY.TTF");



                    /*target score*/
                    int targetscore, star2, star3;
                    Text target;
                    /*targetscore = 12000*/
                    targetscore = 5000;
                    star2 = targetscore + 4000;
                    star3 = star2 + 200;
                    target.setFont(font);
                    target.setString(to_string(targetscore));
                    target.setPosition(215, 25);
                    target.setCharacterSize(45);

                    /*moves counter*/
                    int moves = 30;
                    Text movescount;
                    movescount.setFont(font);
                    movescount.setPosition(175, 230);
                    movescount.setCharacterSize(45);


                    /*star1 in game*/
                    int starone = 0;
                    Texture s1;
                    s1.setSmooth(true);
                    s1.loadFromFile("star1.png");
                    Sprite star1(s1);
                    star1.setScale(.14, .14);
                    star1.setPosition(280, 557);
                    SoundBuffer bufferstar1;
                    bufferstar1.loadFromFile("SFX - 1 Star.ogg");
                    Sound star1sonud(bufferstar1);

                    /*star1 on board*/
                    int flagboard1 = 0;
                    Texture d1;
                    d1.loadFromFile("star1board.png");
                    d1.setSmooth(true);
                    Sprite star1board(d1);
                    star1board.setScale(.39, .39);
                    star1board.setPosition(512, 75);


                    /*star2 in game*/
                    int startwo = 0;
                    Texture s2;
                    s2.loadFromFile("star2.png");
                    Sprite starlight2(s2);
                    starlight2.setScale(.14, .14);
                    starlight2.setPosition(267, 478);
                    SoundBuffer bufferstar2;
                    bufferstar2.loadFromFile("SFX - 2 Star.ogg");
                    Sound star2sonud(bufferstar2);

                    /*star2 on board*/
                    int flagboard2 = 0;
                    Texture d2;
                    d2.loadFromFile("star2board.png");
                    d2.setSmooth(true);
                    Sprite star2board(d2);
                    star2board.setScale(.39, .39);
                    star2board.setPosition(620, 35);



                    /*star3 in game*/
                    int starthree = 0;
                    Texture s3;
                    s3.loadFromFile("star3.png");
                    Sprite starlight3(s3);
                    starlight3.setScale(.14, .14);
                    starlight3.setPosition(267, 412);
                    SoundBuffer bufferstar3;
                    bufferstar3.loadFromFile("SFX - 3 Star.ogg");
                    Sound star3sonud(bufferstar3);

                    /*star3 on board*/
                    int flagboard3 = 0;
                    Texture d3;
                    d3.loadFromFile("star3board.png");
                    d3.setSmooth(true);
                    Sprite star3board(d3);
                    star3board.setScale(.3, .3);
                    star3board.setPosition(800, 71);

                    /*score counter*/
                    int sscore = 0;
                    Text scorecount;
                    scorecount.setFont(font);
                    scorecount.setPosition(100, 400);
                    scorecount.setCharacterSize(45);

                    /*loop's sound*/
                    SoundBuffer bufferloop;
                    int soundlevel = 100;
                    bufferloop.loadFromFile("Candy Crush Loop5.ogg");
                    Sound soundloop(bufferloop);
                    soundloop.setLoop(true);
                    soundloop.setVolume(soundlevel);
                    soundloop.play();


                    /*click sound*/
                    SoundBuffer  bufferclick;
                    bufferclick.loadFromFile("click.wav");
                    Sound  soundclick(bufferclick);
                    int clicklevel = 50;
                    soundclick.setVolume(clicklevel);


                    /*deleting sound*/
                    SoundBuffer deletings;
                    deletings.loadFromFile("SFX - Crack.ogg");
                    Sound deletingsound(deletings);
                    deletingsound.setVolume(50);



                    for (int i = 1; i <= 9; i++) {
                        for (int j = 1; j <= 9; j++)
                        {
                            grid[i][j].kind = rand()%5;
                            grid[i][j].col = j;
                            grid[i][j].row = i;
                            grid[i][j].x = j * tile;
                            grid[i][j].y = i * tile;

                        }

                    }


                    int x1, y1, x2, y2;
                    int click = 0;
                    Vector2i pos;



                    while (1)
                    {
                        window.isOpen();
                        Event event;

                        while (window.pollEvent(event))
                        {
                            if (event.type == event.Closed)
                                window.close();
                            if (Keyboard::isKeyPressed(Keyboard::Key::Add)) {
                                soundlevel += 10;
                                soundloop.setVolume(soundlevel);
                            }
                            if (Keyboard::isKeyPressed(Keyboard::Key::Subtract)) {
                                soundlevel -= 10;
                                soundloop.setVolume(soundlevel);
                            }
                            if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
                                goto Restart;
                            }

                            if (event.type == Event::MouseButtonPressed)

                                if (event.key.code == Mouse::Left)
                                {

                                    if (!swaping && !ifmoving)click++;
                                    pos = Mouse::getPosition(window) - offset;
                                    soundclick.play();

                                }


                        }
                        if (pos.x < 850) {

                            if (click == 1)
                            {

                                x1 = pos.x / tile + 1;
                                y1 = pos.y / tile + 1;


                            }
                            if (click == 2)
                            {

                                x2 = pos.x / tile + 1;
                                y2 = pos.y / tile + 1;


                                if (abs(x2 - x1) + abs(y2 - y1) == 1)
                                {
                                    swap(grid[y1][x1], grid[y2][x2]);
                                    swaping = 1;
                                    click = 0;


                                }
                                else { click = 1; }
                            }
                        }
                        else { click = 0; }


                        for (int i = 1; i <= 9; i++) {
                            for (int j = 1; j <= 9; j++)
                            {
                                piece p = grid[i][j];
                                matchfind(p);
                            }
                        }

                        ifmoving = false;
                        for (int i = 1; i <= 9; i++) {
                            for (int j = 1; j <= 9; j++)
                            {
                                piece p = grid[i][j];
                                moving(p);
                            }
                        }


                        if (!ifmoving)
                            for (int i = 1; i <= 9; i++)
                                for (int j = 1; j <= 9; j++) {
                                    piece p = grid[i][j];
                                    deletinganimation(p);
                                }

                        /*getting score*/
                        int score = 0;
                        for (int i = 1; i <= 9; i++) {
                           for (int j = 1; j <= 9; j++) {
                              if (grid[i][j].match)score++;

                            }
                        }
                        sscore += score;
                        scorecount.setString(to_string(sscore));

                        /*moves countdown*/
                        if (swaping && !ifmoving)
                        {
                            if (score) moves--;

                        }
                        movescount.setString(to_string(moves));


                        /*second swap if not matching*/
                        if (swaping && !ifmoving)
                        {
                            if (!score) swap(grid[y1][x1], grid[y2][x2]); swaping = 0;
                        }



                        if (!ifmoving)
                        {

                            for (int i = 9; i >= 1; i--) {
                                for (int j = 1; j <= 9; j++) {
                                    piece p = grid[i][j];
                                    if (p.match)deletingsound.play();
                                    deleting(p);
                                }

                            }

                            for (int j = 1; j <= 9; j++)
                                for (int i = 9, s = 0; i >= 1; i--)
                                    if (grid[i][j].match)
                                    {
                                        piece p = grid[i][j];
                                        updating(p, s);
                                    }

                        }
                        window.draw(background);
                        for (int i = 1; i <= 9; i++) {
                            for (int j = 1; j <= 9; j++)
                            {
                                pieces.setTextureRect(IntRect(grid[i][j].kind * 49, 0, 49, 49));
                                pieces.setColor(Color(255, 255, 255, grid[i][j].alpha));
                                pieces.setPosition(grid[i][j].x, grid[i][j].y);
                                pieces.move(offset.x - tile, offset.y - tile);
                                window.draw(pieces);
                            }
                        }


                        int finishingflag = false;
                        window.draw(target);
                        window.draw(scorecount);
                        window.draw(movescount);
                        if (sscore >= targetscore) { window.draw(star1); starone++; }
                        if (sscore >= star2) { window.draw(starlight2);  startwo++; }
                        if (sscore >= star3) { window.draw(starlight3); starthree++; }
                        if (starone == 1) { star1sonud.play(); flagboard1 = 1; }
                        if (startwo == 1) { star2sonud.play(); flagboard2 = 1; }
                        if (starthree == 1) { star3sonud.play(); flagboard3 = 1; }

                        window.display();



                        /*next level text*/
                        Text next_level;
                        next_level.setFont(font);
                        next_level.setString("Press 'Enter' to next Level");
                        next_level.setCharacterSize(35);
                        next_level.setFillColor(Color::Black);
                        next_level.setPosition(530, 40);

                        /*Main Menu Text*/
                        Text mainmenu;
                        mainmenu.setFont(font);
                        mainmenu.setString("Press 'Escape' to Main Minu");
                        mainmenu.setCharacterSize(35);
                        mainmenu.setFillColor(Color::Black);
                        mainmenu.setPosition(530, 40);


                        int pass_level_two = 0;
                        if (!moves && !ifmoving && !score) {
                            scorecount.setPosition(690, 293);
                            scorecount.setCharacterSize(45);
                            finishingflag = true;
                            soundloop.stop();
                            if (sscore >= targetscore) {
                                winsound.play();
                                window.draw(finishingbackground);
                                window.draw(winer);
                                window.draw(board);
                                if (flagboard1)window.draw(star1board);
                                if (flagboard2)window.draw(star2board);
                                if (flagboard3)window.draw(star3board);
                                window.draw(scorecount);
                                window.draw(next_level);
                                pass_level_two = 1;


                            }
                            if (sscore < targetscore) {
                                losesound.play();
                                window.draw(finishingbackground);
                                window.draw(loser);
                                window.draw(board2);
                                window.draw(scorecount);
                                window.draw(mainmenu);

                            }
                            window.display();
                            int nextlevel_flag = 0;
                            while (finishingflag) {
                                window.pollEvent(event);
                                if (event.type == event.Closed)
                                    window.close();
                                if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
                                    goto Restart;
                                }
                                /*next level*/
                                if(pass_level_two)if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
                                    nextlevel_flag = 1;
                                }
                                if (nextlevel_flag == 1) {
                                    int sscore = 0;
                                    window.setFramerateLimit(85.5);


                                    /*new background picture 2*/

                                    t1.loadFromFile("backlevel2.png");

                                    /*target score*/
                                    targetscore =rand() % (15000 - 12000 + 1) + 12000;
                                    star2 = targetscore + 15000;
                                    star3 = star2 + 3000;
                                    target.setString(to_string(targetscore));
                                    target.setPosition(260, 195);
                                    target.setCharacterSize(40);

                                    /*time counter*/
                                    int period = 90;
                                    Text timecount;
                                    timecount.setFont(font);
                                    timecount.setPosition(67, 80);
                                    timecount.setCharacterSize(75);
                                    timecount.setFillColor(Color::Black);
                                    Time time, elapsed;
                                    Clock clock;
                                    timecount.setString(to_string(period));



                                    /*star1 in game*/
                                    int starone = 0;
                                    star1.setScale(.16, .16);
                                    star1.setPosition(196, 13);

                                    /*star1 on board*/
                                    int flagboard1 = 0;


                                    /*star2 in game*/
                                    int startwo = 0;
                                    starlight2.setScale(.16, .16);
                                    starlight2.setPosition(241, 4);


                                    /*star2 on board*/
                                    int flagboard2 = 0;




                                    /*star3 in game*/
                                    int starthree = 0;
                                    starlight3.setScale(.16, .16);
                                    starlight3.setPosition(303, 13);


                                    /*star3 on board*/
                                    int flagboard3 = 0;


                                    /*score counter*/
                                    scorecount.setPosition(210, 90);
                                    scorecount.setCharacterSize(50);

                                    /*loop's sound*/
                                    bufferloop.loadFromFile("Candy Crush Saga Loop 1.ogg");
                                    soundloop.setLoop(true);
                                    soundloop.play();


                                    for (int i = 1; i <= 9; i++) {
                                        for (int j = 1; j <= 9; j++)
                                        {
                                            grid[i][j].kind = rand() % 5;
                                            grid[i][j].col = j;
                                            grid[i][j].row = i;
                                            grid[i][j].x = j * tile;
                                            grid[i][j].y = i * tile;

                                        }

                                    }


                                    int x1, y1, x2, y2;
                                    int click = 0;
                                    Vector2i pos;



                                    while (1)
                                    {
                                        elapsed = clock.getElapsedTime();
                                        time = seconds(1);
                                        if (time.asSeconds() < elapsed.asSeconds()) {
                                            clock.restart();
                                            if (period > 0) period--;
                                            timecount.setString(to_string(period));

                                        }
                                        window.isOpen();
                                        Event event;

                                        while (window.pollEvent(event))
                                        {
                                            if (event.type == event.Closed)
                                                window.close();

                                            if (Keyboard::isKeyPressed(Keyboard::Key::Add)) {
                                                soundlevel += 10;
                                                soundloop.setVolume(soundlevel);
                                            }
                                            if (Keyboard::isKeyPressed(Keyboard::Key::Subtract)) {
                                                soundlevel -= 10;
                                                soundloop.setVolume(soundlevel);
                                            }
                                            if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
                                                goto Restart;
                                            }

                                            if (event.type == Event::MouseButtonPressed)

                                                if (event.key.code == Mouse::Left)
                                                {

                                                    if (!swaping && !ifmoving)click++;
                                                    pos = Mouse::getPosition(window) - offset;
                                                    soundclick.play();

                                                }
                                        }

                                        if (pos.x < 850) {

                                            if (click == 1)
                                            {

                                                x1 = pos.x / tile + 1;
                                                y1 = pos.y / tile + 1;


                                            }
                                            if (click == 2)
                                            {

                                                x2 = pos.x / tile + 1;
                                                y2 = pos.y / tile + 1;


                                                if (abs(x2 - x1) + abs(y2 - y1) == 1)
                                                {
                                                    swap(grid[y1][x1], grid[y2][x2]);
                                                    swaping = 1;
                                                    click = 0;


                                                }
                                                else { click = 1; }
                                            }
                                        }
                                        else { click = 0; }


                                        for (int i = 1; i <= 9; i++) {
                                            for (int j = 1; j <= 9; j++)
                                            {
                                                piece p = grid[i][j];
                                                matchfind(p);
                                            }
                                        }


                                        ifmoving = false;
                                        for (int i = 1; i <= 9; i++) {
                                            for (int j = 1; j <= 9; j++)
                                            {
                                                piece p = grid[i][j];
                                                moving(p);
                                            }
                                        }


                                        if (!ifmoving)
                                            for (int i = 1; i <= 9; i++)
                                                for (int j = 1; j <= 9; j++) {
                                                    piece p = grid[i][j];
                                                    deletinganimation(p);
                                                }

                                        /*getting score*/
                                        int score = 0;
                                        for (int i = 1; i <= 9; i++) {
                                            for (int j = 1; j <= 9; j++) {
                                                if (grid[i][j].match)score++;

                                            }
                                        }
                                        sscore += score;
                                        scorecount.setString(to_string(sscore));


                                        /*second swap if not matching*/
                                        if (swaping && !ifmoving)
                                        {
                                            if (!score) swap(grid[y1][x1], grid[y2][x2]); swaping = 0;
                                        }



                                        if (!ifmoving)
                                        {

                                            for (int i = 9; i >= 1; i--) {
                                                for (int j = 1; j <= 9; j++) {
                                                    piece p = grid[i][j];
                                                    if (p.match)deletingsound.play();
                                                    deleting(p);
                                                }

                                            }

                                            for (int j = 1; j <= 9; j++)
                                                for (int i = 9, s = 0; i >= 1; i--)
                                                    if (grid[i][j].match)
                                                    {
                                                        piece p = grid[i][j];
                                                        updating(p, s);
                                                    }

                                        }
                                        window.draw(background);
                                        for (int i = 1; i <= 9; i++) {
                                            for (int j = 1; j <= 9; j++)
                                            {
                                                pieces.setTextureRect(IntRect(grid[i][j].kind * 49, 0, 49, 49));
                                                pieces.setColor(Color(255, 255, 255, grid[i][j].alpha));
                                                pieces.setPosition(grid[i][j].x, grid[i][j].y);
                                                pieces.move(offset.x - tile, offset.y - tile);
                                                window.draw(pieces);
                                            }
                                        }


                                        int finishingflag = false;
                                        window.draw(target);
                                        window.draw(scorecount);
                                        window.draw(timecount);

                                        if (sscore >= targetscore) { window.draw(star1); starone++; }
                                        if (sscore >= star2) { window.draw(starlight2);  startwo++; }
                                        if (sscore >= star3) { window.draw(starlight3); starthree++; }
                                        if (starone == 1) { star1sonud.play(); flagboard1 = 1; }
                                        if (startwo == 1) { star2sonud.play(); flagboard2 = 1; }
                                        if (starthree == 1) { star3sonud.play(); flagboard3 = 1; }

                                        window.display();


                                        int pass_level3 = 0;
                                        if (!period && !ifmoving && !score) {
                                            scorecount.setPosition(690, 293);
                                            scorecount.setCharacterSize(45);
                                            finishingflag = true;
                                            soundloop.stop();
                                            if (sscore >= targetscore) {
                                                winsound.play();
                                                window.draw(finishingbackground);
                                                window.draw(winer);
                                                window.draw(board);
                                                if (flagboard1)window.draw(star1board);
                                                if (flagboard2)window.draw(star2board);
                                                if (flagboard3)window.draw(star3board);
                                                window.draw(scorecount);
                                                window.draw(next_level);
                                                pass_level3 = 1;


                                            }
                                            if (sscore < targetscore) {
                                                losesound.play();
                                                window.draw(finishingbackground);
                                                window.draw(loser);
                                                window.draw(board2);
                                                window.draw(scorecount);
                                                window.draw(mainmenu);


                                            }
                                            window.display();
                                            int nextlevel_flag = 0;
                                            while (finishingflag) {
                                                window.pollEvent(event);
                                                if (event.type == event.Closed)
                                                    window.close();
                                                if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
                                                    goto Restart;
                                                }
                                                /*next level*/
                                                if(pass_level3)if (Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
                                                    nextlevel_flag = 1;
                                                }
                                                if (nextlevel_flag == 1) {
                                                    int sscore = 0;
                                                    window.setFramerateLimit(85.5);


                                                    /*background picture 3*/
                                                    t1.loadFromFile("backlevel3.png");

                                                    /*target score*/
                                                    targetscore = rand() % (16000 - 15000 + 1) + 15000;
                                                    star2 = targetscore + 4000;
                                                    star3 = star2 + 3000;
                                                    target.setString(to_string(targetscore));
                                                    target.setPosition(220, 710);
                                                    target.setCharacterSize(30);

                                                    /*time counter*/
                                                    int period = 90;
                                                    timecount.setPosition(250, 265);
                                                    timecount.setCharacterSize(35);
                                                    timecount.setString(to_string(period));

                                                    /*moves counter*/
                                                    int moves = rand() % (35 - 30 + 1) + 30;
                                                    movescount.setPosition(255, 200);
                                                    movescount.setCharacterSize(45);

                                                    /*star1 in game*/
                                                    int starone = 0;
                                                    star1.setScale(.12, .12);
                                                    star1.setPosition(242, 516);

                                                    /*star1 on board*/
                                                    int flagboard1 = 0;


                                                    /*star2 on board*/
                                                    int flagboard2 = 0;


                                                     /*star3 on board*/
                                                    int flagboard3 = 0;



                                                    /*star2 in game*/
                                                    int startwo = 0;
                                                    starlight2.setScale(.12, .12);
                                                    starlight2.setPosition(229, 464);


                                                    /*star3 in game*/
                                                    int starthree = 0;
                                                    starlight3.setScale(.12, .12);
                                                    starlight3.setPosition(230, 424);


                                                    /*score counter*/
                                                    scorecount.setPosition(220, 630);
                                                    scorecount.setCharacterSize(40);

                                                    /*loop's sound*/
                                                    bufferloop.loadFromFile("Candy Crush Soundtrack3.ogg");
                                                    soundloop.setLoop(true);
                                                    soundloop.play();

                                                    for (int i = 1; i <= 9; i++) {
                                                        for (int j = 1; j <= 9; j++)
                                                        {
                                                            grid[i][j].kind = rand() % 5;
                                                            grid[i][j].col = j;
                                                            grid[i][j].row = i;
                                                            grid[i][j].x = j * tile;
                                                            grid[i][j].y = i * tile;

                                                        }

                                                    }


                                                    int x1, y1, x2, y2;
                                                    int click = 0;
                                                    Vector2i pos;



                                                    while (1)
                                                    {
                                                        elapsed = clock.getElapsedTime();
                                                        time = seconds(1);
                                                        if (time.asSeconds() < elapsed.asSeconds()) {
                                                            clock.restart();
                                                            if (period > 0) period--;
                                                            timecount.setString(to_string(period));

                                                        }
                                                        window.isOpen();
                                                        Event event;

                                                        while (window.pollEvent(event))
                                                        {
                                                            if (event.type == event.Closed)
                                                                window.close();

                                                            if (Keyboard::isKeyPressed(Keyboard::Key::Add)) {
                                                                soundlevel += 10;
                                                                soundloop.setVolume(soundlevel);
                                                            }
                                                            if (Keyboard::isKeyPressed(Keyboard::Key::Subtract)) {
                                                                soundlevel -= 10;
                                                                soundloop.setVolume(soundlevel);
                                                            }
                                                            if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
                                                                goto Restart;
                                                            }

                                                            if (event.type == Event::MouseButtonPressed)

                                                                if (event.key.code == Mouse::Left)
                                                                {

                                                                    if (!swaping && !ifmoving)click++;
                                                                    pos = Mouse::getPosition(window) - offset;
                                                                    soundclick.play();

                                                                }

                                                        }

                                                        if (pos.x < 850) {

                                                            if (click == 1)
                                                            {

                                                                x1 = pos.x / tile + 1;
                                                                y1 = pos.y / tile + 1;


                                                            }
                                                            if (click == 2)
                                                            {

                                                                x2 = pos.x / tile + 1;
                                                                y2 = pos.y / tile + 1;


                                                                if (abs(x2 - x1) + abs(y2 - y1) == 1)
                                                                {
                                                                    swap(grid[y1][x1], grid[y2][x2]);
                                                                    swaping = 1;
                                                                    click = 0;


                                                                }
                                                                else { click = 1; }
                                                            }
                                                        }
                                                        else { click = 0; }


                                                        for (int i = 1; i <= 9; i++) {
                                                            for (int j = 1; j <= 9; j++)
                                                            {
                                                                piece p = grid[i][j];
                                                                matchfind(p);
                                                            }
                                                        }


                                                        ifmoving = false;
                                                        for (int i = 1; i <= 9; i++) {
                                                            for (int j = 1; j <= 9; j++)
                                                            {
                                                                piece p = grid[i][j];
                                                                moving(p);
                                                            }
                                                        }


                                                        if (!ifmoving)
                                                            for (int i = 1; i <= 9; i++)
                                                                for (int j = 1; j <= 9; j++) {
                                                                    piece p = grid[i][j];
                                                                    deletinganimation(p);
                                                                }

                                                        /*getting score*/
                                                        int score = 0;
                                                        for (int i = 1; i <= 9; i++) {
                                                            for (int j = 1; j <= 9; j++) {
                                                                if (grid[i][j].match)score++;

                                                            }
                                                        }
                                                        sscore += score;
                                                        scorecount.setString(to_string(sscore));


                                                        /*moves countdown*/
                                                        if (swaping && !ifmoving)
                                                        {
                                                            if (score) moves--;

                                                        }
                                                        movescount.setString(to_string(moves));

                                                        /*second swap if not matching*/
                                                        if (swaping && !ifmoving)
                                                        {
                                                            if (!score) swap(grid[y1][x1], grid[y2][x2]); swaping = 0;
                                                        }



                                                        if (!ifmoving)
                                                        {

                                                            for (int i = 9; i >= 1; i--) {
                                                                for (int j = 1; j <= 9; j++) {
                                                                    piece p = grid[i][j];
                                                                    if (p.match)deletingsound.play();
                                                                    deleting(p);
                                                                }

                                                            }

                                                            for (int j = 1; j <= 9; j++)
                                                                for (int i = 9, s = 0; i >= 1; i--)
                                                                    if (grid[i][j].match)
                                                                    {
                                                                        piece p = grid[i][j];
                                                                        updating(p, s);
                                                                    }

                                                        }
                                                        window.draw(background);
                                                        for (int i = 1; i <= 9; i++) {
                                                            for (int j = 1; j <= 9; j++)
                                                            {
                                                                pieces.setTextureRect(IntRect(grid[i][j].kind * 49, 0, 49, 49));
                                                                pieces.setColor(Color(255, 255, 255, grid[i][j].alpha));
                                                                pieces.setPosition(grid[i][j].x, grid[i][j].y);
                                                                pieces.move(offset.x - tile, offset.y - tile);
                                                                window.draw(pieces);
                                                            }
                                                        }


                                                        int finishingflag = false;
                                                        window.draw(target);
                                                        window.draw(scorecount);
                                                        window.draw(movescount);
                                                        window.draw(timecount);
                                                        if (sscore >= targetscore) { window.draw(star1); starone++; }
                                                        if (sscore >= star2) { window.draw(starlight2);  startwo++; }
                                                        if (sscore >= star3) { window.draw(starlight3); starthree++; }
                                                        if (starone == 1) { star1sonud.play(); flagboard1 = 1; }
                                                        if (startwo == 1) { star2sonud.play(); flagboard2 = 1; }
                                                        if (starthree == 1) { star3sonud.play(); flagboard3 = 1; }

                                                        window.display();




                                                        if ((!period && !ifmoving && !score) || (!moves && !ifmoving && !score)) {
                                                            scorecount.setPosition(690, 293);
                                                            scorecount.setCharacterSize(45);
                                                            finishingflag = true;
                                                            soundloop.stop();
                                                            if (sscore >= targetscore) {
                                                                winsound.play();
                                                                window.draw(finishingbackground);
                                                                window.draw(winer);
                                                                window.draw(board);
                                                                if (flagboard1)window.draw(star1board);
                                                                if (flagboard2)window.draw(star2board);
                                                                if (flagboard3)window.draw(star3board);
                                                                window.draw(scorecount);
                                                                window.draw(mainmenu);

                                                            }
                                                            if (sscore < targetscore) {
                                                                losesound.play();
                                                                window.draw(finishingbackground);
                                                                window.draw(loser);
                                                                window.draw(board2);
                                                                window.draw(scorecount);
                                                                window.draw(mainmenu);

                                                            }
                                                            window.display();
                                                            while (finishingflag) {
                                                                window.pollEvent(event);
                                                                if (event.type == event.Closed)
                                                                    window.close();
                                                                if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
                                                                    goto Restart;
                                                                }
                                                            }
                                                        }


                                                    }
                                                }
                                            }
                                        }


                                    }
                                }



                            }
                        }
                    }

                    }


                    break;
                    case 1: {
                        while (1) {
                            window.isOpen();
                            Event event;
                            while (window.pollEvent(event)) {
                                if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
                                    goto Restart;
                                    break;
                                }
                                }
                            Texture d;
                            d.loadFromFile("Discreption.png");
                            Sprite discreption(d);
                            window.draw(discreption);
                            window.display();
                        }
                        break; }
                    case 2:
                        window.close();
                        break;
                    }

                    break;
                }

                break;
            case::Event::Closed:
                window.close();

                break;

            }
        }

        window.clear();
        window.draw(menubackground);
        menu.draw(window);


        window.display();
    }
}