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

// Published whenever an existing order is deleted from the order book.
class OrderDeleteMessage {
  public:
    static constexpr const char* name = "OrderDeleteMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderDeleteMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderDeleteMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 56;
    static constexpr std::size_t fixed_size = 56;
    std::size_t encoded_size() const { return 56; }

    std::optional<std::chrono::nanoseconds> trd_reg_ts_time_in() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(0)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(8)))); }

    std::int64_t security_id() const { return wire::read_i64_le(at(16)); }

    OrderDetails order_details() const { return OrderDetails{ bytes_.subspan(24) }; }

    void print(std::ostream& out) const {
        out << "OrderDeleteMessage{";
        out << "trd_reg_ts_time_in=";
        print::optional_duration(out, trd_reg_ts_time_in());
        out << ", transact_time=";
        out << transact_time().count();
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

inline std::ostream& operator<<(std::ostream& out, const OrderDeleteMessage& value) {
    value.print(out);
    return out;
}

} // namespace bse::bseindia::eobi::fbe::v1_4
