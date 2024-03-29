#include "../header/working_with_file.h"

/* c++ lib */
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <iterator>

/*
* @name add_commas
* 
* @note The function of placing commas between coordinates.
* Attention! The initial spaces are removed
*
* @param input The line in which you need to place commas.
*
* @return The comma-separated string.
*/
std::string add_commas(const std::string& _input);

bool wwf::working_with_file::get_XYZ_file_for_CGAL(const std::string &_input_file_name, std::string& _output_file_name_xyz)
{
    /* Files */
    std::ifstream input_file(_input_file_name);
    std::ofstream input_file_for_CGAL(input_file_name_XYZ_for_CGAL);


    if (!(input_file.is_open() && input_file_for_CGAL.is_open())) 
        return false;

    /* Read input files */
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
        /* Return filename output file*/
        _output_file_name_xyz = input_file_name_XYZ_for_CGAL;
    }

    return true;
}

bool wwf::working_with_file::get_file_for_task(const std::string &_output_file_name_OBJ, const std::string &_output_file_name_for_task)
{
    /* Files */
    std::ifstream output_file_OBJ(_output_file_name_OBJ);
    std::ofstream output_file_for_task(_output_file_name_for_task);

    if (!(output_file_OBJ.is_open() && output_file_for_task.is_open())) 
        return false;

    std::size_t counter_vert{1}; /*< Counter for vertices */
    std::size_t counter_tr{1};   /*< Counter for triangles*/

    /* Read lines from OBJ file*/
    std::string line{};
    while (std::getline(output_file_OBJ, line)) {
        /* Skipping empty lines */
        if (line.empty()) {
            continue;
        }

        /* You can provide comments from the OBJ file */
        if (line[0] == '#') {
            // line = line.substr(1);
            // output_file_for_task << "*" << line << std::endl;
            continue;
        }

        /* Replacing the letters V with vertex numbers. */
        if(line[0] == 'v') {
            /* Add comment as in the example task. */
            if(counter_vert == 1) {
                output_file_for_task << "*   N,      X       Y       Z" << std::endl;
                output_file_for_task << "* Nodes" << std::endl;
            }
            line = line.substr(1);

            output_file_for_task << std::setw(7) << counter_vert << ",  " << add_commas(line) << std::endl;
            counter_vert++;
            continue;
        }

        /* Replacing the letters f with triangle numbers */
        if(line[0] == 'f') {
            /* Add comment as in the example task. */
            if(counter_tr == 1) {
                output_file_for_task << std::endl << std::endl;
                output_file_for_task << "* Elements" << std::endl;
            }
            /* To do add commas to line */
            line = line.substr(1);
            output_file_for_task << std::setw(7)<< counter_tr << ",  " << add_commas(line) << std::endl;
            counter_tr++;
            continue;
        }
    }
    
    return true;
}


std::string add_commas(const std::string& _input) {

    std::string input{_input}; /*< Copy string */
    
    /* Removing initial spaces */
    input.erase(0, input.find_first_not_of(' '));

    std::istringstream iss(input);
    std::ostringstream oss;
    std::string token;
    std::vector<std::string> tokens;

    /* Splitting a string into tokens. */
    std::copy(std::istream_iterator<std::string>(iss),
              std::istream_iterator<std::string>(),
              std::back_inserter(tokens));

    /* Collecting a string with commas. */
    for (size_t i = 0; i < tokens.size(); ++i) {
        oss << tokens[i];
        if (i != tokens.size() - 1) { /* Check last token. */
            oss << ", ";
        }
    }

    return oss.str();
}