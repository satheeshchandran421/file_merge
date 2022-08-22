#include <fstream>
#include <iostream>

#include "logmerge.hpp"

LogFileMerge::LogFileMerge(FILES_LIST& ar_file_list,
                           const string& out_directory)
    : IMerge(ar_file_list, out_directory, DEFAULT_EXTN_LOG) {}

bool LogFileMerge::do_merge(const string& input_file_name,
                            const string& output_file_name) {
  bool ret = true;
  bool header_dump = false;
  ofstream op(output_file_name, ios::app);

  if (op.good() == false) {
    throw runtime_error("Unable to open " + output_file_name);
  }

  header_dump = op.tellp() == 0 ? true : false;

  ifstream ios(input_file_name);
  if (ios.good()) {
    while (ios.eof() == false) {
      string line_read;
      getline(ios, line_read);

      if (line_read.length() > 0) {
        if (header_dump == true) {
          op << line_read << endl;
          header_dump = false;
        } else if (line_read[0] != '#') {
          // TODO: parse time, and pass to is_in_range() to 
          // filter log messages based on time-range.
          op << line_read << endl;
        }
      }
    }
  } else {
    throw runtime_error("Unable to open " + input_file_name);
  }

  return (ret);
}