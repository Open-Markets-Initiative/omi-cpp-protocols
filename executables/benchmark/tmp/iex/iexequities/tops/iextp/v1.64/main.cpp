// Iex.IexEquities.Tops.IexTp.v1.64 benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/iex/iexequities/tops/iextp/v1.64.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/tmp/iex/iexequities/tops/iextp/v1.64/iex_iexequities_tops_iextp_v1_64.hpp"

// Iex IexEquities Tops IexTp 1.64: the reading of its packets, through its Template Meta Programming header
namespace iex::iexequities::tops::iextp::v1_64 {

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

// Message Data: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_message_data([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_type& message_type_) {
    if (static_cast<bool>(tmp::rule(message_type_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& system_event_message_ = tmp::read<system_event_message>(data + offset, bound - offset, handler); offset += system_event_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'D')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& security_directory_message_ = tmp::read<security_directory_message>(data + offset, bound - offset, handler); offset += security_directory_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'H')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trading_status_message_ = tmp::read<trading_status_message>(data + offset, bound - offset, handler); offset += trading_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'O')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& operational_halt_status_message_ = tmp::read<operational_halt_status_message>(data + offset, bound - offset, handler); offset += operational_halt_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'P')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& short_sale_price_test_status_message_ = tmp::read<short_sale_price_test_status_message>(data + offset, bound - offset, handler); offset += short_sale_price_test_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'E')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& security_event_message_ = tmp::read<security_event_message>(data + offset, bound - offset, handler); offset += security_event_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'Q')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& quote_update_message_ = tmp::read<quote_update_message>(data + offset, bound - offset, handler); offset += quote_update_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'T')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_report_message_ = tmp::read<trade_report_message>(data + offset, bound - offset, handler); offset += trade_report_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'X')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& official_price_message_ = tmp::read<official_price_message>(data + offset, bound - offset, handler); offset += official_price_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'B')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_break_message_ = tmp::read<trade_break_message>(data + offset, bound - offset, handler); offset += trade_break_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'A')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& auction_information_message_ = tmp::read<auction_information_message>(data + offset, bound - offset, handler); offset += auction_information_message::size;
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
    bound = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(message_header_.template get<message_length>()))) + 2);
    tmp::require(bound, length);
    offset += parse_message_data(data + offset, bound - offset, handler, message_header_.template get<message_type>());
    return bound;
}

// Messages: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_messages([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_count& message_count_) {
    if (static_cast<bool>(tmp::rule(message_count_) == 0)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, heartbeat{});
        return offset;
    }
    {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        {
            std::size_t count = static_cast<std::size_t>(tmp::rule(message_count_));
            while (count-- > 0) {
                offset += parse_message(data + offset, bound - offset, handler);
            }
        }
        return offset;
    }
}

// Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& iextp_header_ = tmp::read<iextp_header>(data + offset, bound - offset, handler); offset += iextp_header::size;
    {
        const std::size_t size = static_cast<std::size_t>(tmp::rule(iextp_header_.template get<payload_length>()));
        tmp::require(offset + size, bound);
        parse_messages(data + offset, size, handler, iextp_header_.template get<message_count>());
        offset += size;
    }
    return offset;
}


} // namespace iex::iexequities::tops::iextp::v1_64

