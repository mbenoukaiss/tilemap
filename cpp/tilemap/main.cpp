#include <SFML/Graphics.hpp>
#include "include/Tilemap.h"

const unsigned int TILE_SIZE = 32;
const unsigned int WIDTH_TILES_COUNT = 6;
const unsigned int HEIGHT_TILES_COUNT = 5;
const unsigned int WINDOW_WIDTH = WIDTH_TILES_COUNT * TILE_SIZE;
const unsigned int WINDOW_HEIGHT = HEIGHT_TILES_COUNT * TILE_SIZE;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tilemap");
    window.setFramerateLimit(60);

    const int tiles[WIDTH_TILES_COUNT*HEIGHT_TILES_COUNT] = {
              0,   1,   1,   2,  177, 193,
             16,  17,  50,  18,  178, 209,
             16,  50,  48,  34,  178, 163,
             16,  66,  18, 177,  194, 163,
             32,  33,  34, 178,  210, 163,
    };

    tiles::Tilemap tilemap("assets/rpgtiles.png", TILE_SIZE);
    tilemap.setTilemap(tiles, sf::Vector2u(WIDTH_TILES_COUNT, HEIGHT_TILES_COUNT));

    while(window.isOpen()) {
        sf::Event event = {};

        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();

        }

        window.clear(sf::Color(51, 51, 51));
        window.draw(tilemap);
        window.display();
    }

    return 0;
}
