#ifndef TILEMAP_TILEMAP_H
#define TILEMAP_TILEMAP_H

#include <SFML/Graphics.hpp>

namespace tiles {

class Tilemap : public sf::Drawable {

    public:
    Tilemap();
    Tilemap(const std::string& tileset, unsigned int tileSize);

    void loadTileset(const std::string& tileset, unsigned int tileSize);
    void setTilemap(const int* tiles, const sf::Vector2u& tilesCount);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    protected:
    sf::Texture m_texture;
    unsigned int m_tileSize;
    std::vector<int> m_map;
    sf::Vector2u m_mapSize;

};

} // namespace tiles


#endif //TILEMAP_TILEMAP_H
