#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/OrderDetails.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Published for each new order that was entered in the order book.
class OrderAddMessage {
  public:
    static constexpr const char* name = "OrderAddMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderAddMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderAddMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 48;
    static constexpr std::size_t fixed_size = 48;
    std::size_t encoded_size() const { return 48; }

    std::optional<std::chrono::nanoseconds> trd_reg_ts_time_in() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(0)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::int64_t security_id() const { return wire::read_i64_le(at(8)); }

    OrderDetails order_details() const { return OrderDetails{ bytes_.subspan(16) }; }

    void print(std::ostream& out) const {
        out << "OrderAddMessage{";
        out << "trd_reg_ts_time_in=";
        print::optional_duration(out, trd_reg_ts_time_in());
        out << ", security_id=";
        out << security_id();
        out << ", order_details=";
        order_details().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderAddMessage& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
