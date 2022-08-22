#include <experimental/filesystem>
#include <iomanip>
#include <iostream>

#include "imerge.hpp"

namespace fs = experimental::filesystem;

bool IMerge::execute() {
  bool ret = false;

  try {
    for (auto tar_file : m_tarfiles) {
      SORTED_LIST files;
      ret = prepare(tar_file,
                    files);  // Extract and prepare list of files to be merged.

      if (ret == true) ret = run(files);  // Run merge functions.

      post();  // Clean up all temp files.
    }

    return (ret); // Done.
  } catch (exception& ex) {
    cout << "ERROR: Error while merging files. Reason : "
      << ex.what() << endl;
  } catch (...) {
    cout << "ERROR: Error while merging files. Uknown error." << endl;
  }

  ret = false;
  post();  // Clean up temp files, in case if not deleted.
  return (ret);
}

bool IMerge::prepare(const string& tar_file, SORTED_LIST& files) {
  bool ret = false;
  // Extract the tar file into a directory.
  ret = extract(tar_file);
  // Get file names from the directory.
  collect_files(files);
  return (ret);
}

bool IMerge::run(SORTED_LIST& files_list) {
  bool ret = true;

  for (auto each_file : files_list) {
    fs::path file_path{each_file};
    string opfile = m_out_directory + "/" + file_path.filename().string();
    ret = do_merge(each_file, opfile);

    if (ret == false) {
      throw("Failed to merge file " + each_file);
    }
  }

  return (ret);
}

void IMerge::post() { remove_directory(get_temp_directory()); }

void IMerge::remove_directory(const string& directory) {
  if (fs::is_directory(directory)) {
    fs::remove_all(directory);
  }
 }

bool IMerge::extract(const string& file_name) {
  bool ret = false;

  if (fs::exists({file_name}) == false) {
    throw runtime_error("Requested file '" + file_name +
                        "' doesn't exist.");
  }

  create_temp_directory_name();
  ret = fs::create_directory(get_temp_directory());  // Create a temp directory
                                                     // to extract files.
  string cmd = TAR_CMD + file_name + " -C " + get_temp_directory();
  int errcode = system(cmd.c_str());
  ret = errcode == 0 ? true : false;

  if (errcode != 0) {
    throw runtime_error("system() call returns error : " + to_string(errcode));
  }

  return (ret);
}

void IMerge::collect_files(SORTED_LIST& files) {
  const fs::path fdir{get_temp_directory()};
  // Get list of files from the requested directory, and if the extension matches, then
  // insert into a list, which will be used later to merge the files.
  for (auto entries : fs::directory_iterator(fdir)) {
    if (entries.path().extension() ==
        m_extension) {  // Match extension. (e.g *.log)
      files.push_back(entries.path().string());
    }
  }
}

void IMerge::create_temp_directory_name() {
  char dir[L_tmpnam + 1];
  char* tmp = tmpnam(dir);
  if (tmp) {
    m_exdir = string(tmp);
  } else {
    throw runtime_error("Temporary directory name could not be generated.");
  }
}