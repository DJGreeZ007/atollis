#include "../header/triangulation.h"

/* CGAL lib */
#include <CGAL/Advancing_front_surface_reconstruction.h>
#include <CGAL/compute_average_spacing.h>

/* c++ lib */
#include <algorithm>
#include <fstream>


/* 
* @name Construct
* 
* @note This structure was created for the operation of 
* the advancing_front_surface_reconstruction function from the CGAL library.
*
* @link https://doc.cgal.org/latest/Advancing_front_surface_reconstruction/Advancing_front_surface_reconstruction_2reconstruction_surface_mesh_8cpp-example.html
*/
struct Construct{
  Mesh& mesh;
  template < typename PointIterator>
  Construct(Mesh& mesh,PointIterator b, PointIterator e)
    : mesh(mesh)
  {
    for(; b!=e; ++b){
      boost::graph_traits<Mesh>::vertex_descriptor v;
      v = add_vertex(mesh);
      mesh.point(v) = *b;
    }
  }
  Construct& operator=(const Facet f)
  {
    typedef boost::graph_traits<Mesh>::vertex_descriptor vertex_descriptor;
    typedef boost::graph_traits<Mesh>::vertices_size_type size_type;
    mesh.add_face(vertex_descriptor(static_cast<size_type>(f[0])),
                  vertex_descriptor(static_cast<size_type>(f[1])),
                  vertex_descriptor(static_cast<size_type>(f[2])));
    return *this;
  }
  Construct&
  operator*() { return *this; }
  Construct&
  operator++() { return *this; }
  Construct
  operator++(int) { return *this; }
};

int trng::triangulation::perform_triangulation(const std::string &_inputfile_name_XYZ_for_CGAL)
{
    /* Open file */
    std::ifstream in(_inputfile_name_XYZ_for_CGAL);
    if(!in.is_open()){
        return false;
    }

    /* Get points*/
    std::vector<Point_3> points; /*< The list of points obtained from the XYZ file.*/
    std::copy(std::istream_iterator<Point_3>(in),
            std::istream_iterator<Point_3>(),
            std::back_inserter(points));


    Construct construct(m,points.begin(),points.end());

    /* Finding the average distance. */
    double average_spacing = CGAL::compute_average_spacing<CGAL::Sequential_tag>(points, 6);

    double ratio{2.0}; /* coefficient for radius_ratio_bound */
    /* @link https://doc.cgal.org/latest/Advancing_front_surface_reconstruction/group__PkgAdvancingFrontSurfaceReconstructionRef.html#gaa2b1f41291920247fd5c6ef7c09f70a4 */
    
    CGAL::advancing_front_surface_reconstruction(points.begin(),
                                                points.end(),
                                                construct, average_spacing*ratio);
    return true;
}

int trng::triangulation::get_OBJ_file(std::string &_outputfile_name_OBJ)
{
    /* @line https://doc.cgal.org/latest/BGL/group__PkgBGLIoFuncsOBJ.html#ga6354f94dfd862ef741f5b3cccf95f35c */
    if(CGAL::IO::write_OBJ(ouput_file_name_OBJ, m)) {
        _outputfile_name_OBJ = ouput_file_name_OBJ;
        return true;
    }
    return false;
}