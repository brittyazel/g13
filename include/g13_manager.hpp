//
// Created by khampf on 13-05-2020.
//

#ifndef G13_MANAGER_HPP
#define G13_MANAGER_HPP

#include "g13_device.hpp"
#include "g13_keys.hpp"
#include "g13_log.hpp"
#include "g13_manager.hpp"
#include <libusb-1.0/libusb.h>

/*!
 * top level class, holds what would otherwise be in global variables
 */
namespace G13 {
    class G13_Manager {

    public:
        G13_Manager();

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
        static const int class_id;

        // static const std::string &getLogoFilename();
        static void setLogoFilename(const std::string& newLogoFilename);

        [[nodiscard]] static int FindG13KeyValue(const std::string& keyname);

        [[nodiscard]] static std::string FindG13KeyName(int v);

        [[nodiscard]] static G13_State_Key FindInputKeyValue(const std::string& keyname, bool down = true);

        [[nodiscard]] static std::string FindInputKeyName(LINUX_KEY_VALUE v);

        [[nodiscard]] static LINUX_KEY_VALUE InputKeyMax() {
            return input_key_max;
        }

        static int Run();

        [[nodiscard]] static std::string getStringConfigValue(const std::string& name);

        static void setStringConfigValue(const std::string& name, const std::string& value);

        static std::string MakePipeName(const G13_Device* usb_device, bool is_input);

        static void start_logging();

        [[maybe_unused]] static void SetLogLevel(log4cpp::Priority::PriorityLevel lvl);

        static void SetLogLevel(const std::string& level);

    protected:
        static void InitKeynames();

        static void DisplayKeys();

        static void DiscoverG13s(libusb_device** devs, ssize_t count);

        static void Cleanup();

        static void SignalHandler(int);

        static void SetupDevice(G13_Device* g13);

        static int LIBUSB_CALL HotplugCallbackEnumerate(libusb_context* usb_context, libusb_device* dev,
                                                        libusb_hotplug_event event, void* user_data);

        static int LIBUSB_CALL HotplugCallbackInsert(libusb_context* usb_context, libusb_device* dev,
                                                     libusb_hotplug_event event, void* user_data);

        static int LIBUSB_CALL HotplugCallbackRemove(libusb_context* usb_context, libusb_device* dev,
                                                     libusb_hotplug_event event, void* user_data);

        static int OpenAndAddG13(libusb_device* dev);

        static void ArmHotplugCallbacks();
    };
} // namespace G13

#endif // G13_MANAGER_HPP
