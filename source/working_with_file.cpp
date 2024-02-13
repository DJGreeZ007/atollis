#include "../header/working_with_file.h"

#include <fstream>
#include <sstream>

bool wwf::working_with_file::get_XYZ_file_for_CGAL(const std::string &_input_file_name, std::string& _output_file_name_xyz)
{
    std::ifstream input_file(_input_file_name);
    std::ofstream output_file(output_file_name_XYZ_for_CGAL);


    if (!(input_file.is_open() && output_file.is_open())) 
        return false;

    std::string read_line{};
    while (std::getline(input_file, read_line)) {
        /* Skip the initial spaces. */
        size_t firstNonSpace = read_line.find_first_not_of(" \t\n\r\f\v");

        /* Check whether the line starts with an asterisk or is empty. */
        if (firstNonSpace != std::string::npos && read_line[firstNonSpace] == '*') {
            continue;
        }

        std::istringstream iss(read_line);
        std::string value{};

        /* Skipping a point number */
        std::getline(iss, value, ',');

        /* Read Point and write it to new file. */
        while (std::getline(iss, value, ',')) {
          output_file << value << " ";
        }
        _output_file_name_xyz = output_file_name_XYZ_for_CGAL;
    }

    return true;
}