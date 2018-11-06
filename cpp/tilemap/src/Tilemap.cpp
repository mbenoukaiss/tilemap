#include <iostream>
#include "../include/Tilemap.h"

namespace tiles {

Tilemap::Tilemap() {
    m_vertices.setPrimitiveType(sf::Quads);
}

Tilemap::Tilemap(const std::string& tileset, const unsigned int tileSize) : Tilemap() {
    loadTileset(tileset, tileSize);
}

void Tilemap::loadTileset(const std::string& tileset, unsigned int tileSize) {
    m_tileSize = tileSize;

    if(!m_texture.loadFromFile(tileset))
        throw std::runtime_error("Failed to load tiles from " + tileset);
}

void Tilemap::setTilemap(const int* tiles, const sf::Vector2u& tilesCount) {
    m_vertices.resize(tilesCount.x * tilesCount.y * 4);

    for(unsigned int j = 0; j < tilesCount.y; ++j) {
        for(unsigned int i = 0; i < tilesCount.x; ++i) {

            unsigned int index = i + j * tilesCount.x;
            unsigned int x = i * m_tileSize;
            unsigned int y = j * m_tileSize;
            unsigned int tilesetX = (tiles[index] % (m_texture.getSize().x / m_tileSize)) * m_tileSize;
            unsigned int tilesetY = (tiles[index] / (m_texture.getSize().y / m_tileSize)) * m_tileSize;

            index *= 4;

            m_vertices[index].position =   sf::Vector2f(x, y);
            m_vertices[index+1].position = sf::Vector2f(x + m_tileSize, y);
            m_vertices[index+2].position = sf::Vector2f(x + m_tileSize, y + m_tileSize);
            m_vertices[index+3].position = sf::Vector2f(x, y + m_tileSize);
            m_vertices[index].texCoords =   sf::Vector2f(tilesetX, tilesetY);
            m_vertices[index+1].texCoords = sf::Vector2f(tilesetX + m_tileSize, tilesetY);
            m_vertices[index+2].texCoords = sf::Vector2f(tilesetX + m_tileSize, tilesetY + m_tileSize);
            m_vertices[index+3].texCoords = sf::Vector2f(tilesetX, tilesetY + m_tileSize);
        }
    }
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_texture;

    target.draw(m_vertices, states);
}

} // namespace tiles