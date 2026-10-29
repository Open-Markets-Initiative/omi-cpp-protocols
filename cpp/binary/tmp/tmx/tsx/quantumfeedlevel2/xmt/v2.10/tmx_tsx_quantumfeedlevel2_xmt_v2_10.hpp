// Tmx Tsx QuantumFeedLevel2 Xmt 2.10 Template Meta Programming

#pragma once

#include <algorithm>
#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>

// A member of a struct laid over its bytes: the overload get<Field>() finds it by, and the member
#ifndef XMTFIELD
#define XMTFIELD(type) constexpr const type& ref(const type*) const noexcept { return type##_; } type type##_
#endif

// A repeating group of a message: its entries' type, which the parse hands over one at a time; no bytes
#ifndef XMTSEQUENCE
#define XMTSEQUENCE(type) using type##_sequence = tmp::sequence<type>
#endif

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

/////////////////////////////////////////////////////////////////////
// Wire
/////////////////////////////////////////////////////////////////////

namespace tmp {
    // The types of a struct's members, in wire order: what generic code walks a struct by
    template <typename... Fields>
    struct list {};

    // A repeating group of a message: the type of its entries, each laid over its bytes in turn
    template <typename Entry>
    struct sequence {
        using entry = Entry;
    };

    // An integer as the wire holds it, in the host's order: swapped when the wire's order is not the host's
    template <std::endian Order, typename T>
    constexpr T ordered(T value) noexcept {
        if constexpr (sizeof(T) == 1 || Order == std::endian::native) { return value; }
        else { return std::byteswap(value); }
    }

    // An integer of a width no C++ integer has, assembled from its bytes in the wire's order
    template <std::endian Order, typename T, std::size_t N>
    constexpr T assembled(const std::array<std::byte, N>& bytes) noexcept {
        using U = std::make_unsigned_t<T>;
        U value = 0;
        for (std::size_t index = 0; index < N; ++index) {
            const std::size_t at = Order == std::endian::big ? index : N - 1 - index;
            value = static_cast<U>((value << 8) | std::to_integer<U>(bytes[at]));
        }
        if constexpr (std::is_signed_v<T>) {
            constexpr int spare = static_cast<int>(sizeof(T) - N) * 8;
            return static_cast<T>(static_cast<T>(value << spare) >> spare);
        }
        else { return value; }
    }

    // Text of a fixed width, as the characters before its fill
    template <std::size_t N>
    constexpr std::string_view trimmed(const std::array<char, N>& text, char fill) noexcept {
        std::size_t length = N;
        while (length > 0 && text[length - 1] == fill) { --length; }
        return { text.data(), length };
    }

    // Text of a fixed width justified right, as the characters after its fill
    template <std::size_t N>
    constexpr std::string_view trimmed_front(const std::array<char, N>& text, char fill) noexcept {
        std::size_t start = 0;
        while (start < N && text[start] == fill) { ++start; }
        return { text.data() + start, N - start };
    }

    // The integer the digits of text state, its fill skipped; it ends at anything else
    template <typename T>
    constexpr T number(std::string_view text, char fill) noexcept {
        T value = 0;
        for (const char character : text) {
            if (character == fill) { continue; }
            if (character < '0' || character > '9') { break; }
            value = static_cast<T>(value * 10 + static_cast<T>(character - '0'));
        }
        return value;
    }
} // namespace tmp

/////////////////////////////////////////////////////////////////////
// Types
/////////////////////////////////////////////////////////////////////

