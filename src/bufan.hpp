// Copyright 2021 bufan

#ifndef SRC_CPP_BUFAN_HPP_
#define SRC_CPP_BUFAN_HPP_

#include "disk.hpp"
#include "util.hpp"



void*  RunBufan(const int i,
     const std::string &tmp2_dirname /*filename*/,
    const std::string &tmp_dirname,
    const std::string &filename
    )
{

     fs::path tmp_2_filename = fs::path(tmp2_dirname) / fs::path(filename + ".table" + std::to_string(i) + ".tmp");
        fs::path tmp_filename = fs::path(tmp_dirname) / fs::path(filename + ".table" + std::to_string(i) + ".tmp");

       if (tmp_2_filename.parent_path() != tmp_filename.parent_path()) {
     Timer copy;
    std::cout << "\tbufan gogo:" << std::endl ;
      bool  bRenameda=false;
            std::error_code ec;
            std::uintmax_t size =  fs::file_size(tmp_filename,ec); 
            std::cout << i << " before size  = " << size << '\n';
             if (fs::exists(tmp_2_filename) || fs::is_symlink(tmp_2_filename)) {
                                  fs::remove(tmp_2_filename);
                }
        do {
                          if (!bRenameda) {
               
             
                   
                    fs::rename(tmp_filename, tmp_2_filename, ec);
         
                        if (ec.value() != 0) {
                            std::cout << " Error "  << i 
                                << ". Retrying in 18s." << std::endl;
                        }else{
                            bRenameda = true;
                              std::uintmax_t size =  fs::file_size(tmp_2_filename,ec); 
                           std::cout << i << " end size  = " << size << '\n';
                            copy.PrintElapsed("time =");
                        
                        //std::string av= std::to_string(i);
 //char s[30000];
//sprintf_s(s, "%s%s%s%s%s%s%s%s%s%s%s%s%s", "mklink  \"",tmp_dirname.data(),"/",filename.data(),".table",av.data(),".tmp\" \" ",tmp2_dirname.data(),"/",filename.c_str(),".table",av.data(),".tmp\" >> 22.txt");
//std::cout << s << std::endl;

//system(s);
                            fs::create_symlink(tmp_2_filename, tmp_filename);
  //System：执行系统的命令行

                        }
#ifdef _WIN32
                        std::cout << "wait bufan 280s " << i << std::endl;
                        Sleep( 28 * 10000);
#else
                        sleep(28 * 10);
#endif
                        }
                        
                    } while (!bRenameda);
       }
  return 0;
        
}
#endif  // SRC_CPP_BUFAN_HPP
