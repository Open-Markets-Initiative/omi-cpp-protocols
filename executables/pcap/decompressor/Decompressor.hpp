#pragma once

#include <cstddef>

namespace packet {

// Abstract Decompressor — reads decompressed bytes from a source
struct Decompressor {
    virtual ~Decompressor() = default;
    virtual std::size_t read(void* buf, std::size_t len) = 0;
    virtual bool eof() const = 0;
};

} // namespace packet