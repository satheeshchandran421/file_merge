#include <iostream>
#include <cassert>
#include <memory>

#include "merge_run.hpp"
#include "logmerge.hpp"

// Merge API. This is the entry point from service function. By default the 
// file type is log file. 
bool merge_files(FILES_LIST& archive_files, const string& target_directory,
                 FILE_TYPE ftype) {
  bool ret = false;
  std::unique_ptr<IMerge> merge;
 
  switch (ftype) {
    case (FILE_TYPE::LOG_TEXT_FILE): {
      merge = std::make_unique<LogFileMerge>(archive_files, target_directory);
    } break;
    case (FILE_TYPE::LOG_PCAP): {
     // merge = std::make_unique<PCAPMerge>(archive_files, target_directory);
    } break;
    default:
      assert(0);
      break;
  }

  if (merge) {
    ret = merge->execute();
    if (ret == true) {
      cout << "SUCCESS: Merged requested files. " << endl;
    } else {
      cout << "ERROR: Error while merging files. " << endl;
    }
  }

  return (ret);
}