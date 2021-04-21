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


module color_mapper(input        [9:0] draw_x, draw_y,
                    output logic [7:0] red, green, blue);

	 assign red = 8'h00; 
    assign green = 8'h00;
    assign blue = 8'h7f - draw_x[9:3];
    
endmodule
