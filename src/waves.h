#ifndef WAVES_H
#define WAVES_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <hw/pci.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <sys/mman.h>
#include <math.h>
#include <time.h>
#include "global_args.h"
#include "utils.h"

#define INTERRUPT iobase[1] + 0 // Badr1 + 0 : also ADC register
#define MUXCHAN iobase[1] + 2   // Badr1 + 2
#define TRIGGER iobase[1] + 4   // Badr1 + 4
#define AUTOCAL iobase[1] + 6   // Badr1 + 6
#define DA_CTLREG iobase[1] + 8 // Badr1 + 8

#define AD_DATA iobase[2] + 0    // Badr2 + 0
#define AD_FIFOCLR iobase[2] + 2 // Badr2 + 2

#define TIMER0 iobase[3] + 0     // Badr3 + 0
#define TIMER1 iobase[3] + 1     // Badr3 + 1
#define TIMER2 iobase[3] + 2     // Badr3 + 2
#define COUNTCTL iobase[3] + 3   // Badr3 + 3
#define DIO_PORTA iobase[3] + 4  // Badr3 + 4
#define DIO_PORTB iobase[3] + 5  // Badr3 + 5
#define DIO_PORTC iobase[3] + 6  // Badr3 + 6
#define DIO_CTLREG iobase[3] + 7 // Badr3 + 7
#define PACER1 iobase[3] + 8     // Badr3 + 8
#define PACER2 iobase[3] + 9     // Badr3 + 9
#define PACER3 iobase[3] + a     // Badr3 + a
#define PACERCTL iobase[3] + b   // Badr3 + b

#define DA_Data iobase[4] + 0    // Badr4 + 0
#define DA_FIFOCLR iobase[4] + 2 // Badr4 + 2

int badr[5]; // PCI 2.2 assigns 6 IO base addresses
// -----------------------------------------------
struct pci_dev_info info;
void *hdl;

uintptr_t iobase[6];
uintptr_t dio_in;
uintptr_t current_input;
uint16_t adc_in;

unsigned int count;
unsigned short chan;
// -----------------------------------------------

// This function setup PCI
void setupPCI();

// This function generates waveform based on the current value of waveforms, amplitude and frequency
// Argument:
//      waveforms: waveforms chosen
//      amplitude: amplitude chosen
//      frequency: frequency chosen
void generateWave(const int waveforms, const float amplitude, const float frequency);

// This function detachs PCI
void detachPCI();

// This function reads potentionmeter
void *readADC(void* arg);

// This function reads digital switch
void *readDIO(void* arg);

#endif
