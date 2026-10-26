#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/FinancialProduct.hpp"
#include "../enums/PutOrCall.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Disseminated for all active securities at start of day or intra-day.
class OrderBookDirectory {
  public:
    static constexpr const char* name = "OrderBookDirectory";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderBookDirectory(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderBookDirectory has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 128;
    static constexpr std::size_t fixed_size = 128;
    std::size_t encoded_size() const { return 128; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint32_t order_book_id() const { return wire::read_u32_be(at(4)); }

    std::string_view symbol() const { return view::text(at(8), 32, ' '); }

    std::string_view long_name() const { return view::text(at(40), 32, ' '); }

    std::string_view isin() const { return view::text(at(72), 12, ' '); }

    FinancialProduct financial_product() const { return static_cast<FinancialProduct>(wire::read_u8(at(84))); }

    std::string_view trading_currency() const { return view::text(at(85), 3, ' '); }

    std::uint16_t decimals_in_price() const { return wire::read_u16_be(at(88)); }

    std::uint16_t decimals_in_nominal_value() const { return wire::read_u16_be(at(90)); }

    std::uint32_t odd_lot_size() const { return wire::read_u32_be(at(92)); }

    std::uint32_t round_lot_size() const { return wire::read_u32_be(at(96)); }

    std::uint32_t block_lot_size() const { return wire::read_u32_be(at(100)); }

    std::uint64_t nominal_value() const { return wire::read_u64_be(at(104)); }

    std::uint8_t number_of_legs() const { return wire::read_u8(at(112)); }

    std::uint32_t underlying_orderbook_id() const { return wire::read_u32_be(at(113)); }

    std::int32_t strike_price() const { return wire::read_i32_be(at(117)); }

    std::uint32_t expiration_date() const { return wire::read_u32_be(at(121)); }

    std::uint16_t decimals_in_strike_price() const { return wire::read_u16_be(at(125)); }

    PutOrCall put_or_call() const { return static_cast<PutOrCall>(wire::read_u8(at(127))); }

    void print(std::ostream& out) const {
        out << "OrderBookDirectory{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", order_book_id=";
        out << order_book_id();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", long_name=";
        print::text(out, long_name());
        out << ", isin=";
        print::text(out, isin());
        out << ", financial_product=";
        out << financial_product();
        out << ", trading_currency=";
        print::text(out, trading_currency());
        out << ", decimals_in_price=";
        out << decimals_in_price();
        out << ", decimals_in_nominal_value=";
        out << decimals_in_nominal_value();
        out << ", odd_lot_size=";
        out << odd_lot_size();
        out << ", round_lot_size=";
        out << round_lot_size();
        out << ", block_lot_size=";
        out << block_lot_size();
        out << ", nominal_value=";
        out << nominal_value();
        out << ", number_of_legs=";
        out << static_cast<int>(number_of_legs());
        out << ", underlying_orderbook_id=";
        out << underlying_orderbook_id();
        out << ", strike_price=";
        out << strike_price();
        out << ", expiration_date=";
        out << expiration_date();
        out << ", decimals_in_strike_price=";
        out << decimals_in_strike_price();
        out << ", put_or_call=";
        out << put_or_call();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderBookDirectory& value) {
    value.print(out);
    return out;
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
