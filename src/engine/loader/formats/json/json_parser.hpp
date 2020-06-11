#ifndef JSON_PARSER_H
  #define JSON_PARSER_H

namespace me {

  namespace parser {

    struct json_tree {

      std::map<std::string, json_tree> trees;
      std::map<std::string, srd::string> values;

    };

    struct json_parser {

      int parse_json(me::fileattr &file, json_tree* tree);

    };

  };

};

#endif