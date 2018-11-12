#include <SFML/Graphics.hpp>
#include "include/Tilemap.h"

const unsigned int TILE_SIZE = 32;
const unsigned int WIDTH_TILES_COUNT = 14;
const unsigned int HEIGHT_TILES_COUNT = 10;
const unsigned int WINDOW_WIDTH = 96;
const unsigned int WINDOW_HEIGHT = 96;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tilemap");
    window.setFramerateLimit(60);

    auto rpgtiles = std::make_shared<tiles::Tileset>("assets/rpgtiles.png", TILE_SIZE);

    auto background = tiles::LayerBuilder()
            .setTileset(rpgtiles)
            .setTiles({
                163, 163, 160, 161, 161, 161, 161, 161, 161, 162, 163, 163, 163, 163,
                163, 163, 176,   0,   1,   1,   2, 177, 193, 194, 163, 163, 163, 163,
                163, 160, 177,  16,  17,  50,  18, 178, 209, 210, 163, 163, 163, 163,
                163, 176, 177,  16,  50,  48,  34, 178, 163, 163, 163, 163, 163, 163,
                163, 192, 177,  16,  66,  18, 177, 194, 163, 163, 163, 163, 163, 163,
                163, 208, 176,  32,  33,  34, 178, 210, 163, 163, 163, 163, 163, 163,
                163, 163, 192, 193, 193, 193, 194, 163, 163, 163, 163, 163, 163, 163,
                163, 163, 208, 209, 209, 209, 210, 163, 163, 163, 163, 163, 163, 163,
                163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163,
                163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163
            })
            .setSize(WIDTH_TILES_COUNT * TILE_SIZE, HEIGHT_TILES_COUNT * TILE_SIZE)
            .setOffset(0, 0)
            .build();

    auto boat = tiles::LayerBuilder()
            .setTileset(rpgtiles)
            .setTiles({
                224, 225, 226, 227,
                240, 241, 242, 243,
            })
            .setSize(4 * TILE_SIZE, 2 * TILE_SIZE)
            .setOffset(8 * TILE_SIZE, 7 * TILE_SIZE)
            .build();

    tiles::Tilemap map(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));
    map.addLayer(*background);
    map.addLayer(*boat);

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
