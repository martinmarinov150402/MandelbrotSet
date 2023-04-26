#include <SFML/Graphics.hpp>

const int WIDTH = 800, HEIGHT = 800;
const long double minimum = -2.0;
const long double maximum = 2.0; 
const int MAX_ITERATIONS = 200;

long double mapValue(long double val, long double in_min, long double in_max, long double out_min, long double out_max)
{
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
int main()
{
    sf::RenderWindow window(sf::VideoMode(1500,1000), "Mandelbrot Set");
    window.clear();
    window.display();
    for(int x = 0; x < WIDTH; x++)
    {
        for(int y = 0; y < HEIGHT; y++)
        {
            long double newX = mapValue(x, 0, WIDTH, minimum, maximum);
            long double newY = mapValue(y, 0, HEIGHT, minimum, maximum);

            long double xInitial = newX;
            long double yInitial = newY;

            int iterations = 0;
            for(int i = 0; i < MAX_ITERATIONS; i++)
            {
                //(x+yi)^2 = x^2 - y ^ 2 + 2xyi
                long double curX = newX * newX - newY * newY;
                long double curY = 2 * newX * newY;

                newX = curX + xInitial;
                newY = curY + yInitial;

                if(newX+newY > maximum)
                {
                    
                    break;
                }
                iterations++;
            }
            if(iterations == MAX_ITERATIONS)
            {
                sf::Vertex point(sf::Vector2f(x,y), sf::Color::White);
                window.draw(&point, 1, sf::Points);
            }
        }
    }
    window.display();


    //Event handling
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                    break;
                }
            }
        }
    }
}