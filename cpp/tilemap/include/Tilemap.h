#ifndef TILEMAP_TILEMAP_H
#define TILEMAP_TILEMAP_H

#include <SFML/Graphics.hpp>

namespace tiles {

class Tilemap : public sf::Drawable {

    public:
    explicit Tilemap(sf::Vector2u size, sf::Vector2f origin);
    Tilemap(const std::string& tileset, unsigned int tileSize, sf::Vector2u size, sf::Vector2f origin);

    void translate(sf::Vector2f offset);
    void resize(sf::Vector2u size);
    void translate(float ox, float oy);
    void resize(unsigned int width, unsigned int height);

    void loadTileset(const std::string& tileset, unsigned int tileSize);
    void setTilemap(const int* tiles, const sf::Vector2u& tilesCount);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    protected:
    sf::Texture m_texture;
    unsigned int m_tileSize;

    std::vector<int> m_map;
    sf::Vector2u m_mapSize;

    sf::Vector2f m_origin;
    sf::Vector2u m_size;

};

} // namespace tiles


#endif //TILEMAP_TILEMAP_H
