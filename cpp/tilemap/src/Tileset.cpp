#include "../include/Tileset.h"

namespace tiles {

Tileset::Tileset(const sf::Texture* texture, unsigned int tileSize) :
        m_texture(texture),
        m_size(new sf::Vector2u(texture->getSize())),
        m_tileSize(tileSize) {

}

Tileset::Tileset(const std::string& tileset, unsigned int tileSize) :
        m_tileSize(tileSize) {

    auto texture = new sf::Texture();

    if(!texture->loadFromFile(tileset))
        throw std::runtime_error("Failed to load tiles from " + tileset);

    m_texture = texture;
    m_size = new sf::Vector2u(texture->getSize());
}

Tileset::~Tileset() {
    delete m_texture;
    delete m_size;
}

const sf::Texture* Tileset::texture() const {
    return m_texture;
}

const sf::Vector2u* Tileset::size() const {
    return m_size;
}

unsigned int Tileset::tileSize() const {
    return m_tileSize;
}

} // namespace tiles
