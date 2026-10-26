#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Side.hpp"
#include "../enums/CustIndicator.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Sent when the price or volume of an order is changed due to an event other than a
// cancel-replace, or full or partial execution.
class OptionsModifyOrderMessage {
  public:
    static constexpr const char* name = "OptionsModifyOrderMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OptionsModifyOrderMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OptionsModifyOrderMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 31;
    static constexpr std::size_t fixed_size = 31;
    std::size_t encoded_size() const { return 31; }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(0)); }

    std::uint32_t series_index() const { return wire::read_u32_le(at(4)); }

    std::uint32_t series_seq_num() const { return wire::read_u32_le(at(8)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(12)); }

    std::int32_t price() const { return wire::read_i32_le(at(20)); }

    std::uint32_t volume() const { return wire::read_u32_le(at(24)); }

    std::uint8_t position_change() const { return wire::read_u8(at(28)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(29))); }

    CustIndicator cust_indicator() const { return static_cast<CustIndicator>(wire::read_char(at(30))); }

    void print(std::ostream& out) const {
        out << "OptionsModifyOrderMessage{";
        out << "source_time_ns=";
        out << source_time_ns();
        out << ", series_index=";
        out << series_index();
        out << ", series_seq_num=";
        out << series_seq_num();
        out << ", order_id=";
        out << order_id();
        out << ", price=";
        out << price();
        out << ", volume=";
        out << volume();
        out << ", position_change=";
        out << static_cast<int>(position_change());
        out << ", side=";
        out << side();
        out << ", cust_indicator=";
        out << cust_indicator();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OptionsModifyOrderMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
