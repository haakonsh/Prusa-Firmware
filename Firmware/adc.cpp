#include "adc.h"
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include "pins.h"

static uint8_t adc_count; //used for oversampling
static uint8_t adc_channel_idx; //bitmask index
volatile int16_t adc_values[ADC_CHAN_CNT];  // Changed from uint to int for differential inputs

static void adc_reset();
static bool adc_setmux(uint8_t ch);
// volatile uint8_t chn = 0;

void adc_init()
{
	puts_P(PSTR("adc_init"));
    DIDR0 = (ADC_DIDR_MSK & 0xff); //disable digital inputs PORTF
    DIDR2 = (ADC_DIDR_MSK >> 8); //disable digital inputs PORTK
    ADMUX |= (1 << REFS0); //use AVCC as reference

    //enable ADC, set prescaler/128, enable interrupt
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADIF) | (1 << ADIE);
}

static void adc_reset()
{  
    ADCSRA &= ~(1 << ADSC); //stop conversion just in case
    adc_count = 0;
    adc_channel_idx = 0;
    while(adc_channel_idx < ADC_CHAN_CNT) // Finds first channel
    {
        if(adc_setmux(adc_channel_idx))
        {
            break;
        }
        else
        {
            adc_channel_idx++;
        }            
    }
    // SERIAL_PROTOCOL("\nFirst channel index: ");
    // SERIAL_PROTOCOL_F(adc_channel_idx, DEC);
    memset((void*)adc_values, 0, sizeof(adc_values));
}

