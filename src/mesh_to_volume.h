#include "mesh.h"

#include <openvdb/openvdb.h>

namespace mylib {

openvdb::FloatGrid::Ptr mesh_to_volume(const Mesh& mesh, float voxel_size);

} // namespace mylib
