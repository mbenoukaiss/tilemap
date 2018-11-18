#include "../include/Layer.h"

namespace tiles {

Layer::Layer(const Layer& other) :
        m_tileset(other.m_tileset),
        m_size(other.m_size),
        m_offset(other.m_offset) {

    copyTiles(other.m_tiles);
}

Layer::Layer(Layer&& other) noexcept {
    m_tileset = std::move(other.m_tileset);

    m_tiles = other.m_tiles;
    other.m_tiles = nullptr;

    m_size = other.m_size;
    other.m_size = nullptr;

    m_offset = other.m_offset;
    other.m_offset = nullptr;
}

Layer::~Layer() {
    delete[] m_tiles;
    delete m_size;
    delete m_offset;
}

const std::shared_ptr<Tileset>& Layer::tileset() const {
    return m_tileset;
}

int* Layer::tiles() {
    return m_tiles;
}

const sf::Vector2u& Layer::size() const {
    return *m_size;
}

const sf::Vector2f& Layer::offset() const {
    return *m_offset;
}

void Layer::copyTiles(int* tiles) {
    size_t tiles_count = (m_size->x * m_size->y) / m_tileset->tileSize();
    m_tiles = (int*) std::malloc(tiles_count * sizeof(int));

    std::copy(tiles, tiles + tiles_count, m_tiles);
}

Layer& Layer::operator=(const Layer& other) {
    m_tileset = other.m_tileset;
    m_size = new sf::Vector2u(*other.m_size);
    m_offset = new sf::Vector2f(*other.m_offset);

    copyTiles(other.m_tiles);

    return *this;
}

Layer& Layer::operator=(Layer&& other) noexcept {
    m_tileset = std::move(other.m_tileset);

    m_tiles = other.m_tiles;
    other.m_tiles = nullptr;

    m_size = other.m_size;
    other.m_size = nullptr;

    m_offset = other.m_offset;
    other.m_offset = nullptr;

    return *this;
}

Layer::Layer() = default;

void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.texture = m_tileset->texture();
    states.transform.translate(*m_offset);

    auto verticalTilesCount = (unsigned int) std::ceil((float) m_size->y / m_tileset->tileSize());
    auto horizontalTilesCount = (unsigned int) std::ceil((float) m_size->x / m_tileset->tileSize());

    size_t vertices_count = verticalTilesCount * horizontalTilesCount * 4;
    sf::VertexArray vertices(sf::Quads, vertices_count);

    for(unsigned int j = 0; j < verticalTilesCount; ++j) {
        for(unsigned int i = 0; i < horizontalTilesCount; ++i) {

            unsigned int index = i + j * horizontalTilesCount;
            if(m_tiles[index] < 0) // negative number means no tile
                continue;

            int x = i * m_tileset->tileSize();
            int y = j * m_tileset->tileSize();
            unsigned int tilesetX = m_tiles[index] * m_tileset->tileSize() % m_tileset->texture()->getSize().x;
            unsigned int tilesetY = (m_tiles[index] / (m_tileset->size()->y / m_tileset->tileSize())) * m_tileset->tileSize();

            index *= 4;

            vertices[index].position = sf::Vector2f(x, y);
            vertices[index + 1].position = sf::Vector2f(x + m_tileset->tileSize(), y);
            vertices[index + 2].position = sf::Vector2f(x + m_tileset->tileSize(), y + m_tileset->tileSize());
            vertices[index + 3].position = sf::Vector2f(x, y + m_tileset->tileSize());
            vertices[index].texCoords = sf::Vector2f(tilesetX, tilesetY);
            vertices[index + 1].texCoords = sf::Vector2f(tilesetX + m_tileset->tileSize(), tilesetY);
            vertices[index + 2].texCoords = sf::Vector2f(tilesetX + m_tileset->tileSize(),
                                                                tilesetY + m_tileset->tileSize());
            vertices[index + 3].texCoords = sf::Vector2f(tilesetX, tilesetY + m_tileset->tileSize());
        }
    }

    target.draw(vertices, states);
}

LayerBuilder::LayerBuilder() {
    m_size = new sf::Vector2u(0, 0);
    m_offset = new sf::Vector2f(0.0f, 0.0f);
}

LayerBuilder::~LayerBuilder() {
    m_tiles = nullptr;
    m_size = nullptr;
    m_offset = nullptr;
}

LayerBuilder& LayerBuilder::setTileset(std::shared_ptr<Tileset>& tileset) {
    m_tileset = tileset;
    return *this;
}

LayerBuilder& LayerBuilder::setTiles(int* tiles) {
    m_tiles = tiles;
    return *this;
}

LayerBuilder& LayerBuilder::setTiles(std::initializer_list<int> tiles) {
    m_tiles = (int*) std::malloc(tiles.size() * sizeof(int));
    std::copy(tiles.begin(), tiles.end(), m_tiles);

    return *this;
}

LayerBuilder& LayerBuilder::setSize(unsigned int width, unsigned int height) {
    m_size->x = width;
    m_size->y = height;
    return *this;
}

LayerBuilder& LayerBuilder::setSize(sf::Vector2u& size) {
    return setSize(size.x, size.y);
}

LayerBuilder& LayerBuilder::setOffset(float x, float y) {
    m_offset->x = x;
    m_offset->y = y;
    return *this;
}

LayerBuilder& LayerBuilder::setOffset(sf::Vector2f& offset) {
    return setOffset(offset.x, offset.y);
}

Layer* LayerBuilder::build() const {
    auto* layer = new Layer();
    layer->m_tileset = m_tileset;
    layer->m_tiles = m_tiles;
    layer->m_size = m_size;
    layer->m_offset = m_offset;

    return layer;
}

} // namespace tiles
