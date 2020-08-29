py_ffi(
    MODULE ${CMAKE_CURRENT_LIST_DIR}/JSONStats.py
    FN json_stats
    OUTPUT JSON_STATS
    INPUTS "{\"a\": 1, \"b\": {}, \"c\": true}"
)

message(STATUS "Number of keys = ${JSON_STATS}")