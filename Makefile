LDFLAGS = -lbcm2835 -lSSD1306_OLED_RPI

all: i2c_ipstat

i2c_ipstat: main.cpp
	$(CXX) -o i2c_ipstat main.cpp $(LDFLAGS)

