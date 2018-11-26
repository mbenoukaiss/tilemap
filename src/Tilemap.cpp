#include <iostream>
#include "../include/Tilemap.h"

namespace tiles {

tiles::Tilemap::Tilemap() = default;

Tilemap::~Tilemap() = default;

Layer& Tilemap::layer(std::string name) {
    return m_layers.at(name);
}

void Tilemap::addLayer(const std::string name, const Layer& layer) {
    if(layer.offset().x < m_boundaries.left)
        m_boundaries.left = layer.offset().x;
    if(layer.offset().x + layer.size().x > m_boundaries.width)
        m_boundaries.width = layer.offset().x + layer.size().x;

    if(layer.offset().y < m_boundaries.top)
        m_boundaries.top = layer.offset().y;
    if(layer.offset().y + layer.size().y > m_boundaries.height)
        m_boundaries.height = layer.offset().y + layer.size().y;

    m_layers.emplace(std::pair<std::string, Layer>(name, layer));
}

void tiles::Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::FloatRect visible(
            target.getView().getCenter() - target.getView().getSize() / 2.0f,
            target.getView().getSize()
    );

    for(auto& pair : m_layers) {
        if(visible.intersects(sf::FloatRect(pair.second.offset(), (sf::Vector2f) pair.second.size())))
            target.draw(pair.second, states);
    }
}

const sf::FloatRect& Tilemap::boundaries() const {
    return m_boundaries;
}

} // namespace tiles