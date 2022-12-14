#ifndef MERGE_INTERFACE_H_
#define MERGE_INTERFACE_H_

#include <list>
#include <unordered_map>
#include <string>

enum class FILE_TYPE { LOG_TEXT_FILE = 0, LOG_PCAP };
using namespace std;
using FILES_LIST = list<string>;
using SORTED_LIST = list<string>;
constexpr char TAR_CMD[] = "tar -xf ";
// Interface class for merging functionality. The function do_merge()
// has to be overriden in the child class and has to implement the logic.
class IMerge {
 public:
  IMerge(FILES_LIST& list, const string& out_dir, const string& extn)
      : m_tarfiles(list),
        m_out_directory(out_dir),
        m_extension(extn) {}
  virtual bool do_merge(const string& input_file_name,
                        const string& output_file_name) = 0;
  bool execute();
  bool is_in_range(const time_t logtime);
  bool is_in_range(const string& str_time);
  virtual ~IMerge() {}
 private:
  IMerge() {}
  bool prepare(const string& tar_file, SORTED_LIST& files);
  bool run(SORTED_LIST& sorted_files);
  void post();
  void remove_directory(const string& dir);
  void collect_files(SORTED_LIST& sorted_files);
  bool extract(const string& fname);
  void create_temp_directory_name();
  string get_temp_directory();
  FILES_LIST m_tarfiles;
  std::string m_out_directory;
  std::string m_extension;
  std::string m_exdir;
};

inline bool IMerge::is_in_range(const time_t tm) { 
  // TODO: time range check will be here.
  return true; }

inline bool IMerge::is_in_range(const string& str_time) {
  // TODO: time range check will be here.
  return true;
}

inline string IMerge::get_temp_directory() {
  return m_exdir;
}

#endif  // MERGE_INTERFACE_H_