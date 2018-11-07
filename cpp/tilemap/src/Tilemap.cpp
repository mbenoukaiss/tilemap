#include <iostream>
#include <zconf.h>
#include "../include/Tilemap.h"

namespace tiles {

Tilemap::Tilemap() {

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
    m_map.resize(tilesCount.x * tilesCount.y);
    for(size_t i = 0; i < m_map.size(); ++i) {
        m_map[i] = tiles[i];
    }

    m_mapSize = tilesCount;
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.texture = &m_texture;

    size_t vertices_count = m_mapSize.x * m_mapSize.y * 4;
    sf::VertexArray tilemap(sf::Quads, vertices_count);

    for(unsigned int j = 0; j < m_mapSize.y; ++j) {
        for(unsigned int i = 0; i < m_mapSize.x; ++i) {

            unsigned int index = i + j * m_mapSize.x;
            unsigned int x = i * m_tileSize;
            unsigned int y = j * m_tileSize;
            unsigned int tilesetX = (m_map[index] % (m_texture.getSize().x / m_tileSize)) * m_tileSize;
            unsigned int tilesetY = (m_map[index] / (m_texture.getSize().y / m_tileSize)) * m_tileSize;

            index *= 4;

            tilemap[index].position =   sf::Vector2f(x, y);
            tilemap[index+1].position = sf::Vector2f(x + m_tileSize, y);
            tilemap[index+2].position = sf::Vector2f(x + m_tileSize, y + m_tileSize);
            tilemap[index+3].position = sf::Vector2f(x, y + m_tileSize);
            tilemap[index].texCoords =   sf::Vector2f(tilesetX, tilesetY);
            tilemap[index+1].texCoords = sf::Vector2f(tilesetX + m_tileSize, tilesetY);
            tilemap[index+2].texCoords = sf::Vector2f(tilesetX + m_tileSize, tilesetY + m_tileSize);
            tilemap[index+3].texCoords = sf::Vector2f(tilesetX, tilesetY + m_tileSize);
        }
    }

    target.draw(tilemap, states);
}

} // namespace tiles