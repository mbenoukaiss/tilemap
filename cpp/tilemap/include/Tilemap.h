#ifndef TILEMAP_TILEMAP_H
#define TILEMAP_TILEMAP_H

#include <SFML/Graphics.hpp>
#include "../include/Layer.h"

namespace tiles {

class Tilemap : public sf::Drawable {

    public:
    explicit Tilemap(sf::Vector2u size, sf::Vector2f origin = sf::Vector2f(0.0f, 0.0f));
    ~Tilemap() override;

    void translate(sf::Vector2f offset);
    void resize(sf::Vector2u size);
    void translate(float ox, float oy);
    void resize(unsigned int width, unsigned int height);

    void loadTileset(const std::string& tileset, unsigned int tileSize);
    void setTilemapSize(const sf::Vector2u& tilesCount);
    void addLayer(const Layer& layer);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    protected:
    sf::Texture m_texture;
    unsigned int m_tileSize;

    std::vector<Layer> m_layers;
    sf::Vector2u m_mapSize;

    sf::Vector2u m_size;
    sf::Vector2f m_origin;

};

} // namespace tiles


#endif //TILEMAP_TILEMAP_H
