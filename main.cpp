#include <SFML/Graphics.hpp>
#include <cmath>

const int WIDTH = 800, HEIGHT = 800;
long double minimum = -2.84;
long double maximum = 2.7; 
const int TRANSLATION_X = 150;
const int TRANSLATION_Y = 0;
int MAX_ITERATIONS = 200;
long double factor = 1;

long double mapValue(long double val, long double in_min, long double in_max, long double out_min, long double out_max)
{
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
int main()
{
    sf::Color colors[16];
    colors[0] = sf::Color(0, 0, 0);
    colors[1] = sf::Color(25, 7, 26);
    colors[2] = sf::Color(9, 1, 47);
    colors[3] = sf::Color(4, 4, 73);
    colors[4] = sf::Color(0, 7, 100);
    colors[5] = sf::Color(12, 44, 138);
    colors[6] = sf::Color(24, 82, 177);
    colors[7] = sf::Color(57, 125, 209);
    colors[8] = sf::Color(134, 181, 229);
    colors[9] = sf::Color(211, 236, 248);
    colors[10] = sf::Color(241, 233, 191);
    colors[11] = sf::Color(248, 201, 95);
    colors[12] = sf::Color(255, 170, 0);
    colors[13] = sf::Color(204, 128, 0);
    colors[14] = sf::Color(153, 87, 0);
    colors[15] = sf::Color(106, 52, 3);

    sf::RenderWindow window(sf::VideoMode(1500,1000), "Mandelbrot Set");
    window.clear();
    window.display();
    
    int count = 0;
    //Event handling
    while(window.isOpen())
    {
        maximum -= 0.1 * factor;
        minimum += 0.15 * factor;
        factor *= 0.9349;
        MAX_ITERATIONS += 5;
        if (count > 30)
        {
        MAX_ITERATIONS *= 1.02;
        }
        //asd
        for(int x = TRANSLATION_X; x < WIDTH + TRANSLATION_X; x++)
        {
            for(int y = TRANSLATION_Y; y < HEIGHT + TRANSLATION_Y; y++)
            {
                long double newX = mapValue(x - TRANSLATION_X, 0, WIDTH, minimum, maximum);
                long double newY = mapValue(y - TRANSLATION_Y, 0, HEIGHT, minimum, maximum);

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
                int brightness = mapValue(iterations, 0, MAX_ITERATIONS, 0, 255);
                if(iterations == MAX_ITERATIONS || brightness < 0)
                {
                    brightness = 0;   
                }
                int r = mapValue(brightness * brightness, 0, 6205, 0, 255);
                int g = brightness;
                int b = mapValue(sqrt(brightness), 0, 16, 0, 255);
                sf::Vertex point(sf::Vector2f(x,y), sf::Color(r, g, b));
                //sf::Vertex point(sf::Vector2f(x,y), colors[brightness%16]);
                window.draw(&point, 1, sf::Points);
            }
        }

        window.display();

        //=======
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
        count++;
        //window.display();
    }
}