const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP | CLK_FILTER_NEAREST;

__kernel void execute(__read_only image2d_t current_frame, __read_only image2d_t previous_frame, __write_only image2d_t screen) {
	// ?? TODO(jaween): Implement
  int x = get_global_id(0);
  int y = get_global_id(1);

  uint4 write_pixel = (uint4) (0xFF00CC00);
  write_imageui(screen, (int2) (x, y), write_pixel);
}