static bool adc_setmux(uint8_t ch_idx)
{
	ADCSRB &= ~(1 << MUX5);
    ADMUX &= ~(0x1F);

    switch (ch_idx)
    {
        #if defined TEMP_0_CHN
            case TEMP_0_IDX:
                #if (TEMP_0_CHN & (1 << 5)) 
                    ADCSRB |= (1 << MUX5);
                #endif
                    ADMUX |= TEMP_0_CHN & 0x1F;                    
                    // SERIAL_PROTOCOL("TEMP_0_CHN: ");
                    // SERIAL_PROTOCOLLNE(TEMP_0_CHN, DEC);
                return true;
        #endif  // TEMP_0_CHN

        #if defined TEMP_1_CHN
            case TEMP_1_IDX:
                #if (TEMP_1_CHN & (1 << 5)) 
                    ADCSRB |= (1 << MUX5);
                #endif
                    ADMUX |= TEMP_1_CHN & 0x1F;
                    // SERIAL_PROTOCOL("TEMP_1_CHN: ");
                    // SERIAL_PROTOCOLLNE(TEMP_1_CHN, DEC);
                return true;
        #endif  // TEMP_1_CHN

        #if defined TEMP_2_CHN
            case TEMP_2_IDX:
                #if (TEMP_2_CHN & (1 << 5)) 
                    ADCSRB |= (1 << MUX5);
                #endif
                    ADMUX |= TEMP_2_CHN & 0x1F;
                    // SERIAL_PROTOCOL("ADMUX: ");
                    // SERIAL_PROTOCOL_F((ADMUX & 0x1F), DEC);
                    // SERIAL_PROTOCOL("   TEMP_2_CHN: ");
                    // SERIAL_PROTOCOLLNE(TEMP_2_CHN, DEC);
                return true;
        #endif  // TEMP_2_CHN

        #if defined TEMP_BED_CHN
            case TEMP_BED_IDX:
                #if (TEMP_BED_CHN & (1 << 5)) 
                    ADCSRB |= (1 << MUX5);
                #endif
                ADMUX |= TEMP_BED_CHN & 0x1F;
                // SERIAL_PROTOCOL("ADCSRB: ");
                // SERIAL_PROTOCOL_F(((ADCSRB & (1 << MUX5))), DEC);
                // SERIAL_PROTOCOL("   ADMUX: ");
                // SERIAL_PROTOCOL_F((ADMUX & 0x1F), DEC);
                // SERIAL_PROTOCOL("   TEMP_BED_CHN: ");
                // SERIAL_PROTOCOLLNE(TEMP_BED_CHN, DEC);
                return true;
        #endif  // TEMP_BED_CHN
        
        #if defined TEMP_AMBIENT_CHN
            case TEMP_AMBIENT_IDX:
                #if (TEMP_AMBIENT_CHN & (1 << 5)) 
                    ADCSRB |= (1 << MUX5);
                #endif
                    ADMUX = (ADMUX & ~(0x1F)) | (TEMP_AMBIENT_CHN & 0x1F);
                    // SERIAL_PROTOCOL("TEMP_AMBIENT_CHN: ");
                    // SERIAL_PROTOCOLLNE(TEMP_AMBIENT_CHN, DEC);
                return true;
        #endif  // TEMP_AMBIENT_CHN

        #if defined TEMP_PINDA_CHN
            case TEMP_PINDA_IDX:
                #if (TEMP_PINDA_CHN & (1 << 5)) 
                    ADCSRB |= (1 << MUX5);
                #endif
                    ADMUX = (ADMUX & ~(0x1F)) | (TEMP_PINDA_CHN & 0x1F);
                    // SERIAL_PROTOCOL("TEMP_PINDA_CHN: ");
                    // SERIAL_PROTOCOLLNE(TEMP_PINDA_CHN, DEC);
                return true;
        #endif  // TEMP_PINDA_CHN

        #if defined VOLT_PWR_CHN
            case VOLT_PWR_IDX:
                #if (VOLT_PWR_CHN & (1 << 5)) 
                    ADCSRB |= (1 << MUX5);
                #endif
                    ADMUX = (ADMUX & ~(0x1F)) | (VOLT_PWR_CHN & 0x1F);
                    // SERIAL_PROTOCOL("VOLT_PWR_CHN: ");
                    // SERIAL_PROTOCOLLNE(VOLT_PWR_CHN, DEC);
                return true;
        #endif  // VOLT_PWR_CHN

        #if defined VOLT_BED_CHN
            case VOLT_BED_IDX:
                #if (VOLT_BED_CHN & (1 << 5)) 
                    ADCSRB |= (1 << MUX5);
                #endif
                    ADMUX = (ADMUX & ~(0x1F)) | (VOLT_BED_CHN & 0x1F);
                    // SERIAL_PROTOCOL("VOLT_BED_CHN: ");
                    // SERIAL_PROTOCOLLNE(VOLT_BED_CHN, DEC);
                return true;
        #endif  // VOLT_BED_CHN

        #if defined VOLT_IR_CHN
            case VOLT_IR_IDX:
                #if (VOLT_IR_CHN & (1 << 5)) 
                    ADCSRB |= (1 << MUX5);
                #endif
                    ADMUX = (ADMUX & ~(0x1F)) | (VOLT_IR_CHN & 0x1F);
                    // SERIAL_PROTOCOL("VOLT_IR_CHN: ");
                    // SERIAL_PROTOCOLLNE(VOLT_IR_CHN, DEC);
                return true;            
        #endif  // VOLT_IR_CHN

        default:
            // SERIAL_PROTOCOL("\nChannel index not in use: ");
            // SERIAL_PROTOCOL_F(ch_idx, DEC);
            return false;        
    }
}

void adc_start_cycle() {
	adc_reset();
	ADCSRA |= (1 << ADSC); //start conversion
}

#ifdef ADC_CALLBACK
extern void ADC_CALLBACK();
#endif //ADC_CALLBACK

