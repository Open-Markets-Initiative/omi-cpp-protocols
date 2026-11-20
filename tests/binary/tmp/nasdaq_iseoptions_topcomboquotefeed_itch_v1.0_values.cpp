// Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0 canonical values, through the Tmp header: every value the Tmp reading hands
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
#include "cpp/binary/tmp/nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/nasdaq_iseoptions_topcomboquotefeed_itch_v1_0.hpp"

// Nasdaq IseOptions TopComboQuoteFeed Itch 1.0: the reading of its packets, through its Template Meta Programming header
namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

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

// Complex Strategy Directory Message: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_complex_strategy_directory_message([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler) {
    std::size_t offset = 0;
    const std::size_t bound = length;
    [[maybe_unused]] const auto& complex_strategy_directory_message_section_1_ = tmp::read<complex_strategy_directory_message_section_1>(data + offset, bound - offset, handler); offset += complex_strategy_directory_message_section_1::size;
    {
        std::size_t count = static_cast<std::size_t>(tmp::rule(complex_strategy_directory_message_section_1_.template get<number_of_legs>()));
        while (count-- > 0) {
            offset += tmp::take<leg_information>(data + offset, bound - offset, handler);
        }
    }
    return offset;
}

// Payload: read from the bytes at data, handing the handler each type laid over them; what it returns is the bytes it took
template <typename Handler>
std::size_t parse_payload([[maybe_unused]] const std::byte* data, [[maybe_unused]] std::size_t length, [[maybe_unused]] Handler& handler, const message_type& message_type_) {
    if (static_cast<bool>(tmp::rule(message_type_) == 'S')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& system_event_message_ = tmp::read<system_event_message>(data + offset, bound - offset, handler); offset += system_event_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'R')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        offset += parse_complex_strategy_directory_message(data + offset, bound - offset, handler);
        tmp::call(handler, complex_strategy_directory_message{});
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'O')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& strategy_open_closed_message_ = tmp::read<strategy_open_closed_message>(data + offset, bound - offset, handler); offset += strategy_open_closed_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'H')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& strategy_trading_action_message_ = tmp::read<strategy_trading_action_message>(data + offset, bound - offset, handler); offset += strategy_trading_action_message::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'C')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& strategy_best_bid_and_ask_update_ = tmp::read<strategy_best_bid_and_ask_update>(data + offset, bound - offset, handler); offset += strategy_best_bid_and_ask_update::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'D')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& strategy_best_bid_update_ = tmp::read<strategy_best_bid_update>(data + offset, bound - offset, handler); offset += strategy_best_bid_update::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 'E')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& strategy_best_ask_update_ = tmp::read<strategy_best_ask_update>(data + offset, bound - offset, handler); offset += strategy_best_ask_update::size;
        return offset;
    }
    if (static_cast<bool>(tmp::rule(message_type_) == 't')) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        [[maybe_unused]] const auto& complex_strategy_ticker_message_ = tmp::read<complex_strategy_ticker_message>(data + offset, bound - offset, handler); offset += complex_strategy_ticker_message::size;
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
    {
        const std::size_t size = static_cast<std::size_t>(static_cast<std::int64_t>(tmp::count(tmp::rule(message_header_.template get<message_length>()))) - 1);
        tmp::require(offset + size, bound);
        parse_payload(data + offset, size, handler, message_header_.template get<message_type>());
        offset += size;
    }
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
    if (static_cast<bool>(tmp::rule(message_count_) == 65535)) {
        std::size_t offset = 0;
        [[maybe_unused]] const std::size_t bound = length;
        tmp::call(handler, end_of_session{});
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
    [[maybe_unused]] const auto& packet_header_ = tmp::read<packet_header>(data + offset, bound - offset, handler); offset += packet_header::size;
    offset += parse_messages(data + offset, bound - offset, handler, packet_header_.template get<message_count>());
    return offset;
}


} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0

