#ifndef LOG_FILE_MERGE_H_
#define LOG_FILE_MERGE_H_

#include "imerge.hpp"
// Log file merging class. The do_merge is overriden and implemented
// the merging functionality. The FILE_LIST has the list of log files
// to be merged. 
class LogFileMerge : public IMerge {
 public:
  LogFileMerge(FILES_LIST& ar_file_list, const string& out_directory);
  bool do_merge(const string& input_file_name,
                const string& output_file_name) override;
  ~LogFileMerge() {}
};

#define DEFAULT_EXTN_LOG ".log"

#endif // LOG_FILE_MERGE_H_