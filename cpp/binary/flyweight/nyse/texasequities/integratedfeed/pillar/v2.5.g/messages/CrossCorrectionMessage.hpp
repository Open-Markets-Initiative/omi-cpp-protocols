#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

// In the event that an earlier Cross Trade has been reported in error, a Cross Correction
// message is sent.
class CrossCorrectionMessage {
  public:
    static constexpr const char* name = "CrossCorrectionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit CrossCorrectionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every CrossCorrectionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 20;
    static constexpr std::size_t fixed_size = 20;
    std::size_t encoded_size() const { return 20; }

    std::chrono::nanoseconds source_time_ns() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t symbol_index() const { return wire::read_u32_le(at(4)); }

    std::uint32_t symbol_seq_num() const { return wire::read_u32_le(at(8)); }

    std::uint32_t cross_id() const { return wire::read_u32_le(at(12)); }

    std::uint32_t volume() const { return wire::read_u32_le(at(16)); }

    void print(std::ostream& out) const {
        out << "CrossCorrectionMessage{";
        out << "source_time_ns=";
        out << source_time_ns().count();
        out << ", symbol_index=";
        out << symbol_index();
        out << ", symbol_seq_num=";
        out << symbol_seq_num();
        out << ", cross_id=";
        out << cross_id();
        out << ", volume=";
        out << volume();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const CrossCorrectionMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::texasequities::integratedfeed::pillar::v2_5_g
