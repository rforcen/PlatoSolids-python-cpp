
#include "PlatoSolids.h"

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

namespace p = boost::python;
namespace np = boost::python::numpy;

#include "python.h"

static p::list tetrahedron()  {    return mesh2list( PlatoSolids::tetrahedron() );   }
static p::list cube()         {    return mesh2list( PlatoSolids::cube() );          }
static p::list octahedron()   {    return mesh2list( PlatoSolids::octahedron() );    }
static p::list icosahedron()  {    return mesh2list( PlatoSolids::icosahedron() );   }
static p::list dodecahedron() {    return mesh2list( PlatoSolids::dodecahedron() );  }
static p::list sphere(int segments)   {    return mesh2list( PlatoSolids::sphere(segments) );        }

static p::list chrysanthemum() {    return mesh2list( PlatoSolids::chrysanthemum() );  }

static p::list normal(p::list coords) { // normal of 3 coords
    auto n = PlatoSolids::calc_normal(
        list2vector(p::extract<p::list>(coords[0])),
        list2vector(p::extract<p::list>(coords[1])),
        list2vector(p::extract<p::list>(coords[2])) );

    return p::list(vector2list(n));
}

static p::list polygon(int n) {   return vv2list(PlatoSolids::textPolygon(n)); } // [u,v] of a n side polygon

BOOST_PYTHON_MODULE(PlatoSolids) {
    def("tetrahedron", tetrahedron);
    def("cube", cube);
    def("octahedron", octahedron);
    def("icosahedron", icosahedron);
    def("dodecahedron", dodecahedron);
    def("sphere", sphere, (p::arg("segments")=20));

    def("chrysanthemum", chrysanthemum);

    def("normal", normal, (p::arg("coordinates")));
    def("polygon", polygon, (p::arg("n")));
}