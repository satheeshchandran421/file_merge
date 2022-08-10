#ifndef MERGE_RUN_H_
#define MERGE_RUN_H_

#include "imerge.hpp"

bool merge_files(FILES_LIST& archive_files, const string& target_directory,
                 FILE_TYPE ftype = FILE_TYPE::LOG_TEXT_FILE);

#endif  // MERGE_RUN_H_