// Ack Required Poss Dup
struct ack_required_poss_dup {
    enum class type : char {
        unused = '0',
        ack_required = 'A',
        poss_dup = 'D',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Admin Id: Admin ID for short window (1 to 255). Note: 0 is not allowed as a value.
struct admin_id {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Board Lot: Contains The Board Lot Size
struct board_lot {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Broker Number: An Exchange Assigned Public Number Uniquely Identifying A Partici Pating Organization
struct broker_number {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Buy Broker Number: An Exchange Assigned Public Number Uniquely Identifying A Partici Pating Organization Associated With A Buy Order
struct buy_broker_number {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Buy Display Volume: Public Remaining Display Volume For The Buy Order
struct buy_display_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Buy Order Id: Public Numeric Identifier Assigned To The Buy Order By The Trading System
struct buy_order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Bypass: An Indicator For Bypass Crosses Which Can Be Printed Outside Of The Protected Nbbo And Are Not Subject To Cross Interference
struct bypass {
    enum class type : char {
        the_order_is_a_bypass = 'Y',
        the_order_is_not_a_bypass = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Calculated Opening Price: The Price At Which Orders Will Trade At The Open
struct calculated_opening_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Comment: A Text Field Corresponding To A Reason Code Entered When A Stock Is Halted Or The Initiator Of A Delayed Opening On A Stock Or When There Is A Change To The Oddlot Trader On A Stock
struct comment {
    using type = std::string_view;
    static constexpr std::size_t size = 40;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 40> value_;
};

// Cross Type: Type Of Crosses Originating From A Participating Organization Between Managed Accounts That Have The Same Manager
struct cross_type {
    enum class type : char {
        internal = 'I',
        basis = 'B',
        contingent = 'C',
        special_trading_session = 'S',
        volume_weighted_average_price = 'V',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Currency: The Currency Associated With A Reported Price
struct currency {
    enum class type : char {
        usd = 'U',
        cad = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Cusip: Clearing And Settlement Registration Number
struct cusip {
    using type = std::string_view;
    static constexpr std::size_t size = 12;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 12> value_;
};

// Face Value: The Face Value Of A Debenture
struct face_value {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Hb Interval: Heartbeat interval in milliseconds (1 to 65536).
struct hb_interval {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Imbalance Reference Price: The Price That Determines If A Given Limit Priced Market On Close Loc Order Can Contribute To The Moc Imbalance All Loc Orders That Are Priced Equal To Or More Aggressively Than This Price Will Contribute To The Moc Imbalance
struct imbalance_reference_price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Imbalance Side: Marker To Indicate Which Side Has An Imbalance Volume For Market On Close
struct imbalance_side {
    enum class type : char {
        buy = 'B',
        sell = 'S',
        no_imbalance_exists = ' ',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Imbalance Volume: Identifies The Volume Of Shares Of The Imbalance Side For Market On Close
struct imbalance_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Initiated By: Indicates Which Side Began The Trade Correction
struct initiated_by {
    enum class type : char {
        buy = 'B',
        sell = 'S',
        both = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Last Sale: Last Sale Price Of A Stock
struct last_sale {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Market State: Indicates The Current Market State
struct market_state {
    enum class type : char {
        pre_open = 'P',
        opening = 'O',
        open = 'S',
        moc_imbalance = 'M',
        ccp_determination = 'A',
        price_movement_extension = 'E',
        closing = 'L',
        extended_hours_cxls = 'N',
        extended_hours_open = 'R',
        extended_hours_close = 'F',
        closed = 'C',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Message Length: Length of message from Header to Body inclusive
struct message_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Msg Length: Length of this message
struct msg_length {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Msg Type
struct msg_type {
    enum class type : char {
        heartbeat = '0',
        symbol_status_message = 'J',
        order_book_message = 'G',
        order_book_terms_message = 'j',
        assign_cop_orders_message = 'A',
        assign_cop_no_orders_message = 'B',
        assign_limit_message = 'C',
        market_state_update_message = 'E',
        moc_imbalance_message = 'F',
        order_booked_message = 'P',
        order_booked_terms_message = 'm',
        order_cancelled_message = 'Q',
        order_cancelled_terms_message = 'n',
        order_price_time_assigned_message = 'R',
        order_price_time_assigned_terms_message = 'o',
        stock_status_message = 'I',
        trade_report_message = 'S',
        trade_report_terms_message = 'p',
        trade_cancelled_message = 'T',
        trade_cancelled_terms_message = 'q',
        trade_correction_message = 'U',
        trade_correction_terms_message = 'r',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Msg Version: Message version number
struct msg_version {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Non Resident: A Terms Marker Indicating That Trade Participant Is Not A Canadian Resident
struct non_resident {
    enum class type : char {
        yes = 'Y',
        no = 'N',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Num Body
struct num_body {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Id: Public Numeric Identifier Assigned To An Order By The Trading System
struct order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Order Side: Market Side Of An Order
struct order_side {
    enum class type : char {
        buy = 'B',
        sell = 'S',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Orig Trade Number: Used With Trade Corrections To Reference Previously Reported Executions
struct orig_trade_number {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Price: The Price In A Valid Currency
struct price {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);
    static constexpr int exponent = -6;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Priority Time Stamp: Time Stamp Assigned By The Trading Engine To Specify Time Priority Of An Order Orders Are Sequenced In The Order Book Based On Symbol Price And Priority Time Stamp
struct priority_time_stamp {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Protocol Name
struct protocol_name {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Protocol Version: Protocol major version number
struct protocol_version {
    using type = char;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    char value_;
};

// Sell Broker Number: An Exchange Assigned Number Uniquely Identifying A Partici Pating Organization Associated With A Sell Order
struct sell_broker_number {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Sell Display Volume: Public Remaining Volume For The Sell Order
struct sell_display_volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Sell Order Id: Public Numeric Identifier Assigned To A Sell Order By The Trading System
struct sell_order_id {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Sequence 0: Reserved for future expansion, Value is 0
struct sequence_0 {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Sequence 1: Sequence per Stream Id of the Business message
struct sequence_1 {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Session Id: Constant Session Id
struct session_id {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Settlement Date: Settlement Date Associated With The Order
struct settlement_date {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Settlement Terms: Settlement Terms Associated With The Order
struct settlement_terms {
    enum class type : char {
        cash = 'C',
        nn = 'N',
        ms = 'M',
        ct = 'T',
        valid_settlement_date = 'D',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Source Id: Source Id of the Business message
struct source_id {
    enum class type : char {
        non_source_related = '0',
        tsx = 'Q',
        tsx_venture = 'V',
        alpha = 'A',
    };

    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return static_cast<type>(raw()); }
    constexpr operator type() const noexcept { return value(); }
    constexpr std::underlying_type_t<type> raw() const noexcept { return value_; }

