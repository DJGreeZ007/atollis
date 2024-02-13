#ifndef __WORKING_WITH_FILE_H__
#define __WORKING_WITH_FILE_H__

#include <string>

namespace wwf {
    class working_with_file {
        public:
            bool get_XYZ_file_for_CGAL(const std::string& _input_file_name, std::string& _output_file_name_xyz);
            bool get_file_for_task(const std::string& _output_file_name_OBJ, const std::string& _output_file_name_for_task);
        private:
            const std::string input_file_name_XYZ_for_CGAL{"tmp_files/tmp_input_wwf.xyz"};
    };
}

#endif /* __WORKING_WITH_FILE_H__ */