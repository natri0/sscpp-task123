#include "FileFinder.h"
#include <iostream>

namespace fs = std::filesystem;

static const FileFinder END;
static const fs::recursive_directory_iterator END_ITER;

/** skip all files that don't match the given set of extensions. */
static void skip_non_matching(const std::unordered_set<std::string> &exts, fs::recursive_directory_iterator &iter) {
    do {
        // the entry's path is only empty at the first iteration, when we don't need to advance yet
        if (!iter->path().empty()) ++iter;
        if (iter == END_ITER) return;
    } while (!iter->is_regular_file() || !exts.contains(iter->path().extension()));
}

const std::filesystem::path &FileFinder::operator*() {
    return iter->path();
}

const std::filesystem::path *FileFinder::operator->() {
    return &*(*this);
}

FileFinder &FileFinder::operator++() {
    ++iter;
    skip_non_matching(extensions, iter);
    return *this;
}

FileFinder FileFinder::begin() {
    iter = fs::recursive_directory_iterator(basedir);
    skip_non_matching(extensions, iter);
    return *this;
}

FileFinder FileFinder::end() {
    return END;
}

bool FileFinder::operator!=(const FileFinder &other) const {
    return iter != other.iter;
}
