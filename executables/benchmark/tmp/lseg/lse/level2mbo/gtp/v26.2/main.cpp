// Lseg.Lse.Level2Mbo.Gtp.v26.2: main.cpp
// Lseg.Lse.Level2Mbo.Gtp.v26.2 benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/lseg/lse/level2mbo/gtp/v26.2.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "executables/benchmark/Benchmark.hpp"
#include "cpp/binary/tmp/lseg/lse/level2mbo/gtp/v26.2/lseg_lse_level2mbo_gtp_v26_2.hpp"

// Lseg Lse Level2Mbo Gtp 26.2: the reading of its packets, through its Template Meta Programming header
namespace lseg::lse::level2mbo::gtp::v26_2 {

/////////////////////////////////////////////////////////////////////
// Reading
/////////////////////////////////////////////////////////////////////

namespace tmp {
    // Thrown when the bytes end before what they must hold
    struct short_read : std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    inline void require(std::size_t needed, std::size_t available) {
        if (needed > available) {
            throw short_read(std::to_string(needed) + " bytes needed, " + std::to_string(available) + " available");
        }
    }

    // The bytes left for a member when the members after it take some: refused when fewer remain
    inline std::size_t leaving(std::size_t available, std::size_t taken) {
        require(taken, available);
        return available - taken;
    }

    // Hand the handler a value, when it takes one
    template <typename Handler, typename T>
    constexpr void call(Handler& handler, const T& value) {
        if constexpr (requires { handler(value); }) { handler(value); }
    }

    // A type laid over its bytes, handed to the handler
    template <typename T, typename Handler>
    const T& read(const std::byte* data, std::size_t length, Handler& handler) {
        require(T::size, length);
        const auto& value = *reinterpret_cast<const T*>(data);
        call(handler, value);
        return value;
    }

    // A field as a rule reads it: an enum by the code the wire holds, a field by its value, and a
    // bit - which its bitfield answers as a value - as it is
    template <typename T>
    constexpr auto rule(const T& field) noexcept {
        if constexpr (requires { field.raw(); }) { return field.raw(); }
        else if constexpr (requires { field.value(); }) { return field.value(); }
        else { return field; }
    }

    // A field an optional member may hold, read as its type's zero when the member is absent
    template <typename T>
    struct maybe {
        const T* field;

        constexpr auto value() const noexcept {
            using type = decltype(field->value());
            return field != nullptr ? field->value() : type{};
        }

        constexpr auto raw() const noexcept requires requires(const T& held) { held.raw(); } {
            using type = decltype(field->raw());
            return field != nullptr ? field->raw() : type{};
        }

        // a bit of an optional bitfield, nothing when the bitfield is absent
        template <typename Bit>
        constexpr auto get() const noexcept requires requires(const T& held) { held.template get<Bit>(); } {
            using type = std::remove_cvref_t<decltype(field->template get<Bit>())>;
            return field != nullptr ? type{ field->template get<Bit>() } : type{};
        }
    };

    // A type laid over its bytes without handing it on: a frame's length, read before the frame is
    template <typename T>
    const T& at(const std::byte* data) noexcept {
        return *reinterpret_cast<const T*>(data);
    }

    // A type laid over bytes ahead of the walk, at a place every byte before it fixes, which a rule
    // reads before the walk reaches it: a branch's code in the header its messages begin with
    template <typename T>
    const T& ahead(const std::byte* data, std::size_t length, std::size_t at) {
        require(at + T::size, length);
        return *reinterpret_cast<const T*>(data + at);
    }

    // A type laid over its bytes and handed to the handler; what it returns is the bytes it took
    template <typename T, typename Handler>
    std::size_t take(const std::byte* data, std::size_t length, Handler& handler) {
        read<T>(data, length, handler);
        return T::size;
    }

    // The characters before a terminating zero, which the bytes must hold
    inline std::size_t terminated(const std::byte* data, std::size_t length) {
        for (std::size_t index = 0; index < length; ++index) {
            if (data[index] == std::byte{ 0 }) { return index; }
        }
        throw short_read("no terminator in " + std::to_string(length) + " bytes");
    }

