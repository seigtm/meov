#include "Common.hpp"

#include "vertex.h"

namespace meov::core {

Vertex::Vertex(glm::vec3 pos, glm::vec4 clr, glm::vec2 texCoords)
    : mPos{ pos }, mClr{ clr }, mTexCoords{ texCoords } {
}

std::vector<float> Vertex::raw() const {
    std::vector<float> rawData;
    rawData.reserve(VertexInfo::count);

    for(size_t i{}; i < mPos.length(); ++i) {
        rawData.push_back(mPos[i]);
    }
    for(size_t i{}; i < mClr.length(); ++i) {
        rawData.push_back(mClr[i]);
    }
    for(size_t i{}; i < mTexCoords.length(); ++i) {
        rawData.push_back(mTexCoords[i]);
    }
    return rawData;
}


Vertices::Vertices(std::initializer_list<Vertex> &&source)
    : mSource{ std::move(source) } {
}

std::vector<float> Vertices::raw() const {
    if(empty()) {
        return {};
    }

    std::vector<float> data;
    data.reserve(mSource.size() * VertexInfo::count);

    for(const auto &vertex : mSource) {
        const auto &vertexRaw{ vertex.raw() };
        if(vertexRaw.empty()) {
            continue;
        }
        data.insert(data.end(), vertexRaw.begin(), vertexRaw.end());
    }

    return data;
}

bool Vertices::empty() const {
    return mSource.empty();
}

size_t Vertices::length() const {
    return mSource.size() * VertexInfo::stride;
}

size_t Vertices::count() const {
    return mSource.size();
}

const Vertex &Vertices::operator[](size_t id) const {
    return mSource.at(id);
}

Vertex &Vertices::operator[](size_t id) {
    return mSource.at(id);
}

}  // namespace meov::core