  protected:
    std::underlying_type_t<type> value_;
};

// Start Of Frame
struct start_of_frame {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Stock Group: An Identifier Of The Stock Group
struct stock_group {
    using type = std::uint8_t;
    static constexpr std::size_t size = 1;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return value_; }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Stock State: The State Of The Stock
struct stock_state {
    using type = std::string_view;
    static constexpr std::size_t size = 2;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 2> value_;
};

// Stream Id: Stream Id per Source Id of the Business message
struct stream_id {
    using type = std::uint16_t;
    static constexpr std::size_t size = 2;
    static constexpr std::endian order = std::endian::little;

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Symbol: A Unique Alphanumeric Identifier For A Security
struct symbol {
    using type = std::string_view;
    static constexpr std::size_t size = 9;
    static constexpr char fill = ' ';

    constexpr type value() const noexcept { return tmp::trimmed(value_, fill); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    std::array<char, 9> value_;
};

// Trade Number: A Unique Identifier Per Stock Assigned To Each Trade
struct trade_number {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trade Time Stamp: The Time At Which The Trade Occurred Manually Set When A Trade Is Added
struct trade_time_stamp {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Trading System Time Stamp: The Time At Which The Event Being Reported Occurred In The Trading Engine
struct trading_system_time_stamp {
    using type = std::uint64_t;
    static constexpr std::size_t size = 8;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};

// Volume: The Quantity Of Shares For An Order Or Trade
struct volume {
    using type = std::uint32_t;
    static constexpr std::size_t size = 4;
    static constexpr std::endian order = std::endian::little;
    static constexpr type no_value = static_cast<type>(0ULL);

    constexpr type value() const noexcept { return tmp::ordered<order>(value_); }
    constexpr operator type() const noexcept { return value(); }

