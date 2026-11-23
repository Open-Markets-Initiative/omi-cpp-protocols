// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: main.cpp
// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6 benchmark, through the Tmp header: every value it reads from every message of the simulated
// sequence (tests/simulated/tmx/tsx/quantumfeedlevel2/xmt/v3.6.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/tmp/tmx/tsx/quantumfeedlevel2/xmt/v3.6/tmx_tsx_quantumfeedlevel2_xmt_v3_6.hpp"

// Tmx Tsx QuantumFeedLevel2 Xmt 3.6: the reading of its packets, through its Template Meta Programming header
namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

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

// Business Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_business_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const msg_type& msg_type_) {
    if (static_cast<bool>(tmp::rule(msg_type_) == 'J')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& symbol_status_message_ = tmp::read<symbol_status_message>(data + offset, bound - offset, handler); offset += symbol_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(msg_type_) == 'G')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_book_message_ = tmp::read<order_book_message>(data + offset, bound - offset, handler); offset += order_book_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(msg_type_) == 'j')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_book_terms_message_ = tmp::read<order_book_terms_message>(data + offset, bound - offset, handler); offset += order_book_terms_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(msg_type_) == 'A')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& assign_cop_orders_message_ = tmp::read<assign_cop_orders_message>(data + offset, bound - offset, handler); offset += assign_cop_orders_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(msg_type_) == 'B')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& assign_cop_no_orders_message_ = tmp::read<assign_cop_no_orders_message>(data + offset, bound - offset, handler); offset += assign_cop_no_orders_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(msg_type_) == 'C')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& assign_limit_message_ = tmp::read<assign_limit_message>(data + offset, bound - offset, handler); offset += assign_limit_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(msg_type_) == 'E')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& market_state_update_message_ = tmp::read<market_state_update_message>(data + offset, bound - offset, handler); offset += market_state_update_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(msg_type_) == 'F')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& moc_imbalance_message_ = tmp::read<moc_imbalance_message>(data + offset, bound - offset, handler); offset += moc_imbalance_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(msg_type_) == 'P')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_booked_message_ = tmp::read<order_booked_message>(data + offset, bound - offset, handler); offset += order_booked_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(msg_type_) == 'm')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_booked_terms_message_ = tmp::read<order_booked_terms_message>(data + offset, bound - offset, handler); offset += order_booked_terms_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(msg_type_) == 'Q')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_cancelled_message_ = tmp::read<order_cancelled_message>(data + offset, bound - offset, handler); offset += order_cancelled_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(msg_type_) == 'n')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_cancelled_terms_message_ = tmp::read<order_cancelled_terms_message>(data + offset, bound - offset, handler); offset += order_cancelled_terms_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(msg_type_) == 'R')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_price_time_assigned_message_ = tmp::read<order_price_time_assigned_message>(data + offset, bound - offset, handler); offset += order_price_time_assigned_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(msg_type_) == 'o')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_price_time_assigned_terms_message_ = tmp::read<order_price_time_assigned_terms_message>(data + offset, bound - offset, handler); offset += order_price_time_assigned_terms_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(msg_type_) == 'I')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& stock_status_message_ = tmp::read<stock_status_message>(data + offset, bound - offset, handler); offset += stock_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(msg_type_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_report_message_ = tmp::read<trade_report_message>(data + offset, bound - offset, handler); offset += trade_report_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(msg_type_) == 'p')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_report_terms_message_ = tmp::read<trade_report_terms_message>(data + offset, bound - offset, handler); offset += trade_report_terms_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(msg_type_) == 'T')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_cancelled_message_ = tmp::read<trade_cancelled_message>(data + offset, bound - offset, handler); offset += trade_cancelled_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(msg_type_) == 'q')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_cancelled_terms_message_ = tmp::read<trade_cancelled_terms_message>(data + offset, bound - offset, handler); offset += trade_cancelled_terms_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(msg_type_) == 'U')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_correction_message_ = tmp::read<trade_correction_message>(data + offset, bound - offset, handler); offset += trade_correction_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(msg_type_) == 'r')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_correction_terms_message_ = tmp::read<trade_correction_terms_message>(data + offset, bound - offset, handler); offset += trade_correction_terms_message::size;
        return offset;
    }
    tmp::unknown(handler, data, length);
    return length;
}

// Body Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_body_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const msg_type& msg_type_) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& business_header_ = tmp::read<business_header>(data + offset, bound - offset, handler); offset += business_header::size;
    offset += parse_business_message(data + offset, bound - offset, handler, msg_type_);
    return offset;
}

