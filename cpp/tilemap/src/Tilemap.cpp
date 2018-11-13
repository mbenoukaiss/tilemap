#include <iostream>
#include "../include/Tilemap.h"

namespace tiles {

tiles::Tilemap::Tilemap() = default;

Tilemap::~Tilemap() = default;

void Tilemap::addLayer(const Layer& layer) {
    if(layer.offset().x < m_bounds.left)
        m_bounds.left = layer.offset().x;
    if(layer.offset().x + layer.size().x > m_bounds.width)
        m_bounds.width = layer.offset().x + layer.size().x;

    if(layer.offset().y < m_bounds.top)
        m_bounds.top = layer.offset().y;
    if(layer.offset().y + layer.size().y > m_bounds.height)
        m_bounds.height = layer.offset().y + layer.size().y;
    
    m_layers.emplace_back(layer);
}

void tiles::Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Vector2f center_offset = target.getView().getSize() / 2.0f;
    sf::FloatRect drawn(target.getView().getCenter() - center_offset, target.getView().getSize());

    if(drawn.left + target.getView().getSize().x > m_bounds.width) {
        drawn.left = m_bounds.width - target.getView().getSize().x;
    }
    if(drawn.left < 0) {
        drawn.left = 0;
    }

    if(drawn.top + target.getView().getSize().y > m_bounds.height) {
        drawn.top = m_bounds.height - target.getView().getSize().y;
    }
    if(drawn.top < 0) {
        drawn.top = 0;
    }


    sf::View new_view = target.getView();
    new_view.setCenter(drawn.left + center_offset.x, drawn.top + center_offset.y);
    target.setView(new_view);

    for(auto& layer : m_layers) {
        target.draw(layer, states); //TODO: test if it'll be inside the window before drawing
    }
}

} // namespace tiles