#ifndef XMP_FORMAT_H
  #define XMP_FORMAT_H

namespace me {

  namespace parser {

    struct xmp_parser {

      static void parse_xmp(const std::string &source, me::MarkupLang &lang);

    };

  };

};

#endif