// Body: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_body([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& body_header_ = tmp::read<body_header>(data + offset, bound - offset, handler); offset += body_header::size;
    bound = static_cast<std::size_t>(tmp::rule(body_header_.template get<msg_length>()));
    tmp::require(bound, length);
    {
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(body_header_.template get<msg_length>()))) - 3);
        tmp::require(offset + size, bound);
        parse_body_message(data + offset, size, handler, body_header_.template get<msg_type>());
        offset += size;
    }
    return bound;
}

// Business Bodies: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_business_bodies([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const num_body& num_body_) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(num_body_));
        while (count-- > 0) {
            offset += parse_body(data + offset, bound - offset, handler);
        }
    }
    return offset;
}

// Heartbeat Body: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_heartbeat_body([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const num_body& num_body_) {
    std::size_t offset = 0;
    std::size_t bound = length;
    [[maybe_unused]] const auto& heartbeat_body_section_1_ = tmp::read<heartbeat_body_section_1>(data + offset, bound - offset, handler); offset += heartbeat_body_section_1::size;
    tmp::call(handler, heartbeat_body_section_1_.template get<body_header>());
    bound = static_cast<std::size_t>(tmp::rule(heartbeat_body_section_1_.template get<body_header>().template get<msg_length>()));
    tmp::require(bound, length);
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(num_body_));
        while (count-- > 0) {
            offset += tmp::take<admin_body>(data + offset, bound - offset, handler);
        }
    }
    return bound;
}

// Packet Body: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_packet_body([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const num_body& num_body_) {
    if (static_cast<bool>(tmp::rule(tmp::ahead<msg_type>(data, length, 2)) == '0')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_heartbeat_body(data + offset, bound - offset, handler, num_body_);
        tmp::call(handler, heartbeat_body{});
        return offset;
    }
    {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_business_bodies(data + offset, bound - offset, handler, num_body_);
        return offset;
    }
}

// Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& frame_header_ = tmp::read<frame_header>(data + offset, bound - offset, handler); offset += frame_header::size;
    if (static_cast<bool>(tmp::rule(frame_header_.template get<message_length>()) > 6)) {
        offset += parse_packet_body(data + offset, bound - offset, handler, frame_header_.template get<num_body>());
    }
    return offset;
}


} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6

