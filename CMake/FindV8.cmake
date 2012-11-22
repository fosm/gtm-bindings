
find_path(V8_INCLUDE_DIR  v8.h
  PATHS
    /usr/include
  )

find_file(V8_LIBRARY NAMES libv8.so
  PATHS
    /usr/lib/
  )
