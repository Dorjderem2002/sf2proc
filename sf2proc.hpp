#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#define HALF_PI 1.57079632679489661923
#define PI 3.14159265358979323846
#define QUARTER_PI 0.7853982
#define TAU 6.28318530717958647693
#define TWO_PI 6.28318530717958647693

class sf2Proc
{
public:
    sf2Proc();
    ~sf2Proc();
public:
    //virtual functions
    virtual bool setup();
    virtual bool draw();
    
    //will change in future
    bool handleEvent();
    
    //functions to start engine
    bool createWindow(int width,int height,std::string label);
    void start();
    
    //useful functions
    
    //draw shapes
    void rect(int x,int y,int w,int h);
    void circle(int x,int y,int diameter);
    void ellipse(int x,int y,int w,int h);
    void line(int x1,int y1,int x2,int y2);
    void square(int x,int y,int l);
    void quad(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4);
    void point(int x,int y);
    void triangle(int x1,int y1,int x2,int y2,int x3,int y3);
    
    //color functions
    void background(int color);
    void fill(int color);
    void fill(int r,int g,int b);
    void fill(int r,int g,int b,int a);
    
    //public Variables
    float frameCount = 0;
private:
    sf::RenderWindow* window;
    bool engineRunning = false;
    sf::Event sfEvent;
    
    //Variables
    sf::Color fillColor = sf::Color::White;
    sf::Color backgroundColor = sf::Color::Black;
    sf::ContextSettings settings;
    sf::Clock clock;
};


inline sf2Proc::sf2Proc()
{
    settings.antialiasingLevel = 8;
}

inline sf2Proc::~sf2Proc()
{
    delete window;
}

inline bool sf2Proc::createWindow(int width,int height,std::string label)
{
    window = new sf::RenderWindow(sf::VideoMode(width,height),label,sf::Style::Default, settings);
    if(window->isOpen())
    {
        return true;
    }
    return false;
}

inline bool sf2Proc::setup()
{
    return false;
}

inline bool sf2Proc::draw()
{
    return false;
}

inline bool sf2Proc::handleEvent()
{
    while (window->pollEvent(sfEvent)) {
        if(sfEvent.type == sf::Event::Closed)
        {
            window->close();
            engineRunning = false;
        }
    }
    return false;
}

inline void sf2Proc::start()
{
    std::cout<<"sf2proc succesfully started"<<std::endl;
    engineRunning = true;
    setup();
    
    while (engineRunning && window->isOpen()) {
        handleEvent();
        float currentTime = clock.restart().asSeconds();
        frameCount = 1.f / currentTime;
        //update();
        window->clear(backgroundColor);
        draw();
        window->display();
    }
}

inline void sf2Proc::rect(int x,int y,int w,int h)
{
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(w,h));
    shape.setPosition(x, y);
    shape.setFillColor(fillColor);
    window->draw(shape);
}
inline void sf2Proc::background(int color)
{
    backgroundColor = sf::Color(color,color,color);
}
inline void sf2Proc::fill(int color)
{
    fillColor = sf::Color(color,color,color);
}
inline void sf2Proc::fill(int r,int g, int b)
{
    fillColor = sf::Color(r,g,b,255);
}
inline void sf2Proc::fill(int r,int g, int b,int a)
{
    fillColor = sf::Color(r,g,b,a);
}
inline void sf2Proc::circle(int x, int y, int diameter)
{
    sf::CircleShape cShape;
    cShape.setRadius(diameter / 2);
    cShape.setPosition(x, y);
    window->draw(cShape);
}
inline void sf2Proc::ellipse(int x, int y, int w, int h)
{
    sf::CircleShape eShape;
    eShape.setRadius(w / 2);
    float hScale = h / w;
    eShape.setScale(1, hScale);
    eShape.setPosition(x, y);
    window->draw(eShape);
}
inline void sf2Proc::line(int x1, int y1, int x2, int y2)
{
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(x1, y1)),
        sf::Vertex(sf::Vector2f(x2, y2))
    };
    
    window->draw(line, 2, sf::Lines);
}
inline void sf2Proc::quad(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
    sf::ConvexShape convex;
    convex.setPointCount(4);
    
    convex.setPoint(0, sf::Vector2f(x1, y1));
    convex.setPoint(1, sf::Vector2f(x2, y2));
    convex.setPoint(2, sf::Vector2f(x3, y3));
    convex.setPoint(3, sf::Vector2f(x4, y4));
    
    window->draw(convex);
}
inline void sf2Proc::point(int x, int y)
{
    sf::CircleShape pShape;
    pShape.setRadius(1);
    pShape.setPosition(x, y);
    window->draw(pShape);
}
inline void sf2Proc::triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    sf::ConvexShape convex;
    convex.setPointCount(3);
    
    convex.setPoint(0, sf::Vector2f(x1, y1));
    convex.setPoint(1, sf::Vector2f(x2, y2));
    convex.setPoint(2, sf::Vector2f(x3, y3));
    
    window->draw(convex);
}
