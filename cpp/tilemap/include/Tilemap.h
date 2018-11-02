#ifndef TILEMAP_TILEMAP_H
#define TILEMAP_TILEMAP_H

#include <SFML/Graphics.hpp>

namespace tiles {

class Tilemap : public sf::Drawable, public sf::Transformable {

    public:
    Tilemap() = delete;
    Tilemap(const std::string& tileset, unsigned int tileSize);
    Tilemap(const std::string& tileset, unsigned int tileSize, const int* tiles,
            unsigned int width, unsigned int height);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
    sf::Texture m_texture;
    const unsigned int m_tileSize;
    sf::VertexArray m_vertices;

};

} // namespace tiles


#endif //TILEMAP_TILEMAP_H
