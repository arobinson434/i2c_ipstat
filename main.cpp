#include <iostream>
#include <bcm2835.h>

#include <cstdio>
#include <cstring>
#include <regex>

#include "SSD1306_OLED.hpp"


#define OLED_W  128
#define OLED_H  32
#define OLED_FS ( OLED_W * (OLED_H/8) )

std::string getIpStr() {
    std::string ret_val;
    char*       buffer = new char[1000];

    std::FILE* ip_file = fopen("/proc/net/fib_trie", "r");
    std::fread(buffer, 1, 1000, ip_file);
    std::fclose(ip_file);

    const char*      read_ptr = buffer;
    const std::regex base(".*\\s+([0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+)\\s*\n\\s+/32 host LOCAL");
    std::cmatch      match;

    while( std::regex_search(read_ptr, match, base) ) {
        if ( match.str(1) != "127.0.0.1" )
            ret_val = match.str(1);
        read_ptr = strchr(read_ptr + match.position(), '\n');
    }

    delete buffer;
    return ret_val;
}

void showIp(SSD1306& display) {
    std::string display_text;
    std::string ip_text    = "IP: "+getIpStr();
    size_t      ip_text_sz = ip_text.size();

    for( uint8_t i=0; i < 42; i++ ){
        if( i < ip_text_sz )
            display_text = ip_text[ip_text_sz-1-i] + display_text;
        else if( i >= ip_text_sz && i < 21 )
            display_text = " " + display_text;
        else {
            display_text = " " + display_text;
            display_text.pop_back();
        }

        display.OLEDclearBuffer();
        display.setCursor(0,16);
        display.print(display_text);
        display.OLEDupdate();

        if( i == ip_text_sz-1 )
            delay(5000);
        else
            delay(100);
    }
}

int main() {
    SSD1306 display(OLED_W, OLED_H);
    uint8_t screen_buf[OLED_FS];

	if ( !bcm2835_init() ) {
		std::cout << "Failed to init the bcm2835 library! Exiting...\n";
		return -1;
	}

    if ( !display.OLED_I2C_ON() ) {
        std::cout << "Failed to turn on the display! Exiting...\n";
        bcm2835_close();
        return -2;
    }

	display.OLEDbegin();
    if ( !display.OLEDSetBufferPtr(OLED_W, OLED_H, screen_buf, sizeof(screen_buf)) )
        return -3;

    display.setTextColor(WHITE);

    while( 1 ) {
        showIp(display);
        delay(2000);
    }

    display.OLEDPowerDown();
    display.OLED_I2C_OFF();
    bcm2835_close();

    return 0;
}
