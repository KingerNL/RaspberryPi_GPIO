// 2.a logfileoverload
  #include "file.hpp"
  
  class Binfile : public File {
    public:
      Binfile();
      ~Binfile();
    private:
      FILE* pFile_;
  };
