#ifndef TILEMAP_LAYER_H
#define TILEMAP_LAYER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
#include "Tileset.h"

namespace tiles {

class LayerBuilder;

class Layer : public sf::Drawable, public sf::Transformable {

    friend class LayerBuilder;

    public:
    Layer(const Layer& other);
    Layer(Layer&& other) noexcept;
    ~Layer() override;

    int* tiles();
    const std::shared_ptr<Tileset>& tileset() const;
    const sf::Vector2u& size() const;
    const sf::Vector2f& offset() const;

    Layer& operator=(const Layer& other);
    Layer& operator=(Layer&& other) noexcept;

    protected:
    Layer();
    void copyTiles(int* tiles);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::shared_ptr<Tileset> m_tileset;
    int* m_tiles;
    sf::Vector2u* m_size;
    sf::Vector2f* m_offset;

};

class LayerBuilder {

    public:
    LayerBuilder();
    virtual ~LayerBuilder();

    LayerBuilder& setTileset(std::shared_ptr<Tileset>& tileset);
    LayerBuilder& setTiles(int* tiles);
    LayerBuilder& setTiles(std::initializer_list<int> tiles);
    LayerBuilder& setSize(unsigned int width, unsigned int height);
    LayerBuilder& setSize(sf::Vector2u& size);
    LayerBuilder& setOffset(float x, float y);
    LayerBuilder& setOffset(sf::Vector2f& offset);

    Layer* build() const;

    private:
    std::shared_ptr<Tileset> m_tileset;
    int* m_tiles;
    sf::Vector2u* m_size;
    sf::Vector2f* m_offset;

};

} // namespace tiles

#endif //TILEMAP_LAYER_H
