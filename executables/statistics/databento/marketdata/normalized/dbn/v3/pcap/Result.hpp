#pragma once

namespace packet {

    enum class result {
        databento_marketdata_normalized_dbn_v3,
        error,
        end_of_file,
        unknown
    };

}