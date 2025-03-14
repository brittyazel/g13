#ifndef G13_H_
#define G13_H_

#include "g13_device.hpp"
#include "g13_log.hpp"

// *************************************************************************

// Forward declaration of printHelp()
void printHelp();

namespace G13 {
    static constexpr size_t G13_VENDOR_ID = 0x046d;
    static constexpr size_t G13_PRODUCT_ID = 0xc21c;
    static constexpr size_t G13_REPORT_SIZE = 8;

    // const size_t G13_INTERFACE = 0;
    static constexpr size_t G13_KEY_ENDPOINT = 1;
    static constexpr size_t G13_LCD_ENDPOINT = 2;
    // const size_t G13_KEY_READ_TIMEOUT = 0;

    // *************************************************************************

    class G13_CommandException final : public std::exception {
    public:
        explicit G13_CommandException(std::string reason) : _reason(std::move(reason)) {}

        ~G13_CommandException() noexcept override = default;

        [[nodiscard]] const char* what() const noexcept override {
            return _reason.c_str();
        }

        std::string _reason;
    };
} // namespace G13

#endif  // G13_H_
