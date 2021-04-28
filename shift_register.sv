module shift_register #(N = 32) (input                clk,
                                 input                shift_enable,
                                 input                shift_in,
                                 input                load,
                                 input        [N-1:0] data_in,
                                 output logic [N-1:0] data_out,
                                 output logic         shift_out);

   always_ff @ (posedge clk)
   begin
      if (load)
         data_out <= data_in;
      else if (shift_enable)
         data_out <= { data_out[N-2:0], shift_in };
   end

   assign shift_out = data_out[N-1];

endmodule
