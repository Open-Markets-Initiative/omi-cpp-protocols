#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../groups/SequencedMessageMessage.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// Sequenced Message
class SequencedMessage {
  public:
    static constexpr const char* name = "SequencedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SequencedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SequencedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 2;
    std::size_t encoded_size() const { return message_end(); }

    std::uint16_t message_count() const { return wire::read_u16_be(at(0)); }

    view::entries<SequencedMessageMessage> message() const { return view::entries<SequencedMessageMessage>{ bytes_.subspan(2), wire::count(message_count()) }; }

    void print(std::ostream& out) const {
        out << "SequencedMessage{";
        out << "message_count=";
        out << message_count();
        out << ", message=";
        print::sequence(out, message());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t message_end() const { return 2 + message().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SequencedMessage& value) {
    value.print(out);
    return out;
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
