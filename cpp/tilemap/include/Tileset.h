#ifndef TILEMAP_TILESET_H
#define TILEMAP_TILESET_H

#include <SFML/Graphics.hpp>

namespace tiles {

class Tileset {

    public:
    Tileset(const sf::Texture* texture, unsigned int tileSize);
    Tileset(const std::string& tileset, unsigned int tileSize);
    virtual ~Tileset();

    const sf::Texture* texture() const;
    const sf::Vector2u* size() const;
    unsigned int tileSize() const;

    private:
    const sf::Texture* m_texture;
    const sf::Vector2u* m_size;
    const unsigned int m_tileSize;

};

} // namespace tiles

#endif //TILEMAP_TILESET_H