namespace protocol = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::frame_header& header) {
        if constexpr (requires { header.template get<protocol::start_of_frame>(); }) { checksum += bench::digest(header.template get<protocol::start_of_frame>().value()); }
        if constexpr (requires { header.template get<protocol::protocol_name>(); }) { checksum += bench::digest(header.template get<protocol::protocol_name>().value()); }
        if constexpr (requires { header.template get<protocol::protocol_version>(); }) { checksum += bench::digest(header.template get<protocol::protocol_version>().value()); }
        if constexpr (requires { header.template get<protocol::message_length>(); }) { checksum += bench::digest(header.template get<protocol::message_length>().value()); }
        if constexpr (requires { header.template get<protocol::session_id>(); }) { checksum += bench::digest(header.template get<protocol::session_id>().value()); }
        if constexpr (requires { header.template get<protocol::ack_required_poss_dup>(); }) { checksum += bench::digest(header.template get<protocol::ack_required_poss_dup>().value()); }
        if constexpr (requires { header.template get<protocol::num_body>(); }) { checksum += bench::digest(header.template get<protocol::num_body>().value()); }
    }

    void operator()(const protocol::business_header& header) {
        checksum += index++;
        if constexpr (requires { header.template get<protocol::msg_version>(); }) { checksum += bench::digest(header.template get<protocol::msg_version>().value()); }
        if constexpr (requires { header.template get<protocol::source_id>(); }) { checksum += bench::digest(header.template get<protocol::source_id>().value()); }
        if constexpr (requires { header.template get<protocol::stream_id>(); }) { checksum += bench::digest(header.template get<protocol::stream_id>().value()); }
        if constexpr (requires { header.template get<protocol::sequence_0>(); }) { checksum += bench::digest(header.template get<protocol::sequence_0>().value()); }
        if constexpr (requires { header.template get<protocol::sequence_1>(); }) { checksum += bench::digest(header.template get<protocol::sequence_1>().value()); }
    }

    void operator()(const protocol::symbol_status_message& message) {
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::stock_group>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::stock_group>().value()) != 0x0U ? bench::digest(message.template get<protocol::stock_group>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::cusip>(); }) { checksum += bench::digest(message.template get<protocol::cusip>().value()); }
        if constexpr (requires { message.template get<protocol::board_lot>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::board_lot>().value()) != 0x0U ? bench::digest(message.template get<protocol::board_lot>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::currency>(); }) { checksum += bench::digest(message.template get<protocol::currency>().value()); }
        if constexpr (requires { message.template get<protocol::face_value>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::face_value>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::face_value>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::last_sale>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::last_sale>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::last_sale>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::listing_market>(); }) { checksum += bench::digest(message.template get<protocol::listing_market>().value()); }
        if constexpr (requires { message.template get<protocol::product_type>(); }) { checksum += bench::digest(message.template get<protocol::product_type>().value()); }
        if constexpr (requires { message.template get<protocol::buy_maximum_quantity>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::buy_maximum_quantity>().value()) != 0x0U ? bench::digest(message.template get<protocol::buy_maximum_quantity>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::buy_minimum_quantity>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::buy_minimum_quantity>().value()) != 0x0U ? bench::digest(message.template get<protocol::buy_minimum_quantity>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::sell_maximum_quantity>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::sell_maximum_quantity>().value()) != 0x0U ? bench::digest(message.template get<protocol::sell_maximum_quantity>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::sell_minimum_quantity>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::sell_minimum_quantity>().value()) != 0x0U ? bench::digest(message.template get<protocol::sell_minimum_quantity>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::stock_state>(); }) { checksum += bench::digest(message.template get<protocol::stock_state>().value()); }
        if constexpr (requires { message.template get<protocol::test_symbol>(); }) { checksum += bench::digest(message.template get<protocol::test_symbol>().value()); }
        if constexpr (requires { message.template get<protocol::moc_eligible>(); }) { checksum += bench::digest(message.template get<protocol::moc_eligible>().value()); }
    }

    void operator()(const protocol::order_book_message& message) {
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::broker_number>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::broker_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::broker_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_side>(); }) { checksum += bench::digest(message.template get<protocol::order_side>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_id>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::order_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_price>(); }) { checksum += bench::digest(message.template get<protocol::order_price>().value()); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::volume>().value()) != 0x0U ? bench::digest(message.template get<protocol::volume>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::priority_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::priority_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::priority_time_stamp>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::order_book_terms_message& message) {
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::broker_number>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::broker_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::broker_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_side>(); }) { checksum += bench::digest(message.template get<protocol::order_side>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_id>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::order_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::volume>().value()) != 0x0U ? bench::digest(message.template get<protocol::volume>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::non_resident>(); }) { checksum += bench::digest(message.template get<protocol::non_resident>().value()); }
        if constexpr (requires { message.template get<protocol::settlement_terms>(); }) { checksum += bench::digest(message.template get<protocol::settlement_terms>().value()); }
        if constexpr (requires { message.template get<protocol::settlement_date>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::settlement_date>().value()) != 0x0U ? bench::digest(message.template get<protocol::settlement_date>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::priority_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::priority_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::priority_time_stamp>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::assign_cop_orders_message& message) {
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::calculated_opening_price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::calculated_opening_price>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::calculated_opening_price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_side>(); }) { checksum += bench::digest(message.template get<protocol::order_side>().value()); }
        for (std::size_t cop_order_index = 0; const auto& cop_order_entry : message.template get<std::array<protocol::cop_order, 15>>()) {
            checksum += cop_order_index++;
            if constexpr (requires { cop_order_entry.template get<protocol::broker_number>(); }) { checksum += (static_cast<std::uint16_t>(cop_order_entry.template get<protocol::broker_number>().value()) != 0x0U ? bench::digest(cop_order_entry.template get<protocol::broker_number>().value()) : std::uint64_t{0}); }
            if constexpr (requires { cop_order_entry.template get<protocol::order_id>(); }) { checksum += (static_cast<std::uint64_t>(cop_order_entry.template get<protocol::order_id>().value()) != 0x0ULL ? bench::digest(cop_order_entry.template get<protocol::order_id>().value()) : std::uint64_t{0}); }
        }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::trading_system_time_stamp>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::assign_cop_no_orders_message& message) {
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::calculated_opening_price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::calculated_opening_price>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::calculated_opening_price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::trading_system_time_stamp>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::assign_limit_message& message) {
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::calculated_opening_price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::calculated_opening_price>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::calculated_opening_price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_side>(); }) { checksum += bench::digest(message.template get<protocol::order_side>().value()); }
        for (std::size_t cop_limit_index = 0; const auto& cop_limit_entry : message.template get<std::array<protocol::cop_limit, 15>>()) {
            checksum += cop_limit_index++;
            if constexpr (requires { cop_limit_entry.template get<protocol::broker_number>(); }) { checksum += (static_cast<std::uint16_t>(cop_limit_entry.template get<protocol::broker_number>().value()) != 0x0U ? bench::digest(cop_limit_entry.template get<protocol::broker_number>().value()) : std::uint64_t{0}); }
            if constexpr (requires { cop_limit_entry.template get<protocol::order_id>(); }) { checksum += (static_cast<std::uint64_t>(cop_limit_entry.template get<protocol::order_id>().value()) != 0x0ULL ? bench::digest(cop_limit_entry.template get<protocol::order_id>().value()) : std::uint64_t{0}); }
            if constexpr (requires { cop_limit_entry.template get<protocol::price>(); }) { checksum += (static_cast<std::uint64_t>(cop_limit_entry.template get<protocol::price>().value()) != 0x0ULL ? bench::digest(cop_limit_entry.template get<protocol::price>().value()) : std::uint64_t{0}); }
        }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::trading_system_time_stamp>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::market_state_update_message& message) {
        if constexpr (requires { message.template get<protocol::market_state>(); }) { checksum += bench::digest(message.template get<protocol::market_state>().value()); }
        if constexpr (requires { message.template get<protocol::stock_group>(); }) { checksum += (static_cast<std::uint8_t>(message.template get<protocol::stock_group>().value()) != 0x0U ? bench::digest(message.template get<protocol::stock_group>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::trading_system_time_stamp>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::moc_imbalance_message& message) {
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::imbalance_side>(); }) { checksum += bench::digest(message.template get<protocol::imbalance_side>().value()); }
        if constexpr (requires { message.template get<protocol::imbalance_volume>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::imbalance_volume>().value()) != 0x0U ? bench::digest(message.template get<protocol::imbalance_volume>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::trading_system_time_stamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::imbalance_reference_price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::imbalance_reference_price>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::imbalance_reference_price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::paired_volume>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::paired_volume>().value()) != 0x0U ? bench::digest(message.template get<protocol::paired_volume>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::market_order_imbalance_volume>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::market_order_imbalance_volume>().value()) != 0x0U ? bench::digest(message.template get<protocol::market_order_imbalance_volume>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::market_order_imbalance_side>(); }) { checksum += bench::digest(message.template get<protocol::market_order_imbalance_side>().value()); }
        if constexpr (requires { message.template get<protocol::near_indicative_closing_price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::near_indicative_closing_price>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::near_indicative_closing_price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::far_indicative_closing_price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::far_indicative_closing_price>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::far_indicative_closing_price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::price_variation>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::price_variation>().value()) != 0x0U ? bench::digest(message.template get<protocol::price_variation>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::order_booked_message& message) {
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::broker_number>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::broker_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::broker_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_side>(); }) { checksum += bench::digest(message.template get<protocol::order_side>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_id>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::order_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_price>(); }) { checksum += bench::digest(message.template get<protocol::order_price>().value()); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::volume>().value()) != 0x0U ? bench::digest(message.template get<protocol::volume>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::priority_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::priority_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::priority_time_stamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::trading_system_time_stamp>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::order_booked_terms_message& message) {
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::broker_number>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::broker_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::broker_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_side>(); }) { checksum += bench::digest(message.template get<protocol::order_side>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_id>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::order_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::volume>().value()) != 0x0U ? bench::digest(message.template get<protocol::volume>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::non_resident>(); }) { checksum += bench::digest(message.template get<protocol::non_resident>().value()); }
        if constexpr (requires { message.template get<protocol::settlement_terms>(); }) { checksum += bench::digest(message.template get<protocol::settlement_terms>().value()); }
        if constexpr (requires { message.template get<protocol::settlement_date>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::settlement_date>().value()) != 0x0U ? bench::digest(message.template get<protocol::settlement_date>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::priority_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::priority_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::priority_time_stamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::trading_system_time_stamp>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::order_cancelled_message& message) {
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::broker_number>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::broker_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::broker_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_side>(); }) { checksum += bench::digest(message.template get<protocol::order_side>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_id>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::order_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::trading_system_time_stamp>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::order_cancelled_terms_message& message) {
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::broker_number>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::broker_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::broker_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_side>(); }) { checksum += bench::digest(message.template get<protocol::order_side>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_id>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::order_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::trading_system_time_stamp>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::order_price_time_assigned_message& message) {
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::broker_number>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::broker_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::broker_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_side>(); }) { checksum += bench::digest(message.template get<protocol::order_side>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_id>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::order_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::volume>().value()) != 0x0U ? bench::digest(message.template get<protocol::volume>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::priority_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::priority_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::priority_time_stamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::trading_system_time_stamp>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::order_price_time_assigned_terms_message& message) {
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::broker_number>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::broker_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::broker_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::order_side>(); }) { checksum += bench::digest(message.template get<protocol::order_side>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::order_id>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::order_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::volume>().value()) != 0x0U ? bench::digest(message.template get<protocol::volume>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::priority_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::priority_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::priority_time_stamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::trading_system_time_stamp>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::stock_status_message& message) {
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::comment>(); }) { checksum += bench::digest(message.template get<protocol::comment>().value()); }
        if constexpr (requires { message.template get<protocol::stock_state>(); }) { checksum += bench::digest(message.template get<protocol::stock_state>().value()); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::trading_system_time_stamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::listing_market>(); }) { checksum += bench::digest(message.template get<protocol::listing_market>().value()); }
        if constexpr (requires { message.template get<protocol::product_type>(); }) { checksum += bench::digest(message.template get<protocol::product_type>().value()); }
    }

    void operator()(const protocol::trade_report_message& message) {
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::trade_number>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::trade_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::trade_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::volume>().value()) != 0x0U ? bench::digest(message.template get<protocol::volume>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::buy_broker_number>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::buy_broker_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::buy_broker_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::buy_order_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::buy_order_id>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::buy_order_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::buy_display_volume>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::buy_display_volume>().value()) != 0x0U ? bench::digest(message.template get<protocol::buy_display_volume>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::sell_broker_number>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::sell_broker_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::sell_broker_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::sell_order_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::sell_order_id>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::sell_order_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::sell_display_volume>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::sell_display_volume>().value()) != 0x0U ? bench::digest(message.template get<protocol::sell_display_volume>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::bypass>(); }) { checksum += bench::digest(message.template get<protocol::bypass>().value()); }
        if constexpr (requires { message.template get<protocol::trade_time_stamp>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::trade_time_stamp>().value()) != 0x0U ? bench::digest(message.template get<protocol::trade_time_stamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::cross_type>(); }) { checksum += bench::digest(message.template get<protocol::cross_type>().value()); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::trading_system_time_stamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::listing_market>(); }) { checksum += bench::digest(message.template get<protocol::listing_market>().value()); }
        if constexpr (requires { message.template get<protocol::product_type>(); }) { checksum += bench::digest(message.template get<protocol::product_type>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::trade_date>().value()) != 0x0U ? bench::digest(message.template get<protocol::trade_date>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::is_mid_only>(); }) { checksum += bench::digest(message.template get<protocol::is_mid_only>().value()); }
        if constexpr (requires { message.template get<protocol::is_dark>(); }) { checksum += bench::digest(message.template get<protocol::is_dark>().value()); }
        if constexpr (requires { message.template get<protocol::is_conditional>(); }) { checksum += bench::digest(message.template get<protocol::is_conditional>().value()); }
    }

    void operator()(const protocol::trade_report_terms_message& message) {
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::trade_number>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::trade_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::trade_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::volume>().value()) != 0x0U ? bench::digest(message.template get<protocol::volume>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::buy_broker_number>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::buy_broker_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::buy_broker_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::buy_order_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::buy_order_id>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::buy_order_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::buy_display_volume>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::buy_display_volume>().value()) != 0x0U ? bench::digest(message.template get<protocol::buy_display_volume>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::sell_broker_number>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::sell_broker_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::sell_broker_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::sell_order_id>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::sell_order_id>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::sell_order_id>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::sell_display_volume>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::sell_display_volume>().value()) != 0x0U ? bench::digest(message.template get<protocol::sell_display_volume>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trade_time_stamp>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::trade_time_stamp>().value()) != 0x0U ? bench::digest(message.template get<protocol::trade_time_stamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::non_resident>(); }) { checksum += bench::digest(message.template get<protocol::non_resident>().value()); }
        if constexpr (requires { message.template get<protocol::settlement_terms>(); }) { checksum += bench::digest(message.template get<protocol::settlement_terms>().value()); }
        if constexpr (requires { message.template get<protocol::settlement_date>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::settlement_date>().value()) != 0x0U ? bench::digest(message.template get<protocol::settlement_date>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::cross_type>(); }) { checksum += bench::digest(message.template get<protocol::cross_type>().value()); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::trading_system_time_stamp>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::trade_cancelled_message& message) {
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::trade_number>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::trade_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::trade_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::trading_system_time_stamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::listing_market>(); }) { checksum += bench::digest(message.template get<protocol::listing_market>().value()); }
        if constexpr (requires { message.template get<protocol::product_type>(); }) { checksum += bench::digest(message.template get<protocol::product_type>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::trade_date>().value()) != 0x0U ? bench::digest(message.template get<protocol::trade_date>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::trade_cancelled_terms_message& message) {
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::trade_number>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::trade_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::trade_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::trading_system_time_stamp>().value()) : std::uint64_t{0}); }
    }

    void operator()(const protocol::trade_correction_message& message) {
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::trade_number>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::trade_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::trade_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::volume>().value()) != 0x0U ? bench::digest(message.template get<protocol::volume>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::buy_broker_number>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::buy_broker_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::buy_broker_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::sell_broker_number>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::sell_broker_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::sell_broker_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::initiated_by>(); }) { checksum += bench::digest(message.template get<protocol::initiated_by>().value()); }
        if constexpr (requires { message.template get<protocol::orig_trade_number>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::orig_trade_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::orig_trade_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::bypass>(); }) { checksum += bench::digest(message.template get<protocol::bypass>().value()); }
        if constexpr (requires { message.template get<protocol::trade_time_stamp>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::trade_time_stamp>().value()) != 0x0U ? bench::digest(message.template get<protocol::trade_time_stamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::cross_type>(); }) { checksum += bench::digest(message.template get<protocol::cross_type>().value()); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::trading_system_time_stamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::listing_market>(); }) { checksum += bench::digest(message.template get<protocol::listing_market>().value()); }
        if constexpr (requires { message.template get<protocol::product_type>(); }) { checksum += bench::digest(message.template get<protocol::product_type>().value()); }
        if constexpr (requires { message.template get<protocol::trade_date>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::trade_date>().value()) != 0x0U ? bench::digest(message.template get<protocol::trade_date>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::is_mid_only>(); }) { checksum += bench::digest(message.template get<protocol::is_mid_only>().value()); }
        if constexpr (requires { message.template get<protocol::is_dark>(); }) { checksum += bench::digest(message.template get<protocol::is_dark>().value()); }
        if constexpr (requires { message.template get<protocol::is_conditional>(); }) { checksum += bench::digest(message.template get<protocol::is_conditional>().value()); }
    }

    void operator()(const protocol::trade_correction_terms_message& message) {
        if constexpr (requires { message.template get<protocol::symbol>(); }) { checksum += bench::digest(message.template get<protocol::symbol>().value()); }
        if constexpr (requires { message.template get<protocol::trade_number>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::trade_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::trade_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::price>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::price>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::volume>().value()) != 0x0U ? bench::digest(message.template get<protocol::volume>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::buy_broker_number>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::buy_broker_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::buy_broker_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::sell_broker_number>(); }) { checksum += (static_cast<std::uint16_t>(message.template get<protocol::sell_broker_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::sell_broker_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::initiated_by>(); }) { checksum += bench::digest(message.template get<protocol::initiated_by>().value()); }
        if constexpr (requires { message.template get<protocol::orig_trade_number>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::orig_trade_number>().value()) != 0x0U ? bench::digest(message.template get<protocol::orig_trade_number>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::trade_time_stamp>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::trade_time_stamp>().value()) != 0x0U ? bench::digest(message.template get<protocol::trade_time_stamp>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::non_resident>(); }) { checksum += bench::digest(message.template get<protocol::non_resident>().value()); }
        if constexpr (requires { message.template get<protocol::settlement_terms>(); }) { checksum += bench::digest(message.template get<protocol::settlement_terms>().value()); }
        if constexpr (requires { message.template get<protocol::settlement_date>(); }) { checksum += (static_cast<std::uint32_t>(message.template get<protocol::settlement_date>().value()) != 0x0U ? bench::digest(message.template get<protocol::settlement_date>().value()) : std::uint64_t{0}); }
        if constexpr (requires { message.template get<protocol::cross_type>(); }) { checksum += bench::digest(message.template get<protocol::cross_type>().value()); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { checksum += (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? bench::digest(message.template get<protocol::trading_system_time_stamp>().value()) : std::uint64_t{0}); }
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
    return bench::run("Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6", "tmp", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