ISR(ADC_vect)
{
#if defined(HEATER_0_USES_PT1000_DIFF_10X_GAIN)
    
    if((adc_channel_idx == TEMP_0_IDX) && (ADC & 0x200))    // Check the sign bit (10th)
    {        
        adc_values[adc_channel_idx] += ADC | 0xFC00; // Pad 1's (two's complement)
    }
    else
#endif //HEATER_0_USES_PT1000_DIFF_10X_GAIN
    {
        adc_values[adc_channel_idx] += ADC;
    }

      
    if (++adc_count == ADC_OVRSAMPL) 
    {
        // find the next channel
        while (++adc_channel_idx) {            
            if (adc_channel_idx == ADC_CHAN_CNT) {
#ifdef ADC_CALLBACK
                ADC_CALLBACK();
#endif
                return; // do not start the next measurement since there are no channels remaining
            }
            // go to the next channel
            if (adc_setmux(adc_channel_idx)) {
                adc_count = 0;
                // chn = (ADMUX & 0x1F);
                // if(ADCSRB & (1 << MUX5))
                // {
                //     chn |= (1 << 5);
                // }
                // switch(chn)
                // {
                //     #if defined TEMP_0_CHN
                //         case TEMP_0_CHN:
                //             SERIAL_PROTOCOLLN("ADC channel: TEMP_0_CHN");
                //             SERIAL_PROTOCOL("Channel: ");
                //             SERIAL_PROTOCOL_F(chn, DEC);
                //             SERIAL_PROTOCOL("   adc_channel_idx: ");
                //             SERIAL_PROTOCOLLNE(adc_channel_idx, DEC);
                //             break;            
                //     #endif  // TEMP_0_CHN
                //     #if defined TEMP_BED_CHN
                //         case TEMP_BED_CHN:
                //             SERIAL_PROTOCOLLN("ADC channel: TEMP_BED_CHN");
                //             SERIAL_PROTOCOL("Channel: ");
                //             SERIAL_PROTOCOL_F(chn, DEC);
                //             SERIAL_PROTOCOL("   adc_channel_idx: ");
                //             SERIAL_PROTOCOLLNE(adc_channel_idx, DEC);
                //             break;
                //     #endif  // TEMP_BED_CHN
                //     #if defined TEMP_PINDA_CHN
                //         case TEMP_PINDA_CHN:
                //             SERIAL_PROTOCOLLN("ADC channel: TEMP_PINDA_CHN");
                //             SERIAL_PROTOCOL("Channel: ");
                //             SERIAL_PROTOCOL_F(chn, DEC);
                //             SERIAL_PROTOCOL("   adc_channel_idx: ");
                //             SERIAL_PROTOCOLLNE(adc_channel_idx, DEC);
                //             break;
                //     #endif  // TEMP_PINDA_CHN
                //     #if defined VOLT_PWR_CHN
                //         case VOLT_PWR_CHN:
                //             SERIAL_PROTOCOLLN("ADC channel: VOLT_PWR_CHN");
                //             SERIAL_PROTOCOL("Channel: ");
                //             SERIAL_PROTOCOL_F(chn, DEC);
                //             SERIAL_PROTOCOL("   adc_channel_idx: ");
                //             SERIAL_PROTOCOLLNE(adc_channel_idx, DEC);

                //             break;
                //     #endif  // VOLT_PWR_CHN
                //     #if defined TEMP_AMBIENT_CHN
                //         case TEMP_AMBIENT_CHN:
                //             SERIAL_PROTOCOLLN("ADC channel: TEMP_AMBIENT_CHN");                        
                //             SERIAL_PROTOCOL("Channel: ");
                //             SERIAL_PROTOCOL_F(chn, DEC);
                //             SERIAL_PROTOCOL("   adc_channel_idx: ");
                //             SERIAL_PROTOCOLLNE(adc_channel_idx, DEC);
                //             break;
                //     #endif  // TEMP_AMBIENT_CHN
                //     #if defined VOLT_IR_CHN           
                //         case (VOLT_IR_CHN):
                //             SERIAL_PROTOCOLLN("ADC channel: VOLT_IR_CHN");
                //             SERIAL_PROTOCOL("Channel: ");
                //             SERIAL_PROTOCOL_F(chn, DEC);
                //             SERIAL_PROTOCOL("   adc_channel_idx: ");
                //             SERIAL_PROTOCOLLNE(adc_channel_idx, DEC);
                //             break;
                //     #endif  // VOLT_IR_CHN
                //     #if defined VOLT_BED_CHN
                //         case (VOLT_BED_CHN):
                //             SERIAL_PROTOCOLLN("ADC channel: VOLT_BED_CHN");
                //             SERIAL_PROTOCOL("Channel: ");
                //             SERIAL_PROTOCOL_F(chn, DEC);
                //             SERIAL_PROTOCOL("   adc_channel_idx: ");
                //             SERIAL_PROTOCOLLNE(adc_channel_idx, DEC);
                //             break;
                //     #endif  // VOLT_BED_CHN
                //         default:
                //             SERIAL_PROTOCOLLN("ADC ERROR: Incorrect channel selected!");
                //             SERIAL_PROTOCOL("Channel: ");
                //             SERIAL_PROTOCOL_F(chn, DEC);
                //             SERIAL_PROTOCOL("   adc_channel_idx: ");
                //             SERIAL_PROTOCOLLNE(adc_channel_idx, DEC);
                //             break;
                // }

                break;
            }          
        }
    }
    ADCSRA |= (1 << ADSC); //start conversion
}
