// Memx.MemxEquities.MemoirDepthFeed.Sbe.v1.3: structs/Frame.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/SbeHeader.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// Message List Element
class Frame {
  public:
    static constexpr const char* name = "Frame";

    // the bytes it reads, which it does not own: they must outlive it
    explicit Frame(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every Frame has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::uint16_t message_length() const { return wire::read_u16_be(at(0)); }

    SbeHeader sbe_header() const { return SbeHeader{ bytes_.subspan(2) }; }

    void print(std::ostream& out) const {
        out << "Frame{";
        out << "message_length=";
        out << message_length();
        out << ", sbe_header=";
        sbe_header().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const Frame& value) {
    value.print(out);
    return out;
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