namespace protocol = ::nasdaq::iseoptions::topcomboquotefeed::itch::v1_0;

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
        if constexpr (requires { header.template get<protocol::session>(); }) { values["packet.packetheader.session"] = canonical::text(std::string(header.template get<protocol::session>().value()), '\0', false); }
        if constexpr (requires { header.template get<protocol::sequence_number>(); }) { values["packet.packetheader.sequencenumber"] = canonical::number(header.template get<protocol::sequence_number>().value()); }
        if constexpr (requires { header.template get<protocol::message_count>(); }) { values["packet.packetheader.messagecount"] = canonical::number(header.template get<protocol::message_count>().value()); }
    }

    void operator()(const protocol::message_header& header) {
        entry = "packet.messages.message[" + std::to_string(index++) + "]";
        if constexpr (requires { header.template get<protocol::message_length>(); }) { values[entry + ".messageheader.messagelength"] = canonical::number(header.template get<protocol::message_length>().value()); }
        if constexpr (requires { header.template get<protocol::message_type>(); }) { values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(header.template get<protocol::message_type>().value())); }
    }

    void operator()(const protocol::system_event_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.systemeventmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::event_code>(); }) { values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character(message.template get<protocol::event_code>().value()), ' ', false); }
        if constexpr (requires { message.template get<protocol::current_year>(); }) { values[entry + ".payload.systemeventmessage.currentyear"] = canonical::number(message.template get<protocol::current_year>().value()); }
        if constexpr (requires { message.template get<protocol::current_month>(); }) { values[entry + ".payload.systemeventmessage.currentmonth"] = canonical::number(message.template get<protocol::current_month>().value()); }
        if constexpr (requires { message.template get<protocol::current_day>(); }) { values[entry + ".payload.systemeventmessage.currentday"] = canonical::number(message.template get<protocol::current_day>().value()); }
        if constexpr (requires { message.template get<protocol::version>(); }) { values[entry + ".payload.systemeventmessage.version"] = canonical::number(message.template get<protocol::version>().value()); }
        if constexpr (requires { message.template get<protocol::sub_version>(); }) { values[entry + ".payload.systemeventmessage.subversion"] = canonical::number(message.template get<protocol::sub_version>().value()); }
    }

    void operator()(const protocol::complex_strategy_directory_message&) {
        values[entry + ".payload"] = "packet.messages.message.payload.complexstrategydirectorymessage";
    }

    void operator()(const protocol::strategy_open_closed_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.strategyopenclosedmessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.strategyopenclosedmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::strategy_id>(); }) { values[entry + ".payload.strategyopenclosedmessage.strategyid"] = canonical::number(message.template get<protocol::strategy_id>().value()); }
        if constexpr (requires { message.template get<protocol::open_state>(); }) { values[entry + ".payload.strategyopenclosedmessage.openstate"] = canonical::text(canonical::character(message.template get<protocol::open_state>().value()), ' ', false); }
    }

    void operator()(const protocol::strategy_trading_action_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.strategytradingactionmessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.strategytradingactionmessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::strategy_id>(); }) { values[entry + ".payload.strategytradingactionmessage.strategyid"] = canonical::number(message.template get<protocol::strategy_id>().value()); }
        if constexpr (requires { message.template get<protocol::current_trading_state>(); }) { values[entry + ".payload.strategytradingactionmessage.currenttradingstate"] = canonical::text(canonical::character(message.template get<protocol::current_trading_state>().value()), ' ', false); }
    }

    void operator()(const protocol::strategy_best_bid_and_ask_update& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.strategybestbidandaskupdate";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.strategybestbidandaskupdate.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::strategy_id>(); }) { values[entry + ".payload.strategybestbidandaskupdate.strategyid"] = canonical::number(message.template get<protocol::strategy_id>().value()); }
        if constexpr (requires { message.template get<protocol::quote_condition>(); }) { values[entry + ".payload.strategybestbidandaskupdate.quotecondition"] = canonical::text(canonical::character(message.template get<protocol::quote_condition>().value()), ' ', false, {std::string_view(" ", 1), std::string_view("", 0)}); }
        if constexpr (requires { message.template get<protocol::bid_price>(); }) { values[entry + ".payload.strategybestbidandaskupdate.bidprice"] = canonical::scaled(message.template get<protocol::bid_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::bid_size>(); }) { values[entry + ".payload.strategybestbidandaskupdate.bidsize"] = canonical::number(message.template get<protocol::bid_size>().value()); }
        if constexpr (requires { message.template get<protocol::bid_cust_size>(); }) { values[entry + ".payload.strategybestbidandaskupdate.bidcustsize"] = canonical::number(message.template get<protocol::bid_cust_size>().value()); }
        if constexpr (requires { message.template get<protocol::bid_pro_cust_size>(); }) { values[entry + ".payload.strategybestbidandaskupdate.bidprocustsize"] = canonical::number(message.template get<protocol::bid_pro_cust_size>().value()); }
        if constexpr (requires { message.template get<protocol::bid_ntt_size>(); }) { values[entry + ".payload.strategybestbidandaskupdate.bidnttsize"] = canonical::number(message.template get<protocol::bid_ntt_size>().value()); }
        if constexpr (requires { message.template get<protocol::bid_market_size>(); }) { values[entry + ".payload.strategybestbidandaskupdate.bidmarketsize"] = canonical::number(message.template get<protocol::bid_market_size>().value()); }
        if constexpr (requires { message.template get<protocol::bid_ntt_market_size>(); }) { values[entry + ".payload.strategybestbidandaskupdate.bidnttmarketsize"] = canonical::number(message.template get<protocol::bid_ntt_market_size>().value()); }
        if constexpr (requires { message.template get<protocol::ask_price>(); }) { values[entry + ".payload.strategybestbidandaskupdate.askprice"] = canonical::scaled(message.template get<protocol::ask_price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::ask_size>(); }) { values[entry + ".payload.strategybestbidandaskupdate.asksize"] = canonical::number(message.template get<protocol::ask_size>().value()); }
        if constexpr (requires { message.template get<protocol::ask_cust_size>(); }) { values[entry + ".payload.strategybestbidandaskupdate.askcustsize"] = canonical::number(message.template get<protocol::ask_cust_size>().value()); }
        if constexpr (requires { message.template get<protocol::ask_pro_cust_size>(); }) { values[entry + ".payload.strategybestbidandaskupdate.askprocustsize"] = canonical::number(message.template get<protocol::ask_pro_cust_size>().value()); }
        if constexpr (requires { message.template get<protocol::ask_ntt_size>(); }) { values[entry + ".payload.strategybestbidandaskupdate.asknttsize"] = canonical::number(message.template get<protocol::ask_ntt_size>().value()); }
        if constexpr (requires { message.template get<protocol::ask_market_size>(); }) { values[entry + ".payload.strategybestbidandaskupdate.askmarketsize"] = canonical::number(message.template get<protocol::ask_market_size>().value()); }
        if constexpr (requires { message.template get<protocol::ask_ntt_market_size>(); }) { values[entry + ".payload.strategybestbidandaskupdate.asknttmarketsize"] = canonical::number(message.template get<protocol::ask_ntt_market_size>().value()); }
    }

    void operator()(const protocol::strategy_best_bid_update& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.strategybestbidupdate";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.strategybestbidupdate.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::strategy_id>(); }) { values[entry + ".payload.strategybestbidupdate.strategyid"] = canonical::number(message.template get<protocol::strategy_id>().value()); }
        if constexpr (requires { message.template get<protocol::quote_condition>(); }) { values[entry + ".payload.strategybestbidupdate.quotecondition"] = canonical::text(canonical::character(message.template get<protocol::quote_condition>().value()), ' ', false, {std::string_view(" ", 1), std::string_view("", 0)}); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.strategybestbidupdate.price"] = canonical::scaled(message.template get<protocol::price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::size_type>(); }) { values[entry + ".payload.strategybestbidupdate.size"] = canonical::number(message.template get<protocol::size_type>().value()); }
        if constexpr (requires { message.template get<protocol::cust_size>(); }) { values[entry + ".payload.strategybestbidupdate.custsize"] = canonical::number(message.template get<protocol::cust_size>().value()); }
        if constexpr (requires { message.template get<protocol::pro_cust_size>(); }) { values[entry + ".payload.strategybestbidupdate.procustsize"] = canonical::number(message.template get<protocol::pro_cust_size>().value()); }
        if constexpr (requires { message.template get<protocol::ntt_size>(); }) { values[entry + ".payload.strategybestbidupdate.nttsize"] = canonical::number(message.template get<protocol::ntt_size>().value()); }
        if constexpr (requires { message.template get<protocol::market_size>(); }) { values[entry + ".payload.strategybestbidupdate.marketsize"] = canonical::number(message.template get<protocol::market_size>().value()); }
        if constexpr (requires { message.template get<protocol::ntt_market_size>(); }) { values[entry + ".payload.strategybestbidupdate.nttmarketsize"] = canonical::number(message.template get<protocol::ntt_market_size>().value()); }
    }

    void operator()(const protocol::strategy_best_ask_update& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.strategybestaskupdate";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.strategybestaskupdate.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::strategy_id>(); }) { values[entry + ".payload.strategybestaskupdate.strategyid"] = canonical::number(message.template get<protocol::strategy_id>().value()); }
        if constexpr (requires { message.template get<protocol::quote_condition>(); }) { values[entry + ".payload.strategybestaskupdate.quotecondition"] = canonical::text(canonical::character(message.template get<protocol::quote_condition>().value()), ' ', false, {std::string_view(" ", 1), std::string_view("", 0)}); }
        if constexpr (requires { message.template get<protocol::price>(); }) { values[entry + ".payload.strategybestaskupdate.price"] = canonical::scaled(message.template get<protocol::price>().value(), -4); }
        if constexpr (requires { message.template get<protocol::size_type>(); }) { values[entry + ".payload.strategybestaskupdate.size"] = canonical::number(message.template get<protocol::size_type>().value()); }
        if constexpr (requires { message.template get<protocol::cust_size>(); }) { values[entry + ".payload.strategybestaskupdate.custsize"] = canonical::number(message.template get<protocol::cust_size>().value()); }
        if constexpr (requires { message.template get<protocol::pro_cust_size>(); }) { values[entry + ".payload.strategybestaskupdate.procustsize"] = canonical::number(message.template get<protocol::pro_cust_size>().value()); }
        if constexpr (requires { message.template get<protocol::ntt_size>(); }) { values[entry + ".payload.strategybestaskupdate.nttsize"] = canonical::number(message.template get<protocol::ntt_size>().value()); }
        if constexpr (requires { message.template get<protocol::market_size>(); }) { values[entry + ".payload.strategybestaskupdate.marketsize"] = canonical::number(message.template get<protocol::market_size>().value()); }
        if constexpr (requires { message.template get<protocol::ntt_market_size>(); }) { values[entry + ".payload.strategybestaskupdate.nttmarketsize"] = canonical::number(message.template get<protocol::ntt_market_size>().value()); }
    }

    void operator()(const protocol::complex_strategy_ticker_message& message) {
        values[entry + ".payload"] = "packet.messages.message.payload.complexstrategytickermessage";
        if constexpr (requires { message.template get<protocol::timestamp>(); }) { values[entry + ".payload.complexstrategytickermessage.timestamp"] = canonical::number(message.template get<protocol::timestamp>().value()); }
        if constexpr (requires { message.template get<protocol::strategy_id>(); }) { values[entry + ".payload.complexstrategytickermessage.strategyid"] = canonical::number(message.template get<protocol::strategy_id>().value()); }
        if constexpr (requires { message.template get<protocol::last_price>(); }) { values[entry + ".payload.complexstrategytickermessage.lastprice"] = canonical::scaled(message.template get<protocol::last_price>().value(), -8); }
        if constexpr (requires { message.template get<protocol::size_type>(); }) { values[entry + ".payload.complexstrategytickermessage.size"] = canonical::number(message.template get<protocol::size_type>().value()); }
        if constexpr (requires { message.template get<protocol::volume>(); }) { values[entry + ".payload.complexstrategytickermessage.volume"] = canonical::number(message.template get<protocol::volume>().value()); }
        if constexpr (requires { message.template get<protocol::high>(); }) { values[entry + ".payload.complexstrategytickermessage.high"] = canonical::scaled(message.template get<protocol::high>().value(), -8); }
        if constexpr (requires { message.template get<protocol::low>(); }) { values[entry + ".payload.complexstrategytickermessage.low"] = canonical::scaled(message.template get<protocol::low>().value(), -8); }
        if constexpr (requires { message.template get<protocol::first>(); }) { values[entry + ".payload.complexstrategytickermessage.first"] = canonical::scaled(message.template get<protocol::first>().value(), -8); }
        if constexpr (requires { message.template get<protocol::trade_condition>(); }) { values[entry + ".payload.complexstrategytickermessage.tradecondition"] = canonical::text(canonical::character(message.template get<protocol::trade_condition>().value()), ' ', false); }
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
    std::printf("== Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0 (tmp values)\n");
    int failures = 0;
    failures += check("ComplexStrategyDirectoryMessage", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/ComplexStrategyDirectoryMessage.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/ComplexStrategyDirectoryMessage.values");
    failures += check("ComplexStrategyTickerMessage", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/ComplexStrategyTickerMessage.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/ComplexStrategyTickerMessage.values");
    failures += check("Heartbeat", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/Heartbeat.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/Heartbeat.values");
    failures += check("StrategyBestAskUpdate", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/StrategyBestAskUpdate.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/StrategyBestAskUpdate.values");
    failures += check("StrategyBestBidAndAskUpdate", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/StrategyBestBidAndAskUpdate.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/StrategyBestBidAndAskUpdate.values");
    failures += check("StrategyBestBidUpdate", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/StrategyBestBidUpdate.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/StrategyBestBidUpdate.values");
    failures += check("StrategyOpenClosedMessage", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/StrategyOpenClosedMessage.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/StrategyOpenClosedMessage.values");
    failures += check("StrategyTradingActionMessage", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/StrategyTradingActionMessage.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/StrategyTradingActionMessage.values");
    return failures == 0 ? 0 : 1;
}
