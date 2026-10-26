#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../enums/MdUpdateAction.hpp"
#include "../enums/MdEntryType.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

// MassDeleteOrders_MBO_52Message
class MassDeleteOrdersMbO52Message {
  public:
    static constexpr const char* name = "MassDeleteOrdersMbO52Message";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MassDeleteOrdersMbO52Message(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MassDeleteOrdersMbO52Message has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 28;
    static constexpr std::size_t fixed_size = 28;
    std::size_t encoded_size() const { return 28; }

    std::uint64_t security_id() const { return wire::read_u64_le(at(0)); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(8) }; }

    MdUpdateAction md_update_action() const { return static_cast<MdUpdateAction>(wire::read_u8(at(9))); }

    MdEntryType md_entry_type() const { return static_cast<MdEntryType>(wire::read_char(at(10))); }

    std::span<const std::byte, 5> offset_11_padding_5() const { return bytes_.subspan(11).template first<5>(); }

    std::optional<std::uint64_t> transact_time() const { return wire::nullable(wire::read_u64_le(at(16)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<std::uint32_t> rpt_seq() const { return wire::nullable(wire::read_u32_le(at(24)), static_cast<std::uint32_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "MassDeleteOrdersMbO52Message{";
        out << "security_id=";
        out << security_id();
        out << ", match_event_indicator=";
        match_event_indicator().print(out);
        out << ", md_update_action=";
        out << md_update_action();
        out << ", md_entry_type=";
        out << md_entry_type();
        out << ", offset_11_padding_5=";
        print::hex(out, offset_11_padding_5().data(), offset_11_padding_5().size());
        out << ", transact_time=";
        print::optional(out, transact_time());
        out << ", rpt_seq=";
        print::optional(out, rpt_seq());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MassDeleteOrdersMbO52Message& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
