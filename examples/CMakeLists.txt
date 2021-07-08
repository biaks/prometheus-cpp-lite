
add_executable       (original_example               "original_example.cpp" )
target_link_libraries(original_example               prometheus-cpp-lite-core)

add_executable       (modern_example                 "modern_example.cpp" )
target_link_libraries(modern_example                 prometheus-cpp-lite-core)

add_executable       (use_counters_in_class_example  "use_counters_in_class_example.cpp" )
target_link_libraries(use_counters_in_class_example  prometheus-cpp-lite-core)

add_executable       (use_gauge_in_class_example     "use_gauge_in_class_example.cpp" )
target_link_libraries(use_gauge_in_class_example     prometheus-cpp-lite-core)

add_executable       (use_benchmark_in_class_example "use_benchmark_in_class_example.cpp" )
target_link_libraries(use_benchmark_in_class_example prometheus-cpp-lite-core)

add_executable       (save_to_file_example           "save_to_file_example.cpp" )
target_link_libraries(save_to_file_example           prometheus-cpp-lite-core)


add_executable       (simpleapi_example              "simpleapi_use_in_class_example.cpp")
target_link_libraries(simpleapi_example              prometheus-cpp-simpleapi)
