#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Side.hpp"
#include "../enums/CustIndicator.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Published when a new visible order has been received and added to the book.
class OptionsAddOrderMessage {
  public:
    static constexpr const char* name = "OptionsAddOrderMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OptionsAddOrderMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OptionsAddOrderMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 36;
    static constexpr std::size_t fixed_size = 36;
    std::size_t encoded_size() const { return 36; }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(0)); }

    std::uint32_t series_index() const { return wire::read_u32_le(at(4)); }

    std::uint32_t series_seq_num() const { return wire::read_u32_le(at(8)); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(12)); }

    std::int32_t price() const { return wire::read_i32_le(at(20)); }

    std::uint32_t volume() const { return wire::read_u32_le(at(24)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(28))); }

    std::string_view firm_id() const { return view::text(at(29), 5, ' '); }

    std::span<const std::byte, 1> reserved_1() const { return bytes_.subspan(34).template first<1>(); }

    CustIndicator cust_indicator() const { return static_cast<CustIndicator>(wire::read_char(at(35))); }

    void print(std::ostream& out) const {
        out << "OptionsAddOrderMessage{";
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
        out << ", side=";
        out << side();
        out << ", firm_id=";
        print::text(out, firm_id());
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

inline std::ostream& operator<<(std::ostream& out, const OptionsAddOrderMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
