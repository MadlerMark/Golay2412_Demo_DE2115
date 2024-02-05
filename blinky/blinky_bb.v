
module blinky (
	binary_external_connection_export,
	clk_clk,
	lcd_external_connection_export,
	leds_external_connection_export,
	reset_reset_n,
	start_external_connection_export,
	switches_external_connection_export);	

	input	[1:0]	binary_external_connection_export;
	input		clk_clk;
	output	[11:0]	lcd_external_connection_export;
	output	[1:0]	leds_external_connection_export;
	input		reset_reset_n;
	input		start_external_connection_export;
	input	[2:0]	switches_external_connection_export;
endmodule
