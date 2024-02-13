#ifndef __WORKING_WITH_FILE_H__
#define __WORKING_WITH_FILE_H__

/* c++ lib */
#include <string>

namespace wwf {
    class working_with_file {
        public:
            /*
            * @name get_XYZ_file_for_CGAL
            * 
            * @note This is a function that converts a file from a job 
            * to an XYZ format that the CGAL library can read.
            *
            * @param _input_file_name Name XYZ file that is taken from the --input parameters
            * @param _output_file_name_xyz Name XYZ file that CGAL can work with
            *
            * @return 0 - successful, otherwise an error.
            */
            bool get_XYZ_file_for_CGAL(const std::string& _input_file_name, std::string& _output_file_name_xyz);

            /*
            * @name get_file_for_task
            * 
            * @note This function converts the output OBJ file to the output 
            * file of the job, which is located --output
            *
            * @param _output_file_name_OBJ Name of the obj file
            * @param _output_file_name_for_task The name of the output file from the task is taken from the --output parameter
            *
            * @return 0 - successful, otherwise an error.
            */
            bool get_file_for_task(const std::string& _output_file_name_OBJ, const std::string& _output_file_name_for_task);
        private:

            /* The name of the XYZ file received after conversion */
            const std::string input_file_name_XYZ_for_CGAL{"tmp_files/tmp_input_wwf.xyz"};
    };
}

#endif /* __WORKING_WITH_FILE_H__ */