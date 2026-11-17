// Nyse.AmexOptions.ComplexFeed.Xdp.v1.3.a canonical values, through the Tmp header: every value the Tmp reading hands
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
#include "cpp/binary/tmp/nyse/amexoptions/complexfeed/xdp/v1.3.a/nyse_amexoptions_complexfeed_xdp_v1_3_a.hpp"

// Nyse AmexOptions ComplexFeed Xdp 1.3.a: the reading of its packets, through its Template Meta Programming header
namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

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

// Complex Symbol Definition Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_complex_symbol_definition_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& complex_symbol_definition_message_section_1_ = tmp::read<complex_symbol_definition_message_section_1>(data + offset, bound - offset, handler); offset += complex_symbol_definition_message_section_1::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(complex_symbol_definition_message_section_1_.template get<no_of_legs>()));
        while (count-- > 0) {
            offset += tmp::take<leg_definition>(data + offset, bound - offset, handler);
        }
    }
    return offset;
}

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_type& message_type_) {
    if (static_cast<bool>(tmp::rule(message_type_) == 423)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& complex_quote_message_ = tmp::read<complex_quote_message>(data + offset, bound - offset, handler); offset += complex_quote_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 425)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& complex_trade_message_ = tmp::read<complex_trade_message>(data + offset, bound - offset, handler); offset += complex_trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 429)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& complex_crossing_rfq_message_ = tmp::read<complex_crossing_rfq_message>(data + offset, bound - offset, handler); offset += complex_crossing_rfq_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 472)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& complex_cube_rfq_message_ = tmp::read<complex_cube_rfq_message>(data + offset, bound - offset, handler); offset += complex_cube_rfq_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 433)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& complex_status_message_ = tmp::read<complex_status_message>(data + offset, bound - offset, handler); offset += complex_status_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 511)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& refresh_complex_quote_message_ = tmp::read<refresh_complex_quote_message>(data + offset, bound - offset, handler); offset += refresh_complex_quote_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 513)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& refresh_complex_trade_message_ = tmp::read<refresh_complex_trade_message>(data + offset, bound - offset, handler); offset += refresh_complex_trade_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 439)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_complex_symbol_definition_message(data + offset, bound - offset, handler);
        tmp::call(handler, complex_symbol_definition_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 455)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& stream_id_message_ = tmp::read<stream_id_message>(data + offset, bound - offset, handler); offset += stream_id_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 1)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& sequence_number_reset_message_ = tmp::read<sequence_number_reset_message>(data + offset, bound - offset, handler); offset += sequence_number_reset_message::size;
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
    bound = static_cast<std::size_t>(tmp::rule(message_header_.template get<message_size>()));
    tmp::require(bound, length);
    offset += parse_payload(data + offset, bound - offset, handler, message_header_.template get<message_type>());
    return bound;
}

// Packet: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_packet([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& packet_header_ = tmp::read<packet_header>(data + offset, bound - offset, handler); offset += packet_header::size;
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


} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a

