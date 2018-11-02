#include <SFML/Graphics.hpp>

int main(int argc, char** argv) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML", sf::Style::Default, settings);

    sf::CircleShape shape(50.0f, 100);
    shape.setPosition(50, 50);
    shape.setFillColor(sf::Color(40, 120, 225));
    shape.setOutlineThickness(10.0f);
    shape.setOutlineColor(sf::Color(21, 96, 193));

    while(window.isOpen()) {
        sf::Event event = {};

        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed || event.type == sf::Event::LostFocus)
                window.close();
        }

        window.clear(sf::Color(51, 51, 51));
        window.draw(shape);
        window.display();
    }

    return 0;
}