  protected:
    type value_;
};


/////////////////////////////////////////////////////////////////////
// Messages
/////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)

// Trade Correction Terms Message
struct trade_correction_terms_message {
    static constexpr std::string_view name = "Trade Correction Terms Message";
    static constexpr std::size_t size = 53;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        trade_number,
        price,
        volume,
        buy_broker_number,
        sell_broker_number,
        initiated_by,
        orig_trade_number,
        trade_time_stamp,
        non_resident,
        settlement_terms,
        settlement_date,
        cross_type,
        trading_system_time_stamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(symbol);
    XMTFIELD(trade_number);
    XMTFIELD(price);
    XMTFIELD(volume);
    XMTFIELD(buy_broker_number);
    XMTFIELD(sell_broker_number);
    XMTFIELD(initiated_by);
    XMTFIELD(orig_trade_number);
    XMTFIELD(trade_time_stamp);
    XMTFIELD(non_resident);
    XMTFIELD(settlement_terms);
    XMTFIELD(settlement_date);
    XMTFIELD(cross_type);
    XMTFIELD(trading_system_time_stamp);
};

static_assert(sizeof(trade_correction_terms_message) == trade_correction_terms_message::size, "trade_correction_terms_message lies over its bytes exactly");

// Trade Correction Message
struct trade_correction_message {
    static constexpr std::string_view name = "Trade Correction Message";
    static constexpr std::size_t size = 48;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        trade_number,
        price,
        volume,
        buy_broker_number,
        sell_broker_number,
        initiated_by,
        orig_trade_number,
        bypass,
        trade_time_stamp,
        cross_type,
        trading_system_time_stamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(symbol);
    XMTFIELD(trade_number);
    XMTFIELD(price);
    XMTFIELD(volume);
    XMTFIELD(buy_broker_number);
    XMTFIELD(sell_broker_number);
    XMTFIELD(initiated_by);
    XMTFIELD(orig_trade_number);
    XMTFIELD(bypass);
    XMTFIELD(trade_time_stamp);
    XMTFIELD(cross_type);
    XMTFIELD(trading_system_time_stamp);
};

static_assert(sizeof(trade_correction_message) == trade_correction_message::size, "trade_correction_message lies over its bytes exactly");

// Trade Cancelled Terms Message
struct trade_cancelled_terms_message {
    static constexpr std::string_view name = "Trade Cancelled Terms Message";
    static constexpr std::size_t size = 21;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        trade_number,
        trading_system_time_stamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(symbol);
    XMTFIELD(trade_number);
    XMTFIELD(trading_system_time_stamp);
};

static_assert(sizeof(trade_cancelled_terms_message) == trade_cancelled_terms_message::size, "trade_cancelled_terms_message lies over its bytes exactly");

// Trade Cancelled Message
struct trade_cancelled_message {
    static constexpr std::string_view name = "Trade Cancelled Message";
    static constexpr std::size_t size = 21;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        trade_number,
        trading_system_time_stamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(symbol);
    XMTFIELD(trade_number);
    XMTFIELD(trading_system_time_stamp);
};

static_assert(sizeof(trade_cancelled_message) == trade_cancelled_message::size, "trade_cancelled_message lies over its bytes exactly");

// Trade Report Terms Message
struct trade_report_terms_message {
    static constexpr std::string_view name = "Trade Report Terms Message";
    static constexpr std::size_t size = 72;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        trade_number,
        price,
        volume,
        buy_broker_number,
        buy_order_id,
        buy_display_volume,
        sell_broker_number,
        sell_order_id,
        sell_display_volume,
        trade_time_stamp,
        non_resident,
        settlement_terms,
        settlement_date,
        cross_type,
        trading_system_time_stamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(symbol);
    XMTFIELD(trade_number);
    XMTFIELD(price);
    XMTFIELD(volume);
    XMTFIELD(buy_broker_number);
    XMTFIELD(buy_order_id);
    XMTFIELD(buy_display_volume);
    XMTFIELD(sell_broker_number);
    XMTFIELD(sell_order_id);
    XMTFIELD(sell_display_volume);
    XMTFIELD(trade_time_stamp);
    XMTFIELD(non_resident);
    XMTFIELD(settlement_terms);
    XMTFIELD(settlement_date);
    XMTFIELD(cross_type);
    XMTFIELD(trading_system_time_stamp);
};

static_assert(sizeof(trade_report_terms_message) == trade_report_terms_message::size, "trade_report_terms_message lies over its bytes exactly");

// Trade Report Message
struct trade_report_message {
    static constexpr std::string_view name = "Trade Report Message";
    static constexpr std::size_t size = 67;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        trade_number,
        price,
        volume,
        buy_broker_number,
        buy_order_id,
        buy_display_volume,
        sell_broker_number,
        sell_order_id,
        sell_display_volume,
        bypass,
        trade_time_stamp,
        cross_type,
        trading_system_time_stamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(symbol);
    XMTFIELD(trade_number);
    XMTFIELD(price);
    XMTFIELD(volume);
    XMTFIELD(buy_broker_number);
    XMTFIELD(buy_order_id);
    XMTFIELD(buy_display_volume);
    XMTFIELD(sell_broker_number);
    XMTFIELD(sell_order_id);
    XMTFIELD(sell_display_volume);
    XMTFIELD(bypass);
    XMTFIELD(trade_time_stamp);
    XMTFIELD(cross_type);
    XMTFIELD(trading_system_time_stamp);
};

static_assert(sizeof(trade_report_message) == trade_report_message::size, "trade_report_message lies over its bytes exactly");

// Stock Status Message
struct stock_status_message {
    static constexpr std::string_view name = "Stock Status Message";
    static constexpr std::size_t size = 59;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        comment,
        stock_state,
        trading_system_time_stamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(symbol);
    XMTFIELD(comment);
    XMTFIELD(stock_state);
    XMTFIELD(trading_system_time_stamp);
};

static_assert(sizeof(stock_status_message) == stock_status_message::size, "stock_status_message lies over its bytes exactly");

// Order Price Time Assigned Terms Message
struct order_price_time_assigned_terms_message {
    static constexpr std::string_view name = "Order Price Time Assigned Terms Message";
    static constexpr std::size_t size = 48;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        broker_number,
        order_side,
        order_id,
        price,
        volume,
        priority_time_stamp,
        trading_system_time_stamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(symbol);
    XMTFIELD(broker_number);
    XMTFIELD(order_side);
    XMTFIELD(order_id);
    XMTFIELD(price);
    XMTFIELD(volume);
    XMTFIELD(priority_time_stamp);
    XMTFIELD(trading_system_time_stamp);
};

static_assert(sizeof(order_price_time_assigned_terms_message) == order_price_time_assigned_terms_message::size, "order_price_time_assigned_terms_message lies over its bytes exactly");

// Order Price Time Assigned Message
struct order_price_time_assigned_message {
    static constexpr std::string_view name = "Order Price Time Assigned Message";
    static constexpr std::size_t size = 48;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        broker_number,
        order_side,
        order_id,
        price,
        volume,
        priority_time_stamp,
        trading_system_time_stamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(symbol);
    XMTFIELD(broker_number);
    XMTFIELD(order_side);
    XMTFIELD(order_id);
    XMTFIELD(price);
    XMTFIELD(volume);
    XMTFIELD(priority_time_stamp);
    XMTFIELD(trading_system_time_stamp);
};

static_assert(sizeof(order_price_time_assigned_message) == order_price_time_assigned_message::size, "order_price_time_assigned_message lies over its bytes exactly");

// Order Cancelled Terms Message
struct order_cancelled_terms_message {
    static constexpr std::string_view name = "Order Cancelled Terms Message";
    static constexpr std::size_t size = 28;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        broker_number,
        order_side,
        order_id,
        trading_system_time_stamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(symbol);
    XMTFIELD(broker_number);
    XMTFIELD(order_side);
    XMTFIELD(order_id);
    XMTFIELD(trading_system_time_stamp);
};

static_assert(sizeof(order_cancelled_terms_message) == order_cancelled_terms_message::size, "order_cancelled_terms_message lies over its bytes exactly");

// Order Cancelled Message
struct order_cancelled_message {
    static constexpr std::string_view name = "Order Cancelled Message";
    static constexpr std::size_t size = 28;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        broker_number,
        order_side,
        order_id,
        trading_system_time_stamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(symbol);
    XMTFIELD(broker_number);
    XMTFIELD(order_side);
    XMTFIELD(order_id);
    XMTFIELD(trading_system_time_stamp);
};

static_assert(sizeof(order_cancelled_message) == order_cancelled_message::size, "order_cancelled_message lies over its bytes exactly");

// Order Booked Terms Message
struct order_booked_terms_message {
    static constexpr std::string_view name = "Order Booked Terms Message";
    static constexpr std::size_t size = 54;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        broker_number,
        order_side,
        order_id,
        price,
        volume,
        non_resident,
        settlement_terms,
        settlement_date,
        priority_time_stamp,
        trading_system_time_stamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(symbol);
    XMTFIELD(broker_number);
    XMTFIELD(order_side);
    XMTFIELD(order_id);
    XMTFIELD(price);
    XMTFIELD(volume);
    XMTFIELD(non_resident);
    XMTFIELD(settlement_terms);
    XMTFIELD(settlement_date);
    XMTFIELD(priority_time_stamp);
    XMTFIELD(trading_system_time_stamp);
};

static_assert(sizeof(order_booked_terms_message) == order_booked_terms_message::size, "order_booked_terms_message lies over its bytes exactly");

// Order Booked Message
struct order_booked_message {
    static constexpr std::string_view name = "Order Booked Message";
    static constexpr std::size_t size = 48;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        broker_number,
        order_side,
        order_id,
        price,
        volume,
        priority_time_stamp,
        trading_system_time_stamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(symbol);
    XMTFIELD(broker_number);
    XMTFIELD(order_side);
    XMTFIELD(order_id);
    XMTFIELD(price);
    XMTFIELD(volume);
    XMTFIELD(priority_time_stamp);
    XMTFIELD(trading_system_time_stamp);
};

static_assert(sizeof(order_booked_message) == order_booked_message::size, "order_booked_message lies over its bytes exactly");

// Moc Imbalance Message
struct moc_imbalance_message {
    static constexpr std::string_view name = "Moc Imbalance Message";
    static constexpr std::size_t size = 30;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        imbalance_side,
        imbalance_volume,
        trading_system_time_stamp,
        imbalance_reference_price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(symbol);
    XMTFIELD(imbalance_side);
    XMTFIELD(imbalance_volume);
    XMTFIELD(trading_system_time_stamp);
    XMTFIELD(imbalance_reference_price);
};

static_assert(sizeof(moc_imbalance_message) == moc_imbalance_message::size, "moc_imbalance_message lies over its bytes exactly");

// Market State Update Message
struct market_state_update_message {
    static constexpr std::string_view name = "Market State Update Message";
    static constexpr std::size_t size = 10;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        market_state,
        stock_group,
        trading_system_time_stamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(market_state);
    XMTFIELD(stock_group);
    XMTFIELD(trading_system_time_stamp);
};

static_assert(sizeof(market_state_update_message) == market_state_update_message::size, "market_state_update_message lies over its bytes exactly");

// Cop Limit
struct cop_limit {
    static constexpr std::string_view name = "Cop Limit";
    static constexpr std::size_t size = 18;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        broker_number,
        order_id,
        price>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(broker_number);
    XMTFIELD(order_id);
    XMTFIELD(price);
};

static_assert(sizeof(cop_limit) == cop_limit::size, "cop_limit lies over its bytes exactly");

// Assign Limit Message
struct assign_limit_message {
    static constexpr std::string_view name = "Assign Limit Message";
    static constexpr std::size_t size = 44;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        calculated_opening_price,
        order_side,
        cop_limit,
        trading_system_time_stamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(symbol);
    XMTFIELD(calculated_opening_price);
    XMTFIELD(order_side);
    XMTFIELD(cop_limit);
    XMTFIELD(trading_system_time_stamp);
};

static_assert(sizeof(assign_limit_message) == assign_limit_message::size, "assign_limit_message lies over its bytes exactly");

// Assign Cop No Orders Message
struct assign_cop_no_orders_message {
    static constexpr std::string_view name = "Assign Cop No Orders Message";
    static constexpr std::size_t size = 25;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        calculated_opening_price,
        trading_system_time_stamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(symbol);
    XMTFIELD(calculated_opening_price);
    XMTFIELD(trading_system_time_stamp);
};

static_assert(sizeof(assign_cop_no_orders_message) == assign_cop_no_orders_message::size, "assign_cop_no_orders_message lies over its bytes exactly");

// Cop Order
struct cop_order {
    static constexpr std::string_view name = "Cop Order";
    static constexpr std::size_t size = 10;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        broker_number,
        order_id>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(broker_number);
    XMTFIELD(order_id);
};

static_assert(sizeof(cop_order) == cop_order::size, "cop_order lies over its bytes exactly");

// Assign Cop Orders Message
struct assign_cop_orders_message {
    static constexpr std::string_view name = "Assign Cop Orders Message";
    static constexpr std::size_t size = 36;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        calculated_opening_price,
        order_side,
        cop_order,
        trading_system_time_stamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(symbol);
    XMTFIELD(calculated_opening_price);
    XMTFIELD(order_side);
    XMTFIELD(cop_order);
    XMTFIELD(trading_system_time_stamp);
};

static_assert(sizeof(assign_cop_orders_message) == assign_cop_orders_message::size, "assign_cop_orders_message lies over its bytes exactly");

// Order Book Terms Message
struct order_book_terms_message {
    static constexpr std::string_view name = "Order Book Terms Message";
    static constexpr std::size_t size = 46;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        broker_number,
        order_side,
        order_id,
        price,
        volume,
        non_resident,
        settlement_terms,
        settlement_date,
        priority_time_stamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(symbol);
    XMTFIELD(broker_number);
    XMTFIELD(order_side);
    XMTFIELD(order_id);
    XMTFIELD(price);
    XMTFIELD(volume);
    XMTFIELD(non_resident);
    XMTFIELD(settlement_terms);
    XMTFIELD(settlement_date);
    XMTFIELD(priority_time_stamp);
};

static_assert(sizeof(order_book_terms_message) == order_book_terms_message::size, "order_book_terms_message lies over its bytes exactly");

// Order Book Message
struct order_book_message {
    static constexpr std::string_view name = "Order Book Message";
    static constexpr std::size_t size = 40;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        broker_number,
        order_side,
        order_id,
        price,
        volume,
        priority_time_stamp>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(symbol);
    XMTFIELD(broker_number);
    XMTFIELD(order_side);
    XMTFIELD(order_id);
    XMTFIELD(price);
    XMTFIELD(volume);
    XMTFIELD(priority_time_stamp);
};

static_assert(sizeof(order_book_message) == order_book_message::size, "order_book_message lies over its bytes exactly");

// Symbol Status Message
struct symbol_status_message {
    static constexpr std::string_view name = "Symbol Status Message";
    static constexpr std::size_t size = 41;
    static constexpr bool is_message = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        symbol,
        stock_group,
        cusip,
        board_lot,
        currency,
        face_value,
        last_sale>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(symbol);
    XMTFIELD(stock_group);
    XMTFIELD(cusip);
    XMTFIELD(board_lot);
    XMTFIELD(currency);
    XMTFIELD(face_value);
    XMTFIELD(last_sale);
};

static_assert(sizeof(symbol_status_message) == symbol_status_message::size, "symbol_status_message lies over its bytes exactly");

// Business Message: Branch
struct business_message {
    static constexpr std::string_view name = "Business Message";
    static constexpr bool is_message = false;
};

// Business Header: Xmt Business Header
struct business_header {
    static constexpr std::string_view name = "Business Header";
    static constexpr std::size_t size = 9;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        msg_version,
        source_id,
        stream_id,
        sequence_0,
        sequence_1>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(msg_version);
    XMTFIELD(source_id);
    XMTFIELD(stream_id);
    XMTFIELD(sequence_0);
    XMTFIELD(sequence_1);
};

static_assert(sizeof(business_header) == business_header::size, "business_header lies over its bytes exactly");

// Body Message: Xmt Body Header
struct body_message {
    static constexpr std::string_view name = "Body Message";
    static constexpr bool is_message = false;
};

// Body Header: Xmt Body Header
struct body_header {
    static constexpr std::string_view name = "Body Header";
    static constexpr std::size_t size = 3;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        msg_length,
        msg_type>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(msg_length);
    XMTFIELD(msg_type);
};

static_assert(sizeof(body_header) == body_header::size, "body_header lies over its bytes exactly");

// Body: Xmt Body
struct body {
    static constexpr std::string_view name = "Body";
    static constexpr bool is_message = false;
};

// Business Bodies
struct business_bodies {
    static constexpr std::string_view name = "Business Bodies";
    static constexpr bool is_message = false;

