	component blinky is
		port (
			binary_external_connection_export   : in  std_logic_vector(1 downto 0)  := (others => 'X'); -- export
			clk_clk                             : in  std_logic                     := 'X';             -- clk
			lcd_external_connection_export      : out std_logic_vector(11 downto 0);                    -- export
			leds_external_connection_export     : out std_logic_vector(1 downto 0);                     -- export
			reset_reset_n                       : in  std_logic                     := 'X';             -- reset_n
			start_external_connection_export    : in  std_logic                     := 'X';             -- export
			switches_external_connection_export : in  std_logic_vector(2 downto 0)  := (others => 'X')  -- export
		);
	end component blinky;

	u0 : component blinky
		port map (
			binary_external_connection_export   => CONNECTED_TO_binary_external_connection_export,   --   binary_external_connection.export
			clk_clk                             => CONNECTED_TO_clk_clk,                             --                          clk.clk
			lcd_external_connection_export      => CONNECTED_TO_lcd_external_connection_export,      --      lcd_external_connection.export
			leds_external_connection_export     => CONNECTED_TO_leds_external_connection_export,     --     leds_external_connection.export
			reset_reset_n                       => CONNECTED_TO_reset_reset_n,                       --                        reset.reset_n
			start_external_connection_export    => CONNECTED_TO_start_external_connection_export,    --    start_external_connection.export
			switches_external_connection_export => CONNECTED_TO_switches_external_connection_export  -- switches_external_connection.export
		);

