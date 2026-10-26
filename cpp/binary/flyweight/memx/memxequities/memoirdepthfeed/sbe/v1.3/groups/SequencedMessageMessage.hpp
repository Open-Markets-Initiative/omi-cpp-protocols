#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/SbeMessage.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// Message List Element
class SequencedMessageMessage {
  public:
    static constexpr const char* name = "SequencedMessageMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SequencedMessageMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SequencedMessageMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 2;
    std::size_t encoded_size() const { return sbe_message_end(); }

    std::uint16_t message_length() const { return wire::read_u16_be(at(0)); }

    SbeMessage sbe_message() const { return SbeMessage{ bytes_.subspan(2) }; }

    void print(std::ostream& out) const {
        out << "SequencedMessageMessage{";
        out << "message_length=";
        out << message_length();
        out << ", sbe_message=";
        sbe_message().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t sbe_message_end() const { return 2 + sbe_message().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SequencedMessageMessage& value) {
    value.print(out);
    return out;
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
