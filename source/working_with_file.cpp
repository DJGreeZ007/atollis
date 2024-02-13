#include "../header/working_with_file.h"

#include <fstream>
#include <sstream>
#include <iomanip>
bool wwf::working_with_file::get_XYZ_file_for_CGAL(const std::string &_input_file_name, std::string& _output_file_name_xyz)
{
    std::ifstream input_file(_input_file_name);
    std::ofstream input_file_for_CGAL(input_file_name_XYZ_for_CGAL);


    if (!(input_file.is_open() && input_file_for_CGAL.is_open())) 
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
          input_file_for_CGAL << value << " ";
        }
        _output_file_name_xyz = input_file_name_XYZ_for_CGAL;
    }

    return true;
}
bool wwf::working_with_file::get_file_for_task(const std::string &_output_file_name_OBJ, const std::string &_output_file_name_for_task)
{
    std::ifstream output_file_OBJ(_output_file_name_OBJ);
    std::ofstream output_file_for_task(_output_file_name_for_task);

    if (!(output_file_OBJ.is_open() && output_file_for_task.is_open())) 
        return false;

    std::size_t counter_vert{1};
    std::size_t counter_tr{1};
    std::string line{};
    while (std::getline(output_file_OBJ, line)) {
        if (line.empty()) {
            continue;
        }
        if (line[0] == '#') {
            // line = line.substr(1);
            // output_file_for_task << "*" << line << std::endl;
            continue;
        }
        if(line[0] == 'v') {
            if(counter_vert == 1) {
                output_file_for_task << "*   N,      X       Y       Z" << std::endl;
                output_file_for_task << "* Nodes" << std::endl;
            }
            line = line.substr(1);
            output_file_for_task << std::setw(7) << counter_vert << "." << line << std::endl;
            counter_vert++;
            continue;
        }
        if(line[0] == 'f') {
            if(counter_tr == 1) {
                output_file_for_task << std::endl << std::endl;
                output_file_for_task << "* Elements" << std::endl;
            }
            line = line.substr(1);
            output_file_for_task << std::setw(7)<< counter_tr << "." << line << std::endl;
            counter_tr++;
            continue;
        }
    }
    
    return true;
}