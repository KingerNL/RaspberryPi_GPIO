// 2.b logfileextends

#ifndef _FILE_HPP_
#define _FILE_HPP_

  #include <stdbool.h>
  #include <stdio.h>

  class File {
    public:
      File();
      ~File();
      virtual bool open(const char* sFilename) = 0;
      virtual bool close() = 0;
      virtual void write(int nValue) = 0;
      virtual void write(char* pBuf) = 0;
      virtual void operator>>(char* pBuf) = 0;

    private:
  };

#endif // _FILE_HPP_