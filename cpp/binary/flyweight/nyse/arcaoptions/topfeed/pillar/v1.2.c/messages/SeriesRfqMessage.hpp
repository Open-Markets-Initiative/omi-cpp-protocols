#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Side.hpp"
#include "../enums/Type.hpp"
#include "../enums/Capacity.hpp"
#include "../enums/RfqStatus.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// The Request for Series RFQ message is published for outright series.
class SeriesRfqMessage {
  public:
    static constexpr const char* name = "SeriesRfqMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SeriesRfqMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SeriesRfqMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 40;
    static constexpr std::size_t fixed_size = 40;
    std::size_t encoded_size() const { return 40; }

    std::uint32_t source_time() const { return wire::read_u32_le(at(0)); }

    std::uint32_t source_time_ns() const { return wire::read_u32_le(at(4)); }

    std::uint32_t series_index() const { return wire::read_u32_le(at(8)); }

    std::uint32_t series_seq_num() const { return wire::read_u32_le(at(12)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(16))); }

    Type type_field() const { return static_cast<Type>(wire::read_char(at(17))); }

    Capacity capacity() const { return static_cast<Capacity>(wire::read_char(at(18))); }

    std::uint32_t total_quantity() const { return wire::read_u32_le(at(19)); }

    std::int32_t working_price() const { return wire::read_i32_le(at(23)); }

    std::uint32_t participant() const { return wire::read_u32_le(at(27)); }

    std::uint64_t auction_id() const { return wire::read_u64_le(at(31)); }

    RfqStatus rfq_status() const { return static_cast<RfqStatus>(wire::read_char(at(39))); }

    void print(std::ostream& out) const {
        out << "SeriesRfqMessage{";
        out << "source_time=";
        out << source_time();
        out << ", source_time_ns=";
        out << source_time_ns();
        out << ", series_index=";
        out << series_index();
        out << ", series_seq_num=";
        out << series_seq_num();
        out << ", side=";
        out << side();
        out << ", type_field=";
        out << type_field();
        out << ", capacity=";
        out << capacity();
        out << ", total_quantity=";
        out << total_quantity();
        out << ", working_price=";
        out << working_price();
        out << ", participant=";
        out << participant();
        out << ", auction_id=";
        out << auction_id();
        out << ", rfq_status=";
        out << rfq_status();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SeriesRfqMessage& value) {
    value.print(out);
    return out;
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
