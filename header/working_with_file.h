#ifndef __WORKING_WITH_FILE_H__
#define __WORKING_WITH_FILE_H__

#include <string>

namespace wwf {
    class working_with_file {
        public:
            bool get_XYZ_file_for_CGAL(const std::string& _input_file_name, std::string& _output_file_name_xyz);

        private:
            const std::string output_file_name_XYZ_for_CGAL{"tmp_wwf.xyz"};
    };
}

#endif /* __WORKING_WITH_FILE_H__ */