namespace protocol = ::iex::iexequities::tops::iextp::v1_64;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::iextp_header& header) {
        if constexpr (requires { header.template get<protocol::version>(); }) { checksum += bench::digest(header.template get<protocol::version>().value()); }
        if constexpr (requires { header.template get<protocol::message_protocol_id>(); }) { checksum += bench::digest(header.template get<protocol::message_protocol_id>().value()); }
        if constexpr (requires { header.template get<protocol::channel_id>(); }) { checksum += bench::digest(header.template get<protocol::channel_id>().value()); }
        if constexpr (requires { header.template get<protocol::session_id>(); }) { checksum += bench::digest(header.template get<protocol::session_id>().value()); }
        if constexpr (requires { header.template get<protocol::payload_length>(); }) { checksum += bench::digest(header.template get<protocol::payload_length>().value()); }
        if constexpr (requires { header.template get<protocol::message_count>(); }) { checksum += bench::digest(header.template get<protocol::message_count>().value()); }
        if constexpr (requires { header.template get<protocol::stream_offset>(); }) { checksum += bench::digest(header.template get<protocol::stream_offset>().value()); }
        if constexpr (requires { header.template get<protocol::first_message_sequence_number>(); }) { checksum += bench::digest(header.template get<protocol::first_message_sequence_number>().value()); }
        if constexpr (requires { header.template get<protocol::send_time>(); }) { checksum += bench::digest(header.template get<protocol::send_time>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        checksum += index++;
        if constexpr (requires { header.template get<protocol::message_length>(); }) { checksum += bench::digest(header.template get<protocol::message_length>().value()); }
        if constexpr (requires { header.template get<protocol::message_type>(); }) { checksum += bench::digest(header.template get<protocol::message_type>().value()); }
    }

    void operator()(const protocol::system_event_message& message) {
        if constexpr (requires { message.template get<protocol::system_event>(); }) { checksum += bench::digest(message.template get<protocol::system_event>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
    }

    void operator()(const protocol::security_directory_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::round_lot_size>(); }) { checksum += bench::digest(message.template get<protocol::round_lot_size>().value()); }
        if constexpr (requires { message.template get<protocol::adjusted_poc_price>(); }) { checksum += bench::digest(message.template get<protocol::adjusted_poc_price>().value()); }
        if constexpr (requires { message.template get<protocol::luld_tier>(); }) { checksum += bench::digest(message.template get<protocol::luld_tier>().value()); }
    }

    void operator()(const protocol::trading_status_message& message) {
        if constexpr (requires { message.template get<protocol::trading_status>(); }) { checksum += bench::digest(message.template get<protocol::trading_status>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::reason>(); }) { checksum += bench::digest(message.template get<protocol::reason>().value()); }
    }

    void operator()(const protocol::operational_halt_status_message& message) {
        if constexpr (requires { message.template get<protocol::operational_halt_status>(); }) { checksum += bench::digest(message.template get<protocol::operational_halt_status>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
    }

    void operator()(const protocol::short_sale_price_test_status_message& message) {
        if constexpr (requires { message.template get<protocol::short_sale_price_test_status>(); }) { checksum += bench::digest(message.template get<protocol::short_sale_price_test_status>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::detail>(); }) { checksum += bench::digest(message.template get<protocol::detail>().value()); }
    }

    void operator()(const protocol::security_event_message& message) {
        if constexpr (requires { message.template get<protocol::security_event>(); }) { checksum += bench::digest(message.template get<protocol::security_event>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
    }

    void operator()(const protocol::quote_update_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::bid_size>(); }) { checksum += bench::digest(message.template get<protocol::bid_size>().value()); }
        if constexpr (requires { message.template get<protocol::bid_price>(); }) { checksum += bench::digest(message.template get<protocol::bid_price>().value()); }
        if constexpr (requires { message.template get<protocol::ask_price>(); }) { checksum += bench::digest(message.template get<protocol::ask_price>().value()); }
        if constexpr (requires { message.template get<protocol::ask_size>(); }) { checksum += bench::digest(message.template get<protocol::ask_size>().value()); }
    }

    void operator()(const protocol::trade_report_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::size_type>(); }) { checksum += bench::digest(message.template get<protocol::size_type>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { checksum += bench::digest(message.template get<protocol::trade_id>().value()); }
    }

    void operator()(const protocol::official_price_message& message) {
        if constexpr (requires { message.template get<protocol::price_type>(); }) { checksum += bench::digest(message.template get<protocol::price_type>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::official_price>(); }) { checksum += bench::digest(message.template get<protocol::official_price>().value()); }
    }

    void operator()(const protocol::trade_break_message& message) {
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::size_type>(); }) { checksum += bench::digest(message.template get<protocol::size_type>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += bench::digest(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { checksum += bench::digest(message.template get<protocol::trade_id>().value()); }
    }

    void operator()(const protocol::auction_information_message& message) {
        if constexpr (requires { message.template get<protocol::auction_type>(); }) { checksum += bench::digest(message.template get<protocol::auction_type>().value()); }
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { checksum += bench::digest(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::paired_shares>(); }) { checksum += bench::digest(message.template get<protocol::paired_shares>().value()); }
        if constexpr (requires { message.template get<protocol::reference_price>(); }) { checksum += bench::digest(message.template get<protocol::reference_price>().value()); }
        if constexpr (requires { message.template get<protocol::indicative_clearing_price>(); }) { checksum += bench::digest(message.template get<protocol::indicative_clearing_price>().value()); }
        if constexpr (requires { message.template get<protocol::imbalance_shares>(); }) { checksum += bench::digest(message.template get<protocol::imbalance_shares>().value()); }
        if constexpr (requires { message.template get<protocol::imbalance_side>(); }) { checksum += bench::digest(message.template get<protocol::imbalance_side>().value()); }
        if constexpr (requires { message.template get<protocol::extension_number>(); }) { checksum += bench::digest(message.template get<protocol::extension_number>().value()); }
        if constexpr (requires { message.template get<protocol::scheduled_auction_time>(); }) { checksum += bench::digest(message.template get<protocol::scheduled_auction_time>().value()); }
        if constexpr (requires { message.template get<protocol::auction_book_clearing_price>(); }) { checksum += bench::digest(message.template get<protocol::auction_book_clearing_price>().value()); }
        if constexpr (requires { message.template get<protocol::collar_reference_price>(); }) { checksum += bench::digest(message.template get<protocol::collar_reference_price>().value()); }
        if constexpr (requires { message.template get<protocol::lower_auction_collar>(); }) { checksum += bench::digest(message.template get<protocol::lower_auction_collar>().value()); }
        if constexpr (requires { message.template get<protocol::upper_auction_collar>(); }) { checksum += bench::digest(message.template get<protocol::upper_auction_collar>().value()); }
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
    return bench::run("Iex.IexEquities.Tops.IexTp.v1.64", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