    // The bytes before the first of a field's delimiters, which it leaves for what follows it; at
    // most its maximum, and the bytes must hold a delimiter when they are shorter than that
    template <std::size_t Count>
    std::size_t delimited(const std::byte* data, std::size_t length, std::size_t maximum, const std::array<std::byte, Count>& delimiters) {
        const std::size_t limit = std::min(maximum, length);
        for (std::size_t index = 0; index < limit; ++index) {
            for (const std::byte delimiter : delimiters) {
                if (data[index] == delimiter) { return index; }
            }
        }
        if (limit < length) { return limit; }
        throw short_read("no delimiter in " + std::to_string(length) + " bytes");
    }

    // The bytes of a frame ending on a terminator, the terminator included; none while the bytes
    // do not hold it yet
    inline std::size_t through(const std::byte* data, std::size_t length, std::byte terminator) noexcept {
        for (std::size_t index = 0; index < length; ++index) {
            if (data[index] == terminator) { return index + 1; }
        }
        return 0;
    }

    // Bytes a branch's code selects no message for, handed to the handler when it takes them
    template <typename Handler>
    void unknown(Handler& handler, const std::byte* data, std::size_t length) {
        if constexpr (requires { handler.unknown(data, length); }) { handler.unknown(data, length); }
    }

    // How many a count or a length states: a number, or digits of text
    template <typename T>
        requires std::is_integral_v<T>
    constexpr std::size_t count(T value) noexcept { return static_cast<std::size_t>(value); }

    inline std::size_t count(char digit) {
        if (digit < '0' || digit > '9') { throw short_read(std::string("'") + digit + "' is not a digit"); }
        return static_cast<std::size_t>(digit - '0');
    }

    inline std::size_t count(std::string_view digits) {
        std::size_t value = 0;
        for (const char digit : digits) {
            if (digit == ' ') { continue; }
            if (digit < '0' || digit > '9') { throw short_read("\"" + std::string(digits) + "\" is not a number"); }
            value = value * 10 + static_cast<std::size_t>(digit - '0');
        }
        return value;
    }
} // namespace tmp

/////////////////////////////////////////////////////////////////////
// Parsing
/////////////////////////////////////////////////////////////////////

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_type& message_type_) {
    if (static_cast<bool>(tmp::rule(message_type_) == 0x53)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& system_event_message_ = tmp::read<system_event_message>(data + offset, bound - offset, handler); offset += system_event_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x70)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& instrument_directory_message_ = tmp::read<instrument_directory_message>(data + offset, bound - offset, handler); offset += instrument_directory_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x48)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& instrument_status_message_ = tmp::read<instrument_status_message>(data + offset, bound - offset, handler); offset += instrument_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x41)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_mbo_message_ = tmp::read<add_order_mbo_message>(data + offset, bound - offset, handler); offset += add_order_mbo_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x65)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_short_mbo_message_ = tmp::read<add_order_short_mbo_message>(data + offset, bound - offset, handler); offset += add_order_short_mbo_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x79)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_book_clear_message_ = tmp::read<order_book_clear_message>(data + offset, bound - offset, handler); offset += order_book_clear_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x50)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_message_ = tmp::read<trade_message>(data + offset, bound - offset, handler); offset += trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x77)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& statistics_message_ = tmp::read<statistics_message>(data + offset, bound - offset, handler); offset += statistics_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x6A)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& statistics_update_message_ = tmp::read<statistics_update_message>(data + offset, bound - offset, handler); offset += statistics_update_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& message_header_ = tmp::read<message_header>(data + offset, bound - offset, handler); offset += message_header::size;
    bound = static_cast<std::size_t>(tmp::rule(message_header_.template get<message_length>()));
    tmp::require(bound, length);
    offset += parse_payload(data + offset, bound - offset, handler, message_header_.template get<message_type>());
    return bound;
}

// Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& unit_header_ = tmp::read<unit_header>(data + offset, bound - offset, handler); offset += unit_header::size;
    {
        const std::size_t end = static_cast<std::size_t>(static_cast<std::int64_t>(bound));
        tmp::require(end, bound);
        while (offset < end) {
            [[maybe_unused]] const std::size_t bound = end;
            offset += parse_message(data + offset, bound - offset, handler);
        }
    }
    return offset;
}


} // namespace lseg::lse::level2mbo::gtp::v26_2

