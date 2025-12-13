#include "IC746.h"

IC746 radio = IC746();


unsigned long freq	= 144200000l;
unsigned long bfreq	= 144174000l;

bool splitActive = false;

#define VFO_A 0
#define VFO_B 1
uint8_t activeVFO = VFO_A;

//modes
#define MODE_LSB 00
#define MODE_USB 01
uint8_t mode = MODE_USB;

#define PTT_RX 0
#define PTT_TX 1
uint8_t ptt = PTT_TX;

void catSetPtt(bool catPTT) {
	if (catPTT) {
		ptt = PTT_TX;
	} else {
		ptt = PTT_RX;
	}
}

bool catGetPtt() {
	if (ptt == PTT_TX) {
		return true;
	} else {
		return false;
	}
}

void catVfoAtoB() {
	if (activeVFO == VFO_A) {
		bfreq = freq;
	} else {
		freq = bfreq;
	}
}

void catSwapVfo() {
	if (activeVFO == VFO_A) {
		activeVFO = VFO_B;
	} else {
		activeVFO = VFO_A;
	}
}

void catSetSplit(bool catSplit) {
	if (catSplit) {
		splitActive = true;
	} else {
		splitActive = false;
	}
}

void catSetFreq(long f) {
	if (activeVFO == VFO_A) {
		freq = f;
	} else {
		bfreq = f;
	}
}

void catSetMode(uint8_t m) {
	if (m == CAT_MODE_LSB) {
		mode = MODE_LSB;
	} else {
		mode = MODE_USB;
	}
}

void catSetVFO(uint8_t v) {
	if (v == CAT_VFO_A) {
		activeVFO = CAT_VFO_A;
	} else {
		activeVFO = CAT_VFO_B;
	}
}

long catGetFreq() {
	long f;
	
	if (activeVFO == VFO_A) {
		f = freq;
	} else {
		f = bfreq;
	}
	
	return f;
}

uint8_t catGetMode() {
	uint8_t catMode;
	
	if (mode == MODE_LSB) {
		catMode = CAT_MODE_LSB;
	} else {
		catMode = CAT_MODE_USB;
	}
	
	return catMode;
}

uint8_t catGetSMeter() {
	static int s = 0;
	static uint8_t counter = 0;

	if (counter == 5) {
		counter = 0;
		if (s == 15) {
			s = 0;
		} else {
			s++;
		}
	} else {
		counter++;
	}
	
	return uint8_t(s);
}


int main(void)
{
	radio.addCATPtt(catSetPtt);
	radio.addCATGetPtt(catGetPtt);
	radio.addCATAtoB(catVfoAtoB);
	radio.addCATSwapVfo(catSwapVfo);
	radio.addCATsplit(catSetSplit);
	radio.addCATFSet(catSetFreq);
	radio.addCATMSet(catSetMode);
	radio.addCATVSet(catSetVFO);
	radio.addCATGetFreq(catGetFreq);
	radio.addCATGetMode(catGetMode);
	radio.addCATSMeter(catGetSMeter);
	
	radio.begin();
	while(true) {
		radio.check();	
	}
}
