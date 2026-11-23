// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10 canonical values, through the Tmp header: every value the Tmp reading hands
// over from each sample, at its address, held to what the model reads.

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
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/tmp/tmx/tsx/quantumfeedlevel2/xmt/v2.10/tmx_tsx_quantumfeedlevel2_xmt_v2_10.hpp"

// Tmx Tsx QuantumFeedLevel2 Xmt 2.10: the reading of its packets, through its Template Meta Programming header
namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

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


} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10

namespace protocol = ::tmx::tsx::quantumfeedlevel2::xmt::v2_10;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;
    std::string entry;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::frame_header& header) {
        if constexpr (requires { header.template get<protocol::start_of_frame>(); }) { values["packet.frameheader.startofframe"] = canonical::number(header.template get<protocol::start_of_frame>().value()); }
        if constexpr (requires { header.template get<protocol::protocol_name>(); }) { values["packet.frameheader.protocolname"] = canonical::text(canonical::character(header.template get<protocol::protocol_name>().value())); }
        if constexpr (requires { header.template get<protocol::protocol_version>(); }) { values["packet.frameheader.protocolversion"] = canonical::numeric(canonical::character(header.template get<protocol::protocol_version>().value())); }
        if constexpr (requires { header.template get<protocol::message_length>(); }) { values["packet.frameheader.messagelength"] = canonical::number(header.template get<protocol::message_length>().value()); }
        if constexpr (requires { header.template get<protocol::session_id>(); }) { values["packet.frameheader.sessionid"] = canonical::number(header.template get<protocol::session_id>().value()); }
        if constexpr (requires { header.template get<protocol::ack_required_poss_dup>(); }) { values["packet.frameheader.ackrequiredpossdup"] = canonical::text(canonical::character(header.template get<protocol::ack_required_poss_dup>().value())); }
        if constexpr (requires { header.template get<protocol::num_body>(); }) { values["packet.frameheader.numbody"] = canonical::number(header.template get<protocol::num_body>().value()); }
    }

    void operator()(const protocol::business_header& header) {
        entry = "packet.packetbody.businessbodies.body[" + std::to_string(index++) + "]";
        if constexpr (requires { header.template get<protocol::msg_version>(); }) { values[entry + ".bodymessage.businessheader.msgversion"] = canonical::number(header.template get<protocol::msg_version>().value()); }
        if constexpr (requires { header.template get<protocol::source_id>(); }) { values[entry + ".bodymessage.businessheader.sourceid"] = canonical::text(canonical::character(header.template get<protocol::source_id>().value())); }
        if constexpr (requires { header.template get<protocol::stream_id>(); }) { values[entry + ".bodymessage.businessheader.streamid"] = canonical::number(header.template get<protocol::stream_id>().value()); }
        if constexpr (requires { header.template get<protocol::sequence_0>(); }) { values[entry + ".bodymessage.businessheader.sequence0"] = canonical::number(header.template get<protocol::sequence_0>().value()); }
        if constexpr (requires { header.template get<protocol::sequence_1>(); }) { values[entry + ".bodymessage.businessheader.sequence1"] = canonical::number(header.template get<protocol::sequence_1>().value()); }
    }

    void operator()(const protocol::symbol_status_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.symbolstatusmessage";
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".bodymessage.businessmessage.symbolstatusmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::stock_group>(); }) { values[entry + ".bodymessage.businessmessage.symbolstatusmessage.stockgroup"] = (static_cast<std::uint8_t>(message.template get<protocol::stock_group>().value()) != 0x0U ? canonical::number(message.template get<protocol::stock_group>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::cusip>(); }) { values[entry + ".bodymessage.businessmessage.symbolstatusmessage.cusip"] = canonical::text(std::string(message.template get<protocol::cusip>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::board_lot>(); }) { values[entry + ".bodymessage.businessmessage.symbolstatusmessage.boardlot"] = (static_cast<std::uint16_t>(message.template get<protocol::board_lot>().value()) != 0x0U ? canonical::number(message.template get<protocol::board_lot>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::currency>(); }) { values[entry + ".bodymessage.businessmessage.symbolstatusmessage.currency"] = canonical::text(canonical::character(message.template get<protocol::currency>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::face_value>(); }) { values[entry + ".bodymessage.businessmessage.symbolstatusmessage.facevalue"] = (static_cast<std::uint64_t>(message.template get<protocol::face_value>().value()) != 0x0ULL ? canonical::scaled(message.template get<protocol::face_value>().value(), -6) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::last_sale>(); }) { values[entry + ".bodymessage.businessmessage.symbolstatusmessage.lastsale"] = (static_cast<std::uint64_t>(message.template get<protocol::last_sale>().value()) != 0x0ULL ? canonical::scaled(message.template get<protocol::last_sale>().value(), -6) : canonical::absent()); }
    }

    void operator()(const protocol::order_book_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.orderbookmessage";
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".bodymessage.businessmessage.orderbookmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::broker_number>(); }) { values[entry + ".bodymessage.businessmessage.orderbookmessage.brokernumber"] = (static_cast<std::uint16_t>(message.template get<protocol::broker_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::broker_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::order_side>(); }) { values[entry + ".bodymessage.businessmessage.orderbookmessage.orderside"] = canonical::text(canonical::character(message.template get<protocol::order_side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".bodymessage.businessmessage.orderbookmessage.orderid"] = (static_cast<std::uint64_t>(message.template get<protocol::order_id>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::order_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".bodymessage.businessmessage.orderbookmessage.price"] = (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x0ULL ? canonical::scaled(message.template get<protocol::price>().value(), -6) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { values[entry + ".bodymessage.businessmessage.orderbookmessage.volume"] = (static_cast<std::uint32_t>(message.template get<protocol::volume>().value()) != 0x0U ? canonical::number(message.template get<protocol::volume>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::priority_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.orderbookmessage.prioritytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::priority_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::priority_time_stamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::order_book_terms_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.orderbooktermsmessage";
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::broker_number>(); }) { values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.brokernumber"] = (static_cast<std::uint16_t>(message.template get<protocol::broker_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::broker_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::order_side>(); }) { values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.orderside"] = canonical::text(canonical::character(message.template get<protocol::order_side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.orderid"] = (static_cast<std::uint64_t>(message.template get<protocol::order_id>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::order_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.price"] = (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x0ULL ? canonical::scaled(message.template get<protocol::price>().value(), -6) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.volume"] = (static_cast<std::uint32_t>(message.template get<protocol::volume>().value()) != 0x0U ? canonical::number(message.template get<protocol::volume>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::non_resident>(); }) { values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.nonresident"] = canonical::text(canonical::character(message.template get<protocol::non_resident>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::settlement_terms>(); }) { values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.settlementterms"] = canonical::text(canonical::character(message.template get<protocol::settlement_terms>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::settlement_date>(); }) { values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.settlementdate"] = (static_cast<std::uint32_t>(message.template get<protocol::settlement_date>().value()) != 0x0U ? canonical::number(message.template get<protocol::settlement_date>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::priority_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.orderbooktermsmessage.prioritytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::priority_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::priority_time_stamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::assign_cop_orders_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.assigncopordersmessage";
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".bodymessage.businessmessage.assigncopordersmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::calculated_opening_price>(); }) { values[entry + ".bodymessage.businessmessage.assigncopordersmessage.calculatedopeningprice"] = (static_cast<std::uint64_t>(message.template get<protocol::calculated_opening_price>().value()) != 0x0ULL ? canonical::scaled(message.template get<protocol::calculated_opening_price>().value(), -6) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::order_side>(); }) { values[entry + ".bodymessage.businessmessage.assigncopordersmessage.orderside"] = canonical::text(canonical::character(message.template get<protocol::order_side>().value()), ' ', false); }
        for (std::size_t cop_order_index = 0; const auto& cop_order_entry : message.template get<std::array<protocol::cop_order, 15>>()) {
            const std::string cop_order_at = std::string{entry + ".bodymessage.businessmessage.assigncopordersmessage.coporder"} + "[" + std::to_string(cop_order_index++) + "]";
            if constexpr (requires { cop_order_entry.template get<protocol::broker_number>(); }) { values[cop_order_at + ".brokernumber"] = (static_cast<std::uint16_t>(cop_order_entry.template get<protocol::broker_number>().value()) != 0x0U ? canonical::number(cop_order_entry.template get<protocol::broker_number>().value()) : canonical::absent()); }
            if constexpr (requires { cop_order_entry.template get<protocol::order_id>(); }) { values[cop_order_at + ".orderid"] = (static_cast<std::uint64_t>(cop_order_entry.template get<protocol::order_id>().value()) != 0x0ULL ? canonical::number(cop_order_entry.template get<protocol::order_id>().value()) : canonical::absent()); }
        }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.assigncopordersmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::trading_system_time_stamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::assign_cop_no_orders_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.assigncopnoordersmessage";
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".bodymessage.businessmessage.assigncopnoordersmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::calculated_opening_price>(); }) { values[entry + ".bodymessage.businessmessage.assigncopnoordersmessage.calculatedopeningprice"] = (static_cast<std::uint64_t>(message.template get<protocol::calculated_opening_price>().value()) != 0x0ULL ? canonical::scaled(message.template get<protocol::calculated_opening_price>().value(), -6) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.assigncopnoordersmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::trading_system_time_stamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::assign_limit_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.assignlimitmessage";
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".bodymessage.businessmessage.assignlimitmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::calculated_opening_price>(); }) { values[entry + ".bodymessage.businessmessage.assignlimitmessage.calculatedopeningprice"] = (static_cast<std::uint64_t>(message.template get<protocol::calculated_opening_price>().value()) != 0x0ULL ? canonical::scaled(message.template get<protocol::calculated_opening_price>().value(), -6) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::order_side>(); }) { values[entry + ".bodymessage.businessmessage.assignlimitmessage.orderside"] = canonical::text(canonical::character(message.template get<protocol::order_side>().value()), ' ', false); }
        for (std::size_t cop_limit_index = 0; const auto& cop_limit_entry : message.template get<std::array<protocol::cop_limit, 15>>()) {
            const std::string cop_limit_at = std::string{entry + ".bodymessage.businessmessage.assignlimitmessage.coplimit"} + "[" + std::to_string(cop_limit_index++) + "]";
            if constexpr (requires { cop_limit_entry.template get<protocol::broker_number>(); }) { values[cop_limit_at + ".brokernumber"] = (static_cast<std::uint16_t>(cop_limit_entry.template get<protocol::broker_number>().value()) != 0x0U ? canonical::number(cop_limit_entry.template get<protocol::broker_number>().value()) : canonical::absent()); }
            if constexpr (requires { cop_limit_entry.template get<protocol::order_id>(); }) { values[cop_limit_at + ".orderid"] = (static_cast<std::uint64_t>(cop_limit_entry.template get<protocol::order_id>().value()) != 0x0ULL ? canonical::number(cop_limit_entry.template get<protocol::order_id>().value()) : canonical::absent()); }
            if constexpr (requires { cop_limit_entry.template get<protocol::price>(); }) { values[cop_limit_at + ".price"] = (static_cast<std::uint64_t>(cop_limit_entry.template get<protocol::price>().value()) != 0x0ULL ? canonical::scaled(cop_limit_entry.template get<protocol::price>().value(), -6) : canonical::absent()); }
        }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.assignlimitmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::trading_system_time_stamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::market_state_update_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.marketstateupdatemessage";
        if constexpr (requires { message.template get<protocol::market_state>(); }) { values[entry + ".bodymessage.businessmessage.marketstateupdatemessage.marketstate"] = canonical::text(canonical::character(message.template get<protocol::market_state>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::stock_group>(); }) { values[entry + ".bodymessage.businessmessage.marketstateupdatemessage.stockgroup"] = (static_cast<std::uint8_t>(message.template get<protocol::stock_group>().value()) != 0x0U ? canonical::number(message.template get<protocol::stock_group>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.marketstateupdatemessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::trading_system_time_stamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::moc_imbalance_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.mocimbalancemessage";
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".bodymessage.businessmessage.mocimbalancemessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::imbalance_side>(); }) { values[entry + ".bodymessage.businessmessage.mocimbalancemessage.imbalanceside"] = canonical::text(canonical::character(message.template get<protocol::imbalance_side>().value()), ' ', false, {std::string_view(" ", 1), std::string_view("", 0)}); }
        if constexpr (requires { message.template get<protocol::imbalance_volume>(); }) { values[entry + ".bodymessage.businessmessage.mocimbalancemessage.imbalancevolume"] = (static_cast<std::uint32_t>(message.template get<protocol::imbalance_volume>().value()) != 0x0U ? canonical::number(message.template get<protocol::imbalance_volume>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.mocimbalancemessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::trading_system_time_stamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::imbalance_reference_price>(); }) { values[entry + ".bodymessage.businessmessage.mocimbalancemessage.imbalancereferenceprice"] = (static_cast<std::uint64_t>(message.template get<protocol::imbalance_reference_price>().value()) != 0x0ULL ? canonical::scaled(message.template get<protocol::imbalance_reference_price>().value(), -6) : canonical::absent()); }
    }

    void operator()(const protocol::order_booked_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.orderbookedmessage";
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".bodymessage.businessmessage.orderbookedmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::broker_number>(); }) { values[entry + ".bodymessage.businessmessage.orderbookedmessage.brokernumber"] = (static_cast<std::uint16_t>(message.template get<protocol::broker_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::broker_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::order_side>(); }) { values[entry + ".bodymessage.businessmessage.orderbookedmessage.orderside"] = canonical::text(canonical::character(message.template get<protocol::order_side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".bodymessage.businessmessage.orderbookedmessage.orderid"] = (static_cast<std::uint64_t>(message.template get<protocol::order_id>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::order_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".bodymessage.businessmessage.orderbookedmessage.price"] = (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x0ULL ? canonical::scaled(message.template get<protocol::price>().value(), -6) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { values[entry + ".bodymessage.businessmessage.orderbookedmessage.volume"] = (static_cast<std::uint32_t>(message.template get<protocol::volume>().value()) != 0x0U ? canonical::number(message.template get<protocol::volume>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::priority_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.orderbookedmessage.prioritytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::priority_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::priority_time_stamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.orderbookedmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::trading_system_time_stamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::order_booked_terms_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.orderbookedtermsmessage";
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::broker_number>(); }) { values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.brokernumber"] = (static_cast<std::uint16_t>(message.template get<protocol::broker_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::broker_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::order_side>(); }) { values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.orderside"] = canonical::text(canonical::character(message.template get<protocol::order_side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.orderid"] = (static_cast<std::uint64_t>(message.template get<protocol::order_id>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::order_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.price"] = (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x0ULL ? canonical::scaled(message.template get<protocol::price>().value(), -6) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.volume"] = (static_cast<std::uint32_t>(message.template get<protocol::volume>().value()) != 0x0U ? canonical::number(message.template get<protocol::volume>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::non_resident>(); }) { values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.nonresident"] = canonical::text(canonical::character(message.template get<protocol::non_resident>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::settlement_terms>(); }) { values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.settlementterms"] = canonical::text(canonical::character(message.template get<protocol::settlement_terms>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::settlement_date>(); }) { values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.settlementdate"] = (static_cast<std::uint32_t>(message.template get<protocol::settlement_date>().value()) != 0x0U ? canonical::number(message.template get<protocol::settlement_date>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::priority_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.prioritytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::priority_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::priority_time_stamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.orderbookedtermsmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::trading_system_time_stamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::order_cancelled_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.ordercancelledmessage";
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".bodymessage.businessmessage.ordercancelledmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::broker_number>(); }) { values[entry + ".bodymessage.businessmessage.ordercancelledmessage.brokernumber"] = (static_cast<std::uint16_t>(message.template get<protocol::broker_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::broker_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::order_side>(); }) { values[entry + ".bodymessage.businessmessage.ordercancelledmessage.orderside"] = canonical::text(canonical::character(message.template get<protocol::order_side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".bodymessage.businessmessage.ordercancelledmessage.orderid"] = (static_cast<std::uint64_t>(message.template get<protocol::order_id>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::order_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.ordercancelledmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::trading_system_time_stamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::order_cancelled_terms_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.ordercancelledtermsmessage";
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".bodymessage.businessmessage.ordercancelledtermsmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::broker_number>(); }) { values[entry + ".bodymessage.businessmessage.ordercancelledtermsmessage.brokernumber"] = (static_cast<std::uint16_t>(message.template get<protocol::broker_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::broker_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::order_side>(); }) { values[entry + ".bodymessage.businessmessage.ordercancelledtermsmessage.orderside"] = canonical::text(canonical::character(message.template get<protocol::order_side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".bodymessage.businessmessage.ordercancelledtermsmessage.orderid"] = (static_cast<std::uint64_t>(message.template get<protocol::order_id>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::order_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.ordercancelledtermsmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::trading_system_time_stamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::order_price_time_assigned_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.orderpricetimeassignedmessage";
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::broker_number>(); }) { values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.brokernumber"] = (static_cast<std::uint16_t>(message.template get<protocol::broker_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::broker_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::order_side>(); }) { values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.orderside"] = canonical::text(canonical::character(message.template get<protocol::order_side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.orderid"] = (static_cast<std::uint64_t>(message.template get<protocol::order_id>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::order_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.price"] = (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x0ULL ? canonical::scaled(message.template get<protocol::price>().value(), -6) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.volume"] = (static_cast<std::uint32_t>(message.template get<protocol::volume>().value()) != 0x0U ? canonical::number(message.template get<protocol::volume>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::priority_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.prioritytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::priority_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::priority_time_stamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.orderpricetimeassignedmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::trading_system_time_stamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::order_price_time_assigned_terms_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.orderpricetimeassignedtermsmessage";
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::broker_number>(); }) { values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.brokernumber"] = (static_cast<std::uint16_t>(message.template get<protocol::broker_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::broker_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::order_side>(); }) { values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.orderside"] = canonical::text(canonical::character(message.template get<protocol::order_side>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.orderid"] = (static_cast<std::uint64_t>(message.template get<protocol::order_id>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::order_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.price"] = (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x0ULL ? canonical::scaled(message.template get<protocol::price>().value(), -6) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.volume"] = (static_cast<std::uint32_t>(message.template get<protocol::volume>().value()) != 0x0U ? canonical::number(message.template get<protocol::volume>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::priority_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.prioritytimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::priority_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::priority_time_stamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.orderpricetimeassignedtermsmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::trading_system_time_stamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::stock_status_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.stockstatusmessage";
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".bodymessage.businessmessage.stockstatusmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::comment>(); }) { values[entry + ".bodymessage.businessmessage.stockstatusmessage.comment"] = canonical::text(std::string(message.template get<protocol::comment>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::stock_state>(); }) { values[entry + ".bodymessage.businessmessage.stockstatusmessage.stockstate"] = canonical::text(std::string(message.template get<protocol::stock_state>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.stockstatusmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::trading_system_time_stamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::trade_report_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.tradereportmessage";
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".bodymessage.businessmessage.tradereportmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trade_number>(); }) { values[entry + ".bodymessage.businessmessage.tradereportmessage.tradenumber"] = (static_cast<std::uint32_t>(message.template get<protocol::trade_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::trade_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".bodymessage.businessmessage.tradereportmessage.price"] = (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x0ULL ? canonical::scaled(message.template get<protocol::price>().value(), -6) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { values[entry + ".bodymessage.businessmessage.tradereportmessage.volume"] = (static_cast<std::uint32_t>(message.template get<protocol::volume>().value()) != 0x0U ? canonical::number(message.template get<protocol::volume>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::buy_broker_number>(); }) { values[entry + ".bodymessage.businessmessage.tradereportmessage.buybrokernumber"] = (static_cast<std::uint16_t>(message.template get<protocol::buy_broker_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::buy_broker_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::buy_order_id>(); }) { values[entry + ".bodymessage.businessmessage.tradereportmessage.buyorderid"] = (static_cast<std::uint64_t>(message.template get<protocol::buy_order_id>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::buy_order_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::buy_display_volume>(); }) { values[entry + ".bodymessage.businessmessage.tradereportmessage.buydisplayvolume"] = (static_cast<std::uint32_t>(message.template get<protocol::buy_display_volume>().value()) != 0x0U ? canonical::number(message.template get<protocol::buy_display_volume>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::sell_broker_number>(); }) { values[entry + ".bodymessage.businessmessage.tradereportmessage.sellbrokernumber"] = (static_cast<std::uint16_t>(message.template get<protocol::sell_broker_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::sell_broker_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::sell_order_id>(); }) { values[entry + ".bodymessage.businessmessage.tradereportmessage.sellorderid"] = (static_cast<std::uint64_t>(message.template get<protocol::sell_order_id>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::sell_order_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::sell_display_volume>(); }) { values[entry + ".bodymessage.businessmessage.tradereportmessage.selldisplayvolume"] = (static_cast<std::uint32_t>(message.template get<protocol::sell_display_volume>().value()) != 0x0U ? canonical::number(message.template get<protocol::sell_display_volume>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::bypass>(); }) { values[entry + ".bodymessage.businessmessage.tradereportmessage.bypass"] = canonical::text(canonical::character(message.template get<protocol::bypass>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trade_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.tradereportmessage.tradetimestamp"] = (static_cast<std::uint32_t>(message.template get<protocol::trade_time_stamp>().value()) != 0x0U ? canonical::number(message.template get<protocol::trade_time_stamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::cross_type>(); }) { values[entry + ".bodymessage.businessmessage.tradereportmessage.crosstype"] = canonical::text(canonical::character(message.template get<protocol::cross_type>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.tradereportmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::trading_system_time_stamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::trade_report_terms_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.tradereporttermsmessage";
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trade_number>(); }) { values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.tradenumber"] = (static_cast<std::uint32_t>(message.template get<protocol::trade_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::trade_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.price"] = (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x0ULL ? canonical::scaled(message.template get<protocol::price>().value(), -6) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.volume"] = (static_cast<std::uint32_t>(message.template get<protocol::volume>().value()) != 0x0U ? canonical::number(message.template get<protocol::volume>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::buy_broker_number>(); }) { values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.buybrokernumber"] = (static_cast<std::uint16_t>(message.template get<protocol::buy_broker_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::buy_broker_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::buy_order_id>(); }) { values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.buyorderid"] = (static_cast<std::uint64_t>(message.template get<protocol::buy_order_id>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::buy_order_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::buy_display_volume>(); }) { values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.buydisplayvolume"] = (static_cast<std::uint32_t>(message.template get<protocol::buy_display_volume>().value()) != 0x0U ? canonical::number(message.template get<protocol::buy_display_volume>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::sell_broker_number>(); }) { values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.sellbrokernumber"] = (static_cast<std::uint16_t>(message.template get<protocol::sell_broker_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::sell_broker_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::sell_order_id>(); }) { values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.sellorderid"] = (static_cast<std::uint64_t>(message.template get<protocol::sell_order_id>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::sell_order_id>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::sell_display_volume>(); }) { values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.selldisplayvolume"] = (static_cast<std::uint32_t>(message.template get<protocol::sell_display_volume>().value()) != 0x0U ? canonical::number(message.template get<protocol::sell_display_volume>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trade_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.tradetimestamp"] = (static_cast<std::uint32_t>(message.template get<protocol::trade_time_stamp>().value()) != 0x0U ? canonical::number(message.template get<protocol::trade_time_stamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::non_resident>(); }) { values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.nonresident"] = canonical::text(canonical::character(message.template get<protocol::non_resident>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::settlement_terms>(); }) { values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.settlementterms"] = canonical::text(canonical::character(message.template get<protocol::settlement_terms>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::settlement_date>(); }) { values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.settlementdate"] = (static_cast<std::uint32_t>(message.template get<protocol::settlement_date>().value()) != 0x0U ? canonical::number(message.template get<protocol::settlement_date>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::cross_type>(); }) { values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.crosstype"] = canonical::text(canonical::character(message.template get<protocol::cross_type>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.tradereporttermsmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::trading_system_time_stamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::trade_cancelled_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.tradecancelledmessage";
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".bodymessage.businessmessage.tradecancelledmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trade_number>(); }) { values[entry + ".bodymessage.businessmessage.tradecancelledmessage.tradenumber"] = (static_cast<std::uint32_t>(message.template get<protocol::trade_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::trade_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.tradecancelledmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::trading_system_time_stamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::trade_cancelled_terms_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.tradecancelledtermsmessage";
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".bodymessage.businessmessage.tradecancelledtermsmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trade_number>(); }) { values[entry + ".bodymessage.businessmessage.tradecancelledtermsmessage.tradenumber"] = (static_cast<std::uint32_t>(message.template get<protocol::trade_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::trade_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.tradecancelledtermsmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::trading_system_time_stamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::trade_correction_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.tradecorrectionmessage";
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trade_number>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.tradenumber"] = (static_cast<std::uint32_t>(message.template get<protocol::trade_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::trade_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.price"] = (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x0ULL ? canonical::scaled(message.template get<protocol::price>().value(), -6) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.volume"] = (static_cast<std::uint32_t>(message.template get<protocol::volume>().value()) != 0x0U ? canonical::number(message.template get<protocol::volume>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::buy_broker_number>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.buybrokernumber"] = (static_cast<std::uint16_t>(message.template get<protocol::buy_broker_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::buy_broker_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::sell_broker_number>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.sellbrokernumber"] = (static_cast<std::uint16_t>(message.template get<protocol::sell_broker_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::sell_broker_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::initiated_by>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.initiatedby"] = canonical::text(canonical::character(message.template get<protocol::initiated_by>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::orig_trade_number>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.origtradenumber"] = (static_cast<std::uint32_t>(message.template get<protocol::orig_trade_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::orig_trade_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::bypass>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.bypass"] = canonical::text(canonical::character(message.template get<protocol::bypass>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trade_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.tradetimestamp"] = (static_cast<std::uint32_t>(message.template get<protocol::trade_time_stamp>().value()) != 0x0U ? canonical::number(message.template get<protocol::trade_time_stamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::cross_type>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.crosstype"] = canonical::text(canonical::character(message.template get<protocol::cross_type>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectionmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::trading_system_time_stamp>().value()) : canonical::absent()); }
    }

    void operator()(const protocol::trade_correction_terms_message& message) {
        values[entry + ".bodymessage.businessmessage"] = "packet.packetbody.businessbodies.body.bodymessage.businessmessage.tradecorrectiontermsmessage";
        if constexpr (requires { message.template get<protocol::symbol>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.symbol"] = canonical::text(std::string(message.template get<protocol::symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trade_number>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.tradenumber"] = (static_cast<std::uint32_t>(message.template get<protocol::trade_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::trade_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.price"] = (static_cast<std::uint64_t>(message.template get<protocol::price>().value()) != 0x0ULL ? canonical::scaled(message.template get<protocol::price>().value(), -6) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.volume"] = (static_cast<std::uint32_t>(message.template get<protocol::volume>().value()) != 0x0U ? canonical::number(message.template get<protocol::volume>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::buy_broker_number>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.buybrokernumber"] = (static_cast<std::uint16_t>(message.template get<protocol::buy_broker_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::buy_broker_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::sell_broker_number>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.sellbrokernumber"] = (static_cast<std::uint16_t>(message.template get<protocol::sell_broker_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::sell_broker_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::initiated_by>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.initiatedby"] = canonical::text(canonical::character(message.template get<protocol::initiated_by>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::orig_trade_number>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.origtradenumber"] = (static_cast<std::uint32_t>(message.template get<protocol::orig_trade_number>().value()) != 0x0U ? canonical::number(message.template get<protocol::orig_trade_number>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::trade_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.tradetimestamp"] = (static_cast<std::uint32_t>(message.template get<protocol::trade_time_stamp>().value()) != 0x0U ? canonical::number(message.template get<protocol::trade_time_stamp>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::non_resident>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.nonresident"] = canonical::text(canonical::character(message.template get<protocol::non_resident>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::settlement_terms>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.settlementterms"] = canonical::text(canonical::character(message.template get<protocol::settlement_terms>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::settlement_date>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.settlementdate"] = (static_cast<std::uint32_t>(message.template get<protocol::settlement_date>().value()) != 0x0U ? canonical::number(message.template get<protocol::settlement_date>().value()) : canonical::absent()); }
        if constexpr (requires { message.template get<protocol::cross_type>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.crosstype"] = canonical::text(canonical::character(message.template get<protocol::cross_type>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trading_system_time_stamp>(); }) { values[entry + ".bodymessage.businessmessage.tradecorrectiontermsmessage.tradingsystemtimestamp"] = (static_cast<std::uint64_t>(message.template get<protocol::trading_system_time_stamp>().value()) != 0x0ULL ? canonical::number(message.template get<protocol::trading_system_time_stamp>().value()) : canonical::absent()); }
    }
};

// The values the Tmp reading reads from one datagram, by indexed address. A datagram it cannot read
// is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::parse_packet(frame.payload, frame.payload_len, reader);
    } catch (const std::exception& error) {
        reader.values["(does not decode)"] = error.what();
    }

    return reader.values;
}

// Read each datagram of a sample with Tmp and hold it to the model's values
int check(const char* name, const char* capture, const char* expected) {
    const char* packets = std::getenv("OMI_PACKETS_DIR");

    if (packets == nullptr) {
        std::printf("FAIL: OMI_PACKETS_DIR is not set\n");
        return 1;
    }

    const auto model = canonical::load(canonical::root() + "/" + expected);
    std::vector<std::pair<std::string, std::int64_t>> sources;
    sources.emplace_back(std::string{packets} + "/" + capture, 0);

    packet::PcapIterator captures(sources);
    std::size_t datagram = 0;
    int differences = 0;

    while (captures.advance()) {
        const packet::Frame frame(captures.data(), captures.length());

        if (!frame.valid() || !frame.is_udp()) { continue; }

        if (datagram >= model.size()) {
            std::printf("FAIL %s: more datagrams than the model read\n", name);
            return 1;
        }

        differences += canonical::compare(name, datagram, model[datagram], read(frame));
        ++datagram;
    }

    if (datagram != model.size()) {
        std::printf("FAIL %s: %zu datagrams, the model read %zu\n", name, datagram, model.size());
        return 1;
    }

    if (differences == 0) {
        std::printf("ok   %s: %zu datagrams\n", name, datagram);
    }

    return differences == 0 ? 0 : 1;
}

}

int main() {
    std::printf("== Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10 (tmp values)\n");
    int failures = 0;
    failures += check("AssignCopOrdersMessage", "Tmx/Tsx.QuantumFeedLevel2.Xmt.v2.10/AssignCopOrdersMessage.pcap", "tmx/tsx/quantumfeedlevel2/xmt/v2.10/AssignCopOrdersMessage.values");
    failures += check("OrderBookedMessage", "Tmx/Tsx.QuantumFeedLevel2.Xmt.v2.10/OrderBookedMessage.pcap", "tmx/tsx/quantumfeedlevel2/xmt/v2.10/OrderBookedMessage.values");
    failures += check("OrderCancelledMessage", "Tmx/Tsx.QuantumFeedLevel2.Xmt.v2.10/OrderCancelledMessage.pcap", "tmx/tsx/quantumfeedlevel2/xmt/v2.10/OrderCancelledMessage.values");
    failures += check("TradeReportMessage", "Tmx/Tsx.QuantumFeedLevel2.Xmt.v2.10/TradeReportMessage.pcap", "tmx/tsx/quantumfeedlevel2/xmt/v2.10/TradeReportMessage.values");
    return failures == 0 ? 0 : 1;
}
