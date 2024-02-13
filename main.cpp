
#include <iostream>

#include "header/working_with_file.h"
#include "header/triangulation.h"

int main(int argc, char* argv[])
{
  
  /* Take parameters */

  std::string input_file_name{};
  std::string output_file_name{};

for (int i = 1; i < argc; ++i) {
    /* Take arg */
    std::string arg = argv[i];

    if ((arg == "-i" || arg == "--input") && i + 1 < argc) {
        /* The parameter of the input file is found.*/
        input_file_name = argv[++i];
    } else if ((arg == "-o" || arg == "--output") && i + 1 < argc) {
        /* The parameter of the ouput file is found. */
        output_file_name = argv[++i];
    } else {
        std::cerr << "Unknown parameter or missing value: " << arg << std::endl;
        return 1;
    }
}

if (input_file_name.empty()) {
    std::cerr << "The name of the input file is not specified ( -i <INPUT_FILE> or--input <INPUT_FILE>)"<< std::endl;
        return 1;
}

if (output_file_name.empty()) {
    std::cerr << "The name of the ouput file is not specified ( -o <OUTPUT_FILE> or --output <OUTPUT_FILE>)"<< std::endl;
        return 1;
}


  wwf::working_with_file wf{};
  std::string tmp_file_name_XYZ{};
  if(!wf.get_XYZ_file_for_CGAL(input_file_name, tmp_file_name_XYZ)) {
    std::cerr << "Error converting files." << std::endl;
    return 1;
  }

  trng::triangulation tr{};
  if(!tr.perform_triangulation(tmp_file_name_XYZ)) {
    std::cerr << "Error perform triangulation" << std::endl;
    return 1;
  }

  std::string tmp_file_name_OBJ{};
  if(!tr.get_OBJ_file(tmp_file_name_OBJ)) {
    std::cerr << "Error getting OBJ file" << std::endl;
    return 1;
  }

  if(!wf.get_file_for_task(tmp_file_name_OBJ, output_file_name)) {
    std::cerr << "Error getting file for task." << std::endl;
    return 1;
  }
return 0;
}