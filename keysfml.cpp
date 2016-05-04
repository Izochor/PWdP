#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <cmath>

#define oknox 800
#define oknoy 600
#define promien 5
#define N 301
#define grawitacja 0.1f


void zderzenia(sf::CircleShape shapes[], float tabvx[], float tabvy[]);


void odbicia(sf::CircleShape shapes[], float tabvx[], float tabvy[]);


int main()
{
    srand(time(NULL));
    
    bool keyonoff = true;
    
    double grawitacja_dodaj=grawitacja;
    
    int tabx [N];
    for (int i=0;i<N;i++)
        tabx [i]=(2*promien)+rand()%(oknox-4*promien);
    
    
    int taby [N];
    for (int i=0;i<N;i++)
        taby [i]=(2*promien)+rand()%(oknoy-4*promien);
    
    float tabvx [N];
    for (int i=0;i<N;i++)
    {
        do
        {
            tabvx [i]=-1+2*((float)rand()/RAND_MAX);
        }
        while(tabvx[i]==0);
    }
    
    float tabvy [N];
    for (int i=0;i<N;i++)
    {
        do
        {
            tabvy [i]=-1+2*((float)rand()/RAND_MAX);
        }
        while(tabvy[i]==0);
    }
    
    sf::CircleShape shapes [N];
    for (int i=0;i<N;i++)
    {
        shapes[i].setRadius(promien);//rysuje koło
        shapes[i].setFillColor(sf::Color(200+50*sqrt(pow(tabvx[i],2)+pow(tabvy[i]+grawitacja,2)),45+10*sqrt(pow(tabvx[i],2)+pow(tabvy[i]+grawitacja,2)),0));//koło jest czarwone
        shapes[i].setPosition(tabx[i],taby[i]);//określam pozycję kółka
        shapes[i].setOrigin(shapes[i].getRadius(),shapes[i].getRadius());
        
    }
    //I TU stanie się okno, a będzie ono dobre
    sf::RenderWindow window(sf::VideoMode(oknox,oknoy), "Kulki!");//stwarzam okno i nadaję mu nazwę
    window.setVerticalSyncEnabled(true);//mam 60 fpsów
    
    sf::Image icon;//określa plik graficzny
    if (!icon.loadFromFile("icon.PNG"))//ładuje plik)
    {
        return -1;
    }
    
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());//ustawia ikonę
    
    while (window.isOpen())//gdy okno jest otwarte
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)//zamyka okno, gdy kliknę krzyżyk
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)//zamyka okno, gdy nacisnę ESC
                window.close();
            if (event.type == sf::Event::KeyPressed)//wciśnięcie czegoś zmienia licznik
                keyonoff = !keyonoff;
        }
        
        window.clear(sf::Color::Black);
        
        if(keyonoff)//rysowanie kulki w zależności od przyciśnięcia klawisza
        {
            for (int i=1;i<N;i++)
            {
                window.draw(shapes[i]);
            }
        }
        
        for (int i=0;i<N;i++)//ruch kulki
        {
            tabvy[i] += grawitacja;
            shapes[i].move(tabvx[i],tabvy[i]);
            shapes[i].setFillColor(sf::Color(200+50*sqrt(pow(tabvx[i],2)+pow(tabvy[i]+grawitacja,2)),45+10*sqrt(pow(tabvx[i],2)+pow(tabvy[i],2)),0));//koło jest czarwone
        }
        
        odbicia (shapes, tabvx, tabvy);
        zderzenia(shapes, tabvx, tabvy);
        
        window.display();
    }
    return 0;
}

void zderzenia(sf::CircleShape shapes[], float tabvx[], float tabvy[])//badanie zderzeń cząsteczek z innnymi cząstkami
{
    for(int i=0;i<N;i++)
    {
        for(int j=i+1;j<N;j++)
        {
            float odleglosc = sqrt(pow(shapes[i].getPosition().x-shapes[j].getPosition().x, 2) + pow(shapes[i].getPosition().y-shapes[j].getPosition().y, 2));
            if(odleglosc<=2*promien)
            {
                tabvx[i]=-tabvx[i];
                tabvy[i]=-tabvy[i];
                tabvx[j]=-tabvx[j];
                tabvy[j]=-tabvy[j];
                /*
                 shapes[i].setPosition(shapes[i].getPosition().x+sqrt(pow(shapes[i].getPosition().x-shapes[j].getPosition().x, 2)),
                 shapes[i].getPosition().y+sqrt(pow(shapes[i].getPosition().y-shapes[j].getPosition().y, 2)));
                 shapes[j].setPosition(shapes[j].getPosition().x+sqrt(pow(shapes[i].getPosition().x-shapes[j].getPosition().x, 2)),
                 shapes[j].getPosition().y+sqrt(pow(shapes[i].getPosition().y-shapes[j].getPosition().y, 2)));
                 */
            }
        }
    }
}

void odbicia(sf::CircleShape shapes[], float tabvx[], float tabvy[])//odbicia od ścian
{
    for(int i=0;i<N;i++)
    {
        if(shapes[i].getPosition().x <=promien)//odbijanie od lewej ściany
        {
            tabvx[i]=-tabvx[i];
            shapes[i].setPosition(promien,shapes[i].getPosition().y);
        }
        
        if(shapes[i].getPosition().x >=oknox-promien)//odbijanie od prawej ściany
        {
            tabvx[i]=-tabvx[i];
            shapes[i].setPosition(oknox-promien,shapes[i].getPosition().y);
        }
        
        if(shapes[i].getPosition().y <=promien)//odbijanie od sufitu
        {
            tabvy[i]=-tabvy[i];
            shapes[i].setPosition(shapes[i].getPosition().x,promien);
        }
        
        if(shapes[i].getPosition().y >=oknoy-promien)//odbijanie od podłogi
        {
            tabvy[i]=-tabvy[i];
            shapes[i].setPosition(shapes[i].getPosition().x,oknoy-promien);
        }
        
    }
}



