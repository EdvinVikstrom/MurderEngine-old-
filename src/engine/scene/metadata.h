#ifndef METADATA_H
  #define METADATA_H

#include <string>
#include <map>

namespace me {

  struct metadata {

    std::map<std::string, std::string> tags;

    inline std::string getTag(std::string key)
    {
      if (!tags.count(key))
        return "";
      return tags[key];
    }

    inline void putTag(std::string key, std::string value)
    {
      tags[key] = value;
    }

  };

};

#endif
