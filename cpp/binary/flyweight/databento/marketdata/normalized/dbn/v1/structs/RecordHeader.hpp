// Databento.MarketData.Normalized.Dbn.v1: structs/RecordHeader.hpp
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
#include "../enums/Rtype.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

// DBN common header of every record
class RecordHeader {
  public:
    static constexpr const char* name = "RecordHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit RecordHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every RecordHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::uint8_t record_length() const { return wire::read_u8(at(0)); }

    Rtype rtype() const { return static_cast<Rtype>(wire::read_u8(at(1))); }

    std::uint16_t publisher_id() const { return wire::read_u16_le(at(2)); }

    std::uint32_t instrument_id() const { return wire::read_u32_le(at(4)); }

    std::optional<std::chrono::nanoseconds> ts_event() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(8)), static_cast<std::uint64_t>(18446744073709551615ULL)); }

    void print(std::ostream& out) const {
        out << "RecordHeader{";
        out << "record_length=";
        out << static_cast<int>(record_length());
        out << ", rtype=";
        out << rtype();
        out << ", publisher_id=";
        out << publisher_id();
        out << ", instrument_id=";
        out << instrument_id();
        out << ", ts_event=";
        print::optional_duration(out, ts_event());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const RecordHeader& value) {
    value.print(out);
    return out;
}

} // namespace databento::marketdata::normalized::dbn::v1
