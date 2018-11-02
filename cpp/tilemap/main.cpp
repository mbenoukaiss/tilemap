#include <SFML/Graphics.hpp>

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML");
    window.setFramerateLimit(60);

    sf::Texture tiles;
    if(!tiles.loadFromFile("assets/rpgtiles.png"))
        throw std::runtime_error("Failed to load RPG tiles");

    sf::VertexArray vertices(sf::Quads, 8);
    vertices[0].position = sf::Vector2f(0.0f, 0.0f);
    vertices[1].position = sf::Vector2f(200.0f, 0.0f);
    vertices[2].position = sf::Vector2f(200.0f, 200.0f);
    vertices[3].position = sf::Vector2f(0.0f, 200.0f);
    vertices[0].texCoords = sf::Vector2f(160.0f, 288.0f);
    vertices[1].texCoords = sf::Vector2f(192.0f, 288.0f);
    vertices[2].texCoords = sf::Vector2f(192.0f, 320.0f);
    vertices[3].texCoords = sf::Vector2f(160.0f, 320.0f);

    vertices[4].position = sf::Vector2f(0.0f, 0.0f);
    vertices[5].position = sf::Vector2f(200.0f, 0.0f);
    vertices[6].position = sf::Vector2f(200.0f, 200.0f);
    vertices[7].position = sf::Vector2f(0.0f, 200.0f);
    vertices[4].texCoords = sf::Vector2f(480.0f, 128.0f);
    vertices[5].texCoords = sf::Vector2f(512.0f, 128.0f);
    vertices[6].texCoords = sf::Vector2f(512.0f, 160.0f);
    vertices[7].texCoords = sf::Vector2f(480.0f, 160.0f);

    while(window.isOpen()) {
        sf::Event event = {};

        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(51, 51, 51));
        window.draw(vertices, &tiles);
        window.display();
    }

    return 0;
}
