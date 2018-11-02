#include <iostream>
#include "../include/Tilemap.h"

namespace tiles {

Tilemap::Tilemap(const std::string& tileset, const unsigned int tileSize) : m_tileSize(tileSize) {

    if(!m_texture.loadFromFile(tileset))
        throw std::runtime_error("Failed to load tiles from " + tileset);

    m_vertices.setPrimitiveType(sf::Quads);
}

Tilemap::Tilemap(const std::string& tileset, const unsigned int tileSize, const int* tiles,
                 const unsigned int width, const unsigned int height) : Tilemap(tileset, tileSize) {

    m_vertices.resize(width * height * 4);

    for(unsigned int j = 0; j < height; ++j) {
        for(unsigned int i = 0; i < width; ++i) {

            unsigned int index = i + j * width;
            unsigned int x = i * tileSize;
            unsigned int y = j * tileSize;
            unsigned int tilesetX = (tiles[index] % (m_texture.getSize().x / tileSize)) * tileSize;
            unsigned int tilesetY = (tiles[index] / (m_texture.getSize().y / tileSize)) * tileSize;

            index *= 4;

            m_vertices[index].position =   sf::Vector2f(x, y);
            m_vertices[index+1].position = sf::Vector2f(x + tileSize, y);
            m_vertices[index+2].position = sf::Vector2f(x + tileSize, y + tileSize);
            m_vertices[index+3].position = sf::Vector2f(x, y + tileSize);
            m_vertices[index].texCoords =   sf::Vector2f(tilesetX, tilesetY);
            m_vertices[index+1].texCoords = sf::Vector2f(tilesetX + tileSize, tilesetY);
            m_vertices[index+2].texCoords = sf::Vector2f(tilesetX + tileSize, tilesetY + tileSize);
            m_vertices[index+3].texCoords = sf::Vector2f(tilesetX, tilesetY + tileSize);
        }
    }

}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_texture;

    target.draw(m_vertices, states);
}

} // namespace tiles