    // its repeating groups, whose entries the parse hands over one at a time
    XMTSEQUENCE(body);
};

// Admin Body
struct admin_body {
    static constexpr std::string_view name = "Admin Body";
    static constexpr std::size_t size = 8;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        source_id,
        stream_id,
        sequence_0,
        sequence_1>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(source_id);
    XMTFIELD(stream_id);
    XMTFIELD(sequence_0);
    XMTFIELD(sequence_1);
};

static_assert(sizeof(admin_body) == admin_body::size, "admin_body lies over its bytes exactly");

// Heartbeat Body Section 1
struct heartbeat_body_section_1 {
    static constexpr std::string_view name = "Heartbeat Body Section 1";
    static constexpr std::size_t size = 6;
    static constexpr bool is_message = false;
    // a section of a message no struct lies over: the fields it lays over in turn
    static constexpr bool is_section = true;

    // the types of its members, in wire order
    using fields = tmp::list<
        body_header,
        admin_id,
        hb_interval>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(body_header);
    XMTFIELD(admin_id);
    XMTFIELD(hb_interval);
};

static_assert(sizeof(heartbeat_body_section_1) == heartbeat_body_section_1::size, "heartbeat_body_section_1 lies over its bytes exactly");

// Heartbeat Body
struct heartbeat_body {
    static constexpr std::string_view name = "Heartbeat Body";
    static constexpr bool is_message = true;

