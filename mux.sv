module mux421 (input [3:0]  data_in,
               input [1:0]  select,
               output logic data_out);

   always_comb
   begin
      if (select == 2'b00)
         data_out = data_in[0];
      else if (select == 2'b01)
         data_out = data_in[1];
      else if (select == 2'b10)
         data_out = data_in[2];
      else
         data_out = data_in[3];
   end

endmodule

module mux81922512 (input [8191:0]       data_in,
                    input [3:0]          select,
                    output logic [511:0] data_out);

   always_comb
   begin
      if (select == 4'h0)
         data_out = data_in[512*1-1:512*0];
      else if (select == 4'h1)
         data_out = data_in[512*2-1:512*1];
      else if (select == 4'h2)
         data_out = data_in[512*3-1:512*2];
      else if (select == 4'h3)
         data_out = data_in[512*4-1:512*3];
      else if (select == 4'h4)
         data_out = data_in[512*5-1:512*4];
      else if (select == 4'h5)
         data_out = data_in[512*6-1:512*5];
      else if (select == 4'h6)
         data_out = data_in[512*7-1:512*6];
      else if (select == 4'h7)
         data_out = data_in[512*8-1:512*7];
      else if (select == 4'h8)
         data_out = data_in[512*9-1:512*8];
      else if (select == 4'h9)
         data_out = data_in[512*10-1:512*9];
      else if (select == 4'ha)
         data_out = data_in[512*11-1:512*10];
      else if (select == 4'hb)
         data_out = data_in[512*12-1:512*11];
      else if (select == 4'hc)
         data_out = data_in[512*13-1:512*12];
      else if (select == 4'hd)
         data_out = data_in[512*14-1:512*13];
      else if (select == 4'he)
         data_out = data_in[512*15-1:512*14];
      else
         data_out = data_in[512*16-1:512*15];
   end

endmodule

module mux512232 (input [511:0]       data_in,
                  input [3:0]         select,
                  output logic [31:0] data_out);

   always_comb
   begin
      if (select == 4'h0)
         data_out = data_in[32*1-1:32*0];
      else if (select == 4'h1)
         data_out = data_in[32*2-1:32*1];
      else if (select == 4'h2)
         data_out = data_in[32*3-1:32*2];
      else if (select == 4'h3)
         data_out = data_in[32*4-1:32*3];
      else if (select == 4'h4)
         data_out = data_in[32*5-1:32*4];
      else if (select == 4'h5)
         data_out = data_in[32*6-1:32*5];
      else if (select == 4'h6)
         data_out = data_in[32*7-1:32*6];
      else if (select == 4'h7)
         data_out = data_in[32*8-1:32*7];
      else if (select == 4'h8)
         data_out = data_in[32*9-1:32*8];
      else if (select == 4'h9)
         data_out = data_in[32*10-1:32*9];
      else if (select == 4'ha)
         data_out = data_in[32*11-1:32*10];
      else if (select == 4'hb)
         data_out = data_in[32*12-1:32*11];
      else if (select == 4'hc)
         data_out = data_in[32*13-1:32*12];
      else if (select == 4'hd)
         data_out = data_in[32*14-1:32*13];
      else if (select == 4'he)
         data_out = data_in[32*15-1:32*14];
      else
         data_out = data_in[32*16-1:32*15];
   end

endmodule

module mux8192232 (input [8191:0]      data_in,
                   input [7:0]         select,
                   output logic [31:0] data_out);

   logic [511:0] horizontal;

   mux81922512 mux0 (.data_in(data_in), .select(select / 16), .data_out(horizontal));
   mux512232 mux1(.data_in(horizontal), .select(select % 16), .data_out(data_out));

endmodule

module mux96002320 (input [9599:0]       data_in,
                    input [5:0]          select,
                    output logic [319:0] data_out);

   always_comb
   begin
      if (select == 6'h00)
         data_out = data_in[320*1-1:320*0];
      else if (select == 6'h01)
         data_out = data_in[320*2-1:320*1];
      else if (select == 6'h02)
         data_out = data_in[320*3-1:320*2];
      else if (select == 6'h03)
         data_out = data_in[320*4-1:320*3];
      else if (select == 6'h04)
         data_out = data_in[320*5-1:320*4];
      else if (select == 6'h05)
         data_out = data_in[320*6-1:320*5];
      else if (select == 6'h06)
         data_out = data_in[320*7-1:320*6];
      else if (select == 6'h07)
         data_out = data_in[320*8-1:320*7];
      else if (select == 6'h08)
         data_out = data_in[320*9-1:320*8];
      else if (select == 6'h09)
         data_out = data_in[320*10-1:320*9];
      else if (select == 6'h0a)
         data_out = data_in[320*11-1:320*10];
      else if (select == 6'h0b)
         data_out = data_in[320*12-1:320*11];
      else if (select == 6'h0c)
         data_out = data_in[320*13-1:320*12];
      else if (select == 6'h0d)
         data_out = data_in[320*14-1:320*13];
      else if (select == 6'h0e)
         data_out = data_in[320*15-1:320*14];
      else if (select == 6'h0f)
         data_out = data_in[320*16-1:320*15];
      else if (select == 6'h10)
         data_out = data_in[320*17-1:320*16];
      else if (select == 6'h11)
         data_out = data_in[320*18-1:320*17];
      else if (select == 6'h12)
         data_out = data_in[320*19-1:320*18];
      else if (select == 6'h13)
         data_out = data_in[320*20-1:320*19];
      else if (select == 6'h14)
         data_out = data_in[320*21-1:320*20];
      else if (select == 6'h15)
         data_out = data_in[320*22-1:320*21];
      else if (select == 6'h16)
         data_out = data_in[320*23-1:320*22];
      else if (select == 6'h17)
         data_out = data_in[320*24-1:320*23];
      else if (select == 6'h18)
         data_out = data_in[320*25-1:320*24];
      else if (select == 6'h19)
         data_out = data_in[320*26-1:320*25];
      else if (select == 6'h1a)
         data_out = data_in[320*27-1:320*26];
      else if (select == 6'h1b)
         data_out = data_in[320*28-1:320*27];
      else if (select == 6'h1c)
         data_out = data_in[320*29-1:320*28];
      else
         data_out = data_in[320*30-1:320*29];
   end

endmodule

module mux32028 (input [319:0]      data_in,
                 input [5:0]        select,
                 output logic [7:0] data_out);

   always_comb
   begin
      if (select == 6'h00)
         data_out = data_in[8*1-1:8*0];
      else if (select == 6'h01)
         data_out = data_in[8*2-1:8*1];
      else if (select == 6'h02)
         data_out = data_in[8*3-1:8*2];
      else if (select == 6'h03)
         data_out = data_in[8*4-1:8*3];
      else if (select == 6'h04)
         data_out = data_in[8*5-1:8*4];
      else if (select == 6'h05)
         data_out = data_in[8*6-1:8*5];
      else if (select == 6'h06)
         data_out = data_in[8*7-1:8*6];
      else if (select == 6'h07)
         data_out = data_in[8*8-1:8*7];
      else if (select == 6'h08)
         data_out = data_in[8*9-1:8*8];
      else if (select == 6'h09)
         data_out = data_in[8*10-1:8*9];
      else if (select == 6'h0a)
         data_out = data_in[8*11-1:8*10];
      else if (select == 6'h0b)
         data_out = data_in[8*12-1:8*11];
      else if (select == 6'h0c)
         data_out = data_in[8*13-1:8*12];
      else if (select == 6'h0d)
         data_out = data_in[8*14-1:8*13];
      else if (select == 6'h0e)
         data_out = data_in[8*15-1:8*14];
      else if (select == 6'h0f)
         data_out = data_in[8*16-1:8*15];
      else if (select == 6'h10)
         data_out = data_in[8*17-1:8*16];
      else if (select == 6'h11)
         data_out = data_in[8*18-1:8*17];
      else if (select == 6'h12)
         data_out = data_in[8*19-1:8*18];
      else if (select == 6'h13)
         data_out = data_in[8*20-1:8*19];
      else if (select == 6'h14)
         data_out = data_in[8*21-1:8*20];
      else if (select == 6'h15)
         data_out = data_in[8*22-1:8*21];
      else if (select == 6'h16)
         data_out = data_in[8*23-1:8*22];
      else if (select == 6'h17)
         data_out = data_in[8*24-1:8*23];
      else if (select == 6'h18)
         data_out = data_in[8*25-1:8*24];
      else if (select == 6'h19)
         data_out = data_in[8*26-1:8*25];
      else if (select == 6'h1a)
         data_out = data_in[8*27-1:8*26];
      else if (select == 6'h1b)
         data_out = data_in[8*28-1:8*27];
      else if (select == 6'h1c)
         data_out = data_in[8*29-1:8*28];
      else if (select == 6'h1d)
         data_out = data_in[8*30-1:8*29];
      else if (select == 6'h1e)
         data_out = data_in[8*31-1:8*30];
      else if (select == 6'h1f)
         data_out = data_in[8*32-1:8*31];
      else if (select == 6'h20)
         data_out = data_in[8*33-1:8*32];
      else if (select == 6'h21)
         data_out = data_in[8*34-1:8*33];
      else if (select == 6'h22)
         data_out = data_in[8*35-1:8*34];
      else if (select == 6'h23)
         data_out = data_in[8*36-1:8*35];
      else if (select == 6'h24)
         data_out = data_in[8*37-1:8*36];
      else if (select == 6'h25)
         data_out = data_in[8*38-1:8*37];
      else if (select == 6'h26)
         data_out = data_in[8*39-1:8*38];
      else
         data_out = data_in[8*40-1:8*39];
   end

endmodule

module mux960028 (input [9599:0]     data_in,
                  input [11:0]       select,
                  output logic [7:0] data_out);

   logic [319:0] horizontal;

   mux96002320 mux0 (.data_in(data_in), .select(select / 40), .data_out(horizontal));
   mux32028 mux1(.data_in(horizontal), .select(select % 40), .data_out(data_out));

endmodule
