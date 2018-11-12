#include "../include/Tilemap.h"

namespace tiles {

tiles::Tilemap::Tilemap(sf::Vector2u size, sf::Vector2f origin) :
        m_size(size),
        m_origin(origin) {

}

Tilemap::~Tilemap() = default;

void tiles::Tilemap::translate(sf::Vector2f& offset) {
    translate(offset.x, offset.y);
}

void Tilemap::translate(float ox, float oy) {
    if(m_origin.x + ox < 0)
        m_origin.x = 0;
    else if(m_origin.x + m_size.x + ox > m_bounds.width)
        m_origin.x = m_bounds.width - m_size.x;
    else
        m_origin.x += ox;

    if(m_origin.y + oy < 0)
        m_origin.y = 0;
    else if(m_origin.y + m_size.y + oy > m_bounds.height)
        m_origin.y = m_bounds.height - m_size.y;
    else
        m_origin.y += oy;
}

void tiles::Tilemap::resize(sf::Vector2u& size) {
    resize(size.x, size.y);
}

void Tilemap::resize(unsigned int width, unsigned int height) {
    m_size.x = width;
    m_size.y = height;
}

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
    states.transform.translate(-m_origin);

    for(auto& layer : m_layers) {
        target.draw(layer, states); //TODO: test if it'll be inside the window before drawing
    }
}

} // namespace tiles