    // its repeating groups, whose entries the parse hands over one at a time
    XMTSEQUENCE(admin_body);
};

// Packet Body: Branch
struct packet_body {
    static constexpr std::string_view name = "Packet Body";
    static constexpr bool is_message = false;
};

// Frame Header: Xmt Udp Packet Frame Header
struct frame_header {
    static constexpr std::string_view name = "Frame Header";
    static constexpr std::size_t size = 11;
    static constexpr bool is_message = false;

    // the types of its members, in wire order
    using fields = tmp::list<
        start_of_frame,
        protocol_name,
        protocol_version,
        message_length,
        session_id,
        ack_required_poss_dup,
        num_body>;

    // the member of the type asked for
    template <typename Field>
    constexpr const Field& get() const noexcept { return ref(static_cast<const Field*>(nullptr)); }

  protected:
    XMTFIELD(start_of_frame);
    XMTFIELD(protocol_name);
    XMTFIELD(protocol_version);
    XMTFIELD(message_length);
    XMTFIELD(session_id);
    XMTFIELD(ack_required_poss_dup);
    XMTFIELD(num_body);
};

static_assert(sizeof(frame_header) == frame_header::size, "frame_header lies over its bytes exactly");

// Packet: Xmt Udp Packet
struct packet {
    static constexpr std::string_view name = "Packet";
    static constexpr bool is_message = false;
};

#pragma pack(pop)

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
