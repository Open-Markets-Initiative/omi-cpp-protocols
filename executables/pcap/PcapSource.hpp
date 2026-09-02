#pragma once

#include <cstddef>
#include <cstdint>

namespace packet {

// Abstract packet source — anything that produces packets in time order
struct PcapSource {
    virtual ~PcapSource() = default;
    virtual bool advance() = 0;
    virtual std::uint64_t timestamp_ns() const = 0;
    virtual const std::byte* data() const = 0;
    virtual std::uint32_t length() const = 0;
    virtual bool done() const = 0;
};

} // namespace packet