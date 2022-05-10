// 2.a logfileoverload
  #include "file.hpp"
  
  class : Logfile {
    public:
        Logfile();
        ~Logfile();
        bool open(const char* sFilename);
        bool close();
        void write(int nValue);
        void write(char* pBuf);
        void operator>>(char* pBuf);

    private:
      FILE* pFile_;
  };
