//-------------------------------------------------------------------------
//    Color_Mapper.sv                                                    --
//    Stephen Kempf                                                      --
//    3-1-06                                                             --
//                                                                       --
//    Modified by David Kesler  07-16-2008                               --
//    Translated by Joe Meng    07-07-2013                               --
//                                                                       --
//    Fall 2014 Distribution                                             --
//                                                                       --
//    For use with ECE 385 Lab 7                                         --
//    University of Illinois ECE Department                              --
//-------------------------------------------------------------------------


module color_mapper(input  logic       blank,
                    input  logic [9:0] draw_x, draw_y,
                    output logic [7:0] red, green, blue);

   always_comb
   begin
      if (~blank)
         begin
            red = 8'h00;
            green = 8'h00;
            blue = 8'h00;
         end
      else
         begin
            red = 8'hff;
            green = 8'h55;
            blue = 8'h00;
         end
   end

endmodule
