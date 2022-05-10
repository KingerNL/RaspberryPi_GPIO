// 1.c cpplogfile

#ifndef _LOGFILE_HPP_
#define _LOGFILE_HPP_

  #include <stdbool.h>
  #include <stdio.h>

  class Logfile {
    public:
        //TODO #1: voeg de logfile 'interface' toe
        bool open(const char* sFilename);
        bool close();
        void write(char* pBuf);
        void read(char* pBuf);

    private:
      FILE* pFile_;
  };

#endif // _LOGFILE_HPP_wx