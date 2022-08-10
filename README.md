This is a simple file merging implementation. The input shall be a list of
archive file names (full path) and target output directory. The current 
implemenation supports merging of text log files, however it can be extended 
to support other file types as well.

 - Compiled and tested in Linux platform.
 - Used C++17 as the compiler.
 - Using 'tar -xf' command to unpack the files.

Please refer to 'main.cpp' to see example code to demonstrate the functionality.

Example:

    string target = "/var/log/result";
    FILES_LIST ar_list = {"/var/log/systemlog/3108-01-31.tgz",
                          "/var/log/systemlog/3108-01-30.tgz",
                         };
    bool ret = merge_files(ar_list, target);
    
