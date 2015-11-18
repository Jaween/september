const sampler_t sampler = CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP | CLK_FILTER_NEAREST;

__kernel void background_removal(__read_only image2d_t source, __write_only image2d_t destination) {
  int x = get_global_id(0);
  int y = get_global_id(1);

  // Creates two ABGR float vectors: the background colour to remove and the 
  // pixel to remove it from
  const float4 background_colour = (float4) (0xFF, 0x84, 0xD6, 0x5A);
  const uint pixel = read_imageui(source, sampler, (int2) (x, y)).x;
  uint4 unpacked = (uint4) (
      ((pixel >> 24) & 0x000000FF), 
      ((pixel >> 16) & 0x000000FF), 
      ((pixel >> 8) & 0x000000FF), 
      ((pixel & 0x000000FF)));
  float4 unpacked_float = (float4) (unpacked.x, unpacked.y, unpacked.z, unpacked.w);

  // Determines colour similarity using Euclidean distance (visually inaccurate)
  float dissimilarity = length(background_colour - unpacked_float);
  if (dissimilarity > 80.0f) {
    // Discards pixels that are similar to the background colour
    write_imageui(destination, (int2) (x, y), pixel);
  }
}

__kernel void shrink_image(const float factor, __read_only image2d_t source, __write_only image2d_t destination) {
  int x = get_global_id(0);
  int y = get_global_id(1);

  uint pixel = read_imageui(source, sampler, (int2) (x, y)).x;

  // Nearest-neighbour scaling
  int center_x = get_image_dim(source).x / 2;
  int center_y = get_image_dim(source).y / 2;
  int dest_x = x + ((center_x - x) * factor);
  int dest_y = y + ((center_y - y) * factor);
  write_imageui(destination, (int2) (dest_x, dest_y), pixel);
}