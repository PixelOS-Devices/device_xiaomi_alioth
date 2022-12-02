/*
 * Copyright (C) 2021 Paranoid Android
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <vector>

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <sys/sysinfo.h>

using android::base::GetProperty;

void property_override(char const prop[], char const value[], bool add = true) {
    prop_info* pi;

    pi = (prop_info*)__system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else if (add)
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void load_dalvikvm_properties() {
    struct sysinfo sys;
    sysinfo(&sys);
    if(sys.totalram > 6144ull * 1024 * 1024) {
    // from - phone-xhdpi-8192-dalvik-heap.mk
        property_override("dalvik.vm.heapstartsize", "24m");
        property_override("dalvik.vm.heaptargetutilization", "0.46");
        property_override("dalvik.vm.heapmaxfree", "48m");
    }

    else {
    // from - phone-xhdpi-6144-dalvik-heap.mk
        property_override("dalvik.vm.heapstartsize", "16m");
        property_override("dalvik.vm.heaptargetutilization", "0.5");
        property_override("dalvik.vm.heapmaxfree", "32m");
    }
    property_override("dalvik.vm.heapgrowthlimit", "256m");
    property_override("dalvik.vm.heapsize", "512m");
    property_override("dalvik.vm.heapminfree", "8m");
}

void load_redmi_k40() {
    property_override("ro.boot.product.hardware.sku", "nfc");
    property_override("ro.product.model", "M2012K11AC");
    property_override("ro.product.brand", "Redmi");
    property_override("ro.product.vendor.marketname", "Redmi K40");
    property_override("ro.product.vendor.manufacturer", "Xiaomi");
    property_override("ro.product.vendor.brand", "Redmi");
    property_override("ro.product.vendor.model", "M2012K11AC");
}

void load_poco_f3() {
    property_override("ro.boot.product.hardware.sku", "nfc");
    property_override("ro.product.model", "M2012K11AG");
    property_override("ro.product.brand", "POCO");
    property_override("ro.product.vendor.marketname", "POCO F3");
    property_override("ro.product.vendor.manufacturer", "Xiaomi");
    property_override("ro.product.vendor.brand", "POCO");
    property_override("ro.product.vendor.model", "M2012K11AG");
}

void load_xiaomi_mi11x() {
    property_override("ro.product.model", "M2012K11AI");
    property_override("ro.product.brand", "Mi");
    property_override("ro.product.vendor.marketname", "Mi 11X");
    property_override("ro.product.vendor.manufacturer", "Xiaomi");
    property_override("ro.product.vendor.brand", "Mi");
    property_override("ro.product.vendor.model", "M2012K11AI");
}

void vendor_load_properties() {
    std::string region = GetProperty("ro.boot.hwc", "");
    if (region.find("CN") != std::string::npos) {
        load_redmi_k40();
    } else if (region.find("INDIA") != std::string::npos) {
        load_xiaomi_mi11x();
    } else {
        load_poco_f3();
    }
    
    load_dalvikvm_properties();
}