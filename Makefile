CFLAGS  = -I../SSD1306_OLED_RPI/include/ 
LDFLAGS = -lbcm2835 -L../SSD1306_OLED_RPI/ -lSSD1306_OLED_RPI

all: ip_disp

ip_disp: main.cpp
	$(CXX) $(CFLAGS) -o ip_disp main.cpp $(LDFLAGS)

install: ip_disp
	@cp ip_disp ../buildroot/output/target/bin/
