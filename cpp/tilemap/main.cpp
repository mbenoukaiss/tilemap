#include <SFML/Graphics.hpp>
#include "include/Tilemap.h"

const unsigned int TILE_SIZE = 32;
const unsigned int WIDTH_TILES_COUNT = 6;
const unsigned int HEIGHT_TILES_COUNT = 5;
const unsigned int WINDOW_WIDTH = 96;
const unsigned int WINDOW_HEIGHT = 96;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tilemap");
    window.setFramerateLimit(60);

    std::vector<int> tiles = {
              0,   1,   1,   2,  177, 193,
             16,  17,  50,  18,  178, 209,
             16,  50,  48,  34,  178, 163,
             16,  66,  18, 177,  194, 163,
             32,  33,  34, 178,  210, 163,
    };

    tiles::Tilemap map("assets/rpgtiles.png", TILE_SIZE, sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT), sf::Vector2f(0, 0));
    map.setTilemap(tiles.data(), sf::Vector2u(WIDTH_TILES_COUNT, HEIGHT_TILES_COUNT));

    while(window.isOpen()) {
        sf::Event event = {};

        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::KeyPressed) {
                switch(event.key.code) {
                    case sf::Keyboard::Up:
                        map.translate(0, -2);
                        break;
                    case sf::Keyboard::Right:
                        map.translate(2, 0);
                        break;
                    case sf::Keyboard::Down:
                        map.translate(0, 2);
                        break;
                    case sf::Keyboard::Left:
                        map.translate(-2, 0);
                        break;
                    default: break;
                }
            }

        }
        
        window.clear(sf::Color(51, 51, 51));
        window.draw(map);
        window.display();
    }

    return 0;
}
