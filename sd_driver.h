#pragma once
#include "esphome.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"
#include "ff.h"

class SDCustom : public Component {
 public:
  FATFS fs; 
  bool is_mounted = false;
  std::string mount_status = "Not Initialized";

  void setup() override {
    mount_status = "Initing...";
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    host.slot = SPI3_HOST;
    host.max_freq_khz = 2000; // Even slower for testing

    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = GPIO_NUM_42;
    slot_config.host_id = (spi_host_device_t)host.slot;

    // Try to mount
    FRESULT res = f_mount(&fs, "0:", 1);
    
    if (res == FR_OK) {
        is_mounted = true;
        mount_status = "Ready";
    } else {
        is_mounted = false;
        // This will print the error code directly to the screen
        mount_status = "Error: " + std::to_string((int)res);
    }
}

  std::string get_file_list() {
  if (!is_mounted) return "SD " + mount_status;
  
  FF_DIR dir;
  FILINFO fno;
  // Attempt to open the root of drive 0
  FRESULT res = f_opendir(&dir, "0:/");
  
  if (res != FR_OK) {
      // This will now report specific FatFS error codes (e.g., 3, 12, 13)
      return "SD Error Code: " + std::to_string((int)res);
  }

  std::string list = "Files Found:\n";
  int count = 0;
  while (f_readdir(&dir, &fno) == FR_OK && fno.fname[0] != 0) {
      if (fno.fname[0] == '.') continue;
      list += "- " + std::string(fno.fname) + "\n";
      count++;
  }
  f_closedir(&dir);
  
  if (count == 0) return "SD Mounted but Empty";
  return list;
}
};