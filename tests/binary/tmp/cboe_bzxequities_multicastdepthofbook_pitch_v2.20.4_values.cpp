// Cboe.BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4 canonical values, through the Tmp header: every value the Tmp reading hands
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
#include "cpp/binary/tmp/cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/cboe_bzxequities_multicastdepthofbook_pitch_v2_20_4.hpp"

// Cboe BzxEquities MulticastDepthOfBook Pitch 2.20.4: the reading of its packets, through its Template Meta Programming header
namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

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
    if (static_cast<bool>(tmp::rule(message_type_) == 0x20)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& time_message_ = tmp::read<time_message>(data + offset, bound - offset, handler); offset += time_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x97)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& unit_clear_message_ = tmp::read<unit_clear_message>(data + offset, bound - offset, handler); offset += unit_clear_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x21)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_long_message_ = tmp::read<add_order_long_message>(data + offset, bound - offset, handler); offset += add_order_long_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x22)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_short_message_ = tmp::read<add_order_short_message>(data + offset, bound - offset, handler); offset += add_order_short_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x2F)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& add_order_expanded_message_ = tmp::read<add_order_expanded_message>(data + offset, bound - offset, handler); offset += add_order_expanded_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x23)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_executed_message_ = tmp::read<order_executed_message>(data + offset, bound - offset, handler); offset += order_executed_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x24)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& order_executed_at_price_size_message_ = tmp::read<order_executed_at_price_size_message>(data + offset, bound - offset, handler); offset += order_executed_at_price_size_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x25)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& reduce_size_long_message_ = tmp::read<reduce_size_long_message>(data + offset, bound - offset, handler); offset += reduce_size_long_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x26)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& reduce_size_short_message_ = tmp::read<reduce_size_short_message>(data + offset, bound - offset, handler); offset += reduce_size_short_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x27)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& modify_order_long_message_ = tmp::read<modify_order_long_message>(data + offset, bound - offset, handler); offset += modify_order_long_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x28)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& modify_order_short_message_ = tmp::read<modify_order_short_message>(data + offset, bound - offset, handler); offset += modify_order_short_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x29)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& delete_order_message_ = tmp::read<delete_order_message>(data + offset, bound - offset, handler); offset += delete_order_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x2A)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_long_message_ = tmp::read<trade_long_message>(data + offset, bound - offset, handler); offset += trade_long_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x2B)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_short_message_ = tmp::read<trade_short_message>(data + offset, bound - offset, handler); offset += trade_short_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x30)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_expanded_message_ = tmp::read<trade_expanded_message>(data + offset, bound - offset, handler); offset += trade_expanded_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x2C)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trade_break_message_ = tmp::read<trade_break_message>(data + offset, bound - offset, handler); offset += trade_break_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x2D)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& end_of_session_message_ = tmp::read<end_of_session_message>(data + offset, bound - offset, handler); offset += end_of_session_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x2E)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& symbol_mapping_message_ = tmp::read<symbol_mapping_message>(data + offset, bound - offset, handler); offset += symbol_mapping_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x31)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& trading_status_message_ = tmp::read<trading_status_message>(data + offset, bound - offset, handler); offset += trading_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x95)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& auction_update_message_ = tmp::read<auction_update_message>(data + offset, bound - offset, handler); offset += auction_update_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x96)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& auction_summary_message_ = tmp::read<auction_summary_message>(data + offset, bound - offset, handler); offset += auction_summary_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 0x98)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& retail_price_improvement_message_ = tmp::read<retail_price_improvement_message>(data + offset, bound - offset, handler); offset += retail_price_improvement_message::size;
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
            const std::size_t end = static_cast<std::size_t>(static_cast<std::int64_t>(bound));
            tmp::require(end, bound);
            while (offset < end) {
                [[maybe_unused]] const std::size_t bound = end;
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
    [[maybe_unused]] const auto& packet_header_ = tmp::read<packet_header>(data + offset, bound - offset, handler); offset += packet_header::size;
    offset += parse_messages(data + offset, bound - offset, handler, packet_header_.template get<message_count>());
    return offset;
}


} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4

namespace protocol = ::cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4;

namespace {

// The handler the reading hands each type laid over a datagram's bytes to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;
    std::string entry;

    // a type this test prints no values of
    template <typename T>
    void operator()(const T&) {}

