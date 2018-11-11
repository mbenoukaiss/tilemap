#include "../include/Tilemap.h"

namespace tiles {

tiles::Tilemap::Tilemap(sf::Vector2u size, sf::Vector2f origin) :
        m_size(size),
        m_origin(origin) {

}

Tilemap::~Tilemap() {

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

void Tilemap::setTilemapSize(const sf::Vector2u& tilesCount) {
    m_mapSize = tilesCount;
}

void Tilemap::addLayer(const Layer& layer) {
    m_layers.emplace_back(layer);
}

void tiles::Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform.translate(-m_origin);

    for(auto& layer : m_layers) {
        target.draw(layer, states); //TODO: test if it'll be inside the window before drawing
    }
}

} // namespace tiles