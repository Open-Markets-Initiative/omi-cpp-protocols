#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Published regularly when there is no activity on the snapshot or the incremental channel.
class HeartbeatMessage {
  public:
    static constexpr const char* name = "HeartbeatMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit HeartbeatMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every HeartbeatMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::uint32_t last_msg_seq_num_processed() const { return wire::read_u32_le(at(0)); }

    std::span<const std::byte, 4> pad_4() const { return bytes_.subspan(4).template first<4>(); }

    void print(std::ostream& out) const {
        out << "HeartbeatMessage{";
        out << "last_msg_seq_num_processed=";
        out << last_msg_seq_num_processed();
        out << ", pad_4=";
        print::hex(out, pad_4().data(), pad_4().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const HeartbeatMessage& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
