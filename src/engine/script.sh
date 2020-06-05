for file in *.h
do
  mv "$file" "${file%.h}.hpp"
done

for dir in ./*/     # list directories in the form "/tmp/dirname/"
do
    dir=${dir%*/}      # remove the trailing "/"
    echo ${dir##*/}    # print everything after the final "/"
done