namespace protocol = ::nyse::amexoptions::complexfeed::xdp::v1_3_a;

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
        if constexpr (requires { header.template get<protocol::packet_size>(); }) { values["packet.packetheader.packetsize"] = canonical::number(header.template get<protocol::packet_size>().value()); }
        if constexpr (requires { header.template get<protocol::delivery_flag>(); }) { values["packet.packetheader.deliveryflag"] = canonical::number(header.template get<protocol::delivery_flag>().value()); }
        if constexpr (requires { header.template get<protocol::message_count>(); }) { values["packet.packetheader.messagecount"] = canonical::number(header.template get<protocol::message_count>().value()); }
        if constexpr (requires { header.template get<protocol::sequence_number>(); }) { values["packet.packetheader.sequencenumber"] = canonical::number(header.template get<protocol::sequence_number>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        entry = "packet.message[" + std::to_string(index++) + "]";
        if constexpr (requires { header.template get<protocol::message_size>(); }) { values[entry + ".messageheader.messagesize"] = canonical::number(header.template get<protocol::message_size>().value()); }
        if constexpr (requires { header.template get<protocol::message_type>(); }) { values[entry + ".messageheader.messagetype"] = canonical::number(header.template get<protocol::message_type>().value()); }
    }

    void operator()(const protocol::complex_quote_message& message) {
        values[entry + ".payload"] = "packet.message.payload.complexquotemessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.complexquotemessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.complexquotemessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::complex_index>(); }) { values[entry + ".payload.complexquotemessage.complexindex"] = canonical::number(message.template get<protocol::complex_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_seq_num>(); }) { values[entry + ".payload.complexquotemessage.symbolseqnum"] = canonical::number(message.template get<protocol::symbol_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::ask_price>(); }) { values[entry + ".payload.complexquotemessage.askprice"] = canonical::number(message.template get<protocol::ask_price>().value()); }
        if constexpr (requires { message.template get<protocol::bid_price>(); }) { values[entry + ".payload.complexquotemessage.bidprice"] = canonical::number(message.template get<protocol::bid_price>().value()); }
        if constexpr (requires { message.template get<protocol::ask_volume>(); }) { values[entry + ".payload.complexquotemessage.askvolume"] = canonical::number(message.template get<protocol::ask_volume>().value()); }
        if constexpr (requires { message.template get<protocol::bid_volume>(); }) { values[entry + ".payload.complexquotemessage.bidvolume"] = canonical::number(message.template get<protocol::bid_volume>().value()); }
        if constexpr (requires { message.template get<protocol::ask_customer_volume>(); }) { values[entry + ".payload.complexquotemessage.askcustomervolume"] = canonical::number(message.template get<protocol::ask_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::bid_customer_volume>(); }) { values[entry + ".payload.complexquotemessage.bidcustomervolume"] = canonical::number(message.template get<protocol::bid_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::quote_condition>(); }) { values[entry + ".payload.complexquotemessage.quotecondition"] = canonical::text(canonical::character(message.template get<protocol::quote_condition>().value()), '\0', false); }
    }

    void operator()(const protocol::complex_trade_message& message) {
        values[entry + ".payload"] = "packet.message.payload.complextrademessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.complextrademessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.complextrademessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::complex_index>(); }) { values[entry + ".payload.complextrademessage.complexindex"] = canonical::number(message.template get<protocol::complex_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_seq_num>(); }) { values[entry + ".payload.complextrademessage.symbolseqnum"] = canonical::number(message.template get<protocol::symbol_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { values[entry + ".payload.complextrademessage.tradeid"] = canonical::number(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.complextrademessage.price"] = canonical::number(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::volume_4>(); }) { values[entry + ".payload.complextrademessage.volume4"] = canonical::number(message.template get<protocol::volume_4>().value()); }
        if constexpr (requires { message.template get<protocol::trade_cond_1>(); }) { values[entry + ".payload.complextrademessage.tradecond1"] = canonical::text(canonical::character(message.template get<protocol::trade_cond_1>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::trade_cond_2>(); }) { values[entry + ".payload.complextrademessage.tradecond2"] = canonical::text(canonical::character(message.template get<protocol::trade_cond_2>().value()), '\0', false); }
    }

    void operator()(const protocol::complex_crossing_rfq_message& message) {
        values[entry + ".payload"] = "packet.message.payload.complexcrossingrfqmessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.complexcrossingrfqmessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_ns>(); }) { values[entry + ".payload.complexcrossingrfqmessage.sourcens"] = canonical::number(message.template get<protocol::source_ns>().value()); }
        if constexpr (requires { message.template get<protocol::complex_index>(); }) { values[entry + ".payload.complexcrossingrfqmessage.complexindex"] = canonical::number(message.template get<protocol::complex_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_seq_num>(); }) { values[entry + ".payload.complexcrossingrfqmessage.symbolseqnum"] = canonical::number(message.template get<protocol::symbol_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.complexcrossingrfqmessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::volume_2>(); }) { values[entry + ".payload.complexcrossingrfqmessage.volume2"] = canonical::number(message.template get<protocol::volume_2>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.complexcrossingrfqmessage.price"] = canonical::number(message.template get<protocol::price>().value()); }
    }

    void operator()(const protocol::complex_cube_rfq_message& message) {
        values[entry + ".payload"] = "packet.message.payload.complexcuberfqmessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.complexcuberfqmessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_ns>(); }) { values[entry + ".payload.complexcuberfqmessage.sourcens"] = canonical::number(message.template get<protocol::source_ns>().value()); }
        if constexpr (requires { message.template get<protocol::complex_index>(); }) { values[entry + ".payload.complexcuberfqmessage.complexindex"] = canonical::number(message.template get<protocol::complex_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_seq_num>(); }) { values[entry + ".payload.complexcuberfqmessage.symbolseqnum"] = canonical::number(message.template get<protocol::symbol_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::side>(); }) { values[entry + ".payload.complexcuberfqmessage.side"] = canonical::text(canonical::character(message.template get<protocol::side>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::volume_2>(); }) { values[entry + ".payload.complexcuberfqmessage.volume2"] = canonical::number(message.template get<protocol::volume_2>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.complexcuberfqmessage.price"] = canonical::number(message.template get<protocol::price>().value()); }
    }

    void operator()(const protocol::complex_status_message& message) {
        values[entry + ".payload"] = "packet.message.payload.complexstatusmessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.complexstatusmessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.complexstatusmessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::complex_index>(); }) { values[entry + ".payload.complexstatusmessage.complexindex"] = canonical::number(message.template get<protocol::complex_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_seq_num>(); }) { values[entry + ".payload.complexstatusmessage.symbolseqnum"] = canonical::number(message.template get<protocol::symbol_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::security_status>(); }) { values[entry + ".payload.complexstatusmessage.securitystatus"] = canonical::text(canonical::character(message.template get<protocol::security_status>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::halt_condition>(); }) { values[entry + ".payload.complexstatusmessage.haltcondition"] = canonical::text(canonical::character(message.template get<protocol::halt_condition>().value()), '\0', false); }
    }

    void operator()(const protocol::refresh_complex_quote_message& message) {
        values[entry + ".payload"] = "packet.message.payload.refreshcomplexquotemessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.refreshcomplexquotemessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.refreshcomplexquotemessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::complex_index>(); }) { values[entry + ".payload.refreshcomplexquotemessage.complexindex"] = canonical::number(message.template get<protocol::complex_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_seq_num>(); }) { values[entry + ".payload.refreshcomplexquotemessage.symbolseqnum"] = canonical::number(message.template get<protocol::symbol_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::ask_price>(); }) { values[entry + ".payload.refreshcomplexquotemessage.askprice"] = canonical::number(message.template get<protocol::ask_price>().value()); }
        if constexpr (requires { message.template get<protocol::bid_price>(); }) { values[entry + ".payload.refreshcomplexquotemessage.bidprice"] = canonical::number(message.template get<protocol::bid_price>().value()); }
        if constexpr (requires { message.template get<protocol::ask_volume>(); }) { values[entry + ".payload.refreshcomplexquotemessage.askvolume"] = canonical::number(message.template get<protocol::ask_volume>().value()); }
        if constexpr (requires { message.template get<protocol::bid_volume>(); }) { values[entry + ".payload.refreshcomplexquotemessage.bidvolume"] = canonical::number(message.template get<protocol::bid_volume>().value()); }
        if constexpr (requires { message.template get<protocol::ask_customer_volume>(); }) { values[entry + ".payload.refreshcomplexquotemessage.askcustomervolume"] = canonical::number(message.template get<protocol::ask_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::bid_customer_volume>(); }) { values[entry + ".payload.refreshcomplexquotemessage.bidcustomervolume"] = canonical::number(message.template get<protocol::bid_customer_volume>().value()); }
        if constexpr (requires { message.template get<protocol::quote_condition>(); }) { values[entry + ".payload.refreshcomplexquotemessage.quotecondition"] = canonical::text(canonical::character(message.template get<protocol::quote_condition>().value()), '\0', false); }
    }

    void operator()(const protocol::refresh_complex_trade_message& message) {
        values[entry + ".payload"] = "packet.message.payload.refreshcomplextrademessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.refreshcomplextrademessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.refreshcomplextrademessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::complex_index>(); }) { values[entry + ".payload.refreshcomplextrademessage.complexindex"] = canonical::number(message.template get<protocol::complex_index>().value()); }
        if constexpr (requires { message.template get<protocol::symbol_seq_num>(); }) { values[entry + ".payload.refreshcomplextrademessage.symbolseqnum"] = canonical::number(message.template get<protocol::symbol_seq_num>().value()); }
        if constexpr (requires { message.template get<protocol::trade_id>(); }) { values[entry + ".payload.refreshcomplextrademessage.tradeid"] = canonical::number(message.template get<protocol::trade_id>().value()); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.refreshcomplextrademessage.price"] = canonical::number(message.template get<protocol::price>().value()); }
        if constexpr (requires { message.template get<protocol::volume_4>(); }) { values[entry + ".payload.refreshcomplextrademessage.volume4"] = canonical::number(message.template get<protocol::volume_4>().value()); }
        if constexpr (requires { message.template get<protocol::trade_cond_1>(); }) { values[entry + ".payload.refreshcomplextrademessage.tradecond1"] = canonical::text(canonical::character(message.template get<protocol::trade_cond_1>().value()), '\0', false); }
        if constexpr (requires { message.template get<protocol::trade_cond_2>(); }) { values[entry + ".payload.refreshcomplextrademessage.tradecond2"] = canonical::text(canonical::character(message.template get<protocol::trade_cond_2>().value()), '\0', false); }
    }

    void operator()(const protocol::complex_symbol_definition_message&) {
        values[entry + ".payload"] = "packet.message.payload.complexsymboldefinitionmessage";
    }

    void operator()(const protocol::stream_id_message& message) {
        values[entry + ".payload"] = "packet.message.payload.streamidmessage";
        if constexpr (requires { message.template get<protocol::stream_id>(); }) { values[entry + ".payload.streamidmessage.streamid"] = canonical::number(message.template get<protocol::stream_id>().value()); }
    }

    void operator()(const protocol::sequence_number_reset_message& message) {
        values[entry + ".payload"] = "packet.message.payload.sequencenumberresetmessage";
        if constexpr (requires { message.template get<protocol::source_time>(); }) { values[entry + ".payload.sequencenumberresetmessage.sourcetime"] = canonical::number(message.template get<protocol::source_time>().value()); }
        if constexpr (requires { message.template get<protocol::source_time_ns>(); }) { values[entry + ".payload.sequencenumberresetmessage.sourcetimens"] = canonical::number(message.template get<protocol::source_time_ns>().value()); }
        if constexpr (requires { message.template get<protocol::product_id>(); }) { values[entry + ".payload.sequencenumberresetmessage.productid"] = canonical::number(message.template get<protocol::product_id>().value()); }
        if constexpr (requires { message.template get<protocol::channel_id>(); }) { values[entry + ".payload.sequencenumberresetmessage.channelid"] = canonical::number(message.template get<protocol::channel_id>().value()); }
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
    std::printf("== Nyse.AmexOptions.ComplexFeed.Xdp.v1.3.a (tmp values)\n");
    int failures = 0;
    failures += check("ComplexCrossingRfqMessage", "Nyse/AmexOptions.ComplexFeed.Xdp.v1.3.a/ComplexCrossingRfqMessage.pcap", "nyse/amexoptions/complexfeed/xdp/v1.3.a/ComplexCrossingRfqMessage.values");
    failures += check("ComplexQuoteMessage", "Nyse/AmexOptions.ComplexFeed.Xdp.v1.3.a/ComplexQuoteMessage.pcap", "nyse/amexoptions/complexfeed/xdp/v1.3.a/ComplexQuoteMessage.values");
    failures += check("ComplexStatusMessage", "Nyse/AmexOptions.ComplexFeed.Xdp.v1.3.a/ComplexStatusMessage.pcap", "nyse/amexoptions/complexfeed/xdp/v1.3.a/ComplexStatusMessage.values");
    failures += check("ComplexSymbolDefinitionMessage", "Nyse/AmexOptions.ComplexFeed.Xdp.v1.3.a/ComplexSymbolDefinitionMessage.pcap", "nyse/amexoptions/complexfeed/xdp/v1.3.a/ComplexSymbolDefinitionMessage.values");
    failures += check("ComplexTradeMessage", "Nyse/AmexOptions.ComplexFeed.Xdp.v1.3.a/ComplexTradeMessage.pcap", "nyse/amexoptions/complexfeed/xdp/v1.3.a/ComplexTradeMessage.values");
    failures += check("RefreshComplexQuoteMessage", "Nyse/AmexOptions.ComplexFeed.Xdp.v1.3.a/RefreshComplexQuoteMessage.pcap", "nyse/amexoptions/complexfeed/xdp/v1.3.a/RefreshComplexQuoteMessage.values");
    failures += check("RefreshComplexTradeMessage", "Nyse/AmexOptions.ComplexFeed.Xdp.v1.3.a/RefreshComplexTradeMessage.pcap", "nyse/amexoptions/complexfeed/xdp/v1.3.a/RefreshComplexTradeMessage.values");
    failures += check("StreamIdMessage", "Nyse/AmexOptions.ComplexFeed.Xdp.v1.3.a/StreamIdMessage.pcap", "nyse/amexoptions/complexfeed/xdp/v1.3.a/StreamIdMessage.values");
    return failures == 0 ? 0 : 1;
}
