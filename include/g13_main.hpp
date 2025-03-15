#ifndef G13_H_
#define G13_H_

#include "g13_device.hpp"
#include "g13_keys.hpp"
#include "g13_log.hpp"
#include <libusb-1.0/libusb.h>
#include <log4cpp/Priority.hh>

// *************************************************************************

namespace G13 {
    static constexpr size_t G13_VENDOR_ID = 0x046d;
    static constexpr size_t G13_PRODUCT_ID = 0xc21c;
    static constexpr size_t G13_REPORT_SIZE = 8;

    // const size_t G13_INTERFACE = 0;
    static constexpr size_t G13_KEY_ENDPOINT = 1;
    static constexpr size_t G13_LCD_ENDPOINT = 2;
    // const size_t G13_KEY_READ_TIMEOUT = 0;

    void printHelp();


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


    // declarations
    static bool running;
    static std::map<std::string, std::string> stringConfigValues;
    static libusb_context* usb_context;
    static std::vector<G13_Device*> g13s;
    static libusb_hotplug_callback_handle usb_hotplug_cb_handle[3];
    static std::map<G13_KEY_INDEX, std::string> g13_key_to_name;
    static std::map<std::string, G13_KEY_INDEX> g13_name_to_key;
    static std::map<LINUX_KEY_VALUE, std::string> input_key_to_name;
    static std::map<std::string, LINUX_KEY_VALUE> input_name_to_key;
    static LINUX_KEY_VALUE input_key_max;
    static libusb_device** devs;
    static std::string logoFilename;
    static int class_id;

    // static const std::string &getLogoFilename();
    static void setLogoFilename(const std::string& newLogoFilename);

    int FindG13KeyValue(const std::string& keyname);

    std::string FindG13KeyName(int v);

    G13_State_Key FindInputKeyValue(const std::string& keyname, bool down = true);

    std::string FindInputKeyName(LINUX_KEY_VALUE v);

    [[nodiscard]] static LINUX_KEY_VALUE InputKeyMax() {
        return input_key_max;
    }

    int Run();

    std::string getStringConfigValue(const std::string& name);

    void setStringConfigValue(const std::string& name, const std::string& value);

    std::string MakePipeName(const G13_Device* usb_device, bool is_input);

    void start_logging();

    void SetLogLevel(log4cpp::Priority::PriorityLevel lvl);
    void SetLogLevel(const std::string& level);


    void InitKeynames();

    void DisplayKeys();

    void DiscoverG13s(libusb_device** devs, ssize_t count);

    void Cleanup();

    void SignalHandler(int);

    void SetupDevice(G13_Device* g13);

    int LIBUSB_CALL HotplugCallbackEnumerate(libusb_context* usb_context, libusb_device* dev,
                                                    libusb_hotplug_event event, void* user_data);

    int LIBUSB_CALL HotplugCallbackInsert(libusb_context* usb_context, libusb_device* dev,
                                                 libusb_hotplug_event event, void* user_data);

    int LIBUSB_CALL HotplugCallbackRemove(libusb_context* usb_context, libusb_device* dev,
                                                 libusb_hotplug_event event, void* user_data);

    int OpenAndAddG13(libusb_device* dev);

    void ArmHotplugCallbacks();
} // namespace G13

#endif  // G13_H_
