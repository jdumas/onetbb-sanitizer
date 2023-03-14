#include "mesh_to_volume.h"
#include "mesh.h"

#include <openvdb/tools/MeshToVolume.h>

namespace mylib {

namespace {

///
/// Adapter class to interface a mesh with OpenVDB functions.
///
class MeshAdapter
{
public:
    ///
    /// Constructs a new instance.
    ///
    /// @param[in]  mesh       Input mesh.
    /// @param[in]  transform  World to index transform.
    ///
    MeshAdapter(const Mesh& mesh, const openvdb::math::Transform& transform)
        : m_mesh(mesh)
        , m_transform(transform)
    {}

    /// Number of mesh facets.
    size_t polygonCount() const { return static_cast<size_t>(m_mesh.facets.size()); }

    /// Number of mesh vertices.
    size_t pointCount() const { return static_cast<size_t>(m_mesh.vertices.size()); }

    /// Number of vertices for a given facet.
    size_t vertexCount(size_t f) const { return 3; }

    ///
    /// Return a vertex position in the grid index space.
    ///
    /// @param[in]  f     Queried facet index.
    /// @param[in]  lv    Queried local vertex index.
    /// @param[out] pos   Vertex position in grid index space.
    ///
    void getIndexSpacePoint(size_t f, size_t lv, openvdb::Vec3d& pos) const
    {
        auto p = m_mesh.vertices[m_mesh.facets[f][lv]];
        pos = openvdb::Vec3d(p[0], p[1], p[2]);
        pos = m_transform.worldToIndex(pos);
    }

protected:
    const Mesh& m_mesh;
    const openvdb::math::Transform& m_transform;
};

} // namespace

openvdb::FloatGrid::Ptr mesh_to_volume(const Mesh& mesh, float voxel_size)
{
    openvdb::initialize();

    const openvdb::Vec3d offset(voxel_size / 2.0, voxel_size / 2.0, voxel_size / 2.0);
    auto transform = openvdb::math::Transform::createLinearTransform(voxel_size);
    transform->postTranslate(offset);

    MeshAdapter adapter(mesh, *transform);
    openvdb::FloatGrid::Ptr grid;
    try {
        grid = openvdb::tools::meshToVolume<openvdb::FloatGrid, MeshAdapter>(adapter, *transform);
    } catch (const openvdb::ArithmeticError&) {
        std::cerr << "Voxel size too small: " << voxel_size << std::endl;
        throw;
    }

    return grid;
}

} // namespace mylib
