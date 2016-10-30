file(REMOVE_RECURSE
  "libclibraries.pdb"
  "libclibraries.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/clibraries.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
