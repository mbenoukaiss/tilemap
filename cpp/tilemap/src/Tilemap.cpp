#include <iostream>
#include <zconf.h>
#include "../include/Tilemap.h"

namespace tiles {

tiles::Tilemap::Tilemap(sf::Vector2u size, sf::Vector2f origin = sf::Vector2f(0.0f, 0.0f)) {
    m_size = size;
    m_origin = origin;
}

tiles::Tilemap::Tilemap(const std::string& tileset, unsigned int tileSize,
        sf::Vector2u size, sf::Vector2f origin = sf::Vector2f(0.0f, 0.0f)) : Tilemap(size, origin) {

    loadTileset(tileset, tileSize);
}

void tiles::Tilemap::translate(sf::Vector2f offset) {
    translate(offset.x, offset.y);
}

void tiles::Tilemap::resize(sf::Vector2u size) {
    m_size = size;
}

void Tilemap::translate(float ox, float oy) {
    if(m_origin.x + ox < 0)
        m_origin.x = 0;
    else if(m_origin.x + m_size.x + ox > m_mapSize.x * m_tileSize)
        m_origin.x = m_mapSize.x * m_tileSize - m_size.x;
    else
        m_origin.x += ox;

    if(m_origin.y + oy < 0)
        m_origin.y = 0;
    else if(m_origin.y + m_size.y + oy > m_mapSize.y * m_tileSize)
        m_origin.y = m_mapSize.y * m_tileSize - m_size.y;
    else
        m_origin.y += oy;
}

void Tilemap::resize(unsigned int width, unsigned int height) {
    m_size = sf::Vector2u(width, height);
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

void tiles::Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.texture = &m_texture;

    size_t vertices_count = m_mapSize.x * m_mapSize.y * 4;
    sf::VertexArray vertices(sf::Quads, vertices_count);

    unsigned int startX = (int) m_origin.x / m_tileSize;
    unsigned int startY = (int) m_origin.y / m_tileSize;

    unsigned int horizontalTilesCount = startX + m_mapSize.x + 1;
    unsigned int verticalTilesCount = startY + m_mapSize.y + 1;

    if(m_mapSize.y < verticalTilesCount)
        verticalTilesCount = m_mapSize.y;
    if(m_mapSize.x < horizontalTilesCount)
        horizontalTilesCount = m_mapSize.x;

    for(unsigned int j = startY; j < verticalTilesCount; ++j) {
        for(unsigned int i = startX; i < horizontalTilesCount; ++i) {

            unsigned int index = i + j * m_mapSize.x;
            int x = i * m_tileSize - (unsigned int) m_origin.x;
            int y = j * m_tileSize - (unsigned int) m_origin.y;
            unsigned int tilesetX = m_map[index] * m_tileSize % m_texture.getSize().x;
            unsigned int tilesetY = (m_map[index] / (m_texture.getSize().y / m_tileSize)) * m_tileSize;

            index *= 4;

            vertices[index].position =   sf::Vector2f(x, y);
            vertices[index+1].position = sf::Vector2f(x + m_tileSize, y);
            vertices[index+2].position = sf::Vector2f(x + m_tileSize, y + m_tileSize);
            vertices[index+3].position = sf::Vector2f(x, y + m_tileSize);
            vertices[index].texCoords =   sf::Vector2f(tilesetX, tilesetY);
            vertices[index+1].texCoords = sf::Vector2f(tilesetX + m_tileSize, tilesetY);
            vertices[index+2].texCoords = sf::Vector2f(tilesetX + m_tileSize, tilesetY + m_tileSize);
            vertices[index+3].texCoords = sf::Vector2f(tilesetX, tilesetY + m_tileSize);

            for(size_t k = 0; k < 4; ++k) {
                sf::Vertex& vertex = vertices[index + k];

                if(vertex.position.x < 0) {
                    vertex.texCoords.x -= vertex.position.x;
                    vertex.position.x = 0;
                } else if(vertex.position.x > m_size.x) {
                    vertex.texCoords.x -= vertex.position.x - m_size.x;
                    vertex.position.x = m_size.x;
                }

                if(vertex.position.y < 0) {
                    vertex.texCoords.y -= vertex.position.y;
                    vertex.position.y = 0;
                } else if(vertex.position.y > m_size.y) {
                    vertex.texCoords.y -= vertex.position.y - m_size.y;
                    vertex.position.y = m_size.y;
                }
            }
        }
    }

    target.draw(vertices, states);
}

} // namespace tiles