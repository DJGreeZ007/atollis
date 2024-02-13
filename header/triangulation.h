#ifndef __TRIANGULATION_H__
#define __TRIANGULATION_H__

/* CGAL lib*/
#include <CGAL/Surface_mesh.h>
#include <CGAL/disable_warnings.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

/* c++ lib */
#include <string>
#include <array>

/* typedef*/
typedef std::array<std::size_t,3> Facet;
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3  Point_3;
typedef CGAL::Surface_mesh<Point_3> Mesh;

namespace trng {
    class triangulation {
        public:
            /*
            * @name perform_triangulation
            * 
            * @note This function reads the XYZ file and restores the read point 
            * cloud using the advancing_front_surface_reconstruction function.
            * The result is saved in this class.
            * The following get_OBJ_file function will use this result.
            *
            * @param _inputfile_name_XYZ_for_CGAL Name XYZ file in CGAL style
            * @link https://doc.cgal.org/latest/Stream_support/IOStreamSupportedFileFormats.html#IOStreamXYZ
            *
            * @return 0 - successful, otherwise an error.
            */
            int perform_triangulation(const std::string& _inputfile_name_XYZ_for_CGAL);
            
            /*
            * @name get_OBJ_file
            * 
            * @note The function returns the name of the file in which 
            * the triangulation result was recorded.
            * The previous function is perform_triangulation.
            *
            * @param [output] _outputfile_name_OBJ Name OBJ file
            *
            * @return 0 - successful, otherwise an error.
            */
            int get_OBJ_file(std::string& _outputfile_name_OBJ);
        private:
            /* The name of the file that will store the OBJ file */
            const std::string ouput_file_name_OBJ{"tmp_files/tmp_output_wwf.obj"};
            Mesh m; /*< The object's mesh */
    };
}

#endif /* __TRIANGULATION_H__ */