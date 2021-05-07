module color_mapper (input  logic        clk,
                     input  logic        blank,
                     input  logic [9:0]  x, y,
                     input  logic [31:0] control,
                     output logic [3:0]  red, green, blue);

   logic [7:0] index;
   logic [11:0] rgb;
   logic [11:0] pallete [16];
   logic [3:0] pixels [65536];
   logic [7:0] indices [1200];

   assign index = indices[(y / 16) * 40 + x / 16];
   assign rgb = pallete[pixels[index * 256 + (y % 16) * 16 + x % 16]];

   initial
   begin
      $readmemh("pallete.txt", pallete);
      $readmemh("sprite_sheet.txt", pixels);
   end

   always_ff @ (posedge clk)
   begin
      indices[control[13:8] * 40 + control[19:14]] <= control[7:0];
   end

   always_comb
   begin
      if (~blank)
         begin
            red = 4'h0;
            green = 4'h0;
            blue = 4'h0;
         end
      else
         begin
            red = rgb[11:8];
            green = rgb[7:4];
            blue = rgb[3:0];
         end
   end

endmodule
