#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nyse::arcaequities::bbo::xdp::v2_4_c {

// This message is sent at the start of every second during periods of active data publication.
class SourceTimeReferenceMessage {
  public:
    static constexpr const char* name = "SourceTimeReferenceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SourceTimeReferenceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SourceTimeReferenceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 12;
    static constexpr std::size_t fixed_size = 12;
    std::size_t encoded_size() const { return 12; }

    std::uint32_t id() const { return wire::read_u32_le(at(0)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(4)); }

    std::uint32_t source_time() const { return wire::read_u32_le(at(8)); }

    void print(std::ostream& out) const {
        out << "SourceTimeReferenceMessage{";
        out << "id=";
        out << id();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
        out << ", source_time=";
        out << source_time();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SourceTimeReferenceMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaequities::bbo::xdp::v2_4_c
