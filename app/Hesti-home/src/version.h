
#include <string>

#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define VERSION_REV 1
#define VERSION_POSTFIX 0


std::uint32_t GetVersionInt(int major = VERSION_MAJOR,
                            int minor = VERSION_MINOR,
                            int patch = VERSION_REV);

std::string GetVersionStr(int major = VERSION_MAJOR,
                          int minor = VERSION_MINOR,
                          int patch = VERSION_REV,
                          const std::string& postfix = VERSION_POSTFIX,
                          const std::string& build_id = BUILD_IDENTIFIER);