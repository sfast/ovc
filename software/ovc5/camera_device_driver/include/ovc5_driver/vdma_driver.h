#ifndef VDMA_DRIVER_H
#define VDMA_DRIVER_H

#include <string>
#include <vector>
#include <ovc5_driver/uio_driver.h>

class VDMADriver
{
  // framebuffers from different cameras should not overlap
  static int framebuffer_id;
  // Register addresses
  const int VDMACR = 0x30 / sizeof(int);
  const int VDMASR = 0x34 / sizeof(int);
  const int VSIZE_REG = 0xA0 / sizeof(int);
  const int HSIZE_REG = 0xA4 / sizeof(int);
  const int FRMDLY_STRIDE_REG = 0xA8 / sizeof(int);
  const int PARK_PTR_REG = 0x28 / sizeof(int);
  const int START_ADDR_0 = 0xAC / sizeof(int);
  const size_t FRAME_BASEADDR = 0x70000000;
  const size_t FRAME_OFFSET = 0x2000000;

  static constexpr int NUM_FRAMEBUFFERS = 4;

  const size_t UIO_SIZE = 0x1000;
  // UIO is for AXI4 lite configuration, memory is to access DDR and images
  UIODriver uio;
  int memory_file;

  unsigned char *memory_mmap[NUM_FRAMEBUFFERS];
  
  void startVDMA(int res_y);
  void sendFramebuffer(int fb_num, uint32_t address);

  void updateLastFramebuffer();

  int last_fb;

public:

  void setHeader(const std::vector<uint8_t>& header, int index = -1);

  void configureVDMA(int res_x, int res_y, int bit_depth);

  VDMADriver(int uio_num);
  unsigned char* getImage();
};
#endif
