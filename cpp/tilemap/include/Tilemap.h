#ifndef TILEMAP_TILEMAP_H
#define TILEMAP_TILEMAP_H

#include <SFML/Graphics.hpp>

namespace tiles {

class Tilemap : public sf::Drawable, public sf::Transformable {

    public:
    Tilemap();
    Tilemap(const std::string& tileset, unsigned int tileSize);

    void loadTileset(const std::string& tileset, unsigned int tileSize);
    void setTilemap(const int* tiles, const sf::Vector2u& tilesCount);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
    sf::Texture m_texture;
    unsigned int m_tileSize;
    sf::VertexArray m_vertices;

};

} // namespace tiles


#endif //TILEMAP_TILEMAP_H
