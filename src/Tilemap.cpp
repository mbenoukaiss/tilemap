#include <iostream>
#include "../include/Tilemap.h"

namespace tiles {

tiles::Tilemap::Tilemap() = default;

Tilemap::~Tilemap() = default;

void Tilemap::addLayer(const Layer& layer) {
    if(layer.offset().x < m_boundaries.left)
        m_boundaries.left = layer.offset().x;
    if(layer.offset().x + layer.size().x > m_boundaries.width)
        m_boundaries.width = layer.offset().x + layer.size().x;

    if(layer.offset().y < m_boundaries.top)
        m_boundaries.top = layer.offset().y;
    if(layer.offset().y + layer.size().y > m_boundaries.height)
        m_boundaries.height = layer.offset().y + layer.size().y;

    m_layers.emplace_back(layer);
}

void tiles::Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::FloatRect visible(
            target.getView().getCenter() - target.getView().getSize() / 2.0f,
            target.getView().getSize()
    );

    for(auto& layer : m_layers) {
        if(visible.intersects(sf::FloatRect(layer.offset(), (sf::Vector2f) layer.size())))
            target.draw(layer, states);
    }
}

const sf::FloatRect& Tilemap::boundaries() const {
    return m_boundaries;
}

} // namespace tiles