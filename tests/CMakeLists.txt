# Unit tests

TestTarget(ut_dawg_dict
    SOURCES
        ut_dawg_dict.cpp
    LIBRARIES
        worddict
    DEPENDS
        testing
)

TestTarget(ut_word_dict
    SOURCES
        ut_word_dict.cpp
    LIBRARIES
        worddict
    DEPENDS
        testing
)

# Performance tests

