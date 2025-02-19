#include "clap/plugin.h"
#include "clap/entry.h"

class HelloPlugin {
public:
  static const clap_plugin_descriptor_t descriptor;

  static const clap_plugin_t plugin_interface;

  static uint32_t CLAP_ABI clapGetFeatures(const clap_plugin_t *plugin, const char *const **features) {
    static const char *feature_list[] = {CLAP_PLUGIN_FEATURE_INSTRUMENT, nullptr};
    *features = feature_list;
    return 1;
  }

  static bool CLAP_ABI clapInit(const clap_plugin_t *plugin) {
    // Plugin initialization
    return true;
  }

  static void CLAP_ABI clapDestroy(const clap_plugin_t *plugin) {
    // Cleanup
  }
};

const clap_plugin_descriptor_t HelloPlugin::descriptor = {
  .clap_version = CLAP_VERSION_INIT,
  .id = "com.example.hello-clap",
  .name = "Hello CLAP",
  .vendor = "Example Inc.",
  .url = "https://example.com",
  .version = "1.0.0",
};

const clap_plugin_t HelloPlugin::plugin_interface = {
  .desc = &HelloPlugin::descriptor,
  .plugin_data = nullptr,
  .init = HelloPlugin::clapInit,
  .destroy = HelloPlugin::clapDestroy,
  .get_features = HelloPlugin::clapGetFeatures,
};

// Entry point
extern "C" CLAP_EXPORT const clap_plugin_entry_t clap_entry = {
  .clap_version = CLAP_VERSION_INIT,
  .init = [](const char *path) { return true; },
  .deinit = []() {},
  .get_factory = [](const char *factory_id) {
    if (strcmp(factory_id, CLAP_PLUGIN_FACTORY_ID) == 0) {
      static const clap_plugin_factory_t factory = {
        .get_plugin_count = [](const clap_plugin_factory_t *factory) { return 1; },
        .get_plugin_descriptor = [](const clap_plugin_factory_t *factory, uint32_t index) {
          return &HelloPlugin::descriptor;
        },
        .create_plugin = [](const clap_plugin_factory_t *factory,
                           const clap_host_t *host,
                           const char *plugin_id) {
          return &HelloPlugin::plugin_interface;
        }
      };
      return &factory;
    }
    return nullptr;
  }
};
