#include "../header/triangulation.h"

#include <CGAL/Advancing_front_surface_reconstruction.h>
#include <CGAL/compute_average_spacing.h>

#include <algorithm>
#include <fstream>

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
       std::ifstream in(_inputfile_name_XYZ_for_CGAL);
       if(!in.is_open()){
              return int{};
       }

       std::vector<Point_3> points;
       std::copy(std::istream_iterator<Point_3>(in),
              std::istream_iterator<Point_3>(),
              std::back_inserter(points));

       Construct construct(m,points.begin(),points.end());

       double average_spacing = CGAL::compute_average_spacing<CGAL::Sequential_tag>(points, 6);

       CGAL::advancing_front_surface_reconstruction(points.begin(),
                                                 points.end(),
                                                 construct, average_spacing*2);
       return true;
}
int trng::triangulation::get_OBJ_file(std::string &_outputfile_name_OBJ)
{
       if(CGAL::IO::write_OBJ(ouput_file_name_OBJ, m)) {
              _outputfile_name_OBJ = ouput_file_name_OBJ;
              return true;
       }
       return false;
}