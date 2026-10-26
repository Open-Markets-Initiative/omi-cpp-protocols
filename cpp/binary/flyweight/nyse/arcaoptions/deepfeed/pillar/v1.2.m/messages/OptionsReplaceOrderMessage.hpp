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

// Published when a cancel/replace order is received. The resting order is replaced with a new
// order containing the same outright or complex series, side and attribution, a new Order ID,
// and the price and size specified.
class OptionsReplaceOrderMessage {
  public:
    static constexpr const char* name = "OptionsReplaceOrderMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OptionsReplaceOrderMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OptionsReplaceOrderMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 39;
    static constexpr std::size_t fixed_size = 39;
    std::size_t encoded_size() const { return 39; }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(0)); }

    std::uint32_t series_index() const { return wire::read_u32_le(at(4)); }

    std::uint32_t series_seq_num() const { return wire::read_u32_le(at(8)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(12)); }

    std::uint64_t new_order_id() const { return wire::read_u64_le(at(20)); }

    std::int32_t price() const { return wire::read_i32_le(at(28)); }

    std::uint32_t volume() const { return wire::read_u32_le(at(32)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(36))); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(37).template first<1>(); }

    CustIndicator cust_indicator() const { return static_cast<CustIndicator>(wire::read_char(at(38))); }

    void print(std::ostream& out) const {
        out << "OptionsReplaceOrderMessage{";
        out << "source_time_ns=";
        out << source_time_ns();
        out << ", series_index=";
        out << series_index();
        out << ", series_seq_num=";
        out << series_seq_num();
        out << ", order_id=";
        out << order_id();
        out << ", new_order_id=";
        out << new_order_id();
        out << ", price=";
        out << price();
        out << ", volume=";
        out << volume();
        out << ", side=";
        out << side();
        out << ", reserved_1=";
        print::hex(out, reserved_1().data(), reserved_1().size());
        out << ", cust_indicator=";
        out << cust_indicator();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OptionsReplaceOrderMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
