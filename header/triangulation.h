#ifndef __TRIANGULATION_H__
#define __TRIANGULATION_H__


#include <CGAL/Surface_mesh.h>
#include <CGAL/disable_warnings.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <string>
#include <array>

typedef std::array<std::size_t,3> Facet;
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3  Point_3;
typedef CGAL::Surface_mesh<Point_3> Mesh;

namespace trng {
    class triangulation {
        public:
            int perform_triangulation(const std::string& _inputfile_name_XYZ_for_CGAL);
            int get_OBJ_file(std::string& _outputfile_name_OBJ);
        private:
            const std::string ouput_file_name_OBJ{"tmp_output_wwf.obj"};
            Mesh m;
    };
}

#endif /* __TRIANGULATION_H__ */