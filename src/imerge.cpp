#include <experimental/filesystem>
#include <iomanip>
#include <iostream>

#include "imerge.hpp"

namespace fs = experimental::filesystem;

bool IMerge::execute() {
  bool ret = false;

  if (m_tarfiles.size()) {
    SORTED_LIST files;
    ret =
        prepare(files);  // Extract and prepare list of files to be merged.

    if (ret == true) ret = run(files);  // Run merge functions.

    post();  // Clean up all temp files.
  }

  return (ret);
}

bool IMerge::prepare(SORTED_LIST& files) {
  bool ret = false;
  // Iterate through all tar files and extract them into 
  // separate directories. 
  for (auto i : m_tarfiles) {
    ret = extract(i);

    if (ret == true) {
      // Get file names from the directory. 
      // Grouped in key(file name)-value(list of files) format.
      collect_files(i, files);
    } else {
      cout << "ERROR: Error while extracting " << quoted(i) << " file. "
           << endl;
      break;
    }
  }

  return (ret);
}

bool IMerge::run(SORTED_LIST& files) {
  bool ret = true;

  for (auto i : files) {
    string opfile = m_out_directory + "/" + i.first;
    ret = do_merge(i.second, opfile);

    if (ret == false) {
      cout << "ERROR: Failed to merge file '" << i.first << "'" << endl;
      break;
    }
  }

  return (ret);
}

void IMerge::post() {
  for (auto i : m_tarfiles) {
    string rmdir = m_out_directory + "/" + trim_extension(i);
    remove_directory(rmdir);
  }
}

string IMerge::trim_extension(const string& file_name) {
  string res;
  fs::path file_path{file_name};
  string extension = file_path.filename().extension().string();
  res = file_path.filename().string();
  res.resize(res.length() -
             extension.length());  // Trim extension of the tar file.
  return (res);
}

void IMerge::remove_directory(const string& directory) {
  try {
    fs::remove_all(directory);
  } catch (exception& ex) {}
}

bool IMerge::extract(const string& file_name) {
  bool ret = false;
  string extracted_dir = m_out_directory + "/" + trim_extension(file_name);

  try {
    fs::path check{file_name};
    ret = fs::exists(check);

    if (ret == false) {
      cout << "ERROR: Requested file '" << file_name << "' doesn't exist."
           << endl;
      return (ret);
    }

    ret = fs::create_directory(
        extracted_dir);  // Create a temp directory to extract files.

    if (ret == false) {
      cout << "WARING: Directory " << quoted(extracted_dir)
           << " already present." << endl;
    }

    string cmd = TAR_CMD + file_name + " -C " + extracted_dir;
    ret = system(cmd.c_str()) != -1 ? true : false;
  } catch (exception& ex) {
    ret = false;
    cout << "ERROR: Exception caught while creating directory "
         << quoted(extracted_dir) << ". Reason, " << quoted(ex.what()) << endl;
  }

  return (ret);
}

void IMerge::collect_files(const std::string& file_name, SORTED_LIST& files) {
  string dir = m_out_directory + "/" + trim_extension(file_name);
  const fs::path fdir{dir};
  // Get list of files from each directory, and if the extension matches, then
  // insert into a list, which will be used later to merge the files.
  for (auto entries : fs::directory_iterator(fdir)) {
    if (entries.path().extension() ==
        m_extension) {  // Match extension. (e.g *.log)
      auto i = files.find(entries.path().filename().string());
      if (i != files.end()) {
        i->second.push_back(entries.path().string());
      } else {
        // the map container will have a list of same name files.
        // e.g: luke.log(file name only) as key, and all luke.log(with full
        // path) files from other directories will be in the list<string>.
        files.insert(pair<string, FILES_LIST>(
            entries.path().filename().string(), {entries.path().string()}));
      }
    }
  }
}
