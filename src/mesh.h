#pragma once

#include <array>
#include <vector>

namespace mylib {

struct Mesh
{
    using Vertex = std::array<float, 3>;
    using Facet = std::array<int, 3>;

    std::vector<Vertex> vertices;
    std::vector<Facet> facets;
};

} // namespace mylib
