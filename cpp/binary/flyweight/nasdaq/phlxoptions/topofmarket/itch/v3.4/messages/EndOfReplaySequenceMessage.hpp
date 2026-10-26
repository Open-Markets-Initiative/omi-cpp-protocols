#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// The End of replay Sequence message reflects the sequence number at the time replay of
// existing messages is complete. The firms can then use this sequence number to resume on the
// real time Mold channel. Only for SoupBINTCP.
class EndOfReplaySequenceMessage {
  public:
    static constexpr const char* name = "EndOfReplaySequenceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit EndOfReplaySequenceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every EndOfReplaySequenceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 20;
    static constexpr std::size_t fixed_size = 20;
    std::size_t encoded_size() const { return 20; }

    std::string_view end_of_replay_sequence_number() const { return view::text(at(0), 20, ' '); }

    void print(std::ostream& out) const {
        out << "EndOfReplaySequenceMessage{";
        out << "end_of_replay_sequence_number=";
        print::text(out, end_of_replay_sequence_number());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const EndOfReplaySequenceMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
