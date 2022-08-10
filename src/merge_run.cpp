#include <iostream>
#include <cassert>

#include "merge_run.hpp"
#include "logmerge.hpp"

// Merge API. This is the entry point from service function. By default the 
// file type is log file. 
bool merge_files(FILES_LIST& archive_files, const string& target_directory,
                 FILE_TYPE ftype) {
  bool ret = false;
  IMerge* merge = nullptr;

  switch (ftype) {
    case (FILE_TYPE::LOG_TEXT_FILE): {
      merge = new LogFileMerge(archive_files, target_directory);
      assert(merge);
    } break;
    case (FILE_TYPE::LOG_PCAP): {
     // merge = new PCAPMerge(archive_files, target_directory);
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

  delete merge;
  return (ret);
}