//
// Created by Adonis on 16/04/2014.
//

#include <dirent.h>


// Get the frame rate
void getFPS(Time& time, Clock& clock, Text& fps, unsigned short int& count)
{
    time = clock.restart();

    count++;

    if(count == 60)
    {
        fps.setString("FPS: "+nbStr(floor(1.f/time.asSeconds())));
        fps.setPosition(Vector2f(SCREEN_WIDTH-1.5*fps.getLocalBounds().width, fps.getLocalBounds().height));
        count = 0;
    }

}



// Get a file in a folder, randomly
string getFile(string dir)
{
    vector<string> files;
    DIR *dp;
    struct dirent *dirp;
    const char* c_str(dir.c_str());

    dp = opendir(c_str);

    while((dirp = readdir(dp)) != NULL)
    {
        if(strcmp(dirp->d_name, ".") && strcmp(dirp->d_name, ".."))
            files.push_back(string(dirp->d_name));
    }

    closedir(dp);

    if(!files.size())
        exit(1);

    return dir+files.at(rand()%files.size());
}




// Convert number to string
string nbStr(float nb)
{
    ostringstream str;
    str << nb;
    return str.str();
}




// Detect if the mouse is over a sprite
bool isHover(Sprite button, RenderWindow& window)
{
    Mouse mouse;

    if(mouse.getPosition(window).x >= button.getPosition().x && mouse.getPosition(window).x <= button.getPosition().x + button.getLocalBounds().width && mouse.getPosition(window).y >= button.getPosition().y && mouse.getPosition(window).y <= button.getPosition().y + button.getLocalBounds().height)
        return true;

    return false;
}





// Change the sprite apparence when the mouse is hover it
void hoverTrans(Sprite& button, RenderWindow& window)
{
    if(isHover(button, window))
        button.setColor(Color(255, 255, 255));
    else
        button.setColor(Color(255, 255, 255, 128));
}