    void operator()(const protocol::packet_header& header) {
        if constexpr (requires { header.template get<protocol::length_type>(); }) { values["packet.packetheader.length"] = canonical::number(header.template get<protocol::length_type>().value()); }
        if constexpr (requires { header.template get<protocol::message_count>(); }) { values["packet.packetheader.messagecount"] = canonical::number(header.template get<protocol::message_count>().value()); }
        if constexpr (requires { header.template get<protocol::unit>(); }) { values["packet.packetheader.unit"] = canonical::number(header.template get<protocol::unit>().value()); }
        if constexpr (requires { header.template get<protocol::sequence>(); }) { values["packet.packetheader.sequence"] = canonical::number(header.template get<protocol::sequence>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        entry = "packet.messages.message[" + std::to_string(index++) + "]";
        if constexpr (requires { header.template get<protocol::message_length>(); }) { values[entry + ".messageheader.messagelength"] = canonical::number(header.template get<protocol::message_length>().value()); }
        if constexpr (requires { header.template get<protocol::message_type>(); }) { values[entry + ".messageheader.messagetype"] = canonical::number(header.template get<protocol::message_type>().value()); }
    }

    void operator()(const protocol::time_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.timemessage";
        if constexpr (requires { message.template get<protocol::time>(); }) { values[entry + ".payload.timemessage.time"] = canonical::number(message.template get<protocol::time>().value()); }
    }

    void operator()(const protocol::unit_clear_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.unitclearmessage";
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { values[entry + ".payload.unitclearmessage.timeoffset"] = canonical::number(message.template get<protocol::time_offset>().value()); }
    }

    void operator()(const protocol::add_order_long_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.addorderlongmessage";
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { values[entry + ".payload.addorderlongmessage.timeoffset"] = canonical::number(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.addorderlongmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::side_indicator>(); }) { values[entry + ".payload.addorderlongmessage.sideindicator"] = canonical::text(canonical::character(message.template get<protocol::side_indicator>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::quantity_binary_4>(); }) { values[entry + ".payload.addorderlongmessage.quantitybinary4"] = canonical::number(message.template get<protocol::quantity_binary_4>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_short>(); }) { values[entry + ".payload.addorderlongmessage.symbolshort"] = canonical::text(std::string(message.template get<protocol::symbol_short>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::price_binary_long_price_8>(); }) { values[entry + ".payload.addorderlongmessage.pricebinarylongprice8"] = canonical::scaled(message.template get<protocol::price_binary_long_price_8>().value(), -4); }
    }

    void operator()(const protocol::add_order_short_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.addordershortmessage";
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { values[entry + ".payload.addordershortmessage.timeoffset"] = canonical::number(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.addordershortmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::side_indicator>(); }) { values[entry + ".payload.addordershortmessage.sideindicator"] = canonical::text(canonical::character(message.template get<protocol::side_indicator>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::quantity_binary_2>(); }) { values[entry + ".payload.addordershortmessage.quantitybinary2"] = canonical::number(message.template get<protocol::quantity_binary_2>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_short>(); }) { values[entry + ".payload.addordershortmessage.symbolshort"] = canonical::text(std::string(message.template get<protocol::symbol_short>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::price_binary_short_price_2>(); }) { values[entry + ".payload.addordershortmessage.pricebinaryshortprice2"] = canonical::scaled(message.template get<protocol::price_binary_short_price_2>().value(), -2); }
    }

    void operator()(const protocol::add_order_expanded_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.addorderexpandedmessage";
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { values[entry + ".payload.addorderexpandedmessage.timeoffset"] = canonical::number(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.addorderexpandedmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::side_indicator>(); }) { values[entry + ".payload.addorderexpandedmessage.sideindicator"] = canonical::text(canonical::character(message.template get<protocol::side_indicator>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::quantity_binary_4>(); }) { values[entry + ".payload.addorderexpandedmessage.quantitybinary4"] = canonical::number(message.template get<protocol::quantity_binary_4>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_long>(); }) { values[entry + ".payload.addorderexpandedmessage.symbollong"] = canonical::text(std::string(message.template get<protocol::symbol_long>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::price_binary_long_price_8>(); }) { values[entry + ".payload.addorderexpandedmessage.pricebinarylongprice8"] = canonical::scaled(message.template get<protocol::price_binary_long_price_8>().value(), -4); }
        if constexpr (requires { message.template get<protocol::participant_id>(); }) { values[entry + ".payload.addorderexpandedmessage.participantid"] = canonical::text(std::string(message.template get<protocol::participant_id>().value()), ' ', false); }
    }

    void operator()(const protocol::order_executed_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedmessage";
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { values[entry + ".payload.orderexecutedmessage.timeoffset"] = canonical::number(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.orderexecutedmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { values[entry + ".payload.orderexecutedmessage.executedquantity"] = canonical::number(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::execution_id>(); }) { values[entry + ".payload.orderexecutedmessage.executionid"] = canonical::number(message.template get<protocol::execution_id>().value()); }
    }

    void operator()(const protocol::order_executed_at_price_size_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.orderexecutedatpricesizemessage";
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { values[entry + ".payload.orderexecutedatpricesizemessage.timeoffset"] = canonical::number(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.orderexecutedatpricesizemessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::executed_quantity>(); }) { values[entry + ".payload.orderexecutedatpricesizemessage.executedquantity"] = canonical::number(message.template get<protocol::executed_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::remaining_quantity>(); }) { values[entry + ".payload.orderexecutedatpricesizemessage.remainingquantity"] = canonical::number(message.template get<protocol::remaining_quantity>().value()); }
        if constexpr (requires { message.template get<protocol::execution_id>(); }) { values[entry + ".payload.orderexecutedatpricesizemessage.executionid"] = canonical::number(message.template get<protocol::execution_id>().value()); }
        if constexpr (requires { message.template get<protocol::price_binary_long_price_8>(); }) { values[entry + ".payload.orderexecutedatpricesizemessage.pricebinarylongprice8"] = canonical::scaled(message.template get<protocol::price_binary_long_price_8>().value(), -4); }
    }

    void operator()(const protocol::reduce_size_long_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.reducesizelongmessage";
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { values[entry + ".payload.reducesizelongmessage.timeoffset"] = canonical::number(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.reducesizelongmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::canceled_quantity_binary_4>(); }) { values[entry + ".payload.reducesizelongmessage.canceledquantitybinary4"] = canonical::number(message.template get<protocol::canceled_quantity_binary_4>().value()); }
    }

    void operator()(const protocol::reduce_size_short_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.reducesizeshortmessage";
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { values[entry + ".payload.reducesizeshortmessage.timeoffset"] = canonical::number(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.reducesizeshortmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::canceled_quantity_binary_2>(); }) { values[entry + ".payload.reducesizeshortmessage.canceledquantitybinary2"] = canonical::number(message.template get<protocol::canceled_quantity_binary_2>().value()); }
    }

    void operator()(const protocol::modify_order_long_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.modifyorderlongmessage";
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { values[entry + ".payload.modifyorderlongmessage.timeoffset"] = canonical::number(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.modifyorderlongmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::quantity_binary_4>(); }) { values[entry + ".payload.modifyorderlongmessage.quantitybinary4"] = canonical::number(message.template get<protocol::quantity_binary_4>().value()); }
        if constexpr (requires { message.template get<protocol::price_binary_long_price_8>(); }) { values[entry + ".payload.modifyorderlongmessage.pricebinarylongprice8"] = canonical::scaled(message.template get<protocol::price_binary_long_price_8>().value(), -4); }
    }

    void operator()(const protocol::modify_order_short_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.modifyordershortmessage";
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { values[entry + ".payload.modifyordershortmessage.timeoffset"] = canonical::number(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.modifyordershortmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::quantity_binary_2>(); }) { values[entry + ".payload.modifyordershortmessage.quantitybinary2"] = canonical::number(message.template get<protocol::quantity_binary_2>().value()); }
        if constexpr (requires { message.template get<protocol::price_binary_short_price_2>(); }) { values[entry + ".payload.modifyordershortmessage.pricebinaryshortprice2"] = canonical::scaled(message.template get<protocol::price_binary_short_price_2>().value(), -2); }
    }

    void operator()(const protocol::delete_order_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.deleteordermessage";
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { values[entry + ".payload.deleteordermessage.timeoffset"] = canonical::number(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.deleteordermessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
    }

    void operator()(const protocol::trade_long_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.tradelongmessage";
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { values[entry + ".payload.tradelongmessage.timeoffset"] = canonical::number(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.tradelongmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::side_indicator>(); }) { values[entry + ".payload.tradelongmessage.sideindicator"] = canonical::text(canonical::character(message.template get<protocol::side_indicator>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::quantity_binary_4>(); }) { values[entry + ".payload.tradelongmessage.quantitybinary4"] = canonical::number(message.template get<protocol::quantity_binary_4>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_short>(); }) { values[entry + ".payload.tradelongmessage.symbolshort"] = canonical::text(std::string(message.template get<protocol::symbol_short>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::price_binary_long_price_8>(); }) { values[entry + ".payload.tradelongmessage.pricebinarylongprice8"] = canonical::scaled(message.template get<protocol::price_binary_long_price_8>().value(), -4); }
        if constexpr (requires { message.template get<protocol::execution_id>(); }) { values[entry + ".payload.tradelongmessage.executionid"] = canonical::number(message.template get<protocol::execution_id>().value()); }
    }

    void operator()(const protocol::trade_short_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.tradeshortmessage";
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { values[entry + ".payload.tradeshortmessage.timeoffset"] = canonical::number(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.tradeshortmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::side_indicator>(); }) { values[entry + ".payload.tradeshortmessage.sideindicator"] = canonical::text(canonical::character(message.template get<protocol::side_indicator>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::quantity_binary_2>(); }) { values[entry + ".payload.tradeshortmessage.quantitybinary2"] = canonical::number(message.template get<protocol::quantity_binary_2>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_short>(); }) { values[entry + ".payload.tradeshortmessage.symbolshort"] = canonical::text(std::string(message.template get<protocol::symbol_short>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::price_binary_short_price_2>(); }) { values[entry + ".payload.tradeshortmessage.pricebinaryshortprice2"] = canonical::scaled(message.template get<protocol::price_binary_short_price_2>().value(), -2); }
        if constexpr (requires { message.template get<protocol::execution_id>(); }) { values[entry + ".payload.tradeshortmessage.executionid"] = canonical::number(message.template get<protocol::execution_id>().value()); }
    }

    void operator()(const protocol::trade_expanded_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.tradeexpandedmessage";
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { values[entry + ".payload.tradeexpandedmessage.timeoffset"] = canonical::number(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::order_id>(); }) { values[entry + ".payload.tradeexpandedmessage.orderid"] = canonical::number(message.template get<protocol::order_id>().value()); }
        if constexpr (requires { message.template get<protocol::side_indicator>(); }) { values[entry + ".payload.tradeexpandedmessage.sideindicator"] = canonical::text(canonical::character(message.template get<protocol::side_indicator>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::quantity_binary_4>(); }) { values[entry + ".payload.tradeexpandedmessage.quantitybinary4"] = canonical::number(message.template get<protocol::quantity_binary_4>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_long>(); }) { values[entry + ".payload.tradeexpandedmessage.symbollong"] = canonical::text(std::string(message.template get<protocol::symbol_long>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::price_binary_long_price_8>(); }) { values[entry + ".payload.tradeexpandedmessage.pricebinarylongprice8"] = canonical::scaled(message.template get<protocol::price_binary_long_price_8>().value(), -4); }
        if constexpr (requires { message.template get<protocol::execution_id>(); }) { values[entry + ".payload.tradeexpandedmessage.executionid"] = canonical::number(message.template get<protocol::execution_id>().value()); }
    }

    void operator()(const protocol::trade_break_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.tradebreakmessage";
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { values[entry + ".payload.tradebreakmessage.timeoffset"] = canonical::number(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::execution_id>(); }) { values[entry + ".payload.tradebreakmessage.executionid"] = canonical::number(message.template get<protocol::execution_id>().value()); }
    }

    void operator()(const protocol::end_of_session_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.endofsessionmessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.endofsessionmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
    }

    void operator()(const protocol::symbol_mapping_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.symbolmappingmessage";
        if constexpr (requires { message.template get<protocol::feed_symbol>(); }) { values[entry + ".payload.symbolmappingmessage.feedsymbol"] = canonical::text(std::string(message.template get<protocol::feed_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::osi_symbol>(); }) { values[entry + ".payload.symbolmappingmessage.osisymbol"] = canonical::text(std::string(message.template get<protocol::osi_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::symbol_condition>(); }) { values[entry + ".payload.symbolmappingmessage.symbolcondition"] = canonical::text(canonical::character(message.template get<protocol::symbol_condition>().value()), ' ', false); }
    }

    void operator()(const protocol::trading_status_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.tradingstatusmessage";
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { values[entry + ".payload.tradingstatusmessage.timeoffset"] = canonical::number(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_long>(); }) { values[entry + ".payload.tradingstatusmessage.symbollong"] = canonical::text(std::string(message.template get<protocol::symbol_long>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::trading_status>(); }) { values[entry + ".payload.tradingstatusmessage.tradingstatus"] = canonical::text(canonical::character(message.template get<protocol::trading_status>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::reg_sho_action>(); }) { values[entry + ".payload.tradingstatusmessage.regshoaction"] = canonical::text(canonical::character(message.template get<protocol::reg_sho_action>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::reserved_1>(); }) { values[entry + ".payload.tradingstatusmessage.reserved1"] = canonical::text(canonical::character(message.template get<protocol::reserved_1>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::second_reserved_1>(); }) { values[entry + ".payload.tradingstatusmessage.secondreserved1"] = canonical::text(canonical::character(message.template get<protocol::second_reserved_1>().value()), ' ', false); }
    }

    void operator()(const protocol::auction_update_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.auctionupdatemessage";
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { values[entry + ".payload.auctionupdatemessage.timeoffset"] = canonical::number(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::stock_symbol>(); }) { values[entry + ".payload.auctionupdatemessage.stocksymbol"] = canonical::text(std::string(message.template get<protocol::stock_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::auction_type>(); }) { values[entry + ".payload.auctionupdatemessage.auctiontype"] = canonical::text(canonical::character(message.template get<protocol::auction_type>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::reference_price>(); }) { values[entry + ".payload.auctionupdatemessage.referenceprice"] = canonical::number(message.template get<protocol::reference_price>().value()); }
        if constexpr (requires { message.template get<protocol::buy_shares>(); }) { values[entry + ".payload.auctionupdatemessage.buyshares"] = canonical::number(message.template get<protocol::buy_shares>().value()); }
        if constexpr (requires { message.template get<protocol::sell_shares>(); }) { values[entry + ".payload.auctionupdatemessage.sellshares"] = canonical::number(message.template get<protocol::sell_shares>().value()); }
        if constexpr (requires { message.template get<protocol::indicative_price>(); }) { values[entry + ".payload.auctionupdatemessage.indicativeprice"] = canonical::number(message.template get<protocol::indicative_price>().value()); }
        if constexpr (requires { message.template get<protocol::auction_only_price>(); }) { values[entry + ".payload.auctionupdatemessage.auctiononlyprice"] = canonical::number(message.template get<protocol::auction_only_price>().value()); }
    }

    void operator()(const protocol::auction_summary_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.auctionsummarymessage";
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { values[entry + ".payload.auctionsummarymessage.timeoffset"] = canonical::number(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::stock_symbol>(); }) { values[entry + ".payload.auctionsummarymessage.stocksymbol"] = canonical::text(std::string(message.template get<protocol::stock_symbol>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::auction_type>(); }) { values[entry + ".payload.auctionsummarymessage.auctiontype"] = canonical::text(canonical::character(message.template get<protocol::auction_type>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::price_binary_8>(); }) { values[entry + ".payload.auctionsummarymessage.pricebinary8"] = canonical::number(message.template get<protocol::price_binary_8>().value()); }
        if constexpr (requires { message.template get<protocol::shares>(); }) { values[entry + ".payload.auctionsummarymessage.shares"] = canonical::number(message.template get<protocol::shares>().value()); }
    }

    void operator()(const protocol::retail_price_improvement_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.retailpriceimprovementmessage";
        if constexpr (requires { message.template get<protocol::time_offset>(); }) { values[entry + ".payload.retailpriceimprovementmessage.timeoffset"] = canonical::number(message.template get<protocol::time_offset>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_long>(); }) { values[entry + ".payload.retailpriceimprovementmessage.symbollong"] = canonical::text(std::string(message.template get<protocol::symbol_long>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::retail_price_improvement>(); }) { values[entry + ".payload.retailpriceimprovementmessage.retailpriceimprovement"] = canonical::text(canonical::character(message.template get<protocol::retail_price_improvement>().value()), ' ', false); }
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
    std::printf("== Cboe.BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4 (tmp values)\n");
    int failures = 0;
    failures += check("AddOrderLongMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4/AddOrderLongMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/AddOrderLongMessage.values");
    failures += check("AddOrderShortMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4/AddOrderShortMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/AddOrderShortMessage.values");
    failures += check("DeleteOrderMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4/DeleteOrderMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/DeleteOrderMessage.values");
    failures += check("ModifyOrderLongMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4/ModifyOrderLongMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/ModifyOrderLongMessage.values");
    failures += check("ModifyOrderShortMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4/ModifyOrderShortMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/ModifyOrderShortMessage.values");
    failures += check("OrderExecutedMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4/OrderExecutedMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/OrderExecutedMessage.values");
    failures += check("ReduceSizeShortMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4/ReduceSizeShortMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/ReduceSizeShortMessage.values");
    failures += check("TimeMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4/TimeMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/TimeMessage.values");
    failures += check("TradeLongMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4/TradeLongMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/TradeLongMessage.values");
    failures += check("TradeShortMessage", "Cboe/BzxEquities.MulticastDepthOfBook.Pitch.v2.20.4/TradeShortMessage.pcap", "cboe/bzxequities/multicastdepthofbook/pitch/v2.20.4/TradeShortMessage.values");
    return failures == 0 ? 0 : 1;
}
