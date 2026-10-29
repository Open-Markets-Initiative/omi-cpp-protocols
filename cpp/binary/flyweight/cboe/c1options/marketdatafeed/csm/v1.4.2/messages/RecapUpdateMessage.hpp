#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/PrevClosePx.hpp"
#include "../groups/RecapUpdateMdEntry.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// The Recap Update message contains the latest Last Sale price, Last Sale size, Total Volume,
// Open price, High price, Low price, and Previous close price. It is sent as a result of a
// trade or cancel.
class RecapUpdateMessage {
  public:
    static constexpr const char* name = "RecapUpdateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RecapUpdateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RecapUpdateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 19;
    std::size_t encoded_size() const { return recap_update_md_entry_end(); }

    std::uint32_t class_key() const { return wire::read_u32_be(at(0)); }

    std::uint32_t security_id() const { return wire::read_u32_be(at(4)); }

    std::uint8_t price_type() const { return wire::read_u8(at(8)); }

    PrevClosePx prev_close_px() const { return PrevClosePx{ bytes_.subspan(9) }; }

    std::uint32_t trade_volume() const { return wire::read_u32_be(at(14)); }

    std::uint8_t no_entries() const { return wire::read_u8(at(18)); }

    view::entries<RecapUpdateMdEntry> recap_update_md_entry() const { return view::entries<RecapUpdateMdEntry>{ bytes_.subspan(19), wire::count(no_entries()) }; }

    void print(std::ostream& out) const {
        out << "RecapUpdateMessage{";
        out << "class_key=";
        out << class_key();
        out << ", security_id=";
        out << security_id();
        out << ", price_type=";
        out << static_cast<int>(price_type());
        out << ", prev_close_px=";
        prev_close_px().print(out);
        out << ", trade_volume=";
        out << trade_volume();
        out << ", no_entries=";
        out << static_cast<int>(no_entries());
        out << ", recap_update_md_entry=";
        print::sequence(out, recap_update_md_entry());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t recap_update_md_entry_end() const { return 19 + recap_update_md_entry().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RecapUpdateMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
