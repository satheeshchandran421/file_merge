#include <fstream>
#include <iostream>

#include "logmerge.hpp"

LogFileMerge::LogFileMerge(FILES_LIST& ar_file_list,
                           const string& out_directory)
    : IMerge(ar_file_list, out_directory, DEFAULT_EXTN_LOG) {}

bool LogFileMerge::do_merge(const FILES_LIST& flist,
                            const string& output_file_name) {
  bool ret = true;
  ofstream op;
  bool header_dump = false;
  op.open(output_file_name, ios::out);

  if (op.good() == false) {
    return false;
  }

  for (auto i : flist) {
    ifstream ios(i);
    if (ios.good()) {
      while (ios.eof() == false) {
        string line_read;
        getline(ios, line_read);

        if (line_read.length() > 0) {
          if (header_dump != true) {
            op << line_read << endl;
            header_dump = true;
          } else if (line_read[0] != '#') {
            // TODO: parse time, and pass to is_in_range() to 
            // filter log messages based on time-range.
            op << line_read << endl;
          }
        }
      }
    } else {
      cout << "ERROR: Unable to open '" 
           << i << "'. Not expected." << endl;
      ret = false;
    }
  }

  return (ret);
}