namespace protocol = ::lseg::lse::level2mbo::gtp::v26_2;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::unit_header& header) {
        if constexpr (requires { header.template get<protocol::length_type>(); }) { checksum += bench::digest(header.template get<protocol::length_type>().value()); }
        if constexpr (requires { header.template get<protocol::message_count>(); }) { checksum += bench::digest(header.template get<protocol::message_count>().value()); }
        if constexpr (requires { header.template get<protocol::market_data_group>(); }) { checksum += bench::digest(header.template get<protocol::market_data_group>().value()); }
        if constexpr (requires { header.template get<protocol::sequence_number>(); }) { checksum += bench::digest(header.template get<protocol::sequence_number>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        checksum += index++;
        if constexpr (requires { header.template get<protocol::message_length>(); }) { checksum += bench::digest(header.template get<protocol::message_length>().value()); }
        if constexpr (requires { header.template get<protocol::message_type>(); }) { checksum += bench::digest(header.template get<protocol::message_type>().value()); }
    }

    void operator()(const protocol::system_event_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::source_venue>(); }) { checksum += bench::digest(message.template get<protocol::source_venue>().value()); }
    }

    void operator()(const protocol::instrument_directory_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::instrument>(); }) { checksum += bench::digest(message.template get<protocol::instrument>().value()); }
        if constexpr (requires { message.template get<protocol::allowed_book_types>(); }) { checksum += bench::digest(message.template get<protocol::allowed_book_types>().template get<protocol::firm_quote_book>()); }
        if constexpr (requires { message.template get<protocol::allowed_book_types>(); }) { checksum += bench::digest(message.template get<protocol::allowed_book_types>().template get<protocol::off_book>()); }
        if constexpr (requires { message.template get<protocol::allowed_book_types>(); }) { checksum += bench::digest(message.template get<protocol::allowed_book_types>().template get<protocol::electronic_order_book>()); }
        if constexpr (requires { message.template get<protocol::allowed_book_types>(); }) { checksum += bench::digest(message.template get<protocol::allowed_book_types>().template get<protocol::private_rfq>()); }
        if constexpr (requires { message.template get<protocol::source_venue>(); }) { checksum += bench::digest(message.template get<protocol::source_venue>().value()); }
        if constexpr (requires { message.template get<protocol::dynamic_circuit_breaker_tolerances>(); }) { checksum += bench::digest(message.template get<protocol::dynamic_circuit_breaker_tolerances>().value()); }
        if constexpr (requires { message.template get<protocol::static_circuit_breaker_tolerances>(); }) { checksum += bench::digest(message.template get<protocol::static_circuit_breaker_tolerances>().value()); }
        if constexpr (requires { message.template get<protocol::average_daily_turnover_adt>(); }) { checksum += bench::digest(message.template get<protocol::average_daily_turnover_adt>().value()); }
    }

    void operator()(const protocol::instrument_status_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::instrument>(); }) { checksum += bench::digest(message.template get<protocol::instrument>().value()); }
        if constexpr (requires { message.template get<protocol::source_venue>(); }) { checksum += bench::digest(message.template get<protocol::source_venue>().value()); }
        if constexpr (requires { message.template get<protocol::session_change_reason>(); }) { checksum += bench::digest(message.template get<protocol::session_change_reason>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_type>(); }) { checksum += bench::digest(message.template get<protocol::order_book_type>().value()); }
    }

    void operator()(const protocol::add_order_mbo_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::size_type>(); }) { checksum += bench::digest(message.template get<protocol::size_type>().value()); }
        if constexpr (requires { message.template get<protocol::instrument>(); }) { checksum += bench::digest(message.template get<protocol::instrument>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::source_venue>(); }) { checksum += bench::digest(message.template get<protocol::source_venue>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_type>(); }) { checksum += bench::digest(message.template get<protocol::order_book_type>().value()); }
        if constexpr (requires { message.template get<protocol::depth>(); }) { checksum += bench::digest(message.template get<protocol::depth>().value()); }
    }

    void operator()(const protocol::add_order_short_mbo_message& message) {
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += bench::digest(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::size_type>(); }) { checksum += bench::digest(message.template get<protocol::size_type>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
    }

    void operator()(const protocol::order_book_clear_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::source_venue>(); }) { checksum += bench::digest(message.template get<protocol::source_venue>().value()); }
        if constexpr (requires { message.template get<protocol::instrument>(); }) { checksum += bench::digest(message.template get<protocol::instrument>().value()); }
        if constexpr (requires { message.template get<protocol::order_book_type>(); }) { checksum += bench::digest(message.template get<protocol::order_book_type>().value()); }
    }

    void operator()(const protocol::trade_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::transaction_time>(); }) { checksum += bench::digest(message.template get<protocol::transaction_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_venue>(); }) { checksum += bench::digest(message.template get<protocol::source_venue>().value()); }
        if constexpr (requires { message.template get<protocol::executed_size>(); }) { checksum += bench::digest(message.template get<protocol::executed_size>().value()); }
        if constexpr (requires { message.template get<protocol::instrument>(); }) { checksum += bench::digest(message.template get<protocol::instrument>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { checksum += bench::digest(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::trade_type>(); }) { checksum += bench::digest(message.template get<protocol::trade_type>().value()); }
        if constexpr (requires { message.template get<protocol::trade_flags>(); }) { checksum += bench::digest(message.template get<protocol::trade_flags>().template get<protocol::trade_cancellation>()); }
        if constexpr (requires { message.template get<protocol::trade_flags>(); }) { checksum += bench::digest(message.template get<protocol::trade_flags>().template get<protocol::trade_correction>()); }
        if constexpr (requires { message.template get<protocol::hidden_execution_indicator>(); }) { checksum += bench::digest(message.template get<protocol::hidden_execution_indicator>().value()); }
    }

    void operator()(const protocol::statistics_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::instrument>(); }) { checksum += bench::digest(message.template get<protocol::instrument>().value()); }
        if constexpr (requires { message.template get<protocol::source_venue>(); }) { checksum += bench::digest(message.template get<protocol::source_venue>().value()); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { checksum += bench::digest(message.template get<protocol::volume>().value()); }
        if constexpr (requires { message.template get<protocol::volume_on_book_only>(); }) { checksum += bench::digest(message.template get<protocol::volume_on_book_only>().value()); }
        if constexpr (requires { message.template get<protocol::vwap>(); }) { checksum += bench::digest(message.template get<protocol::vwap>().value()); }
        if constexpr (requires { message.template get<protocol::vwap_on_book_only>(); }) { checksum += bench::digest(message.template get<protocol::vwap_on_book_only>().value()); }
        if constexpr (requires { message.template get<protocol::number_of_trades>(); }) { checksum += bench::digest(message.template get<protocol::number_of_trades>().value()); }
        if constexpr (requires { message.template get<protocol::number_of_trades_on_book_only>(); }) { checksum += bench::digest(message.template get<protocol::number_of_trades_on_book_only>().value()); }
        if constexpr (requires { message.template get<protocol::turnover>(); }) { checksum += bench::digest(message.template get<protocol::turnover>().value()); }
        if constexpr (requires { message.template get<protocol::turnover_on_book_only>(); }) { checksum += bench::digest(message.template get<protocol::turnover_on_book_only>().value()); }
    }

    void operator()(const protocol::statistics_update_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::instrument>(); }) { checksum += bench::digest(message.template get<protocol::instrument>().value()); }
        if constexpr (requires { message.template get<protocol::source_venue>(); }) { checksum += bench::digest(message.template get<protocol::source_venue>().value()); }
        if constexpr (requires { message.template get<protocol::statistic_type>(); }) { checksum += bench::digest(message.template get<protocol::statistic_type>().value()); }
        if constexpr (requires { message.template get<protocol::statistic_price>(); }) { checksum += bench::digest(message.template get<protocol::statistic_price>().value()); }
        if constexpr (requires { message.template get<protocol::statistic_size>(); }) { checksum += bench::digest(message.template get<protocol::statistic_size>().value()); }
        if constexpr (requires { message.template get<protocol::imbalance_quantity>(); }) { checksum += bench::digest(message.template get<protocol::imbalance_quantity>().value()); }
    }
};

// The values the Tmp reading reads from one datagram, folded into a checksum. A datagram it cannot read
// is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::parse_packet(frame.payload, frame.payload_len, reader);
    } catch (const std::exception& error) {
        throw;
    }

    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Lseg.Lse.Level2Mbo.Gtp.v26.2", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
